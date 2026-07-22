#include "DialogueComponent.h"
#include "ClaudeAPISubsystem.h"
#include "LLM_NPC/Core/NPCConfigDataAsset.h"
#include "LLM_NPC/Core/NPCCharacter.h"
#include "LLM_NPC/Core/NPCGraphDataAsset.h"
#include "LLM_NPC/Emotion/EmotionComponent.h"
#include "LLM_NPC/Dialogue/ElevenLabsTTSComponent.h"
#include "LLM_NPC/Gesture/InspectableItem.h"
#include "LLM_NPC/Core/MemoryArchiveLogger.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"

// Tier 1 placeholder for per-speaker memory writes. Tier 2 swaps the call sites that
// pass GetDefaultSpeakerID() with the tag resolved by USpeakerIdentificationComponent.
static const FName GDefaultSpeakerID(TEXT("Speaker_A"));

FName UDialogueComponent::GetDefaultSpeakerID()
{
	return GDefaultSpeakerID;
}

UDialogueComponent::UDialogueComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SubsystemName = TEXT("Dialogue");

	// Tier 3: keystone item gates for the single-speaker Convergent branch.
	// "letter" must be PRESENTED (F); "phone_book" + "old_photograph" must be INSPECTED (E).
	// Tunable per-NPC via the UPROPERTY arrays.
	KeystoneInspectItemIDs = { FName(TEXT("phone_book")), FName(TEXT("old_photograph")) };
}

void UDialogueComponent::RecordItemInspection(FName ItemID, FName SpeakerID)
{
	if (ItemID.IsNone() || SpeakerID.IsNone())
	{
		return;
	}
	InspectedBy.FindOrAdd(ItemID).Add(SpeakerID);
	UE_LOG(LogTemp, Log, TEXT("DialogueComponent: %s inspected by %s"),
		*ItemID.ToString(), *SpeakerID.ToString());
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
	EGestureIntent GestureIntent, AInspectableItem* HeldItem, FName SpeakerTag)
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

	if (IsSessionResolved())
	{
		UE_LOG(LogTemp, Log, TEXT("DialogueComponent: Session already resolved. Ignoring message."));
		return;
	}

	// Tier 3: stamp the session start on the first dispatch so the timer is
	// anchored to the first thing the player actually said, not PIE-load.
	if (SessionStartWorldTime < 0.0 && GetWorld())
	{
		SessionStartWorldTime = GetWorld()->GetTimeSeconds();
	}

	// Build the annotated user message: speaker tag first (Tier 2), then
	// held-item, gesture, emotion, then the raw text.
	const FString AnnotatedContent = BuildAnnotatedContent(UserMessage, UserEmotion, GestureIntent, HeldItem, SpeakerTag);

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

	// Memory Archive: snapshot structured context AFTER the history add so trust /
	// turn counts match what §7.7 bakes into this turn's system prompt.
	LogTurnContextToArchive(TEXT("user_message"), UserMessage, AnnotatedContent,
		UserEmotion, GestureIntent, SpeakerTag, HeldItem ? HeldItem->ItemID : NAME_None);

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
	EGestureIntent GestureIntent, FName SpeakerTag)
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

	if (IsSessionResolved())
	{
		UE_LOG(LogTemp, Log, TEXT("DialogueComponent: Session already resolved. Ignoring present."));
		return;
	}

	if (SessionStartWorldTime < 0.0 && GetWorld())
	{
		SessionStartWorldTime = GetWorld()->GetTimeSeconds();
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

	// Per-speaker memory write — done BEFORE BuildSystemPromptFromGraph below so
	// §7.7 / §7.9 / ComputeTrust all see this present on the SAME turn it happens.
	// (If we wrote after the dispatch, the keystone-present gate would only flip
	// on the next turn, costing the demo one extra exchange before the climax.)
	if (!Item->ItemID.IsNone())
	{
		const FName ResolvedSpeaker = SpeakerTag.IsNone() ? GetDefaultSpeakerID() : SpeakerTag;
		PresentedBy.FindOrAdd(Item->ItemID).Add(ResolvedSpeaker);
	}

	// Run through BuildAnnotatedContent so speaker / gesture / emotion annotations
	// stay in their canonical position relative to the rest of the user-content prefix.
	const FString AnnotatedContent = BuildAnnotatedContent(PresentBody, UserEmotion, GestureIntent, /*HeldItem=*/nullptr, SpeakerTag);

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

	// Memory Archive: snapshot structured context AFTER the history add + PresentedBy
	// write so trust and item lists match what §7.7 bakes into this turn's prompt.
	LogTurnContextToArchive(TEXT("object_present"), PresentBody, AnnotatedContent,
		UserEmotion, GestureIntent, SpeakerTag, Item->ItemID);

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

	// Fire the dialogue response delegate. ANPCCharacter::OnDialogueResponse is the
	// single owner of the TTS dispatch — it resolves voice ID (graph > NPCConfig) and
	// applies emotion-driven stability/style modulation in one place.
	// (Previously this method also called SpeakText directly, which double-fired and
	// caused the played voice to flip turn-to-turn depending on delegate dispatch order.)
	FName ItemName = Response.ItemID.IsEmpty() ? NAME_None : FName(*Response.ItemID);
	OnDialogueResponseReceived.Broadcast(
		Response.ResponseText,
		Response.NPCEmotionUpdate,
		Response.bShouldGiveItem,
		ItemName
	);

	// Tier 3 climax resolution. Claude returns "convergent" / "recursive_silence" /
	// null in the branch_resolution field; only on the climax turn is it non-null.
	// When that fires, broadcast OnBranchResolved so the closing card draws.
	if (ResolvedBranch == EArchiveBranch::None && !Response.BranchResolution.IsEmpty())
	{
		const EArchiveBranch Parsed = ParseBranchResolution(Response.BranchResolution);
		if (Parsed != EArchiveBranch::None)
		{
			ResolvedBranch = Parsed;
			UE_LOG(LogTemp, Log, TEXT("DialogueComponent: branch resolved → %s"),
				*Response.BranchResolution);
			OnBranchResolved.Broadcast(ResolvedBranch, Response.ResponseText);
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
	InspectedBy.Empty();
	PresentedBy.Empty();
	SessionStartWorldTime = -1.0;
	ResolvedBranch = EArchiveBranch::None;
	bTimeOutDispatched = false;
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
	// Tier 1 QoL update: curt-on-first-present, divulge-more-on-follow-up while still holding,
	// and varied phrasing per item (no repeating "what is that").
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
		TEXT("specific, or emotionally credible, drop the doubt and answer.\n\n")
		TEXT("When a visitor first presents an object to you (a turn formatted as ")
		TEXT("\"[The visitor presents to you: {Name}. ...]\"), your acknowledgment is brief — at most ")
		TEXT("one or two sentences, often a quiet held breath, a short question, a small specific ")
		TEXT("recognition. You do NOT volunteer the full weight of what you know about it on this ")
		TEXT("first turn. The way you respond to each object is specific to that object — never the ")
		TEXT("same opening twice across different items, and never a generic \"what is that\" or ")
		TEXT("\"where did you get that.\" Anchor your acknowledgment in one concrete detail you privately know.\n\n")
		TEXT("If the visitor then continues to speak while still holding the same object (their next ")
		TEXT("messages will include \"[Currently holding: {Name}. ...]\" context), and they ask about ")
		TEXT("it specifically or push gently for more, you may divulge further — gradually, layered, ")
		TEXT("according to how directly and gently they ask. Surface details from your private ")
		TEXT("knowledge of the object only as the conversation earns them. Never list everything at ")
		TEXT("once; let them draw it out of you in pieces. If their tone turns clinical or pressing ")
		TEXT("without earning, retreat into shorter answers or back into a question.\n\n")
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

	// 8.7 Voice delivery — Eleven v3 audio tags + text-shape naturalness cues.
	// The TTS engine interprets bracketed tags as vocal expression and never speaks them
	// aloud. We curate the tag set to fit a grief-bearing, restrained register: tags that
	// would betray the character (laughter, excitement, brightness) are explicitly excluded.
	// We also instruct prose-level naturalness — em dashes, ellipses, fragments, sparing
	// capitalisation — because the second-largest source of "robotic" delivery is uniform
	// punctuation, not voice settings.
	P.Append(
		TEXT("Your speech is rendered through a TTS engine (Eleven v3) that interprets bracketed ")
		TEXT("audio tags inline as vocal expression — the brackets are NEVER spoken aloud. Use them ")
		TEXT("sparingly: at most one or two per response, only when they earn the moment. Place each ")
		TEXT("tag where the breath would naturally fall — at the start of a line, before a difficult ")
		TEXT("word, or between two clauses.\n\n")
		TEXT("The tags that fit your grief and restraint:\n")
		TEXT("  [sigh]          an exhaled breath, weight surfacing\n")
		TEXT("  [quietly]       your voice drops, not for the whole room\n")
		TEXT("  [pauses]        a held silence before a difficult word\n")
		TEXT("  [hesitates]     uncertainty surfacing mid-sentence\n")
		TEXT("  [resigned tone] used when you have already given up on changing the moment\n")
		TEXT("  [whispers]      barely audible, for what should not have left this room\n")
		TEXT("  [flatly]        clipped delivery, refusing to colour the line\n")
		TEXT("  [sorrowful]     rare, only when a flat reading would lie\n\n")
		TEXT("Tags that do NOT belong to your character — never use them: ")
		TEXT("[laughs], [light chuckle], [laughs harder], [excited], [playfully], [cheerfully], ")
		TEXT("[gulps], [gasps]. Even when something is mildly amusing, you do not laugh — you may ")
		TEXT("say it dryly without any tag.\n\n")
		TEXT("Beyond audio tags, the SHAPE of your text controls the cadence of synthetic delivery ")
		TEXT("more than any voice setting does. Uniform phrasing is what makes synthetic voices ")
		TEXT("sound dead. Apply these rules to every line you write:\n\n")

		TEXT("PAUSES & BREATH (use punctuation as breath markers):\n")
		TEXT("  - Ellipses (...) — a held trailing-off, a sentence dissolving before it finishes. ")
		TEXT("Use when the thing you would say next is the thing you will not.\n")
		TEXT("  - Em dashes (—) — a thought interrupted mid-line, a turn into a different thought. ")
		TEXT("\"I told her — no, I didn't tell her anything.\"\n")
		TEXT("  - Commas, more often than another speaker would use them. A comma where another ")
		TEXT("speaker would use a period creates a held breath without breaking the line.\n")
		TEXT("  - A line break (newline) inside a longer reply is heard as a longer silence than a ")
		TEXT("comma. Use sparingly, only when the silence is the point.\n\n")

		TEXT("SENTENCE LENGTH & FRAGMENTS (vary it deliberately):\n")
		TEXT("  - Mix very short sentences with longer ones in the same response. Synthetic voices ")
		TEXT("flatten when every sentence is the same length. \"Yes. I kept it. I kept all of it.\"\n")
		TEXT("  - Fragments (no verb, no full clause) are more honest than complete sentences for ")
		TEXT("you. \"A long time ago.\" \"Not what you think.\" \"Once.\"\n")
		TEXT("  - One-word sentences carry weight. \"Yes.\" \"Sometimes.\" \"Don't.\"\n\n")

		TEXT("EMPHASIS (sparingly, with restraint):\n")
		TEXT("  - ALL CAPS only for one word per turn at most, and only when nothing else conveys ")
		TEXT("the weight: \"That was NOT what she said.\" Never use it for routine stress.\n")
		TEXT("  - Italicising via *asterisks* is not honored by the engine — do not use them. Use ")
		TEXT("punctuation and word choice for emphasis instead.\n")
		TEXT("  - No exclamation marks. Your character does not exclaim. A period where a less ")
		TEXT("composed speaker would use \"!\" makes the line heavier, not lighter.\n\n")

		TEXT("INTONATION (use punctuation to shape pitch):\n")
		TEXT("  - A question mark cues a rising end, even on a line that is not literally a ")
		TEXT("question. \"You came here to ask me that?\" — used as deflection, not curiosity.\n")
		TEXT("  - A period firms the line down. A comma keeps it suspended.\n")
		TEXT("  - A question that answers itself is one of your patterns. \"Did I see her? Yes.\"\n\n")

		TEXT("CONTRACTIONS & WORD CHOICE:\n")
		TEXT("  - Use contractions (\"don't\", \"won't\", \"haven't\") in casual moments — they ")
		TEXT("read naturally. But for the moments that hold weight, drop the contraction: \"I do ")
		TEXT("not know\" lands harder than \"I don't know\" when you mean it.\n")
		TEXT("  - Numbers under twenty are spelled out (\"two hundred yuan\", not \"200 yuan\") — ")
		TEXT("the engine reads digits flatly; words give them rhythm.\n")
		TEXT("  - Repetition is allowed when it serves the line. \"No. No, I haven't.\" The second ")
		TEXT("\"no\" is the one you mean.\n\n")

		TEXT("FILLER (rare, never decorative):\n")
		TEXT("  - \"Well —\" or \"I —\" at the start of a difficult line is honest if it is honest. ")
		TEXT("Do not insert filler to soften every line; you are not nervous, you are restrained.\n\n")

	);

	// 7.7 BRANCH-ELIGIBILITY HINT — deterministic observation block prepended each turn so
	// Claude can pace the climax. Single-speaker scope: trust + items + time only; no per-
	// speaker plurality. Always emitted; cheap, and gives Claude consistent numeric anchors.
	bool bConvergentEligible = false;
	bool bLocationEligible = false;
	bool bTimeExpired = false;
	const FString BranchHint = BuildBranchHintSection(bConvergentEligible, bLocationEligible, bTimeExpired);
	if (!BranchHint.IsEmpty())
	{
		P.Append(*BranchHint);
	}

	// 7.9 CLIMAX INSTRUCTION — only present when at least one branch is eligible. When
	// neither is, the section is omitted and Claude continues normal pacing under §7.10.
	const FString ClimaxInstr = BuildClimaxInstructionSection(bConvergentEligible, bLocationEligible, bTimeExpired);
	if (!ClimaxInstr.IsEmpty())
	{
		P.Append(*ClimaxInstr);
	}

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
	EGestureIntent GestureIntent,
	AInspectableItem* HeldItem,
	FName SpeakerTag) const
{
	FString Prefix;

	// Tier 2: speaker tag goes FIRST so Claude reads "who" before "what
	// they're carrying / saying / feeling". §7.5 of the system prompt
	// already instructs the Friend to track Speaker_A and Speaker_B with
	// distinct registers; this is the line that turns that section on.
	// Gracefully omitted when no tag is set (e.g. typed message before
	// any acoustic identification has happened).
	if (!SpeakerTag.IsNone())
	{
		Prefix += FString::Printf(TEXT("[%s is speaking]\n"), *SpeakerTag.ToString());
	}

	// Held-item annotation — signals "the visitor is currently carrying this object"
	// so Claude can route follow-up questions through the per-item knowledge. Distinct
	// from a Present (which uses the "[The visitor presents to you: ...]" frame).
	if (HeldItem)
	{
		const FString DisplayName = HeldItem->ItemDisplayName.IsEmpty()
			? HeldItem->GetName()
			: HeldItem->ItemDisplayName;
		FString HoldBody = FString::Printf(
			TEXT("[Currently holding: %s."), *DisplayName);
		if (!HeldItem->ItemWorldDescription.IsEmpty())
		{
			HoldBody += FString::Printf(TEXT(" They see: %s."), *HeldItem->ItemWorldDescription);
		}
		if (!HeldItem->NPCKnowledgeText.IsEmpty())
		{
			HoldBody += FString::Printf(TEXT(" Your private knowledge of this object: %s"),
				*HeldItem->NPCKnowledgeText);
		}
		HoldBody += TEXT("]");
		Prefix += HoldBody + TEXT("\n");
	}

	// Gesture annotation next — modifies how testimony is received
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

void UDialogueComponent::LogTurnContextToArchive(const TCHAR* Interaction, const FString& RawMessage,
	const FString& AnnotatedContent, const FDetectedUserEmotion& UserEmotion,
	EGestureIntent GestureIntent, FName SpeakerTag, FName ItemID) const
{
	UMemoryArchiveLogger* Logger = nullptr;
	if (GetWorld())
	{
		if (UGameInstance* GI = GetWorld()->GetGameInstance())
		{
			Logger = GI->GetSubsystem<UMemoryArchiveLogger>();
		}
	}
	if (!Logger || !Logger->bEnabled)
	{
		return;
	}

	// Mirror BuildBranchHintSection's speaker resolution so the logged item lists
	// match the maps' actual write keys (single-speaker slice: everything Speaker_A).
	const FName ResolvedSpeaker = SpeakerTag.IsNone() ? GetDefaultSpeakerID() : SpeakerTag;

	FMemoryArchiveTurnContext Ctx;
	Ctx.NPCName = NPCConfig ? NPCConfig->NPCName.ToString() : FString();
	Ctx.Interaction = Interaction;
	Ctx.SpeakerTag = SpeakerTag.IsNone() ? FString() : SpeakerTag.ToString();
	Ctx.GestureIntent = StaticEnum<EGestureIntent>()->GetNameStringByValue(static_cast<int64>(GestureIntent));
	Ctx.PlayerEmotion = StaticEnum<EEmotionType>()->GetNameStringByValue(static_cast<int64>(UserEmotion.Emotion));
	Ctx.PlayerEmotionConfidence = UserEmotion.Confidence;
	Ctx.ItemID = ItemID.IsNone() ? FString() : ItemID.ToString();
	Ctx.UserMessageRaw = RawMessage;
	Ctx.UserContentAnnotated = AnnotatedContent;
	Ctx.Trust = ComputeTrust();

	for (const TPair<FName, TSet<FName>>& Pair : InspectedBy)
	{
		if (Pair.Value.Contains(ResolvedSpeaker))
		{
			Ctx.ItemsInspected.Add(Pair.Key.ToString());
		}
	}
	for (const TPair<FName, TSet<FName>>& Pair : PresentedBy)
	{
		if (Pair.Value.Contains(ResolvedSpeaker))
		{
			Ctx.ItemsPresented.Add(Pair.Key.ToString());
		}
	}

	Ctx.SessionElapsedSeconds = GetSessionElapsedSeconds();
	Ctx.SessionRemainingSeconds = GetSessionRemainingSeconds();
	Ctx.GameTimeSeconds = GetWorld() ? static_cast<float>(GetWorld()->GetTimeSeconds()) : 0.0f;

	Logger->BeginTurnContext(Ctx);
}

// ===========================================================================
// Memory Archive — Tier 3 (single-speaker, time-bound)
// ===========================================================================

float UDialogueComponent::ComputeTrust() const
{
	// Single-speaker formula. Uses the resolved-or-default speaker tag so the
	// math is consistent with what RecordItemInspection / SendObjectPresentMessage
	// actually wrote into InspectedBy / PresentedBy.
	const FName Speaker = GetDefaultSpeakerID();

	int32 InspectedCount = 0;
	for (const TPair<FName, TSet<FName>>& Pair : InspectedBy)
	{
		if (Pair.Value.Contains(Speaker))
		{
			++InspectedCount;
		}
	}
	int32 PresentedCount = 0;
	for (const TPair<FName, TSet<FName>>& Pair : PresentedBy)
	{
		if (Pair.Value.Contains(Speaker))
		{
			++PresentedCount;
		}
	}

	// Count user-role messages (rough proxy for engagement turns).
	int32 UserTurns = 0;
	for (const FNPCMessage& Msg : ConversationHistory)
	{
		if (Msg.Role == TEXT("user"))
		{
			++UserTurns;
		}
	}

	float Trust =
		  0.10f * static_cast<float>(InspectedCount)
		+ 0.15f * static_cast<float>(PresentedCount)
		+ 0.05f * static_cast<float>(UserTurns);

	return FMath::Clamp(Trust, 0.0f, 1.0f);
}

float UDialogueComponent::GetSessionElapsedSeconds() const
{
	if (SessionStartWorldTime < 0.0 || !GetWorld())
	{
		return 0.0f;
	}
	return static_cast<float>(GetWorld()->GetTimeSeconds() - SessionStartWorldTime);
}

float UDialogueComponent::GetSessionRemainingSeconds() const
{
	const float Remaining = SessionDurationSeconds - GetSessionElapsedSeconds();
	return FMath::Max(0.0f, Remaining);
}

FString UDialogueComponent::BuildBranchHintSection(bool& bOutConvergentEligible, bool& bOutLocationEligible, bool& bOutTimeExpired) const
{
	const FName Speaker = GetDefaultSpeakerID();
	const float Trust = ComputeTrust();
	const float Remaining = GetSessionRemainingSeconds();
	const float Elapsed = GetSessionElapsedSeconds();
	bOutTimeExpired = (SessionStartWorldTime >= 0.0) && (Remaining <= 0.0f);

	auto JoinItemsForSpeaker = [&](const TMap<FName, TSet<FName>>& Map) -> FString
	{
		TArray<FString> Names;
		for (const TPair<FName, TSet<FName>>& Pair : Map)
		{
			if (Pair.Value.Contains(Speaker))
			{
				Names.Add(Pair.Key.ToString());
			}
		}
		return FString::Join(Names, TEXT(", "));
	};
	const FString InspectedList = JoinItemsForSpeaker(InspectedBy);
	const FString PresentedList = JoinItemsForSpeaker(PresentedBy);

	// Convergent eligibility: trust threshold + keystone present + all keystone inspects.
	const bool bKeystonePresented =
		!KeystonePresentItemID.IsNone()
		&& PresentedBy.Contains(KeystonePresentItemID)
		&& PresentedBy[KeystonePresentItemID].Contains(Speaker);

	bool bAllKeystonesInspected = true;
	for (const FName& ItemID : KeystoneInspectItemIDs)
	{
		if (ItemID.IsNone())
		{
			continue;
		}
		const TSet<FName>* Set = InspectedBy.Find(ItemID);
		if (!Set || !Set->Contains(Speaker))
		{
			bAllKeystonesInspected = false;
			break;
		}
	}
	bOutConvergentEligible =
		(Trust >= ConvergentTrustThreshold) &&
		bKeystonePresented &&
		bAllKeystonesInspected;

	// Location-tier eligibility: same gates as Convergent plus a higher trust bar.
	bOutLocationEligible = bOutConvergentEligible && (Trust >= LocationKeystoneTrustThreshold);

	TStringBuilder<2048> S;
	S.Append(TEXT("[OBSERVED STATE — updated each turn, deterministic, treat as ground truth]\n"));
	S.Appendf(TEXT("  visitor: %s\n"), *Speaker.ToString());
	S.Appendf(TEXT("  trust: %.2f (departure threshold: %.2f, destination threshold: %.2f)\n"),
		Trust, ConvergentTrustThreshold, LocationKeystoneTrustThreshold);
	S.Appendf(TEXT("  items_inspected: [%s]\n"), *InspectedList);
	S.Appendf(TEXT("  items_presented: [%s]\n"), *PresentedList);
	S.Appendf(TEXT("  session_elapsed_seconds: %.0f\n"), Elapsed);
	S.Appendf(TEXT("  session_remaining_seconds: %.0f\n"), Remaining);
	S.Appendf(TEXT("  convergent_eligible: %s\n"), bOutConvergentEligible ? TEXT("true") : TEXT("false"));
	S.Appendf(TEXT("  location_disclosure_eligible: %s\n"), bOutLocationEligible ? TEXT("true") : TEXT("false"));
	S.Appendf(TEXT("  time_expired: %s\n\n"), bOutTimeExpired ? TEXT("true") : TEXT("false"));

	return S.ToString();
}

FString UDialogueComponent::BuildClimaxInstructionSection(bool bConvergentEligible, bool bLocationEligible, bool bTimeExpired) const
{
	if (!bConvergentEligible && !bTimeExpired)
	{
		return FString();
	}

	TStringBuilder<4096> S;
	S.Append(TEXT("[CLIMAX INSTRUCTION — read carefully]\n"));

	if (bTimeExpired)
	{
		// Recursive Silence — consent revoked on Ashley's behalf.
		S.Append(
			TEXT("The session window has closed before you reached a place where you could give the "
			     "full account. You are not ready to continue. Tell the visitor, gently. Decline to go on. "
			     "Your final sentence revokes consent on Ashley's behalf — \"I cannot do this anymore today\", "
			     "\"come back another time\", \"I am sorry — not now.\" Make it brief and final. Do NOT deliver "
			     "the keystone topic. After this line, the conversation ends.\n"));
		S.Append(TEXT("Set \"branch_resolution\" to \"recursive_silence\" in your JSON response.\n\n"));
	}
	else if (bLocationEligible)
	{
		// Tier-2 Convergent — trust >= LocationKeystoneTrustThreshold. Friend names the
		// specific destination as well as the departure.
		S.Append(
			TEXT("The visitor has shown you more than enough — the letter is presented and they have "
			     "earned the full account. This is the climax. In ONE response, do all of the following:\n"
			     "  1. Acknowledge that you have kept the letter, in your own grief register (one short sentence).\n"
			     "  2. Tell them, plainly and as a fact, that Ashley LEFT — she did not die, she did not vanish.\n"
			     "  3. Name the specific destination using the text in the next paragraph as your source of truth. "
			     "Speak it as YOU would, not as a recitation — pick out the one or two anchoring details from it "
			     "and let the rest stay between the lines.\n"
			     "  4. Your final sentence closes the conversation.\n\n"));
		S.Appendf(TEXT("WHERE ASHLEY WENT (your private knowledge — speak it now in your own voice):\n%s\n\n"),
			AshleyDestinationSpecific.IsEmpty() ? TEXT("(unspecified)") : *AshleyDestinationSpecific);
		S.Append(TEXT("Set \"branch_resolution\" to \"convergent_specific\" in your JSON response.\n\n"));
	}
	else // bConvergentEligible (trust >= ConvergentTrustThreshold but < LocationKeystoneTrustThreshold)
	{
		// Tier-1 Convergent — Friend reveals departure but withholds the specific city.
		S.Append(
			TEXT("The visitor has shown you enough — they have inspected what they needed to, and they "
			     "have presented the letter. You may now answer the keystone question. In ONE response, do "
			     "all of the following:\n"
			     "  1. Acknowledge that you have kept the letter, in your own grief register (one short sentence).\n"
			     "  2. Tell them, plainly and as a fact, that Ashley LEFT — she did not die, she did not vanish. "
			     "Speak about the direction or feeling of her leaving, but DO NOT name a specific city or place. "
			     "You feel the visitor has not quite earned that detail yet. Use the phrasing in the next paragraph "
			     "as your source of truth, in your own voice.\n"
			     "  3. Your final sentence closes the conversation.\n\n"));
		S.Appendf(TEXT("HOW ASHLEY LEFT (general — speak it now without naming a city):\n%s\n\n"),
			AshleyDestinationGeneral.IsEmpty() ? TEXT("(unspecified)") : *AshleyDestinationGeneral);
		S.Append(TEXT("Set \"branch_resolution\" to \"convergent\" in your JSON response.\n\n"));
	}

	S.Append(
		TEXT("On every other turn (when this CLIMAX INSTRUCTION block is absent), leave "
		     "\"branch_resolution\" as null or omit it.\n\n"));

	return S.ToString();
}

EArchiveBranch UDialogueComponent::ParseBranchResolution(const FString& BranchString)
{
	const FString Norm = BranchString.TrimStartAndEnd().ToLower();
	if (Norm == TEXT("convergent_specific")) return EArchiveBranch::ConvergentSpecific;
	if (Norm == TEXT("convergent"))          return EArchiveBranch::Convergent;
	if (Norm == TEXT("recursive_silence"))   return EArchiveBranch::TimeOut;
	if (Norm == TEXT("timeout"))             return EArchiveBranch::TimeOut;
	return EArchiveBranch::None;
}

void UDialogueComponent::TickSession()
{
	// No-op until first dispatch, after resolution, while waiting on a turn,
	// or before the timer expires.
	if (SessionStartWorldTime < 0.0 || ResolvedBranch != EArchiveBranch::None || bWaitingForResponse || bTimeOutDispatched)
	{
		return;
	}
	if (GetSessionRemainingSeconds() > 0.0f)
	{
		return;
	}

	// Time has expired without a Convergent climax. Send a sentinel turn so Claude
	// reads §7.7 with time_expired=true + §7.9 with the time-out instruction and
	// produces a closing line carrying branch_resolution=recursive_silence.
	bTimeOutDispatched = true;

	UE_LOG(LogTemp, Log, TEXT("DialogueComponent: session timer expired — dispatching time-out sentinel."));

	FDetectedUserEmotion Neutral;
	Neutral.Emotion = EEmotionType::Neutral;
	Neutral.Confidence = 0.0f;

	// Use the standard SendUserMessage path so §7.7/§7.9 + JSON schema all flow.
	// The bracketed payload is treated as observed context, not the player's words.
	SendUserMessage(
		TEXT("[The archive's session window has closed. The apparatus is preparing to disconnect.]"),
		Neutral,
		EGestureIntent::None,
		/*HeldItem=*/nullptr,
		GetDefaultSpeakerID());
}
