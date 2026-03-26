#include "NPCDialogueOverlay.h"
#include "LLM_NPC/Dialogue/DialogueComponent.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "LLM_NPC/Core/NPCCharacter.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

TSharedRef<SWidget> UNPCDialogueOverlay::RebuildWidget()
{
	RootBox = SNew(SVerticalBox);

	// Chat log area (top, takes all available space)
	RootBox->AddSlot()
	.FillHeight(1.0f)
	.Padding(10.0f)
	[
		SNew(SBorder)
		.BorderBackgroundColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.6f))
		.Padding(8.0f)
		.Visibility_Lambda([this]() { return bInputVisible ? EVisibility::Visible : EVisibility::Collapsed; })
		[
			SAssignNew(ChatScrollBox, SScrollBox)
		]
	];

	// Status text
	RootBox->AddSlot()
	.AutoHeight()
	.Padding(10.0f, 0.0f, 10.0f, 2.0f)
	[
		SAssignNew(StatusText, STextBlock)
		.ColorAndOpacity(FSlateColor(FLinearColor(0.7f, 0.7f, 0.7f, 1.0f)))
		.Visibility_Lambda([this]() { return bInputVisible ? EVisibility::Visible : EVisibility::Collapsed; })
	];

	// Input row (bottom)
	TSharedPtr<SHorizontalBox> InputRow;
	RootBox->AddSlot()
	.AutoHeight()
	.Padding(10.0f, 2.0f, 10.0f, 10.0f)
	[
		SNew(SBox)
		.HeightOverride(40.0f)
		.Visibility_Lambda([this]() { return bInputVisible ? EVisibility::Visible : EVisibility::Collapsed; })
		[
			SAssignNew(InputRow, SHorizontalBox)

			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			[
				SAssignNew(InputTextBox, SEditableTextBox)
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
			.Padding(4.0f, 0.0f, 0.0f, 0.0f)
			[
				SNew(SButton)
				.Text(FText::FromString(TEXT("Send")))
				.OnClicked_Lambda([this]() -> FReply
				{
					SubmitText();
					return FReply::Handled();
				})
			]
		]
	];

	// Hint text (always visible)
	RootBox->AddSlot()
	.AutoHeight()
	.HAlign(HAlign_Center)
	.Padding(0.0f, 0.0f, 0.0f, 5.0f)
	[
		SNew(STextBlock)
		.Text(FText::FromString(TEXT("Press T to toggle dialogue")))
		.ColorAndOpacity(FSlateColor(FLinearColor(0.5f, 0.5f, 0.5f, 0.7f)))
	];

	return RootBox.ToSharedRef();
}

void UNPCDialogueOverlay::NativeConstruct()
{
	Super::NativeConstruct();

	// Auto-find the first NPCCharacter in the world and bind to its DialogueComponent
	if (GetWorld())
	{
		TArray<AActor*> NPCActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANPCCharacter::StaticClass(), NPCActors);

		for (AActor* Actor : NPCActors)
		{
			if (ANPCCharacter* NPC = Cast<ANPCCharacter>(Actor))
			{
				if (NPC->DialogueComponent)
				{
					BindToNPC(NPC->DialogueComponent);
					break;
				}
			}
		}
	}
}

void UNPCDialogueOverlay::ToggleInput()
{
	bInputVisible = !bInputVisible;

	if (bInputVisible && InputTextBox.IsValid())
	{
		FSlateApplication::Get().SetKeyboardFocus(InputTextBox);
	}
}

void UNPCDialogueOverlay::AddChatMessage(const FString& Sender, const FString& Message, FLinearColor Color)
{
	if (!ChatScrollBox.IsValid())
	{
		return;
	}

	FString FormattedMsg = FString::Printf(TEXT("[%s]: %s"), *Sender, *Message);

	ChatScrollBox->AddSlot()
	.Padding(2.0f)
	[
		SNew(STextBlock)
		.Text(FText::FromString(FormattedMsg))
		.ColorAndOpacity(FSlateColor(Color))
		.AutoWrapText(true)
	];

	// Scroll to bottom
	ChatScrollBox->ScrollToEnd();
}

void UNPCDialogueOverlay::SetStatus(const FString& InStatusText)
{
	if (StatusText.IsValid())
	{
		StatusText->SetText(FText::FromString(InStatusText));
	}
}

void UNPCDialogueOverlay::BindToNPC(UDialogueComponent* InDialogueComp)
{
	BoundDialogueComp = InDialogueComp;

	if (BoundDialogueComp)
	{
		BoundDialogueComp->OnDialogueResponseReceived.AddDynamic(this, &UNPCDialogueOverlay::OnNPCResponse);
		UE_LOG(LogTemp, Log, TEXT("DialogueOverlay: Bound to NPC DialogueComponent"));
	}
}

void UNPCDialogueOverlay::SubmitText()
{
	if (!InputTextBox.IsValid() || !BoundDialogueComp)
	{
		if (!BoundDialogueComp)
		{
			AddChatMessage(TEXT("System"), TEXT("No NPC found to talk to. Make sure BP_NPC_Test has NPC Config assigned."), FLinearColor::Red);
		}
		return;
	}

	FString UserText = InputTextBox->GetText().ToString().TrimStartAndEnd();
	if (UserText.IsEmpty())
	{
		return;
	}

	// Clear input
	InputTextBox->SetText(FText::GetEmpty());

	// Show user message in chat
	AddChatMessage(TEXT("You"), UserText, FLinearColor(0.4f, 0.8f, 1.0f));
	SetStatus(TEXT("Waiting for NPC response..."));

	// Send to NPC dialogue system
	FDetectedUserEmotion DefaultEmotion;
	DefaultEmotion.Emotion = EEmotionType::Neutral;
	DefaultEmotion.Confidence = 0.0f;
	BoundDialogueComp->SendUserMessage(UserText, DefaultEmotion);
}

void UNPCDialogueOverlay::OnNPCResponse(const FString& ResponseText, EEmotionType NPCEmotionHint,
	bool bShouldGiveItem, FName ItemID)
{
	// Show NPC response in chat
	AddChatMessage(TEXT("NPC"), ResponseText, FLinearColor(0.2f, 1.0f, 0.4f));
	SetStatus(TEXT(""));

	if (bShouldGiveItem)
	{
		FString ItemMsg = FString::Printf(TEXT("* NPC gives you: %s *"), *ItemID.ToString());
		AddChatMessage(TEXT("System"), ItemMsg, FLinearColor(1.0f, 0.8f, 0.2f));
	}
}
