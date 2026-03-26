#include "NPCPlayerController.h"
#include "NPCDialogueHUD.h"

ANPCPlayerController::ANPCPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ANPCPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);

	UE_LOG(LogTemp, Log, TEXT("NPCPlayerController: BeginPlay"));
}

void ANPCPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void ANPCPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Manual edge detection: only fire on key DOWN transition
	bool bTKeyDown = IsInputKeyDown(EKeys::T);
	if (bTKeyDown && !bTKeyWasDown)
	{
		ToggleDialogueInput();
	}
	bTKeyWasDown = bTKeyDown;
}

void ANPCPlayerController::ToggleDialogueInput()
{
	if (ANPCDialogueHUD* DialogueHUD = Cast<ANPCDialogueHUD>(GetHUD()))
	{
		bDialogueVisible = !bDialogueVisible;
		DialogueHUD->ToggleDialogueInput();
		UE_LOG(LogTemp, Log, TEXT("NPCPlayerController: Dialogue %s"), bDialogueVisible ? TEXT("OPENED") : TEXT("CLOSED"));

		if (bDialogueVisible)
		{
			FInputModeUIOnly InputMode;
			SetInputMode(InputMode);
		}
		else
		{
			FInputModeGameAndUI InputMode;
			InputMode.SetHideCursorDuringCapture(false);
			SetInputMode(InputMode);
		}
	}
}
