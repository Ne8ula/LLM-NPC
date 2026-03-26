#include "FaceExpressionModel.h"
#include "HAL/PlatformTime.h"

#if WITH_ONNXRUNTIME
#include "onnxruntime_cxx_api.h"
#endif

DEFINE_LOG_CATEGORY_STATIC(LogFaceExpression, Log, All);

// 7-class lookup: standard FER-2013 ordering
const EEmotionType UFaceExpressionModel::EmotionLookupTable[7] = {
	EEmotionType::Neutral,   // 0
	EEmotionType::Joy,       // 1
	EEmotionType::Sadness,   // 2
	EEmotionType::Anger,     // 3
	EEmotionType::Fear,      // 4
	EEmotionType::Surprise,  // 5
	EEmotionType::Disgust    // 6
};

UFaceExpressionModel::UFaceExpressionModel()
{
	SmoothedProbabilities.SetNumZeroed(NumClasses);
	// Initialize neutral as dominant
	SmoothedProbabilities[0] = 1.0f;
}

bool UFaceExpressionModel::LoadModel(const FString& ModelPath)
{
#if WITH_ONNXRUNTIME
	try
	{
		// Create ONNX Runtime environment and session
		Ort::Env* Env = new Ort::Env(ORT_LOGGING_LEVEL_WARNING, "FaceExpression");
		OrtEnvironment = static_cast<void*>(Env);

		Ort::SessionOptions SessionOptions;
		SessionOptions.SetIntraOpNumThreads(1);
		SessionOptions.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_EXTENDED);

#if PLATFORM_WINDOWS
		Ort::Session* Session = new Ort::Session(*Env, *ModelPath, SessionOptions);
#else
		Ort::Session* Session = new Ort::Session(*Env, TCHAR_TO_UTF8(*ModelPath), SessionOptions);
#endif
		OrtSession = static_cast<void*>(Session);

		bModelLoaded = true;
		UE_LOG(LogFaceExpression, Log, TEXT("ONNX model loaded from: %s"), *ModelPath);
		return true;
	}
	catch (const Ort::Exception& Exception)
	{
		UE_LOG(LogFaceExpression, Error, TEXT("Failed to load ONNX model: %hs"), Exception.what());
		bModelLoaded = false;
		return false;
	}
#else
	UE_LOG(LogFaceExpression, Warning, TEXT("ONNX Runtime not available. Model loading skipped."));
	return false;
#endif
}

FDetectedUserEmotion UFaceExpressionModel::Classify(const TArray<uint8>& FaceROI, int32 Width, int32 Height)
{
	FDetectedUserEmotion Result;
	Result.Timestamp = static_cast<float>(FPlatformTime::Seconds());

	if (!bModelLoaded || FaceROI.Num() == 0)
	{
		Result.Emotion = EEmotionType::Neutral;
		Result.Confidence = 0.0f;
		return Result;
	}

	// Preprocess: resize to 48x48 grayscale, normalize
	TArray<float> InputTensor = Preprocess(FaceROI, Width, Height);

	// Run ONNX inference
	TArray<float> RawProbabilities = RunInference(InputTensor);

	// Apply temporal smoothing (EMA)
	ApplyTemporalSmoothing(RawProbabilities);

	// Find dominant emotion from smoothed probabilities
	int32 DominantIndex = 0;
	float MaxProb = SmoothedProbabilities[0];
	for (int32 i = 1; i < NumClasses; ++i)
	{
		if (SmoothedProbabilities[i] > MaxProb)
		{
			MaxProb = SmoothedProbabilities[i];
			DominantIndex = i;
		}
	}

	EEmotionType DominantEmotion = IndexToEmotion(DominantIndex);

	// Track persistence of dominant emotion
	if (DominantEmotion != CurrentDominantEmotion)
	{
		CurrentDominantEmotion = DominantEmotion;
		DominantEmotionStartTime = FPlatformTime::Seconds();
	}

	// Only report change if persisted for 0.5s
	if (HasDominantEmotionPersisted())
	{
		LastReportedEmotion = CurrentDominantEmotion;
	}

	Result.Emotion = LastReportedEmotion;
	Result.Confidence = MaxProb;

	// Fill probability map
	for (int32 i = 0; i < NumClasses; ++i)
	{
		Result.Probabilities.Add(IndexToEmotion(i), SmoothedProbabilities[i]);
	}

	return Result;
}

TArray<float> UFaceExpressionModel::Preprocess(const TArray<uint8>& FaceROI, int32 Width, int32 Height)
{
	// Target: 48x48 grayscale normalized to [0, 1]
	static constexpr int32 TargetSize = 48;
	TArray<float> OutputTensor;
	OutputTensor.SetNumZeroed(TargetSize * TargetSize);

	if (FaceROI.Num() == 0 || Width <= 0 || Height <= 0)
	{
		return OutputTensor;
	}

	// Determine number of channels from data size
	const int32 TotalPixels = Width * Height;
	const int32 NumChannels = FaceROI.Num() / TotalPixels;

	for (int32 y = 0; y < TargetSize; ++y)
	{
		for (int32 x = 0; x < TargetSize; ++x)
		{
			// Nearest-neighbor resize
			const int32 SrcX = FMath::Clamp(x * Width / TargetSize, 0, Width - 1);
			const int32 SrcY = FMath::Clamp(y * Height / TargetSize, 0, Height - 1);
			const int32 SrcIdx = (SrcY * Width + SrcX) * NumChannels;

			float GrayValue;
			if (NumChannels >= 3)
			{
				// BGR to grayscale: 0.114*B + 0.587*G + 0.299*R
				GrayValue = 0.114f * FaceROI[SrcIdx]
					+ 0.587f * FaceROI[SrcIdx + 1]
					+ 0.299f * FaceROI[SrcIdx + 2];
			}
			else
			{
				GrayValue = static_cast<float>(FaceROI[SrcIdx]);
			}

			// Normalize to [0, 1]
			OutputTensor[y * TargetSize + x] = GrayValue / 255.0f;
		}
	}

	return OutputTensor;
}

TArray<float> UFaceExpressionModel::RunInference(const TArray<float>& InputTensor)
{
	TArray<float> Probabilities;
	Probabilities.SetNumZeroed(NumClasses);

#if WITH_ONNXRUNTIME
	if (!OrtSession || !OrtEnvironment)
	{
		Probabilities[0] = 1.0f; // Default to neutral
		return Probabilities;
	}

	try
	{
		Ort::Session* Session = static_cast<Ort::Session*>(OrtSession);
		Ort::MemoryInfo MemInfo = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);

		// Input shape: [1, 1, 48, 48] (batch, channels, height, width)
		std::array<int64_t, 4> InputShape = {1, 1, 48, 48};
		Ort::Value InputOrtTensor = Ort::Value::CreateTensor<float>(
			MemInfo,
			const_cast<float*>(InputTensor.GetData()),
			InputTensor.Num(),
			InputShape.data(),
			InputShape.size());

		const char* InputNames[] = {"input"};
		const char* OutputNames[] = {"output"};

		auto OutputTensors = Session->Run(
			Ort::RunOptions{nullptr},
			InputNames, &InputOrtTensor, 1,
			OutputNames, 1);

		const float* OutputData = OutputTensors[0].GetTensorData<float>();

		// Softmax
		float MaxVal = OutputData[0];
		for (int32 i = 1; i < NumClasses; ++i)
		{
			MaxVal = FMath::Max(MaxVal, OutputData[i]);
		}

		float SumExp = 0.0f;
		for (int32 i = 0; i < NumClasses; ++i)
		{
			Probabilities[i] = FMath::Exp(OutputData[i] - MaxVal);
			SumExp += Probabilities[i];
		}

		for (int32 i = 0; i < NumClasses; ++i)
		{
			Probabilities[i] /= SumExp;
		}
	}
	catch (const Ort::Exception& Exception)
	{
		UE_LOG(LogFaceExpression, Error, TEXT("ONNX inference failed: %hs"), Exception.what());
		Probabilities[0] = 1.0f;
	}
#else
	// Without ONNX, return neutral
	Probabilities[0] = 1.0f;
#endif

	return Probabilities;
}

EEmotionType UFaceExpressionModel::IndexToEmotion(int32 Index)
{
	if (Index >= 0 && Index < 7)
	{
		return EmotionLookupTable[Index];
	}
	return EEmotionType::Neutral;
}

void UFaceExpressionModel::ApplyTemporalSmoothing(const TArray<float>& RawProbabilities)
{
	if (RawProbabilities.Num() != NumClasses)
	{
		return;
	}

	// Exponential moving average: smoothed = alpha * raw + (1 - alpha) * smoothed
	for (int32 i = 0; i < NumClasses; ++i)
	{
		SmoothedProbabilities[i] = SmoothingAlpha * RawProbabilities[i]
			+ (1.0f - SmoothingAlpha) * SmoothedProbabilities[i];
	}
}

bool UFaceExpressionModel::HasDominantEmotionPersisted() const
{
	const double CurrentTime = FPlatformTime::Seconds();
	return (CurrentTime - DominantEmotionStartTime) >= PersistenceThreshold;
}
