#include "MetahumanAnimComponent.h"
#include "LLM_NPC/Emotion/EmotionComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ChildActorComponent.h"
#include "Animation/AnimInstance.h"

UMetahumanAnimComponent::UMetahumanAnimComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	// Tick AFTER animation so our morph targets aren't overwritten by the AnimBP
	PrimaryComponentTick.TickGroup = TG_PostUpdateWork;
	SubsystemName = TEXT("MetahumanAnimation");
}

void UMetahumanAnimComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMetahumanAnimComponent::InitializeSubsystem()
{
	Super::InitializeSubsystem();

	// Load the blend shape mapping data asset
	if (!BlendShapeMappingAssetRef.IsNull())
	{
		LoadedMappingData = BlendShapeMappingAssetRef.LoadSynchronous();
		if (LoadedMappingData)
		{
			UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: Loaded BlendShapeMappingDataAsset with %d mappings"),
				LoadedMappingData->Mappings.Num());
		}
	}

	// If no data asset, create default mappings in memory
	if (!LoadedMappingData)
	{
		UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: No BlendShapeMappingDataAsset assigned, creating defaults"));
		LoadedMappingData = NewObject<UBlendShapeMappingDataAsset>(this);
		PopulateDefaultMappings();
	}

	// Cache the EmotionComponent
	if (AActor* Owner = GetOwner())
	{
		CachedEmotionComp = Owner->FindComponentByClass<UEmotionComponent>();

		// Find the Face skeletal mesh — search owner first, then Child Actors (for Metahuman setup)
		CachedSkeletalMesh = FindFaceMesh(Owner);

		if (CachedSkeletalMesh)
		{
			UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: Found Face mesh '%s' with %d morph targets"),
				*CachedSkeletalMesh->GetName(),
				CachedSkeletalMesh->GetSkeletalMeshAsset() ?
					CachedSkeletalMesh->GetSkeletalMeshAsset()->GetMorphTargets().Num() : 0);

			// Completely disable the Face mesh's animation system.
			// Metahuman uses RigLogic which recalculates ALL morph targets every frame.
			// We must remove the AnimBP entirely to take control.
			CachedSkeletalMesh->SetAnimInstanceClass(nullptr);
			CachedSkeletalMesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);
			CachedSkeletalMesh->Stop();

			UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: Cleared AnimBP on Face mesh for code-driven morph targets"));

			// Set a neutral baseline — reset all morph targets to 0
			if (USkeletalMesh* SkelMesh = CachedSkeletalMesh->GetSkeletalMeshAsset())
			{
				for (const UMorphTarget* MT : SkelMesh->GetMorphTargets())
				{
					if (MT)
					{
						CachedSkeletalMesh->SetMorphTarget(MT->GetFName(), 0.0f);
					}
				}
			}

			// Add idle blinking on a timer
			bShouldBlink = true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("MetahumanAnim: No Face skeletal mesh found"));
		}
	}
}

USkeletalMeshComponent* UMetahumanAnimComponent::FindFaceMesh(AActor* Actor) const
{
	if (!Actor) return nullptr;

	auto SearchForFace = [](AActor* SearchActor) -> USkeletalMeshComponent*
	{
		TArray<USkeletalMeshComponent*> SkeletalMeshes;
		SearchActor->GetComponents<USkeletalMeshComponent>(SkeletalMeshes);
		for (USkeletalMeshComponent* SMC : SkeletalMeshes)
		{
			if (SMC && SMC->GetName().Contains(TEXT("Face")))
			{
				return SMC;
			}
		}
		return nullptr;
	};

	// Search the actor directly
	if (USkeletalMeshComponent* Found = SearchForFace(Actor))
	{
		return Found;
	}

	// Search Child Actors (Metahuman spawned as Child Actor)
	TArray<UChildActorComponent*> ChildActors;
	Actor->GetComponents<UChildActorComponent>(ChildActors);
	for (UChildActorComponent* CAC : ChildActors)
	{
		if (!CAC || !CAC->GetChildActor()) continue;

		if (USkeletalMeshComponent* Found = SearchForFace(CAC->GetChildActor()))
		{
			UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: Found Face mesh in Child Actor: %s"), *Found->GetName());
			return Found;
		}

		// Search nested child actors
		TArray<UChildActorComponent*> NestedChildren;
		CAC->GetChildActor()->GetComponents<UChildActorComponent>(NestedChildren);
		for (UChildActorComponent* Nested : NestedChildren)
		{
			if (Nested && Nested->GetChildActor())
			{
				if (USkeletalMeshComponent* Found = SearchForFace(Nested->GetChildActor()))
				{
					return Found;
				}
			}
		}
	}

	return nullptr;
}

void UMetahumanAnimComponent::PopulateDefaultMappings()
{
	if (!LoadedMappingData) return;

	LoadedMappingData->Mappings.Empty();

	// Helper to add a mapping
	auto AddMapping = [this](EEmotionType Emotion, TArray<TPair<FString, float>> Targets)
	{
		FEmotionBlendShapeMapping Mapping;
		Mapping.EmotionType = Emotion;
		Mapping.MinIntensity = 0.0f;
		Mapping.MaxIntensity = 1.0f;

		for (const auto& T : Targets)
		{
			FEmotionBlendShapeTarget Target;
			Target.BlendShapeName = FName(*T.Key);
			Target.TargetValue = T.Value;
			Mapping.BlendShapeTargets.Add(Target);
		}

		LoadedMappingData->Mappings.Add(Mapping);
	};

	// Joy — smile, cheek raise, slight squint
	AddMapping(EEmotionType::Joy, {
		{TEXT("head_lod0_mesh__mouth_cornerPull_left"), 0.8f},
		{TEXT("head_lod0_mesh__mouth_cornerPull_right"), 0.8f},
		{TEXT("head_lod0_mesh__eye_cheekRaise_L"), 0.5f},
		{TEXT("head_lod0_mesh__eye_cheekRaise_R"), 0.5f},
		{TEXT("head_lod0_mesh__eye_squintInner_L"), 0.3f},
		{TEXT("head_lod0_mesh__eye_squintInner_R"), 0.3f},
	});

	// Sadness — frown, inner brow raise, mouth corners down
	AddMapping(EEmotionType::Sadness, {
		{TEXT("head_lod0_mesh__mouth_cornerDepress_L"), 0.6f},
		{TEXT("head_lod0_mesh__mouth_cornerDepress_R"), 0.6f},
		{TEXT("head_lod0_mesh__mouth_stretch_left"), 0.3f},
		{TEXT("head_lod0_mesh__mouth_stretch_right"), 0.3f},
		{TEXT("head_lod0_mesh__eye_squintInner_L"), 0.4f},
		{TEXT("head_lod0_mesh__eye_squintInner_R"), 0.4f},
	});

	// Anger — brow lower, nose wrinkle, jaw clench, lips tight
	AddMapping(EEmotionType::Anger, {
		{TEXT("head_lod0_mesh__nose_wrinkle_left"), 0.7f},
		{TEXT("head_lod0_mesh__nose_wrinkle_right"), 0.7f},
		{TEXT("head_lod0_mesh__jaw_clench_L"), 0.5f},
		{TEXT("head_lod0_mesh__jaw_clench_R"), 0.5f},
		{TEXT("head_lod0_mesh__mouth_press_UL"), 0.4f},
		{TEXT("head_lod0_mesh__mouth_press_UR"), 0.4f},
		{TEXT("head_lod0_mesh__mouth_cornerDepress_L"), 0.3f},
		{TEXT("head_lod0_mesh__mouth_cornerDepress_R"), 0.3f},
	});

	// Fear — eyes wide, brows up, mouth slightly open
	AddMapping(EEmotionType::Fear, {
		{TEXT("head_lod0_mesh__eye_widen_L"), 0.7f},
		{TEXT("head_lod0_mesh__eye_widen_R"), 0.7f},
		{TEXT("head_lod0_mesh__jaw_open"), 0.3f},
		{TEXT("head_lod0_mesh__mouth_stretch_left"), 0.4f},
		{TEXT("head_lod0_mesh__mouth_stretch_right"), 0.4f},
	});

	// Surprise — eyes wide, jaw open, brows up
	AddMapping(EEmotionType::Surprise, {
		{TEXT("head_lod0_mesh__eye_widen_L"), 0.9f},
		{TEXT("head_lod0_mesh__eye_widen_R"), 0.9f},
		{TEXT("head_lod0_mesh__jaw_open"), 0.5f},
		{TEXT("head_lod0_mesh__mouth_upperLipRaise_left"), 0.3f},
		{TEXT("head_lod0_mesh__mouth_upperLipRaise_right"), 0.3f},
	});

	// Disgust — nose wrinkle, upper lip raise, squint
	AddMapping(EEmotionType::Disgust, {
		{TEXT("head_lod0_mesh__nose_wrinkle_left"), 0.8f},
		{TEXT("head_lod0_mesh__nose_wrinkle_right"), 0.8f},
		{TEXT("head_lod0_mesh__mouth_upperLipRaise_left"), 0.6f},
		{TEXT("head_lod0_mesh__mouth_upperLipRaise_right"), 0.6f},
		{TEXT("head_lod0_mesh__eye_squintInner_L"), 0.5f},
		{TEXT("head_lod0_mesh__eye_squintInner_R"), 0.5f},
	});

	// Trust — gentle smile, soft eyes
	AddMapping(EEmotionType::Trust, {
		{TEXT("head_lod0_mesh__mouth_cornerPull_left"), 0.4f},
		{TEXT("head_lod0_mesh__mouth_cornerPull_right"), 0.4f},
		{TEXT("head_lod0_mesh__eye_cheekRaise_L"), 0.3f},
		{TEXT("head_lod0_mesh__eye_cheekRaise_R"), 0.3f},
	});

	// Anticipation — slight smile, eyes widened
	AddMapping(EEmotionType::Anticipation, {
		{TEXT("head_lod0_mesh__mouth_cornerPull_left"), 0.3f},
		{TEXT("head_lod0_mesh__mouth_cornerPull_right"), 0.3f},
		{TEXT("head_lod0_mesh__eye_widen_L"), 0.4f},
		{TEXT("head_lod0_mesh__eye_widen_R"), 0.4f},
	});

	UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: Created %d default emotion mappings"), LoadedMappingData->Mappings.Num());
}

void UMetahumanAnimComponent::ShutdownSubsystem()
{
	if (CachedSkeletalMesh)
	{
		for (const auto& Pair : CurrentBlendShapeValues)
		{
			CachedSkeletalMesh->SetMorphTarget(Pair.Key, 0.0f);
		}
	}

	CurrentBlendShapeValues.Empty();
	TargetBlendShapeValues.Empty();

	Super::ShutdownSubsystem();
}

void UMetahumanAnimComponent::SetLipSyncJawOpen(float Value)
{
	LipSyncJawOpenValue = FMath::Clamp(Value, 0.0f, 1.0f);
}

void UMetahumanAnimComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsInitialized || !LoadedMappingData || !CachedSkeletalMesh)
	{
		return;
	}

	// Read the current emotion state from EmotionComponent
	FEmotionState CurrentState;
	if (CachedEmotionComp)
	{
		CurrentState = CachedEmotionComp->GetCurrentEmotionState();
	}

	// Look up blend shape targets for the current emotion state
	TArray<FEmotionBlendShapeTarget> Targets = LoadedMappingData->GetTargetsForState(CurrentState);

	// Build target map — reset all existing targets to zero first
	TMap<FName, float> NewTargets;
	for (const auto& Pair : CurrentBlendShapeValues)
	{
		NewTargets.Add(Pair.Key, 0.0f);
	}
	for (const FEmotionBlendShapeTarget& Target : Targets)
	{
		NewTargets.Add(Target.BlendShapeName, Target.TargetValue);
	}

	// Add lip sync jaw open — blends with emotion jaw value
	static const FName JawOpenName(TEXT("head_lod0_mesh__jaw_open"));
	if (LipSyncJawOpenValue > 0.01f)
	{
		float& JawTarget = NewTargets.FindOrAdd(JawOpenName);
		JawTarget = FMath::Max(JawTarget, LipSyncJawOpenValue);
	}

	// Idle blinking
	if (bShouldBlink)
	{
		BlinkTimer -= DeltaTime;
		if (BlinkTimer <= 0.0f)
		{
			BlinkTimer = FMath::RandRange(2.5f, 6.0f);
			BlinkPhase = 0.0f;
			bIsBlinking = true;
		}

		float BlinkValue = 0.0f;
		if (bIsBlinking)
		{
			BlinkPhase += DeltaTime;
			// Quick close (0-0.08s), hold (0.08-0.15s), open (0.15-0.3s)
			if (BlinkPhase < 0.08f)
				BlinkValue = BlinkPhase / 0.08f;
			else if (BlinkPhase < 0.15f)
				BlinkValue = 1.0f;
			else if (BlinkPhase < 0.3f)
				BlinkValue = 1.0f - (BlinkPhase - 0.15f) / 0.15f;
			else
			{
				BlinkValue = 0.0f;
				bIsBlinking = false;
			}
		}

		if (BlinkValue > 0.01f)
		{
			static const FName BlinkL(TEXT("head_lod0_mesh__EcheekRaise_Eblink_L"));
			static const FName BlinkR(TEXT("head_lod0_mesh__EcheekRaise_Eblink_R"));
			NewTargets.FindOrAdd(BlinkL) = FMath::Max(NewTargets.FindOrAdd(BlinkL), BlinkValue);
			NewTargets.FindOrAdd(BlinkR) = FMath::Max(NewTargets.FindOrAdd(BlinkR), BlinkValue);
		}
	}

	TargetBlendShapeValues = NewTargets;

	UpdateBlendShapes(DeltaTime);
}

void UMetahumanAnimComponent::UpdateBlendShapes(float DeltaTime)
{
	if (!CachedSkeletalMesh)
	{
		return;
	}

	for (const auto& Pair : TargetBlendShapeValues)
	{
		const FName& MorphName = Pair.Key;
		const float TargetValue = Pair.Value;

		float& CurrentValue = CurrentBlendShapeValues.FindOrAdd(MorphName, 0.0f);

		// Smoothly interpolate toward target
		float InterpSpeed = (MorphName.ToString().Contains(TEXT("jaw_open"))) ?
			LipSyncInterpolationSpeed : InterpolationSpeed;
		CurrentValue = FMath::FInterpTo(CurrentValue, TargetValue, DeltaTime, InterpSpeed);

		// Apply morph target
		CachedSkeletalMesh->SetMorphTarget(MorphName, CurrentValue);

		// Debug: log once when we start applying non-zero values
		static bool bLoggedOnce = false;
		if (!bLoggedOnce && CurrentValue > 0.05f)
		{
			UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: First morph target applied: '%s' = %.2f"), *MorphName.ToString(), CurrentValue);
			bLoggedOnce = true;
		}
	}

	// Force render update
	CachedSkeletalMesh->MarkRenderDynamicDataDirty();

	// Remove blend shapes that have reached zero
	TArray<FName> ToRemove;
	for (auto& Pair : CurrentBlendShapeValues)
	{
		if (!TargetBlendShapeValues.Contains(Pair.Key) && FMath::IsNearlyZero(Pair.Value, 0.001f))
		{
			ToRemove.Add(Pair.Key);
		}
	}
	for (const FName& Name : ToRemove)
	{
		CurrentBlendShapeValues.Remove(Name);
	}
}
