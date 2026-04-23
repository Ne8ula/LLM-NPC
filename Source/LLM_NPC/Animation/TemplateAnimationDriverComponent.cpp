#include "TemplateAnimationDriverComponent.h"
#include "LLM_NPC/Emotion/EmotionComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ChildActorComponent.h"
#include "Animation/AnimInstance.h"
#include "UObject/EnumProperty.h"
#include "UObject/UnrealType.h"

UTemplateAnimationDriverComponent::UTemplateAnimationDriverComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PrePhysics;
	SubsystemName = TEXT("TemplateAnimationDriver");

	BuildDefaultEmotionMappings();
}

void UTemplateAnimationDriverComponent::BuildDefaultEmotionMappings()
{
	// Plutchik → MetaHuman template collapse. Closest-match where no direct
	// template exists (Trust / Anticipation / Disgust / Neutral all fold to
	// existing templates). User approved this collapse in the design review.
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

void UTemplateAnimationDriverComponent::InitializeSubsystem()
{
	Super::InitializeSubsystem();

	AActor* Owner = GetOwner();
	if (!Owner)
	{
		return;
	}

	CachedEmotionComp = Owner->FindComponentByClass<UEmotionComponent>();
	if (CachedEmotionComp)
	{
		CachedEmotionComp->OnEmotionChanged.AddDynamic(this, &UTemplateAnimationDriverComponent::HandleEmotionChanged);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TemplateAnimDriver: No EmotionComponent on '%s' — templates will not respond to emotion changes."),
			*Owner->GetName());
	}

	CachedFaceMesh = FindFaceMesh(Owner);
	CachedBodyMesh = FindBodyMesh(Owner);

	if (CachedFaceMesh)
	{
		CachedFaceAnimInstance = CachedFaceMesh->GetAnimInstance();
	}
	if (CachedBodyMesh)
	{
		CachedBodyAnimInstance = CachedBodyMesh->GetAnimInstance();
	}

	UE_LOG(LogTemp, Log, TEXT("TemplateAnimDriver: Face='%s' (Anim=%s) | Body='%s' (Anim=%s)"),
		CachedFaceMesh ? *CachedFaceMesh->GetName() : TEXT("<none>"),
		CachedFaceAnimInstance ? *CachedFaceAnimInstance->GetClass()->GetName() : TEXT("<none>"),
		CachedBodyMesh ? *CachedBodyMesh->GetName() : TEXT("<none>"),
		CachedBodyAnimInstance ? *CachedBodyAnimInstance->GetClass()->GetName() : TEXT("<none>"));

	// Dump candidate enum/byte property names on both anim instances so the
	// user can discover the actual MetaHuman template property names in one
	// PIE run rather than hunting in the BP editor.
	auto DumpEnumProps = [](UAnimInstance* AI, const TCHAR* Tag)
	{
		if (!AI) return;
		UE_LOG(LogTemp, Log, TEXT("TemplateAnimDriver.%s: enum/byte properties on %s:"),
			Tag, *AI->GetClass()->GetName());
		for (TFieldIterator<FProperty> It(AI->GetClass()); It; ++It)
		{
			FProperty* P = *It;
			if (P->IsA<FEnumProperty>() || P->IsA<FByteProperty>())
			{
				UE_LOG(LogTemp, Log, TEXT("  - %s : %s"), *P->GetName(), *P->GetCPPType());
			}
		}
	};
	DumpEnumProps(CachedFaceAnimInstance, TEXT("Face"));
	DumpEnumProps(CachedBodyAnimInstance, TEXT("Body"));

	// Apply the starting emotion immediately so the NPC doesn't linger in
	// whatever the BP default was.
	if (CachedEmotionComp)
	{
		const FEmotionState S = CachedEmotionComp->GetCurrentEmotionState();
		LastHandledEmotion = S.PrimaryEmotion;
		const EMetahumanTemplateAnim Picked = PickVariantForEmotion(S.PrimaryEmotion);
		CurrentLockedTemplate = Picked;
		ApplyTemplate(Picked);
	}
}

void UTemplateAnimationDriverComponent::ShutdownSubsystem()
{
	if (CachedEmotionComp)
	{
		CachedEmotionComp->OnEmotionChanged.RemoveDynamic(this, &UTemplateAnimationDriverComponent::HandleEmotionChanged);
	}
	Super::ShutdownSubsystem();
}

void UTemplateAnimationDriverComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bHasPendingTemplate)
	{
		return;
	}

	const UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	if (World->GetTimeSeconds() >= PendingApplyTime)
	{
		ApplyTemplate(PendingTemplate);
		CurrentLockedTemplate = PendingTemplate;
		bHasPendingTemplate = false;
	}
}

void UTemplateAnimationDriverComponent::HandleEmotionChanged(FEmotionState OldState, FEmotionState NewState)
{
	if (NewState.PrimaryEmotion == LastHandledEmotion)
	{
		// Same emotion — keep the locked variant. Intensity changes do not
		// re-roll the template; the user wanted variants locked for the
		// duration of the emotional state.
		return;
	}

	LastHandledEmotion = NewState.PrimaryEmotion;
	const EMetahumanTemplateAnim Picked = PickVariantForEmotion(NewState.PrimaryEmotion);

	if (SettleDelaySeconds <= KINDA_SMALL_NUMBER)
	{
		ApplyTemplate(Picked);
		CurrentLockedTemplate = Picked;
		return;
	}

	// Defer the swap: gives the outgoing pose a beat to relax visually
	// before the new template stamps in. If the next emotion arrives during
	// the pending window we overwrite — always apply the most recent intent.
	PendingTemplate = Picked;
	bHasPendingTemplate = true;
	if (const UWorld* World = GetWorld())
	{
		PendingApplyTime = World->GetTimeSeconds() + SettleDelaySeconds;
	}
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
	const uint8 Value = static_cast<uint8>(Template);
	const bool bFaceOK = WriteTemplateEnumProperty(CachedFaceAnimInstance, FaceTemplateAnimProperty, Value);
	const bool bBodyOK = WriteTemplateEnumProperty(CachedBodyAnimInstance, BodyTemplateAnimProperty, Value);

	UE_LOG(LogTemp, Log, TEXT("TemplateAnimDriver: Applied template=%d face=%s body=%s"),
		(int32)Value, bFaceOK ? TEXT("ok") : TEXT("FAIL"), bBodyOK ? TEXT("ok") : TEXT("FAIL"));
}

bool UTemplateAnimationDriverComponent::WriteTemplateEnumProperty(UAnimInstance* AnimInstance, FName PropertyName, uint8 EnumValue) const
{
	if (!AnimInstance)
	{
		return false;
	}

	FProperty* Prop = AnimInstance->GetClass()->FindPropertyByName(PropertyName);
	if (!Prop)
	{
		// Try the name with underscores-in-place-of-spaces as a fallback
		// (FName lookup is exact; the BP variable display "Face Template
		// Animation" may be serialized as "Face_Template_Animation").
		FString Alt = PropertyName.ToString().Replace(TEXT(" "), TEXT("_"));
		Prop = AnimInstance->GetClass()->FindPropertyByName(FName(*Alt));
	}
	if (!Prop)
	{
		return false;
	}

	if (FEnumProperty* EnumProp = CastField<FEnumProperty>(Prop))
	{
		FNumericProperty* Underlying = EnumProp->GetUnderlyingProperty();
		void* PropAddr = EnumProp->ContainerPtrToValuePtr<void>(AnimInstance);
		Underlying->SetIntPropertyValue(PropAddr, (int64)EnumValue);
		return true;
	}
	if (FByteProperty* ByteProp = CastField<FByteProperty>(Prop))
	{
		ByteProp->SetPropertyValue_InContainer(AnimInstance, EnumValue);
		return true;
	}
	return false;
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
