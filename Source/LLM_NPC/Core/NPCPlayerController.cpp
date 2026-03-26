#include "NPCPlayerController.h"
#include "NPCDialogueHUD.h"

ANPCPlayerController::ANPCPlayerController()
{
	// Show mouse cursor for UI interaction
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ANPCPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Bind T key to toggle dialogue
	InputComponent->BindAction("ToggleTextInput", IE_Pressed, this, &ANPCPlayerController::ToggleDialogueInput);

	// Also bind T directly in case action mapping isn't set
	InputComponent->BindKey(EKeys::T, IE_Pressed, this, &ANPCPlayerController::ToggleDialogueInput);
}

void ANPCPlayerController::ToggleDialogueInput()
{
	if (ANPCDialogueHUD* DialogueHUD = Cast<ANPCDialogueHUD>(GetHUD()))
	{
		DialogueHUD->ToggleDialogueInput();

		// Toggle input mode between game and UI
		if (bShowMouseCursor)
		{
			FInputModeGameAndUI InputMode;
			InputMode.SetHideCursorDuringCapture(false);
			SetInputMode(InputMode);
		}
	}
}
