#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NPCTypes.h"
#include "NPCAIController.generated.h"

class ANPCCharacter;

/**
 * Orchestrator AI controller for the NPC.
 * Routes input between subsystems, coordinates turn-taking,
 * and manages the dialogue loop:
 *   User input → assemble context → Claude API → process response → animate
 */
UCLASS()
class FLLM_NPC_API ANPCAIController : public AAIController
{
	GENERATED_BODY()

public:
	ANPCAIController();

	/** Process a user message (from voice STT or text input). */
	UFUNCTION(BlueprintCallable, Category = "NPC|Dialogue")
	void HandleUserInput(const FString& UserMessage, const FDetectedUserEmotion& UserEmotion);

	/** Called when Claude API returns a response. */
	void OnDialogueResponseReceived(const FString& ResponseText, EEmotionType NPCEmotionHint,
		bool bShouldGiveItem, FName ItemID);

	/** Called when user emotion is detected from camera. */
	void OnUserEmotionDetected(const FDetectedUserEmotion& DetectedEmotion);

	/** Called when a gesture is detected. */
	void OnGestureDetected(const FGestureInput& Gesture);

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY()
	TObjectPtr<ANPCCharacter> NPCCharacter;

	/** Whether the NPC is currently processing a dialogue turn. */
	bool bIsProcessingTurn = false;
};
