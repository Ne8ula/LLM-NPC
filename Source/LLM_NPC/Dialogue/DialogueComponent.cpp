#include "DialogueComponent.h"
#include "ClaudeAPISubsystem.h"
#include "LLM_NPC/Core/NPCConfigDataAsset.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"

UDialogueComponent::UDialogueComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SubsystemName = TEXT("Dialogue");
}

void UDialogueComponent::BeginPlay()
{
	Super::BeginPlay();

	// Cache the ClaudeAPISubsystem reference
	if (UGameInstance* GI = GetWorld()->GetGameInstance())
	{
		CachedClaudeSubsystem = GI->GetSubsystem<UClaudeAPISubsystem>();
	}
}

void UDialogueComponent::InitializeSubsystem()
{
	Super::InitializeSubsystem();

	if (!NPCConfig)
	{
		UE_LOG(LogTemp, Warning, TEXT("DialogueComponent: No NPCConfig assigned on %s. Dialogue will not function."),
			*GetOwner()->GetName());
		bIsAvailable = false;
		return;
	}

	if (CachedClaudeSubsystem && CachedClaudeSubsystem->IsAPIKeyConfigured())
	{
		bIsAvailable = true;
		bIsInitialized = true;
		UE_LOG(LogTemp, Log, TEXT("DialogueComponent: Initialized for %s."), *GetOwner()->GetName());
	}
	else
	{
		bIsAvailable = false;
		UE_LOG(LogTemp, Warning, TEXT("DialogueComponent: ClaudeAPISubsystem not available or API key not configured."));
	}
}

void UDialogueComponent::ShutdownSubsystem()
{
	ConversationHistory.Empty();
	bWaitingForResponse = false;
	bIsInitialized = false;
	bIsAvailable = false;

	Super::ShutdownSubsystem();
}

bool UDialogueComponent::IsSubsystemAvailable() const
{
	return bIsAvailable && CachedClaudeSubsystem != nullptr && CachedClaudeSubsystem->IsAPIKeyConfigured();
}

void UDialogueComponent::SendUserMessage(const FString& UserMessage, const FDetectedUserEmotion& UserEmotion)
{
	if (!IsSubsystemAvailable())
	{
		UE_LOG(LogTemp, Warning, TEXT("DialogueComponent: Cannot send message - subsystem not available."));
		return;
	}

	if (bWaitingForResponse)
	{
		UE_LOG(LogTemp, Warning, TEXT("DialogueComponent: Already waiting for a response. Ignoring new message."));
		return;
	}

	if (!NPCConfig)
	{
		UE_LOG(LogTemp, Error, TEXT("DialogueComponent: No NPCConfig assigned."));
		return;
	}

	// Build the user message with emotion annotation
	FString AnnotatedContent = UserMessage;
	FString EmotionAnnotation = BuildEmotionAnnotation(UserEmotion);
	if (!EmotionAnnotation.IsEmpty())
	{
		AnnotatedContent = FString::Printf(TEXT("[Player emotion: %s]\n%s"), *EmotionAnnotation, *UserMessage);
	}

	// Add user message to history
	FNPCMessage UserMsg;
	UserMsg.Role = TEXT("user");
	UserMsg.Content = AnnotatedContent;
	UserMsg.Timestamp = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
	UserMsg.DetectedUserEmotion = UserEmotion.Emotion;
	UserMsg.UserEmotionConfidence = UserEmotion.Confidence;
	ConversationHistory.Add(UserMsg);

	// Trim history to configured maximum
	TrimConversationHistory();

	// Send to Claude
	bWaitingForResponse = true;

	FOnClaudeRequestComplete Callback;
	Callback.BindDynamic(this, &UDialogueComponent::OnClaudeResponseReceived);

	CachedClaudeSubsystem->SendMessage(
		NPCConfig->SystemPrompt,
		ConversationHistory,
		NPCConfig->ClaudeModelID,
		NPCConfig->MaxResponseTokens,
		Callback
	);
}

void UDialogueComponent::OnClaudeResponseReceived(const FClaudeAPIResponse& Response)
{
	bWaitingForResponse = false;

	if (!Response.bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("DialogueComponent: Claude API error: %s"), *Response.ErrorMessage);
		return;
	}

	// Add assistant message to history
	FNPCMessage AssistantMsg;
	AssistantMsg.Role = TEXT("assistant");
	AssistantMsg.Content = Response.ResponseText;
	AssistantMsg.Timestamp = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
	ConversationHistory.Add(AssistantMsg);

	// Fire the dialogue response delegate
	FName ItemName = Response.ItemID.IsEmpty() ? NAME_None : FName(*Response.ItemID);
	OnDialogueResponseReceived.Broadcast(
		Response.ResponseText,
		Response.NPCEmotionUpdate,
		Response.bShouldGiveItem,
		ItemName
	);
}

FString UDialogueComponent::BuildEmotionAnnotation(const FDetectedUserEmotion& UserEmotion) const
{
	if (UserEmotion.Confidence < 0.3f)
	{
		return FString();
	}

	FString EmotionName;
	switch (UserEmotion.Emotion)
	{
	case EEmotionType::Joy:           EmotionName = TEXT("Joy"); break;
	case EEmotionType::Sadness:       EmotionName = TEXT("Sadness"); break;
	case EEmotionType::Anger:         EmotionName = TEXT("Anger"); break;
	case EEmotionType::Fear:          EmotionName = TEXT("Fear"); break;
	case EEmotionType::Surprise:      EmotionName = TEXT("Surprise"); break;
	case EEmotionType::Disgust:       EmotionName = TEXT("Disgust"); break;
	case EEmotionType::Trust:         EmotionName = TEXT("Trust"); break;
	case EEmotionType::Anticipation:  EmotionName = TEXT("Anticipation"); break;
	default:                          EmotionName = TEXT("Neutral"); break;
	}

	return FString::Printf(TEXT("%s (confidence: %.0f%%)"), *EmotionName, UserEmotion.Confidence * 100.0f);
}

void UDialogueComponent::TrimConversationHistory()
{
	if (!NPCConfig)
	{
		return;
	}

	int32 MaxHistory = NPCConfig->MaxConversationHistory;
	if (ConversationHistory.Num() > MaxHistory)
	{
		int32 ToRemove = ConversationHistory.Num() - MaxHistory;
		ConversationHistory.RemoveAt(0, ToRemove);
	}
}

void UDialogueComponent::ClearConversationHistory()
{
	ConversationHistory.Empty();
	OnDialogueHistoryCleared.Broadcast();
}
