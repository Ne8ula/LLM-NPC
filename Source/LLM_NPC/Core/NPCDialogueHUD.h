#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "NPCDialogueHUD.generated.h"

class UNPCDialogueOverlay;

/**
 * HUD class that creates and manages the NPC dialogue overlay widget.
 * Automatically creates the text input UI when the game starts.
 */
UCLASS()
class LLM_NPC_API ANPCDialogueHUD : public AHUD
{
	GENERATED_BODY()

public:
	/** Toggle the dialogue input box visibility. */
	UFUNCTION(BlueprintCallable, Category = "NPC|UI")
	void ToggleDialogueInput();

	/** Get the dialogue overlay widget. */
	UNPCDialogueOverlay* GetDialogueOverlay() const { return DialogueOverlay; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UNPCDialogueOverlay> DialogueOverlay;
};
