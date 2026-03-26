#pragma once

#include "CoreMinimal.h"
#include "LLM_NPC/Core/NPCSubsystemComponent.h"
#include "NPCLipSyncComponent.generated.h"

class USoundWave;
class UAudioComponent;

/**
 * Drives viseme blend shapes from TTS audio output for lip synchronization.
 *
 * Currently implements a simple amplitude-based mouth open/close driver as a
 * placeholder. Designed to be replaced with OVRLipSync or a similar phoneme-based
 * solution in production.
 */
UCLASS(ClassGroup = (LLMNPC), meta = (BlueprintSpawnableComponent))
class FLLM_NPC_API UNPCLipSyncComponent : public UNPCSubsystemComponent
{
	GENERATED_BODY()

public:
	UNPCLipSyncComponent();

	// --- Lifecycle ---
	virtual void InitializeSubsystem() override;
	virtual void ShutdownSubsystem() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	// --- Public API ---

	/**
	 * Begin driving lip sync from the given audio source.
	 * Creates an audio component on the owner and plays the sound.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|LipSync")
	void StartLipSync(USoundWave* AudioSource);

	/** Stop lip sync and smoothly close the mouth. */
	UFUNCTION(BlueprintCallable, Category = "NPC|LipSync")
	void StopLipSync();

	// --- Configuration ---

	/** Name of the morph target controlling mouth open on the skeletal mesh. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|LipSync")
	FName MouthOpenBlendShape = FName(TEXT("jawOpen"));

	/** Sensitivity multiplier for amplitude-to-morph-target mapping. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|LipSync",
		meta = (ClampMin = "0.1", ClampMax = "10.0"))
	float Sensitivity = 1.0f;

	/** Interpolation speed for smoothing mouth movement. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|LipSync",
		meta = (ClampMin = "0.1"))
	float LipSyncInterpolationSpeed = 8.0f;

protected:
	virtual void BeginPlay() override;

private:
	/** Cached reference to the owner's skeletal mesh component. */
	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> CachedSkeletalMesh;

	/** Audio component used for playback. */
	UPROPERTY()
	TObjectPtr<UAudioComponent> ActiveAudioComponent;

	/** Whether lip sync is currently active. */
	bool bIsLipSyncActive = false;

	/** Current mouth open value being interpolated. */
	float CurrentMouthOpenValue = 0.0f;

	/** Target mouth open value derived from audio amplitude. */
	float TargetMouthOpenValue = 0.0f;
};
