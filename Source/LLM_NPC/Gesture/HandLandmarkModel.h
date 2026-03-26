#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HandLandmarkModel.generated.h"

/**
 * ONNX-based hand landmark detection model (MediaPipe-style).
 * Detects 21 hand landmarks and returns them as normalized (0-1) x,y coordinates.
 */
UCLASS(BlueprintType)
class FLLM_NPC_API UHandLandmarkModel : public UObject
{
	GENERATED_BODY()

public:
	UHandLandmarkModel();
	virtual ~UHandLandmarkModel();

	/**
	 * Load the ONNX model from disk.
	 * @param ModelPath  Absolute or project-relative path to the .onnx file.
	 * @return true if the model was loaded successfully.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Gesture")
	bool LoadModel(const FString& ModelPath);

	/**
	 * Detect 21 hand landmarks in the given frame.
	 * @param FrameData     Raw BGR pixel data.
	 * @param Width         Frame width in pixels.
	 * @param Height        Frame height in pixels.
	 * @param OutLandmarks  Output array of 21 normalized (0-1) 2D coordinates.
	 * @return true if a hand was detected with landmarks.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Gesture")
	bool DetectHandLandmarks(const TArray<uint8>& FrameData, int32 Width, int32 Height,
		TArray<FVector2D>& OutLandmarks);

	/** Whether a model has been loaded. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Gesture")
	bool IsModelLoaded() const { return bModelLoaded; }

	/** Number of landmarks detected by this model. */
	static constexpr int32 NumLandmarks = 21;

private:
	/** Preprocess frame for hand landmark model: resize to 224x224, normalize to [0,1]. */
	TArray<float> Preprocess(const TArray<uint8>& FrameData, int32 Width, int32 Height);

	/** Run ONNX inference and return raw landmark coordinates. */
	TArray<float> RunInference(const TArray<float>& InputTensor);

	bool bModelLoaded = false;

	// ONNX Runtime handles (opaque pointers, managed behind WITH_ONNXRUNTIME guard)
	void* OrtSession = nullptr;
	void* OrtEnvironment = nullptr;

	/** Input image size expected by the model. */
	static constexpr int32 InputSize = 224;
};
