#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "FaceExpressionModel.generated.h"

/**
 * Wraps ONNX Runtime inference for facial expression classification.
 * Uses trpakov/vit-face-expression (ViT-base) model from HuggingFace.
 * Preprocesses face ROI to 224x224 RGB and runs a 7-class emotion model.
 * Temporal smoothing via exponential moving average prevents noisy flickering.
 * A new dominant emotion is only reported after persisting for 0.5 seconds.
 */
UCLASS(BlueprintType)
class LLM_NPC_API UFaceExpressionModel : public UObject
{
	GENERATED_BODY()

public:
	UFaceExpressionModel();

	/**
	 * Load the ONNX model from disk.
	 * @param ModelPath  Absolute or project-relative path to the .onnx file.
	 * @return true if the model was loaded successfully.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Vision")
	bool LoadModel(const FString& ModelPath);

	/**
	 * Classify the emotion in a cropped face region of interest.
	 * @param FaceROI  Raw pixel data (BGR) of the cropped face.
	 * @param Width    Width of the face ROI in pixels.
	 * @param Height   Height of the face ROI in pixels.
	 * @return Detected emotion with confidence and probability map.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Vision")
	FDetectedUserEmotion Classify(const TArray<uint8>& FaceROI, int32 Width, int32 Height);

	/** Whether a model has been loaded. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Vision")
	bool IsModelLoaded() const { return bModelLoaded; }

private:
	/** Preprocess face ROI: resize to 224x224 RGB, normalize with ImageNet mean/std. */
	TArray<float> Preprocess(const TArray<uint8>& FaceROI, int32 Width, int32 Height);

	/** Run inference and return raw softmax probabilities for 7 classes. */
	TArray<float> RunInference(const TArray<float>& InputTensor);

	/** Map class index (0-6) to EEmotionType. */
	static EEmotionType IndexToEmotion(int32 Index);

	/** Apply exponential moving average smoothing to raw probabilities. */
	void ApplyTemporalSmoothing(const TArray<float>& RawProbabilities);

	/** Check if the dominant emotion has persisted long enough to report. */
	bool HasDominantEmotionPersisted() const;

	// Model state
	bool bModelLoaded = false;

	// ONNX Runtime session handle (opaque pointer, managed behind WITH_ONNXRUNTIME guard)
	void* OrtSession = nullptr;
	void* OrtEnvironment = nullptr;

	// Smoothing state
	static constexpr int32 NumClasses = 7;
	static constexpr int32 SmoothingWindow = 10;
	static constexpr float SmoothingAlpha = 0.3f;
	static constexpr float PersistenceThreshold = 0.5f; // seconds

	TArray<float> SmoothedProbabilities;
	EEmotionType CurrentDominantEmotion = EEmotionType::Neutral;
	EEmotionType LastReportedEmotion = EEmotionType::Neutral;
	double DominantEmotionStartTime = 0.0;

	/** 7-class lookup table matching trpakov/vit-face-expression ordering:
	 *  0=Angry, 1=Disgust, 2=Fear, 3=Happy, 4=Sad, 5=Surprise, 6=Neutral */
	static const EEmotionType EmotionLookupTable[7];
};
