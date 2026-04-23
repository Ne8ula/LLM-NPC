#pragma once

#include "CoreMinimal.h"
#include "LLM_NPC/Core/NPCSubsystemComponent.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "BlendShapeMappingDataAsset.h"
#include "MetahumanAnimComponent.generated.h"

class UWhisperSTTComponent;
class UElevenLabsTTSComponent;

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

	/**
	 * Push a set of viseme-driven face curves. Any curve that was active on
	 * the previous call but is missing from this call is zeroed. Called by
	 * UNPCLipSyncComponent each tick while a viseme schedule is playing.
	 * Viseme curves win over emotion curves on overlapping mouth controls.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Animation")
	void SetVisemeCurves(const TMap<FName, float>& Curves);

	/**
	 * Enable/disable the subtle "thinking" facial pose layered on top of the
	 * current emotion pose. Fluidly blends in through the existing emotion
	 * curve interpolation loop. Idempotent — safe to call repeatedly.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Animation")
	void SetThinkingActive(bool bActive);

	/** Get the cached Face skeletal mesh. */
	USkeletalMeshComponent* GetFaceMesh() const { return CachedSkeletalMesh; }

	// --- Configuration ---

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Animation")
	TSoftObjectPtr<UBlendShapeMappingDataAsset> BlendShapeMappingAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Animation", meta = (ClampMin = "0.1"))
	float InterpolationSpeed = 4.0f;

	/**
	 * When true, emotion state drives FACS curves (legacy path — mouthSmile_L,
	 * browDown, etc. set per emotion). When false, emotional expression comes
	 * from the MetaHuman template animations driven by
	 * UTemplateAnimationDriverComponent and this component only handles lip
	 * sync + jaw + blink + thinking overlay. Default on: classic RigLogic
	 * MetaHumans (Face_AnimBP_C) have no Template Animation enum for the
	 * reflection path, so FACS curve emotions are the working pipeline. Flip
	 * off only when the MetaHuman is rebuilt via MetaHuman Creator.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Animation")
	bool bUseCurveBasedEmotions = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Animation", meta = (ClampMin = "0.1"))
	float LipSyncInterpolationSpeed = 12.0f;

	/**
	 * Subtle "thinking" pose merged into the emotion target curves while
	 * bIsThinking is true. IMPORTANT: intentionally brow-only — no mouth
	 * curves — so lip sync has unambiguous authority over the mouth during
	 * the handoff to speech. The ActiveVisemeCurveNames skip list would
	 * still protect lip sync if mouth curves were added, but at the cost of
	 * one frame of visible overlap on the handoff.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Animation|Thinking")
	TMap<FName, float> ThinkingCurves;

	/** Auto-clear thinking if it's been active for longer than this (seconds).
	 *  Guards against DialogueComponent silent-error paths where no TTS event
	 *  ever fires — without this, thinking would latch on indefinitely. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Animation|Thinking",
		meta = (ClampMin = "1.0", ClampMax = "60.0"))
	float ThinkingTimeoutSeconds = 15.0f;

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

	/** Curves that the last SetVisemeCurves call pushed. Used to zero stale curves and to lock these names away from the emotion decay loop. */
	TSet<FName> ActiveVisemeCurveNames;

	/** Blinking state. */
	bool bIsBlinking = false;
	float BlinkTimer = 3.0f;
	float BlinkPhase = 0.0f;

	/** Whisper transcript successfully received — start thinking pose. */
	UFUNCTION()
	void HandleTranscriptReady(const FString& Transcript);

	/** Primary handoff — TTS alignment received, lip sync about to start. */
	UFUNCTION()
	void HandleTTSAlignmentReceived(
		const FString& Characters,
		const TArray<float>& StartTimesSec,
		const TArray<float>& DurationsSec);

	/** Fallback — covers the Characters.Len()==0 alignment-missing path. */
	UFUNCTION()
	void HandleSpeechStarted();

	/** Safety net — covers error paths and speech completion. */
	UFUNCTION()
	void HandleSpeechFinished();

	/** Bound to UElevenLabsTTSComponent::OnSpeechError — immediate thinking
	 *  pose clear so brow curves decay without waiting for the 15s watchdog. */
	UFUNCTION()
	void HandleSpeechError(int32 ResponseCode, const FString& ErrorBody);

	/** Cached sibling pipeline components (subscribe/unsubscribe pairing). */
	TWeakObjectPtr<UWhisperSTTComponent>    CachedSTT;
	TWeakObjectPtr<UElevenLabsTTSComponent> CachedTTS;

	/** Thinking state. */
	bool  bIsThinking   = false;
	float ThinkingTimer = 0.0f;
};
