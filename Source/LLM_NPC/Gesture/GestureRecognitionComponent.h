#pragma once

#include "CoreMinimal.h"
#include "LLM_NPC/Core/NPCSubsystemComponent.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "GestureRecognitionComponent.generated.h"

class UCameraManagerSubsystem;
class UHandLandmarkModel;
class UGestureClassifier;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGestureDetected, FGestureInput, DetectedGesture);

/**
 * NPC subsystem component that reads camera frames, detects hand landmarks
 * via an ONNX model, and classifies gestures using geometry-based analysis.
 * Processes at ~15 FPS using a timer (not tick-based).
 */
UCLASS(ClassGroup = (LLMNPC), meta = (BlueprintSpawnableComponent))
class LLM_NPC_API UGestureRecognitionComponent : public UNPCSubsystemComponent
{
	GENERATED_BODY()

public:
	UGestureRecognitionComponent();

	// UNPCSubsystemComponent interface
	virtual void InitializeSubsystem() override;
	virtual void ShutdownSubsystem() override;
	virtual bool IsSubsystemAvailable() const override;

	/** Fired when a gesture is detected from the camera feed. */
	UPROPERTY(BlueprintAssignable, Category = "NPC|Gesture")
	FOnGestureDetected OnGestureDetected;

	/** Path to the hand landmark ONNX model. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Gesture")
	FString HandLandmarkModelPath;

	/** Processing rate in seconds (default ~15 FPS = 0.066s interval). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Gesture", meta = (ClampMin = "0.016", ClampMax = "1.0"))
	float ProcessingInterval = 0.066f;

	/** Access the gesture classifier for tuning parameters. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Gesture")
	UGestureClassifier* GetGestureClassifier() const { return GestureClassifier; }

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	/** Timer callback for periodic frame processing. */
	void ProcessFrame();

	UPROPERTY()
	TObjectPtr<UHandLandmarkModel> HandLandmarkModel;

	UPROPERTY()
	TObjectPtr<UGestureClassifier> GestureClassifier;

	FTimerHandle ProcessingTimerHandle;

	/** Cached reference to the camera manager subsystem. */
	TWeakObjectPtr<UCameraManagerSubsystem> CameraManager;

	/** Timestamp of last processed frame for delta time computation. */
	double LastProcessTime = 0.0;
};
