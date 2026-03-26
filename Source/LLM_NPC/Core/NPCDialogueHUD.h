#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "NPCDialogueHUD.generated.h"

class UDialogueComponent;

/**
 * HUD that draws NPC dialogue chat using canvas DrawText.
 * This approach uses AHUD::DrawHUD which is guaranteed visible.
 */
UCLASS()
class LLM_NPC_API ANPCDialogueHUD : public AHUD
{
	GENERATED_BODY()

public:
	void ToggleDialogueInput();
	bool IsDialogueVisible() const { return bDialogueVisible; }

	/** Called from player controller when user submits text. */
	void SubmitChatMessage(const FString& Message);
	void SetStatus(const FString& Status) { StatusMessage = Status; }

	/** Get the current input text buffer. */
	FString GetInputBuffer() const { return InputBuffer; }
	void SetInputBuffer(const FString& Text) { InputBuffer = Text; }
	void AppendToInput(const FString& Char);
	void BackspaceInput();

protected:
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;

private:
	UFUNCTION()
	void OnNPCResponse(const FString& ResponseText, EEmotionType NPCEmotionHint, bool bShouldGiveItem, FName ItemID);

	struct FChatLine
	{
		FString Text;
		FLinearColor Color;
	};

	TArray<FChatLine> ChatLines;
	FString InputBuffer;
	FString StatusMessage = TEXT("Type a message and press Enter.");
	bool bDialogueVisible = true;

	UPROPERTY()
	TObjectPtr<UDialogueComponent> BoundDialogue;

	/** Callback when voice transcript arrives. */
	UFUNCTION()
	void OnVoiceTranscript(const FString& Transcript);

	bool bIsVoiceRecording = false;
};
