#pragma once

#include "CoreMinimal.h"
#include "LLM_NPC/Core/NPCSubsystemComponent.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "BlendShapeMappingDataAsset.h"
#include "MetahumanAnimComponent.generated.h"

/**
 * Drives Metahuman facial blend shapes based on the NPC's current emotional state.
 *
 * Each tick the component reads the current FEmotionState from the Emotion subsystem,
 * looks up the corresponding blend shape targets in the BlendShapeMappingDataAsset,
 * and smoothly interpolates the skeletal mesh's morph targets toward those values.
 */
UCLASS(ClassGroup = (LLMNPC), meta = (BlueprintSpawnableComponent))
class LLM_NPC_API UMetahumanAnimComponent : public UNPCSubsystemComponent
{
	GENERATED_BODY()

public:
	UMetahumanAnimComponent();

	// --- Lifecycle ---
	virtual void InitializeSubsystem() override;
	virtual void ShutdownSubsystem() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	// --- Public API ---

	/**
	 * Interpolate current blend shape values toward targets.
	 * Called automatically from TickComponent.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Animation")
	void UpdateBlendShapes(float DeltaTime);

	// --- Configuration ---

	/** Data asset mapping emotions to blend shape targets. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Animation")
	TSoftObjectPtr<UBlendShapeMappingDataAsset> BlendShapeMappingAssetRef;

	/** Speed of interpolation toward target blend shape values (higher = faster). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Animation",
		meta = (ClampMin = "0.1"))
	float InterpolationSpeed = 4.0f;

protected:
	virtual void BeginPlay() override;

private:
	/** Cached reference to the owner's skeletal mesh component (face mesh). */
	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> CachedSkeletalMesh;

	/** Loaded blend shape mapping data asset (runtime). */
	UPROPERTY()
	TObjectPtr<UBlendShapeMappingDataAsset> LoadedMappingData;

	/** Current blend shape values being interpolated. Key = morph target name. */
	TMap<FName, float> CurrentBlendShapeValues;

	/** Target blend shape values from the latest emotion state lookup. */
	TMap<FName, float> TargetBlendShapeValues;
};
