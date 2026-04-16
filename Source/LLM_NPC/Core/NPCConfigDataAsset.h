#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NPCTypes.h"
#include "NPCConfigDataAsset.generated.h"

/**
 * Data asset defining an NPC archetype's personality, system prompt, and configuration.
 * One per NPC type (e.g., DA_NPC_Healer, DA_NPC_Merchant).
 * Designed to be created by designers with zero code changes.
 *
 * This is the primary configuration point for procedural NPC generation:
 * at runtime, fields can be populated from templates and personality parameters.
 */
UCLASS(BlueprintType)
class LLM_NPC_API UNPCConfigDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	// ---- Identity ----

	/** Display name of this NPC archetype. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC|Identity")
	FText NPCName;

	/** Short description of the NPC's role and personality. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC|Identity", meta = (MultiLine = true))
	FText NPCDescription;

	// ---- Claude Prompt Configuration ----

	/**
	 * [SOFT DEPRECATED — Phase 2 will replace with BuildSystemPromptFromGraph()]
	 *
	 * The system prompt sent to Claude API.
	 * Establishes the "Magic Circle" — NPC exists entirely within the fiction.
	 *
	 * In THRESHOLD, system prompts are assembled at runtime from UNPCGraphDataAsset
	 * via DialogueComponent::BuildSystemPromptFromGraph(). This field remains for
	 * backward compatibility with existing test assets and will be removed once
	 * all NPCs are graph-driven.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC|Dialogue", meta = (MultiLine = true))
	FString SystemPrompt;

	/** Maximum number of conversation history messages to include in context. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC|Dialogue", meta = (ClampMin = "1", ClampMax = "50"))
	int32 MaxConversationHistory = 20;

	/** Claude model ID to use (e.g., "claude-sonnet-4-6"). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC|Dialogue")
	FString ClaudeModelID = TEXT("claude-sonnet-4-6");

	/** Max tokens for Claude response. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC|Dialogue", meta = (ClampMin = "64", ClampMax = "4096"))
	int32 MaxResponseTokens = 512;

	// ---- Voice Configuration ----

	/** ElevenLabs voice ID for TTS output. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC|Voice")
	FString ElevenLabsVoiceID;

	/** Voice stability (0.0 to 1.0). Higher = more consistent. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC|Voice", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float VoiceStability = 0.5f;

	/** Voice similarity boost (0.0 to 1.0). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC|Voice", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float VoiceSimilarityBoost = 0.75f;

	// ---- Emotion Configuration ----

	/** Default starting emotion for this NPC. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC|Emotion")
	EEmotionType DefaultEmotion = EEmotionType::Neutral;

	/** Default starting intensity. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC|Emotion", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float DefaultIntensity = 0.0f;

	/**
	 * Emotion decay rate per second. When no input signals arrive,
	 * intensity decays toward 0 at this rate.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC|Emotion", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float EmotionDecayRate = 0.05f;

	/**
	 * Intensity threshold below which the NPC transitions to Neutral.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC|Emotion", meta = (ClampMin = "0.0", ClampMax = "0.5"))
	float NeutralThreshold = 0.1f;

	/**
	 * Per-emotion transition cost multipliers for GOAP-inspired planning.
	 * Higher cost = harder for this NPC to reach that emotion.
	 * E.g., a "stoic" NPC has high cost for Sadness, low cost for Neutral.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC|Emotion")
	TMap<EEmotionType, float> EmotionTransitionCosts;

	// ---- References to Other Data Assets ----

	/**
	 * Social graph data asset for this playthrough.
	 * When set, DialogueComponent::BuildSystemPromptFromGraph() uses this to
	 * assemble the system prompt at runtime, ignoring SystemPrompt above.
	 * Set by NPCGameMode after loading the active UNPCGraphDataAsset.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC|References")
	TSoftObjectPtr<class UNPCGraphDataAsset> GraphDataAsset;

	/** Emotion graph data asset for this NPC's state machine. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC|References")
	TSoftObjectPtr<class UEmotionGraphDataAsset> EmotionGraphAsset;

	/** Inventory data asset for this NPC's hidden items. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC|References")
	TSoftObjectPtr<class UInventoryDataAsset> InventoryAsset;

	/** Blend shape mapping data asset for Metahuman animation. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC|References")
	TSoftObjectPtr<class UBlendShapeMappingDataAsset> BlendShapeMapAsset;

	// ---- UPrimaryDataAsset Interface ----

	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("NPCConfig", GetFName());
	}
};
