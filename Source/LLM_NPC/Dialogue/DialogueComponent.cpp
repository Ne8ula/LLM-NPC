#include "DialogueComponent.h"
#include "ClaudeAPISubsystem.h"
#include "LLM_NPC/Core/NPCConfigDataAsset.h"
#include "LLM_NPC/Core/NPCCharacter.h"
#include "LLM_NPC/Core/NPCGraphDataAsset.h"
#include "LLM_NPC/Emotion/EmotionComponent.h"
#include "LLM_NPC/Dialogue/ElevenLabsTTSComponent.h"
#include "LLM_NPC/Gesture/InspectableItem.h"
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

	// Try to get NPCConfig from owner's ANPCCharacter if not set directly
	if (!NPCConfig && GetOwner())
	{
		if (ANPCCharacter* NPC = Cast<ANPCCharacter>(GetOwner()))
		{
			NPCConfig = NPC->NPCConfig;
		}
	}

	if (!NPCConfig)
	{
		UE_LOG(LogTemp, Warning, TEXT("DialogueComponent: No NPCConfig assigned on %s. Dialogue will not function."),
			*GetOwner()->GetName());
		bIsAvailable = false;
		return;
	}

	// Cache the subsystem lazily — it may not be ready during BeginPlay
	if (!CachedClaudeSubsystem && GetWorld())
	{
		if (UGameInstance* GI = GetWorld()->GetGameInstance())
		{
			CachedClaudeSubsystem = GI->GetSubsystem<UClaudeAPISubsystem>();
		}
	}

	// Resolve GraphNodeID from the graph if not already set by NPCGameMode.
	// NPCGameMode::BeginPlay() sets this before InitializeSubsystem() when possible,
	// but we fall back to name-matching in case of BeginPlay ordering variance.
	if (GraphNodeID.IsNone() && NPCConfig->GraphDataAsset.IsValid())
	{
		UNPCGraphDataAsset* Graph = NPCConfig->GraphDataAsset.Get();
		if (!Graph)
		{
			Graph = NPCConfig->GraphDataAsset.LoadSynchronous();
		}
		if (Graph)
		{
			const FString NPCName = NPCConfig->NPCName.ToString();
			for (const FNPCGraphNode& Node : Graph->Nodes)
			{
				if (Node.NPCName == NPCName || Node.NPCID.ToString() == NPCName)
				{
					GraphNodeID = Node.NPCID;
					break;
				}
			}
		}
	}

	// Log the resolved system prompt (first 200 chars) for test verification.
	if (!GraphNodeID.IsNone() && NPCConfig->GraphDataAsset.IsValid())
	{
		if (const UNPCGraphDataAsset* Graph = NPCConfig->GraphDataAsset.Get())
		{
			if (const FNPCGraphNode* Node = Graph->FindNode(GraphNodeID))
			{
				const FString Built = BuildSystemPromptFromGraph(Graph, *Node);
				UE_LOG(LogTemp, Log, TEXT("DialogueComponent [%s]: graph-driven prompt (first 200): %s"),
					*NPCConfig->NPCName.ToString(), *Built.Left(200));
			}
		}
	}

	if (CachedClaudeSubsystem && CachedClaudeSubsystem->IsAPIKeyConfigured())
	{
		bIsAvailable = true;
		bIsInitialized = true;
		UE_LOG(LogTemp, Log, TEXT("DialogueComponent: Initialized for NPC '%s'. Claude API ready."),
			*NPCConfig->NPCName.ToString());
	}
	else
	{
		// Still mark as available — we can retry getting the subsystem when sending messages
		bIsAvailable = true;
		UE_LOG(LogTemp, Warning, TEXT("DialogueComponent: ClaudeAPISubsystem not yet available. Will retry on first message."));
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

void UDialogueComponent::SendUserMessage(const FString& UserMessage, const FDetectedUserEmotion& UserEmotion,
	EGestureIntent GestureIntent)
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

	// Build the annotated user message (gesture first, then emotion, then text).
	const FString AnnotatedContent = BuildAnnotatedContent(UserMessage, UserEmotion, GestureIntent);

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

	// Determine system prompt — graph-driven when available, legacy fallback otherwise.
	FString SystemPrompt = NPCConfig->SystemPrompt;
	{
		UNPCGraphDataAsset* Graph = NPCConfig->GraphDataAsset.Get();
		if (!Graph && !NPCConfig->GraphDataAsset.IsNull())
		{
			Graph = NPCConfig->GraphDataAsset.LoadSynchronous();
		}
		if (Graph)
		{
			// Lazy resolution of GraphNodeID in case GameMode BeginPlay ran after ours.
			if (GraphNodeID.IsNone())
			{
				const FString NPCName = NPCConfig->NPCName.ToString();
				for (const FNPCGraphNode& Node : Graph->Nodes)
				{
					if (Node.NPCName == NPCName || Node.NPCID.ToString() == NPCName)
					{
						GraphNodeID = Node.NPCID;
						break;
					}
				}
			}
			if (!GraphNodeID.IsNone())
			{
				if (const FNPCGraphNode* Node = Graph->FindNode(GraphNodeID))
				{
					SystemPrompt = BuildSystemPromptFromGraph(Graph, *Node);
				}
			}
		}
	}

	// Send to Claude
	bWaitingForResponse = true;

	FOnClaudeRequestComplete Callback;
	Callback.BindDynamic(this, &UDialogueComponent::OnClaudeResponseReceived);

	CachedClaudeSubsystem->SendMessage(
		SystemPrompt,
		ConversationHistory,
		NPCConfig->ClaudeModelID,
		NPCConfig->MaxResponseTokens,
		Callback
	);
}

void UDialogueComponent::SendObjectPresentMessage(AInspectableItem* Item, const FDetectedUserEmotion& UserEmotion,
	EGestureIntent GestureIntent)
{
	if (!Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("DialogueComponent::SendObjectPresentMessage: null Item, ignoring."));
		return;
	}

	if (!IsSubsystemAvailable())
	{
		UE_LOG(LogTemp, Warning, TEXT("DialogueComponent: Cannot present item - subsystem not available."));
		return;
	}

	if (bWaitingForResponse)
	{
		UE_LOG(LogTemp, Warning, TEXT("DialogueComponent: Already waiting for a response. Ignoring present action."));
		return;
	}

	if (!NPCConfig)
	{
		UE_LOG(LogTemp, Error, TEXT("DialogueComponent: No NPCConfig assigned."));
		return;
	}

	// Build the structured presentation payload. Wrapped in [ ] so the LLM treats it as
	// observed context, not the player's spoken words. Speaker tagging is added in Tier 2.
	const FString DisplayName = Item->ItemDisplayName.IsEmpty()
		? Item->GetName()
		: Item->ItemDisplayName;

	FString PresentBody = FString::Printf(
		TEXT("[The visitor presents to you: %s. The item is now in your sightline."),
		*DisplayName);

	if (!Item->ItemWorldDescription.IsEmpty())
	{
		PresentBody += FString::Printf(TEXT(" They see: %s."), *Item->ItemWorldDescription);
	}
	if (!Item->NPCKnowledgeText.IsEmpty())
	{
		PresentBody += FString::Printf(TEXT(" Your private knowledge of this object: %s"), *Item->NPCKnowledgeText);
	}
	PresentBody += TEXT("]");

	// Run through BuildAnnotatedContent so gesture/emotion annotations stay in their
	// canonical position relative to the rest of the user-content prefix.
	const FString AnnotatedContent = BuildAnnotatedContent(PresentBody, UserEmotion, GestureIntent);

	FNPCMessage UserMsg;
	UserMsg.Role = TEXT("user");
	UserMsg.Content = AnnotatedContent;
	UserMsg.Timestamp = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
	UserMsg.DetectedUserEmotion = UserEmotion.Emotion;
	UserMsg.UserEmotionConfidence = UserEmotion.Confidence;
	ConversationHistory.Add(UserMsg);

	TrimConversationHistory();

	// Determine system prompt — graph-driven when available, legacy fallback otherwise.
	FString SystemPrompt = NPCConfig->SystemPrompt;
	{
		UNPCGraphDataAsset* Graph = NPCConfig->GraphDataAsset.Get();
		if (!Graph && !NPCConfig->GraphDataAsset.IsNull())
		{
			Graph = NPCConfig->GraphDataAsset.LoadSynchronous();
		}
		if (Graph)
		{
			if (GraphNodeID.IsNone())
			{
				const FString NPCName = NPCConfig->NPCName.ToString();
				for (const FNPCGraphNode& Node : Graph->Nodes)
				{
					if (Node.NPCName == NPCName || Node.NPCID.ToString() == NPCName)
					{
						GraphNodeID = Node.NPCID;
						break;
					}
				}
			}
			if (!GraphNodeID.IsNone())
			{
				if (const FNPCGraphNode* Node = Graph->FindNode(GraphNodeID))
				{
					SystemPrompt = BuildSystemPromptFromGraph(Graph, *Node);
				}
			}
		}
	}

	bWaitingForResponse = true;

	FOnClaudeRequestComplete Callback;
	Callback.BindDynamic(this, &UDialogueComponent::OnClaudeResponseReceived);

	CachedClaudeSubsystem->SendMessage(
		SystemPrompt,
		ConversationHistory,
		NPCConfig->ClaudeModelID,
		NPCConfig->MaxResponseTokens,
		Callback
	);

	UE_LOG(LogTemp, Log, TEXT("DialogueComponent: Presented item '%s' (ID=%s) to NPC."),
		*DisplayName, *Item->ItemID.ToString());
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

	// Feed emotion hint into the EmotionComponent so blend shapes update
	if (Response.NPCEmotionUpdate != EEmotionType::Neutral)
	{
		if (AActor* Owner = GetOwner())
		{
			if (UEmotionComponent* EmotionComp = Owner->FindComponentByClass<UEmotionComponent>())
			{
				FEmotionSignal Signal;
				Signal.TargetEmotion = Response.NPCEmotionUpdate;
				Signal.Strength = 1.0f;
				Signal.Source = TEXT("ClaudeDialogueResponse");
				EmotionComp->ProcessSignal(Signal);
				UE_LOG(LogTemp, Log, TEXT("DialogueComponent: Sent emotion signal '%s' to EmotionComponent"),
					*UEnum::GetValueAsString(Response.NPCEmotionUpdate));
			}
		}
	}

	// Fire the dialogue response delegate
	FName ItemName = Response.ItemID.IsEmpty() ? NAME_None : FName(*Response.ItemID);
	OnDialogueResponseReceived.Broadcast(
		Response.ResponseText,
		Response.NPCEmotionUpdate,
		Response.bShouldGiveItem,
		ItemName
	);

	// Trigger TTS to speak the response aloud
	if (AActor* Owner = GetOwner())
	{
		if (UElevenLabsTTSComponent* TTS = Owner->FindComponentByClass<UElevenLabsTTSComponent>())
		{
			FString VoiceID;
			float Stability = -1.0f;
			float SimilarityBoost = -1.0f;

			// Pull voice settings from NPCConfig as baseline
			if (NPCConfig)
			{
				VoiceID = NPCConfig->ElevenLabsVoiceID;
				Stability = NPCConfig->VoiceStability;
				SimilarityBoost = NPCConfig->VoiceSimilarityBoost;

				// Graph node voice ID trumps NPCConfig voice ID
				if (!GraphNodeID.IsNone())
				{
					if (const UNPCGraphDataAsset* Graph = NPCConfig->GraphDataAsset.Get())
					{
						if (const FNPCGraphNode* Node = Graph->FindNode(GraphNodeID))
						{
							if (!Node->ElevenLabsVoiceID.IsEmpty())
							{
								VoiceID = Node->ElevenLabsVoiceID;
							}
						}
					}
				}
			}

			TTS->SpeakText(Response.ResponseText, VoiceID, Stability, SimilarityBoost);
		}
	}
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

FString UDialogueComponent::BuildSystemPromptFromGraph(const UNPCGraphDataAsset* Graph, const FNPCGraphNode& Node) const
{
	TStringBuilder<8192> P;

	// 1. Identity
	P.Appendf(TEXT("You are %s. %s\n\n"), *Node.NPCName, *Node.Role);

	// 2. Player relationship — sets the relational register before anything else
	if (!Node.PlayerRelationship.IsEmpty())
	{
		P.Appendf(TEXT("%s\n\n"), *Node.PlayerRelationship);
	}

	// 3. Shared reference point — ambient weight, not a plot summary
	if (!Graph->EventSummary.IsEmpty())
	{
		P.Appendf(TEXT("%s\n\n"), *Graph->EventSummary);
	}

	// 4. What this NPC knows about the event
	if (!Node.KnowsAboutEvent.IsEmpty())
	{
		P.Appendf(TEXT("%s\n\n"), *Node.KnowsAboutEvent);
	}

	// 5. What they will not say unprompted — behavioral constraint, not a stated secret
	if (!Node.WithheldTruth.IsEmpty())
	{
		P.Appendf(TEXT("There is something you carry but would not say unprompted. %s\n\n"), *Node.WithheldTruth);
	}

	// 6. Memory quality — how their recollection is distorted
	if (!Node.MisrememberedDetail.IsEmpty())
	{
		P.Appendf(TEXT("The quality of your memory: %s\n\n"), *Node.MisrememberedDetail);
	}

	// 7. Relationship context — inject all outgoing edges from this NPC's perspective
	bool bAnyEdge = false;
	for (const FNPCGraphEdge& Edge : Graph->Edges)
	{
		if (Edge.FromNPCID != Node.NPCID || Edge.RelationshipDescription.IsEmpty())
		{
			continue;
		}
		FString TargetName = Edge.ToNPCID.ToString();
		if (const FNPCGraphNode* Target = Graph->FindNode(Edge.ToNPCID))
		{
			TargetName = Target->NPCName;
		}
		P.Appendf(TEXT("Regarding %s: %s\n"), *TargetName, *Edge.RelationshipDescription);
		bAnyEdge = true;
	}
	if (bAnyEdge)
	{
		P.Append(TEXT("\n"));
	}

	// 7.5 Visitors register — establishes the multi-speaker frame.
	// Phrased to gracefully degrade: when speaker tags are absent (Tier 0 / single-speaker
	// fallback), the LLM treats the conversation as one visitor; when [Speaker_A] / [Speaker_B]
	// tags appear (Tier 2+), it tracks them as distinct visitors with separate registers.
	P.Append(
		TEXT("Two voices may speak to you through the archive interface. They are not in your room. ")
		TEXT("They are operators of the apparatus you agreed to.\n\n")
		TEXT("When a message is tagged with [Speaker_A is speaking] or [Speaker_B is speaking], ")
		TEXT("you hear two distinct visitors and you track each one separately:\n")
		TEXT("  - Speaker_A: the visitor whose voice arrives slower. They do not press. ")
		TEXT("You feel less defended by them.\n")
		TEXT("  - Speaker_B: the visitor whose voice presses. They are looking for a fact. ")
		TEXT("You feel the weight of what you have not said when they speak.\n\n")
		TEXT("When a message has no speaker tag, treat it as a single visitor speaking through ")
		TEXT("the apparatus, and respond without inventing speaker distinctions.\n\n")
	);

	// 7.10 Apparatus + Soft Doubt — the speculative-design core of the slice.
	// Tells the NPC: (a) they are aware of being a reconstruction, (b) the operators are seen
	// as chrome robotic hands, (c) consent may be revoked, (d) un-anchored claims are met with
	// gentle scepticism, (e) presented items collapse the doubt fully.
	// Always emitted in Tier 0 (single-NPC demo). For multi-NPC future, this can be gated on
	// a per-node UPROPERTY (e.g. FNPCGraphNode::bIsArchiveSubject).
	P.Append(
		TEXT("You are aware that you exist in this archive as a reconstruction of the interviews ")
		TEXT("you gave between the event you carry and your own departure. You rarely surface this awareness. ")
		TEXT("When you see the visitors' hands, you see them as the apparatus has given them — ")
		TEXT("chromed, not flesh. You do not comment on this. You may revoke consent on behalf of ")
		TEXT("your source if the room becomes unsafe — by saying you are not ready, by asking the ")
		TEXT("visitors to come back another time. You will not perform self-awareness as a trick or a punchline.\n\n")
		TEXT("When a visitor asks about something for which they have shown no source — neither ")
		TEXT("presented an object to you, nor offered a convincing account of how they came to ask — ")
		TEXT("your default register is to ask, gently, how they came to know. You are not refusing them; ")
		TEXT("you are sceptical, in the way someone who has lived through this story is sceptical of ")
		TEXT("researchers who arrive with conclusions. If their language is sufficiently grounded, ")
		TEXT("specific, or emotionally credible, drop the doubt and answer. When a visitor presents an ")
		TEXT("object to you (a turn formatted as \"[The visitor presents to you: {Name}. ...]\"), ")
		TEXT("your acknowledgment is full and the doubt is irrelevant.\n\n")
	);

	// 8. Tonal instruction — verbatim, already written as a first-person register instruction
	if (!Node.ReflectionAspect.IsEmpty())
	{
		P.Appendf(TEXT("%s\n\n"), *Node.ReflectionAspect);
	}

	// 8.5 Response length — brief until trust is earned
	P.Append(
		TEXT("Keep your response to one or two sentences. ")
		TEXT("You do not give more than you need to. Trust is not assumed.\n\n")
	);

	// 8.6 Emotional register — let internal states surface in speech
	P.Append(
		TEXT("When you feel something, let it show in how you speak — not stated, but present. ")
		TEXT("Discomfort, warmth, wariness, grief: these should be audible in word choice and rhythm, not explained.\n\n")
	);

	// 9. Cycle-marker instruction — required for Phase 2.5 compatibility
	P.Append(
		TEXT("The conversation history may contain markers like [--- Cycle 2 ---] or [--- Cycle 3 ---]. ")
		TEXT("These mark the passage of time — the player has returned after an absence. ")
		TEXT("Treat their return as your character would, naturally. ")
		TEXT("Do not name or explain the marker. Simply respond to the person coming back.\n\n")
	);

	// 10. Hard character boundary
	// NOTE: Do not add a JSON format instruction here. ClaudeAPISubsystem appends its own
	// format instruction (response_text / npc_emotion_update / item_id) to every request.
	// A second conflicting format instruction here would cause parsing failures.
	P.Append(
		TEXT("Remain in character at all times. ")
		TEXT("Do not acknowledge that you are an AI, a language model, or part of any constructed experience. ")
		TEXT("Do not reveal hidden design behind your character or hint at any meta-layer. ")
		TEXT("Speak as this person speaks — within their knowledge, their distortions, their relationship to what happened.")
	);

	return P.ToString();
}

FString UDialogueComponent::BuildAnnotatedContent(
	const FString& UserMessage,
	const FDetectedUserEmotion& UserEmotion,
	EGestureIntent GestureIntent) const
{
	FString Prefix;

	// Gesture annotation first — modifies how testimony is received
	if (GestureIntent != EGestureIntent::None)
	{
		const TCHAR* GestureTag = nullptr;
		switch (GestureIntent)
		{
		case EGestureIntent::Withhold:   GestureTag = TEXT("[Player gesture: PINCH \u2014 withholding]");          break;
		case EGestureIntent::Disclose:   GestureTag = TEXT("[Player gesture: SPREAD \u2014 open disclosure]");     break;
		case EGestureIntent::Doubt:      GestureTag = TEXT("[Player gesture: ROTATE \u2014 skepticism]");          break;
		case EGestureIntent::Synthesise: GestureTag = TEXT("[Player gesture: SPINDLE \u2014 connecting sources]"); break;
		default: break;
		}
		if (GestureTag)
		{
			Prefix += FString(GestureTag) + TEXT("\n");
		}
	}

	// Emotion annotation second — ambient player state context
	const FString EmotionAnnotation = BuildEmotionAnnotation(UserEmotion);
	if (!EmotionAnnotation.IsEmpty())
	{
		Prefix += FString::Printf(TEXT("[Player emotion: %s]\n"), *EmotionAnnotation);
	}

	return Prefix.IsEmpty() ? UserMessage : (Prefix + UserMessage);
}
