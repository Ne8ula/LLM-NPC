#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "NPCPlayerController.generated.h"

class ANPCCharacter;

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

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;

private:
	void ToggleDialogueInput();

	/** Update FocusedNPC based on proximity + facing. Notifies HUD on change. */
	void UpdateNPCFocus();

	/** Returns the nearest NPC within InteractionRadius that the player is facing, or nullptr. */
	ANPCCharacter* FindNearestNPCInRange() const;

	/** Maps EGestureType to EGestureIntent and caches in PendingGestureIntent. */
	UFUNCTION()
	void OnGestureDetected(FGestureInput DetectedGesture);

	bool bTKeyWasDown = false;
	bool bDialogueVisible = false;
	bool bVKeyWasDown = false;
};
