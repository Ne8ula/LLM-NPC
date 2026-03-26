#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueFallbackWidget.generated.h"

class UEditableTextBox;
class UButton;
class UTextBlock;
class UVerticalBox;

/** Delegate fired when the user submits text through the fallback widget. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTextSubmitted, const FString&, SubmittedText);

/**
 * Simple text-input fallback widget for dialogue when voice input is unavailable.
 *
 * Contains an editable text box and a send button. Automatically shows/hides
 * based on whether voice input (WhisperSTTComponent) is available on the
 * interacting NPC.
 */
UCLASS()
class LLM_NPC_API UDialogueFallbackWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Fired when the user submits text input. */
	UPROPERTY(BlueprintAssignable, Category = "NPC|Dialogue|Fallback")
	FOnTextSubmitted OnTextSubmitted;

	/** Show the widget with optional animation. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Dialogue|Fallback")
	void ShowWidget();

	/** Hide the widget with optional animation. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Dialogue|Fallback")
	void HideWidget();

	/** Set whether the widget should be visible based on voice availability. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Dialogue|Fallback")
	void SetVisibleBasedOnVoiceAvailability(bool bVoiceAvailable);

	/** Clear the text input field. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Dialogue|Fallback")
	void ClearInput();

	/** Set focus to the text input field. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Dialogue|Fallback")
	void FocusInput();

	/** Show a status message (e.g., "Waiting for response..."). */
	UFUNCTION(BlueprintCallable, Category = "NPC|Dialogue|Fallback")
	void SetStatusText(const FString& StatusText);

	/** Enable or disable the input controls. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Dialogue|Fallback")
	void SetInputEnabled(bool bEnabled);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	/** The text input box. Bind in Blueprint or set via BindWidget. */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UEditableTextBox> TextInputBox;

	/** The send button. Bind in Blueprint or set via BindWidget. */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> SendButton;

	/** Optional status text display. */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> StatusTextBlock;

private:
	/** Called when the send button is clicked. */
	UFUNCTION()
	void OnSendButtonClicked();

	/** Called when the user presses Enter in the text box. */
	UFUNCTION()
	void OnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	/** Submit the current text. */
	void SubmitCurrentText();
};
