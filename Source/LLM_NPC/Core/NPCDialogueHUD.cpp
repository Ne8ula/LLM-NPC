#include "NPCDialogueHUD.h"
#include "NPCCharacter.h"
#include "NPCConfigDataAsset.h"
#include "LLM_NPC/Dialogue/DialogueComponent.h"
#include "LLM_NPC/Dialogue/WhisperSTTComponent.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"
#include "Kismet/GameplayStatics.h"

// Chat line colors — defined once, used in all Add() calls
static const FLinearColor ColSystem (0.38f, 0.38f, 0.46f, 1.0f);
static const FLinearColor ColFocus  (0.48f, 0.48f, 0.72f, 1.0f);
static const FLinearColor ColPlayer (0.45f, 0.82f, 1.00f, 1.0f);
static const FLinearColor ColNPC    (0.28f, 0.90f, 0.52f, 1.0f);
static const FLinearColor ColError  (1.00f, 0.35f, 0.35f, 1.0f);
static const FLinearColor ColGold   (1.00f, 0.80f, 0.30f, 1.0f);

void ANPCDialogueHUD::BeginPlay()
{
	Super::BeginPlay();

	ChatLines.Add({TEXT("[System]: Chat ready. Type or hold V to speak."), ColSystem});

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
		BoundDialogue = nullptr;
	}
	if (BoundSTT)
	{
		BoundSTT->OnTranscriptReady.RemoveDynamic(this, &ANPCDialogueHUD::OnVoiceTranscript);
		BoundSTT = nullptr;
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
		UE_LOG(LogTemp, Log, TEXT("NPCDialogueHUD: Bound to DialogueComponent of %s"), *NPC->GetName());
	}
	if (NPC->WhisperSTTComponent)
	{
		BoundSTT = NPC->WhisperSTTComponent;
		BoundSTT->OnTranscriptReady.AddDynamic(this, &ANPCDialogueHUD::OnVoiceTranscript);
	}

	FocusedNPCName = (NPC->NPCConfig && !NPC->NPCConfig->NPCName.IsEmpty())
		? NPC->NPCConfig->NPCName.ToString()
		: NPC->GetName();

	StatusMessage = TEXT("idle");
	ChatLines.Add({FString::Printf(TEXT("Now speaking with %s."), *FocusedNPCName), ColFocus});
}

void ANPCDialogueHUD::DrawHUD()
{
	Super::DrawHUD();

	if (!Canvas || !bDialogueVisible)
	{
		return;
	}

	UFont* Font = GEngine->GetSmallFont();
	if (!Font)
	{
		return;
	}

	const float ScreenH = Canvas->SizeY;
	CachedScreenH = ScreenH;  // used by HandleMouseClick for hit-testing

	// ── Panel geometry ───────────────────────────────────────
	const float PanelX  = 20.0f;
	const float PanelW  = 400.0f;
	const float LineH   = 21.0f;
	const float Pad     = 10.0f;
	const float HeaderH = 30.0f;
	const float SepH    = 1.0f;
	const int32 MaxLines = 5;
	const float ChatH   = MaxLines * LineH + Pad;
	const float InputH  = 32.0f;
	const float PanelH  = HeaderH + SepH + ChatH + SepH + InputH;
	const float PanelY  = ScreenH - PanelH - 20.0f;

	// ── Draw helpers ─────────────────────────────────────────
	auto Rect = [&](float X, float Y, float W, float H, FLinearColor C)
	{
		FCanvasTileItem Item(FVector2D(X, Y), FVector2D(W, H), C);
		Item.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(Item);
	};

	auto Txt = [&](const FString& S, float X, float Y, FLinearColor C, float Sc = 1.12f)
	{
		FCanvasTextItem Item(FVector2D(X, Y), FText::FromString(S), Font, C);
		Item.Scale = FVector2D(Sc, Sc);
		Canvas->DrawItem(Item);
	};

	auto Clip = [](const FString& S, int32 Max) -> FString
	{
		return S.Len() > Max ? S.Left(Max - 1) + TEXT("\u2026") : S;
	};

	// ── Color palette ────────────────────────────────────────
	const FLinearColor cBG    (0.04f, 0.04f, 0.07f, 0.92f);
	const FLinearColor cHead  (0.06f, 0.06f, 0.11f, 1.00f);
	const FLinearColor cSep   (0.14f, 0.14f, 0.22f, 1.00f);
	const FLinearColor cInput (bTextInputActive ? 0.09f : 0.05f,
	                           bTextInputActive ? 0.09f : 0.05f,
	                           bTextInputActive ? 0.14f : 0.09f, 1.00f);
	const FLinearColor cName  (0.90f, 0.90f, 0.96f, 1.00f);
	const FLinearColor cHint  (0.27f, 0.27f, 0.34f, 1.00f);
	const FLinearColor cCaret (0.72f, 0.72f, 0.80f, 1.00f);
	const FLinearColor cRec   (1.00f, 0.25f, 0.25f, 1.00f);
	const FLinearColor cWait  (0.50f, 0.50f, 0.60f, 1.00f);

	// ── Panel background ─────────────────────────────────────
	Rect(PanelX, PanelY, PanelW, PanelH, cBG);

	// ── Header ───────────────────────────────────────────────
	Rect(PanelX, PanelY, PanelW, HeaderH, cHead);

	if (!FocusedNPCName.IsEmpty())
	{
		Txt(FString::Printf(TEXT(" \u25CF  %s"), *FocusedNPCName),
			PanelX + 6.0f, PanelY + 7.0f, cName, 1.15f);
	}
	else
	{
		Txt(TEXT(" No one nearby"), PanelX + 6.0f, PanelY + 7.0f, cHint, 1.05f);
	}

	// ── Header / chat separator ───────────────────────────────
	const float ChatTop = PanelY + HeaderH;
	Rect(PanelX, ChatTop, PanelW, SepH, cSep);

	// ── Chat lines ────────────────────────────────────────────
	const int32 FirstLine = FMath::Max(0, ChatLines.Num() - MaxLines);
	float TY = ChatTop + SepH + Pad * 0.5f;
	for (int32 i = FirstLine; i < ChatLines.Num(); ++i)
	{
		Txt(Clip(ChatLines[i].Text, 54), PanelX + Pad, TY, ChatLines[i].Color, 1.10f);
		TY += LineH;
	}

	// ── Chat / input separator ────────────────────────────────
	const float InputTop = ChatTop + SepH + ChatH;
	Rect(PanelX, InputTop, PanelW, SepH, cSep);

	// ── Input bar ─────────────────────────────────────────────
	Rect(PanelX, InputTop + SepH, PanelW, InputH, cInput);
	const float TxtY = InputTop + SepH + 8.0f;

	if (!BoundDialogue)
	{
		Txt(TEXT(" Walk near someone"), PanelX + Pad, TxtY, cHint, 1.05f);
	}
	else if (bIsVoiceRecording)
	{
		Txt(TEXT(" \u25CF  REC  \u2014  release V to send"), PanelX + Pad, TxtY, cRec, 1.10f);
	}
	else if (StatusMessage == TEXT("Waiting for NPC response..."))
	{
		Txt(TEXT(" \u2026"), PanelX + Pad, TxtY, cWait, 1.20f);
	}
	else if (!InputBuffer.IsEmpty())
	{
		Txt(TEXT(" ") + Clip(InputBuffer, 50) + TEXT("|"), PanelX + Pad, TxtY, cCaret, 1.10f);
	}
	else
	{
		FString Placeholder = bTextInputActive
			? TEXT(" Type here...")
			: TEXT(" Click to type  \u00B7  hold V to speak");
		Txt(Placeholder, PanelX + Pad, TxtY, cHint, 1.05f);
	}
}

void ANPCDialogueHUD::ToggleDialogueInput()
{
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
	const float PanelX  = 20.0f;
	const float PanelW  = 400.0f;
	const float HeaderH = 30.0f;
	const float SepH    = 1.0f;
	const float ChatH   = 5 * 21.0f + 10.0f;  // MaxLines * LineH + Pad
	const float InputH  = 32.0f;
	const float PanelH  = HeaderH + SepH + ChatH + SepH + InputH;
	const float PanelY  = CachedScreenH - PanelH - 20.0f;

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

	ChatLines.Add({FString::Printf(TEXT("[You]  %s"), *Message), ColPlayer});
	InputBuffer.Empty();
	StatusMessage = TEXT("Waiting for NPC response...");

	if (BoundDialogue)
	{
		FDetectedUserEmotion DefaultEmotion;
		DefaultEmotion.Emotion = EEmotionType::Neutral;
		DefaultEmotion.Confidence = 0.0f;
		BoundDialogue->SendUserMessage(Message, DefaultEmotion);
	}
	else
	{
		ChatLines.Add({TEXT("[System]  No NPC in range."), ColError});
	}
}

void ANPCDialogueHUD::OnNPCResponse(const FString& ResponseText, EEmotionType NPCEmotionHint,
	bool bShouldGiveItem, FName ItemID)
{
	FString Label = FocusedNPCName.IsEmpty() ? TEXT("NPC") : FocusedNPCName;
	ChatLines.Add({FString::Printf(TEXT("[%s]  %s"), *Label, *ResponseText), ColNPC});
	StatusMessage = TEXT("idle");

	if (bShouldGiveItem)
	{
		ChatLines.Add({FString::Printf(TEXT("[Item]  %s"), *ItemID.ToString()), ColGold});
	}
}

void ANPCDialogueHUD::OnVoiceTranscript(const FString& Transcript)
{
	UE_LOG(LogTemp, Log, TEXT("NPCDialogueHUD: Voice transcript: %s"), *Transcript);
	SubmitChatMessage(Transcript);
}
