#include "NPCDialogueHUD.h"
#include "NPCCharacter.h"
#include "LLM_NPC/Dialogue/DialogueComponent.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "Engine/GameViewportClient.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SBorder.h"

void ANPCDialogueHUD::BeginPlay()
{
	Super::BeginPlay();

	// Find the first NPC and bind to its dialogue
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
				UE_LOG(LogTemp, Log, TEXT("NPCDialogueHUD: Bound to NPC DialogueComponent"));
				break;
			}
		}
	}

	BuildChatUI();
}

void ANPCDialogueHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (RootWidget.IsValid() && GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(RootWidget.ToSharedRef());
	}
	Super::EndPlay(EndPlayReason);
}

void ANPCDialogueHUD::BuildChatUI()
{
	if (bUIBuilt || !GEngine || !GEngine->GameViewport)
	{
		return;
	}

	// Build the chat panel with Slate
	SAssignNew(RootWidget, SVerticalBox)

	// Spacer pushes chat to bottom
	+ SVerticalBox::Slot()
	.FillHeight(1.0f)

	// Chat log
	+ SVerticalBox::Slot()
	.AutoHeight()
	.MaxHeight(250.0f)
	.Padding(20.0f, 0.0f)
	[
		SNew(SBorder)
		.BorderBackgroundColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.7f))
		.Padding(8.0f)
		[
			SAssignNew(ChatLog, SScrollBox)
		]
	]

	// Status text
	+ SVerticalBox::Slot()
	.AutoHeight()
	.Padding(20.0f, 4.0f)
	[
		SAssignNew(StatusText, STextBlock)
		.ColorAndOpacity(FSlateColor(FLinearColor(0.7f, 0.7f, 0.7f)))
		.Text(FText::FromString(TEXT("Press T to toggle chat. Type a message and press Enter.")))
	]

	// Input row
	+ SVerticalBox::Slot()
	.AutoHeight()
	.Padding(20.0f, 0.0f, 20.0f, 20.0f)
	[
		SNew(SHorizontalBox)

		+ SHorizontalBox::Slot()
		.FillWidth(1.0f)
		[
			SAssignNew(InputBox, SEditableTextBox)
			.HintText(FText::FromString(TEXT("Type a message to the NPC...")))
			.OnTextCommitted_Lambda([this](const FText& Text, ETextCommit::Type CommitType)
			{
				if (CommitType == ETextCommit::OnEnter)
				{
					SubmitText();
				}
			})
		]

		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(8.0f, 0.0f, 0.0f, 0.0f)
		[
			SNew(SButton)
			.Text(FText::FromString(TEXT("Send")))
			.OnClicked_Lambda([this]() -> FReply
			{
				SubmitText();
				return FReply::Handled();
			})
		]
	];

	// Add directly to the game viewport
	GEngine->GameViewport->AddViewportWidgetContent(
		SNew(SWeakWidget).PossiblyNullContent(RootWidget),
		10  // Z-order
	);

	bUIBuilt = true;

	// Add welcome message
	AddChatMessage(TEXT("System"), TEXT("Chat ready. Type a message and press Enter to talk to the NPC."), FLinearColor(0.5f, 0.5f, 0.5f));

	UE_LOG(LogTemp, Log, TEXT("NPCDialogueHUD: Chat UI built and added to viewport"));
}

void ANPCDialogueHUD::ToggleDialogueInput()
{
	bDialogueVisible = !bDialogueVisible;

	if (RootWidget.IsValid())
	{
		RootWidget->SetVisibility(bDialogueVisible ? EVisibility::Visible : EVisibility::Collapsed);
	}

	if (bDialogueVisible && InputBox.IsValid())
	{
		FSlateApplication::Get().SetKeyboardFocus(InputBox);
	}
}

void ANPCDialogueHUD::SubmitText()
{
	if (!InputBox.IsValid())
	{
		return;
	}

	FString UserText = InputBox->GetText().ToString().TrimStartAndEnd();
	if (UserText.IsEmpty())
	{
		return;
	}

	InputBox->SetText(FText::GetEmpty());
	AddChatMessage(TEXT("You"), UserText, FLinearColor(0.4f, 0.8f, 1.0f));

	if (BoundDialogue)
	{
		FDetectedUserEmotion DefaultEmotion;
		DefaultEmotion.Emotion = EEmotionType::Neutral;
		DefaultEmotion.Confidence = 0.0f;
		BoundDialogue->SendUserMessage(UserText, DefaultEmotion);

		if (StatusText.IsValid())
		{
			StatusText->SetText(FText::FromString(TEXT("Waiting for NPC response...")));
		}
	}
	else
	{
		AddChatMessage(TEXT("System"), TEXT("No NPC found. Make sure BP_NPC_Test is in the level with NPC Config assigned."), FLinearColor(1.0f, 0.3f, 0.3f));
	}
}

void ANPCDialogueHUD::AddChatMessage(const FString& Sender, const FString& Message, FLinearColor Color)
{
	if (!ChatLog.IsValid())
	{
		return;
	}

	ChatLog->AddSlot()
	.Padding(2.0f)
	[
		SNew(STextBlock)
		.Text(FText::FromString(FString::Printf(TEXT("[%s]: %s"), *Sender, *Message)))
		.ColorAndOpacity(FSlateColor(Color))
		.AutoWrapText(true)
	];

	ChatLog->ScrollToEnd();
}

void ANPCDialogueHUD::OnNPCResponse(const FString& ResponseText, EEmotionType NPCEmotionHint,
	bool bShouldGiveItem, FName ItemID)
{
	AddChatMessage(TEXT("NPC"), ResponseText, FLinearColor(0.2f, 1.0f, 0.4f));

	if (StatusText.IsValid())
	{
		StatusText->SetText(FText::FromString(TEXT("Press T to toggle chat. Type a message and press Enter.")));
	}

	if (bShouldGiveItem)
	{
		AddChatMessage(TEXT("System"), FString::Printf(TEXT("* NPC gives you: %s *"), *ItemID.ToString()), FLinearColor(1.0f, 0.8f, 0.2f));
	}
}
