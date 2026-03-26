#include "BlendShapeMappingDataAsset.h"

TArray<FEmotionBlendShapeTarget> UBlendShapeMappingDataAsset::GetTargetsForState(const FEmotionState& State) const
{
	for (const FEmotionBlendShapeMapping& Mapping : Mappings)
	{
		if (Mapping.EmotionType == State.PrimaryEmotion &&
			State.Intensity >= Mapping.MinIntensity &&
			State.Intensity <= Mapping.MaxIntensity)
		{
			return Mapping.BlendShapeTargets;
		}
	}

	return TArray<FEmotionBlendShapeTarget>();
}
