#pragma once

#include "CoreMinimal.h"
#include "LLM_NPC/Core/NPCSubsystemComponent.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "DialogueComponent.generated.h"

class UClaudeAPISubsystem;
class UNPCConfigDataAsset;
class UNPCGraphDataAsset;
struct FNPCGraphNode;
struct FClaudeAPIResponse;

/** Delegate fired when a dialogue response is received from Claude. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(
	FOnDialogueResponseReceived,
	const FString&, ResponseText,
	EEmotionType, NPCEmotionHint,
	bool, bShouldGiveItem,
	FName, ItemID
);

/** Delegate fired when the dialogue history is cleared. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueHistoryCleared);

/**
 * Manages dialogue state for a single NPC.
 *
 * Maintains conversation history, assembles context (system prompt + emotion annotations),
 * and routes messages through the ClaudeAPISubsystem. Each NPC actor gets its own
 * DialogueComponent instance.
 */
UCLASS(ClassGroup = (LLMNPC), meta = (BlueprintSpawnableComponent))
class LLM_NPC_API UDialogueComponent : public UNPCSubsystemComponent
{
	GENERATED_BODY()

public:
	UDialogueComponent();

	// --- UNPCSubsystemComponent Interface ---
	virtual void InitializeSubsystem() override;
	virtual void ShutdownSubsystem() override;
	virtual bool IsSubsystemAvailable() const override;

	/**
	 * Send a user message to the NPC, including detected user emotion context.
	 * Assembles the full conversation context and routes through ClaudeAPISubsystem.
	 *
	 * @param UserMessage    The player's text input.
	 * @param UserEmotion    Detected emotion from the player (facial recognition or default).
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Dialogue")
	void SendUserMessage(const FString& UserMessage, const FDetectedUserEmotion& UserEmotion);

	/** Clear all conversation history. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Dialogue")
	void ClearConversationHistory();

	/** Get the current conversation history. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Dialogue")
	const TArray<FNPCMessage>& GetConversationHistory() const { return ConversationHistory; }

	/** Get the number of messages in history. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Dialogue")
	int32 GetConversationLength() const { return ConversationHistory.Num(); }

	/** Whether the NPC is currently waiting for a Claude response. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Dialogue")
	bool IsWaitingForResponse() const { return bWaitingForResponse; }

	/** Fired when a dialogue response is received. */
	UPROPERTY(BlueprintAssignable, Category = "NPC|Dialogue")
	FOnDialogueResponseReceived OnDialogueResponseReceived;

	/** Fired when conversation history is cleared. */
	UPROPERTY(BlueprintAssignable, Category = "NPC|Dialogue")
	FOnDialogueHistoryCleared OnDialogueHistoryCleared;

	/** The NPC configuration data asset providing system prompt and model settings. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Dialogue")
	TObjectPtr<UNPCConfigDataAsset> NPCConfig;

	/**
	 * NPCID of this NPC's node in the active UNPCGraphDataAsset.
	 * Set by ANPCGameMode::BeginPlay() before InitializeSubsystem() when using graph-driven prompts.
	 * Falls back to name-matching against NPCConfig->NPCName if not set.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Dialogue")
	FName GraphNodeID;

protected:
	virtual void BeginPlay() override;

private:
	/** Callback when Claude API responds. */
	UFUNCTION()
	void OnClaudeResponseReceived(const FClaudeAPIResponse& Response);

	/**
	 * Assemble a full system prompt from graph data for a specific NPC node.
	 * Called by SendUserMessage() when NPCConfig->GraphDataAsset is valid.
	 * Falls back to NPCConfig->SystemPrompt if graph is not available.
	 */
	FString BuildSystemPromptFromGraph(const UNPCGraphDataAsset* Graph, const FNPCGraphNode& Node) const;

	/**
	 * Build the annotated user message content.
	 * Prepends gesture annotation (if any), then emotion annotation (if confidence >= 0.3),
	 * then the raw user message. Phase 3 will pass the real GestureIntent from NPCPlayerController;
	 * Phase 2 always passes EGestureIntent::None.
	 */
	FString BuildAnnotatedContent(const FString& UserMessage, const FDetectedUserEmotion& UserEmotion, EGestureIntent GestureIntent) const;

	/** Build a user emotion annotation string for the system context. */
	FString BuildEmotionAnnotation(const FDetectedUserEmotion& UserEmotion) const;

	/** Trim conversation history to the configured maximum. */
	void TrimConversationHistory();

	/** Conversation history for this NPC. */
	UPROPERTY()
	TArray<FNPCMessage> ConversationHistory;

	/** Whether we are currently waiting for a response. */
	bool bWaitingForResponse = false;

	/** Cached reference to the ClaudeAPISubsystem. */
	UPROPERTY()
	TObjectPtr<UClaudeAPISubsystem> CachedClaudeSubsystem;
};
