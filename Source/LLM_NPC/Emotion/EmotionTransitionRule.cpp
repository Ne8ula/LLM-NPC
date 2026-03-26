#include "EmotionTransitionRule.h"

UEmotionTransitionRule::UEmotionTransitionRule()
{
}

bool UEmotionTransitionRule::EvaluateRule(const FEmotionSignal& Signal, float TimeSinceLastTransition) const
{
	// Check that the signal targets the same emotion as this rule
	if (Signal.TargetEmotion != TargetEmotion)
	{
		return false;
	}

	// Check minimum strength threshold
	if (Signal.Strength < MinInputStrength)
	{
		return false;
	}

	// Check cooldown
	if (TimeSinceLastTransition < CooldownTime)
	{
		return false;
	}

	// Check required keywords (if any are specified, at least one must match)
	if (RequiredKeywords.Num() > 0)
	{
		bool bKeywordFound = false;
		for (const FString& Keyword : RequiredKeywords)
		{
			if (Signal.Source.Contains(Keyword, ESearchCase::IgnoreCase))
			{
				bKeywordFound = true;
				break;
			}
		}

		if (!bKeywordFound)
		{
			return false;
		}
	}

	return true;
}

float UEmotionTransitionRule::GetTransitionCost() const
{
	return TransitionCost;
}
