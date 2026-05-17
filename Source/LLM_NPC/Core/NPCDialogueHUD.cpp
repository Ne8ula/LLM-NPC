#include "NPCDialogueHUD.h"
#include "NPCCharacter.h"
#include "NPCConfigDataAsset.h"
#include "NPCPlayerController.h"
#include "LLM_NPC/Dialogue/DialogueComponent.h"
#include "LLM_NPC/Dialogue/ElevenLabsTTSComponent.h"
#include "LLM_NPC/Dialogue/WhisperSTTComponent.h"
#include "LLM_NPC/Emotion/EmotionComponent.h"
#include "LLM_NPC/Gesture/InspectableItem.h"
#include "LLM_NPC/Vision/FacialRecognitionComponent.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Archive instrument palette (matrix-green phosphor on near-black).
// Body content (chat text, NPC name, last line) stays high-contrast white-ish so
// the script reads cleanly; ALL framing/labels/numerals are phosphor-green.
static const FLinearColor cPhosphor      (0.20f, 0.98f, 0.45f, 1.00f);  // primary green
static const FLinearColor cPhosphorDim   (0.10f, 0.62f, 0.28f, 1.00f);  // dim labels
static const FLinearColor cPhosphorBright(0.40f, 1.00f, 0.55f, 1.00f);  // active state
static const FLinearColor cPanelBG       (0.00f, 0.04f, 0.02f, 0.86f);  // panel bg
static const FLinearColor cPanelBorder   (0.10f, 0.55f, 0.24f, 1.00f);  // bevel/edge
static const FLinearColor cContent       (0.92f, 0.96f, 0.92f, 1.00f);  // body text
static const FLinearColor cContentDim    (0.55f, 0.66f, 0.58f, 1.00f);  // hint text
static const FLinearColor cWarn          (1.00f, 0.65f, 0.20f, 1.00f);  // amber accent
static const FLinearColor cAlert         (1.00f, 0.32f, 0.32f, 1.00f);  // alert/REC

// Global UI scale — bump every panel, padding, line height, and font scale uniformly.
// Single source of truth so HandleMouseClick stays in sync with DrawHUD geometry.
static const float UIScale = 1.20f;

// Chat line colors (player + NPC + system)
static const FLinearColor ColSystem (cPhosphorDim);
static const FLinearColor ColFocus  (cPhosphor);
static const FLinearColor ColPlayer (0.85f, 0.95f, 1.00f, 1.00f);  // visitor lines: cool white
static const FLinearColor ColNPC    (cContent);                    // Friend's lines: warm white
static const FLinearColor ColError  (cAlert);
static const FLinearColor ColGold   (cWarn);

void ANPCDialogueHUD::BeginPlay()
{
	Super::BeginPlay();

	ChatLines.Add({TEXT("[archive] link established. type T or step closer to begin."), ColSystem});

	// Demo instrumentation: count inspectable items in the level so the archive bar
	// can render "INSPECTED N/M" without hardcoding a 7. Done once at BeginPlay; the
	// level layout is static during a session.
	{
		TArray<AActor*> Items;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInspectableItem::StaticClass(), Items);
		TotalInspectableItems = Items.Num();
	}

	// Bind to first NPC in world as initial focus.
	// NPCPlayerController::UpdateNPCFocus() takes over proximity tracking on its first tick.
	TArray<AActor*> NPCActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANPCCharacter::StaticClass(), NPCActors);
	for (AActor* Actor : NPCActors)
	{
		if (ANPCCharacter* NPC = Cast<ANPCCharacter>(Actor))
		{
			SetFocusedNPC(NPC);
			break;
		}
	}
}

void ANPCDialogueHUD::SetFocusedNPC(ANPCCharacter* NPC)
{
	if (NPC == FocusedNPCActor)
	{
		return;
	}

	if (BoundDialogue)
	{
		BoundDialogue->OnDialogueResponseReceived.RemoveDynamic(this, &ANPCDialogueHUD::OnNPCResponse);
		BoundDialogue->OnBranchResolved.RemoveDynamic(this, &ANPCDialogueHUD::OnArchiveBranchResolved);
		BoundDialogue = nullptr;
	}
	if (BoundSTT)
	{
		BoundSTT->OnTranscriptReady.RemoveDynamic(this, &ANPCDialogueHUD::OnVoiceTranscript);
		BoundSTT = nullptr;
	}
	if (BoundFacialRec)
	{
		BoundFacialRec->OnUserEmotionDetected.RemoveDynamic(this, &ANPCDialogueHUD::OnUserEmotionDetected);
		BoundFacialRec = nullptr;
	}
	if (BoundTTS)
	{
		BoundTTS->OnSpeechFinished.RemoveDynamic(this, &ANPCDialogueHUD::OnFriendSpeechFinished);
		BoundTTS = nullptr;
	}

	FocusedNPCActor = NPC;
	FocusedNPCName.Empty();
	bIsVoiceRecording = false;
	bTextInputActive = false;

	if (!IsValid(NPC))
	{
		StatusMessage = TEXT("idle");
		return;
	}

	if (NPC->DialogueComponent)
	{
		BoundDialogue = NPC->DialogueComponent;
		BoundDialogue->OnDialogueResponseReceived.AddDynamic(this, &ANPCDialogueHUD::OnNPCResponse);
		BoundDialogue->OnBranchResolved.AddDynamic(this, &ANPCDialogueHUD::OnArchiveBranchResolved);
		UE_LOG(LogTemp, Log, TEXT("NPCDialogueHUD: Bound to DialogueComponent of %s"), *NPC->GetName());
	}
	if (NPC->WhisperSTTComponent)
	{
		BoundSTT = NPC->WhisperSTTComponent;
		BoundSTT->OnTranscriptReady.AddDynamic(this, &ANPCDialogueHUD::OnVoiceTranscript);
	}
	if (NPC->FacialRecognitionComponent)
	{
		BoundFacialRec = NPC->FacialRecognitionComponent;
		BoundFacialRec->OnUserEmotionDetected.AddDynamic(this, &ANPCDialogueHUD::OnUserEmotionDetected);
	}
	if (NPC->ElevenLabsTTSComponent)
	{
		BoundTTS = NPC->ElevenLabsTTSComponent;
		BoundTTS->OnSpeechFinished.AddDynamic(this, &ANPCDialogueHUD::OnFriendSpeechFinished);
	}

	FocusedNPCName = (NPC->NPCConfig && !NPC->NPCConfig->NPCName.IsEmpty())
		? NPC->NPCConfig->NPCName.ToString()
		: NPC->GetName();

	StatusMessage = TEXT("idle");
	ChatLines.Add({FString::Printf(TEXT("[archive] subject in range: %s"), *FocusedNPCName), ColFocus});
}

void ANPCDialogueHUD::DrawHUD()
{
	Super::DrawHUD();

	if (!Canvas)
	{
		return;
	}

	UFont* Font = GEngine->GetSmallFont();
	if (!Font)
	{
		return;
	}

	// Draw helpers shared across the closing card and the live HUD.
	auto Rect = [&](float X, float Y, float W, float H, FLinearColor C)
	{
		FCanvasTileItem Item(FVector2D(X, Y), FVector2D(W, H), C);
		Item.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(Item);
	};
	auto Txt = [&](const FString& S, float X, float Y, FLinearColor C, float Sc = 1.10f)
	{
		FCanvasTextItem Item(FVector2D(X, Y), FText::FromString(S), Font, C);
		Item.Scale = FVector2D(Sc * UIScale, Sc * UIScale);
		Canvas->DrawItem(Item);
	};
	auto Clip = [](const FString& S, int32 Max) -> FString
	{
		return S.Len() > Max ? S.Left(Max - 1) + TEXT("…") : S;
	};
	auto FramedPanel = [&](float X, float Y, float W, float H)
	{
		Rect(X, Y, W, H, cPanelBG);
		Rect(X,         Y,         W, 1.0f, cPanelBorder);
		Rect(X,         Y + H - 1, W, 1.0f, cPanelBorder);
		Rect(X,         Y,         1.0f, H, cPanelBorder);
		Rect(X + W - 1, Y,         1.0f, H, cPanelBorder);
	};
	auto EmotionLabel = [](EEmotionType E) -> const TCHAR*
	{
		switch (E)
		{
		case EEmotionType::Joy:           return TEXT("JOY");
		case EEmotionType::Sadness:       return TEXT("SADNESS");
		case EEmotionType::Anger:         return TEXT("ANGER");
		case EEmotionType::Fear:          return TEXT("FEAR");
		case EEmotionType::Surprise:      return TEXT("SURPRISE");
		case EEmotionType::Disgust:       return TEXT("DISGUST");
		case EEmotionType::Trust:         return TEXT("TRUST");
		case EEmotionType::Anticipation:  return TEXT("ANTICIPATION");
		default:                          return TEXT("NEUTRAL");
		}
	};

	// Tier 3 closing card. Drawn over everything else and is the only thing on
	// screen when the session resolves; we suppress all other HUD while it's up.
	if (bClosingCardActive)
	{
		const float ScreenW = Canvas->SizeX;
		const float ScreenHF = Canvas->SizeY;

		const float Now = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
		const float Elapsed = Now - ClosingCardStartTime;
		const float FadeIn = FMath::Clamp(Elapsed / 0.5f, 0.0f, 1.0f);
		const float Alpha = FadeIn;

		Rect(0.0f, 0.0f, ScreenW, ScreenHF, FLinearColor(0.0f, 0.02f, 0.01f, 0.94f * Alpha));

		const float CenterY = ScreenHF * 0.40f;
		const FLinearColor cLine    (0.92f, 0.96f, 0.92f, Alpha);
		const FLinearColor cProvoke (cPhosphor.R, cPhosphor.G, cPhosphor.B, Alpha);
		const FLinearColor cBranch  (cPhosphorDim.R, cPhosphorDim.G, cPhosphorDim.B, Alpha);

		const FString Line = ClosingCardLine.IsEmpty() ? TEXT("(silence)") : ClosingCardLine;
		Txt(FString::Printf(TEXT("“%s”"), *Line),
			ScreenW * 0.10f, CenterY, cLine, 1.6f);

		const FString Provocation =
			TEXT("When the model of a witness withdraws consent, what testimony remains?");
		Txt(Provocation, ScreenW * 0.10f, CenterY + 80.0f * UIScale, cProvoke, 1.15f);

		const TCHAR* BranchLabel =
			ClosingCardBranch == EArchiveBranch::ConvergentSpecific ? TEXT("[ BRANCH: CONVERGENT DISCLOSURE — DESTINATION DISCLOSED ]") :
			ClosingCardBranch == EArchiveBranch::Convergent         ? TEXT("[ BRANCH: CONVERGENT DISCLOSURE — DEPARTURE ONLY ]")        :
			ClosingCardBranch == EArchiveBranch::TimeOut            ? TEXT("[ BRANCH: RECURSIVE SILENCE — CONSENT REVOKED ]")           :
			                                                          TEXT("[ BRANCH: — ]");
		Txt(BranchLabel, ScreenW * 0.10f, CenterY + 130.0f * UIScale, cBranch, 1.05f);

		// Subtle subtitle for the tiered convergent branches: tells the audience
		// what specifically the Friend just disclosed, so the demo lands without
		// needing to re-watch the line.
		const TCHAR* Subtitle = nullptr;
		if (ClosingCardBranch == EArchiveBranch::ConvergentSpecific)
		{
			Subtitle = TEXT("She named the place. The visitor earned the full record.");
		}
		else if (ClosingCardBranch == EArchiveBranch::Convergent)
		{
			Subtitle = TEXT("She admitted the leaving. She kept the place for herself.");
		}
		else if (ClosingCardBranch == EArchiveBranch::TimeOut)
		{
			Subtitle = TEXT("The witness model declined to continue. The session is over.");
		}
		if (Subtitle)
		{
			Txt(Subtitle, ScreenW * 0.10f, CenterY + 158.0f * UIScale, cBranch, 0.95f);
		}
		return;
	}

	const float ScreenW = Canvas->SizeX;
	const float ScreenH = Canvas->SizeY;
	CachedScreenH = ScreenH;  // used by HandleMouseClick for hit-testing

	ANPCPlayerController* PC = Cast<ANPCPlayerController>(GetOwningPlayerController());

	// =====================================================================
	// (1) ARCHIVE TOP BAR — always visible. Reads the demo's vital signs.
	//   ARCHIVE LINK ACTIVE | SUBJECT ASHLEY WEI | T-MM:SS | TRUST 0.42
	//   | INSPECT 3/7 | PRESENT 1/7 | CLIMAX READY
	// =====================================================================
	{
		const float BarH = 28.0f * UIScale;
		FramedPanel(0.0f, 0.0f, ScreenW, BarH);

		float CursorX = 12.0f * UIScale;
		const float Y = 7.0f * UIScale;
		auto Sep = [&]()
		{
			Txt(TEXT("│"), CursorX, Y, cPanelBorder, 1.05f);
			CursorX += 12.0f * UIScale;
		};
		auto Seg = [&](const TCHAR* Label, const FString& Value, FLinearColor ValColor)
		{
			Txt(Label, CursorX, Y, cPhosphorDim, 1.05f);
			CursorX += static_cast<float>(FCString::Strlen(Label)) * 6.4f * UIScale + 4.0f * UIScale;
			Txt(Value, CursorX, Y, ValColor, 1.10f);
			CursorX += static_cast<float>(Value.Len()) * 7.4f * UIScale + 8.0f * UIScale;
			Sep();
		};

		Txt(TEXT("ARCHIVE LINK ACTIVE"), CursorX, Y, cPhosphorBright, 1.10f);
		CursorX += 158.0f * UIScale;
		Sep();

		Seg(TEXT("SUBJECT "), TEXT("ASHLEY WEI"), cContent);

		// Read session telemetry from the focused NPC's DialogueComponent.
		float Trust = 0.0f;
		float Remaining = 0.0f;
		bool bConvergentReady = false;
		bool bLocationReady = false;
		bool bTimeExpired = false;
		int32 InspectedDistinct = 0;
		int32 PresentedDistinct = 0;
		const FName SpeakerKey = UDialogueComponent::GetDefaultSpeakerID();
		if (BoundDialogue)
		{
			Trust = BoundDialogue->ComputeTrust();
			Remaining = BoundDialogue->GetSessionRemainingSeconds();
			bTimeExpired = (Remaining <= 0.0f) && (BoundDialogue->GetSessionElapsedSeconds() > 0.1f);
			for (const TPair<FName, TSet<FName>>& P : BoundDialogue->GetInspectedBy())
			{
				if (P.Value.Contains(SpeakerKey)) ++InspectedDistinct;
			}
			for (const TPair<FName, TSet<FName>>& P : BoundDialogue->GetPresentedBy())
			{
				if (P.Value.Contains(SpeakerKey)) ++PresentedDistinct;
			}
			bConvergentReady = (Trust >= BoundDialogue->ConvergentTrustThreshold);
			bLocationReady = (Trust >= BoundDialogue->LocationKeystoneTrustThreshold);
		}

		const int32 Mins = FMath::FloorToInt(Remaining / 60.0f);
		const int32 Secs = FMath::FloorToInt(Remaining) % 60;
		FLinearColor cTime = cPhosphor;
		if (Remaining < 30.0f) cTime = cWarn;
		if (Remaining <= 0.0f) cTime = cAlert;
		Seg(TEXT("T-"), FString::Printf(TEXT("%02d:%02d"), Mins, Secs), cTime);

		const FLinearColor cTrust = bConvergentReady ? cPhosphorBright : cPhosphor;
		Seg(TEXT("TRUST "), FString::Printf(TEXT("%.2f"), Trust), cTrust);

		Seg(TEXT("INSPECT "), FString::Printf(TEXT("%d/%d"), InspectedDistinct, TotalInspectableItems), cContent);
		Seg(TEXT("PRESENT "), FString::Printf(TEXT("%d/%d"), PresentedDistinct, TotalInspectableItems), cContent);

		const TCHAR* ClimaxState = TEXT("WAITING");
		FLinearColor cClimax = cPhosphorDim;
		if (bTimeExpired)             { ClimaxState = TEXT("TIMEOUT");       cClimax = cAlert; }
		else if (bLocationReady)      { ClimaxState = TEXT("READY+LOCATION"); cClimax = cPhosphorBright; }
		else if (bConvergentReady)    { ClimaxState = TEXT("READY");          cClimax = cPhosphorBright; }
		Txt(TEXT("ENDING "), CursorX, Y, cPhosphorDim, 1.05f);
		CursorX += 50.0f * UIScale;
		Txt(ClimaxState, CursorX, Y, cClimax, 1.10f);
	}

	// =====================================================================
	// (1.5) INPUT MODE CHIP — top-center. Shows whether the voice channel is
	// in Push-to-Talk (default), Proximity (P-toggle on), or actively recording.
	// Panel width is measured against the actual text each frame so the longest
	// mode label can't overflow the frame.
	// =====================================================================
	{
		const TCHAR* Mode = TEXT("PUSH-TO-TALK · HOLD V");
		FLinearColor cMode = cContentDim;
		if (PC)
		{
			if (PC->bProximityChatEnabled)
			{
				Mode = PC->bPushToTalkActive
					? TEXT("PROXIMITY · PTT OVERRIDE")    // shouldn't happen, but defensive
					: TEXT("PROXIMITY · P TO TOGGLE OFF");
				cMode = cPhosphorBright;
			}
			else if (PC->bPushToTalkActive)
			{
				Mode = TEXT("● REC — V HELD");
				cMode = cAlert;
			}
			else
			{
				Mode = TEXT("PUSH-TO-TALK · HOLD V · P FOR PROXIMITY");
				cMode = cContentDim;
			}
		}

		// Measure each string at its draw scale. Canvas::StrLen returns
		// unscaled pixel width via out-params; multiply by our text scale.
		const FString LabelStr = TEXT("[ INPUT ]");
		const float TextScale = 1.05f * UIScale;
		float LabelW = 0.0f, LabelH = 0.0f;
		float ValueW = 0.0f, ValueH = 0.0f;
		Canvas->StrLen(Font, LabelStr, LabelW, LabelH);
		Canvas->StrLen(Font, Mode, ValueW, ValueH);
		LabelW *= TextScale;
		ValueW *= TextScale;

		const float HPad = 10.0f * UIScale;
		const float Gap  = 10.0f * UIScale;
		const float PW = HPad * 2.0f + LabelW + Gap + ValueW;
		const float PH = 30.0f * UIScale;
		const float PX = (ScreenW - PW) * 0.5f;
		const float PY = 36.0f * UIScale;
		FramedPanel(PX, PY, PW, PH);

		Txt(LabelStr, PX + HPad, PY + 7.0f * UIScale, cPhosphor, 1.05f);
		Txt(Mode,     PX + HPad + LabelW + Gap, PY + 7.0f * UIScale, cMode, 1.05f);
	}

	// =====================================================================
	// (2) VISITOR PANEL — top-left. Speaker tag + their face-detected emotion.
	// =====================================================================
	{
		const float PX = 12.0f * UIScale;
		const float PY = 36.0f * UIScale;
		const float PW = 240.0f * UIScale;
		const float PH = 84.0f * UIScale;
		FramedPanel(PX, PY, PW, PH);

		Txt(TEXT("[ VISITOR ]"), PX + 8.0f * UIScale, PY + 6.0f * UIScale, cPhosphor, 1.05f);

		FString SpeakerLine = TEXT("UNIDENTIFIED");
		FLinearColor cSpeaker = cContentDim;
		if (PC && !PC->LastSpeakerTag.IsNone())
		{
			FString TagDisplay = PC->LastSpeakerTag.ToString().ToUpper();
			TagDisplay.ReplaceInline(TEXT("SPEAKER_"), TEXT("SPEAKER "));
			SpeakerLine = FString::Printf(TEXT("%s  ·  %.2f"),
				*TagDisplay, PC->LastSpeakerConfidence);
			cSpeaker = cContent;
		}
		Txt(SpeakerLine, PX + 8.0f * UIScale, PY + 24.0f * UIScale, cSpeaker, 1.05f);

		Txt(TEXT("EMOTION"), PX + 8.0f * UIScale, PY + 44.0f * UIScale, cPhosphorDim, 1.00f);
		Txt(EmotionLabel(LastUserEmotion.Emotion), PX + 70.0f * UIScale, PY + 44.0f * UIScale, cContent, 1.05f);

		Txt(TEXT("CONFIDENCE"), PX + 8.0f * UIScale, PY + 62.0f * UIScale, cPhosphorDim, 1.00f);
		Txt(FString::Printf(TEXT("%.2f"), LastUserEmotion.Confidence),
			PX + 86.0f * UIScale, PY + 62.0f * UIScale, cContent, 1.05f);
	}

	// =====================================================================
	// (3) FRIEND STATE PANEL — top-right. Her current emotion + intensity bar.
	// =====================================================================
	{
		const float PW = 280.0f * UIScale;
		const float PH = 84.0f * UIScale;
		const float PX = ScreenW - PW - 12.0f * UIScale;
		const float PY = 36.0f * UIScale;
		FramedPanel(PX, PY, PW, PH);

		const FString HeaderLine = FocusedNPCName.IsEmpty()
			? TEXT("[ TESTIMONY: — ]")
			: FString::Printf(TEXT("[ TESTIMONY: %s ]"), *FocusedNPCName.ToUpper());
		Txt(HeaderLine, PX + 8.0f * UIScale, PY + 6.0f * UIScale, cPhosphor, 1.05f);

		FEmotionState NPCState;
		NPCState.PrimaryEmotion = EEmotionType::Neutral;
		NPCState.Intensity = 0.0f;
		if (IsValid(FocusedNPCActor))
		{
			if (UEmotionComponent* EC = FocusedNPCActor->FindComponentByClass<UEmotionComponent>())
			{
				NPCState = EC->GetCurrentEmotionState();
			}
		}

		Txt(TEXT("EMOTION"), PX + 8.0f * UIScale, PY + 24.0f * UIScale, cPhosphorDim, 1.00f);
		Txt(EmotionLabel(NPCState.PrimaryEmotion), PX + 80.0f * UIScale, PY + 24.0f * UIScale, cContent, 1.05f);

		Txt(TEXT("INTENSITY"), PX + 8.0f * UIScale, PY + 42.0f * UIScale, cPhosphorDim, 1.00f);
		Txt(FString::Printf(TEXT("%.2f"), NPCState.Intensity),
			PX + 80.0f * UIScale, PY + 42.0f * UIScale, cContent, 1.05f);

		const float BarX = PX + 130.0f * UIScale;
		const float BarY = PY + 46.0f * UIScale;
		const float BarW = PW - (BarX - PX) - 12.0f * UIScale;
		const float BarH = 6.0f * UIScale;
		Rect(BarX, BarY, BarW, BarH, FLinearColor(0.02f, 0.10f, 0.05f, 1.0f));
		Rect(BarX, BarY,
			BarW * FMath::Clamp(NPCState.Intensity, 0.0f, 1.0f), BarH, cPhosphor);

		Txt(TEXT("PAD"), PX + 8.0f * UIScale, PY + 62.0f * UIScale, cPhosphorDim, 1.00f);
		Txt(FString::Printf(TEXT("%+0.2f / %+0.2f / %+0.2f"),
				NPCState.PAD.Pleasure, NPCState.PAD.Arousal, NPCState.PAD.Dominance),
			PX + 80.0f * UIScale, PY + 62.0f * UIScale, cContent, 1.05f);
	}

	// Below this line: chat panel renders only when the overlay is open.
	if (!bDialogueVisible)
	{
		return;
	}

	// Chat panel geometry
	const float PanelX  = 20.0f * UIScale;
	const float PanelW  = 420.0f * UIScale;
	const float LineH   = 21.0f * UIScale;
	const float Pad     = 10.0f * UIScale;
	const float HeaderH = 28.0f * UIScale;
	const float SepH    = 1.0f;
	const int32 MaxLines = 5;
	const float ChatH   = MaxLines * LineH + Pad;
	const float InputH  = 30.0f * UIScale;
	const float PanelH  = HeaderH + SepH + ChatH + SepH + InputH;
	const float PanelY  = ScreenH - PanelH - 20.0f * UIScale;

	const FLinearColor cInput(
		bTextInputActive ? 0.02f : 0.00f,
		bTextInputActive ? 0.10f : 0.05f,
		bTextInputActive ? 0.05f : 0.02f, 1.00f);

	FramedPanel(PanelX, PanelY, PanelW, PanelH);

	// Header
	Rect(PanelX + 1.0f, PanelY + 1.0f, PanelW - 2.0f, HeaderH - 1.0f,
		FLinearColor(0.00f, 0.06f, 0.03f, 1.00f));

	if (!FocusedNPCName.IsEmpty())
	{
		Txt(FString::Printf(TEXT(" ▸ %s"), *FocusedNPCName.ToUpper()),
			PanelX + 8.0f * UIScale, PanelY + 7.0f * UIScale, cPhosphorBright, 1.10f);
	}
	else
	{
		Txt(TEXT(" ▸ NO SUBJECT IN RANGE"),
			PanelX + 8.0f * UIScale, PanelY + 7.0f * UIScale, cContentDim, 1.05f);
	}

	// Chat lines
	const float ChatTop = PanelY + HeaderH;
	Rect(PanelX, ChatTop, PanelW, SepH, cPanelBorder);
	const int32 FirstLine = FMath::Max(0, ChatLines.Num() - MaxLines);
	float TY = ChatTop + SepH + Pad * 0.5f;
	for (int32 i = FirstLine; i < ChatLines.Num(); ++i)
	{
		Txt(Clip(ChatLines[i].Text, 56), PanelX + Pad, TY, ChatLines[i].Color, 1.08f);
		TY += LineH;
	}

	// Input bar
	const float InputTop = ChatTop + SepH + ChatH;
	Rect(PanelX, InputTop, PanelW, SepH, cPanelBorder);
	Rect(PanelX + 1.0f, InputTop + SepH, PanelW - 2.0f, InputH - 1.0f, cInput);
	const float TxtY = InputTop + SepH + 7.0f * UIScale;

	if (!BoundDialogue)
	{
		Txt(TEXT(" walk closer to a subject"), PanelX + Pad, TxtY, cContentDim, 1.05f);
	}
	else if (bIsVoiceRecording)
	{
		Txt(TEXT(" ● REC — speaking into archive"),
			PanelX + Pad, TxtY, cAlert, 1.08f);
	}
	else if (StatusMessage == TEXT("Waiting for NPC response..."))
	{
		Txt(TEXT(" … awaiting response"), PanelX + Pad, TxtY, cWarn, 1.08f);
	}
	else if (!InputBuffer.IsEmpty())
	{
		Txt(TEXT(" > ") + Clip(InputBuffer, 50) + TEXT("|"),
			PanelX + Pad, TxtY, cPhosphor, 1.08f);
	}
	else
	{
		const FString Placeholder = bTextInputActive
			? TEXT(" > _")
			: TEXT(" click to type  ·  speak freely when in range");
		Txt(Placeholder, PanelX + Pad, TxtY, cContentDim, 1.05f);
	}
}

void ANPCDialogueHUD::ToggleDialogueInput()
{
	// Once the closing card is up, the session is over — don't let T re-open chat.
	if (bClosingCardActive)
	{
		return;
	}
	bDialogueVisible = !bDialogueVisible;
	if (!bDialogueVisible)
	{
		bTextInputActive = false;
	}
}

void ANPCDialogueHUD::HandleMouseClick(float MouseX, float MouseY)
{
	if (!BoundDialogue || !bDialogueVisible || CachedScreenH <= 0.0f)
	{
		bTextInputActive = false;
		return;
	}

	// Mirror the geometry constants from DrawHUD
	const float PanelX  = 20.0f * UIScale;
	const float PanelW  = 420.0f * UIScale;
	const float HeaderH = 28.0f * UIScale;
	const float SepH    = 1.0f;
	const float ChatH   = (5 * 21.0f + 10.0f) * UIScale;  // MaxLines * LineH + Pad
	const float InputH  = 30.0f * UIScale;
	const float PanelH  = HeaderH + SepH + ChatH + SepH + InputH;
	const float PanelY  = CachedScreenH - PanelH - 20.0f * UIScale;

	const float InputBoxY = PanelY + HeaderH + SepH + ChatH + SepH;

	bTextInputActive =
		MouseX >= PanelX && MouseX <= PanelX + PanelW &&
		MouseY >= InputBoxY && MouseY <= InputBoxY + InputH;
}

void ANPCDialogueHUD::AppendToInput(const FString& Char)
{
	InputBuffer += Char;
}

void ANPCDialogueHUD::BackspaceInput()
{
	if (InputBuffer.Len() > 0)
	{
		InputBuffer = InputBuffer.Left(InputBuffer.Len() - 1);
	}
}

void ANPCDialogueHUD::SubmitChatMessage(const FString& Message)
{
	if (Message.IsEmpty())
	{
		return;
	}

	ChatLines.Add({FString::Printf(TEXT("[you]  %s"), *Message), ColPlayer});
	InputBuffer.Empty();
	StatusMessage = TEXT("Waiting for NPC response...");

	if (BoundDialogue)
	{
		FDetectedUserEmotion DefaultEmotion;
		DefaultEmotion.Emotion = EEmotionType::Neutral;
		DefaultEmotion.Confidence = 0.0f;

		// Pull the cached gesture intent, currently held item, and Tier 2
		// speaker tag from the owning controller and consume them for this
		// turn. Both Enter-submit and voice-transcript flows funnel through
		// here, so this is the single canonical consumption point.
		EGestureIntent Gesture = EGestureIntent::None;
		AInspectableItem* HeldItem = nullptr;
		FName SpeakerTag = NAME_None;
		if (ANPCPlayerController* PC = Cast<ANPCPlayerController>(GetOwningPlayerController()))
		{
			Gesture = PC->PendingGestureIntent;
			PC->PendingGestureIntent = EGestureIntent::None;
			HeldItem = PC->GetHeldItem();
			SpeakerTag = PC->PendingSpeakerTag;
			PC->PendingSpeakerTag = NAME_None;
		}

		BoundDialogue->SendUserMessage(Message, DefaultEmotion, Gesture, HeldItem, SpeakerTag);
	}
	else
	{
		ChatLines.Add({TEXT("[archive]  no subject in range."), ColError});
	}
}

void ANPCDialogueHUD::OnNPCResponse(const FString& ResponseText, EEmotionType NPCEmotionHint,
	bool bShouldGiveItem, FName ItemID)
{
	const FString Label = FocusedNPCName.IsEmpty() ? TEXT("subject") : FocusedNPCName;
	ChatLines.Add({FString::Printf(TEXT("[%s]  %s"), *Label, *ResponseText), ColNPC});
	StatusMessage = TEXT("idle");

	if (bShouldGiveItem)
	{
		ChatLines.Add({FString::Printf(TEXT("[item]  %s"), *ItemID.ToString()), ColGold});
	}
}

void ANPCDialogueHUD::OnVoiceTranscript(const FString& Transcript)
{
	UE_LOG(LogTemp, Log, TEXT("NPCDialogueHUD: Voice transcript: %s"), *Transcript);
	SubmitChatMessage(Transcript);
}

void ANPCDialogueHUD::OnArchiveBranchResolved(EArchiveBranch Branch, const FString& FinalLine)
{
	// Arm — do NOT activate yet. The closing card waits until the Friend's TTS line
	// finishes so the audience hears her line in full before the overlay covers the
	// scene. OnFriendSpeechFinished activates; the watchdog timer is a fallback in
	// case the engine never fires that delegate (USoundWaveProcedural's drain isn't
	// fully reliable per existing code comments).
	bClosingCardArmed = true;
	ClosingCardLine = FinalLine;
	ClosingCardBranch = Branch;
	bDialogueVisible = false;
	bTextInputActive = false;

	// Generous watchdog — pick max plausible TTS length for a 1-2 sentence line at
	// Eleven v3's pace, plus a few seconds of cushion.
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(ClosingCardWatchdogTimer);
		World->GetTimerManager().SetTimer(
			ClosingCardWatchdogTimer, this,
			&ANPCDialogueHUD::OnClosingCardWatchdog,
			16.0f, /*bLoop=*/false);
	}

	UE_LOG(LogTemp, Log, TEXT("NPCDialogueHUD: closing card ARMED (branch=%d). Awaiting TTS finish."),
		static_cast<int32>(Branch));
}

void ANPCDialogueHUD::OnFriendSpeechFinished()
{
	if (bClosingCardArmed && !bClosingCardActive)
	{
		ActivateClosingCard();
	}
}

void ANPCDialogueHUD::OnClosingCardWatchdog()
{
	if (bClosingCardArmed && !bClosingCardActive)
	{
		UE_LOG(LogTemp, Warning, TEXT("NPCDialogueHUD: closing-card watchdog fired — TTS finished delegate never arrived. Activating card."));
		ActivateClosingCard();
	}
}

void ANPCDialogueHUD::ActivateClosingCard()
{
	bClosingCardActive = true;
	ClosingCardStartTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(ClosingCardWatchdogTimer);
	}
	UE_LOG(LogTemp, Log, TEXT("NPCDialogueHUD: closing card ACTIVE."));
}

void ANPCDialogueHUD::OnUserEmotionDetected(FDetectedUserEmotion DetectedEmotion)
{
	// Latch the latest non-trivial reading so the Visitor panel always shows
	// something stable. Confidence floor avoids flickering between Neutral
	// and a 0.05 false positive.
	if (DetectedEmotion.Confidence >= 0.20f)
	{
		LastUserEmotion = DetectedEmotion;
	}
}
