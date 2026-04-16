#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "NPCGraphDataAsset.generated.h"

/**
 * A single NPC node in the THRESHOLD social graph.
 *
 * Each node describes one NPC's personality, knowledge, memory distortions,
 * and their hidden reflection aspect (never shown to the player during play;
 * revealed only in the post-run Phase 2 reveal).
 */
USTRUCT(BlueprintType)
struct LLM_NPC_API FNPCGraphNode
{
	GENERATED_BODY()

	// --- Identity ---

	/** Unique identifier for this NPC — used to look up edges. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC Graph|Identity")
	FName NPCID;

	/** Display name shown in the UI and spoken by the notepad. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC Graph|Identity")
	FString NPCName;

	/** Short role description — "Elder resident", "Childhood friend", etc. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC Graph|Identity")
	FString Role;

	// --- Emotion ---

	/** Starting emotion for this NPC's EmotionComponent. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC Graph|Emotion")
	EEmotionType EmotionBaseline = EEmotionType::Neutral;

	/** Baseline emotion intensity (0.0–1.0). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC Graph|Emotion",
		meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float EmotionBaselineIntensity = 0.4f;

	// --- Memory and Knowledge ---

	/** What this NPC knows about the shared reference point. Injected into system prompt. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC Graph|Memory", meta = (MultiLine = true))
	FString KnowsAboutEvent;

	/** What they refuse to say unprompted. Injected into system prompt as a behavioral constraint. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC Graph|Memory", meta = (MultiLine = true))
	FString WithheldTruth;

	/** Something this NPC has misremembered — not deception, just how memory works. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC Graph|Memory", meta = (MultiLine = true))
	FString MisrememberedDetail;

	/** How this NPC knew the player before departure. Sets relational tone. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC Graph|Memory", meta = (MultiLine = true))
	FString PlayerRelationship;

	// --- Voice ---

	/** ElevenLabs voice ID for this NPC. Overrides NPCConfig value if set. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC Graph|Voice")
	FString ElevenLabsVoiceID;

	// --- Metahuman / Gender Ambiguity ---

	/**
	 * Voice gender for procedural Metahuman assignment: "Male", "Female", "Neutral".
	 * Randomly selected from MetahumanVariantPool at procedural run generation.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC Graph|Metahuman")
	FName VoiceGender;

	/** Pool of Metahuman Blueprint asset names to randomly select from per run. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC Graph|Metahuman")
	TArray<FName> MetahumanVariantPool;

	// --- Hidden Reflection Layer ---
	// These fields are never surfaced in the player-facing UI during play.
	// They are injected into the system prompt as tonal instructions and
	// revealed only in the post-run Phase 2 text block.

	/**
	 * Tonal instruction for BuildSystemPromptFromGraph().
	 * Shapes how this NPC speaks about memory and departure without stating the meta-design.
	 * E.g.: "You have made a kind of peace with complicated things by finding the simpler
	 * feeling inside them. This is your register. You do not name this."
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC Graph|Hidden Layer", meta = (MultiLine = true))
	FString ReflectionAspect;

	/**
	 * The "The One Who..." label for this NPC.
	 * Assembled into UNPCGraphDataAsset::ReflectionReveal for post-run Phase 2 display.
	 * Never shown to the player during play.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC Graph|Hidden Layer")
	FString HiddenTitle;
};

/** A directed relationship edge between two NPC nodes in the social graph. */
USTRUCT(BlueprintType)
struct LLM_NPC_API FNPCGraphEdge
{
	GENERATED_BODY()

	/** Source NPC. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC Graph")
	FName FromNPCID;

	/** Target NPC. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC Graph")
	FName ToNPCID;

	/**
	 * Plain-language description of this relationship, from FromNPC's perspective.
	 * E.g.: "She raised him. She blames herself."
	 * Injected into the system prompt of FromNPC.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC Graph", meta = (MultiLine = true))
	FString RelationshipDescription;

	/** How much FromNPC trusts ToNPC (0.0 = distrust, 1.0 = full trust). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC Graph",
		meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float TrustLevel = 0.5f;
};

/**
 * Data asset storing the complete social graph for one THRESHOLD playthrough.
 *
 * Handcrafted for the vertical slice (DA_Graph_ThresholdDefault).
 * Procedurally generated via ClaudeAPISubsystem for subsequent runs from Graph Studio.
 *
 * Consumed by DialogueComponent::BuildSystemPromptFromGraph() to assemble
 * each NPC's system prompt at runtime — no hardcoded system prompts needed.
 *
 * Post-run reveal is two-phase:
 *   Phase 1: GroundTruth — factual texture of what each NPC actually carries.
 *   Phase 2: ReflectionReveal — the hidden "The One Who..." titles assembled from node HiddenTitle fields.
 */
UCLASS(BlueprintType)
class LLM_NPC_API UNPCGraphDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	// --- Shared Reference Point ---

	/** Category of shared reference point: "emigration", "disappearance", "decision", etc. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Graph|Event")
	FString EventType;

	/**
	 * Plain-language description of the shared reference point.
	 * Injected into each NPC's system prompt as shared context.
	 * Should be abstract — a weight, not a cause-and-effect event.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Graph|Event", meta = (MultiLine = true))
	FString EventSummary;

	// --- Post-Run Reveal ---

	/**
	 * Phase 1 reveal — factual texture.
	 * What each NPC actually carries underneath what they say.
	 * Shown after the compound's Return Statement response.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Graph|Reveal", meta = (MultiLine = true))
	FString GroundTruth;

	/**
	 * Phase 2 reveal — the hidden "The One Who..." titles.
	 * Assembled from all node HiddenTitle fields by BuildReflectionReveal().
	 * Shown 3s after Phase 1, with no further explanation.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Graph|Reveal", meta = (MultiLine = true))
	FString ReflectionReveal;

	// --- Nodes and Edges ---

	/** All NPC nodes in this social graph. Order determines default spawn order. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Graph")
	TArray<FNPCGraphNode> Nodes;

	/** All directed relationship edges between NPC nodes. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Graph")
	TArray<FNPCGraphEdge> Edges;

	// --- Utility ---

	/**
	 * Find a node by NPCID.
	 * Returns nullptr if NPCID is not found in Nodes.
	 * C++ only — raw pointer return cannot be Blueprint-exposed.
	 */
	const FNPCGraphNode* FindNode(FName NPCID) const;

	/**
	 * Assemble ReflectionReveal from all node HiddenTitle fields.
	 * Call once after populating Nodes (either at asset save time or after procedural generation).
	 * Overwrites any existing ReflectionReveal value.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC Graph")
	void BuildReflectionReveal();
};
