#include "NPCPlayerController.h"
#include "NPCDialogueHUD.h"
#include "GameFramework/PlayerInput.h"

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
}

void ANPCPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void ANPCPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ANPCDialogueHUD* HUD = Cast<ANPCDialogueHUD>(GetHUD());
	if (!HUD)
	{
		return;
	}

	// T key toggle with edge detection
	bool bTDown = IsInputKeyDown(EKeys::T);
	if (bTDown && !bTKeyWasDown && !HUD->IsDialogueVisible())
	{
		HUD->ToggleDialogueInput();
	}
	// Only allow T to close when not typing
	if (bTDown && !bTKeyWasDown && HUD->IsDialogueVisible() && HUD->GetInputBuffer().IsEmpty())
	{
		HUD->ToggleDialogueInput();
	}
	bTKeyWasDown = bTDown;

	// When dialogue is visible, capture keyboard for typing
	if (HUD->IsDialogueVisible())
	{
		// Enter to submit
		if (WasInputKeyJustPressed(EKeys::Enter))
		{
			FString Input = HUD->GetInputBuffer();
			if (!Input.IsEmpty())
			{
				HUD->SubmitChatMessage(Input);
			}
		}

		// Backspace
		if (WasInputKeyJustPressed(EKeys::BackSpace))
		{
			HUD->BackspaceInput();
		}

		// Capture typed characters using FKey
		bool bShift = IsInputKeyDown(EKeys::LeftShift) || IsInputKeyDown(EKeys::RightShift);

		// Helper lambda to check key and append char
		auto TryKey = [&](FKey InKey, const TCHAR* Normal, const TCHAR* Shifted = nullptr)
		{
			if (WasInputKeyJustPressed(InKey))
			{
				HUD->AppendToInput(FString((bShift && Shifted) ? Shifted : Normal));
			}
		};

		// Letters
		TryKey(EKeys::A, TEXT("a"), TEXT("A"));
		TryKey(EKeys::B, TEXT("b"), TEXT("B"));
		TryKey(EKeys::C, TEXT("c"), TEXT("C"));
		TryKey(EKeys::D, TEXT("d"), TEXT("D"));
		TryKey(EKeys::E, TEXT("e"), TEXT("E"));
		TryKey(EKeys::F, TEXT("f"), TEXT("F"));
		TryKey(EKeys::G, TEXT("g"), TEXT("G"));
		TryKey(EKeys::H, TEXT("h"), TEXT("H"));
		TryKey(EKeys::I, TEXT("i"), TEXT("I"));
		TryKey(EKeys::J, TEXT("j"), TEXT("J"));
		TryKey(EKeys::K, TEXT("k"), TEXT("K"));
		TryKey(EKeys::L, TEXT("l"), TEXT("L"));
		TryKey(EKeys::M, TEXT("m"), TEXT("M"));
		TryKey(EKeys::N, TEXT("n"), TEXT("N"));
		TryKey(EKeys::O, TEXT("o"), TEXT("O"));
		TryKey(EKeys::P, TEXT("p"), TEXT("P"));
		TryKey(EKeys::Q, TEXT("q"), TEXT("Q"));
		TryKey(EKeys::R, TEXT("r"), TEXT("R"));
		TryKey(EKeys::S, TEXT("s"), TEXT("S"));
		TryKey(EKeys::U, TEXT("u"), TEXT("U"));
		TryKey(EKeys::V, TEXT("v"), TEXT("V"));
		TryKey(EKeys::W, TEXT("w"), TEXT("W"));
		TryKey(EKeys::X, TEXT("x"), TEXT("X"));
		TryKey(EKeys::Y, TEXT("y"), TEXT("Y"));
		TryKey(EKeys::Z, TEXT("z"), TEXT("Z"));

		// Numbers
		TryKey(EKeys::Zero, TEXT("0"), TEXT(")"));
		TryKey(EKeys::One, TEXT("1"), TEXT("!"));
		TryKey(EKeys::Two, TEXT("2"), TEXT("@"));
		TryKey(EKeys::Three, TEXT("3"), TEXT("#"));
		TryKey(EKeys::Four, TEXT("4"), TEXT("$"));
		TryKey(EKeys::Five, TEXT("5"), TEXT("%"));
		TryKey(EKeys::Six, TEXT("6"), TEXT("^"));
		TryKey(EKeys::Seven, TEXT("7"), TEXT("&"));
		TryKey(EKeys::Eight, TEXT("8"), TEXT("*"));
		TryKey(EKeys::Nine, TEXT("9"), TEXT("("));

		// Punctuation and space
		TryKey(EKeys::SpaceBar, TEXT(" "));
		TryKey(EKeys::Period, TEXT("."), TEXT(">"));
		TryKey(EKeys::Comma, TEXT(","), TEXT("<"));
		TryKey(EKeys::Semicolon, TEXT(";"), TEXT(":"));
		TryKey(EKeys::Apostrophe, TEXT("'"), TEXT("\""));
		TryKey(EKeys::Hyphen, TEXT("-"), TEXT("_"));
		TryKey(EKeys::Equals, TEXT("="), TEXT("+"));
		TryKey(EKeys::Slash, TEXT("/"), TEXT("?"));
	}
}

void ANPCPlayerController::ToggleDialogueInput()
{
	if (ANPCDialogueHUD* HUD = Cast<ANPCDialogueHUD>(GetHUD()))
	{
		HUD->ToggleDialogueInput();
	}
}
