#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "NPCPlayerController.generated.h"

class ANPCCharacter;
class AInspectableItem;
class UInputMappingContext;

UCLASS()
class LLM_NPC_API ANPCPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ANPCPlayerController();

	/** Currently focused NPC (nearest within InteractionRadius + facing). */
	UPROPERTY(BlueprintReadOnly, Category = "NPC|Focus")
	TObjectPtr<ANPCCharacter> FocusedNPC;

	/** Radius (cm) within which an NPC can be focused. */
	UPROPERTY(EditAnywhere, Category = "NPC|Focus")
	float InteractionRadius = 300.0f;

	/** Cached gesture intent — set by OnGestureDetected, consumed per-message submit. */
	EGestureIntent PendingGestureIntent = EGestureIntent::None;

	// ---------------------------------------------------------------------------
	// Memory Archive — Tier 2 speaker identification
	// ---------------------------------------------------------------------------

	/**
	 * Tag of the speaker most recently identified (acoustically or via 1/2
	 * override). Consumed once when a user message is dispatched to Claude
	 * and threaded through DialogueComponent::BuildAnnotatedContent as the
	 * `[Speaker_X is speaking]` prefix. Cleared on focus loss so a stale tag
	 * doesn't leak into a different conversation.
	 */
	FName PendingSpeakerTag = NAME_None;

	/** Sticky last-identified speaker — the HUD chip reads this so the
	 *  display persists between dispatches (PendingSpeakerTag is cleared
	 *  on each submit, this one isn't). */
	FName LastSpeakerTag = NAME_None;

	/** Confidence (cosine similarity, [0,1]) for LastSpeakerTag. HUD chip. */
	float LastSpeakerConfidence = 0.0f;

	UFUNCTION()
	void HandleSpeakerIdentified(FName Tag, float Confidence);

	// ---------------------------------------------------------------------------
	// Memory Archive — Tier 1 inspect / present / drop
	// ---------------------------------------------------------------------------

	/** Maximum reach of the E-key pickup line trace, in cm. */
	UPROPERTY(EditAnywhere, Category = "NPC|Inspect")
	float MaxInteractionDistance = 300.0f;

	/**
	 * Offset (in camera-local axes: forward/right/up, cm) where a held item is positioned
	 * relative to the camera each tick. Tweak in the editor for hand-mesh alignment.
	 */
	UPROPERTY(EditAnywhere, Category = "NPC|Inspect")
	FVector HoldOffset = FVector(70.0f, 15.0f, -15.0f);

	/** Multiplier on raw mouse delta when right-mouse drag is rotating a held item. */
	UPROPERTY(EditAnywhere, Category = "NPC|Inspect")
	float MouseRotationSensitivity = 1.5f;

	/** Uniform-scale step applied to the held item per scroll-wheel tick. */
	UPROPERTY(EditAnywhere, Category = "NPC|Inspect", meta = (ClampMin = "0.0"))
	float ScrollScaleStep = 0.1f;

	/** Returns true while the player is holding an inspectable item. */
	UFUNCTION(BlueprintPure, Category = "NPC|Inspect")
	bool IsHoldingItem() const { return HeldItem.IsValid(); }

	/** Returns the held item (or nullptr). Used by HUD to attach "currently holding" context. */
	AInspectableItem* GetHeldItem() const { return HeldItem.Get(); }

	// ---------------------------------------------------------------------------
	// Enhanced Input — IMC registration (UE 5.4+ FP template style)
	// ---------------------------------------------------------------------------

	/**
	 * Mapping contexts to register with the local player on possession.
	 * Pre-populated in the constructor with the FP feature pack's IMC_Default and
	 * IMC_MouseLook (paths /Game/Input/IMC_Default and /Game/Input/IMC_MouseLook).
	 * Override on a Blueprint subclass if your project uses different IMCs.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TArray<TObjectPtr<UInputMappingContext>> DefaultMappingContexts;

	/** Priority passed to AddMappingContext for every entry above. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (ClampMin = "0"))
	int32 DefaultMappingContextPriority = 0;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	void ToggleDialogueInput();

	/** Update FocusedNPC based on proximity + facing. Notifies HUD on change. */
	void UpdateNPCFocus();

	/** Returns the nearest NPC within InteractionRadius that the player is facing, or nullptr. */
	ANPCCharacter* FindNearestNPCInRange() const;

	/** Maps EGestureType to EGestureIntent and caches in PendingGestureIntent. */
	UFUNCTION()
	void OnGestureDetected(FGestureInput DetectedGesture);

	// --- Tier 1 inspect / present / drop helpers ---

	/** 300cm camera-forward line trace on ECC_Visibility; returns the hit AInspectableItem or nullptr. */
	AInspectableItem* TraceForInspectable() const;

	/** E-key handler. Drops the held item if holding, otherwise traces and picks up. */
	void HandleEPressed();

	/** F-key handler. Routes the held item to the focused NPC's DialogueComponent::SendObjectPresentMessage. */
	void HandleFPressed();

	/** Q-key handler. Drops the held item if holding. No-op otherwise. */
	void HandleQPressed();

	/** Attaches conceptual ownership of the item, walk-locks, records inspection, caches reset state. */
	void PickupItem(AInspectableItem* Item);

	/** Releases the held item: ResetTransform, restore world location, re-enable walking. */
	void DropHeldItem();

	/** Each tick while holding: sync item to camera + offset, apply mouse-drag rotation, scroll scale. */
	void TickHeldItem(float DeltaTime);

	/** FPS-style: cursor hidden, mouse captured continuously. Used outside the chat overlay. */
	void SetGameOnlyInputMode();

	/** Cursor visible, click-through Slate UI works. Used while the chat overlay is open. */
	void SetGameAndUIInputMode();

	/** Tracks chat overlay state from previous tick so we only switch modes on transition. */
	bool bChatOverlayWasOpen = false;

	/** Held item, weak so destroy/GC during play does not dangle. */
	TWeakObjectPtr<AInspectableItem> HeldItem;

	/** World location of the item at pickup time, restored on drop. */
	FVector HeldItemOriginalLocation = FVector::ZeroVector;

	bool bTKeyWasDown = false;
	bool bDialogueVisible = false;
	bool bEKeyWasDown = false;
	bool bFKeyWasDown = false;
	bool bQKeyWasDown = false;
	bool bLCtrlKeyWasDown = false;
	bool bWasIgnoringLook = false;
	bool b1KeyWasDown = false;
	bool b2KeyWasDown = false;
};
