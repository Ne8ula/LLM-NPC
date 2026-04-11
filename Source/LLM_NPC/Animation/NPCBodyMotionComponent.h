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
 * Full-body target pose for one state (Idle / Thinking / Speaking).
 *
 * Each field is a LOCAL-space FRotator delta applied to the corresponding
 * bone on top of the ref pose via forward-kinematics propagation in the
 * body motion component. The component blends the three state poses by
 * state alphas and writes the result through ApplyBoneLayer.
 *
 * All fields are EditAnywhere / BlueprintReadWrite so poses can be tuned
 * live in the Details panel during PIE — no rebuild required to dial in
 * the hand-to-chin thinking pose or the hands-to-waist speaking gesture.
 *
 * Axis convention: MetaHuman / UE5 Mannequin. Local X runs ALONG the bone
 * (shoulder → elbow, elbow → wrist), so:
 *   - Pitch = rotation around Y axis (typically "up/down" from ref pose)
 *   - Yaw   = rotation around Z axis (typically "forward/back" OR swings
 *             arm down from T-pose — CRITICAL for dropping arms)
 *   - Roll  = rotation around X axis (spins the bone along its length —
 *             usually NOT what you want for arms)
 */
USTRUCT(BlueprintType)
struct FBodyMotionPose
{
	GENERATED_BODY()

	// --- Upper body ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upper Body")
	FRotator Pelvis = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upper Body")
	FRotator Spine01 = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upper Body")
	FRotator Spine03 = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upper Body")
	FRotator Neck01 = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upper Body")
	FRotator Head = FRotator::ZeroRotator;

	// --- Arms ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arms")
	FRotator ClavicleL = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arms")
	FRotator ClavicleR = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arms")
	FRotator UpperArmL = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arms")
	FRotator UpperArmR = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arms")
	FRotator LowerArmL = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arms")
	FRotator LowerArmR = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arms")
	FRotator HandL = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arms")
	FRotator HandR = FRotator::ZeroRotator;

	// --- Legs (weight shift / contrapposto) ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Legs")
	FRotator ThighL = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Legs")
	FRotator ThighR = FRotator::ZeroRotator;

	/** Scaled linear blend — used for state alpha weighting. */
	static FRotator Blend(const FRotator& A, float AW, const FRotator& B, float BW, const FRotator& C, float CW)
	{
		return FRotator(
			A.Pitch * AW + B.Pitch * BW + C.Pitch * CW,
			A.Yaw   * AW + B.Yaw   * BW + C.Yaw   * CW,
			A.Roll  * AW + B.Roll  * BW + C.Roll  * CW);
	}

	static FRotator Lerp(const FRotator& A, const FRotator& B, float T)
	{
		return FRotator(
			FMath::Lerp(A.Pitch, B.Pitch, T),
			FMath::Lerp(A.Yaw,   B.Yaw,   T),
			FMath::Lerp(A.Roll,  B.Roll,  T));
	}
};

/**
 * Drives procedural body motion on a MetaHuman NPC so she doesn't T-pose
 * while speaking and shows natural conversational body language during
 * idle / thinking / speaking states.
 *
 * 100% procedural — no animation assets, no AnimBP edits. Mutates the body
 * skeletal mesh's component-space bone transforms from the
 * USkinnedMeshComponent::OnBoneTransformsFinalizedMC delegate. Writes
 * local-space rotations to 15 bones (pelvis, spine_01/03, neck_01, head,
 * clavicle_l/r, upperarm_l/r, lowerarm_l/r, hand_l/r, thigh_l/r) via
 * forward-kinematics propagation, converting each local-space delta to a
 * component-space pivot rotation.
 *
 * States are driven by voice pipeline delegates (same as the thinking face):
 *   OnTranscriptReady        -> Thinking
 *   OnTTSAlignmentReceived   -> Speaking
 *   OnSpeechStarted          -> Speaking (fallback)
 *   OnSpeechFinished         -> Idle
 *   OnSpeechError            -> Idle (immediate recovery from TTS failure)
 *
 * Per-state POSE keyframes (FBodyMotionPose) are blended by three state
 * alphas (IdleAlpha / ThinkingAlpha / SpeakingAlpha). A secondary slow
 * cycle blends between SpeakingPose and SpeakingGesturePose while in the
 * Speaking state — produces periodic "hands to waist" gestures.
 *
 * Small sine overlays (breathing, head nods) are added on top of the
 * blended pose for life, using `BreathFrequencyHz` etc. as amplitudes.
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

	// --- Bone name overrides (defaults = MetaHuman / UE5 Mannequin skeleton) ---

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Bones")
	FName PelvisBoneName = "pelvis";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Bones")
	FName Spine01BoneName = "spine_01";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Bones")
	FName Spine03BoneName = "spine_03";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Bones")
	FName NeckBoneName = "neck_01";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Bones")
	FName HeadBoneName = "head";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Bones")
	FName ClavicleLBoneName = "clavicle_l";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Bones")
	FName ClavicleRBoneName = "clavicle_r";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Bones")
	FName UpperArmLBoneName = "upperarm_l";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Bones")
	FName UpperArmRBoneName = "upperarm_r";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Bones")
	FName LowerArmLBoneName = "lowerarm_l";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Bones")
	FName LowerArmRBoneName = "lowerarm_r";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Bones")
	FName HandLBoneName = "hand_l";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Bones")
	FName HandRBoneName = "hand_r";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Bones")
	FName ThighLBoneName = "thigh_l";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Bones")
	FName ThighRBoneName = "thigh_r";

	// --- State poses ---

	/** Relaxed standing pose. Arms hanging, slight contrapposto on left leg,
	 *  weight slightly to left, gentle breathing and head drift layered on. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Poses")
	FBodyMotionPose IdlePose;

	/** Held while LLM is thinking. Right hand brought up near the chin,
	 *  slight head tilt and look-up, weight on left leg. Tune via Details
	 *  panel until hand-to-chin lands believably on your specific rig. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Poses")
	FBodyMotionPose ThinkingPose;

	/** Base speaking pose. Slight forward engagement lean, contrapposto,
	 *  arms relaxed but ready to gesture. Head nods are layered via sine. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Poses")
	FBodyMotionPose SpeakingPose;

	/** Alternate speaking pose cycled slowly with SpeakingPose — hands
	 *  brought up to waist level for gesture variation. GestureCycleSec
	 *  controls the full in-out period. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Poses")
	FBodyMotionPose SpeakingGesturePose;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Poses",
		meta = (ClampMin = "2.0", ClampMax = "30.0"))
	float SpeakingGestureCycleSec = 8.0f;

	// --- Oscillation overlays (added on top of blended pose) ---
	//
	// Overlays are scaled by state alphas, so they fade out when a state
	// ends. Keep amplitudes MODEST so residual motion during the state
	// blend-out doesn't read as "wobbling after speech is done."

	/** Chest breathing amplitude on Spine03 pitch. Keep at 0 unless you want
	 *  visible breathing — Spine03 is a parent bone so any rotation here
	 *  propagates via FK to the entire upper body (head, arms, hands) and
	 *  reads as "wobble" even at 0.5°. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Overlays")
	float BreathAmplitudeDeg = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Overlays",
		meta = (ClampMin = "0.05", ClampMax = "2.0"))
	float BreathFrequencyHz = 0.25f;

	/** Slow idle head yaw drift. Off by default. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Overlays")
	float IdleHeadDriftDeg = 0.0f;

	/** Amplitude for the non-rhythmic contemplative head motion during thinking.
	 *  Uses two incommensurable-period sines that beat together so the motion
	 *  never repeats in a regular rhythm — looks like natural pondering.
	 *  Set to 0 to disable entirely. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Overlays")
	float ThinkingHeadContemplativeDeg = 5.0f;

	/** Speaking head nod amplitude. Zero = no rhythmic nod during speech. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Overlays")
	float SpeakingHeadNodDeg = 0.0f;

	/** Speaking shoulder micro-motion amplitude. Zero = no shoulder sway. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Overlays")
	float SpeakingShoulderDeg = 0.0f;

	// --- Blend / watchdog ---

	/** FInterpTo speed for state alphas. 1.2 ~= 830 ms blend time. Lower
	 *  values = smoother, longer transitions. Raise above 2.5 for snappy. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|BodyMotion|Blend",
		meta = (ClampMin = "0.5", ClampMax = "20.0"))
	float StateBlendSpeed = 1.2f;

	/** Auto-clear thinking if no downstream event fires to reset state. */
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

	float IdleAlpha = 1.0f;
	float ThinkingAlpha = 0.0f;
	float SpeakingAlpha = 0.0f;

	float TimeAccum = 0.0f;
	float ThinkingWatchdog = 0.0f;

	/** Cached sibling pipeline components. */
	TWeakObjectPtr<USkeletalMeshComponent>  CachedBodyMesh;
	TWeakObjectPtr<UWhisperSTTComponent>    CachedSTT;
	TWeakObjectPtr<UElevenLabsTTSComponent> CachedTTS;

	/** Cached bone indices — 15 bones, INDEX_NONE until CacheBoneIndices runs. */
	int32 PelvisIdx = INDEX_NONE;
	int32 Spine01Idx = INDEX_NONE;
	int32 Spine03Idx = INDEX_NONE;
	int32 NeckIdx = INDEX_NONE;
	int32 HeadIdx = INDEX_NONE;
	int32 ClavLIdx = INDEX_NONE;
	int32 ClavRIdx = INDEX_NONE;
	int32 UArmLIdx = INDEX_NONE;
	int32 UArmRIdx = INDEX_NONE;
	int32 LArmLIdx = INDEX_NONE;
	int32 LArmRIdx = INDEX_NONE;
	int32 HandLIdx = INDEX_NONE;
	int32 HandRIdx = INDEX_NONE;
	int32 ThighLIdx = INDEX_NONE;
	int32 ThighRIdx = INDEX_NONE;

	FDelegateHandle FinalizeHandle;
	bool bDelegateRegistered = false;

	/** Which bone an FBodyMotionPose field is addressing — used by the
	 *  per-tick pose evaluator to pull the right FRotator out of each pose. */
	enum class EBodyMotionBone : uint8
	{
		Pelvis, Spine01, Spine03, Neck, Head,
		ClavicleL, ClavicleR,
		UpperArmL, UpperArmR,
		LowerArmL, LowerArmR,
		HandL, HandR,
		ThighL, ThighR,
	};

	/** Pull the FRotator for a specific bone out of a pose struct. */
	static const FRotator& GetPoseRotator(const FBodyMotionPose& Pose, EBodyMotionBone Bone);

	/** Compute the final local-space delta rotation for one bone this frame.
	 *  Blends the three state poses by alpha, blends Speaking <-> Gesture by
	 *  the cosine gesture cycle, then adds sine overlays for bones that get
	 *  them (Spine03 breathing, Head nods, Clavicle shoulder motion). */
	FRotator ComputeBoneLocalDelta(EBodyMotionBone Bone) const;

	void OnBoneTransformsFinalized();
	void CacheBoneIndices(const FReferenceSkeleton& RefSkel);

	USkeletalMeshComponent* FindBodyMesh(AActor* Owner) const;

	void RegisterFinalizeDelegate();
	void UnregisterFinalizeDelegate();

	/** Apply a LOCAL-SPACE delta rotation to BoneIdx, propagating the same
	 *  rotation to all descendants via ref-skeleton walk. Top-down order
	 *  required — each later call reads parents from already-updated CS. */
	void ApplyBoneLayer(
		USkeletalMeshComponent* Mesh,
		const FReferenceSkeleton& RefSkel,
		TArray<FTransform>& CS,
		int32 BoneIdx,
		const FQuat& LocalDeltaRot);

	// --- Voice pipeline handlers ---
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

	UFUNCTION()
	void HandleSpeechError(int32 ResponseCode, const FString& ErrorBody);
};
