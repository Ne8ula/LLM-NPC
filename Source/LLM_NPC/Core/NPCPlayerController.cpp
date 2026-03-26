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

		// Capture typed characters (A-Z, 0-9, space, punctuation)
		static const EKeys::Type CharKeys[] = {
			EKeys::A, EKeys::B, EKeys::C, EKeys::D, EKeys::E, EKeys::F, EKeys::G,
			EKeys::H, EKeys::I, EKeys::J, EKeys::K, EKeys::L, EKeys::M, EKeys::N,
			EKeys::O, EKeys::P, EKeys::Q, EKeys::R, EKeys::S, EKeys::U,
			EKeys::V, EKeys::W, EKeys::X, EKeys::Y, EKeys::Z,
			EKeys::Zero, EKeys::One, EKeys::Two, EKeys::Three, EKeys::Four,
			EKeys::Five, EKeys::Six, EKeys::Seven, EKeys::Eight, EKeys::Nine,
			EKeys::SpaceBar, EKeys::Period, EKeys::Comma, EKeys::Semicolon,
			EKeys::Apostrophe, EKeys::Hyphen, EKeys::Equals, EKeys::Slash,
			EKeys::Exclamation
		};

		bool bShift = IsInputKeyDown(EKeys::LeftShift) || IsInputKeyDown(EKeys::RightShift);

		for (EKeys::Type Key : CharKeys)
		{
			if (WasInputKeyJustPressed(FKey(Key)))
			{
				FString KeyName = FKey(Key).GetFName().ToString();

				// Map key to character
				FString Char;
				if (KeyName.Len() == 1)
				{
					Char = bShift ? KeyName.ToUpper() : KeyName.ToLower();
				}
				else if (Key == EKeys::SpaceBar) Char = TEXT(" ");
				else if (Key == EKeys::Period) Char = bShift ? TEXT(">") : TEXT(".");
				else if (Key == EKeys::Comma) Char = bShift ? TEXT("<") : TEXT(",");
				else if (Key == EKeys::Semicolon) Char = bShift ? TEXT(":") : TEXT(";");
				else if (Key == EKeys::Apostrophe) Char = bShift ? TEXT("\"") : TEXT("'");
				else if (Key == EKeys::Hyphen) Char = bShift ? TEXT("_") : TEXT("-");
				else if (Key == EKeys::Equals) Char = bShift ? TEXT("+") : TEXT("=");
				else if (Key == EKeys::Slash) Char = bShift ? TEXT("?") : TEXT("/");
				else if (Key == EKeys::Exclamation) Char = TEXT("!");
				else if (KeyName.StartsWith(TEXT("Zero"))) Char = bShift ? TEXT(")") : TEXT("0");
				else if (KeyName.StartsWith(TEXT("One"))) Char = bShift ? TEXT("!") : TEXT("1");
				else if (KeyName.StartsWith(TEXT("Two"))) Char = bShift ? TEXT("@") : TEXT("2");
				else if (KeyName.StartsWith(TEXT("Three"))) Char = bShift ? TEXT("#") : TEXT("3");
				else if (KeyName.StartsWith(TEXT("Four"))) Char = bShift ? TEXT("$") : TEXT("4");
				else if (KeyName.StartsWith(TEXT("Five"))) Char = bShift ? TEXT("%") : TEXT("5");
				else if (KeyName.StartsWith(TEXT("Six"))) Char = bShift ? TEXT("^") : TEXT("6");
				else if (KeyName.StartsWith(TEXT("Seven"))) Char = bShift ? TEXT("&") : TEXT("7");
				else if (KeyName.StartsWith(TEXT("Eight"))) Char = bShift ? TEXT("*") : TEXT("8");
				else if (KeyName.StartsWith(TEXT("Nine"))) Char = bShift ? TEXT("(") : TEXT("9");

				if (!Char.IsEmpty())
				{
					HUD->AppendToInput(Char);
				}
			}
		}
	}
}

void ANPCPlayerController::ToggleDialogueInput()
{
	if (ANPCDialogueHUD* HUD = Cast<ANPCDialogueHUD>(GetHUD()))
	{
		HUD->ToggleDialogueInput();
	}
}
