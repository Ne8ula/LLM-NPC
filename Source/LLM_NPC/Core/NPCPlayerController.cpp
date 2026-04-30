#include "NPCPlayerController.h"
#include "NPCDialogueHUD.h"
#include "NPCCharacter.h"
#include "LLM_NPC/Dialogue/DialogueComponent.h"
#include "LLM_NPC/Dialogue/WhisperSTTComponent.h"
#include "LLM_NPC/Dialogue/SpeakerIdentificationComponent.h"
#include "LLM_NPC/Gesture/GestureRecognitionComponent.h"
#include "LLM_NPC/Gesture/InspectableItem.h"
#include "LLM_NPC/Vision/FacialRecognitionComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Engine/Engine.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerInput.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ANPCPlayerController::ANPCPlayerController()
{
	// Start hidden — FPS-style mouse look. SetGameAndUIInputMode() flips this on when
	// the chat overlay opens (T key) so click-to-focus works on the input box.
	bShowMouseCursor = false;
	DefaultMouseCursor = EMouseCursor::Default;

	// UE 5.4+ FP template registers IMCs at the PlayerController, not the pawn.
	// We pre-load the FP feature pack's stock IMCs so any project using the FP pack
	// gets WASD/look/jump out of the box. Override on a BP subclass for custom IMCs.
	{
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCDefault(
			TEXT("/Game/Input/IMC_Default"));
		if (IMCDefault.Succeeded())
		{
			DefaultMappingContexts.Add(IMCDefault.Object);
		}
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCMouseLook(
			TEXT("/Game/Input/IMC_MouseLook"));
		if (IMCMouseLook.Succeeded())
		{
			DefaultMappingContexts.Add(IMCMouseLook.Object);
		}
	}
}

void ANPCPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Start in FPS mode — mouse captured continuously, cursor hidden, no clicking required
	// to look around. Tick() flips to GameAndUI when the chat overlay opens.
	SetGameOnlyInputMode();

	UE_LOG(LogTemp, Warning,
		TEXT("[NPCPlayerController DIAG] InputComponent class = %s"),
		*GetNameSafe(InputComponent ? InputComponent->GetClass() : nullptr));
}

void ANPCPlayerController::SetGameOnlyInputMode()
{
	FInputModeGameOnly Mode;
	SetInputMode(Mode);
	bShowMouseCursor = false;
}

void ANPCPlayerController::SetGameAndUIInputMode()
{
	FInputModeGameAndUI Mode;
	Mode.SetHideCursorDuringCapture(false);
	Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(Mode);
	bShowMouseCursor = true;
}

void ANPCPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UE_LOG(LogTemp, Warning,
		TEXT("[NPCPlayerController DIAG] OnPossess: pawn = %s (class %s)"),
		*GetNameSafe(InPawn),
		*GetNameSafe(InPawn ? InPawn->GetClass() : nullptr));

	// Register every default mapping context against the local player's Enhanced Input
	// subsystem. This is the UE 5.4+ canonical place — the FP feature pack ships with
	// BP_FirstPersonPlayerController doing the same thing.
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* IMC : DefaultMappingContexts)
		{
			if (!IMC)
			{
				continue;
			}
			Subsystem->AddMappingContext(IMC, DefaultMappingContextPriority);
			UE_LOG(LogTemp, Log, TEXT("[NPCPlayerController] Added IMC: %s (priority %d)"),
				*IMC->GetName(), DefaultMappingContextPriority);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning,
			TEXT("[NPCPlayerController] OnPossess: no EnhancedInputLocalPlayerSubsystem; movement will not work."));
	}
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

	// Tier 3 session timer — when the focused NPC's session has run past its
	// budget without a Convergent climax, this dispatches the time-out sentinel
	// turn and Claude returns the recursive_silence closing line.
	if (IsValid(FocusedNPC) && FocusedNPC->DialogueComponent)
	{
		FocusedNPC->DialogueComponent->TickSession();
	}

	ANPCDialogueHUD* HUD = Cast<ANPCDialogueHUD>(GetHUD());
	if (!HUD)
	{
		return;
	}

	// T key toggles the chat overlay (movement always remains enabled)
	bool bTDown = IsInputKeyDown(EKeys::T);
	if (bTDown && !bTKeyWasDown)
	{
		HUD->ToggleDialogueInput();
	}
	bTKeyWasDown = bTDown;

	// Escape hides the chat overlay
	if (WasInputKeyJustPressed(EKeys::Escape) && HUD->IsDialogueVisible())
	{
		HUD->ToggleDialogueInput();
	}

	// Track chat overlay open/close transitions and flip input modes accordingly.
	// FPS mode (cursor hidden, mouse captured continuously) when chat is closed —
	// player looks around with raw mouse delta, no clicking required. GameAndUI
	// (cursor visible) the moment chat opens so the input box can be clicked.
	const bool bChatOverlayOpenNow = HUD->IsDialogueVisible();
	if (bChatOverlayOpenNow != bChatOverlayWasOpen)
	{
		if (bChatOverlayOpenNow)
		{
			SetGameAndUIInputMode();
		}
		else
		{
			SetGameOnlyInputMode();
		}
		bChatOverlayWasOpen = bChatOverlayOpenNow;
	}

	// Left click — focus or unfocus the text input box
	if (WasInputKeyJustPressed(EKeys::LeftMouseButton))
	{
		float MouseX, MouseY;
		if (GetMousePosition(MouseX, MouseY))
		{
			HUD->HandleMouseClick(MouseX, MouseY);
		}
	}

	// E / F / Q for inspect verbs. Gated on text-input NOT being focused — otherwise
	// typing those letters in the chat input would trigger pickup/present/drop. The
	// existing TryKey block below already gates text capture on IsTextInputActive(),
	// so these inspect bindings are the natural fallthrough when the input box is unfocused.
	const bool bTextActive = HUD->IsDialogueVisible() && HUD->IsTextInputActive();

	bool bEDown = IsInputKeyDown(EKeys::E);
	if (bEDown && !bEKeyWasDown && !bTextActive)
	{
		HandleEPressed();
	}
	bEKeyWasDown = bEDown;

	bool bFDown = IsInputKeyDown(EKeys::F);
	if (bFDown && !bFKeyWasDown && !bTextActive)
	{
		HandleFPressed();
	}
	bFKeyWasDown = bFDown;

	bool bQDown = IsInputKeyDown(EKeys::Q);
	if (bQDown && !bQKeyWasDown && !bTextActive)
	{
		HandleQPressed();
	}
	bQKeyWasDown = bQDown;

	// On-screen debug: prove every frame whether the Ctrl/C key state is reaching this controller.
	// Yellow text appears top-left of viewport when ANY of these keys is currently held.
	if (GEngine)
	{
		const bool bDbgLCtrl = IsInputKeyDown(EKeys::LeftControl);
		const bool bDbgRCtrl = IsInputKeyDown(EKeys::RightControl);
		const bool bDbgC = IsInputKeyDown(EKeys::C);
		if (bDbgLCtrl || bDbgRCtrl || bDbgC)
		{
			GEngine->AddOnScreenDebugMessage(
				42, 0.2f, FColor::Yellow,
				FString::Printf(TEXT("LCtrl=%d RCtrl=%d C=%d  TextActive=%d"),
					bDbgLCtrl, bDbgRCtrl, bDbgC, bTextActive));
		}
	}

	// Crouch toggle — bound to Left Ctrl AND C as a fallback test. If LCtrl never fires
	// but C does, the FP template (or some Slate focus) is consuming LCtrl somewhere.
	const bool bCrouchKeyDown =
		IsInputKeyDown(EKeys::LeftControl) ||
		IsInputKeyDown(EKeys::RightControl) ||
		IsInputKeyDown(EKeys::C);
	if (bCrouchKeyDown && !bLCtrlKeyWasDown && !bTextActive)
	{
		ACharacter* MyCharacter = Cast<ACharacter>(GetPawn());
		UCharacterMovementComponent* MoveComp = MyCharacter ? MyCharacter->GetCharacterMovement() : nullptr;
		UE_LOG(LogTemp, Warning, TEXT("[Crouch] key pressed | Pawn=%s | CMC=%s | CanCrouch=%d | IsCrouching=%d"),
			*GetNameSafe(MyCharacter),
			*GetNameSafe(MoveComp),
			MoveComp ? (int32)MoveComp->NavAgentProps.bCanCrouch : 0,
			MoveComp ? (int32)MoveComp->IsCrouching() : -1);
		if (MoveComp)
		{
			if (MoveComp->IsCrouching())
			{
				MyCharacter->UnCrouch();
			}
			else
			{
				MyCharacter->Crouch();
			}
		}
	}
	bLCtrlKeyWasDown = bCrouchKeyDown;

	// Tier 2: 1/2 manual speaker override — primes the next utterance's
	// tag regardless of what acoustic ID would have picked. Gated on
	// !bTextActive so typing "1" or "2" into the chat input doesn't
	// accidentally override.
	{
		const bool b1Down = IsInputKeyDown(EKeys::One);
		if (b1Down && !b1KeyWasDown && !bTextActive)
		{
			if (IsValid(FocusedNPC) && FocusedNPC->SpeakerIdentificationComponent)
			{
				FocusedNPC->SpeakerIdentificationComponent->SetManualOverrideTag(FName(TEXT("Speaker_A")));
				UE_LOG(LogTemp, Log, TEXT("[SpeakerOverride] next utterance forced to Speaker_A"));
			}
		}
		b1KeyWasDown = b1Down;

		const bool b2Down = IsInputKeyDown(EKeys::Two);
		if (b2Down && !b2KeyWasDown && !bTextActive)
		{
			if (IsValid(FocusedNPC) && FocusedNPC->SpeakerIdentificationComponent)
			{
				FocusedNPC->SpeakerIdentificationComponent->SetManualOverrideTag(FName(TEXT("Speaker_B")));
				UE_LOG(LogTemp, Log, TEXT("[SpeakerOverride] next utterance forced to Speaker_B"));
			}
		}
		b2KeyWasDown = b2Down;
	}

	// While holding an item, every tick: keep it in the camera's hand-position,
	// apply mouse-drag rotation (RMB held), and apply scroll-wheel scale.
	TickHeldItem(DeltaTime);

	// (V push-to-talk removed. Voice now auto-starts in UpdateNPCFocus when entering an
	// NPC's vicinity and auto-stops + transcribes when leaving.)

	// Only capture keyboard when the user has clicked the input box
	if (HUD->IsDialogueVisible() && HUD->IsTextInputActive())
	{
		// Enter to submit. Gesture intent is consumed inside SubmitChatMessage —
		// that is the canonical consumption point for both Enter and voice-transcript flows.
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

	// Unbind from old focused NPC. Voice mic is NOT torn down here — see the
	// "single-user slice" note below; WhisperSTT auto-starts in its own
	// InitializeSubsystem and runs continuously for the whole PIE session.
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
		if (FocusedNPC->SpeakerIdentificationComponent)
		{
			FocusedNPC->SpeakerIdentificationComponent->OnSpeakerIdentified.RemoveDynamic(
				this, &ANPCPlayerController::HandleSpeakerIdentified);
			// Drop any pending 1/2 override on focus loss — a primed override
			// for the previous NPC shouldn't bleed into the next conversation.
			FocusedNPC->SpeakerIdentificationComponent->ClearManualOverride();
		}
	}

	FocusedNPC = NewFocus;

	// Bind to new focused NPC. Single-user slice intentionally does NOT
	// Start/Stop the WhisperSTT recording on focus change: focus
	// flicker (chat-overlay mode flips, sub-degree mouse-look jitter at
	// the proximity/facing boundary) would otherwise tear down + restart
	// waveIn every tick, resetting VAD state and producing 0-byte
	// captures forever after the first NPC turn. The mic stays open;
	// the echo gate handles TTS bleed-through; transcripts route via
	// the HUD's BoundSTT subscription rebound below in SetFocusedNPC.
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
		if (FocusedNPC->SpeakerIdentificationComponent)
		{
			FocusedNPC->SpeakerIdentificationComponent->OnSpeakerIdentified.AddDynamic(
				this, &ANPCPlayerController::HandleSpeakerIdentified);
		}
		if (ANPCDialogueHUD* HUD = Cast<ANPCDialogueHUD>(GetHUD()))
		{
			HUD->SetVoiceRecording(true);
		}
	}
	else
	{
		// Player left every NPC's vicinity — clear the REC indicator.
		// (Mic is still capturing; transcripts just have nowhere to route.)
		if (ANPCDialogueHUD* HUD = Cast<ANPCDialogueHUD>(GetHUD()))
		{
			HUD->SetVoiceRecording(false);
		}
	}

	// Clear stale gesture intent on focus switch
	PendingGestureIntent = EGestureIntent::None;

	// Clear stale speaker tag on focus switch — same reasoning. The HUD-
	// chip-facing `LastSpeakerTag` is intentionally NOT cleared so the
	// chip retains its last visible state until a new identification.
	PendingSpeakerTag = NAME_None;

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

	// Hysteresis: gain focus only when clearly inside the radius and clearly
	// facing the NPC; keep focus until the player has clearly stepped away or
	// turned around. Without this, the dot-product-vs-zero and distance-vs-
	// exactly-radius checks flip on sub-degree mouse-look jitter every tick,
	// which tears down + restarts WhisperSTT recording (and resets VAD state)
	// so no user speech ever accumulates long enough to dispatch.
	const float GainRadiusSq      = InteractionRadius * InteractionRadius;
	const float KeepRadius        = InteractionRadius * 1.25f;
	const float KeepRadiusSq      = KeepRadius * KeepRadius;
	const float GainFacingDotMin  =  0.1f;   // must clearly face NPC to engage
	const float KeepFacingDotMin  = -0.3f;   // must clearly turn away to disengage

	TArray<AActor*> NPCActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANPCCharacter::StaticClass(), NPCActors);

	ANPCCharacter* Nearest = nullptr;
	float NearestDistSq = TNumericLimits<float>::Max();

	for (AActor* Actor : NPCActors)
	{
		ANPCCharacter* NPC = Cast<ANPCCharacter>(Actor);
		if (!NPC)
		{
			continue;
		}

		const FVector Delta    = NPC->GetActorLocation() - PlayerLocation;
		const float   DistSq   = Delta.SizeSquared();
		const float   FaceDot  = FVector::DotProduct(PlayerForward, Delta.GetSafeNormal());

		const bool   bIsCurrent  = (NPC == FocusedNPC);
		const float  MaxDistSq   = bIsCurrent ? KeepRadiusSq    : GainRadiusSq;
		const float  FacingMin   = bIsCurrent ? KeepFacingDotMin : GainFacingDotMin;

		if (DistSq > MaxDistSq)
		{
			continue;
		}
		if (FaceDot < FacingMin)
		{
			continue;
		}

		if (DistSq < NearestDistSq)
		{
			NearestDistSq = DistSq;
			Nearest = NPC;
		}
	}

	return Nearest;
}

void ANPCPlayerController::HandleSpeakerIdentified(FName Tag, float Confidence)
{
	// Cache for this turn's dispatch (consumed by HUD::SubmitChatMessage)
	// AND for the HUD chip (sticky, persists across dispatches).
	PendingSpeakerTag = Tag;
	LastSpeakerTag = Tag;
	LastSpeakerConfidence = Confidence;
	UE_LOG(LogTemp, Log, TEXT("[SpeakerID] resolved %s (%.2f)"),
		*Tag.ToString(), Confidence);
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

// ===========================================================================
// Memory Archive — Tier 1 inspect / present / drop
// ===========================================================================

AInspectableItem* ANPCPlayerController::TraceForInspectable() const
{
	APawn* MyPawn = GetPawn();
	if (!MyPawn || !PlayerCameraManager || !GetWorld())
	{
		return nullptr;
	}

	const FVector Start = PlayerCameraManager->GetCameraLocation();
	const FVector End = Start + PlayerCameraManager->GetCameraRotation().Vector() * MaxInteractionDistance;

	FCollisionQueryParams Params(SCENE_QUERY_STAT(NPCInspectableTrace), false, MyPawn);
	Params.AddIgnoredActor(MyPawn);

	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		return Cast<AInspectableItem>(Hit.GetActor());
	}
	return nullptr;
}

void ANPCPlayerController::HandleEPressed()
{
	// E while holding -> drop (silent, no Claude turn).
	if (HeldItem.IsValid())
	{
		DropHeldItem();
		return;
	}

	// E while not holding -> trace and pick up.
	if (AInspectableItem* Item = TraceForInspectable())
	{
		PickupItem(Item);
	}
}

void ANPCPlayerController::HandleFPressed()
{
	if (!HeldItem.IsValid())
	{
		return;
	}
	if (!IsValid(FocusedNPC) || !FocusedNPC->DialogueComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Present: no focused NPC or DialogueComponent on focus."));
		return;
	}

	FDetectedUserEmotion DefaultEmotion;
	DefaultEmotion.Emotion = EEmotionType::Neutral;
	DefaultEmotion.Confidence = 0.0f;

	// Consume the cached gesture intent + speaker tag for this turn — same
	// pattern as the HUD uses for typed/voice messages.
	const EGestureIntent Gesture = PendingGestureIntent;
	PendingGestureIntent = EGestureIntent::None;
	const FName SpeakerTag = PendingSpeakerTag;
	PendingSpeakerTag = NAME_None;

	FocusedNPC->DialogueComponent->SendObjectPresentMessage(
		HeldItem.Get(), DefaultEmotion, Gesture, SpeakerTag);

	// Per the handoff: do NOT clear hold after presenting. Player may keep the item
	// out, drop with Q, or pick up another with E.
}

void ANPCPlayerController::HandleQPressed()
{
	if (HeldItem.IsValid())
	{
		DropHeldItem();
	}
}

void ANPCPlayerController::PickupItem(AInspectableItem* Item)
{
	if (!Item)
	{
		return;
	}

	HeldItem = Item;
	HeldItemOriginalLocation = Item->GetActorLocation();

	// Per-speaker memory write — silent state-tracking, no Claude turn fires.
	// Pickup ALWAYS registers inspection. If the player is currently focused on
	// an NPC, write to that NPC's component; otherwise fall back to the only
	// NPC in the level (single-NPC slice assumption) so items inspected before
	// the player walks up to the Friend still count toward trust.
	UDialogueComponent* TargetDialogue = nullptr;
	if (IsValid(FocusedNPC) && FocusedNPC->DialogueComponent)
	{
		TargetDialogue = FocusedNPC->DialogueComponent;
	}
	else
	{
		TArray<AActor*> NPCActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANPCCharacter::StaticClass(), NPCActors);
		for (AActor* Actor : NPCActors)
		{
			if (ANPCCharacter* NPC = Cast<ANPCCharacter>(Actor))
			{
				if (NPC->DialogueComponent)
				{
					TargetDialogue = NPC->DialogueComponent;
					break;
				}
			}
		}
	}

	if (TargetDialogue)
	{
		const FName SpeakerID = LastSpeakerTag.IsNone()
			? UDialogueComponent::GetDefaultSpeakerID()
			: LastSpeakerTag;
		TargetDialogue->RecordItemInspection(Item->ItemID, SpeakerID);
	}

	UE_LOG(LogTemp, Log, TEXT("Picked up '%s' (ID=%s)"),
		*Item->ItemDisplayName, *Item->ItemID.ToString());
}

void ANPCPlayerController::DropHeldItem()
{
	if (!HeldItem.IsValid())
	{
		return;
	}

	AInspectableItem* Item = HeldItem.Get();
	Item->ResetTransform();
	Item->SetActorLocation(HeldItemOriginalLocation);

	HeldItem = nullptr;

	// Restore camera look in case the player was mid-drag when dropping.
	if (bWasIgnoringLook)
	{
		SetIgnoreLookInput(false);
		bWasIgnoringLook = false;
	}

	UE_LOG(LogTemp, Log, TEXT("Dropped held item."));
}

void ANPCPlayerController::TickHeldItem(float DeltaTime)
{
	if (!HeldItem.IsValid() || !PlayerCameraManager)
	{
		return;
	}

	AInspectableItem* Item = HeldItem.Get();

	// Sync item world location to camera + offset (forward / right / up in camera-local axes).
	const FVector CamLoc = PlayerCameraManager->GetCameraLocation();
	const FRotator CamRot = PlayerCameraManager->GetCameraRotation();
	const FRotationMatrix CamMatrix(CamRot);
	const FVector Forward = CamMatrix.GetUnitAxis(EAxis::X);
	const FVector Right = CamMatrix.GetUnitAxis(EAxis::Y);
	const FVector Up = CamMatrix.GetUnitAxis(EAxis::Z);

	const FVector HoldWorld = CamLoc
		+ Forward * HoldOffset.X
		+ Right * HoldOffset.Y
		+ Up * HoldOffset.Z;

	Item->SetActorLocation(HoldWorld);

	// Mouse drag (RMB held) -> rotate item on the horizontal axis only (yaw).
	// While RMB is held, the camera also stops responding to mouse-look so that
	// dragging only spins the item — the viewport stays fixed. SetIgnoreLookInput
	// uses an internal counter, so we toggle on state-change, not every frame.
	const bool bRMBHeldNow = IsInputKeyDown(EKeys::RightMouseButton);
	if (bRMBHeldNow != bWasIgnoringLook)
	{
		SetIgnoreLookInput(bRMBHeldNow);
		bWasIgnoringLook = bRMBHeldNow;
	}
	if (bRMBHeldNow)
	{
		float MouseDX = 0.0f, MouseDY = 0.0f;
		GetInputMouseDelta(MouseDX, MouseDY);
		if (!FMath::IsNearlyZero(MouseDX))
		{
			// Yaw only — strict horizontal axis. MouseDY is ignored intentionally.
			const FRotator Delta(0.0f, MouseDX * MouseRotationSensitivity, 0.0f);
			Item->ApplyRotation(Delta);
		}
	}

	// Scroll wheel -> scale item via spring-damper.
	if (WasInputKeyJustPressed(EKeys::MouseScrollUp))
	{
		Item->ApplyScale(ScrollScaleStep);
	}
	if (WasInputKeyJustPressed(EKeys::MouseScrollDown))
	{
		Item->ApplyScale(-ScrollScaleStep);
	}
}
