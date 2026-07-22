#include "MemoryArchiveLogger.h"
#include "LLM_NPC/Dialogue/ClaudeAPISubsystem.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Policies/CondensedJsonPrintPolicy.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"

void UMemoryArchiveLogger::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	// File creation is deferred to the first logged event so idle editor
	// sessions (no PIE turn ever dispatched) leave no empty files behind.
	SessionTimestamp = FDateTime::Now().ToString(TEXT("%Y%m%d-%H%M%S"));
}

void UMemoryArchiveLogger::Deinitialize()
{
	ExportTranscript();
	Super::Deinitialize();
}

void UMemoryArchiveLogger::BeginTurnContext(const FMemoryArchiveTurnContext& Context)
{
	if (!bEnabled)
	{
		return;
	}
	PendingContext = Context;
	bHasPendingContext = true;
}

void UMemoryArchiveLogger::LogRequestDispatched(const FString& ModelID, int32 MaxTokens, const FString& RequestBody, int32 RetryCount)
{
	if (!bEnabled)
	{
		return;
	}
	PendingModelID = ModelID;
	PendingMaxTokens = MaxTokens;
	PendingRequestBody = RequestBody;
	PendingRetryCount = RetryCount;
	PendingDispatchTime = FPlatformTime::Seconds();
	bHasPendingRequest = true;
}

void UMemoryArchiveLogger::LogResponse(int32 ResponseCode, const FString& RawResponseBody, const FClaudeAPIResponse& Parsed, int32 RetryCount)
{
	if (!bEnabled)
	{
		return;
	}

	const double LatencySeconds = bHasPendingRequest
		? FPlatformTime::Seconds() - PendingDispatchTime
		: -1.0;

	++TurnCounter;

	TSharedPtr<FJsonObject> Rec = MakeShared<FJsonObject>();
	Rec->SetNumberField(TEXT("turn"), TurnCounter);
	Rec->SetStringField(TEXT("t_wall"), FDateTime::UtcNow().ToIso8601());

	// -- Step 1: dialogue-component context (may be absent for non-Dialogue callers)
	if (bHasPendingContext)
	{
		Rec->SetNumberField(TEXT("t_game"), PendingContext.GameTimeSeconds);
		Rec->SetStringField(TEXT("npc"), PendingContext.NPCName);
		Rec->SetStringField(TEXT("interaction"), PendingContext.Interaction);
		Rec->SetStringField(TEXT("speaker"), PendingContext.SpeakerTag);
		Rec->SetStringField(TEXT("gesture"), PendingContext.GestureIntent);
		Rec->SetStringField(TEXT("player_emotion"), PendingContext.PlayerEmotion);
		Rec->SetNumberField(TEXT("player_emotion_confidence"), PendingContext.PlayerEmotionConfidence);
		Rec->SetStringField(TEXT("item"), PendingContext.ItemID);
		Rec->SetStringField(TEXT("user_message_raw"), PendingContext.UserMessageRaw);
		Rec->SetStringField(TEXT("user_content_annotated"), PendingContext.UserContentAnnotated);
		Rec->SetNumberField(TEXT("trust"), PendingContext.Trust);

		TArray<TSharedPtr<FJsonValue>> Inspected;
		for (const FString& Id : PendingContext.ItemsInspected)
		{
			Inspected.Add(MakeShared<FJsonValueString>(Id));
		}
		Rec->SetArrayField(TEXT("items_inspected"), Inspected);

		TArray<TSharedPtr<FJsonValue>> Presented;
		for (const FString& Id : PendingContext.ItemsPresented)
		{
			Presented.Add(MakeShared<FJsonValueString>(Id));
		}
		Rec->SetArrayField(TEXT("items_presented"), Presented);

		Rec->SetNumberField(TEXT("session_elapsed_s"), PendingContext.SessionElapsedSeconds);
		Rec->SetNumberField(TEXT("session_remaining_s"), PendingContext.SessionRemainingSeconds);
	}

	// -- Step 2: request payload
	if (bHasPendingRequest)
	{
		Rec->SetStringField(TEXT("model"), PendingModelID);
		Rec->SetNumberField(TEXT("max_tokens"), PendingMaxTokens);
		Rec->SetStringField(TEXT("request_body"), PendingRequestBody);
	}

	// -- Step 3: response
	Rec->SetNumberField(TEXT("http_code"), ResponseCode);
	Rec->SetNumberField(TEXT("retries"), RetryCount);
	Rec->SetNumberField(TEXT("latency_s"), LatencySeconds);
	Rec->SetStringField(TEXT("response_raw"), RawResponseBody);
	Rec->SetBoolField(TEXT("success"), Parsed.bSuccess);
	Rec->SetStringField(TEXT("response_text"), Parsed.ResponseText);
	Rec->SetStringField(TEXT("npc_emotion"), UEnum::GetDisplayValueAsText(Parsed.NPCEmotionUpdate).ToString());
	Rec->SetBoolField(TEXT("should_give_item"), Parsed.bShouldGiveItem);
	Rec->SetStringField(TEXT("item_id"), Parsed.ItemID);
	Rec->SetStringField(TEXT("branch_resolution"), Parsed.BranchResolution);
	Rec->SetStringField(TEXT("error"), Parsed.ErrorMessage);

	// Condensed policy => single line, valid JSONL.
	FString Line;
	TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer =
		TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Line);
	FJsonSerializer::Serialize(Rec.ToSharedRef(), Writer);
	AppendLine(Line);

	// Retain the transcript slice.
	FTranscriptTurn T;
	if (bHasPendingContext)
	{
		T.NPCName = PendingContext.NPCName;
		T.SpeakerTag = PendingContext.SpeakerTag;
		T.Interaction = PendingContext.Interaction;
		T.GestureIntent = PendingContext.GestureIntent;
		T.UserMessageRaw = PendingContext.UserMessageRaw;
	}
	T.ResponseText = Parsed.ResponseText;
	T.NPCEmotion = UEnum::GetDisplayValueAsText(Parsed.NPCEmotionUpdate).ToString();
	T.BranchResolution = Parsed.BranchResolution;
	T.bSuccess = Parsed.bSuccess;
	T.ErrorMessage = Parsed.ErrorMessage;
	TranscriptTurns.Add(MoveTemp(T));

	// Consume the pending slots.
	bHasPendingContext = false;
	bHasPendingRequest = false;
}

void UMemoryArchiveLogger::EnsureSessionFile()
{
	if (!SessionFilePath.IsEmpty())
	{
		return;
	}
	const FString Dir = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("MemoryArchive"));
	IFileManager::Get().MakeDirectory(*Dir, /*Tree=*/true);
	SessionFilePath = FPaths::Combine(Dir, FString::Printf(TEXT("session-%s.jsonl"), *SessionTimestamp));
	TranscriptFilePath = FPaths::Combine(Dir, FString::Printf(TEXT("session-%s-transcript.md"), *SessionTimestamp));
	UE_LOG(LogTemp, Log, TEXT("MemoryArchiveLogger: session file %s"), *SessionFilePath);
}

void UMemoryArchiveLogger::AppendLine(const FString& Line)
{
	EnsureSessionFile();
	FFileHelper::SaveStringToFile(
		Line + LINE_TERMINATOR,
		*SessionFilePath,
		FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM,
		&IFileManager::Get(),
		FILEWRITE_Append);
}

void UMemoryArchiveLogger::ExportTranscript()
{
	if (TranscriptTurns.Num() == 0 || TranscriptFilePath.IsEmpty())
	{
		return;
	}

	FString Md;
	Md += FString::Printf(TEXT("# Memory Archive transcript — session %s\n\n"), *SessionTimestamp);
	Md += FString::Printf(TEXT("%d turns.\n\n---\n\n"), TranscriptTurns.Num());

	for (const FTranscriptTurn& T : TranscriptTurns)
	{
		const FString Who = T.SpeakerTag.IsEmpty() ? TEXT("Visitor") : T.SpeakerTag;
		if (T.Interaction == TEXT("object_present"))
		{
			Md += FString::Printf(TEXT("**%s** *(presents item)*: %s\n\n"), *Who, *T.UserMessageRaw);
		}
		else
		{
			FString Suffix;
			if (!T.GestureIntent.IsEmpty() && T.GestureIntent != TEXT("None"))
			{
				Suffix = FString::Printf(TEXT(" *(gesture: %s)*"), *T.GestureIntent);
			}
			Md += FString::Printf(TEXT("**%s**%s: %s\n\n"), *Who, *Suffix, *T.UserMessageRaw);
		}

		if (T.bSuccess)
		{
			FString Tail;
			if (!T.BranchResolution.IsEmpty())
			{
				Tail = FString::Printf(TEXT(" *(branch: %s)*"), *T.BranchResolution);
			}
			Md += FString::Printf(TEXT("**%s** *(%s)*%s: %s\n\n"),
				T.NPCName.IsEmpty() ? TEXT("NPC") : *T.NPCName, *T.NPCEmotion, *Tail, *T.ResponseText);
		}
		else
		{
			Md += FString::Printf(TEXT("*(API error: %s)*\n\n"), *T.ErrorMessage);
		}
	}

	FFileHelper::SaveStringToFile(Md, *TranscriptFilePath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
	UE_LOG(LogTemp, Log, TEXT("MemoryArchiveLogger: transcript exported to %s"), *TranscriptFilePath);
}
