#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "EmotionStateMachine.generated.h"

class UEmotionTransitionRule;

/** Delegate fired when the emotion state changes. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEmotionStateChanged, FEmotionState, OldState, FEmotionState, NewState);

/**
 * Graph-based emotion finite state machine.
 * Nodes = emotion states (Plutchik types), edges = transition rules with A*-weighted costs.
 *
 * Mirrors the F.E.A.R. GOAP architecture: a minimal node set with goal-driven transitions.
 * Instead of pre-authored animation trees, the planner searches for the lowest-cost
 * emotional transition given the NPC's archetype cost profile.
 *
 * Intensity decays toward 0 at a configurable rate. When intensity drops below
 * the neutral threshold (default 0.1), the machine transitions to Neutral.
 * The PAD vector interpolates smoothly; the discrete emotion label is updated
 * to the nearest canonical PAD point.
 */
UCLASS(BlueprintType)
class LLM_NPC_API UEmotionStateMachine : public UObject
{
	GENERATED_BODY()

public:
	UEmotionStateMachine();

	/**
	 * Process an incoming emotion signal.
	 * Evaluates all transition rules and fires the lowest-cost valid transition.
	 * @param Signal The emotion signal to process.
	 */
	UFUNCTION(BlueprintCallable, Category = "Emotion|StateMachine")
	void ProcessSignal(const FEmotionSignal& Signal);

	/**
	 * Tick the state machine: handles intensity decay and PAD interpolation.
	 * Called each frame by the owning EmotionComponent.
	 * @param DeltaTime Frame delta time in seconds.
	 */
	UFUNCTION(BlueprintCallable, Category = "Emotion|StateMachine")
	void Tick(float DeltaTime);

	/**
	 * Find the best transition target for a given signal using A*-like cost search.
	 * @param Signal The signal to evaluate.
	 * @return The best target emotion type, or current emotion if no valid transition found.
	 */
	UFUNCTION(BlueprintCallable, Category = "Emotion|StateMachine")
	EEmotionType FindBestTransition(const FEmotionSignal& Signal) const;

	/** Get the current emotional state. */
	UFUNCTION(BlueprintCallable, Category = "Emotion|StateMachine")
	FEmotionState GetCurrentState() const { return CurrentState; }

	/** Set the current state directly (used during initialization). */
	void SetCurrentState(const FEmotionState& NewState);

	/** Fired when the emotion state changes. */
	UPROPERTY(BlueprintAssignable, Category = "Emotion|StateMachine")
	FOnEmotionStateChanged OnEmotionStateChanged;

	// ---- Configuration ----

	/** All transition rules in this emotion graph. */
	UPROPERTY(BlueprintReadOnly, Category = "Emotion|StateMachine")
	TArray<TObjectPtr<UEmotionTransitionRule>> TransitionRules;

	/** Per-emotion transition cost multipliers (from NPC archetype). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion|StateMachine")
	TMap<EEmotionType, float> EmotionTransitionCosts;

	/** Rate at which intensity decays per second. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion|StateMachine", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float DecayRate = 0.05f;

	/** Intensity threshold below which the NPC transitions to Neutral. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion|StateMachine", meta = (ClampMin = "0.0", ClampMax = "0.5"))
	float NeutralThreshold = 0.1f;

	/** Speed of PAD vector interpolation (alpha per second). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion|StateMachine", meta = (ClampMin = "0.1", ClampMax = "10.0"))
	float PADInterpSpeed = 3.0f;

protected:
	/** The NPC's current emotional state. */
	UPROPERTY(BlueprintReadOnly, Category = "Emotion|StateMachine")
	FEmotionState CurrentState;

	/** World time of the last emotion transition (for cooldown tracking). */
	UPROPERTY()
	float LastTransitionTime = 0.0f;

	/** Target PAD vector we are interpolating toward. */
	UPROPERTY()
	FPADVector TargetPAD;

	/**
	 * Determine the nearest canonical emotion for a given PAD vector.
	 * @param PAD The PAD vector to classify.
	 * @return The nearest emotion type.
	 */
	EEmotionType ClassifyPAD(const FPADVector& PAD) const;

	/**
	 * Execute a state transition to the given emotion with the given intensity.
	 * @param NewEmotion The target emotion.
	 * @param NewIntensity The intensity of the new emotion.
	 */
	void TransitionTo(EEmotionType NewEmotion, float NewIntensity);

	/** Get the current world time. Falls back to FPlatformTime if no world context. */
	float GetCurrentTime() const;
};
