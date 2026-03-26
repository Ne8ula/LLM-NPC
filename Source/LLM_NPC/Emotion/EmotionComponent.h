#pragma once

#include "CoreMinimal.h"
#include "LLM_NPC/Core/NPCSubsystemComponent.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "EmotionComponent.generated.h"

class UEmotionStateMachine;
class UEmotionGraphDataAsset;
class UNPCConfigDataAsset;

/** Delegate fired when the EmotionComponent detects a state change. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEmotionChanged, FEmotionState, OldState, FEmotionState, NewState);

/**
 * NPC subsystem component that owns and drives the Emotion Engine.
 *
 * Loads an EmotionGraphDataAsset from the NPC's config, instantiates the
 * EmotionStateMachine, and ticks it each frame for decay and PAD interpolation.
 * Other subsystems (Dialogue, Vision, Gesture) send FEmotionSignals via
 * ProcessSignal() to influence the NPC's emotional state.
 *
 * SubsystemName = "EmotionEngine"
 */
UCLASS(ClassGroup = (LLMNPC), meta = (BlueprintSpawnableComponent))
class LLM_NPC_API UEmotionComponent : public UNPCSubsystemComponent
{
	GENERATED_BODY()

public:
	UEmotionComponent();

	// ---- UNPCSubsystemComponent Interface ----
	virtual void InitializeSubsystem() override;
	virtual void ShutdownSubsystem() override;

	// ---- UActorComponent Interface ----
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * Process an incoming emotion signal by forwarding it to the state machine.
	 * @param Signal The emotion signal to process.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Emotion")
	void ProcessSignal(const FEmotionSignal& Signal);

	/**
	 * Get the NPC's current emotional state.
	 * @return The current FEmotionState.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Emotion")
	FEmotionState GetCurrentEmotionState() const;

	/** Delegate broadcast when the emotion state changes. */
	UPROPERTY(BlueprintAssignable, Category = "NPC|Emotion")
	FOnEmotionChanged OnEmotionChanged;

	/** The active state machine (created at initialization). */
	UPROPERTY(BlueprintReadOnly, Category = "NPC|Emotion")
	TObjectPtr<UEmotionStateMachine> StateMachine;

protected:
	/**
	 * Load the EmotionGraphDataAsset from the NPC's config and instantiate the state machine.
	 * @param Config The NPC config data asset to read from.
	 */
	void LoadFromConfig(const UNPCConfigDataAsset* Config);

	/** Callback bound to the state machine's OnEmotionStateChanged delegate. */
	UFUNCTION()
	void HandleEmotionStateChanged(FEmotionState OldState, FEmotionState NewState);
};
