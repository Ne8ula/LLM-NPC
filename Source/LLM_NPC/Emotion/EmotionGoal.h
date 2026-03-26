#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "EmotionGoal.generated.h"

/**
 * GOAP-style goal defining WHAT emotional state the NPC should reach.
 *
 * Goals are archetype-agnostic: different NPC archetypes share the same goals
 * but have different transition costs, so a "stoic warrior" and a "nervous merchant"
 * reach the same goal emotion via different paths through PAD space.
 *
 * Cost calculation uses PAD distance + weighted transition cost map,
 * enabling A*-like planning through the emotion graph.
 */
UCLASS(BlueprintType, EditInlineNew, DefaultToInstanced)
class LLM_NPC_API UEmotionGoal : public UObject
{
	GENERATED_BODY()

public:
	UEmotionGoal();

	/** The target emotion this goal wants to reach. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion|Goal")
	EEmotionType GoalEmotion = EEmotionType::Neutral;

	/** Desired intensity at the goal emotion. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion|Goal", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float GoalIntensity = 0.5f;

	/** Priority of this goal. Higher priority goals are preferred when multiple goals compete. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion|Goal", meta = (ClampMin = "0.0"))
	float Priority = 1.0f;

	/**
	 * Check if the current emotional state satisfies this goal.
	 * Satisfied when the primary emotion matches and intensity is within tolerance.
	 * @param CurrentState The NPC's current emotional state.
	 * @return True if the goal is considered satisfied.
	 */
	UFUNCTION(BlueprintCallable, Category = "Emotion|Goal")
	bool IsSatisfied(const FEmotionState& CurrentState) const;

	/**
	 * Estimate cost to reach this goal from a given state using A*-like heuristic.
	 * Combines PAD Euclidean distance with per-emotion transition cost multipliers.
	 * @param FromState The starting emotional state.
	 * @param TransitionCosts Per-emotion cost multipliers from the NPC archetype config.
	 * @return Estimated cost (lower = easier to reach).
	 */
	UFUNCTION(BlueprintCallable, Category = "Emotion|Goal")
	float GetCostToReach(const FEmotionState& FromState, const TMap<EEmotionType, float>& TransitionCosts) const;

protected:
	/** Intensity tolerance for goal satisfaction. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion|Goal", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float IntensityTolerance = 0.15f;
};
