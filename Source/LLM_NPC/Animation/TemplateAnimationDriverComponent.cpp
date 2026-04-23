#include "TemplateAnimationDriverComponent.h"
#include "LLM_NPC/Emotion/EmotionComponent.h"
#include "LLM_NPC/Dialogue/DialogueComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimSequence.h"
#include "Components/ChildActorComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Misc/Paths.h"
#include "UObject/Package.h"

UTemplateAnimationDriverComponent::UTemplateAnimationDriverComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PrePhysics;
	SubsystemName = TEXT("TemplateAnimationDriver");

	BuildDefaultEmotionMappings();
	BuildDefaultClipMappings();
	BuildDefaultSlotAnimBPs();
}

void UTemplateAnimationDriverComponent::BuildDefaultSlotAnimBPs()
{
	// Point at the minimal slot-host AnimBPs the user authored for Friend.
	// These are project assets (not plugin content) — each has a single
	// Slot node named "DefaultSlot" connected to Output Pose. Other NPCs
	// (not Friend) leave these null and fall back to PlayAnimation hard-swap.
	//
	// Path format: /Game/.../Asset.Asset_C — the trailing _C refers to the
	// generated UClass, which is what TSoftClassPtr expects.
	FaceSlotAnimBP = TSoftClassPtr<UAnimInstance>(FSoftObjectPath(
		TEXT("/Game/THRESHOLD/Blueprints/ABP_EmotionSlot_Face.ABP_EmotionSlot_Face_C")));
	BodySlotAnimBP = TSoftClassPtr<UAnimInstance>(FSoftObjectPath(
		TEXT("/Game/THRESHOLD/Blueprints/ABP_EmotionSlot_Body.ABP_EmotionSlot_Body_C")));
}

void UTemplateAnimationDriverComponent::BuildDefaultEmotionMappings()
{
	// Plutchik → MetaHuman template collapse. Closest-match where no direct
	// template exists (Trust / Anticipation / Disgust / Neutral all fold to
	// existing templates).
	EmotionMapPrimary.Reset();
	EmotionMapPrimary.Add(EEmotionType::Neutral,      EMetahumanTemplateAnim::Idle);
	EmotionMapPrimary.Add(EEmotionType::Joy,          EMetahumanTemplateAnim::HappyA);
	EmotionMapPrimary.Add(EEmotionType::Sadness,      EMetahumanTemplateAnim::SadA);
	EmotionMapPrimary.Add(EEmotionType::Anger,        EMetahumanTemplateAnim::AngerA);
	EmotionMapPrimary.Add(EEmotionType::Fear,         EMetahumanTemplateAnim::FearA);
	EmotionMapPrimary.Add(EEmotionType::Surprise,     EMetahumanTemplateAnim::SupriseA);
	EmotionMapPrimary.Add(EEmotionType::Disgust,      EMetahumanTemplateAnim::AngerA); // wariness
	EmotionMapPrimary.Add(EEmotionType::Trust,        EMetahumanTemplateAnim::Idle);
	EmotionMapPrimary.Add(EEmotionType::Anticipation, EMetahumanTemplateAnim::Idle);

	EmotionMapVariantB.Reset();
	EmotionMapVariantB.Add(EEmotionType::Joy,       EMetahumanTemplateAnim::HappyB);
	EmotionMapVariantB.Add(EEmotionType::Sadness,   EMetahumanTemplateAnim::SadB);
	EmotionMapVariantB.Add(EEmotionType::Anger,     EMetahumanTemplateAnim::AngerB);
	EmotionMapVariantB.Add(EEmotionType::Fear,      EMetahumanTemplateAnim::FearB);
	EmotionMapVariantB.Add(EEmotionType::Surprise,  EMetahumanTemplateAnim::SupriseB);
}

void UTemplateAnimationDriverComponent::BuildDefaultClipMappings()
{
	// MetaHumanCharacter plugin ships template animation loops as standalone
	// UAnimSequence assets. Defaults point at female (_f_) variants — suitable
	// for Friend. Per-NPC overrides can swap to _m_ (male) by editing ClipMap
	// in the NPC Blueprint's component details.
	//
	// Path format: /MetaHumanCharacter/Optional/Animation/TemplateAnimations/
	//              Expression_Loops/<Emotion>/mhc_mh002_fmn_<b|f>_facialloop_<emo>_<f|m>_s001
	// The `fmn_b` prefix = body layer, `fmn_f` prefix = face layer.
	// The trailing `_f_` = female, `_m_` = male.
	auto MakePath = [](const TCHAR* Full) -> TSoftObjectPtr<UAnimSequence>
	{
		return TSoftObjectPtr<UAnimSequence>(FSoftObjectPath(Full));
	};

	// Use long form (/Package/Path.AssetName) — required for plugin
	// Optional/ content where the short form sometimes fails to resolve.
	// The macro takes the filename once and duplicates it as the asset name.
	#define EXP_LOOP(SubFolder, FileBody) \
		TEXT("/MetaHumanCharacter/Optional/Animation/TemplateAnimations/Expression_Loops/" SubFolder "/" FileBody "." FileBody)

	auto Pair = [&MakePath](const TCHAR* FaceP, const TCHAR* BodyP)
	{
		FMetahumanTemplateClipRef R;
		R.FaceClip = MakePath(FaceP);
		R.BodyClip = MakePath(BodyP);
		return R;
	};

	ClipMap.Reset();

	// Idle uses the Technical_Loops/Idle clips (different folder + filename
	// prefix from the Expression_Loops clips — authored from mh001 rather
	// than mh002 — but same archetype skeleton, so they play on Friend).
	{
		FMetahumanTemplateClipRef R;
		R.FaceClip = MakePath(
			TEXT("/MetaHumanCharacter/Optional/Animation/TemplateAnimations/Technical_Loops/Idle/mhc_mh001_fmn_f_idle.mhc_mh001_fmn_f_idle"));
		R.BodyClip = MakePath(
			TEXT("/MetaHumanCharacter/Optional/Animation/TemplateAnimations/Technical_Loops/Idle/mhc_mh001_fmn_b_idle.mhc_mh001_fmn_b_idle"));
		ClipMap.Add(EMetahumanTemplateAnim::Idle, R);
	}

	ClipMap.Add(EMetahumanTemplateAnim::AngerA, Pair(
		EXP_LOOP("AngerA", "mhc_mh002_fmn_f_facialloop_angry_f_s001"),
		EXP_LOOP("AngerA", "mhc_mh002_fmn_b_facialloop_angry_f_s001")));
	ClipMap.Add(EMetahumanTemplateAnim::AngerB, Pair(
		EXP_LOOP("AngerB", "mhc_mh002_fmn_f_facialloop_angry_m_s001"),
		EXP_LOOP("AngerB", "mhc_mh002_fmn_b_facialloop_angry_m_s001")));

	ClipMap.Add(EMetahumanTemplateAnim::FearA, Pair(
		EXP_LOOP("FearA", "mhc_mh002_fmn_f_facialloop_fear_f_s001"),
		EXP_LOOP("FearA", "mhc_mh002_fmn_b_facialloop_fear_f_s001")));
	ClipMap.Add(EMetahumanTemplateAnim::FearB, Pair(
		EXP_LOOP("FearB", "mhc_mh002_fmn_f_facialloop_fear_m_s001"),
		EXP_LOOP("FearB", "mhc_mh002_fmn_b_facialloop_fear_m_s001")));

	ClipMap.Add(EMetahumanTemplateAnim::HappyA, Pair(
		EXP_LOOP("HappyA", "mhc_mh002_fmn_f_facialloop_happy_f_s001"),
		EXP_LOOP("HappyA", "mhc_mh002_fmn_b_facialloop_happy_f_s001")));
	ClipMap.Add(EMetahumanTemplateAnim::HappyB, Pair(
		EXP_LOOP("HappyB", "ue_mh002_fmn_f_facialloop_happy_m_s001"),
		EXP_LOOP("HappyB", "mhc_mh002_fmn_b_facialloop_happy_m_s001")));

	ClipMap.Add(EMetahumanTemplateAnim::SadA, Pair(
		EXP_LOOP("SadA", "mhc_mh002_fmn_f_facialloop_sad_f_s001"),
		EXP_LOOP("SadA", "mhc_mh002_fmn_b_facialloop_sad_f_s001")));
	ClipMap.Add(EMetahumanTemplateAnim::SadB, Pair(
		EXP_LOOP("SadB", "mhc_mh002_fmn_f_facialloop_sad_m_s001"),
		EXP_LOOP("SadB", "mhc_mh002_fmn_b_facialloop_sad_m_s001")));

	// Surprise folder is "Surprise" (correct spelling) in the plugin; keep
	// our internal enum misspelled "Suprise" for consistency with the
	// MetaHuman Creator preview UI, but map to the correctly-named folder.
	ClipMap.Add(EMetahumanTemplateAnim::SupriseA, Pair(
		EXP_LOOP("SurpriseA", "mhc_mh002_fmn_f_facialloop_surprise_f_s001"),
		EXP_LOOP("SurpriseA", "mhc_mh002_fmn_b_facialloop_surprise_m_s001")));
	ClipMap.Add(EMetahumanTemplateAnim::SupriseB, Pair(
		EXP_LOOP("SurpriseB", "mhc_mh002_fmn_f_facialloop_surprise_m_s001"),
		EXP_LOOP("SurpriseB", "mhc_mh002_fmn_b_facialloop_surprise_m_s002")));

	#undef EXP_LOOP
}

void UTemplateAnimationDriverComponent::InitializeSubsystem()
{
	Super::InitializeSubsystem();

	AActor* Owner = GetOwner();
	if (!Owner)
	{
		return;
	}

	CachedEmotionComp = Owner->FindComponentByClass<UEmotionComponent>();
	CachedDialogueComp = Owner->FindComponentByClass<UDialogueComponent>();

	// Template animation signal source:
	//   bDriveFromDialogueResponse == true  → DialogueComponent's Claude-parsed
	//                                         emotion hint (bypasses state
	//                                         machine decay).
	//   bDriveFromDialogueResponse == false → EmotionComponent's state
	//                                         machine (old behaviour).
	// EmotionComponent is NOT unbound in either case — its state still drives
	// voice modulation, FACS curves, etc. We just don't use it for templates
	// when dialogue-driven.
	if (bDriveFromDialogueResponse && CachedDialogueComp)
	{
		CachedDialogueComp->OnDialogueResponseReceived.AddDynamic(this, &UTemplateAnimationDriverComponent::HandleDialogueResponse);
		UE_LOG(LogTemp, Log, TEXT("TemplateAnimDriver[%s]: routing templates from DialogueComponent (Claude-parsed emotion)."),
			*Owner->GetName());
	}
	else if (CachedEmotionComp)
	{
		CachedEmotionComp->OnEmotionChanged.AddDynamic(this, &UTemplateAnimationDriverComponent::HandleEmotionChanged);
		UE_LOG(LogTemp, Log, TEXT("TemplateAnimDriver[%s]: routing templates from EmotionComponent state machine."),
			*Owner->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TemplateAnimDriver: No DialogueComponent/EmotionComponent on '%s' — templates will not respond."),
			*Owner->GetName());
	}

	CachedFaceMesh = FindFaceMesh(Owner);
	CachedBodyMesh = FindBodyMesh(Owner);

	// Install the slot-host AnimBP on any mesh that has no primary
	// AnimInstance yet. This is what turns PlaySlotAnimationAsDynamicMontage
	// from a no-op into a real crossfade pipeline. Must run BEFORE the
	// starting-emotion ApplyTemplate call below.
	InstallSlotAnimBP(CachedFaceMesh, FaceSlotAnimBP, TEXT("Face"));
	InstallSlotAnimBP(CachedBodyMesh, BodySlotAnimBP, TEXT("Body"));

	const auto DescribeAnim = [](USkeletalMeshComponent* M) -> FString
	{
		if (!M) return TEXT("<none>");
		UAnimInstance* Primary = M->GetAnimInstance();
		UAnimInstance* Post    = M->GetPostProcessInstance();
		return FString::Printf(TEXT("primary=%s postProcess=%s"),
			Primary ? *Primary->GetClass()->GetName() : TEXT("<none>"),
			Post    ? *Post->GetClass()->GetName()    : TEXT("<none>"));
	};

	UE_LOG(LogTemp, Log, TEXT("TemplateAnimDriver[%s]: Face='%s' (%s) | Body='%s' (%s)"),
		*Owner->GetName(),
		CachedFaceMesh ? *CachedFaceMesh->GetName() : TEXT("<none>"),
		*DescribeAnim(CachedFaceMesh),
		CachedBodyMesh ? *CachedBodyMesh->GetName() : TEXT("<none>"),
		*DescribeAnim(CachedBodyMesh));

	// Apply the starting emotion so Friend doesn't linger in the assembled
	// default pose when her PAD starting state is non-Neutral.
	if (CachedEmotionComp)
	{
		const FEmotionState S = CachedEmotionComp->GetCurrentEmotionState();
		LastHandledEmotion = S.PrimaryEmotion;
		const EMetahumanTemplateAnim Picked = PickVariantForEmotion(S.PrimaryEmotion);
		CurrentLockedTemplate = Picked;
		ApplyTemplate(Picked);
	}
}

void UTemplateAnimationDriverComponent::InstallSlotAnimBP(USkeletalMeshComponent* Mesh, TSoftClassPtr<UAnimInstance>& SlotClassPtr, const TCHAR* Tag)
{
	if (!Mesh) return;
	if (Mesh->GetAnimInstance())
	{
		// Already has a primary AnimInstance; don't override. Montages will
		// play on whatever AnimBP is there (if it has a matching Slot node).
		return;
	}
	UClass* SlotClass = SlotClassPtr.LoadSynchronous();
	if (!SlotClass)
	{
		UE_LOG(LogTemp, Verbose,
			TEXT("TemplateAnimDriver[%s]: no %s slot AnimBP configured (path='%s'); montages will fall back to PlayAnimation hard-swap."),
			GetOwner() ? *GetOwner()->GetName() : TEXT("?"), Tag, *SlotClassPtr.ToString());
		return;
	}
	Mesh->SetAnimInstanceClass(SlotClass);
	UE_LOG(LogTemp, Log,
		TEXT("TemplateAnimDriver[%s]: Installed %s slot AnimBP '%s'"),
		GetOwner() ? *GetOwner()->GetName() : TEXT("?"), Tag, *SlotClass->GetName());
}

void UTemplateAnimationDriverComponent::ShutdownSubsystem()
{
	if (CachedEmotionComp)
	{
		CachedEmotionComp->OnEmotionChanged.RemoveDynamic(this, &UTemplateAnimationDriverComponent::HandleEmotionChanged);
	}
	if (CachedDialogueComp)
	{
		CachedDialogueComp->OnDialogueResponseReceived.RemoveDynamic(this, &UTemplateAnimationDriverComponent::HandleDialogueResponse);
	}
	StopAllEmotionMontages();
	Super::ShutdownSubsystem();
}

void UTemplateAnimationDriverComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Nothing to do each tick — montage system handles the blend.
}

void UTemplateAnimationDriverComponent::HandleEmotionChanged(FEmotionState OldState, FEmotionState NewState)
{
	if (NewState.PrimaryEmotion == LastHandledEmotion)
	{
		// Same emotion — keep the locked variant. Intensity changes do not
		// re-roll the template; variants are locked for the duration of the
		// emotional state.
		return;
	}

	LastHandledEmotion = NewState.PrimaryEmotion;
	const EMetahumanTemplateAnim Picked = PickVariantForEmotion(NewState.PrimaryEmotion);
	// Apply immediately — montage blend-in/blend-out handles the smooth
	// transition (old clip blends out while new clip blends in, both over
	// SettleDelaySeconds).
	ApplyTemplate(Picked);
	CurrentLockedTemplate = Picked;
}

void UTemplateAnimationDriverComponent::HandleDialogueResponse(const FString& /*ResponseText*/,
	EEmotionType NPCEmotionHint, bool /*bShouldGiveItem*/, FName /*ItemID*/)
{
	// Route Claude's directly-parsed emotion to template selection. Decoupled
	// from EmotionComponent so slow decay (300s half-life with our default
	// NeutralThreshold) can't hold Sadness on the face after Claude has
	// already moved on to Neutral. Reuses the same dedup / pick-variant /
	// crossfade pipeline as the state-machine path.
	if (NPCEmotionHint == LastHandledEmotion)
	{
		return;
	}

	LastHandledEmotion = NPCEmotionHint;
	const EMetahumanTemplateAnim Picked = PickVariantForEmotion(NPCEmotionHint);
	UE_LOG(LogTemp, Log, TEXT("TemplateAnimDriver[%s]: dialogue-emotion=%s → template=%d"),
		GetOwner() ? *GetOwner()->GetName() : TEXT("?"),
		*UEnum::GetValueAsString(NPCEmotionHint), (int32)Picked);
	ApplyTemplate(Picked);
	CurrentLockedTemplate = Picked;
}

EMetahumanTemplateAnim UTemplateAnimationDriverComponent::PickVariantForEmotion(EEmotionType Emotion) const
{
	const EMetahumanTemplateAnim* PrimaryPtr = EmotionMapPrimary.Find(Emotion);
	const EMetahumanTemplateAnim  Primary    = PrimaryPtr ? *PrimaryPtr : EMetahumanTemplateAnim::Idle;

	const EMetahumanTemplateAnim* VariantBPtr = EmotionMapVariantB.Find(Emotion);
	if (!VariantBPtr)
	{
		return Primary;
	}
	return FMath::RandBool() ? Primary : *VariantBPtr;
}

void UTemplateAnimationDriverComponent::ForceRepickVariant()
{
	if (!CachedEmotionComp)
	{
		return;
	}
	const FEmotionState S = CachedEmotionComp->GetCurrentEmotionState();
	const EMetahumanTemplateAnim Picked = PickVariantForEmotion(S.PrimaryEmotion);
	ApplyTemplate(Picked);
	CurrentLockedTemplate = Picked;
}

void UTemplateAnimationDriverComponent::ApplyTemplate(EMetahumanTemplateAnim Template)
{
	const FMetahumanTemplateClipRef* ClipRef = ClipMap.Find(Template);
	if (!ClipRef)
	{
		UE_LOG(LogTemp, Verbose, TEXT("TemplateAnimDriver[%s]: no ClipMap entry for template=%d — skipping."),
			GetOwner() ? *GetOwner()->GetName() : TEXT("?"), (int32)Template);
		return;
	}

	UAnimSequence* FaceClip = ClipRef->FaceClip.LoadSynchronous();
	UAnimSequence* BodyClip = ClipRef->BodyClip.LoadSynchronous();

	const FString OwnerName = GetOwner() ? GetOwner()->GetName() : TEXT("?");
	if (!FaceClip)
	{
		// Diagnostic: the asset IS visible in Content Browser, so the mount
		// works. LoadSynchronous failure may be due to soft-pointer path
		// storage quirks. Retry via StaticLoadObject with explicit long form
		// to confirm the asset is reachable at all.
		const FString LongPath = ClipRef->FaceClip.ToString() +
			TEXT(".") + FPaths::GetBaseFilename(ClipRef->FaceClip.ToString());
		UAnimSequence* Retry = Cast<UAnimSequence>(StaticLoadObject(
			UAnimSequence::StaticClass(), nullptr, *LongPath));
		UE_LOG(LogTemp, Error,
			TEXT("TemplateAnimDriver[%s]: FaceClip did not load — softPath='%s'  longRetry(path='%s')=%s"),
			*OwnerName, *ClipRef->FaceClip.ToString(), *LongPath,
			Retry ? TEXT("OK!") : TEXT("FAIL"));
		if (Retry)
		{
			FaceClip = Retry;
		}
	}
	if (!BodyClip)
	{
		const FString LongPath = ClipRef->BodyClip.ToString() +
			TEXT(".") + FPaths::GetBaseFilename(ClipRef->BodyClip.ToString());
		UAnimSequence* Retry = Cast<UAnimSequence>(StaticLoadObject(
			UAnimSequence::StaticClass(), nullptr, *LongPath));
		UE_LOG(LogTemp, Error,
			TEXT("TemplateAnimDriver[%s]: BodyClip did not load — softPath='%s'  longRetry(path='%s')=%s"),
			*OwnerName, *ClipRef->BodyClip.ToString(), *LongPath,
			Retry ? TEXT("OK!") : TEXT("FAIL"));
		if (Retry)
		{
			BodyClip = Retry;
		}
	}

	const float Blend = FMath::Max(0.0f, SettleDelaySeconds);

	auto PlayOn = [&](USkeletalMeshComponent* Mesh, UAnimSequence* Clip, const TCHAR* Tag) -> bool
	{
		if (!Mesh || !Clip)
		{
			return false;
		}
		// Preferred path: a slot-host AnimBP is installed on this mesh, so
		// PlaySlotAnimationAsDynamicMontage produces a real A→B crossfade.
		// If the new montage is played while an old one is active on the
		// same slot, Unreal blends them automatically via the new montage's
		// blend-in time.
		if (UAnimInstance* AI = Mesh->GetAnimInstance())
		{
			constexpr int32 LongLoop = 9999;
			UAnimMontage* Montage = AI->PlaySlotAnimationAsDynamicMontage(
				Clip,
				MontageSlotName,
				Blend,     // blend-in  — this IS the crossfade duration
				Blend,     // blend-out — used when replaced by next emotion
				1.0f,      // play rate
				LongLoop,  // loop count (UE5 clamps 0→1, so use large value)
				-1.0f,     // blend-out trigger time (-1 = at end)
				0.0f);     // time to start montage at
			return Montage != nullptr;
		}
		// Fallback: no primary AnimInstance and no slot AnimBP was installed
		// (slot config was null for this NPC, or SetAnimInstanceClass failed).
		// Hard-swap via PlayAnimation — no blend, but at least something plays.
		Mesh->PlayAnimation(Clip, /*bLooping=*/true);
		return true;
	};

	const bool bFaceOK = PlayOn(CachedFaceMesh, FaceClip, TEXT("Face"));
	const bool bBodyOK = PlayOn(CachedBodyMesh, BodyClip, TEXT("Body"));

	UE_LOG(LogTemp, Log,
		TEXT("TemplateAnimDriver[%s]: Applied template=%d via montage; face=%s body=%s (slot=%s blend=%.2fs)"),
		GetOwner() ? *GetOwner()->GetName() : TEXT("?"),
		(int32)Template,
		bFaceOK ? TEXT("ok") : TEXT("skip/FAIL"),
		bBodyOK ? TEXT("ok") : TEXT("skip/FAIL"),
		*MontageSlotName.ToString(), Blend);
}

void UTemplateAnimationDriverComponent::StopAllEmotionMontages()
{
	// Shutdown cleanup: stop single-node playback on both meshes. The post-
	// process AnimBPs continue running harmlessly after.
	if (CachedFaceMesh)
	{
		CachedFaceMesh->Stop();
	}
	if (CachedBodyMesh)
	{
		CachedBodyMesh->Stop();
	}
}

USkeletalMeshComponent* UTemplateAnimationDriverComponent::FindFaceMesh(AActor* Actor) const
{
	if (!Actor) return nullptr;

	auto Search = [](AActor* A) -> USkeletalMeshComponent*
	{
		TArray<USkeletalMeshComponent*> Meshes;
		A->GetComponents<USkeletalMeshComponent>(Meshes);
		for (USkeletalMeshComponent* M : Meshes)
		{
			if (M && M->GetName().Contains(TEXT("Face")))
			{
				return M;
			}
		}
		return nullptr;
	};

	if (USkeletalMeshComponent* Found = Search(Actor)) return Found;

	TArray<UChildActorComponent*> ChildActors;
	Actor->GetComponents<UChildActorComponent>(ChildActors);
	for (UChildActorComponent* CAC : ChildActors)
	{
		if (!CAC || !CAC->GetChildActor()) continue;
		if (USkeletalMeshComponent* Found = Search(CAC->GetChildActor())) return Found;

		TArray<UChildActorComponent*> Nested;
		CAC->GetChildActor()->GetComponents<UChildActorComponent>(Nested);
		for (UChildActorComponent* N : Nested)
		{
			if (N && N->GetChildActor())
			{
				if (USkeletalMeshComponent* Found = Search(N->GetChildActor())) return Found;
			}
		}
	}
	return nullptr;
}

USkeletalMeshComponent* UTemplateAnimationDriverComponent::FindBodyMesh(AActor* Actor) const
{
	if (!Actor) return nullptr;

	auto Search = [](AActor* A) -> USkeletalMeshComponent*
	{
		TArray<USkeletalMeshComponent*> Meshes;
		A->GetComponents<USkeletalMeshComponent>(Meshes);
		for (USkeletalMeshComponent* M : Meshes)
		{
			if (!M) continue;
			const FString Name = M->GetName();
			// Body mesh is the one that is NOT the Face / Hair / Eyebrows / Eyes
			// etc. Heuristic: skip meshes with a known face-related token.
			if (Name.Contains(TEXT("Face")) || Name.Contains(TEXT("Eyebrow")) ||
				Name.Contains(TEXT("Eyelash")) || Name.Contains(TEXT("Hair")) ||
				Name.Contains(TEXT("Teeth")) || Name.Contains(TEXT("Eye")))
			{
				continue;
			}
			// Skip ACharacter's inherited default CharacterMesh0 when it has
			// no mesh asset assigned. On MetaHuman-child-actor NPCs the real
			// body lives inside the child actor; CharacterMesh0 is an empty
			// stub we don't want to pick.
			if (!M->GetSkeletalMeshAsset())
			{
				continue;
			}
			return M;
		}
		return nullptr;
	};

	if (USkeletalMeshComponent* Found = Search(Actor)) return Found;

	TArray<UChildActorComponent*> ChildActors;
	Actor->GetComponents<UChildActorComponent>(ChildActors);
	for (UChildActorComponent* CAC : ChildActors)
	{
		if (!CAC || !CAC->GetChildActor()) continue;
		if (USkeletalMeshComponent* Found = Search(CAC->GetChildActor())) return Found;

		TArray<UChildActorComponent*> Nested;
		CAC->GetChildActor()->GetComponents<UChildActorComponent>(Nested);
		for (UChildActorComponent* N : Nested)
		{
			if (N && N->GetChildActor())
			{
				if (USkeletalMeshComponent* Found = Search(N->GetChildActor())) return Found;
			}
		}
	}
	return nullptr;
}
