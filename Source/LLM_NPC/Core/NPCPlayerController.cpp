#include "NPCPlayerController.h"
#include "NPCDialogueHUD.h"
#include "NPCCharacter.h"
#include "LLM_NPC/Dialogue/WhisperSTTComponent.h"
#include "LLM_NPC/Gesture/GestureRecognitionComponent.h"
#include "LLM_NPC/Vision/FacialRecognitionComponent.h"
#include "GameFramework/PlayerInput.h"
#include "Kismet/GameplayStatics.h"

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

	// Chat starts visible, so disable pawn movement immediately
	GetWorldTimerManager().SetTimerForNextTick([this]()
	{
		if (GetPawn()) GetPawn()->DisableInput(this);
	});
}

void ANPCPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void ANPCPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update proximity focus each tick
	UpdateNPCFocus();

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
		if (GetPawn()) GetPawn()->DisableInput(this);
	}
	bTKeyWasDown = bTDown;

	// Escape closes chat and re-enables movement
	if (WasInputKeyJustPressed(EKeys::Escape) && HUD->IsDialogueVisible())
	{
		HUD->ToggleDialogueInput();
		if (GetPawn()) GetPawn()->EnableInput(this);
	}

	// V key push-to-talk: routes to focused NPC's WhisperSTT
	bool bVDown = IsInputKeyDown(EKeys::V);
	if (bVDown && !bVKeyWasDown)
	{
		if (IsValid(FocusedNPC) && FocusedNPC->WhisperSTTComponent)
		{
			FocusedNPC->WhisperSTTComponent->StartRecording();
			HUD->SetStatus(TEXT("Recording... release V to send."));
		}
	}
	else if (!bVDown && bVKeyWasDown)
	{
		if (IsValid(FocusedNPC) && FocusedNPC->WhisperSTTComponent)
		{
			FocusedNPC->WhisperSTTComponent->StopRecordingAndTranscribe();
			HUD->SetStatus(TEXT("Transcribing..."));
		}
	}
	bVKeyWasDown = bVDown;

	// When dialogue is visible, capture keyboard for typing
	if (HUD->IsDialogueVisible())
	{
		// Enter to submit — also consumes pending gesture intent
		if (WasInputKeyJustPressed(EKeys::Enter))
		{
			FString Input = HUD->GetInputBuffer();
			if (!Input.IsEmpty())
			{
				HUD->SubmitChatMessage(Input);
				PendingGestureIntent = EGestureIntent::None;
			}
		}

		// Backspace
		if (WasInputKeyJustPressed(EKeys::BackSpace))
		{
			HUD->BackspaceInput();
		}

		bool bShift = IsInputKeyDown(EKeys::LeftShift) || IsInputKeyDown(EKeys::RightShift);

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

void ANPCPlayerController::UpdateNPCFocus()
{
	ANPCCharacter* NewFocus = FindNearestNPCInRange();
	if (NewFocus == FocusedNPC)
	{
		return;
	}

	// Unbind from old focused NPC
	if (IsValid(FocusedNPC))
	{
		if (FocusedNPC->GestureRecognitionComponent)
		{
			FocusedNPC->GestureRecognitionComponent->OnGestureDetected.RemoveDynamic(
				this, &ANPCPlayerController::OnGestureDetected);
		}
		if (FocusedNPC->FacialRecognitionComponent)
		{
			FocusedNPC->FacialRecognitionComponent->ShutdownSubsystem();
		}
	}

	FocusedNPC = NewFocus;

	// Bind to new focused NPC
	if (IsValid(FocusedNPC))
	{
		if (FocusedNPC->GestureRecognitionComponent)
		{
			FocusedNPC->GestureRecognitionComponent->OnGestureDetected.AddDynamic(
				this, &ANPCPlayerController::OnGestureDetected);
		}
		if (FocusedNPC->FacialRecognitionComponent)
		{
			FocusedNPC->FacialRecognitionComponent->InitializeSubsystem();
		}
	}

	// Clear stale gesture intent on focus switch
	PendingGestureIntent = EGestureIntent::None;

	// Notify HUD to rebind its delegates
	if (ANPCDialogueHUD* HUD = Cast<ANPCDialogueHUD>(GetHUD()))
	{
		HUD->SetFocusedNPC(FocusedNPC);
	}
}

ANPCCharacter* ANPCPlayerController::FindNearestNPCInRange() const
{
	APawn* PlayerPawn = GetPawn();
	if (!PlayerPawn)
	{
		return nullptr;
	}

	const FVector PlayerLocation = PlayerPawn->GetActorLocation();
	const FVector PlayerForward = PlayerPawn->GetActorForwardVector();
	const float RadiusSq = InteractionRadius * InteractionRadius;

	TArray<AActor*> NPCActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANPCCharacter::StaticClass(), NPCActors);

	ANPCCharacter* Nearest = nullptr;
	float NearestDistSq = RadiusSq;

	for (AActor* Actor : NPCActors)
	{
		ANPCCharacter* NPC = Cast<ANPCCharacter>(Actor);
		if (!NPC)
		{
			continue;
		}

		const FVector Delta = NPC->GetActorLocation() - PlayerLocation;
		const float DistSq = Delta.SizeSquared();

		if (DistSq > NearestDistSq)
		{
			continue;
		}

		// Facing check: NPC must be in the forward hemisphere
		if (FVector::DotProduct(PlayerForward, Delta.GetSafeNormal()) < 0.0f)
		{
			continue;
		}

		NearestDistSq = DistSq;
		Nearest = NPC;
	}

	return Nearest;
}

void ANPCPlayerController::OnGestureDetected(FGestureInput DetectedGesture)
{
	switch (DetectedGesture.GestureType)
	{
	case EGestureType::Pinch:   PendingGestureIntent = EGestureIntent::Withhold;   break;
	case EGestureType::Spread:  PendingGestureIntent = EGestureIntent::Disclose;   break;
	case EGestureType::Rotate:  PendingGestureIntent = EGestureIntent::Doubt;      break;
	case EGestureType::Spindle: PendingGestureIntent = EGestureIntent::Synthesise; break;
	default:                    PendingGestureIntent = EGestureIntent::None;       break;
	}
}
