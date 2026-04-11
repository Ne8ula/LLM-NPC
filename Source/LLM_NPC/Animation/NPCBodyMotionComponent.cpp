#include "NPCBodyMotionComponent.h"

#include "LLM_NPC/Dialogue/WhisperSTTComponent.h"
#include "LLM_NPC/Dialogue/ElevenLabsTTSComponent.h"

#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/SkinnedAsset.h"
#include "ReferenceSkeleton.h"
#include "GameFramework/Character.h"

UNPCBodyMotionComponent::UNPCBodyMotionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	// Default tick group is fine — our actual bone writes happen inside the
	// mesh's finalize delegate which runs after anim eval regardless of our
	// own tick group. Tick only drives the state-blend alphas and watchdog.
	SubsystemName = TEXT("BodyMotion");
}

// -----------------------------------------------------------------------------
// Lifecycle
// -----------------------------------------------------------------------------

void UNPCBodyMotionComponent::InitializeSubsystem()
{
	Super::InitializeSubsystem();

	AActor* Owner = GetOwner();
	if (!Owner)
	{
		return;
	}

	CachedBodyMesh = FindBodyMesh(Owner);
	if (CachedBodyMesh.IsValid())
	{
		if (USkinnedAsset* SkinnedAsset = CachedBodyMesh->GetSkinnedAsset())
		{
			CacheBoneIndices(SkinnedAsset->GetRefSkeleton());
		}
		RegisterFinalizeDelegate();
		UE_LOG(LogTemp, Log, TEXT("BodyMotion: Bound to body mesh '%s' on owner '%s'"),
			*CachedBodyMesh->GetName(), *Owner->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BodyMotion: No body skeletal mesh found on '%s'"),
			*Owner->GetName());
	}

	// Subscribe to the voice pipeline — same FindComponentByClass discovery as
	// UNPCLipSyncComponent and the thinking-face hook, so we correlate with
	// the same TTS instance they subscribe to. There are two
	// UElevenLabsTTSComponent subobjects on ANPCCharacter (pre-existing
	// quirk), and only FindComponentByClass lands on the same one.
	CachedSTT = Owner->FindComponentByClass<UWhisperSTTComponent>();
	if (CachedSTT.IsValid())
	{
		CachedSTT->OnTranscriptReady.AddDynamic(
			this, &UNPCBodyMotionComponent::HandleTranscriptReady);
	}

	CachedTTS = Owner->FindComponentByClass<UElevenLabsTTSComponent>();
	if (CachedTTS.IsValid())
	{
		CachedTTS->OnTTSAlignmentReceived.AddDynamic(
			this, &UNPCBodyMotionComponent::HandleTTSAlignmentReceived);
		CachedTTS->OnSpeechStarted.AddDynamic(
			this, &UNPCBodyMotionComponent::HandleSpeechStarted);
		CachedTTS->OnSpeechFinished.AddDynamic(
			this, &UNPCBodyMotionComponent::HandleSpeechFinished);
	}
}

void UNPCBodyMotionComponent::ShutdownSubsystem()
{
	UnregisterFinalizeDelegate();

	if (CachedSTT.IsValid())
	{
		CachedSTT->OnTranscriptReady.RemoveDynamic(
			this, &UNPCBodyMotionComponent::HandleTranscriptReady);
	}
	if (CachedTTS.IsValid())
	{
		CachedTTS->OnTTSAlignmentReceived.RemoveDynamic(
			this, &UNPCBodyMotionComponent::HandleTTSAlignmentReceived);
		CachedTTS->OnSpeechStarted.RemoveDynamic(
			this, &UNPCBodyMotionComponent::HandleSpeechStarted);
		CachedTTS->OnSpeechFinished.RemoveDynamic(
			this, &UNPCBodyMotionComponent::HandleSpeechFinished);
	}

	TargetState = EBodyState::Idle;
	IdleAlpha = 1.0f;
	ThinkingAlpha = 0.0f;
	SpeakingAlpha = 0.0f;
	ThinkingWatchdog = 0.0f;
	TimeAccum = 0.0f;

	Super::ShutdownSubsystem();
}

void UNPCBodyMotionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsInitialized)
	{
		return;
	}

	// Monotonic time — sines keyed off this so nothing looks metronomic.
	TimeAccum += DeltaTime;

	// Thinking watchdog: auto-clear if stuck (silent Claude/TTS error path).
	if (TargetState == EBodyState::Thinking)
	{
		ThinkingWatchdog += DeltaTime;
		if (ThinkingWatchdog >= ThinkingTimeoutSeconds)
		{
			UE_LOG(LogTemp, Warning,
				TEXT("BodyMotion: Thinking watchdog tripped after %.1fs — clearing."),
				ThinkingWatchdog);
			TargetState = EBodyState::Idle;
			ThinkingWatchdog = 0.0f;
		}
	}
	else
	{
		ThinkingWatchdog = 0.0f;
	}

	// Blend the three alphas toward the target state.
	const float IdleTarget     = (TargetState == EBodyState::Idle)     ? 1.0f : 0.0f;
	const float ThinkingTarget = (TargetState == EBodyState::Thinking) ? 1.0f : 0.0f;
	const float SpeakingTarget = (TargetState == EBodyState::Speaking) ? 1.0f : 0.0f;
	IdleAlpha     = FMath::FInterpTo(IdleAlpha,     IdleTarget,     DeltaTime, StateBlendSpeed);
	ThinkingAlpha = FMath::FInterpTo(ThinkingAlpha, ThinkingTarget, DeltaTime, StateBlendSpeed);
	SpeakingAlpha = FMath::FInterpTo(SpeakingAlpha, SpeakingTarget, DeltaTime, StateBlendSpeed);

	// PIE-restart safety: if our cached mesh went null (new PIE session
	// destroyed + re-created it), unregister the stale delegate handle,
	// re-acquire the mesh, and re-register. Mirrors how MetahumanAnimComponent
	// re-caches its AnimInstance after PIE restarts.
	if (!CachedBodyMesh.IsValid())
	{
		UnregisterFinalizeDelegate();
		HeadIdx = NeckIdx = Spine03Idx = Spine01Idx = INDEX_NONE;
		ClavLIdx = ClavRIdx = UArmLIdx = UArmRIdx = INDEX_NONE;

		if (AActor* Owner = GetOwner())
		{
			CachedBodyMesh = FindBodyMesh(Owner);
			if (CachedBodyMesh.IsValid())
			{
				if (USkinnedAsset* SkinnedAsset = CachedBodyMesh->GetSkinnedAsset())
				{
					CacheBoneIndices(SkinnedAsset->GetRefSkeleton());
				}
				RegisterFinalizeDelegate();
			}
		}
	}
}

// -----------------------------------------------------------------------------
// Body mesh discovery
// -----------------------------------------------------------------------------

USkeletalMeshComponent* UNPCBodyMotionComponent::FindBodyMesh(AActor* Owner) const
{
	if (!Owner)
	{
		return nullptr;
	}

	// ACharacter::GetMesh() is the canonical body skeletal mesh. Do NOT use
	// FindComponentByClass<USkeletalMeshComponent>() — the face lives in a
	// UChildActorComponent which can be returned first depending on spawn
	// order, and we'd end up rotating the face's bones instead of the body.
	if (ACharacter* Character = Cast<ACharacter>(Owner))
	{
		return Character->GetMesh();
	}

	return nullptr;
}

void UNPCBodyMotionComponent::CacheBoneIndices(const FReferenceSkeleton& RefSkel)
{
	HeadIdx    = RefSkel.FindBoneIndex(HeadBoneName);
	NeckIdx    = RefSkel.FindBoneIndex(NeckBoneName);
	Spine01Idx = RefSkel.FindBoneIndex(Spine01BoneName);
	Spine03Idx = RefSkel.FindBoneIndex(Spine03BoneName);
	ClavLIdx   = RefSkel.FindBoneIndex(ClavicleLBoneName);
	ClavRIdx   = RefSkel.FindBoneIndex(ClavicleRBoneName);
	UArmLIdx   = RefSkel.FindBoneIndex(UpperArmLBoneName);
	UArmRIdx   = RefSkel.FindBoneIndex(UpperArmRBoneName);

	UE_LOG(LogTemp, Log,
		TEXT("BodyMotion: Bone indices — Head=%d Neck=%d Spine01=%d Spine03=%d ClavL=%d ClavR=%d UArmL=%d UArmR=%d"),
		HeadIdx, NeckIdx, Spine01Idx, Spine03Idx, ClavLIdx, ClavRIdx, UArmLIdx, UArmRIdx);
}

// -----------------------------------------------------------------------------
// Finalize delegate register / unregister
// -----------------------------------------------------------------------------

void UNPCBodyMotionComponent::RegisterFinalizeDelegate()
{
	USkeletalMeshComponent* Mesh = CachedBodyMesh.Get();
	if (!Mesh || bDelegateRegistered)
	{
		return;
	}

	FinalizeHandle = Mesh->RegisterOnBoneTransformsFinalizedDelegate(
		FOnBoneTransformsFinalizedMultiCast::FDelegate::CreateUObject(
			this, &UNPCBodyMotionComponent::OnBoneTransformsFinalized));
	bDelegateRegistered = FinalizeHandle.IsValid();
}

void UNPCBodyMotionComponent::UnregisterFinalizeDelegate()
{
	if (!bDelegateRegistered)
	{
		return;
	}
	if (USkeletalMeshComponent* Mesh = CachedBodyMesh.Get())
	{
		Mesh->UnregisterOnBoneTransformsFinalizedDelegate(FinalizeHandle);
	}
	FinalizeHandle.Reset();
	bDelegateRegistered = false;
}

// -----------------------------------------------------------------------------
// The finalize hook — post-anim, pre-render
// -----------------------------------------------------------------------------

void UNPCBodyMotionComponent::OnBoneTransformsFinalized()
{
	USkeletalMeshComponent* Mesh = CachedBodyMesh.Get();
	if (!Mesh)
	{
		return;
	}

	USkinnedAsset* SkinnedAsset = Mesh->GetSkinnedAsset();
	if (!SkinnedAsset)
	{
		return;
	}

	const FReferenceSkeleton& RefSkel = SkinnedAsset->GetRefSkeleton();

	// IMPORTANT: by the time this delegate fires, USkinnedMeshComponent has
	// ALREADY called FlipEditableSpaceBases() inside FinalizeBoneTransform.
	// That means GetComponentSpaceTransforms() (const) is now the buffer the
	// renderer will read this frame, and GetEditableComponentSpaceTransforms()
	// is the OTHER (stale) buffer — writes there are thrown away next frame.
	//
	// const_cast here is load-bearing: it's the only way to inject bone
	// overrides from this hook without creating a custom anim graph. The
	// engine's own cloth & control-rig-edit-mode systems use the same
	// delegate at the same point (cloth only reads, we write). Do NOT
	// "clean up" this const_cast to GetEditableComponentSpaceTransforms().
	TArray<FTransform>& CS = const_cast<TArray<FTransform>&>(Mesh->GetComponentSpaceTransforms());
	if (CS.Num() == 0)
	{
		return;
	}

	// Lazy bone-index cache (re-cache if PIE invalidated them).
	if (HeadIdx == INDEX_NONE)
	{
		CacheBoneIndices(RefSkel);
	}

	// Top-down application order. Each later ApplyBoneLayer reads parent CS
	// transforms that include the earlier rotations, so composition is clean.
	// We convert each local-space delta into a component-space pivot rotation
	// inside ApplyBoneLayer using the bone's CURRENT CS transform.
	ApplyBoneLayer(Mesh, RefSkel, CS, Spine01Idx, ComputeSpine01LocalDelta());
	ApplyBoneLayer(Mesh, RefSkel, CS, Spine03Idx, ComputeSpine03LocalDelta());
	ApplyBoneLayer(Mesh, RefSkel, CS, NeckIdx,    ComputeNeckLocalDelta());
	ApplyBoneLayer(Mesh, RefSkel, CS, HeadIdx,    ComputeHeadLocalDelta());
	ApplyBoneLayer(Mesh, RefSkel, CS, ClavLIdx,   ComputeClavicleLLocalDelta());
	ApplyBoneLayer(Mesh, RefSkel, CS, ClavRIdx,   ComputeClavicleRLocalDelta());
	ApplyBoneLayer(Mesh, RefSkel, CS, UArmLIdx,   ComputeUpperArmLLocalDelta());
	ApplyBoneLayer(Mesh, RefSkel, CS, UArmRIdx,   ComputeUpperArmRLocalDelta());

	// DO NOT call MarkRenderDynamicDataDirty — SendRenderDynamicData_Concurrent
	// is already scheduled this frame and will read CS in its current state.
	// DO NOT call FlipEditableSpaceBases — it's protected AND already happened.
}

// -----------------------------------------------------------------------------
// Manual forward kinematics: rotate a bone + all descendants
// -----------------------------------------------------------------------------

void UNPCBodyMotionComponent::ApplyBoneLayer(
	USkeletalMeshComponent* Mesh,
	const FReferenceSkeleton& RefSkel,
	TArray<FTransform>& CS,
	int32 BoneIdx,
	const FQuat& LocalDeltaRot)
{
	if (BoneIdx == INDEX_NONE || !CS.IsValidIndex(BoneIdx))
	{
		return;
	}
	if (LocalDeltaRot.IsIdentity(1e-5f))
	{
		return;
	}

	// Convert the local-space rotation into a component-space pivot rotation
	// centered on BoneIdx's CURRENT component-space location:
	//   CSDelta = BoneCSRot * LocalDelta * BoneCSRot.Inverse()
	// This gives us an "apply around the bone's own pivot" rotation in the
	// component space we're about to mutate.
	const FTransform& BoneCS = CS[BoneIdx];
	const FQuat BoneCSRot = BoneCS.GetRotation();
	const FQuat CSDelta = BoneCSRot * LocalDeltaRot * BoneCSRot.Inverse();
	const FVector Pivot = BoneCS.GetLocation();

	const int32 NumBones = CS.Num();

	// Walk forward from BoneIdx; any bone whose ancestor chain hits BoneIdx
	// is a descendant and gets rotated with us. Ref skeleton parent indices
	// are always strictly less than the child, so we can short-circuit.
	for (int32 i = BoneIdx; i < NumBones; ++i)
	{
		bool bIsDescendantOrSelf = (i == BoneIdx);
		if (!bIsDescendantOrSelf)
		{
			int32 Cur = RefSkel.GetParentIndex(i);
			while (Cur != INDEX_NONE)
			{
				if (Cur == BoneIdx)
				{
					bIsDescendantOrSelf = true;
					break;
				}
				if (Cur < BoneIdx)
				{
					break;  // parent chain went past our root — not a descendant
				}
				Cur = RefSkel.GetParentIndex(Cur);
			}
		}
		if (!bIsDescendantOrSelf)
		{
			continue;
		}

		FTransform& T = CS[i];
		const FVector NewLoc = Pivot + CSDelta.RotateVector(T.GetLocation() - Pivot);
		T.SetLocation(NewLoc);
		T.SetRotation((CSDelta * T.GetRotation()).GetNormalized());
	}
}

// -----------------------------------------------------------------------------
// Per-bone delta computers
// -----------------------------------------------------------------------------

// Weight-shift lower spine. Idle only — during speaking the upper body
// (Spine03) does the work, and thinking is a stationary tell.
FQuat UNPCBodyMotionComponent::ComputeSpine01LocalDelta() const
{
	const float WeightShift = IdleWeightShiftDeg * FMath::Sin(TimeAccum * 2.f * PI * 0.10f);
	const float Roll = IdleAlpha * WeightShift;
	return FQuat(FRotator(0.f, 0.f, Roll));
}

// Breathing lives here — slow pitch oscillation on the upper chest.
// Plus a tiny speaking sway so the chest leads head nods subtly.
FQuat UNPCBodyMotionComponent::ComputeSpine03LocalDelta() const
{
	const float Breath = BreathAmplitudeDeg * FMath::Sin(TimeAccum * 2.f * PI * BreathFrequencyHz);
	const float SpeakSway = SpeakingAlpha * 0.5f * FMath::Sin(TimeAccum * 2.f * PI * 0.8f);
	return FQuat(FRotator(Breath + SpeakSway, 0.f, 0.f));
}

// Neck follows the head subtly so rotations compound naturally across
// the chain instead of a sharp "only the head turns" look.
FQuat UNPCBodyMotionComponent::ComputeNeckLocalDelta() const
{
	const float FollowYaw = IdleAlpha * IdleHeadDriftDeg * 0.25f
		* FMath::Sin(TimeAccum * 2.f * PI * 0.07f);
	const float FollowPitch = SpeakingAlpha * SpeakingHeadNodDeg * 0.3f
		* FMath::Sin(TimeAccum * 2.f * PI * 1.5f);
	return FQuat(FRotator(FollowPitch, FollowYaw, 0.f));
}

// The primary head motion — distinct per state.
FQuat UNPCBodyMotionComponent::ComputeHeadLocalDelta() const
{
	// Idle: slow drift
	const float IdlePitch = IdleHeadDriftDeg * 0.4f * FMath::Sin(TimeAccum * 2.f * PI * 0.12f);
	const float IdleYaw   = IdleHeadDriftDeg        * FMath::Sin(TimeAccum * 2.f * PI * 0.07f);

	// Thinking: slight look-up + head tilt (held, not oscillating)
	const float ThinkPitch = -ThinkingHeadTiltDeg * 0.5f;
	const float ThinkRoll  =  ThinkingHeadTiltDeg;

	// Speaking: ~1.5 Hz phrase-rate nods + micro yaw
	const float SpeakPitch = SpeakingHeadNodDeg          * FMath::Sin(TimeAccum * 2.f * PI * 1.5f);
	const float SpeakYaw   = SpeakingHeadNodDeg * 0.25f  * FMath::Sin(TimeAccum * 2.f * PI * 0.9f);

	const float Pitch = IdleAlpha * IdlePitch + ThinkingAlpha * ThinkPitch + SpeakingAlpha * SpeakPitch;
	const float Yaw   = IdleAlpha * IdleYaw                                + SpeakingAlpha * SpeakYaw;
	const float Roll  =                          ThinkingAlpha * ThinkRoll;

	return FQuat(FRotator(Pitch, Yaw, Roll));
}

// Shoulder micro-motion during speaking. Relax rotation is always applied.
FQuat UNPCBodyMotionComponent::ComputeClavicleLLocalDelta() const
{
	const FQuat Base = FQuat(ClavicleLRelaxRotation);
	const float Shoulder = SpeakingAlpha * SpeakingShoulderDeg
		* FMath::Sin(TimeAccum * 2.f * PI * 1.2f);
	return Base * FQuat(FRotator(0.f, 0.f, Shoulder));
}

FQuat UNPCBodyMotionComponent::ComputeClavicleRLocalDelta() const
{
	const FQuat Base = FQuat(ClavicleRRelaxRotation);
	// Opposite phase so shoulders counter-move subtly.
	const float Shoulder = SpeakingAlpha * SpeakingShoulderDeg
		* FMath::Sin(TimeAccum * 2.f * PI * 1.2f + PI);
	return Base * FQuat(FRotator(0.f, 0.f, Shoulder));
}

// Upperarm relax-down is ALWAYS applied — this is what breaks the T-pose.
// Breathing and speaking layer subtle oscillations on top.
FQuat UNPCBodyMotionComponent::ComputeUpperArmLLocalDelta() const
{
	const FQuat Base = FQuat(UpperArmLRelaxRotation);
	const float Breath = BreathAmplitudeDeg * 0.3f
		* FMath::Sin(TimeAccum * 2.f * PI * BreathFrequencyHz);
	const float Speak  = SpeakingAlpha * SpeakingShoulderDeg
		* FMath::Sin(TimeAccum * 2.f * PI * 1.1f);
	return Base * FQuat(FRotator(0.f, 0.f, Breath + Speak));
}

FQuat UNPCBodyMotionComponent::ComputeUpperArmRLocalDelta() const
{
	const FQuat Base = FQuat(UpperArmRRelaxRotation);
	const float Breath = BreathAmplitudeDeg * 0.3f
		* FMath::Sin(TimeAccum * 2.f * PI * BreathFrequencyHz + PI * 0.5f);
	const float Speak  = SpeakingAlpha * SpeakingShoulderDeg
		* FMath::Sin(TimeAccum * 2.f * PI * 1.1f + PI);
	return Base * FQuat(FRotator(0.f, 0.f, Breath + Speak));
}

// -----------------------------------------------------------------------------
// Voice pipeline handlers — three-hook defense in depth (same as thinking face)
// -----------------------------------------------------------------------------

void UNPCBodyMotionComponent::HandleTranscriptReady(const FString& /*Transcript*/)
{
	TargetState = EBodyState::Thinking;
	ThinkingWatchdog = 0.0f;
	UE_LOG(LogTemp, Verbose, TEXT("BodyMotion: Thinking"));
}

void UNPCBodyMotionComponent::HandleTTSAlignmentReceived(
	const FString& /*Characters*/,
	const TArray<float>& /*StartTimesSec*/,
	const TArray<float>& /*DurationsSec*/)
{
	TargetState = EBodyState::Speaking;
	UE_LOG(LogTemp, Verbose, TEXT("BodyMotion: Speaking (alignment)"));
}

void UNPCBodyMotionComponent::HandleSpeechStarted()
{
	// Fallback for the alignment-missing path in ElevenLabsTTSComponent.
	TargetState = EBodyState::Speaking;
	UE_LOG(LogTemp, Verbose, TEXT("BodyMotion: Speaking (started)"));
}

void UNPCBodyMotionComponent::HandleSpeechFinished()
{
	TargetState = EBodyState::Idle;
	UE_LOG(LogTemp, Verbose, TEXT("BodyMotion: Idle"));
}
