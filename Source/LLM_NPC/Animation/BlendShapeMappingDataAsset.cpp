#include "BlendShapeMappingDataAsset.h"

TArray<FEmotionBlendShapeTarget> UBlendShapeMappingDataAsset::GetTargetsForState(const FEmotionState& State) const
{
	for (const FEmotionBlendShapeMapping& Mapping : Mappings)
	{
		if (Mapping.EmotionType == State.PrimaryEmotion &&
			State.Intensity >= Mapping.MinIntensity &&
			State.Intensity <= Mapping.MaxIntensity)
		{
			// Scale blend shape values by intensity
			TArray<FEmotionBlendShapeTarget> ScaledTargets = Mapping.BlendShapeTargets;
			for (FEmotionBlendShapeTarget& Target : ScaledTargets)
			{
				Target.TargetValue *= State.Intensity;
			}
			return ScaledTargets;
		}
	}

	return TArray<FEmotionBlendShapeTarget>();
}

void UBlendShapeMappingDataAsset::PopulateDefaultMetahumanMappings()
{
	Mappings.Empty();

	// Helper lambda to create a mapping
	auto AddMapping = [this](EEmotionType Emotion, TArray<TPair<FName, float>> Targets)
	{
		FEmotionBlendShapeMapping Mapping;
		Mapping.EmotionType = Emotion;
		Mapping.MinIntensity = 0.0f;
		Mapping.MaxIntensity = 1.0f;

		for (const auto& Pair : Targets)
		{
			FEmotionBlendShapeTarget Target;
			Target.BlendShapeName = Pair.Key;
			Target.TargetValue = Pair.Value;
			Mapping.BlendShapeTargets.Add(Target);
		}

		Mappings.Add(Mapping);
	};

	// Neutral — relaxed face (no blend shapes active)
	AddMapping(EEmotionType::Neutral, {});

	// Joy — smile, cheeks up, eyes slightly narrowed
	AddMapping(EEmotionType::Joy, {
		{FName("mouthSmile_L"), 0.8f},
		{FName("mouthSmile_R"), 0.8f},
		{FName("cheekSquint_L"), 0.5f},
		{FName("cheekSquint_R"), 0.5f},
		{FName("eyeSquint_L"), 0.3f},
		{FName("eyeSquint_R"), 0.3f},
	});

	// Sadness — inner brow up, frown, mouth down
	AddMapping(EEmotionType::Sadness, {
		{FName("browInnerUp"), 0.7f},
		{FName("browDown_L"), 0.2f},
		{FName("browDown_R"), 0.2f},
		{FName("mouthFrown_L"), 0.6f},
		{FName("mouthFrown_R"), 0.6f},
		{FName("mouthPucker"), 0.2f},
		{FName("eyeSquint_L"), 0.2f},
		{FName("eyeSquint_R"), 0.2f},
	});

	// Anger — brows down, jaw clench, nose flare
	AddMapping(EEmotionType::Anger, {
		{FName("browDown_L"), 0.8f},
		{FName("browDown_R"), 0.8f},
		{FName("jawForward"), 0.3f},
		{FName("mouthFrown_L"), 0.4f},
		{FName("mouthFrown_R"), 0.4f},
		{FName("noseSneer_L"), 0.5f},
		{FName("noseSneer_R"), 0.5f},
		{FName("eyeSquint_L"), 0.4f},
		{FName("eyeSquint_R"), 0.4f},
	});

	// Fear — wide eyes, raised brows, open mouth
	AddMapping(EEmotionType::Fear, {
		{FName("browInnerUp"), 0.8f},
		{FName("browOuterUp_L"), 0.6f},
		{FName("browOuterUp_R"), 0.6f},
		{FName("eyeWide_L"), 0.7f},
		{FName("eyeWide_R"), 0.7f},
		{FName("jawOpen"), 0.3f},
		{FName("mouthStretch_L"), 0.3f},
		{FName("mouthStretch_R"), 0.3f},
	});

	// Surprise — raised brows, wide eyes, open mouth
	AddMapping(EEmotionType::Surprise, {
		{FName("browInnerUp"), 0.9f},
		{FName("browOuterUp_L"), 0.8f},
		{FName("browOuterUp_R"), 0.8f},
		{FName("eyeWide_L"), 0.8f},
		{FName("eyeWide_R"), 0.8f},
		{FName("jawOpen"), 0.5f},
	});

	// Disgust — nose wrinkle, upper lip raise, squint
	AddMapping(EEmotionType::Disgust, {
		{FName("noseSneer_L"), 0.8f},
		{FName("noseSneer_R"), 0.8f},
		{FName("mouthUpperUp_L"), 0.5f},
		{FName("mouthUpperUp_R"), 0.5f},
		{FName("browDown_L"), 0.4f},
		{FName("browDown_R"), 0.4f},
		{FName("eyeSquint_L"), 0.3f},
		{FName("eyeSquint_R"), 0.3f},
	});

	// Trust — gentle smile, relaxed brows
	AddMapping(EEmotionType::Trust, {
		{FName("mouthSmile_L"), 0.5f},
		{FName("mouthSmile_R"), 0.5f},
		{FName("cheekSquint_L"), 0.3f},
		{FName("cheekSquint_R"), 0.3f},
		{FName("browInnerUp"), 0.2f},
	});

	// Anticipation — slight brow raise, focused eyes, slight smile
	AddMapping(EEmotionType::Anticipation, {
		{FName("browInnerUp"), 0.4f},
		{FName("browOuterUp_L"), 0.3f},
		{FName("browOuterUp_R"), 0.3f},
		{FName("eyeWide_L"), 0.2f},
		{FName("eyeWide_R"), 0.2f},
		{FName("mouthSmile_L"), 0.2f},
		{FName("mouthSmile_R"), 0.2f},
	});

	UE_LOG(LogTemp, Log, TEXT("BlendShapeMapping: Populated %d default Metahuman mappings"), Mappings.Num());
}
