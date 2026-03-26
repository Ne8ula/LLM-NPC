#include "FacialRecognitionComponent.h"
#include "CameraManagerSubsystem.h"
#include "FaceExpressionModel.h"
#include "Engine/GameInstance.h"
#include "TimerManager.h"

#if WITH_OPENCV
#include "PreOpenCVHeaders.h"
#include "opencv2/dnn.hpp"
#include "opencv2/imgproc.hpp"
#include "PostOpenCVHeaders.h"
#endif

DEFINE_LOG_CATEGORY_STATIC(LogFacialRecognition, Log, All);

UFacialRecognitionComponent::UFacialRecognitionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SubsystemName = TEXT("FacialRecognition");
}

void UFacialRecognitionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UFacialRecognitionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ShutdownSubsystem();
	Super::EndPlay(EndPlayReason);
}

void UFacialRecognitionComponent::InitializeSubsystem()
{
	Super::InitializeSubsystem();

	// Get the camera manager subsystem
	if (UGameInstance* GI = GetOwner()->GetGameInstance())
	{
		CameraManager = GI->GetSubsystem<UCameraManagerSubsystem>();
	}

	if (!CameraManager.IsValid())
	{
		UE_LOG(LogFacialRecognition, Warning, TEXT("CameraManagerSubsystem not available."));
		bIsAvailable = false;
		return;
	}

	// Create and load the expression model
	ExpressionModel = NewObject<UFaceExpressionModel>(this);
	if (!ExpressionModelPath.IsEmpty())
	{
		if (!ExpressionModel->LoadModel(ExpressionModelPath))
		{
			UE_LOG(LogFacialRecognition, Warning, TEXT("Failed to load expression model from: %s"), *ExpressionModelPath);
		}
	}

	// Load OpenCV DNN face detection model
#if WITH_OPENCV
	if (!FaceDetectionModelPath.IsEmpty() && !FaceDetectionConfigPath.IsEmpty())
	{
		try
		{
			cv::dnn::Net* Net = new cv::dnn::Net(cv::dnn::readNet(
				TCHAR_TO_UTF8(*FaceDetectionModelPath),
				TCHAR_TO_UTF8(*FaceDetectionConfigPath)));
			FaceDetectionNet = static_cast<void*>(Net);
			UE_LOG(LogFacialRecognition, Log, TEXT("Face detection DNN model loaded."));
		}
		catch (const cv::Exception& Ex)
		{
			UE_LOG(LogFacialRecognition, Error, TEXT("Failed to load face detection model: %hs"), Ex.what());
			FaceDetectionNet = nullptr;
		}
	}
#endif

	// Start periodic processing timer
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(
			ProcessingTimerHandle,
			this,
			&UFacialRecognitionComponent::ProcessFrame,
			ProcessingInterval,
			true); // bLoop
	}

	bIsAvailable = CameraManager.IsValid() && CameraManager->IsCameraAvailable();
	UE_LOG(LogFacialRecognition, Log, TEXT("FacialRecognition subsystem initialized. Available: %s"),
		bIsAvailable ? TEXT("true") : TEXT("false"));
}

void UFacialRecognitionComponent::ShutdownSubsystem()
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(ProcessingTimerHandle);
	}

#if WITH_OPENCV
	if (FaceDetectionNet)
	{
		cv::dnn::Net* Net = static_cast<cv::dnn::Net*>(FaceDetectionNet);
		delete Net;
		FaceDetectionNet = nullptr;
	}
#endif

	ExpressionModel = nullptr;
	Super::ShutdownSubsystem();
}

bool UFacialRecognitionComponent::IsSubsystemAvailable() const
{
	return bIsInitialized && bIsAvailable
		&& CameraManager.IsValid()
		&& CameraManager->IsCameraAvailable();
}

void UFacialRecognitionComponent::ProcessFrame()
{
	if (!CameraManager.IsValid() || !CameraManager->IsCameraAvailable())
	{
		return;
	}

	TArray<uint8> FrameData;
	int32 Width = 0;
	int32 Height = 0;

	if (!CameraManager->GetLatestFrame(FrameData, Width, Height))
	{
		return;
	}

	// Detect face bounding box
	int32 FaceX = 0, FaceY = 0, FaceW = 0, FaceH = 0;
	if (!DetectFace(FrameData, Width, Height, FaceX, FaceY, FaceW, FaceH))
	{
		return;
	}

	// Crop face ROI
	TArray<uint8> FaceROI = CropFaceROI(FrameData, Width, Height, FaceX, FaceY, FaceW, FaceH);

	if (FaceROI.Num() == 0 || !ExpressionModel || !ExpressionModel->IsModelLoaded())
	{
		return;
	}

	// Classify emotion
	FDetectedUserEmotion DetectedEmotion = ExpressionModel->Classify(FaceROI, FaceW, FaceH);

	// Broadcast to listeners
	OnUserEmotionDetected.Broadcast(DetectedEmotion);
}

bool UFacialRecognitionComponent::DetectFace(const TArray<uint8>& FrameData, int32 Width, int32 Height,
	int32& OutX, int32& OutY, int32& OutW, int32& OutH)
{
#if WITH_OPENCV
	if (!FaceDetectionNet || FrameData.Num() == 0)
	{
		return false;
	}

	cv::dnn::Net* Net = static_cast<cv::dnn::Net*>(FaceDetectionNet);

	// Reconstruct cv::Mat from raw BGR data
	cv::Mat Frame(Height, Width, CV_8UC3, const_cast<uint8*>(FrameData.GetData()));

	// Create input blob: 300x300, scale 1.0, mean (104, 177, 123)
	cv::Mat Blob = cv::dnn::blobFromImage(Frame, 1.0, cv::Size(300, 300),
		cv::Scalar(104.0, 177.0, 123.0), false, false);

	Net->setInput(Blob);
	cv::Mat Detections = Net->forward();

	// Detections shape: [1, 1, N, 7] where columns are:
	// [batch_id, class_id, confidence, x_min, y_min, x_max, y_max]
	const float* Data = reinterpret_cast<float*>(Detections.data);
	const int32 NumDetections = Detections.size[2];

	float BestConfidence = 0.0f;
	int32 BestIdx = -1;

	for (int32 i = 0; i < NumDetections; ++i)
	{
		const float Confidence = Data[i * 7 + 2];
		if (Confidence > FaceDetectionConfidence && Confidence > BestConfidence)
		{
			BestConfidence = Confidence;
			BestIdx = i;
		}
	}

	if (BestIdx < 0)
	{
		return false;
	}

	// Convert normalized coordinates to pixel coordinates
	const float XMin = FMath::Clamp(Data[BestIdx * 7 + 3], 0.0f, 1.0f);
	const float YMin = FMath::Clamp(Data[BestIdx * 7 + 4], 0.0f, 1.0f);
	const float XMax = FMath::Clamp(Data[BestIdx * 7 + 5], 0.0f, 1.0f);
	const float YMax = FMath::Clamp(Data[BestIdx * 7 + 6], 0.0f, 1.0f);

	OutX = FMath::RoundToInt(XMin * Width);
	OutY = FMath::RoundToInt(YMin * Height);
	OutW = FMath::RoundToInt((XMax - XMin) * Width);
	OutH = FMath::RoundToInt((YMax - YMin) * Height);

	return OutW > 0 && OutH > 0;
#else
	return false;
#endif
}

TArray<uint8> UFacialRecognitionComponent::CropFaceROI(const TArray<uint8>& FrameData, int32 FrameWidth, int32 FrameHeight,
	int32 FaceX, int32 FaceY, int32 FaceW, int32 FaceH)
{
	TArray<uint8> CroppedROI;

	if (FrameData.Num() == 0 || FaceW <= 0 || FaceH <= 0)
	{
		return CroppedROI;
	}

	// Assume 3 channels (BGR)
	static constexpr int32 NumChannels = 3;
	CroppedROI.SetNumUninitialized(FaceW * FaceH * NumChannels);

	for (int32 Row = 0; Row < FaceH; ++Row)
	{
		const int32 SrcRow = FMath::Clamp(FaceY + Row, 0, FrameHeight - 1);
		for (int32 Col = 0; Col < FaceW; ++Col)
		{
			const int32 SrcCol = FMath::Clamp(FaceX + Col, 0, FrameWidth - 1);
			const int32 SrcIdx = (SrcRow * FrameWidth + SrcCol) * NumChannels;
			const int32 DstIdx = (Row * FaceW + Col) * NumChannels;

			for (int32 C = 0; C < NumChannels; ++C)
			{
				CroppedROI[DstIdx + C] = FrameData[SrcIdx + C];
			}
		}
	}

	return CroppedROI;
}
