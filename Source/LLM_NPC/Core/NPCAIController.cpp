#include "NPCAIController.h"
#include "NPCCharacter.h"
#include "LLM_NPC/Dialogue/DialogueComponent.h"
#include "LLM_NPC/Emotion/EmotionComponent.h"
#include "LLM_NPC/Inventory/NPCInventoryComponent.h"

ANPCAIController::ANPCAIController()
{
}

void ANPCAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	NPCCharacter = Cast<ANPCCharacter>(InPawn);

	if (NPCCharacter)
	{
		UE_LOG(LogTemp, Log, TEXT("ANPCAIController possessed NPC: %s"), *NPCCharacter->GetName());
	}
}

void ANPCAIController::HandleUserInput(const FString& UserMessage, const FDetectedUserEmotion& UserEmotion)
{
	if (!NPCCharacter || bIsProcessingTurn)
	{
		return;
	}

	bIsProcessingTurn = true;

	// 1. Feed user emotion to the Emotion Engine
	if (NPCCharacter->EmotionComponent)
	{
		FEmotionSignal Signal;
		Signal.TargetEmotion = UserEmotion.Emotion;
		Signal.Strength = UserEmotion.Confidence;
		Signal.Source = TEXT("UserFacialExpression");
		NPCCharacter->EmotionComponent->ProcessSignal(Signal);
	}

	// 2. Send to Dialogue System which assembles context and calls Claude
	if (NPCCharacter->DialogueComponent)
	{
		NPCCharacter->DialogueComponent->SendUserMessage(UserMessage, UserEmotion);
	}
}

void ANPCAIController::OnDialogueResponseReceived(const FString& ResponseText, EEmotionType NPCEmotionHint,
	bool bShouldGiveItem, FName ItemID)
{
	if (!NPCCharacter)
	{
		bIsProcessingTurn = false;
		return;
	}

	// 1. Update NPC emotion based on Claude's hint
	if (NPCCharacter->EmotionComponent && NPCEmotionHint != EEmotionType::Neutral)
	{
		FEmotionSignal Signal;
		Signal.TargetEmotion = NPCEmotionHint;
		Signal.Strength = 0.7f;
		Signal.Source = TEXT("ClaudeEmotionHint");
		NPCCharacter->EmotionComponent->ProcessSignal(Signal);
	}

	// 2. Handle item giving
	if (bShouldGiveItem && NPCCharacter->InventoryComponent)
	{
		NPCCharacter->InventoryComponent->TryGiveItem(ItemID);
	}

	// 3. TTS will be triggered by the DialogueComponent after receiving response
	// 4. Metahuman animation is driven by EmotionComponent delegates

	bIsProcessingTurn = false;
}

void ANPCAIController::OnUserEmotionDetected(const FDetectedUserEmotion& DetectedEmotion)
{
	if (!NPCCharacter || !NPCCharacter->EmotionComponent)
	{
		return;
	}

	FEmotionSignal Signal;
	Signal.TargetEmotion = DetectedEmotion.Emotion;
	Signal.Strength = DetectedEmotion.Confidence * 0.5f; // Attenuate camera-based signals
	Signal.Source = TEXT("UserFacialExpression_Continuous");
	NPCCharacter->EmotionComponent->ProcessSignal(Signal);
}

void ANPCAIController::OnGestureDetected(const FGestureInput& Gesture)
{
	// Gesture handling is routed directly to the ObjectInspectWidget
	// through the GestureRecognitionComponent's delegates.
	// This method exists for any controller-level gesture logic if needed.
}
