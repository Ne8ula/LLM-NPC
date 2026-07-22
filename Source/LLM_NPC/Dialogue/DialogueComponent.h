#pragma once

#include "CoreMinimal.h"
#include "LLM_NPC/Core/NPCSubsystemComponent.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "DialogueComponent.generated.h"

class UClaudeAPISubsystem;
class UNPCConfigDataAsset;
class UNPCGraphDataAsset;
class AInspectableItem;
struct FNPCGraphNode;
struct FClaudeAPIResponse;

/**
 * Memory Archive branch resolution. Single-speaker scope.
 *  Convergent          — trust >= ConvergentTrustThreshold (~0.5). Friend reveals that
 *                        Ashley left and speaks of her departure in general terms.
 *  ConvergentSpecific  — trust >= LocationKeystoneTrustThreshold (~0.7). Friend names
 *                        the specific destination (AshleyDestinationSpecific).
 *  TimeOut             — session timer expires before the gates are met; consent revoked.
 */
UENUM(BlueprintType)
enum class EArchiveBranch : uint8
{
	None                UMETA(DisplayName = "None"),
	Convergent          UMETA(DisplayName = "Convergent Disclosure (Departure Only)"),
	ConvergentSpecific  UMETA(DisplayName = "Convergent Disclosure (Destination Disclosed)"),
	TimeOut             UMETA(DisplayName = "Recursive Silence (Time-Out)")
};

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
 * Delegate fired when the session resolves into a branch. Carries the final NPC line
 * (so the closing card can draw it) and the resolved branch. Listeners: NPCDialogueHUD
 * draws the closing card.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FOnBranchResolved,
	EArchiveBranch, Branch,
	const FString&, FinalLine
);

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
	 * Send a user message to the NPC, including detected user emotion and gesture context.
	 * Assembles the full conversation context and routes through ClaudeAPISubsystem.
	 *
	 * @param UserMessage    The player's text input.
	 * @param UserEmotion    Detected emotion from the player (facial recognition or default).
	 * @param GestureIntent  Meta-communicative intent of any concurrent gesture, mapped from
	 *                       EGestureType by NPCPlayerController. Defaults to None for callers
	 *                       that do not yet pass a gesture (e.g. text input).
	 * @param HeldItem       If the player is currently holding an inspectable item while speaking,
	 *                       it is annotated as "[Currently holding: ...]" before the message so
	 *                       Claude can follow-up on the item. nullptr when not holding anything.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Dialogue")
	void SendUserMessage(const FString& UserMessage, const FDetectedUserEmotion& UserEmotion,
		EGestureIntent GestureIntent = EGestureIntent::None,
		AInspectableItem* HeldItem = nullptr,
		FName SpeakerTag = NAME_None);

	/**
	 * Send a presentation message to the NPC: the player has extended a held item into the NPC's
	 * sightline. Fires a Claude turn with payload describing what the item is and what the NPC
	 * privately knows about it. The NPC's response is generated against the rest of the system
	 * prompt + this turn's anchored context.
	 *
	 * Only the Present verb fires a turn; the Pickup/Inspect verb is silent state-tracking by
	 * the controller and does NOT call this method (per the slice's two-verb design).
	 *
	 * @param Item           The item being presented. Must be non-null and have ItemDisplayName set.
	 * @param UserEmotion    Detected emotion from the player at present time.
	 * @param GestureIntent  Optional gesture intent applied to this turn.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Dialogue")
	void SendObjectPresentMessage(AInspectableItem* Item, const FDetectedUserEmotion& UserEmotion,
		EGestureIntent GestureIntent = EGestureIntent::None,
		FName SpeakerTag = NAME_None);

	/** Clear all conversation history. Also empties InspectedBy / PresentedBy maps. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Dialogue")
	void ClearConversationHistory();

	/**
	 * Speaker ID used for per-speaker memory writes until Tier 2 (acoustic speaker ID) lands.
	 * Returns FName("Speaker_A"). Tier 2 will swap call sites to use the resolved tag from
	 * USpeakerIdentificationComponent.
	 */
	static FName GetDefaultSpeakerID();

	/**
	 * Record that a speaker has inspected (E-key picked up) an item. Idempotent — TSet
	 * dedups. Called from ANPCPlayerController on every successful pickup. Tier 3 gating
	 * logic reads InspectedBy to decide which topics are unlocked for which speaker.
	 */
	void RecordItemInspection(FName ItemID, FName SpeakerID);

	/** ItemID -> set of speaker IDs that have inspected (E) this item. */
	const TMap<FName, TSet<FName>>& GetInspectedBy() const { return InspectedBy; }

	/** ItemID -> set of speaker IDs that have presented (F) this item. */
	const TMap<FName, TSet<FName>>& GetPresentedBy() const { return PresentedBy; }

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

	/** Fired once when the session resolves into a branch (Convergent or TimeOut). */
	UPROPERTY(BlueprintAssignable, Category = "NPC|Dialogue")
	FOnBranchResolved OnBranchResolved;

	/** The NPC configuration data asset providing system prompt and model settings. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Dialogue")
	TObjectPtr<UNPCConfigDataAsset> NPCConfig;

	// ---- Memory Archive — Tier 3 (single-speaker, time-bound) ------------------

	/**
	 * Hard session length in seconds. Timer starts on the first user dispatch.
	 * When elapsed > duration AND no climax has fired, the next NPC turn is
	 * forced into the TimeOut branch (Recursive Silence — Friend revokes consent).
	 * Default 240s = 4 minutes; tune in 180–300s range for the demo.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Archive", meta = (ClampMin = "60.0", ClampMax = "600.0"))
	float SessionDurationSeconds = 240.0f;

	/** Trust threshold (0-1) above which Convergent climax is eligible. Friend speaks of Ashley's departure in general terms. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Archive", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float ConvergentTrustThreshold = 0.5f;

	/** Trust threshold above which the Friend additionally names Ashley's specific destination (AshleyDestinationSpecific). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Archive", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float LocationKeystoneTrustThreshold = 0.7f;

	/** ItemID that must be PRESENTED (F) for Convergent eligibility. Default: "letter". */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Archive")
	FName KeystonePresentItemID = FName(TEXT("letter"));

	/**
	 * ItemIDs that must be INSPECTED (E) for Convergent eligibility.
	 * Default: "phone_book", "old_photograph".
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Archive")
	TArray<FName> KeystoneInspectItemIDs;

	/**
	 * Phrasing the Friend uses when trust is between ConvergentTrustThreshold and
	 * LocationKeystoneTrustThreshold. Speaks to direction / mood / general sense of
	 * Ashley's leaving without naming a city. Editable per playthrough.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Archive", meta = (MultiLine = true))
	FString AshleyDestinationGeneral = TEXT("She boarded a southbound train that night. South — away from the coast, away from her family. I do not know more than that, or I do not say more than that.");

	/**
	 * Specific destination text the Friend names only when trust >= LocationKeystoneTrustThreshold.
	 * Should be one concrete place + one anchoring detail.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Archive", meta = (MultiLine = true))
	FString AshleyDestinationSpecific = TEXT("Kunming. In Yunnan province. She had a friend there from the language school — someone who would not ask questions. A small hostel near Cuihu Lake. She wrote that name down and tore it out of the phone book before she left.");

	/** Compute trust [0,1] for the lone speaker from current InspectedBy / PresentedBy / history. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Archive")
	float ComputeTrust() const;

	/** Time elapsed in the current session, in seconds. 0 until the first dispatch. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Archive")
	float GetSessionElapsedSeconds() const;

	/** Seconds remaining until the time-out branch is forced. Clamped to >= 0. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Archive")
	float GetSessionRemainingSeconds() const;

	/** True once the session has resolved (Convergent or TimeOut fired). No further dispatch. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Archive")
	bool IsSessionResolved() const { return ResolvedBranch != EArchiveBranch::None; }

	/** Returns the resolved branch, or None until OnBranchResolved fires. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Archive")
	EArchiveBranch GetResolvedBranch() const { return ResolvedBranch; }

	/**
	 * Called every tick from ANPCPlayerController. When the session timer expires and no
	 * climax has fired, sends a sentinel "[time has run out in the archive]" turn so the
	 * model returns a TimeOut closing line. No-op once resolved or before first dispatch.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Archive")
	void TickSession();

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
	 * Order: held-item annotation (if any), gesture annotation (if any), emotion annotation
	 * (if confidence >= 0.3), then the raw user message. The held-item annotation lets Claude
	 * recognise that follow-up speech is "about the object I'm carrying."
	 */
	FString BuildAnnotatedContent(const FString& UserMessage, const FDetectedUserEmotion& UserEmotion,
		EGestureIntent GestureIntent, AInspectableItem* HeldItem = nullptr,
		FName SpeakerTag = NAME_None) const;

	/** Build a user emotion annotation string for the system context. */
	FString BuildEmotionAnnotation(const FDetectedUserEmotion& UserEmotion) const;

	/**
	 * Snapshot structured turn context into UMemoryArchiveLogger (Tier 3) just before
	 * dispatch. Values mirror what §7.7 OBSERVED STATE bakes into the prompt, plus the
	 * raw pre-annotation user message. No-op if the logger subsystem is absent/disabled.
	 */
	void LogTurnContextToArchive(const TCHAR* Interaction, const FString& RawMessage,
		const FString& AnnotatedContent, const FDetectedUserEmotion& UserEmotion,
		EGestureIntent GestureIntent, FName SpeakerTag, FName ItemID) const;

	/** Trim conversation history to the configured maximum. */
	void TrimConversationHistory();

	/** Conversation history for this NPC. */
	UPROPERTY()
	TArray<FNPCMessage> ConversationHistory;

	/**
	 * Per-speaker memory: which speakers have inspected (E) which items.
	 * Keyed by AInspectableItem::ItemID, value is the set of speaker tags.
	 * Not a UPROPERTY — UE reflection does not support TMap<FName, TSet<FName>>.
	 * Tier 3 reads from C++ only; editor inspection is not required.
	 */
	TMap<FName, TSet<FName>> InspectedBy;

	/** Per-speaker memory: which speakers have presented (F) which items. Same shape. */
	TMap<FName, TSet<FName>> PresentedBy;

	/** Whether we are currently waiting for a response. */
	bool bWaitingForResponse = false;

	/** Cached reference to the ClaudeAPISubsystem. */
	UPROPERTY()
	TObjectPtr<UClaudeAPISubsystem> CachedClaudeSubsystem;

	// ---- Tier 3 session state (single-speaker) ---------------------------------

	/** World time (seconds) at first user dispatch. -1 until then. */
	double SessionStartWorldTime = -1.0;

	/** Resolved branch — None until Claude returns a non-null branch_resolution OR time forces TimeOut. */
	EArchiveBranch ResolvedBranch = EArchiveBranch::None;

	/** Set when TickSession has dispatched the time-out sentinel turn so we don't spam. */
	bool bTimeOutDispatched = false;

	/** Build the §7.7 OBSERVED STATE block for the current session. */
	FString BuildBranchHintSection(bool& bOutConvergentEligible, bool& bOutLocationEligible, bool& bOutTimeExpired) const;

	/** Build the §7.9 climax instruction block (Convergent / ConvergentSpecific / TimeOut), or empty when neither. */
	FString BuildClimaxInstructionSection(bool bConvergentEligible, bool bLocationEligible, bool bTimeExpired) const;

	/** Map a Claude branch_resolution string to the enum. */
	static EArchiveBranch ParseBranchResolution(const FString& BranchString);
};
