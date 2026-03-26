#pragma once

#include "CoreMinimal.h"
#include "LLM_NPC/Core/NPCSubsystemComponent.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "InventoryTypes.h"
#include "NPCInventoryComponent.generated.h"

class UInventoryDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemUnlocked, FName, ItemID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemGiven, FName, ItemID);

/**
 * Manages the NPC's item inventory and emotion-driven unlock system.
 *
 * Listens to the Emotion subsystem's OnEmotionStateChanged delegate and tracks
 * how long each unlock condition has been continuously satisfied.  When all
 * conditions for an item are met the item is unlocked and the NPC can give it
 * to the player.
 */
UCLASS(ClassGroup = (LLMNPC), meta = (BlueprintSpawnableComponent))
class FLLM_NPC_API UNPCInventoryComponent : public UNPCSubsystemComponent
{
	GENERATED_BODY()

public:
	UNPCInventoryComponent();

	// --- Lifecycle ---
	virtual void InitializeSubsystem() override;
	virtual void ShutdownSubsystem() override;

	// --- Public API ---

	/**
	 * Evaluate unlock conditions for every item against the current emotion state.
	 * Called automatically when the emotion state changes.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Inventory")
	void CheckUnlockConditions(const FEmotionState& CurrentState);

	/**
	 * Mark an item as given to the player and broadcast OnItemGiven.
	 * Only succeeds if the item is unlocked and has not already been given.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Inventory")
	void TryGiveItem(FName ItemID);

	/** Return all items that have been unlocked (regardless of whether they have been given). */
	UFUNCTION(BlueprintCallable, Category = "NPC|Inventory")
	TArray<FInventoryItem> GetUnlockedItems() const;

	/**
	 * Feed dialogue text so that keyword-based unlock conditions can be checked.
	 * Typically called by the Dialogue subsystem whenever a new message is received.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Inventory")
	void UpdateKeywords(const FString& DialogueText);

	// --- Delegates ---

	/** Broadcast when an item transitions from locked to unlocked. */
	UPROPERTY(BlueprintAssignable, Category = "NPC|Inventory")
	FOnItemUnlocked OnItemUnlocked;

	/** Broadcast when an unlocked item is given to the player. */
	UPROPERTY(BlueprintAssignable, Category = "NPC|Inventory")
	FOnItemGiven OnItemGiven;

	// --- Configuration ---

	/** Data asset defining the item catalogue for this NPC. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Inventory")
	TSoftObjectPtr<UInventoryDataAsset> InventoryDataAssetRef;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	/** Callback bound to the Emotion subsystem's OnEmotionStateChanged delegate. */
	UFUNCTION()
	void HandleEmotionStateChanged(const FEmotionState& NewState);

	/** Check whether a single unlock condition is satisfied. */
	bool IsConditionMet(const FEmotionUnlockCondition& Condition, const FEmotionState& CurrentState) const;

	/** Check whether dialogue keywords satisfy a condition. */
	bool AreKeywordsMet(const FEmotionUnlockCondition& Condition) const;

	/** Start or reset the duration tracker timer for a specific item. */
	void StartDurationTracker(FName ItemID);

	/** Stop the duration tracker timer for a specific item. */
	void StopDurationTracker(FName ItemID);

	/** Loaded inventory data asset (runtime). */
	UPROPERTY()
	TObjectPtr<UInventoryDataAsset> LoadedInventoryData;

	/** Runtime copy of items so we can mutate unlock/given state. */
	UPROPERTY()
	TArray<FInventoryItem> RuntimeItems;

	/** Per-item timer handles for tracking continuous emotion duration. */
	TMap<FName, FTimerHandle> DurationTimerHandles;

	/** Per-item accumulated duration (seconds) the emotion condition has been continuously met. */
	TMap<FName, float> AccumulatedDurations;

	/** Set of keywords observed in recent dialogue. */
	TSet<FString> MatchedKeywords;

	/** The most recently observed emotion state, cached for timer callbacks. */
	FEmotionState CachedEmotionState;
};
