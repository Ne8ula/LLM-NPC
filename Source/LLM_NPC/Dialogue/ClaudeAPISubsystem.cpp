#include "ClaudeAPISubsystem.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Async/Async.h"
#include "TimerManager.h"
#include "Engine/GameInstance.h"

UClaudeAPISubsystem::UClaudeAPISubsystem()
	: APIBaseURL(TEXT("https://api.anthropic.com/v1/messages"))
	, AnthropicVersion(TEXT("2023-06-01"))
{
}

void UClaudeAPISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	LoadAPIKey();
}

void UClaudeAPISubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UClaudeAPISubsystem::LoadAPIKey()
{
	// Try environment variable first
	FString EnvKey = FPlatformMisc::GetEnvironmentVariable(TEXT("ANTHROPIC_API_KEY"));
	if (!EnvKey.IsEmpty())
	{
		APIKey = EnvKey;
		UE_LOG(LogTemp, Log, TEXT("ClaudeAPISubsystem: API key loaded from environment variable."));
		return;
	}

	// Fallback: try loading from config file
	FString ConfigKey;
	if (GConfig && GConfig->GetString(TEXT("/Script/LLM_NPC.ClaudeAPISettings"), TEXT("APIKey"), ConfigKey, GGameIni))
	{
		APIKey = ConfigKey;
		UE_LOG(LogTemp, Log, TEXT("ClaudeAPISubsystem: API key loaded from project settings."));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("ClaudeAPISubsystem: No API key found. Set ANTHROPIC_API_KEY environment variable or configure in project settings."));
}

bool UClaudeAPISubsystem::IsAPIKeyConfigured() const
{
	return !APIKey.IsEmpty();
}

void UClaudeAPISubsystem::SetAPIKey(const FString& InAPIKey)
{
	APIKey = InAPIKey;
}

void UClaudeAPISubsystem::SendMessage(
	const FString& SystemPrompt,
	const TArray<FNPCMessage>& ConversationHistory,
	const FString& ModelID,
	int32 MaxTokens,
	const FOnClaudeRequestComplete& OnComplete)
{
	if (!IsAPIKeyConfigured())
	{
		FClaudeAPIResponse ErrorResponse;
		ErrorResponse.bSuccess = false;
		ErrorResponse.ErrorMessage = TEXT("API key not configured.");
		OnComplete.ExecuteIfBound(ErrorResponse);
		return;
	}

	TSharedPtr<FPendingRequest> PendingRequest = MakeShared<FPendingRequest>();
	PendingRequest->SystemPrompt = SystemPrompt;
	PendingRequest->ConversationHistory = ConversationHistory;
	PendingRequest->ModelID = ModelID;
	PendingRequest->MaxTokens = MaxTokens;
	PendingRequest->OnComplete = OnComplete;
	PendingRequest->RetryCount = 0;
	PendingRequest->NextRetryTime = 0.0;

	// Rate limiting: ensure minimum interval between requests
	double CurrentTime = FPlatformTime::Seconds();
	double TimeSinceLastRequest = CurrentTime - LastRequestTime;

	if (TimeSinceLastRequest < MinRequestInterval)
	{
		float Delay = MinRequestInterval - TimeSinceLastRequest;
		if (UGameInstance* GI = GetGameInstance())
		{
			if (UWorld* World = GI->GetWorld())
			{
				FTimerHandle TimerHandle;
				FTimerDelegate TimerDelegate;
				TimerDelegate.BindLambda([this, PendingRequest]()
				{
					ExecuteRequest(PendingRequest);
				});
				World->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, Delay, false);
				return;
			}
		}
	}

	ExecuteRequest(PendingRequest);
}

FString UClaudeAPISubsystem::BuildRequestBody(
	const FString& SystemPrompt,
	const TArray<FNPCMessage>& ConversationHistory,
	const FString& ModelID,
	int32 MaxTokens) const
{
	TSharedPtr<FJsonObject> RootObject = MakeShared<FJsonObject>();

	RootObject->SetStringField(TEXT("model"), ModelID);
	RootObject->SetNumberField(TEXT("max_tokens"), MaxTokens);

	// System prompt with structured output instructions
	FString AugmentedSystemPrompt = SystemPrompt + TEXT("\n\n")
		TEXT("IMPORTANT: You must respond with ONLY a valid JSON object in this exact format:\n")
		TEXT("{\n")
		TEXT("  \"response_text\": \"your dialogue response here\",\n")
		TEXT("  \"npc_emotion_update\": \"one of: Neutral, Joy, Sadness, Anger, Fear, Surprise, Disgust, Trust, Anticipation\",\n")
		TEXT("  \"should_give_item\": false,\n")
		TEXT("  \"item_id\": \"\"\n")
		TEXT("}\n")
		TEXT("Always respond in this JSON format. The response_text field contains your in-character dialogue.");

	RootObject->SetStringField(TEXT("system"), AugmentedSystemPrompt);

	// Build messages array
	TArray<TSharedPtr<FJsonValue>> MessagesArray;
	for (const FNPCMessage& Message : ConversationHistory)
	{
		TSharedPtr<FJsonObject> MessageObject = MakeShared<FJsonObject>();
		MessageObject->SetStringField(TEXT("role"), Message.Role);
		MessageObject->SetStringField(TEXT("content"), Message.Content);
		MessagesArray.Add(MakeShared<FJsonValueObject>(MessageObject));
	}

	RootObject->SetArrayField(TEXT("messages"), MessagesArray);

	// Serialize to string
	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(RootObject.ToSharedRef(), Writer);

	return OutputString;
}

void UClaudeAPISubsystem::ExecuteRequest(TSharedPtr<FPendingRequest> PendingRequest)
{
	LastRequestTime = FPlatformTime::Seconds();

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(APIBaseURL);
	HttpRequest->SetVerb(TEXT("POST"));
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	HttpRequest->SetHeader(TEXT("x-api-key"), APIKey);
	HttpRequest->SetHeader(TEXT("anthropic-version"), AnthropicVersion);

	FString RequestBody = BuildRequestBody(
		PendingRequest->SystemPrompt,
		PendingRequest->ConversationHistory,
		PendingRequest->ModelID,
		PendingRequest->MaxTokens
	);
	HttpRequest->SetContentAsString(RequestBody);

	TWeakObjectPtr<UClaudeAPISubsystem> WeakThis(this);
	HttpRequest->OnProcessRequestComplete().BindLambda(
		[WeakThis, PendingRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
		{
			if (!WeakThis.IsValid())
			{
				return;
			}

			int32 ResponseCode = Response.IsValid() ? Response->GetResponseCode() : 0;
			FString ResponseBody = Response.IsValid() ? Response->GetContentAsString() : TEXT("");

			WeakThis->HandleResponse(PendingRequest, bConnectedSuccessfully, ResponseCode, ResponseBody);
		}
	);

	HttpRequest->ProcessRequest();
}

void UClaudeAPISubsystem::HandleResponse(
	TSharedPtr<FPendingRequest> PendingRequest,
	bool bWasSuccessful,
	int32 ResponseCode,
	const FString& ResponseBody)
{
	// Check for retryable errors (rate limit, server errors, connection failures)
	bool bShouldRetry = false;
	if (!bWasSuccessful || ResponseCode == 429 || ResponseCode >= 500)
	{
		bShouldRetry = PendingRequest->RetryCount < MaxRetries;
	}

	if (bShouldRetry)
	{
		PendingRequest->RetryCount++;
		float Delay = BaseRetryDelay * FMath::Pow(2.0f, static_cast<float>(PendingRequest->RetryCount - 1));
		// Add jitter
		Delay += FMath::FRandRange(0.0f, Delay * 0.25f);

		UE_LOG(LogTemp, Warning, TEXT("ClaudeAPISubsystem: Request failed (code %d). Retry %d/%d in %.1fs"),
			ResponseCode, PendingRequest->RetryCount, MaxRetries, Delay);

		if (UGameInstance* GI = GetGameInstance())
		{
			if (UWorld* World = GI->GetWorld())
			{
				FTimerHandle TimerHandle;
				FTimerDelegate TimerDelegate;
				TimerDelegate.BindLambda([this, PendingRequest]()
				{
					ExecuteRequest(PendingRequest);
				});
				World->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, Delay, false);
				return;
			}
		}
	}

	// Parse the response or construct an error
	FClaudeAPIResponse ParsedResponse;

	if (bWasSuccessful && ResponseCode == 200)
	{
		ParsedResponse = ParseResponse(ResponseBody);
	}
	else
	{
		ParsedResponse.bSuccess = false;
		ParsedResponse.ErrorMessage = FString::Printf(TEXT("HTTP %d: %s"), ResponseCode, *ResponseBody);
		UE_LOG(LogTemp, Error, TEXT("ClaudeAPISubsystem: Request failed after %d retries. %s"),
			PendingRequest->RetryCount, *ParsedResponse.ErrorMessage);
	}

	// Fire callbacks on the game thread
	TWeakObjectPtr<UClaudeAPISubsystem> WeakSelf(this);
	AsyncTask(ENamedThreads::GameThread, [WeakSelf, PendingRequest, ParsedResponse]()
	{
		PendingRequest->OnComplete.ExecuteIfBound(ParsedResponse);
		if (WeakSelf.IsValid())
		{
			WeakSelf->OnAnyResponseReceived.Broadcast(ParsedResponse);
		}
	});
}

FClaudeAPIResponse UClaudeAPISubsystem::ParseResponse(const FString& ResponseBody) const
{
	FClaudeAPIResponse Result;

	TSharedPtr<FJsonObject> RootObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseBody);

	if (!FJsonSerializer::Deserialize(Reader, RootObject) || !RootObject.IsValid())
	{
		Result.bSuccess = false;
		Result.ErrorMessage = TEXT("Failed to parse Claude API response JSON.");
		return Result;
	}

	// Extract the text content from the Anthropic Messages API response format
	// Format: { "content": [ { "type": "text", "text": "..." } ] }
	const TArray<TSharedPtr<FJsonValue>>* ContentArray = nullptr;
	if (!RootObject->TryGetArrayField(TEXT("content"), ContentArray) || ContentArray->Num() == 0)
	{
		Result.bSuccess = false;
		Result.ErrorMessage = TEXT("No content array in Claude response.");
		return Result;
	}

	FString RawText;
	for (const TSharedPtr<FJsonValue>& ContentItem : *ContentArray)
	{
		const TSharedPtr<FJsonObject>* ContentObj = nullptr;
		if (ContentItem->TryGetObject(ContentObj))
		{
			FString Type;
			if ((*ContentObj)->TryGetStringField(TEXT("type"), Type) && Type == TEXT("text"))
			{
				(*ContentObj)->TryGetStringField(TEXT("text"), RawText);
				break;
			}
		}
	}

	if (RawText.IsEmpty())
	{
		Result.bSuccess = false;
		Result.ErrorMessage = TEXT("No text content found in Claude response.");
		return Result;
	}

	// Try to extract JSON from the response text
	// Claude may return pure JSON, or JSON embedded in text
	FString JsonText = RawText;

	// Find the first { and last } to extract JSON block
	int32 FirstBrace = RawText.Find(TEXT("{"));
	int32 LastBrace = RawText.Find(TEXT("}"), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	if (FirstBrace != INDEX_NONE && LastBrace != INDEX_NONE && LastBrace > FirstBrace)
	{
		JsonText = RawText.Mid(FirstBrace, LastBrace - FirstBrace + 1);
	}

	// Parse the structured JSON from Claude's text response
	TSharedPtr<FJsonObject> StructuredResponse;
	TSharedRef<TJsonReader<>> InnerReader = TJsonReaderFactory<>::Create(JsonText);

	if (FJsonSerializer::Deserialize(InnerReader, StructuredResponse) && StructuredResponse.IsValid())
	{
		StructuredResponse->TryGetStringField(TEXT("response_text"), Result.ResponseText);

		FString EmotionString;
		if (StructuredResponse->TryGetStringField(TEXT("npc_emotion_update"), EmotionString))
		{
			Result.NPCEmotionUpdate = StringToEmotionType(EmotionString);
		}

		StructuredResponse->TryGetBoolField(TEXT("should_give_item"), Result.bShouldGiveItem);
		StructuredResponse->TryGetStringField(TEXT("item_id"), Result.ItemID);

		Result.bSuccess = true;
		UE_LOG(LogTemp, Log, TEXT("ClaudeAPISubsystem: Parsed structured response. Emotion: %s"), *EmotionString);
	}
	else
	{
		// Fallback: use raw text but strip any JSON-looking content
		Result.ResponseText = RawText;
		Result.NPCEmotionUpdate = EEmotionType::Neutral;
		Result.bShouldGiveItem = false;
		Result.bSuccess = true;

		UE_LOG(LogTemp, Warning, TEXT("ClaudeAPISubsystem: Response was not structured JSON, using raw text."));
	}

	return Result;
}

EEmotionType UClaudeAPISubsystem::StringToEmotionType(const FString& EmotionString) const
{
	FString Normalized = EmotionString.TrimStartAndEnd().ToLower();

	if (Normalized == TEXT("joy"))           return EEmotionType::Joy;
	if (Normalized == TEXT("sadness"))       return EEmotionType::Sadness;
	if (Normalized == TEXT("anger"))         return EEmotionType::Anger;
	if (Normalized == TEXT("fear"))          return EEmotionType::Fear;
	if (Normalized == TEXT("surprise"))      return EEmotionType::Surprise;
	if (Normalized == TEXT("disgust"))       return EEmotionType::Disgust;
	if (Normalized == TEXT("trust"))         return EEmotionType::Trust;
	if (Normalized == TEXT("anticipation"))  return EEmotionType::Anticipation;

	return EEmotionType::Neutral;
}
