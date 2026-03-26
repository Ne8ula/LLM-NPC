#include "FaceExpressionModel.h"
#include "HAL/PlatformTime.h"

#if WITH_ONNXRUNTIME
#include "onnxruntime_cxx_api.h"
#endif

DEFINE_LOG_CATEGORY_STATIC(LogFaceExpression, Log, All);

// 7-class lookup: trpakov/vit-face-expression ordering (FER-2013 standard)
const EEmotionType UFaceExpressionModel::EmotionLookupTable[7] = {
	EEmotionType::Anger,     // 0 - angry
	EEmotionType::Disgust,   // 1 - disgust
	EEmotionType::Fear,      // 2 - fear
	EEmotionType::Joy,       // 3 - happy
	EEmotionType::Sadness,   // 4 - sad
	EEmotionType::Surprise,  // 5 - surprise
	EEmotionType::Neutral    // 6 - neutral
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

	// Preprocess: resize to 224x224 RGB, normalize with ImageNet mean/std
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
	// Target: 224x224 RGB normalized with ImageNet mean/std for ViT model
	// trpakov/vit-face-expression uses standard ImageNet preprocessing
	static constexpr int32 TargetSize = 224;
	static constexpr int32 NumOutputChannels = 3;

	// ImageNet normalization constants
	static constexpr float Mean[3] = {0.485f, 0.456f, 0.406f}; // R, G, B
	static constexpr float Std[3] = {0.229f, 0.224f, 0.225f};

	TArray<float> OutputTensor;
	OutputTensor.SetNumZeroed(NumOutputChannels * TargetSize * TargetSize);

	if (FaceROI.Num() == 0 || Width <= 0 || Height <= 0)
	{
		return OutputTensor;
	}

	// Determine number of channels from data size
	const int32 TotalPixels = Width * Height;
	const int32 NumChannels = FaceROI.Num() / TotalPixels;

	// ViT expects CHW format (channels first): [3, 224, 224]
	for (int32 y = 0; y < TargetSize; ++y)
	{
		for (int32 x = 0; x < TargetSize; ++x)
		{
			// Nearest-neighbor resize
			const int32 SrcX = FMath::Clamp(x * Width / TargetSize, 0, Width - 1);
			const int32 SrcY = FMath::Clamp(y * Height / TargetSize, 0, Height - 1);
			const int32 SrcIdx = (SrcY * Width + SrcX) * NumChannels;

			float R, G, B;
			if (NumChannels >= 3)
			{
				// Input is BGR from OpenCV
				B = static_cast<float>(FaceROI[SrcIdx]) / 255.0f;
				G = static_cast<float>(FaceROI[SrcIdx + 1]) / 255.0f;
				R = static_cast<float>(FaceROI[SrcIdx + 2]) / 255.0f;
			}
			else
			{
				// Grayscale: replicate to all channels
				float Gray = static_cast<float>(FaceROI[SrcIdx]) / 255.0f;
				R = G = B = Gray;
			}

			// ImageNet normalization: (pixel - mean) / std
			// CHW layout: channel 0 = R, channel 1 = G, channel 2 = B
			const int32 PixelOffset = y * TargetSize + x;
			OutputTensor[0 * TargetSize * TargetSize + PixelOffset] = (R - Mean[0]) / Std[0];
			OutputTensor[1 * TargetSize * TargetSize + PixelOffset] = (G - Mean[1]) / Std[1];
			OutputTensor[2 * TargetSize * TargetSize + PixelOffset] = (B - Mean[2]) / Std[2];
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

		// Input shape: [1, 3, 224, 224] (batch, channels, height, width) for ViT
		std::array<int64_t, 4> InputShape = {1, 3, 224, 224};
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
