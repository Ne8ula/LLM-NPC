#pragma once

#include "CoreMinimal.h"
#include "LLM_NPC/Core/NPCSubsystemComponent.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "BlendShapeMappingDataAsset.h"
#include "MetahumanAnimComponent.generated.h"

/**
 * Drives Metahuman facial expressions via the Face AnimBP's control system.
 *
 * Works WITH RigLogic by setting curves through the AnimBP's "Set Control" function
 * and "Jaw Open Alpha" property, rather than trying to override morph targets directly.
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

	/** Legacy — now handled internally. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Animation")
	void UpdateBlendShapes(float DeltaTime);

	/** Set the lip sync jaw open value (0-1). Called externally by TTS/audio system. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Animation")
	void SetLipSyncJawOpen(float Value);

	/** Get the cached Face skeletal mesh. */
	USkeletalMeshComponent* GetFaceMesh() const { return CachedSkeletalMesh; }

	// --- Configuration ---

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Animation")
	TSoftObjectPtr<UBlendShapeMappingDataAsset> BlendShapeMappingAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Animation", meta = (ClampMin = "0.1"))
	float InterpolationSpeed = 4.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Animation", meta = (ClampMin = "0.1"))
	float LipSyncInterpolationSpeed = 12.0f;

protected:
	virtual void BeginPlay() override;

private:
	USkeletalMeshComponent* FindFaceMesh(AActor* Actor) const;
	void BuildDefaultEmotionMappings();

	/** Call the Face AnimBP's "Set Control" function via reflection. */
	void SetFaceControl(FName ControlName, float Value);

	/** Set "Jaw Open Alpha" on the Face AnimBP via property reflection. */
	void SetJawOpenAlpha(float Value);

	UPROPERTY()
	TObjectPtr<class UEmotionComponent> CachedEmotionComp;

	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> CachedSkeletalMesh;

	UPROPERTY()
	TObjectPtr<UBlendShapeMappingDataAsset> LoadedMappingData;

	/** Cached Face AnimInstance for reflection calls. */
	UPROPERTY()
	TObjectPtr<UAnimInstance> CachedFaceAnimInstance;

	/** Cached "Set Control" function pointer. */
	UFunction* CachedSetControlFunc = nullptr;

	/** Emotion to FACS curve mappings (curve name → target value). */
	TMap<EEmotionType, TArray<TPair<FName, float>>> EmotionCurveMappings;

	/** Currently active curve values (for smooth interpolation). */
	TMap<FName, float> ActiveCurveValues;

	/** Lip sync state. */
	float LipSyncJawOpenValue = 0.0f;
	float CurrentJawOpenValue = 0.0f;

	/** Blinking state. */
	bool bIsBlinking = false;
	float BlinkTimer = 3.0f;
	float BlinkPhase = 0.0f;
};
