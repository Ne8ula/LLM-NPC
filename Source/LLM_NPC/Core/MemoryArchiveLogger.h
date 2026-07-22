#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MemoryArchiveLogger.generated.h"

struct FClaudeAPIResponse;

/**
 * Per-turn context snapshot captured by UDialogueComponent immediately before a
 * Claude dispatch. Carries everything the request body only encodes as prose
 * (the §7.7 OBSERVED STATE block) in machine-readable form, plus the raw
 * pre-annotation user message which never appears in the request at all.
 */
struct FMemoryArchiveTurnContext
{
	FString NPCName;
	FString Interaction;              // "user_message" | "object_present"
	FString SpeakerTag;               // "Speaker_A" / "Speaker_B" / "" when untagged
	FString GestureIntent;            // EGestureIntent value name, "None" when absent
	FString PlayerEmotion;            // EEmotionType value name
	float   PlayerEmotionConfidence = 0.0f;
	FString ItemID;                   // held (user_message) or presented (object_present) item, "" if none
	FString UserMessageRaw;           // player's words before annotation
	FString UserContentAnnotated;     // exact content string entering the messages array
	float   Trust = 0.0f;
	TArray<FString> ItemsInspected;   // for the resolved speaker
	TArray<FString> ItemsPresented;   // for the resolved speaker
	float   SessionElapsedSeconds = 0.0f;
	float   SessionRemainingSeconds = 0.0f;
	float   GameTimeSeconds = 0.0f;
};

/**
 * Memory Archive per-turn logger (Tier 3).
 *
 * Writes one JSON object per completed Claude turn to
 *   Saved/MemoryArchive/session-{timestamp}.jsonl
 * and exports a human-readable Markdown transcript to
 *   Saved/MemoryArchive/session-{timestamp}-transcript.md
 * on session end (Deinitialize).
 *
 * A turn record merges three event streams:
 *   1. BeginTurnContext()     — UDialogueComponent, just before dispatch
 *   2. LogRequestDispatched() — UClaudeAPISubsystem::ExecuteRequest (full request body)
 *   3. LogResponse()          — UClaudeAPISubsystem::HandleResponse (raw + parsed + latency)
 * The JSONL line is emitted at step 3. Latency is measured from the most recent
 * dispatch (i.e. it excludes retry backoff waits but includes the final attempt's
 * round trip).
 *
 * Single in-flight request assumption: UDialogueComponent::bWaitingForResponse
 * serializes turns per NPC and the slice runs one NPC, so pending state is a
 * single slot. If multi-NPC concurrency returns, key the pending state by
 * requester.
 */
UCLASS()
class LLM_NPC_API UMemoryArchiveLogger : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/** Master switch. Flip false to disable all file output without recompiling call sites. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Archive|Logging")
	bool bEnabled = true;

	/** Step 1 — structured turn context from the dialogue component. */
	void BeginTurnContext(const FMemoryArchiveTurnContext& Context);

	/** Step 2 — the exact serialized request body handed to the HTTP layer. */
	void LogRequestDispatched(const FString& ModelID, int32 MaxTokens, const FString& RequestBody, int32 RetryCount);

	/** Step 3 — terminal response (success or post-retry failure). Emits the JSONL line. */
	void LogResponse(int32 ResponseCode, const FString& RawResponseBody, const FClaudeAPIResponse& Parsed, int32 RetryCount);

	/** Absolute path of the current session's JSONL file ("" until first write). */
	const FString& GetSessionFilePath() const { return SessionFilePath; }

private:
	/** Lazily create Saved/MemoryArchive/ and the session file paths on first write. */
	void EnsureSessionFile();

	/** Append one line to the session JSONL file. */
	void AppendLine(const FString& Line);

	/** Write the Markdown transcript from accumulated turns. */
	void ExportTranscript();

	// --- Pending (in-flight) turn state -----------------------------------

	FMemoryArchiveTurnContext PendingContext;
	bool    bHasPendingContext = false;

	FString PendingModelID;
	int32   PendingMaxTokens = 0;
	FString PendingRequestBody;
	int32   PendingRetryCount = 0;
	double  PendingDispatchTime = 0.0;
	bool    bHasPendingRequest = false;

	// --- Session state ----------------------------------------------------

	FString SessionTimestamp;
	FString SessionFilePath;
	FString TranscriptFilePath;
	int32   TurnCounter = 0;

	/** Minimal per-turn record retained in memory for the transcript export. */
	struct FTranscriptTurn
	{
		FString NPCName;
		FString SpeakerTag;
		FString Interaction;
		FString GestureIntent;
		FString UserMessageRaw;
		FString ResponseText;
		FString NPCEmotion;
		FString BranchResolution;
		bool    bSuccess = true;
		FString ErrorMessage;
	};
	TArray<FTranscriptTurn> TranscriptTurns;
};
