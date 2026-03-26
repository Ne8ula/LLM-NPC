#include "NPCInventoryComponent.h"
#include "InventoryDataAsset.h"
#include "Engine/StreamableManager.h"
#include "TimerManager.h"

UNPCInventoryComponent::UNPCInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SubsystemName = TEXT("Inventory");
}

void UNPCInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UNPCInventoryComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// Clear all duration timers
	if (GetWorld())
	{
		for (auto& Pair : DurationTimerHandles)
		{
			GetWorld()->GetTimerManager().ClearTimer(Pair.Value);
		}
	}
	DurationTimerHandles.Empty();

	Super::EndPlay(EndPlayReason);
}

void UNPCInventoryComponent::InitializeSubsystem()
{
	Super::InitializeSubsystem();

	// Load the inventory data asset
	if (!InventoryDataAssetRef.IsNull())
	{
		LoadedInventoryData = InventoryDataAssetRef.LoadSynchronous();
		if (LoadedInventoryData)
		{
			// Create a runtime copy so we can mutate bUnlocked / bGivenToPlayer
			RuntimeItems = LoadedInventoryData->Items;
			UE_LOG(LogTemp, Log, TEXT("NPC Inventory: Loaded %d items from data asset"), RuntimeItems.Num());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("NPC Inventory: Failed to load InventoryDataAsset"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NPC Inventory: No InventoryDataAsset assigned"));
	}

	// Bind to emotion subsystem's delegate if available
	if (AActor* Owner = GetOwner())
	{
		TArray<UActorComponent*> Components;
		Owner->GetComponents(UNPCSubsystemComponent::StaticClass(), Components);
		for (UActorComponent* Comp : Components)
		{
			if (Comp && Comp->GetClass()->GetName().Contains(TEXT("Emotion")))
			{
				// Bind via dynamic delegate lookup – the Emotion component is expected
				// to have an OnEmotionStateChanged delegate. We bind at runtime.
				FScriptDelegate Delegate;
				Delegate.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(UNPCInventoryComponent, HandleEmotionStateChanged));

				FMulticastScriptDelegate* EmotionDelegate = Comp->GetClass()->FindPropertyByName(TEXT("OnEmotionStateChanged"))
					? nullptr : nullptr;

				// Fallback: attempt to find and bind via reflection
				if (FMulticastDelegateProperty* DelegateProp = CastField<FMulticastDelegateProperty>(
					Comp->GetClass()->FindPropertyByName(TEXT("OnEmotionStateChanged"))))
				{
					DelegateProp->GetMulticastDelegate(Comp)->AddDelegate(Delegate);
					UE_LOG(LogTemp, Log, TEXT("NPC Inventory: Bound to EmotionComponent's OnEmotionStateChanged"));
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("NPC Inventory: Could not find OnEmotionStateChanged delegate on Emotion component"));
				}
				break;
			}
		}
	}
}

void UNPCInventoryComponent::ShutdownSubsystem()
{
	// Clear timers
	if (GetWorld())
	{
		for (auto& Pair : DurationTimerHandles)
		{
			GetWorld()->GetTimerManager().ClearTimer(Pair.Value);
		}
	}
	DurationTimerHandles.Empty();
	AccumulatedDurations.Empty();
	MatchedKeywords.Empty();

	Super::ShutdownSubsystem();
}

void UNPCInventoryComponent::HandleEmotionStateChanged(const FEmotionState& NewState)
{
	CachedEmotionState = NewState;
	CheckUnlockConditions(NewState);
}

void UNPCInventoryComponent::CheckUnlockConditions(const FEmotionState& CurrentState)
{
	for (FInventoryItem& Item : RuntimeItems)
	{
		if (Item.bUnlocked)
		{
			continue;
		}

		bool bAllConditionsMet = true;
		for (const FEmotionUnlockCondition& Condition : Item.UnlockConditions)
		{
			if (!IsConditionMet(Condition, CurrentState))
			{
				bAllConditionsMet = false;
				StopDurationTracker(Item.ItemID);
				break;
			}
		}

		if (bAllConditionsMet && Item.UnlockConditions.Num() > 0)
		{
			// Check if duration requirement is already met via accumulated time
			float RequiredDuration = 0.0f;
			for (const FEmotionUnlockCondition& Condition : Item.UnlockConditions)
			{
				RequiredDuration = FMath::Max(RequiredDuration, Condition.MinDurationSeconds);
			}

			float* Accumulated = AccumulatedDurations.Find(Item.ItemID);
			if (Accumulated && *Accumulated >= RequiredDuration)
			{
				// Unlock the item
				Item.bUnlocked = true;
				StopDurationTracker(Item.ItemID);
				OnItemUnlocked.Broadcast(Item.ItemID);
				UE_LOG(LogTemp, Log, TEXT("NPC Inventory: Item '%s' unlocked!"), *Item.ItemID.ToString());
			}
			else
			{
				// Start or continue tracking duration
				StartDurationTracker(Item.ItemID);
			}
		}
	}
}

bool UNPCInventoryComponent::IsConditionMet(const FEmotionUnlockCondition& Condition, const FEmotionState& CurrentState) const
{
	// Check emotion type
	if (CurrentState.PrimaryEmotion != Condition.RequiredEmotion)
	{
		return false;
	}

	// Check minimum intensity
	if (CurrentState.Intensity < Condition.MinIntensity)
	{
		return false;
	}

	// Check keywords if any are specified
	if (Condition.OptionalKeywords.Num() > 0 && !AreKeywordsMet(Condition))
	{
		return false;
	}

	return true;
}

bool UNPCInventoryComponent::AreKeywordsMet(const FEmotionUnlockCondition& Condition) const
{
	if (Condition.OptionalKeywords.Num() == 0)
	{
		return true;
	}

	if (Condition.bRequireAllKeywords)
	{
		for (const FString& Keyword : Condition.OptionalKeywords)
		{
			if (!MatchedKeywords.Contains(Keyword.ToLower()))
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		for (const FString& Keyword : Condition.OptionalKeywords)
		{
			if (MatchedKeywords.Contains(Keyword.ToLower()))
			{
				return true;
			}
		}
		return false;
	}
}

void UNPCInventoryComponent::StartDurationTracker(FName ItemID)
{
	if (DurationTimerHandles.Contains(ItemID))
	{
		// Timer already running, accumulate
		return;
	}

	// Initialize accumulated duration if not present
	if (!AccumulatedDurations.Contains(ItemID))
	{
		AccumulatedDurations.Add(ItemID, 0.0f);
	}

	// Set up a repeating timer that increments the accumulated duration
	FTimerHandle& Handle = DurationTimerHandles.FindOrAdd(ItemID);
	const float TickInterval = 0.25f;

	GetWorld()->GetTimerManager().SetTimer(
		Handle,
		[this, ItemID, TickInterval]()
		{
			if (float* Accumulated = AccumulatedDurations.Find(ItemID))
			{
				*Accumulated += TickInterval;
			}
			// Re-check unlock conditions with cached state
			CheckUnlockConditions(CachedEmotionState);
		},
		TickInterval,
		true // Looping
	);
}

void UNPCInventoryComponent::StopDurationTracker(FName ItemID)
{
	if (FTimerHandle* Handle = DurationTimerHandles.Find(ItemID))
	{
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().ClearTimer(*Handle);
		}
		DurationTimerHandles.Remove(ItemID);
	}

	// Reset accumulated duration when condition is no longer met
	AccumulatedDurations.Remove(ItemID);
}

void UNPCInventoryComponent::TryGiveItem(FName ItemID)
{
	for (FInventoryItem& Item : RuntimeItems)
	{
		if (Item.ItemID == ItemID)
		{
			if (!Item.bUnlocked)
			{
				UE_LOG(LogTemp, Warning, TEXT("NPC Inventory: Cannot give item '%s' - not unlocked"), *ItemID.ToString());
				return;
			}
			if (Item.bGivenToPlayer)
			{
				UE_LOG(LogTemp, Warning, TEXT("NPC Inventory: Item '%s' already given to player"), *ItemID.ToString());
				return;
			}

			Item.bGivenToPlayer = true;
			OnItemGiven.Broadcast(ItemID);
			UE_LOG(LogTemp, Log, TEXT("NPC Inventory: Item '%s' given to player"), *ItemID.ToString());
			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("NPC Inventory: Item '%s' not found"), *ItemID.ToString());
}

TArray<FInventoryItem> UNPCInventoryComponent::GetUnlockedItems() const
{
	TArray<FInventoryItem> Result;
	for (const FInventoryItem& Item : RuntimeItems)
	{
		if (Item.bUnlocked)
		{
			Result.Add(Item);
		}
	}
	return Result;
}

void UNPCInventoryComponent::UpdateKeywords(const FString& DialogueText)
{
	// Tokenize the dialogue text and store lowercase keywords
	TArray<FString> Words;
	DialogueText.ParseIntoArray(Words, TEXT(" "), true);

	for (const FString& Word : Words)
	{
		// Strip basic punctuation and store lowercase
		FString CleanWord = Word.ToLower();
		CleanWord.RemoveFromEnd(TEXT("."));
		CleanWord.RemoveFromEnd(TEXT(","));
		CleanWord.RemoveFromEnd(TEXT("!"));
		CleanWord.RemoveFromEnd(TEXT("?"));
		CleanWord.RemoveFromEnd(TEXT(";"));

		if (!CleanWord.IsEmpty())
		{
			MatchedKeywords.Add(CleanWord);
		}
	}

	// Re-check unlock conditions after keyword update
	CheckUnlockConditions(CachedEmotionState);
}
