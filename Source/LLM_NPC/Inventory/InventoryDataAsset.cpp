#include "InventoryDataAsset.h"

FInventoryItem* UInventoryDataAsset::FindItem(FName ItemID)
{
	for (FInventoryItem& Item : Items)
	{
		if (Item.ItemID == ItemID)
		{
			return &Item;
		}
	}
	return nullptr;
}
