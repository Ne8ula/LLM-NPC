#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "EmotionTransitionRule.generated.h"

/**
 * A single transition rule in the emotion graph.
 * Represents a directed edge from one emotion state to another,
 * with conditions that must be met for the transition to fire.
 *
 * Inspired by F.E.A.R.'s GOAP system: each transition has a cost,
 * enabling A*-like search through emotion space to find the
 * lowest-cost path to a goal emotion.
 */
UCLASS(BlueprintType, EditInlineNew, DefaultToInstanced)
class LLM_NPC_API UEmotionTransitionRule : public UObject
{
	GENERATED_BODY()

public:
	UEmotionTransitionRule();

	/** The emotion this rule transitions TO. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion|Transition")
	EEmotionType TargetEmotion = EEmotionType::Neutral;

	/** Minimum signal strength required for this rule to activate. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion|Transition", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float MinInputStrength = 0.1f;

	/**
	 * Keywords that must be present in the signal source for this rule to match.
	 * If empty, any source matches. If populated, at least one keyword must appear.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion|Transition")
	TArray<FString> RequiredKeywords;

	/** Minimum time (seconds) that must elapse since the last transition before this rule can fire again. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion|Transition", meta = (ClampMin = "0.0"))
	float CooldownTime = 0.5f;

	/** Weight/priority of this rule. Lower cost = preferred transition in A* search. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion|Transition", meta = (ClampMin = "0.0"))
	float TransitionCost = 1.0f;

	/**
	 * Evaluate whether this rule should fire given a signal and timing context.
	 * @param Signal The incoming emotion signal to evaluate against.
	 * @param TimeSinceLastTransition Seconds elapsed since the last emotion transition.
	 * @return True if all conditions are met and the rule should fire.
	 */
	UFUNCTION(BlueprintCallable, Category = "Emotion|Transition")
	bool EvaluateRule(const FEmotionSignal& Signal, float TimeSinceLastTransition) const;

	/**
	 * Get the cost of this transition for A*-like search.
	 * @return The transition cost value.
	 */
	UFUNCTION(BlueprintCallable, Category = "Emotion|Transition")
	float GetTransitionCost() const;
};
