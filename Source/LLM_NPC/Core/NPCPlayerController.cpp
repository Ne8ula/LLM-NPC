#include "NPCPlayerController.h"
#include "NPCDialogueHUD.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"

ANPCPlayerController::ANPCPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ANPCPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Set input mode to Game and UI so we can interact with widgets
	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);

	UE_LOG(LogTemp, Log, TEXT("NPCPlayerController: BeginPlay, setting up Enhanced Input"));
}

void ANPCPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Try Enhanced Input first (UE5.7 default)
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		UE_LOG(LogTemp, Log, TEXT("NPCPlayerController: Using Enhanced Input System"));
		// We'll handle T key via Tick since we can't easily create InputAction assets from C++
	}

	// Also bind using legacy system as fallback
	if (InputComponent)
	{
		InputComponent->BindKey(EKeys::T, IE_Pressed, this, &ANPCPlayerController::ToggleDialogueInput);
		UE_LOG(LogTemp, Log, TEXT("NPCPlayerController: Bound T key via legacy input"));
	}
}

void ANPCPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Poll T key directly as fallback for Enhanced Input
	if (WasInputKeyJustPressed(EKeys::T))
	{
		ToggleDialogueInput();
	}
}

void ANPCPlayerController::ToggleDialogueInput()
{
	if (ANPCDialogueHUD* DialogueHUD = Cast<ANPCDialogueHUD>(GetHUD()))
	{
		DialogueHUD->ToggleDialogueInput();
		UE_LOG(LogTemp, Log, TEXT("NPCPlayerController: Toggled dialogue input"));

		FInputModeGameAndUI InputMode;
		InputMode.SetHideCursorDuringCapture(false);
		SetInputMode(InputMode);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NPCPlayerController: No NPCDialogueHUD found on GetHUD()"));
	}
}
