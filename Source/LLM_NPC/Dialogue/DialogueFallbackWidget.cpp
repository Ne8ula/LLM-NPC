#include "DialogueFallbackWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UDialogueFallbackWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Bind button click
	if (SendButton)
	{
		SendButton->OnClicked.AddDynamic(this, &UDialogueFallbackWidget::OnSendButtonClicked);
	}

	// Bind text commit (Enter key)
	if (TextInputBox)
	{
		TextInputBox->OnTextCommitted.AddDynamic(this, &UDialogueFallbackWidget::OnTextCommitted);
	}

	// Clear status text
	if (StatusTextBlock)
	{
		StatusTextBlock->SetText(FText::GetEmpty());
	}
}

void UDialogueFallbackWidget::NativeDestruct()
{
	if (SendButton)
	{
		SendButton->OnClicked.RemoveDynamic(this, &UDialogueFallbackWidget::OnSendButtonClicked);
	}

	if (TextInputBox)
	{
		TextInputBox->OnTextCommitted.RemoveDynamic(this, &UDialogueFallbackWidget::OnTextCommitted);
	}

	Super::NativeDestruct();
}

void UDialogueFallbackWidget::ShowWidget()
{
	SetVisibility(ESlateVisibility::Visible);
	FocusInput();
}

void UDialogueFallbackWidget::HideWidget()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UDialogueFallbackWidget::SetVisibleBasedOnVoiceAvailability(bool bVoiceAvailable)
{
	if (bVoiceAvailable)
	{
		HideWidget();
	}
	else
	{
		ShowWidget();
	}
}

void UDialogueFallbackWidget::ClearInput()
{
	if (TextInputBox)
	{
		TextInputBox->SetText(FText::GetEmpty());
	}
}

void UDialogueFallbackWidget::FocusInput()
{
	if (TextInputBox)
	{
		TextInputBox->SetKeyboardFocus();
	}
}

void UDialogueFallbackWidget::SetStatusText(const FString& StatusText)
{
	if (StatusTextBlock)
	{
		StatusTextBlock->SetText(FText::FromString(StatusText));
	}
}

void UDialogueFallbackWidget::SetInputEnabled(bool bEnabled)
{
	if (TextInputBox)
	{
		TextInputBox->SetIsReadOnly(!bEnabled);
	}

	if (SendButton)
	{
		SendButton->SetIsEnabled(bEnabled);
	}
}

void UDialogueFallbackWidget::OnSendButtonClicked()
{
	SubmitCurrentText();
}

void UDialogueFallbackWidget::OnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		SubmitCurrentText();
	}
}

void UDialogueFallbackWidget::SubmitCurrentText()
{
	if (!TextInputBox)
	{
		return;
	}

	FString InputText = TextInputBox->GetText().ToString().TrimStartAndEnd();
	if (InputText.IsEmpty())
	{
		return;
	}

	// Clear the input and fire the delegate
	ClearInput();
	OnTextSubmitted.Broadcast(InputText);
}
