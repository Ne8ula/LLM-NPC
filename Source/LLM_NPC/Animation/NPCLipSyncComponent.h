#pragma once

#include "CoreMinimal.h"
#include "LLM_NPC/Core/NPCSubsystemComponent.h"
#include "VisemeTypes.h"
#include "NPCLipSyncComponent.generated.h"

class USoundWave;
class UMetahumanAnimComponent;
class UElevenLabsTTSComponent;

/**
 * Drives MetaHuman viseme blend shapes from ElevenLabs TTS character alignment.
 *
 * Subscribes to UElevenLabsTTSComponent::OnTTSAlignmentReceived, converts the
 * character timings into an FVisemeSchedule via FPhonemeVisemeMapper, and
 * samples the schedule each tick against the TTS playback clock to drive
 * MetaHuman face curves through UMetahumanAnimComponent::SetVisemeCurves.
 */
UCLASS(ClassGroup = (LLMNPC), meta = (BlueprintSpawnableComponent))
class LLM_NPC_API UNPCLipSyncComponent : public UNPCSubsystemComponent
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
	 * Deprecated stub kept for Blueprint back-compat. The new lip sync path is
	 * driven by the TTS alignment delegate and does not take a sound wave.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|LipSync")
	void StartLipSync(USoundWave* AudioSource);

	/** Stop lip sync and close the mouth. */
	UFUNCTION(BlueprintCallable, Category = "NPC|LipSync")
	void StopLipSync();

	// --- Configuration ---

	/**
	 * Default per-curve exponential smoothing speed applied on top of the
	 * schedule sampler. Higher = snappier (less inertia), lower = lazier.
	 * 16 ≈ ~110 ms to reach target at 60 fps; comfortable range is 12
	 * (very smooth) to 30 (very snappy). Used for vowel/jaw curves.
	 *
	 * Lower values give the face more "weight" through brief consonant
	 * transitions — TH, DD, KK don't pop in/out as visibly because the
	 * smoother lags slightly through the short consonant window.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|LipSync",
		meta = (ClampMin = "1.0", ClampMax = "60.0"))
	float OutputSmoothingSpeed = 16.0f;

	/**
	 * Fast attack speed used by closure curves (lipsTogether*) when their
	 * target value is *increasing* — i.e. the lips are snapping shut. Real
	 * lip closures happen quickly (~50 ms), so this needs to be much higher
	 * than the default. 50 ≈ near-instant closure.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|LipSync",
		meta = (ClampMin = "1.0", ClampMax = "120.0"))
	float ClosureAttackSpeed = 50.0f;

	/**
	 * Slow decay speed used by closure curves (lipsTogether*) when their
	 * target value is *decreasing* — i.e. the lips are relaxing open. Slow
	 * decay makes the closure linger long enough to read visually before
	 * the next vowel pulls the lips fully open. 7 ≈ ~250 ms relax.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|LipSync",
		meta = (ClampMin = "1.0", ClampMax = "30.0"))
	float ClosureDecaySpeed = 7.0f;

	/** Fade-out duration at the end of an utterance, in seconds. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|LipSync",
		meta = (ClampMin = "0.01", ClampMax = "0.5"))
	float EndFadeOutSec = 0.150f;

protected:
	virtual void BeginPlay() override;

private:
	/** Bound to UElevenLabsTTSComponent::OnTTSAlignmentReceived. */
	UFUNCTION()
	void HandleTTSAlignmentReceived(
		const FString& Characters,
		const TArray<float>& StartTimesSec,
		const TArray<float>& DurationsSec);

	/** Bound to UElevenLabsTTSComponent::OnSpeechFinished. */
	UFUNCTION()
	void HandleSpeechFinished();

	/**
	 * Sample the active schedule at ScheduleTime. Returns the blended curve
	 * map (curve name → weight). Empty when the schedule is idle. Updates
	 * LastKeyIndex as a hint for the next tick.
	 */
	TMap<FName, float> SampleScheduleAt(float ScheduleTime);

	/** Cached sibling components on the owner. TWeakObjectPtr tracks GC independently — no UPROPERTY needed. */
	TWeakObjectPtr<UMetahumanAnimComponent> CachedMetahumanAnim;
	TWeakObjectPtr<UElevenLabsTTSComponent> CachedTTS;

	/** The schedule currently being played back. */
	FVisemeSchedule ActiveSchedule;

	/** Index hint into ActiveSchedule.Keys for the current time (avoids repeated linear scans). */
	int32 LastKeyIndex = 0;

	/** True while ActiveSchedule is being sampled. */
	bool bScheduleActive = false;

	/** Fade-out state after the schedule ends so the mouth closes smoothly. */
	bool bFadingOut = false;
	float FadeOutTimeRemaining = 0.0f;

	/** Last raw sample from the schedule (pre-smoothing). */
	TMap<FName, float> LastCurves;

	/**
	 * Per-curve smoothed values that are actually pushed to the face each
	 * tick. Updated by exponentially damping toward the schedule sample,
	 * giving the mouth motion natural inertia and eliminating snap between
	 * adjacent visemes.
	 */
	TMap<FName, float> SmoothedCurves;
};
