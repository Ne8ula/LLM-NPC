#include "GestureRecognitionComponent.h"
#include "LLM_NPC/Vision/CameraManagerSubsystem.h"
#include "HandLandmarkModel.h"
#include "GestureClassifier.h"
#include "Engine/GameInstance.h"
#include "TimerManager.h"
#include "HAL/PlatformTime.h"

DEFINE_LOG_CATEGORY_STATIC(LogGestureRecognition, Log, All);

UGestureRecognitionComponent::UGestureRecognitionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SubsystemName = TEXT("GestureRecognition");
}

void UGestureRecognitionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UGestureRecognitionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ShutdownSubsystem();
	Super::EndPlay(EndPlayReason);
}

void UGestureRecognitionComponent::InitializeSubsystem()
{
	Super::InitializeSubsystem();

	// Get the camera manager subsystem
	if (UGameInstance* GI = GetOwner()->GetGameInstance())
	{
		CameraManager = GI->GetSubsystem<UCameraManagerSubsystem>();
	}

	if (!CameraManager.IsValid())
	{
		UE_LOG(LogGestureRecognition, Warning, TEXT("CameraManagerSubsystem not available."));
		bIsAvailable = false;
		return;
	}

	// Create hand landmark model
	HandLandmarkModel = NewObject<UHandLandmarkModel>(this);
	if (!HandLandmarkModelPath.IsEmpty())
	{
		if (!HandLandmarkModel->LoadModel(HandLandmarkModelPath))
		{
			UE_LOG(LogGestureRecognition, Warning, TEXT("Failed to load hand landmark model from: %s"), *HandLandmarkModelPath);
		}
	}

	// Create gesture classifier
	GestureClassifier = NewObject<UGestureClassifier>(this);

	// Start periodic processing timer
	LastProcessTime = FPlatformTime::Seconds();
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(
			ProcessingTimerHandle,
			this,
			&UGestureRecognitionComponent::ProcessFrame,
			ProcessingInterval,
			true); // bLoop
	}

	bIsAvailable = CameraManager.IsValid() && CameraManager->IsCameraAvailable();
	UE_LOG(LogGestureRecognition, Log, TEXT("GestureRecognition subsystem initialized. Available: %s"),
		bIsAvailable ? TEXT("true") : TEXT("false"));
}

void UGestureRecognitionComponent::ShutdownSubsystem()
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(ProcessingTimerHandle);
	}

	if (GestureClassifier)
	{
		GestureClassifier->Reset();
	}

	HandLandmarkModel = nullptr;
	GestureClassifier = nullptr;

	Super::ShutdownSubsystem();
}

bool UGestureRecognitionComponent::IsSubsystemAvailable() const
{
	return bIsInitialized && bIsAvailable
		&& CameraManager.IsValid()
		&& CameraManager->IsCameraAvailable();
}

void UGestureRecognitionComponent::ProcessFrame()
{
	if (!CameraManager.IsValid() || !CameraManager->IsCameraAvailable())
	{
		return;
	}

	if (!HandLandmarkModel || !HandLandmarkModel->IsModelLoaded() || !GestureClassifier)
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

	// Compute delta time
	const double CurrentTime = FPlatformTime::Seconds();
	const float DeltaTime = static_cast<float>(CurrentTime - LastProcessTime);
	LastProcessTime = CurrentTime;

	if (DeltaTime <= 0.0f)
	{
		return;
	}

	// Detect hand landmarks
	TArray<FVector2D> Landmarks;
	if (!HandLandmarkModel->DetectHandLandmarks(FrameData, Width, Height, Landmarks))
	{
		return;
	}

	// Classify gesture
	FGestureInput DetectedGesture = GestureClassifier->ClassifyGesture(Landmarks, DeltaTime);

	// Only broadcast if a meaningful gesture was detected
	if (DetectedGesture.GestureType != EGestureType::None && DetectedGesture.Confidence > 0.0f)
	{
		OnGestureDetected.Broadcast(DetectedGesture);
	}
}
