#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "NPCDialogueHUD.generated.h"

class UDialogueComponent;
class UWhisperSTTComponent;
class ANPCCharacter;

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

	/** Rebind all delegates to a new focused NPC. Pass nullptr to enter null-focus state. */
	void SetFocusedNPC(ANPCCharacter* NPC);

	/** Called by NPCPlayerController on V press/release to drive the recording indicator. */
	void SetVoiceRecording(bool bRecording) { bIsVoiceRecording = bRecording; }

	/** Called by NPCPlayerController on left mouse click. Focuses input if click is inside the input box. */
	void HandleMouseClick(float MouseX, float MouseY);

	/** True only when the user has clicked the input box — keyboard capture is gated on this. */
	bool IsTextInputActive() const { return bTextInputActive; }

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

	/** Cached STT reference so we can RemoveDynamic on NPC switch. */
	UPROPERTY()
	TObjectPtr<UWhisperSTTComponent> BoundSTT;

	/** Cached focused NPC actor — used to detect no-op re-binds. */
	UPROPERTY()
	TObjectPtr<ANPCCharacter> FocusedNPCActor;

	/** Display name of the currently focused NPC. */
	FString FocusedNPCName;

	/** Callback when voice transcript arrives. */
	UFUNCTION()
	void OnVoiceTranscript(const FString& Transcript);

	bool bIsVoiceRecording = false;

	/** True when the user has clicked the input box. Cleared on click-outside, focus switch, or overlay hide. */
	bool bTextInputActive = false;

	/** Cached from the last DrawHUD call — used to compute input box bounds in HandleMouseClick. */
	float CachedScreenH = 0.0f;
};
