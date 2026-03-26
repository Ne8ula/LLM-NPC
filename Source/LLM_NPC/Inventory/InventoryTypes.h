#pragma once

#include "CoreMinimal.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "InventoryTypes.generated.h"

/**
 * Condition that must be met (emotion type + intensity + duration + optional keywords)
 * before an inventory item becomes unlocked.
 */
USTRUCT(BlueprintType)
struct FLLM_NPC_API FEmotionUnlockCondition
{
	GENERATED_BODY()

	/** The emotion the player must evoke in the NPC. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Unlock")
	EEmotionType RequiredEmotion = EEmotionType::Neutral;

	/** Minimum intensity the emotion must reach. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Unlock",
		meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float MinIntensity = 0.5f;

	/** How long (seconds) the emotion must be sustained at or above MinIntensity. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Unlock",
		meta = (ClampMin = "0.0"))
	float MinDurationSeconds = 3.0f;

	/** Optional keywords that must appear in recent dialogue to satisfy this condition. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Unlock")
	TArray<FString> OptionalKeywords;

	/** If true, ALL keywords must be present; otherwise ANY one suffices. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Unlock")
	bool bRequireAllKeywords = false;
};

/**
 * A single item an NPC can give to the player when unlock conditions are met.
 */
USTRUCT(BlueprintType)
struct FLLM_NPC_API FInventoryItem
{
	GENERATED_BODY()

	/** Unique identifier for this item. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Item")
	FName ItemID;

	/** Localised display name shown to the player. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Item")
	FText DisplayName;

	/** Localised description shown in the inspect panel. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Item")
	FText Description;

	/** Mesh displayed when the player inspects the item in 3D. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Item")
	TSoftObjectPtr<UStaticMesh> InspectMesh;

	/** 2D icon for UI display. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Item")
	TSoftObjectPtr<UTexture2D> Icon;

	/** All conditions that must be satisfied to unlock this item. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Item")
	TArray<FEmotionUnlockCondition> UnlockConditions;

	/** Whether the item has been unlocked (conditions met). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory|Item")
	bool bUnlocked = false;

	/** Whether the item has been handed to the player. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory|Item")
	bool bGivenToPlayer = false;
};
