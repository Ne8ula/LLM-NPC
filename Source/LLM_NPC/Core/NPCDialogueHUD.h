#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "NPCDialogueHUD.generated.h"

class UDialogueComponent;
class SEditableTextBox;
class SScrollBox;
class STextBlock;
class SVerticalBox;

/**
 * HUD that manages the NPC dialogue chat overlay.
 * Adds Slate widgets directly to the game viewport (no UUserWidget needed).
 */
UCLASS()
class LLM_NPC_API ANPCDialogueHUD : public AHUD
{
	GENERATED_BODY()

public:
	void ToggleDialogueInput();
	bool IsDialogueVisible() const { return bDialogueVisible; }

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void BuildChatUI();
	void SubmitText();
	void AddChatMessage(const FString& Sender, const FString& Message, FLinearColor Color);

	UFUNCTION()
	void OnNPCResponse(const FString& ResponseText, EEmotionType NPCEmotionHint, bool bShouldGiveItem, FName ItemID);

	TSharedPtr<SVerticalBox> ChatPanel;
	TSharedPtr<SScrollBox> ChatLog;
	TSharedPtr<SEditableTextBox> InputBox;
	TSharedPtr<STextBlock> StatusText;
	TSharedPtr<SWidget> RootWidget;

	bool bDialogueVisible = true;
	bool bUIBuilt = false;

	UPROPERTY()
	TObjectPtr<UDialogueComponent> BoundDialogue;
};
