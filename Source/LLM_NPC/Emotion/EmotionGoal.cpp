#include "EmotionGoal.h"

UEmotionGoal::UEmotionGoal()
{
}

bool UEmotionGoal::IsSatisfied(const FEmotionState& CurrentState) const
{
	// Primary emotion must match
	if (CurrentState.PrimaryEmotion != GoalEmotion)
	{
		return false;
	}

	// Intensity must be within tolerance of the goal intensity
	return FMath::Abs(CurrentState.Intensity - GoalIntensity) <= IntensityTolerance;
}

float UEmotionGoal::GetCostToReach(const FEmotionState& FromState, const TMap<EEmotionType, float>& TransitionCosts) const
{
	// PAD distance component: Euclidean distance in PAD space
	const FPADVector GoalPAD = EmotionPADDefaults::GetCanonicalPAD(GoalEmotion);
	const float PADDistance = FromState.PAD.DistanceTo(GoalPAD);

	// Transition cost multiplier for the target emotion
	const float* CostMultiplierPtr = TransitionCosts.Find(GoalEmotion);
	const float CostMultiplier = CostMultiplierPtr ? *CostMultiplierPtr : 1.0f;

	// Intensity delta component
	const float IntensityDelta = FMath::Abs(FromState.Intensity - GoalIntensity);

	// Combined cost: PAD distance weighted by archetype-specific transition cost + intensity gap
	return (PADDistance * CostMultiplier) + IntensityDelta;
}
