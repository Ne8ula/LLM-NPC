#include "NPCDialogueHUD.h"
#include "NPCCharacter.h"
#include "LLM_NPC/Dialogue/DialogueComponent.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"
#include "Kismet/GameplayStatics.h"

void ANPCDialogueHUD::BeginPlay()
{
	Super::BeginPlay();

	// Find NPC and bind
	TArray<AActor*> NPCActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANPCCharacter::StaticClass(), NPCActors);
	for (AActor* Actor : NPCActors)
	{
		if (ANPCCharacter* NPC = Cast<ANPCCharacter>(Actor))
		{
			if (NPC->DialogueComponent)
			{
				BoundDialogue = NPC->DialogueComponent;
				BoundDialogue->OnDialogueResponseReceived.AddDynamic(this, &ANPCDialogueHUD::OnNPCResponse);
				UE_LOG(LogTemp, Log, TEXT("NPCDialogueHUD: Bound to NPC"));
				break;
			}
		}
	}

	ChatLines.Add({TEXT("[System]: Chat ready. Type a message and press Enter to talk."), FLinearColor(0.5f, 0.5f, 0.5f)});
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

	// ---- Draw chat background ----
	const float ChatTop = ScreenH - ChatAreaHeight - InputBoxHeight - Padding * 3;
	FCanvasTileItem BG(
		FVector2D(Padding, ChatTop),
		FVector2D(ScreenW - Padding * 2, ChatAreaHeight + InputBoxHeight + Padding * 2),
		FLinearColor(0.0f, 0.0f, 0.0f, 0.7f)
	);
	BG.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(BG);

	// ---- Draw chat lines ----
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

	// ---- Draw status text ----
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

	// ---- Draw input box ----
	float InputY = StatusY + LineHeight + 5.0f;
	{
		// Input background
		FCanvasTileItem InputBG(
			FVector2D(Padding + 10.0f, InputY),
			FVector2D(ScreenW - Padding * 2 - 20.0f, InputBoxHeight),
			FLinearColor(0.15f, 0.15f, 0.15f, 0.9f)
		);
		InputBG.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(InputBG);

		// Input text with cursor
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
		ChatLines.Add({TEXT("[System]: No NPC found. Place BP_NPC_Test with NPC Config assigned."), FLinearColor(1.0f, 0.3f, 0.3f)});
	}
}

void ANPCDialogueHUD::OnNPCResponse(const FString& ResponseText, EEmotionType NPCEmotionHint,
	bool bShouldGiveItem, FName ItemID)
{
	ChatLines.Add({FString::Printf(TEXT("[NPC]: %s"), *ResponseText), FLinearColor(0.2f, 1.0f, 0.4f)});
	StatusMessage = TEXT("Type a message and press Enter.");

	if (bShouldGiveItem)
	{
		ChatLines.Add({FString::Printf(TEXT("[System]: * NPC gives you: %s *"), *ItemID.ToString()), FLinearColor(1.0f, 0.8f, 0.2f)});
	}
}
