#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InventoryTypes.h"
#include "InventoryDataAsset.generated.h"

/**
 * Data asset that defines the inventory catalogue for a single NPC archetype.
 * Designers author one of these per NPC to configure which items can be unlocked.
 */
UCLASS(BlueprintType)
class LLM_NPC_API UInventoryDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	/** All items this NPC can potentially give to the player. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<FInventoryItem> Items;

	/**
	 * Find an item by its unique ID.
	 * @return Pointer to the item, or nullptr if not found.
	 */
	FInventoryItem* FindItem(FName ItemID);
};
