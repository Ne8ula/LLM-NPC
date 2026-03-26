#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "BlendShapeMappingDataAsset.generated.h"

/**
 * A single blend shape target: the name of the morph target and the value it
 * should be driven toward (0-1).
 */
USTRUCT(BlueprintType)
struct LLM_NPC_API FEmotionBlendShapeTarget
{
	GENERATED_BODY()

	/** Name of the morph target on the skeletal mesh (e.g. "browInnerUp"). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation|BlendShape")
	FName BlendShapeName;

	/** Target value to drive the morph target toward (0.0 - 1.0). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation|BlendShape",
		meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float TargetValue = 0.0f;
};

/**
 * Maps an emotion type and intensity range to a set of blend shape targets.
 * Multiple mappings can exist for the same emotion at different intensity bands.
 */
USTRUCT(BlueprintType)
struct LLM_NPC_API FEmotionBlendShapeMapping
{
	GENERATED_BODY()

	/** The emotion type this mapping applies to. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation|BlendShape")
	EEmotionType EmotionType = EEmotionType::Neutral;

	/** Minimum intensity for this mapping to activate (inclusive). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation|BlendShape",
		meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float MinIntensity = 0.0f;

	/** Maximum intensity for this mapping to activate (inclusive). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation|BlendShape",
		meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float MaxIntensity = 1.0f;

	/** Blend shape targets to drive when this mapping is active. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation|BlendShape")
	TArray<FEmotionBlendShapeTarget> BlendShapeTargets;
};

/**
 * Data asset that maps NPC emotion states to Metahuman facial blend shapes.
 * Designers configure one per character or share across archetypes with similar rigs.
 */
UCLASS(BlueprintType)
class LLM_NPC_API UBlendShapeMappingDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	/** All emotion-to-blend-shape mappings. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|BlendShape")
	TArray<FEmotionBlendShapeMapping> Mappings;

	/**
	 * Find the best matching mapping for the given emotion state and return its
	 * blend shape targets.  Returns an empty array if no mapping matches.
	 */
	TArray<FEmotionBlendShapeTarget> GetTargetsForState(const FEmotionState& State) const;
};
