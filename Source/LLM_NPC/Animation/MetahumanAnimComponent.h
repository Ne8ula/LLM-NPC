#pragma once

#include "CoreMinimal.h"
#include "LLM_NPC/Core/NPCSubsystemComponent.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "BlendShapeMappingDataAsset.h"
#include "MetahumanAnimComponent.generated.h"

/**
 * Drives Metahuman facial blend shapes based on emotion state and lip sync.
 *
 * Ticks in TG_PostUpdateWork (after AnimBP) so morph targets aren't overwritten.
 * Reads emotion from EmotionComponent and drives facial expressions.
 * Accepts lip sync jaw open values from external audio analysis.
 */
UCLASS(ClassGroup = (LLMNPC), meta = (BlueprintSpawnableComponent))
class LLM_NPC_API UMetahumanAnimComponent : public UNPCSubsystemComponent
{
	GENERATED_BODY()

public:
	UMetahumanAnimComponent();

	virtual void InitializeSubsystem() override;
	virtual void ShutdownSubsystem() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	/** Interpolate current blend shape values toward targets. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Animation")
	void UpdateBlendShapes(float DeltaTime);

	/** Set the lip sync jaw open value (0-1). Called externally by TTS/audio system. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Animation")
	void SetLipSyncJawOpen(float Value);

	/** Get the cached Face skeletal mesh (useful for other systems). */
	USkeletalMeshComponent* GetFaceMesh() const { return CachedSkeletalMesh; }

	// --- Configuration ---

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Animation")
	TSoftObjectPtr<UBlendShapeMappingDataAsset> BlendShapeMappingAssetRef;

	/** Speed of interpolation for emotion blend shapes (higher = faster). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Animation", meta = (ClampMin = "0.1"))
	float InterpolationSpeed = 4.0f;

	/** Speed of interpolation for lip sync jaw movement (higher = snappier). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Animation", meta = (ClampMin = "0.1"))
	float LipSyncInterpolationSpeed = 12.0f;

protected:
	virtual void BeginPlay() override;

private:
	/** Find the Face skeletal mesh on an actor (searches child actors recursively). */
	USkeletalMeshComponent* FindFaceMesh(AActor* Actor) const;

	/** Populate LoadedMappingData with default Metahuman Hana morph target mappings. */
	void PopulateDefaultMappings();

	UPROPERTY()
	TObjectPtr<class UEmotionComponent> CachedEmotionComp;

	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> CachedSkeletalMesh;

	UPROPERTY()
	TObjectPtr<UBlendShapeMappingDataAsset> LoadedMappingData;

	TMap<FName, float> CurrentBlendShapeValues;
	TMap<FName, float> TargetBlendShapeValues;

	/** Current lip sync jaw open value (set externally). */
	float LipSyncJawOpenValue = 0.0f;
};
