#pragma once

#include "CoreMinimal.h"
#include "LLM_NPC/Core/NPCSubsystemComponent.h"
#include "Components/SkinnedMeshComponent.h"  // FOnBoneTransformsFinalizedMultiCast
#include "NPCBodyMotionComponent.generated.h"

class USkeletalMeshComponent;
class UWhisperSTTComponent;
class UElevenLabsTTSComponent;
struct FReferenceSkeleton;

/**
 * Drives procedural body motion on a MetaHuman NPC so she doesn't T-pose
 * while speaking and shows subtle "alive" mannerisms while idling/thinking.
 *
 * 100% procedural — no animation assets, no AnimBP edits. Mutates the body
 * skeletal mesh's component-space bone transforms from the
 * USkinnedMeshComponent::OnBoneTransformsFinalizedMC delegate (after the
 * AnimBP has finalized the pose, before the scene proxy reads it).
 *
 * Has three states (Idle / Thinking / Speaking) driven by the same voice
 * pipeline delegates UNPCLipSyncComponent and UMetahumanAnimComponent's
 * thinking pose already subscribe to:
 *
 *   UWhisperSTTComponent::OnTranscriptReady          -> Thinking
 *   UElevenLabsTTSComponent::OnTTSAlignmentReceived  -> Speaking
 *   UElevenLabsTTSComponent::OnSpeechStarted         -> Speaking (fallback)
 *   UElevenLabsTTSComponent::OnSpeechFinished        -> Idle
 *
 * Three alphas (IdleAlpha/ThinkingAlpha/SpeakingAlpha) FInterpTo-blend
 * toward their target each tick so transitions are always smooth.
 *
 * Touches body bones only — never face curves — so there is zero overlap
 * with UNPCLipSyncComponent (mouth curves) or UMetahumanAnimComponent's
 * thinking pose (brow curves).
 */
UCLASS(ClassGroup = (LLMNPC), meta = (BlueprintSpawnableComponent))
class LLM_NPC_API UNPCBodyMotionComponent : public UNPCSubsystemComponent
{
	GENERATED_BODY()

public:
	UNPCBodyMotionComponent();

	virtual void InitializeSubsystem() override;
	virtual void ShutdownSubsystem() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	// --- Bone name overrides (defaults = MetaHuman skeleton) ---

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Bones")
	FName HeadBoneName = "head";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Bones")
	FName NeckBoneName = "neck_01";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Bones")
	FName Spine01BoneName = "spine_01";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Bones")
	FName Spine03BoneName = "spine_03";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Bones")
	FName ClavicleLBoneName = "clavicle_l";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Bones")
	FName ClavicleRBoneName = "clavicle_r";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Bones")
	FName UpperArmLBoneName = "upperarm_l";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Bones")
	FName UpperArmRBoneName = "upperarm_r";

	// --- Amplitudes (degrees unless noted) ---

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Amplitudes")
	float BreathAmplitudeDeg = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Amplitudes",
		meta = (ClampMin = "0.05", ClampMax = "2.0"))
	float BreathFrequencyHz = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Amplitudes")
	float IdleHeadDriftDeg = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Amplitudes")
	float IdleWeightShiftDeg = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Amplitudes")
	float ThinkingHeadTiltDeg = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Amplitudes")
	float SpeakingHeadNodDeg = 4.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Amplitudes")
	float SpeakingShoulderDeg = 2.5f;

	// --- T-pose break (full FRotators so local-axis can be tuned in-editor) ---
	//
	// MetaHuman upperarm local axes are non-obvious. A single scalar "pitch down"
	// is a guessing game; exposing the full rotator lets the user dial the
	// relaxed standing pose in Details panel without a rebuild.
	//
	// Default values approximate a relaxed "arms hanging" pose for MetaHuman;
	// tune per-rig if your skeleton differs.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|ArmRelax")
	FRotator UpperArmLRelaxRotation = FRotator(0.f, 0.f, 55.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|ArmRelax")
	FRotator UpperArmRRelaxRotation = FRotator(0.f, 0.f, -55.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|ArmRelax")
	FRotator ClavicleLRelaxRotation = FRotator(0.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|ArmRelax")
	FRotator ClavicleRRelaxRotation = FRotator(0.f, 0.f, 0.f);

	// --- Blend / watchdog ---

	/** FInterpTo speed for state alphas. 3.0 ~= 330 ms blend time. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Blend",
		meta = (ClampMin = "0.5", ClampMax = "20.0"))
	float StateBlendSpeed = 3.0f;

	/** Auto-clear thinking if it's been active for longer than this.
	 *  Guards silent Claude/TTS error paths where no event fires. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Blend",
		meta = (ClampMin = "1.0", ClampMax = "60.0"))
	float ThinkingTimeoutSeconds = 15.0f;

private:
	enum class EBodyState : uint8
	{
		Idle,
		Thinking,
		Speaking,
	};

	EBodyState TargetState = EBodyState::Idle;

	/** Three alphas for smooth cross-fade between states. */
	float IdleAlpha = 1.0f;
	float ThinkingAlpha = 0.0f;
	float SpeakingAlpha = 0.0f;

	/** Monotonic time accumulator for sine oscillations. */
	float TimeAccum = 0.0f;

	/** Watchdog elapsed time for stuck-in-thinking recovery. */
	float ThinkingWatchdog = 0.0f;

	/** Cached sibling pipeline components. */
	TWeakObjectPtr<USkeletalMeshComponent>  CachedBodyMesh;
	TWeakObjectPtr<UWhisperSTTComponent>    CachedSTT;
	TWeakObjectPtr<UElevenLabsTTSComponent> CachedTTS;

	/** Lazily-populated bone indices (indices are stable per skeleton). */
	int32 HeadIdx = INDEX_NONE;
	int32 NeckIdx = INDEX_NONE;
	int32 Spine03Idx = INDEX_NONE;
	int32 Spine01Idx = INDEX_NONE;
	int32 ClavLIdx = INDEX_NONE;
	int32 ClavRIdx = INDEX_NONE;
	int32 UArmLIdx = INDEX_NONE;
	int32 UArmRIdx = INDEX_NONE;

	/** Finalize-delegate registration state. */
	FDelegateHandle FinalizeHandle;
	bool bDelegateRegistered = false;

	/** The post-anim, pre-render hook where we mutate bone transforms. */
	void OnBoneTransformsFinalized();

	/** One-time bone index lookup from the ref skeleton. */
	void CacheBoneIndices(const FReferenceSkeleton& RefSkel);

	/** Body mesh discovery: prefers ACharacter::GetMesh() over search. */
	USkeletalMeshComponent* FindBodyMesh(AActor* Owner) const;

	void RegisterFinalizeDelegate();
	void UnregisterFinalizeDelegate();

	/**
	 * Apply a LOCAL-SPACE delta rotation to BoneIdx, propagating the same
	 * rotation to all descendants (manual forward kinematics through the
	 * ref skeleton parent chain). Top-down calling order is required —
	 * each later call reads parents from CS that have already been updated
	 * by earlier calls.
	 */
	void ApplyBoneLayer(
		USkeletalMeshComponent* Mesh,
		const FReferenceSkeleton& RefSkel,
		TArray<FTransform>& CS,
		int32 BoneIdx,
		const FQuat& LocalDeltaRot);

	// --- Per-bone delta computers (all read state alphas + TimeAccum) ---
	FQuat ComputeSpine01LocalDelta() const;
	FQuat ComputeSpine03LocalDelta() const;
	FQuat ComputeNeckLocalDelta() const;
	FQuat ComputeHeadLocalDelta() const;
	FQuat ComputeClavicleLLocalDelta() const;
	FQuat ComputeClavicleRLocalDelta() const;
	FQuat ComputeUpperArmLLocalDelta() const;
	FQuat ComputeUpperArmRLocalDelta() const;

	// --- Voice pipeline handlers (subscribe/unsubscribe via AddDynamic) ---
	UFUNCTION()
	void HandleTranscriptReady(const FString& Transcript);

	UFUNCTION()
	void HandleTTSAlignmentReceived(
		const FString& Characters,
		const TArray<float>& StartTimesSec,
		const TArray<float>& DurationsSec);

	UFUNCTION()
	void HandleSpeechStarted();

	UFUNCTION()
	void HandleSpeechFinished();
};
