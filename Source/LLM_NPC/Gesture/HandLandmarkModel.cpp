#include "HandLandmarkModel.h"

#if WITH_ONNXRUNTIME
#include "onnxruntime_cxx_api.h"
#endif

DEFINE_LOG_CATEGORY_STATIC(LogHandLandmark, Log, All);

UHandLandmarkModel::UHandLandmarkModel()
{
}

UHandLandmarkModel::~UHandLandmarkModel()
{
#if WITH_ONNXRUNTIME
	if (OrtSession)
	{
		Ort::Session* Session = static_cast<Ort::Session*>(OrtSession);
		delete Session;
		OrtSession = nullptr;
	}
	if (OrtEnvironment)
	{
		Ort::Env* Env = static_cast<Ort::Env*>(OrtEnvironment);
		delete Env;
		OrtEnvironment = nullptr;
	}
#endif
}

bool UHandLandmarkModel::LoadModel(const FString& ModelPath)
{
#if WITH_ONNXRUNTIME
	try
	{
		Ort::Env* Env = new Ort::Env(ORT_LOGGING_LEVEL_WARNING, "HandLandmark");
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
		UE_LOG(LogHandLandmark, Log, TEXT("Hand landmark ONNX model loaded from: %s"), *ModelPath);
		return true;
	}
	catch (const Ort::Exception& Exception)
	{
		UE_LOG(LogHandLandmark, Error, TEXT("Failed to load hand landmark model: %hs"), Exception.what());
		bModelLoaded = false;
		return false;
	}
#else
	UE_LOG(LogHandLandmark, Warning, TEXT("ONNX Runtime not available. Hand landmark model loading skipped."));
	return false;
#endif
}

bool UHandLandmarkModel::DetectHandLandmarks(const TArray<uint8>& FrameData, int32 Width, int32 Height,
	TArray<FVector2D>& OutLandmarks)
{
	OutLandmarks.Empty();

	if (!bModelLoaded || FrameData.Num() == 0 || Width <= 0 || Height <= 0)
	{
		return false;
	}

	// Preprocess frame
	TArray<float> InputTensor = Preprocess(FrameData, Width, Height);

	// Run inference
	TArray<float> RawOutput = RunInference(InputTensor);

	// Expected output: 21 landmarks x 2 coordinates (x, y) = 42 floats
	if (RawOutput.Num() < NumLandmarks * 2)
	{
		return false;
	}

	OutLandmarks.Reserve(NumLandmarks);
	for (int32 i = 0; i < NumLandmarks; ++i)
	{
		float X = FMath::Clamp(RawOutput[i * 2], 0.0f, 1.0f);
		float Y = FMath::Clamp(RawOutput[i * 2 + 1], 0.0f, 1.0f);
		OutLandmarks.Add(FVector2D(X, Y));
	}

	return true;
}

TArray<float> UHandLandmarkModel::Preprocess(const TArray<uint8>& FrameData, int32 Width, int32 Height)
{
	// Target: InputSize x InputSize x 3 channels, normalized to [0, 1]
	// Layout: CHW (channels first) for ONNX convention
	const int32 NumChannels = 3;
	const int32 TensorSize = NumChannels * InputSize * InputSize;
	TArray<float> OutputTensor;
	OutputTensor.SetNumZeroed(TensorSize);

	if (FrameData.Num() == 0 || Width <= 0 || Height <= 0)
	{
		return OutputTensor;
	}

	const int32 SrcChannels = FrameData.Num() / (Width * Height);

	for (int32 y = 0; y < InputSize; ++y)
	{
		for (int32 x = 0; x < InputSize; ++x)
		{
			// Nearest-neighbor resize
			const int32 SrcX = FMath::Clamp(x * Width / InputSize, 0, Width - 1);
			const int32 SrcY = FMath::Clamp(y * Height / InputSize, 0, Height - 1);
			const int32 SrcIdx = (SrcY * Width + SrcX) * SrcChannels;

			for (int32 C = 0; C < NumChannels; ++C)
			{
				float Value = 0.0f;
				if (C < SrcChannels)
				{
					Value = static_cast<float>(FrameData[SrcIdx + C]) / 255.0f;
				}

				// CHW layout: [channel][y][x]
				const int32 DstIdx = C * InputSize * InputSize + y * InputSize + x;
				OutputTensor[DstIdx] = Value;
			}
		}
	}

	return OutputTensor;
}

TArray<float> UHandLandmarkModel::RunInference(const TArray<float>& InputTensor)
{
	TArray<float> Output;

#if WITH_ONNXRUNTIME
	if (!OrtSession || !OrtEnvironment)
	{
		return Output;
	}

	try
	{
		Ort::Session* Session = static_cast<Ort::Session*>(OrtSession);
		Ort::MemoryInfo MemInfo = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);

		// Input shape: [1, 3, 224, 224]
		std::array<int64_t, 4> InputShape = {1, 3, InputSize, InputSize};
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

		auto& OutputTensor = OutputTensors[0];
		auto TypeInfo = OutputTensor.GetTensorTypeAndShapeInfo();
		const size_t OutputCount = TypeInfo.GetElementCount();
		const float* OutputData = OutputTensor.GetTensorData<float>();

		Output.SetNumUninitialized(static_cast<int32>(OutputCount));
		FMemory::Memcpy(Output.GetData(), OutputData, OutputCount * sizeof(float));
	}
	catch (const Ort::Exception& Exception)
	{
		UE_LOG(LogHandLandmark, Error, TEXT("Hand landmark inference failed: %hs"), Exception.what());
	}
#endif

	return Output;
}
