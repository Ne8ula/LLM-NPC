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

	// Joy — smile (corner pull), cheeks up, eyes slightly narrowed
	AddMapping(EEmotionType::Joy, {
		{FName("head_lod0_mesh__mouth_cornerPull_left"), 0.8f},
		{FName("head_lod0_mesh__mouth_cornerPull_right"), 0.8f},
		{FName("head_lod0_mesh__eye_cheekRaise_L"), 0.5f},
		{FName("head_lod0_mesh__eye_cheekRaise_R"), 0.5f},
		{FName("head_lod0_mesh__eye_squintInner_L"), 0.3f},
		{FName("head_lod0_mesh__eye_squintInner_R"), 0.3f},
		{FName("head_lod0_mesh__mouth_dimple_left"), 0.3f},
		{FName("head_lod0_mesh__mouth_dimple_right"), 0.3f},
	});

	// Sadness — inner brow up, frown (corner depress), mouth down
	AddMapping(EEmotionType::Sadness, {
		{FName("head_lod0_mesh__brow_raiseIn_L"), 0.7f},
		{FName("head_lod0_mesh__brow_raiseIn_R"), 0.7f},
		{FName("head_lod0_mesh__brow_down_L"), 0.3f},
		{FName("head_lod0_mesh__brow_down_R"), 0.3f},
		{FName("head_lod0_mesh__mouth_cornerDepress_L"), 0.6f},
		{FName("head_lod0_mesh__mouth_cornerDepress_R"), 0.6f},
		{FName("head_lod0_mesh__mouth_stretch_left"), 0.2f},
		{FName("head_lod0_mesh__mouth_stretch_right"), 0.2f},
	});

	// Anger — brows down, jaw forward, nose wrinkle
	AddMapping(EEmotionType::Anger, {
		{FName("head_lod0_mesh__brow_down_L"), 0.8f},
		{FName("head_lod0_mesh__brow_down_R"), 0.8f},
		{FName("head_lod0_mesh__mouth_cornerDepress_L"), 0.4f},
		{FName("head_lod0_mesh__mouth_cornerDepress_R"), 0.4f},
		{FName("head_lod0_mesh__nose_wrinkle_left"), 0.5f},
		{FName("head_lod0_mesh__nose_wrinkle_right"), 0.5f},
		{FName("head_lod0_mesh__eye_squintInner_L"), 0.4f},
		{FName("head_lod0_mesh__eye_squintInner_R"), 0.4f},
		{FName("head_lod0_mesh__mouth_lipsTighten_UL"), 0.3f},
		{FName("head_lod0_mesh__mouth_lipsTighten_UR"), 0.3f},
	});

	// Fear — wide eyes, raised brows, open mouth
	AddMapping(EEmotionType::Fear, {
		{FName("head_lod0_mesh__brow_raiseIn_L"), 0.8f},
		{FName("head_lod0_mesh__brow_raiseIn_R"), 0.8f},
		{FName("head_lod0_mesh__brow_raiseOuter_left"), 0.6f},
		{FName("head_lod0_mesh__brow_raiseOuter_right"), 0.6f},
		{FName("head_lod0_mesh__eye_widen_L"), 0.7f},
		{FName("head_lod0_mesh__eye_widen_R"), 0.7f},
		{FName("head_lod0_mesh__mouth_stretch_left"), 0.4f},
		{FName("head_lod0_mesh__mouth_stretch_right"), 0.4f},
	});

	// Surprise — raised brows, wide eyes, open mouth
	AddMapping(EEmotionType::Surprise, {
		{FName("head_lod0_mesh__brow_raiseIn_L"), 0.9f},
		{FName("head_lod0_mesh__brow_raiseIn_R"), 0.9f},
		{FName("head_lod0_mesh__brow_raiseOuter_left"), 0.8f},
		{FName("head_lod0_mesh__brow_raiseOuter_right"), 0.8f},
		{FName("head_lod0_mesh__eye_widen_L"), 0.8f},
		{FName("head_lod0_mesh__eye_widen_R"), 0.8f},
		{FName("head_lod0_mesh__mouth_lowerLipDepress_left"), 0.5f},
		{FName("head_lod0_mesh__mouth_lowerLipDepress_right"), 0.5f},
	});

	// Disgust — nose wrinkle, upper lip raise
	AddMapping(EEmotionType::Disgust, {
		{FName("head_lod0_mesh__nose_wrinkle_left"), 0.8f},
		{FName("head_lod0_mesh__nose_wrinkle_right"), 0.8f},
		{FName("head_lod0_mesh__mouth_upperLipRaise_left"), 0.5f},
		{FName("head_lod0_mesh__mouth_upperLipRaise_right"), 0.5f},
		{FName("head_lod0_mesh__brow_down_L"), 0.4f},
		{FName("head_lod0_mesh__brow_down_R"), 0.4f},
	});

	// Trust — gentle smile, relaxed brows
	AddMapping(EEmotionType::Trust, {
		{FName("head_lod0_mesh__mouth_cornerPull_left"), 0.5f},
		{FName("head_lod0_mesh__mouth_cornerPull_right"), 0.5f},
		{FName("head_lod0_mesh__eye_cheekRaise_L"), 0.3f},
		{FName("head_lod0_mesh__eye_cheekRaise_R"), 0.3f},
		{FName("head_lod0_mesh__brow_raiseIn_L"), 0.2f},
		{FName("head_lod0_mesh__brow_raiseIn_R"), 0.2f},
	});

	// Anticipation — slight brow raise, focused eyes, slight smile
	AddMapping(EEmotionType::Anticipation, {
		{FName("head_lod0_mesh__brow_raiseIn_L"), 0.4f},
		{FName("head_lod0_mesh__brow_raiseIn_R"), 0.4f},
		{FName("head_lod0_mesh__brow_raiseOuter_left"), 0.3f},
		{FName("head_lod0_mesh__brow_raiseOuter_right"), 0.3f},
		{FName("head_lod0_mesh__eye_widen_L"), 0.2f},
		{FName("head_lod0_mesh__eye_widen_R"), 0.2f},
		{FName("head_lod0_mesh__mouth_cornerPull_left"), 0.2f},
		{FName("head_lod0_mesh__mouth_cornerPull_right"), 0.2f},
	});

	UE_LOG(LogTemp, Log, TEXT("BlendShapeMapping: Populated %d default Metahuman mappings"), Mappings.Num());
}
