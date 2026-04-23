#include "NPCBodyMotionComponent.h"
#include "NPCBodyIdleAnimInstance.h"

#include "LLM_NPC/Dialogue/WhisperSTTComponent.h"
#include "LLM_NPC/Dialogue/ElevenLabsTTSComponent.h"

#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/SkinnedAsset.h"
#include "ReferenceSkeleton.h"
#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"
#include "Components/ChildActorComponent.h"

UNPCBodyMotionComponent::UNPCBodyMotionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SubsystemName = TEXT("BodyMotion");

	// ---------------------------------------------------------------------
	// Default state poses — CONSERVATIVE MetaHuman-body-safe defaults.
	// ---------------------------------------------------------------------
	//
	// IMPORTANT: This NPC uses the MetaHuman body skeleton (342 bones), NOT
	// the UE5 Mannequin (~150 bones). The two skeletons have DIFFERENT local
	// bone axis conventions — the earlier "yaw drops the arm from T-pose"
	// assumption was a UE5 Mannequin rule that does not hold for MetaHuman.
	//
	// MetaHumans also ship with an A-POSE reference already (arms hanging at
	// the sides). That means zero-delta from ref pose == arms hanging =="idle"
	// — we do NOT need to rotate arms out of T-pose. Adding 75° of yaw to an
	// already-hanging arm is what produced the "raised arm with bent elbow"
	// teapot look.
	//
	// Therefore: all arm/hand rotations start at ZERO in every pose. The
	// MetaHuman ref pose IS the idle upper-body pose, and we only touch the
	// torso/head/pelvis/thigh bones which have more predictable axis
	// semantics (smaller rotations, any axis roughly works for small
	// weight-shift / head-tilt amounts).
	//
	// Dial in thinking/speaking arm rotations via the Details panel after
	// observing the ref pose in PIE. The ref-pose log at init prints the
	// actual upperarm_l/r local rotations so you know your starting point.
	// ---------------------------------------------------------------------

	// ---- AXIS FACTS (from ref-pose log, NOT guesses any more) ----
	//
	// MetaHuman body skeleton ref pose:
	//   upperarm_l/r : P=-46, Y=2.8, R=-4.6   (pitch = up/down axis)
	//   lowerarm_l/r : P=0,   Y=36.6, R=0     (yaw   = elbow bend axis)
	//
	// Both arms have IDENTICAL local rotations because the CLAVICLES carry
	// the L/R mirroring (clavicle_l yaw=-162.9 vs clavicle_r yaw=17.1, a
	// ~180° rotation flips the child coordinate frame). So a positive-pitch
	// delta on upperarm_l and upperarm_r rotates BOTH arms in their local
	// pitch axis — which corresponds to raising both arms upward when added
	// to the -46 A-pose baseline. We use SAME-SIGN deltas on L and R.
	//
	// To RAISE the arm from A-pose:    add POSITIVE pitch to upperarm
	// To BEND the elbow more:          add POSITIVE yaw to lowerarm
	// ---------------------------------------------------------------------

	// ---- ARM DROP BASELINE ----
	// MetaHuman ref pose has upperarm.pitch = -46 → A-pose (arms slightly out
	// from body). User wants arms hanging vertically ("I" pose, relaxed).
	// Apply -30 delta → effective upperarm pitch = -46 + (-30) = -76, close
	// to straight down. This is the "base relaxed arms" used in every state
	// except where a state explicitly overrides (ThinkingPose.UpperArmR).
	const FRotator ArmDropDelta = FRotator(-30.f, 0.f, 0.f);

	// IdlePose — arms dropped (I-pose), slight pelvis weight shift left,
	// counter-rolled spine, tiny head lift, contrapposto on left leg.
	IdlePose.Pelvis    = FRotator(0.f, 0.f,  2.f);
	IdlePose.Spine01   = FRotator(0.f, 0.f, -1.f);
	IdlePose.Spine03   = FRotator(0.f, 0.f, -1.f);
	IdlePose.Head      = FRotator(0.f, 0.f,  1.f);
	IdlePose.UpperArmL = ArmDropDelta;
	IdlePose.UpperArmR = ArmDropDelta;
	IdlePose.ThighL    = FRotator(0.f, 0.f, -6.f);     // planted weight leg
	IdlePose.ThighR    = FRotator(10.f, 0.f,  8.f);    // non-weight: visible forward/out

	// ThinkingPose — right hand toward mouth, NATURAL arm geometry.
	//   upperarm_r pitch = +45   → lifts arm from ref -46 to net -1 (near horizontal).
	//                              Elbow is now up around shoulder height — natural
	//                              starting point for a hand-to-face gesture.
	//   upperarm_r yaw   = +15   → rotates the upper arm inward slightly, bringing
	//                              the elbow toward the chest center so the forearm
	//                              can fold up toward the mouth (not the shoulder).
	//   lowerarm_r yaw   = +60   → natural elbow bend. Ref is 36, net 96 — just past
	//                              90° which is the sweet spot for a relaxed elbow.
	//                              (Previous +140 put the forearm at 176°, almost
	//                              fully folded onto the upperarm — looked broken.)
	// Geometry: with elbow at shoulder height and a 96° bend, the forearm points
	// upward and slightly inward, bringing the hand to roughly the face/mouth area.
	// Left arm stays at drop baseline so it hangs relaxed.
	ThinkingPose.Pelvis    = FRotator(0.f, 0.f,  3.f);
	ThinkingPose.Spine01   = FRotator(-2.f, 0.f, -2.f);
	ThinkingPose.Spine03   = FRotator(-2.f, 0.f, -1.f);
	ThinkingPose.Head      = FRotator(-5.f, 10.f, 5.f);
	ThinkingPose.UpperArmL = ArmDropDelta;                  // L stays dropped
	// R arm: pitch +55 → net ref -46+55 = +9° (just above horizontal, elbow at face height)
	// yaw +25 → rotate inward so forearm folds toward the face, not outward
	ThinkingPose.UpperArmR = FRotator(55.f, 25.f, 0.f);
	// Elbow bend: ref lowerarm yaw=36.6, +70 → net 106.6° — sharp fold pointing hand at face
	ThinkingPose.LowerArmR = FRotator(0.f, 70.f, 0.f);
	// Wrist: tilt slightly to aim the fingers toward the chin/mouth
	ThinkingPose.HandR     = FRotator(-15.f, -10.f, 0.f);
	ThinkingPose.ThighL    = FRotator(0.f, 0.f, -7.f);    // visible contrapposto
	ThinkingPose.ThighR    = FRotator(12.f, 0.f, 10.f);   // even more forward while thinking

	// SpeakingPose — base speaking: weight on RIGHT leg, subtle forward
	// engagement lean. BOTH arms dropped (relaxed I-pose, not rigid).
	// Head nods are added as sine overlay in ComputeBoneLocalDelta.
	SpeakingPose.Pelvis    = FRotator(0.f, 0.f, -3.f);
	SpeakingPose.Spine01   = FRotator(0.f, 0.f,  2.f);
	SpeakingPose.Spine03   = FRotator(-1.f, 0.f, 2.f);
	SpeakingPose.Head      = FRotator(-2.f, 0.f, 0.f);
	SpeakingPose.UpperArmL = ArmDropDelta;
	SpeakingPose.UpperArmR = ArmDropDelta;
	SpeakingPose.ThighL    = FRotator(10.f, 0.f, -8.f);   // non-weight leg forward (mirror idle)
	SpeakingPose.ThighR    = FRotator(0.f, 0.f,  6.f);    // weight leg, slight outward

	// SpeakingGesturePose — arms identical to SpeakingPose so the gesture
	// cycle produces NO arm motion (user request: arms stay still during speech).
	// Only torso/head/leg deltas differ slightly for a very subtle weight shift.
	SpeakingGesturePose.Pelvis    = FRotator(0.f, 0.f, -4.f);
	SpeakingGesturePose.Spine01   = FRotator(0.f, 0.f,  3.f);
	SpeakingGesturePose.Spine03   = FRotator(-2.f, 0.f, 3.f);
	SpeakingGesturePose.Head      = FRotator(-3.f, 0.f, 0.f);
	// Arms same as SpeakingPose (ArmDropDelta) — gesture cycle won't move them.
	SpeakingGesturePose.UpperArmL = ArmDropDelta;
	SpeakingGesturePose.UpperArmR = ArmDropDelta;
	SpeakingGesturePose.LowerArmL = FRotator::ZeroRotator;
	SpeakingGesturePose.LowerArmR = FRotator::ZeroRotator;
	SpeakingGesturePose.ThighL    = FRotator(10.f, 0.f, -8.f);
	SpeakingGesturePose.ThighR    = FRotator(0.f, 0.f,  6.f);
}

// -----------------------------------------------------------------------------
// Lifecycle
// -----------------------------------------------------------------------------

void UNPCBodyMotionComponent::InitializeSubsystem()
{
	UE_LOG(LogTemp, Warning, TEXT("BodyMotion: InitializeSubsystem START on owner '%s'"),
		GetOwner() ? *GetOwner()->GetName() : TEXT("<null>"));

	Super::InitializeSubsystem();

	AActor* Owner = GetOwner();
	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("BodyMotion: InitializeSubsystem — no owner, aborting"));
		return;
	}

	CachedBodyMesh = FindBodyMesh(Owner);
	if (CachedBodyMesh.IsValid())
	{
		if (USkinnedAsset* SkinnedAsset = CachedBodyMesh->GetSkinnedAsset())
		{
			CacheBoneIndices(SkinnedAsset->GetRefSkeleton());
		}
		else
		{
			UE_LOG(LogTemp, Warning,
				TEXT("BodyMotion: Body mesh '%s' has no SkinnedAsset — bone indices will stay -1"),
				*CachedBodyMesh->GetName());
		}

		UClass* ExistingAnimClass = CachedBodyMesh->GetAnimClass();
		UE_LOG(LogTemp, Warning,
			TEXT("BodyMotion: Body mesh '%s' existing AnimClass: %s"),
			*CachedBodyMesh->GetName(),
			ExistingAnimClass ? *ExistingAnimClass->GetName() : TEXT("<none>"));

		if (!ExistingAnimClass)
		{
			UE_LOG(LogTemp, Warning,
				TEXT("BodyMotion: Assigning UNPCBodyIdleAnimInstance to body mesh so the anim pipeline runs"));
			CachedBodyMesh->SetAnimInstanceClass(UNPCBodyIdleAnimInstance::StaticClass());
		}

		CachedBodyMesh->SetComponentTickEnabled(true);
		CachedBodyMesh->bEnableUpdateRateOptimizations = false;

		RegisterFinalizeDelegate();
		UE_LOG(LogTemp, Warning,
			TEXT("BodyMotion: Bound to body mesh '%s' on owner '%s' — delegate registered=%d"),
			*CachedBodyMesh->GetName(), *Owner->GetName(), bDelegateRegistered ? 1 : 0);
	}
	else
	{
		UE_LOG(LogTemp, Error,
			TEXT("BodyMotion: No body skeletal mesh found on '%s'"),
			*Owner->GetName());
	}

	// Voice pipeline — FindComponentByClass so we hit the same TTS instance
	// lip sync and thinking face subscribe to (pre-existing double-subobject
	// quirk on ANPCCharacter).
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
		CachedTTS->OnSpeechError.AddDynamic(
			this, &UNPCBodyMotionComponent::HandleSpeechError);
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
		CachedTTS->OnSpeechError.RemoveDynamic(
			this, &UNPCBodyMotionComponent::HandleSpeechError);
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

	TimeAccum += DeltaTime;

	// Thinking watchdog — belt to the OnSpeechError suspenders.
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

	const float IdleTarget     = (TargetState == EBodyState::Idle)     ? 1.0f : 0.0f;
	const float ThinkingTarget = (TargetState == EBodyState::Thinking) ? 1.0f : 0.0f;
	const float SpeakingTarget = (TargetState == EBodyState::Speaking) ? 1.0f : 0.0f;
	IdleAlpha     = FMath::FInterpTo(IdleAlpha,     IdleTarget,     DeltaTime, StateBlendSpeed);
	ThinkingAlpha = FMath::FInterpTo(ThinkingAlpha, ThinkingTarget, DeltaTime, StateBlendSpeed);
	SpeakingAlpha = FMath::FInterpTo(SpeakingAlpha, SpeakingTarget, DeltaTime, StateBlendSpeed);

	// Head-turn Reacting overlay: expire the target alpha once the duration
	// elapses. Actual Head-bone application happens in OnBoneTransformsFinalized.
	if (HeadTurnTargetAlpha > 0.0f)
	{
		if (const UWorld* World = GetWorld())
		{
			if (World->GetTimeSeconds() >= HeadTurnExpireTime)
			{
				HeadTurnTargetAlpha = 0.0f;
			}
		}
	}
	HeadTurnAlpha = FMath::FInterpTo(HeadTurnAlpha, HeadTurnTargetAlpha, DeltaTime, HeadTurnBlendSpeed);

	// PIE-restart safety: re-acquire the mesh + delegate if invalidated.
	if (!CachedBodyMesh.IsValid())
	{
		UnregisterFinalizeDelegate();
		PelvisIdx = Spine01Idx = Spine03Idx = NeckIdx = HeadIdx = INDEX_NONE;
		ClavLIdx = ClavRIdx = UArmLIdx = UArmRIdx = INDEX_NONE;
		LArmLIdx = LArmRIdx = HandLIdx = HandRIdx = INDEX_NONE;
		ThighLIdx = ThighRIdx = INDEX_NONE;

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
// Body mesh discovery + bone cache
// -----------------------------------------------------------------------------

USkeletalMeshComponent* UNPCBodyMotionComponent::FindBodyMesh(AActor* Owner) const
{
	if (!Owner)
	{
		return nullptr;
	}

	// Covers three layouts:
	//   1) body mesh directly on the owner (ACharacter::Mesh)
	//   2) body mesh inside a ChildActorComponent (BP_NPC_Test -> BP_Hana)
	//   3) body mesh two levels deep (BP_NPC_Test -> wrapper -> rig)
	// Prefers a mesh named "Body" with a SkinnedAsset, falls back to any
	// non-Face skeletal mesh. Mirrors FindFaceMesh's child-actor walk.
	auto SearchForBody = [](AActor* SearchActor) -> USkeletalMeshComponent*
	{
		if (!SearchActor) return nullptr;

		TArray<USkeletalMeshComponent*> SkeletalMeshes;
		SearchActor->GetComponents<USkeletalMeshComponent>(SkeletalMeshes);

		for (USkeletalMeshComponent* SMC : SkeletalMeshes)
		{
			if (SMC && SMC->GetSkinnedAsset() && SMC->GetName().Contains(TEXT("Body")))
			{
				return SMC;
			}
		}
		for (USkeletalMeshComponent* SMC : SkeletalMeshes)
		{
			if (SMC && SMC->GetSkinnedAsset() && !SMC->GetName().Contains(TEXT("Face")))
			{
				return SMC;
			}
		}
		return nullptr;
	};

	if (USkeletalMeshComponent* Found = SearchForBody(Owner))
	{
		UE_LOG(LogTemp, Warning, TEXT("BodyMotion: FindBodyMesh — found '%s' directly on owner '%s'"),
			*Found->GetName(), *Owner->GetName());
		return Found;
	}

	TArray<UChildActorComponent*> ChildActors;
	Owner->GetComponents<UChildActorComponent>(ChildActors);
	for (UChildActorComponent* CAC : ChildActors)
	{
		if (!CAC || !CAC->GetChildActor()) continue;

		AActor* ChildActor = CAC->GetChildActor();
		if (USkeletalMeshComponent* Found = SearchForBody(ChildActor))
		{
			UE_LOG(LogTemp, Warning,
				TEXT("BodyMotion: FindBodyMesh — found '%s' in ChildActor '%s' under owner '%s'"),
				*Found->GetName(), *ChildActor->GetName(), *Owner->GetName());
			return Found;
		}

		TArray<UChildActorComponent*> NestedChildren;
		ChildActor->GetComponents<UChildActorComponent>(NestedChildren);
		for (UChildActorComponent* Nested : NestedChildren)
		{
			if (!Nested || !Nested->GetChildActor()) continue;
			if (USkeletalMeshComponent* Found = SearchForBody(Nested->GetChildActor()))
			{
				UE_LOG(LogTemp, Warning,
					TEXT("BodyMotion: FindBodyMesh — found '%s' in nested ChildActor '%s' under owner '%s'"),
					*Found->GetName(), *Nested->GetChildActor()->GetName(), *Owner->GetName());
				return Found;
			}
		}
	}

	UE_LOG(LogTemp, Error,
		TEXT("BodyMotion: FindBodyMesh — NO body mesh found on '%s'"), *Owner->GetName());
	return nullptr;
}

void UNPCBodyMotionComponent::CacheBoneIndices(const FReferenceSkeleton& RefSkel)
{
	PelvisIdx  = RefSkel.FindBoneIndex(PelvisBoneName);
	Spine01Idx = RefSkel.FindBoneIndex(Spine01BoneName);
	Spine03Idx = RefSkel.FindBoneIndex(Spine03BoneName);
	NeckIdx    = RefSkel.FindBoneIndex(NeckBoneName);
	HeadIdx    = RefSkel.FindBoneIndex(HeadBoneName);
	ClavLIdx   = RefSkel.FindBoneIndex(ClavicleLBoneName);
	ClavRIdx   = RefSkel.FindBoneIndex(ClavicleRBoneName);
	UArmLIdx   = RefSkel.FindBoneIndex(UpperArmLBoneName);
	UArmRIdx   = RefSkel.FindBoneIndex(UpperArmRBoneName);
	LArmLIdx   = RefSkel.FindBoneIndex(LowerArmLBoneName);
	LArmRIdx   = RefSkel.FindBoneIndex(LowerArmRBoneName);
	HandLIdx   = RefSkel.FindBoneIndex(HandLBoneName);
	HandRIdx   = RefSkel.FindBoneIndex(HandRBoneName);
	ThighLIdx  = RefSkel.FindBoneIndex(ThighLBoneName);
	ThighRIdx  = RefSkel.FindBoneIndex(ThighRBoneName);

	UE_LOG(LogTemp, Warning,
		TEXT("BodyMotion: Bone indices — Pelvis=%d S01=%d S03=%d Neck=%d Head=%d ClavL/R=%d/%d UArmL/R=%d/%d LArmL/R=%d/%d HandL/R=%d/%d ThighL/R=%d/%d (RefSkel has %d bones)"),
		PelvisIdx, Spine01Idx, Spine03Idx, NeckIdx, HeadIdx,
		ClavLIdx, ClavRIdx, UArmLIdx, UArmRIdx,
		LArmLIdx, LArmRIdx, HandLIdx, HandRIdx,
		ThighLIdx, ThighRIdx, RefSkel.GetNum());

	// DIAGNOSTIC: dump the local-space ref-pose rotation of key bones so we
	// can see what the MetaHuman body skeleton's natural arm position is.
	// If upperarm_l/r are already at a non-zero rotation in the ref pose,
	// that's the A-pose baseline and we should leave arm deltas at zero.
	auto LogRefBone = [&RefSkel](const TCHAR* Label, int32 Idx)
	{
		if (Idx == INDEX_NONE) return;
		const TArray<FTransform>& RefPose = RefSkel.GetRefBonePose();
		if (!RefPose.IsValidIndex(Idx)) return;
		const FTransform& T = RefPose[Idx];
		const FRotator R = T.GetRotation().Rotator();
		const FVector  Loc = T.GetLocation();
		UE_LOG(LogTemp, Warning,
			TEXT("BodyMotion: RefPose[%s] LocalRot=(P=%.1f Y=%.1f R=%.1f) LocalLoc=(X=%.1f Y=%.1f Z=%.1f)"),
			Label, R.Pitch, R.Yaw, R.Roll, Loc.X, Loc.Y, Loc.Z);
	};
	LogRefBone(TEXT("UpperArmL"), UArmLIdx);
	LogRefBone(TEXT("UpperArmR"), UArmRIdx);
	LogRefBone(TEXT("LowerArmL"), LArmLIdx);
	LogRefBone(TEXT("LowerArmR"), LArmRIdx);
	LogRefBone(TEXT("ClavicleL"), ClavLIdx);
	LogRefBone(TEXT("ClavicleR"), ClavRIdx);
	LogRefBone(TEXT("Spine03"),   Spine03Idx);
	LogRefBone(TEXT("Head"),      HeadIdx);

	if (PelvisIdx == INDEX_NONE && Spine01Idx == INDEX_NONE && HeadIdx == INDEX_NONE)
	{
		UE_LOG(LogTemp, Error,
			TEXT("BodyMotion: NONE of the default bone names were found! Rig is not MetaHuman standard. First 10 ref bones:"));
		for (int32 i = 0; i < FMath::Min(RefSkel.GetNum(), 10); ++i)
		{
			UE_LOG(LogTemp, Error, TEXT("  RefBone[%d]: %s"), i, *RefSkel.GetBoneName(i).ToString());
		}
	}
}

// -----------------------------------------------------------------------------
// Finalize delegate
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
// The finalize hook
// -----------------------------------------------------------------------------

void UNPCBodyMotionComponent::OnBoneTransformsFinalized()
{
	// Verbose-level diagnostic log (was Warning during bring-up).
	static int32 FinalizeCallCount = 0;
	if ((FinalizeCallCount++ % 60) == 0)
	{
		UE_LOG(LogTemp, Verbose,
			TEXT("BodyMotion: OnBoneTransformsFinalized fired (#%d) — IdleA=%.2f ThinkA=%.2f SpeakA=%.2f"),
			FinalizeCallCount, IdleAlpha, ThinkingAlpha, SpeakingAlpha);
	}

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

	// By the time this delegate fires, FlipEditableSpaceBases has already
	// happened inside FinalizeBoneTransform. GetComponentSpaceTransforms()
	// (const) is the buffer the renderer will read this frame. const_cast
	// is load-bearing — do NOT switch to GetEditableComponentSpaceTransforms
	// (that's the stale buffer now).
	TArray<FTransform>& CS = const_cast<TArray<FTransform>&>(Mesh->GetComponentSpaceTransforms());
	if (CS.Num() == 0)
	{
		return;
	}

	if (HeadIdx == INDEX_NONE)
	{
		CacheBoneIndices(RefSkel);
	}

	// Helper: compute local delta for a bone, convert to quat, and apply.
	auto Apply = [&](EBodyMotionBone Bone, int32 Idx)
	{
		if (Idx == INDEX_NONE) return;
		const FRotator LocalRot = ComputeBoneLocalDelta(Bone);
		ApplyBoneLayer(Mesh, RefSkel, CS, Idx, FQuat(LocalRot));
	};

	// Full-body procedural FK — gated so the MetaHuman template body animation
	// (driven by UTemplateAnimationDriverComponent) can play unobstructed in
	// the default deployment. Flip bProceduralFKEnabled on to revert to the
	// legacy procedural-only path.
	if (bProceduralFKEnabled)
	{
		// Top-down order so later calls read parents that include earlier rots.
		// Pelvis → trunk chain → left arm chain → right arm chain → legs.
		Apply(EBodyMotionBone::Pelvis,    PelvisIdx);
		Apply(EBodyMotionBone::Spine01,   Spine01Idx);
		Apply(EBodyMotionBone::Spine03,   Spine03Idx);
		Apply(EBodyMotionBone::Neck,      NeckIdx);
		Apply(EBodyMotionBone::Head,      HeadIdx);
		Apply(EBodyMotionBone::ClavicleL, ClavLIdx);
		Apply(EBodyMotionBone::UpperArmL, UArmLIdx);
		Apply(EBodyMotionBone::LowerArmL, LArmLIdx);
		Apply(EBodyMotionBone::HandL,     HandLIdx);
		Apply(EBodyMotionBone::ClavicleR, ClavRIdx);
		Apply(EBodyMotionBone::UpperArmR, UArmRIdx);
		Apply(EBodyMotionBone::LowerArmR, LArmRIdx);
		Apply(EBodyMotionBone::HandR,     HandRIdx);
		Apply(EBodyMotionBone::ThighL,    ThighLIdx);
		Apply(EBodyMotionBone::ThighR,    ThighRIdx);
	}

	// Head-turn Reacting overlay — Head bone only, additive on top of whatever
	// pose is currently there (template animation or procedural FK above).
	// Computed in component space from the current Head CS transform and the
	// world-space target; clamped to ±HeadTurnMaxDeg so the NPC never
	// pops her head behind her.
	if (HeadTurnAlpha > KINDA_SMALL_NUMBER && HeadIdx != INDEX_NONE && HeadIdx < CS.Num())
	{
		const FTransform CompToWorld = Mesh->GetComponentTransform();
		const FTransform HeadCS = CS[HeadIdx];
		const FVector HeadWorldLoc = CompToWorld.TransformPosition(HeadCS.GetLocation());
		const FVector ToTargetWorld = HeadTurnTargetWorldLoc - HeadWorldLoc;

		if (!ToTargetWorld.IsNearlyZero())
		{
			// Express the aim direction in the Head bone's component-space frame.
			const FVector ToTargetComp = CompToWorld.InverseTransformVectorNoScale(ToTargetWorld).GetSafeNormal();

			// Head forward in the ref pose: MetaHuman head's local-forward tends
			// to be -Y or +X depending on the rig; we derive it from the current
			// Head CS rotation's X axis so this stays rig-agnostic.
			const FVector HeadForwardComp = HeadCS.GetRotation().GetAxisX();

			// Yaw (horizontal) + pitch (vertical) toward target.
			const float TargetYawRad   = FMath::Atan2(ToTargetComp.Y, ToTargetComp.X) - FMath::Atan2(HeadForwardComp.Y, HeadForwardComp.X);
			const float TargetPitchRad = FMath::Asin(ToTargetComp.Z) - FMath::Asin(HeadForwardComp.Z);

			const float MaxRad = FMath::DegreesToRadians(HeadTurnMaxDeg);
			const float Yaw    = FMath::Clamp(TargetYawRad,   -MaxRad, MaxRad) * HeadTurnAlpha;
			const float Pitch  = FMath::Clamp(TargetPitchRad, -MaxRad, MaxRad) * HeadTurnAlpha;

			const FRotator HeadDelta(FMath::RadiansToDegrees(Pitch), FMath::RadiansToDegrees(Yaw), 0.0f);
			ApplyBoneLayer(Mesh, RefSkel, CS, HeadIdx, FQuat(HeadDelta));
		}
	}
}

// -----------------------------------------------------------------------------
// Pose evaluation
// -----------------------------------------------------------------------------

const FRotator& UNPCBodyMotionComponent::GetPoseRotator(const FBodyMotionPose& Pose, EBodyMotionBone Bone)
{
	switch (Bone)
	{
	case EBodyMotionBone::Pelvis:    return Pose.Pelvis;
	case EBodyMotionBone::Spine01:   return Pose.Spine01;
	case EBodyMotionBone::Spine03:   return Pose.Spine03;
	case EBodyMotionBone::Neck:      return Pose.Neck01;
	case EBodyMotionBone::Head:      return Pose.Head;
	case EBodyMotionBone::ClavicleL: return Pose.ClavicleL;
	case EBodyMotionBone::ClavicleR: return Pose.ClavicleR;
	case EBodyMotionBone::UpperArmL: return Pose.UpperArmL;
	case EBodyMotionBone::UpperArmR: return Pose.UpperArmR;
	case EBodyMotionBone::LowerArmL: return Pose.LowerArmL;
	case EBodyMotionBone::LowerArmR: return Pose.LowerArmR;
	case EBodyMotionBone::HandL:     return Pose.HandL;
	case EBodyMotionBone::HandR:     return Pose.HandR;
	case EBodyMotionBone::ThighL:    return Pose.ThighL;
	case EBodyMotionBone::ThighR:    return Pose.ThighR;
	}
	static const FRotator Zero = FRotator::ZeroRotator;
	return Zero;
}

FRotator UNPCBodyMotionComponent::ComputeBoneLocalDelta(EBodyMotionBone Bone) const
{
	// --- 1. Speaking pose cycles slowly between base and gesture variants. ---
	// GestureBlend eases 0..1..0 on a cos curve over SpeakingGestureCycleSec.
	const float CyclePhase = (SpeakingGestureCycleSec > KINDA_SMALL_NUMBER)
		? (TimeAccum * 2.f * PI / SpeakingGestureCycleSec)
		: 0.f;
	const float GestureBlend = 0.5f * (1.f - FMath::Cos(CyclePhase));

	const FRotator& SpeakBase    = GetPoseRotator(SpeakingPose, Bone);
	const FRotator& SpeakGesture = GetPoseRotator(SpeakingGesturePose, Bone);
	const FRotator SpeakBlended  = FBodyMotionPose::Lerp(SpeakBase, SpeakGesture, GestureBlend);

	// --- 2. Blend all three states by their alphas. ---
	const FRotator& IdleRot  = GetPoseRotator(IdlePose, Bone);
	const FRotator& ThinkRot = GetPoseRotator(ThinkingPose, Bone);
	FRotator Blended = FBodyMotionPose::Blend(
		IdleRot,     IdleAlpha,
		ThinkRot,    ThinkingAlpha,
		SpeakBlended, SpeakingAlpha);

	// --- 3. Sine overlays for specific bones. ---
	//
	// For speaking overlays, we use SpeakingAlpha² instead of SpeakingAlpha.
	// Why: the linear state alpha decays asymptotically via FInterpTo, so at
	// 1 second post-speech with StateBlendSpeed=1.2 we still have α ≈ 0.3.
	// Linear × 3° amplitude = 0.9° of residual head nod — visible as "wobble
	// that doesn't stop." Squaring gives α² = 0.09, amplifying the decay so
	// the visible sine fades out ~6× faster than the pose blend. At peak
	// (α=1) it's identical to linear; the difference only kicks in on the
	// tail. This is a standard animation-blending trick for killing residual
	// motion without making the state transition itself feel abrupt.
	const float SpeakDecay = SpeakingAlpha * SpeakingAlpha;

	switch (Bone)
	{
	case EBodyMotionBone::Spine03:
	{
		// Breathing — always on but very subtle. Higher amplitudes propagate
		// via forward kinematics to head and arms, which reads as "wobble"
		// on the entire upper body. Keep this below 1° to stay imperceptible.
		const float Breath = BreathAmplitudeDeg
			* FMath::Sin(TimeAccum * 2.f * PI * BreathFrequencyHz);
		Blended.Pitch += Breath;
		break;
	}
	case EBodyMotionBone::Head:
	{
		// Thinking: non-rhythmic contemplative head motion.
		// Two incommensurable periods (~13.7 s and ~9.1 s) beat together to
		// create a slowly-varying signal that never repeats in a regular rhythm.
		// A third independent period (~11.2 s) adds a small pitch component.
		// All three are weighted by ThinkingAlpha so the motion smoothly fades
		// in when thinking starts and out when speaking/idle takes over.
		if (ThinkingAlpha > 0.001f && ThinkingHeadContemplativeDeg > 0.f)
		{
			const float ContemplYaw = ThinkingAlpha * ThinkingHeadContemplativeDeg
				* (0.6f * FMath::Sin(TimeAccum * 2.f * PI * 0.073f)   // ~13.7 s period
				 + 0.4f * FMath::Sin(TimeAccum * 2.f * PI * 0.11f));  // ~9.1 s period
			const float ContemplPitch = ThinkingAlpha * ThinkingHeadContemplativeDeg * 0.35f
				* FMath::Sin(TimeAccum * 2.f * PI * 0.089f);           // ~11.2 s period
			Blended.Yaw   += ContemplYaw;
			Blended.Pitch += ContemplPitch;
		}

		// Idle: slow yaw drift (off by default — set IdleHeadDriftDeg > 0 to enable).
		if (IdleHeadDriftDeg > 0.f)
		{
			Blended.Yaw += IdleAlpha * IdleHeadDriftDeg
				* FMath::Sin(TimeAccum * 2.f * PI * 0.07f);
		}

		// Speaking head nod: off by default (SpeakingHeadNodDeg = 0).
		// Re-enable in the Details panel if you want rhythmic nods during speech.
		if (SpeakingHeadNodDeg > 0.f)
		{
			const float SpeakNod = SpeakDecay * SpeakingHeadNodDeg
				* FMath::Sin(TimeAccum * 2.f * PI * 1.5f);
			Blended.Pitch += SpeakNod;
		}
		break;
	}
	case EBodyMotionBone::ClavicleL:
	{
		// Subtle shoulder micro-motion while speaking. Alpha-squared decay.
		const float Shoulder = SpeakDecay * SpeakingShoulderDeg
			* FMath::Sin(TimeAccum * 2.f * PI * 1.2f);
		Blended.Roll += Shoulder;
		break;
	}
	case EBodyMotionBone::ClavicleR:
	{
		// Counter-phase on the other shoulder.
		const float Shoulder = SpeakDecay * SpeakingShoulderDeg
			* FMath::Sin(TimeAccum * 2.f * PI * 1.2f + PI);
		Blended.Roll += Shoulder;
		break;
	}
	default:
		break;
	}

	return Blended;
}

// -----------------------------------------------------------------------------
// Forward-kinematics propagation (unchanged from previous implementation)
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

	const FTransform& BoneCS = CS[BoneIdx];
	const FQuat BoneCSRot = BoneCS.GetRotation();
	const FQuat CSDelta = BoneCSRot * LocalDeltaRot * BoneCSRot.Inverse();
	const FVector Pivot = BoneCS.GetLocation();

	const int32 NumBones = CS.Num();

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
					break;
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
// Voice pipeline handlers
// -----------------------------------------------------------------------------

void UNPCBodyMotionComponent::HandleTranscriptReady(const FString& /*Transcript*/)
{
	TargetState = EBodyState::Thinking;
	ThinkingWatchdog = 0.0f;
	UE_LOG(LogTemp, Warning, TEXT("BodyMotion: STATE -> Thinking (OnTranscriptReady)"));
}

void UNPCBodyMotionComponent::HandleTTSAlignmentReceived(
	const FString& /*Characters*/,
	const TArray<float>& /*StartTimesSec*/,
	const TArray<float>& /*DurationsSec*/)
{
	TargetState = EBodyState::Speaking;
	UE_LOG(LogTemp, Warning, TEXT("BodyMotion: STATE -> Speaking (OnTTSAlignmentReceived)"));
}

void UNPCBodyMotionComponent::HandleSpeechStarted()
{
	TargetState = EBodyState::Speaking;
	UE_LOG(LogTemp, Warning, TEXT("BodyMotion: STATE -> Speaking (OnSpeechStarted)"));
}

void UNPCBodyMotionComponent::HandleSpeechFinished()
{
	TargetState = EBodyState::Idle;
	UE_LOG(LogTemp, Warning, TEXT("BodyMotion: STATE -> Idle (OnSpeechFinished)"));
}

void UNPCBodyMotionComponent::HandleSpeechError(int32 ResponseCode, const FString& ErrorBody)
{
	UE_LOG(LogTemp, Warning,
		TEXT("BodyMotion: HandleSpeechError — code=%d, body=%s — returning to Idle."),
		ResponseCode, *ErrorBody);
	TargetState = EBodyState::Idle;
	ThinkingWatchdog = 0.0f;
}

void UNPCBodyMotionComponent::TriggerReactToItem(const FVector& WorldLoc, float DurationSec)
{
	HeadTurnTargetWorldLoc = WorldLoc;
	HeadTurnTargetAlpha = 1.0f;
	if (const UWorld* World = GetWorld())
	{
		HeadTurnExpireTime = World->GetTimeSeconds() + FMath::Max(DurationSec, 0.1f);
	}
}
