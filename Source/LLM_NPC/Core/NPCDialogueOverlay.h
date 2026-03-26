#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NPCDialogueOverlay.generated.h"

class UEditableTextBox;
class UButton;
class UTextBlock;
class UScrollBox;
class UVerticalBox;
class UDialogueComponent;

/**
 * Pure C++ dialogue overlay widget — no Blueprint required.
 * Shows a chat log + text input at the bottom of the screen.
 * Builds all UI elements programmatically in NativeConstruct.
 */
UCLASS()
class LLM_NPC_API UNPCDialogueOverlay : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Toggle visibility of the input area. */
	void ToggleInput();

	/** Add a message to the chat log. */
	void AddChatMessage(const FString& Sender, const FString& Message, FLinearColor Color);

	/** Set status text (e.g., "Waiting for response..."). */
	void SetStatus(const FString& StatusText);

	/** Bind to an NPC's DialogueComponent for sending/receiving messages. */
	void BindToNPC(UDialogueComponent* InDialogueComp);

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void NativeConstruct() override;

private:
	/** Called when user presses Enter or clicks Send. */
	void SubmitText();

	/** Callback from DialogueComponent when Claude responds. */
	UFUNCTION()
	void OnNPCResponse(const FString& ResponseText, EEmotionType NPCEmotionHint,
		bool bShouldGiveItem, FName ItemID);

	// Slate widgets (built programmatically)
	TSharedPtr<SVerticalBox> RootBox;
	TSharedPtr<SScrollBox> ChatScrollBox;
	TSharedPtr<SEditableTextBox> InputTextBox;
	TSharedPtr<STextBlock> StatusText;

	bool bInputVisible = false;

	UPROPERTY()
	TObjectPtr<UDialogueComponent> BoundDialogueComp;
};
