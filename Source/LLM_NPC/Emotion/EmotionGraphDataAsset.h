#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "EmotionGraphDataAsset.generated.h"

class UEmotionStateMachine;

/**
 * Configuration for a single node in the emotion graph.
 * Each node represents one emotion type with optional overrides.
 */
USTRUCT(BlueprintType)
struct FLLM_NPC_API FEmotionNodeConfig
{
	GENERATED_BODY()

	/** The emotion type this node represents. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion|Graph")
	EEmotionType EmotionType = EEmotionType::Neutral;

	/** If true, use CustomPAD instead of the canonical PAD for this emotion. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion|Graph")
	bool bUseCustomPAD = false;

	/** Custom PAD override for this emotion node. Only used if bUseCustomPAD is true. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion|Graph", meta = (EditCondition = "bUseCustomPAD"))
	FPADVector CustomPAD;

	/** Custom decay rate override. 0 means use the default from NPCConfig. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion|Graph", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float CustomDecayRate = 0.0f;
};

/**
 * Configuration for a single edge (transition) in the emotion graph.
 * Connects a source emotion to a target emotion with conditions and cost.
 */
USTRUCT(BlueprintType)
struct FLLM_NPC_API FEmotionEdgeConfig
{
	GENERATED_BODY()

	/** The source emotion state this edge originates from. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion|Graph")
	EEmotionType SourceEmotion = EEmotionType::Neutral;

	/** The target emotion state this edge leads to. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion|Graph")
	EEmotionType TargetEmotion = EEmotionType::Neutral;

	/** Minimum signal strength required for this transition. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion|Graph", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float MinInputStrength = 0.1f;

	/** Keywords required in the signal source for this transition. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion|Graph")
	TArray<FString> RequiredKeywords;

	/** Base transition cost for A*-like search. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion|Graph", meta = (ClampMin = "0.0"))
	float Cost = 1.0f;

	/** Cooldown time in seconds between firings of this edge. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion|Graph", meta = (ClampMin = "0.0"))
	float Cooldown = 0.5f;
};

/**
 * Data asset defining the complete emotion graph for an NPC archetype.
 * Serialized as nodes (emotion types) and edges (transition rules).
 *
 * Designed for future UEdGraph visual editor integration:
 * nodes map to graph editor nodes, edges map to connections.
 * At runtime, instantiates an EmotionStateMachine.
 */
UCLASS(BlueprintType)
class FLLM_NPC_API UEmotionGraphDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	/** All emotion nodes in this graph. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Emotion|Graph")
	TArray<FEmotionNodeConfig> Nodes;

	/** All transition edges in this graph. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Emotion|Graph")
	TArray<FEmotionEdgeConfig> Edges;

	/** The default starting emotion for NPCs using this graph. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Emotion|Graph")
	EEmotionType DefaultEmotion = EEmotionType::Neutral;

	/** Default starting intensity. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Emotion|Graph", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float DefaultIntensity = 0.0f;

	/**
	 * Instantiate a fully configured EmotionStateMachine from this data asset.
	 * Creates transition rule UObjects for each edge and configures the initial state.
	 * @param Outer The outer object for the created state machine and rules.
	 * @return A new EmotionStateMachine instance, or nullptr if creation fails.
	 */
	UFUNCTION(BlueprintCallable, Category = "Emotion|Graph")
	UEmotionStateMachine* CreateStateMachine(UObject* Outer) const;
};
