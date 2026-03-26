#pragma once

#include "CoreMinimal.h"
#include "LLM_NPC/Core/NPCSubsystemComponent.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "FacialRecognitionComponent.generated.h"

class UCameraManagerSubsystem;
class UFaceExpressionModel;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUserEmotionDetected, FDetectedUserEmotion, DetectedEmotion);

/**
 * NPC subsystem component that reads camera frames, detects faces via
 * OpenCV DNN, and classifies facial expressions through an ONNX model.
 * Processes at ~10 FPS using a timer (not tick-based) to avoid overloading
 * the game thread.
 */
UCLASS(ClassGroup = (LLMNPC), meta = (BlueprintSpawnableComponent))
class FLLM_NPC_API UFacialRecognitionComponent : public UNPCSubsystemComponent
{
	GENERATED_BODY()

public:
	UFacialRecognitionComponent();

	// UNPCSubsystemComponent interface
	virtual void InitializeSubsystem() override;
	virtual void ShutdownSubsystem() override;
	virtual bool IsSubsystemAvailable() const override;

	/** Fired when a user emotion is detected from the camera feed. */
	UPROPERTY(BlueprintAssignable, Category = "NPC|Vision")
	FOnUserEmotionDetected OnUserEmotionDetected;

	/** Path to the facial expression ONNX model. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Vision")
	FString ExpressionModelPath;

	/** Path to the OpenCV DNN face detection model (Caffe or TensorFlow). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Vision")
	FString FaceDetectionModelPath;

	/** Path to the face detection model config (prototxt). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Vision")
	FString FaceDetectionConfigPath;

	/** Minimum confidence threshold for face detection. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Vision", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float FaceDetectionConfidence = 0.5f;

	/** Processing rate in seconds (default ~10 FPS = 0.1s interval). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Vision", meta = (ClampMin = "0.016", ClampMax = "1.0"))
	float ProcessingInterval = 0.1f;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	/** Timer callback for periodic frame processing. */
	void ProcessFrame();

	/**
	 * Run OpenCV DNN face detection on the frame.
	 * @return true if a face was found; OutX/Y/W/H define the bounding box.
	 */
	bool DetectFace(const TArray<uint8>& FrameData, int32 Width, int32 Height,
		int32& OutX, int32& OutY, int32& OutW, int32& OutH);

	/** Crop face ROI from frame data. */
	TArray<uint8> CropFaceROI(const TArray<uint8>& FrameData, int32 FrameWidth, int32 FrameHeight,
		int32 FaceX, int32 FaceY, int32 FaceW, int32 FaceH);

	UPROPERTY()
	TObjectPtr<UFaceExpressionModel> ExpressionModel;

	FTimerHandle ProcessingTimerHandle;

	/** Cached reference to the camera manager subsystem. */
	TWeakObjectPtr<UCameraManagerSubsystem> CameraManager;

	/** OpenCV DNN net handle (opaque pointer, managed behind WITH_OPENCV guard). */
	void* FaceDetectionNet = nullptr;
};
