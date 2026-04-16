#include "NPCDialogueHUD.h"
#include "NPCCharacter.h"
#include "NPCConfigDataAsset.h"
#include "LLM_NPC/Dialogue/DialogueComponent.h"
#include "LLM_NPC/Dialogue/WhisperSTTComponent.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"
#include "Kismet/GameplayStatics.h"

void ANPCDialogueHUD::BeginPlay()
{
	Super::BeginPlay();

	ChatLines.Add({TEXT("[System]: Chat ready. Type or hold V to speak."), FLinearColor(0.5f, 0.5f, 0.5f)});

	// Bind to first NPC in world as initial focus.
	// NPCPlayerController::UpdateNPCFocus() will take over proximity tracking on its first tick.
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
	// No-op if already focused on this NPC
	if (NPC == FocusedNPCActor)
	{
		return;
	}

	// Unbind from old dialogue
	if (BoundDialogue)
	{
		BoundDialogue->OnDialogueResponseReceived.RemoveDynamic(this, &ANPCDialogueHUD::OnNPCResponse);
		BoundDialogue = nullptr;
	}

	// Unbind from old STT
	if (BoundSTT)
	{
		BoundSTT->OnTranscriptReady.RemoveDynamic(this, &ANPCDialogueHUD::OnVoiceTranscript);
		BoundSTT = nullptr;
	}

	FocusedNPCActor = NPC;
	FocusedNPCName.Empty();

	if (!IsValid(NPC))
	{
		StatusMessage = TEXT("Walk near an NPC to begin.");
		return;
	}

	// Bind new dialogue component
	if (NPC->DialogueComponent)
	{
		BoundDialogue = NPC->DialogueComponent;
		BoundDialogue->OnDialogueResponseReceived.AddDynamic(this, &ANPCDialogueHUD::OnNPCResponse);
		UE_LOG(LogTemp, Log, TEXT("NPCDialogueHUD: Bound to DialogueComponent of %s"), *NPC->GetName());
	}

	// Bind new STT component
	if (NPC->WhisperSTTComponent)
	{
		BoundSTT = NPC->WhisperSTTComponent;
		BoundSTT->OnTranscriptReady.AddDynamic(this, &ANPCDialogueHUD::OnVoiceTranscript);
	}

	// Resolve display name: prefer NPCConfig name, fall back to actor name
	FocusedNPCName = (NPC->NPCConfig && !NPC->NPCConfig->NPCName.IsEmpty())
		? NPC->NPCConfig->NPCName.ToString()
		: NPC->GetName();

	StatusMessage = TEXT("Type or hold V to speak.");
	ChatLines.Add({FString::Printf(TEXT("[System]: Now speaking with %s."), *FocusedNPCName),
		FLinearColor(0.5f, 0.5f, 0.8f)});
}

void ANPCDialogueHUD::DrawHUD()
{
	Super::DrawHUD();

	if (!Canvas || !bDialogueVisible)
	{
		return;
	}

	const float ScreenW = Canvas->SizeX;
	const float ScreenH = Canvas->SizeY;
	const float Padding = 20.0f;
	const float LineHeight = 22.0f;
	const float InputBoxHeight = 30.0f;
	const float ChatAreaHeight = FMath::Min(250.0f, ScreenH * 0.4f);

	UFont* Font = GEngine->GetSmallFont();
	if (!Font)
	{
		return;
	}

	const float ChatTop = ScreenH - ChatAreaHeight - InputBoxHeight - Padding * 3;

	// ---- NPC name label (above chat box) ----
	if (!FocusedNPCName.IsEmpty())
	{
		FCanvasTextItem NameItem(
			FVector2D(Padding + 10.0f, ChatTop - LineHeight - 4.0f),
			FText::FromString(FString::Printf(TEXT("— %s —"), *FocusedNPCName)),
			Font,
			FLinearColor(0.8f, 0.8f, 0.8f)
		);
		NameItem.Scale = FVector2D(1.3f, 1.3f);
		Canvas->DrawItem(NameItem);
	}

	// ---- Chat background ----
	FCanvasTileItem BG(
		FVector2D(Padding, ChatTop),
		FVector2D(ScreenW - Padding * 2, ChatAreaHeight + InputBoxHeight + Padding * 2),
		FLinearColor(0.0f, 0.0f, 0.0f, 0.7f)
	);
	BG.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(BG);

	// ---- Chat lines ----
	float Y = ChatTop + 10.0f;
	int32 StartLine = FMath::Max(0, ChatLines.Num() - (int32)(ChatAreaHeight / LineHeight));
	for (int32 i = StartLine; i < ChatLines.Num(); ++i)
	{
		FCanvasTextItem TextItem(
			FVector2D(Padding + 10.0f, Y),
			FText::FromString(ChatLines[i].Text),
			Font,
			ChatLines[i].Color
		);
		TextItem.Scale = FVector2D(1.2f, 1.2f);
		Canvas->DrawItem(TextItem);
		Y += LineHeight;

		if (Y > ChatTop + ChatAreaHeight)
		{
			break;
		}
	}

	// ---- Status text ----
	float StatusY = ChatTop + ChatAreaHeight + 5.0f;
	{
		FCanvasTextItem StatusItem(
			FVector2D(Padding + 10.0f, StatusY),
			FText::FromString(StatusMessage),
			Font,
			FLinearColor(0.6f, 0.6f, 0.6f)
		);
		StatusItem.Scale = FVector2D(1.0f, 1.0f);
		Canvas->DrawItem(StatusItem);
	}

	// ---- Input box (only when an NPC is focused) ----
	if (BoundDialogue)
	{
		float InputY = StatusY + LineHeight + 5.0f;

		FCanvasTileItem InputBG(
			FVector2D(Padding + 10.0f, InputY),
			FVector2D(ScreenW - Padding * 2 - 20.0f, InputBoxHeight),
			FLinearColor(0.15f, 0.15f, 0.15f, 0.9f)
		);
		InputBG.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(InputBG);

		FString DisplayText = InputBuffer.IsEmpty()
			? TEXT("Type here...")
			: InputBuffer + TEXT("|");

		FCanvasTextItem InputItem(
			FVector2D(Padding + 15.0f, InputY + 5.0f),
			FText::FromString(DisplayText),
			Font,
			InputBuffer.IsEmpty() ? FLinearColor(0.4f, 0.4f, 0.4f) : FLinearColor::White
		);
		InputItem.Scale = FVector2D(1.2f, 1.2f);
		Canvas->DrawItem(InputItem);
	}
}

void ANPCDialogueHUD::ToggleDialogueInput()
{
	bDialogueVisible = !bDialogueVisible;
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

	ChatLines.Add({FString::Printf(TEXT("[You]: %s"), *Message), FLinearColor(0.4f, 0.8f, 1.0f)});
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
		ChatLines.Add({TEXT("[System]: No NPC in range. Walk near an NPC to begin."),
			FLinearColor(1.0f, 0.3f, 0.3f)});
	}
}

void ANPCDialogueHUD::OnNPCResponse(const FString& ResponseText, EEmotionType NPCEmotionHint,
	bool bShouldGiveItem, FName ItemID)
{
	FString NPCLabel = FocusedNPCName.IsEmpty() ? TEXT("NPC") : FocusedNPCName;
	ChatLines.Add({FString::Printf(TEXT("[%s]: %s"), *NPCLabel, *ResponseText), FLinearColor(0.2f, 1.0f, 0.4f)});
	StatusMessage = TEXT("Type or hold V to speak.");

	if (bShouldGiveItem)
	{
		ChatLines.Add({FString::Printf(TEXT("[System]: * %s gives you: %s *"), *NPCLabel, *ItemID.ToString()),
			FLinearColor(1.0f, 0.8f, 0.2f)});
	}
}

void ANPCDialogueHUD::OnVoiceTranscript(const FString& Transcript)
{
	UE_LOG(LogTemp, Log, TEXT("NPCDialogueHUD: Voice transcript: %s"), *Transcript);
	SubmitChatMessage(Transcript);
}
