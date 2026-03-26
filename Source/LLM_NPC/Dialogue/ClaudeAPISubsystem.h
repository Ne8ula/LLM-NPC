#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "ClaudeAPISubsystem.generated.h"

class FHttpModule;
class IHttpRequest;
class IHttpResponse;

/**
 * Parsed response from the Claude API.
 * Includes the NPC's dialogue text plus structured metadata for emotion and item triggers.
 */
USTRUCT(BlueprintType)
struct LLM_NPC_API FClaudeAPIResponse
{
	GENERATED_BODY()

	/** The NPC's dialogue text response. */
	UPROPERTY(BlueprintReadOnly, Category = "Claude")
	FString ResponseText;

	/** Emotion hint parsed from Claude's structured output. */
	UPROPERTY(BlueprintReadOnly, Category = "Claude")
	EEmotionType NPCEmotionUpdate = EEmotionType::Neutral;

	/** Whether the NPC should give an item to the player. */
	UPROPERTY(BlueprintReadOnly, Category = "Claude")
	bool bShouldGiveItem = false;

	/** Item ID if bShouldGiveItem is true. */
	UPROPERTY(BlueprintReadOnly, Category = "Claude")
	FString ItemID;

	/** Whether the request was successful. */
	UPROPERTY(BlueprintReadOnly, Category = "Claude")
	bool bSuccess = false;

	/** Error message if the request failed. */
	UPROPERTY(BlueprintReadOnly, Category = "Claude")
	FString ErrorMessage;
};

/** Delegate fired when a Claude API response is received. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClaudeResponseReceived, const FClaudeAPIResponse&, Response);

/** Delegate for single-request completion callbacks. */
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnClaudeRequestComplete, const FClaudeAPIResponse&, Response);

/**
 * Singleton game instance subsystem that manages all communication with the Anthropic Claude API.
 *
 * Handles HTTP request construction, rate limiting with exponential backoff,
 * and parsing of structured JSON responses. All NPC dialogue routes through this subsystem.
 */
UCLASS()
class LLM_NPC_API UClaudeAPISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UClaudeAPISubsystem();

	// --- USubsystem Interface ---
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override { return true; }

	/**
	 * Send a message to the Claude API using the Anthropic Messages API format.
	 *
	 * @param SystemPrompt     The system prompt establishing NPC personality and rules.
	 * @param ConversationHistory  Array of prior messages for context.
	 * @param ModelID          Claude model identifier (e.g., "claude-sonnet-4-6").
	 * @param MaxTokens        Maximum tokens for the response.
	 * @param OnComplete       Callback delegate fired when the response arrives.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Claude")
	void SendMessage(
		const FString& SystemPrompt,
		const TArray<FNPCMessage>& ConversationHistory,
		const FString& ModelID,
		int32 MaxTokens,
		const FOnClaudeRequestComplete& OnComplete
	);

	/** Broadcast delegate fired for every received response (useful for logging/analytics). */
	UPROPERTY(BlueprintAssignable, Category = "NPC|Claude")
	FOnClaudeResponseReceived OnAnyResponseReceived;

	/** Check if the API key is configured and the subsystem is ready. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Claude")
	bool IsAPIKeyConfigured() const;

	/** Set the API key at runtime (overrides environment variable). */
	UFUNCTION(BlueprintCallable, Category = "NPC|Claude")
	void SetAPIKey(const FString& InAPIKey);

private:
	/** Internal request state for retry tracking. */
	struct FPendingRequest
	{
		FString SystemPrompt;
		TArray<FNPCMessage> ConversationHistory;
		FString ModelID;
		int32 MaxTokens;
		FOnClaudeRequestComplete OnComplete;
		int32 RetryCount;
		double NextRetryTime;
	};

	/** Load the API key from environment variable or project settings. */
	void LoadAPIKey();

	/** Build the JSON request body for the Anthropic Messages API. */
	FString BuildRequestBody(const FString& SystemPrompt, const TArray<FNPCMessage>& ConversationHistory, const FString& ModelID, int32 MaxTokens) const;

	/** Send the actual HTTP request. */
	void ExecuteRequest(TSharedPtr<FPendingRequest> PendingRequest);

	/** Handle the HTTP response, with retry logic on failure. */
	void HandleResponse(TSharedPtr<FPendingRequest> PendingRequest, bool bWasSuccessful, int32 ResponseCode, const FString& ResponseBody);

	/** Parse the Claude JSON response into our structured format. */
	FClaudeAPIResponse ParseResponse(const FString& ResponseBody) const;

	/** Convert an emotion string from Claude to our enum. */
	EEmotionType StringToEmotionType(const FString& EmotionString) const;

	/** The Anthropic API key. */
	FString APIKey;

	/** Base URL for the Anthropic API. */
	FString APIBaseURL;

	/** Anthropic API version header. */
	FString AnthropicVersion;

	/** Maximum number of retries per request. */
	static constexpr int32 MaxRetries = 3;

	/** Base delay for exponential backoff (seconds). */
	static constexpr float BaseRetryDelay = 1.0f;

	/** Rate limiting: minimum interval between requests (seconds). */
	UPROPERTY(EditDefaultsOnly, Category = "NPC|Claude")
	float MinRequestInterval = 0.5f;

	/** Timestamp of the last sent request for rate limiting. */
	double LastRequestTime = 0.0;
};
