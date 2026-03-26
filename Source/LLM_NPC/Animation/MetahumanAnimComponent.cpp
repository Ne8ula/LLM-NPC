#include "MetahumanAnimComponent.h"
#include "LLM_NPC/Emotion/EmotionComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ChildActorComponent.h"

UMetahumanAnimComponent::UMetahumanAnimComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
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
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("MetahumanAnim: Failed to load BlendShapeMappingDataAsset"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MetahumanAnim: No BlendShapeMappingDataAsset assigned"));
	}

	// Cache the EmotionComponent
	if (AActor* Owner = GetOwner())
	{
		CachedEmotionComp = Owner->FindComponentByClass<UEmotionComponent>();
		if (!CachedEmotionComp)
		{
			UE_LOG(LogTemp, Warning, TEXT("MetahumanAnim: No EmotionComponent found on owner"));
		}

		// Find the Face skeletal mesh — search owner first, then Child Actors (for Metahuman setup)
		auto FindFaceMesh = [](AActor* Actor) -> USkeletalMeshComponent*
		{
			TArray<USkeletalMeshComponent*> SkeletalMeshes;
			Actor->GetComponents<USkeletalMeshComponent>(SkeletalMeshes);

			for (USkeletalMeshComponent* SMC : SkeletalMeshes)
			{
				if (SMC && SMC->GetName().Contains(TEXT("Face")))
				{
					return SMC;
				}
			}
			return nullptr;
		};

		// First search the owner actor
		CachedSkeletalMesh = FindFaceMesh(Owner);

		// If not found, search inside Child Actor components (Metahuman is spawned as Child Actor)
		if (!CachedSkeletalMesh)
		{
			TArray<UChildActorComponent*> ChildActors;
			Owner->GetComponents<UChildActorComponent>(ChildActors);

			for (UChildActorComponent* CAC : ChildActors)
			{
				if (CAC && CAC->GetChildActor())
				{
					UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: Searching Child Actor: %s"), *CAC->GetChildActor()->GetName());

					// Search the child actor for face mesh
					CachedSkeletalMesh = FindFaceMesh(CAC->GetChildActor());
					if (CachedSkeletalMesh)
					{
						UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: Found Face mesh in Child Actor: %s"), *CachedSkeletalMesh->GetName());
						break;
					}

					// Also search recursively — Metahumans have nested child actors for Face
					TArray<UChildActorComponent*> NestedChildren;
					CAC->GetChildActor()->GetComponents<UChildActorComponent>(NestedChildren);
					for (UChildActorComponent* Nested : NestedChildren)
					{
						if (Nested && Nested->GetChildActor())
						{
							CachedSkeletalMesh = FindFaceMesh(Nested->GetChildActor());
							if (CachedSkeletalMesh)
							{
								UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: Found Face mesh in nested Child Actor: %s"), *CachedSkeletalMesh->GetName());
								break;
							}
						}
					}
					if (CachedSkeletalMesh) break;
				}
			}
		}

		if (!CachedSkeletalMesh)
		{
			UE_LOG(LogTemp, Warning, TEXT("MetahumanAnim: No Face skeletal mesh found on owner or Child Actors"));
		}
		else
		{
			// List ALL available morph targets from the skeletal mesh asset
			if (USkeletalMesh* SkelMesh = CachedSkeletalMesh->GetSkeletalMeshAsset())
			{
				const TArray<UMorphTarget*>& MorphTargets = SkelMesh->GetMorphTargets();
				UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: Face mesh '%s' has %d total morph targets available"),
					*CachedSkeletalMesh->GetName(), MorphTargets.Num());

				// Log morph targets containing key facial feature keywords
				TArray<FString> Keywords = {TEXT("smile"), TEXT("frown"), TEXT("mouth"), TEXT("eye_s"), TEXT("eye_w"), TEXT("jaw"), TEXT("nose"), TEXT("cheek"), TEXT("pucker")};
				for (const UMorphTarget* MT : MorphTargets)
				{
					if (!MT) continue;
					FString Name = MT->GetName();
					for (const FString& Keyword : Keywords)
					{
						if (Name.Contains(Keyword, ESearchCase::IgnoreCase))
						{
							UE_LOG(LogTemp, Log, TEXT("  FacialMorph: %s"), *Name);
							break;
						}
					}
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("MetahumanAnim: Face mesh has no skeletal mesh asset"));
			}
		}
	}
}

void UMetahumanAnimComponent::ShutdownSubsystem()
{
	// Reset all morph targets to zero
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

void UMetahumanAnimComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsInitialized || !LoadedMappingData || !CachedSkeletalMesh)
	{
		return;
	}

	// Read the current emotion state directly from EmotionComponent
	FEmotionState CurrentState;
	if (CachedEmotionComp)
	{
		CurrentState = CachedEmotionComp->GetCurrentEmotionState();
	}

	// Look up blend shape targets for the current emotion state
	TArray<FEmotionBlendShapeTarget> Targets = LoadedMappingData->GetTargetsForState(CurrentState);

	// Debug: log when emotion changes and targets are found (only log once per change)
	static EEmotionType LastLoggedEmotion = EEmotionType::Neutral;
	if (CurrentState.PrimaryEmotion != LastLoggedEmotion)
	{
		UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: Emotion changed to %s (intensity: %.2f), found %d blend shape targets"),
			*UEnum::GetValueAsString(CurrentState.PrimaryEmotion), CurrentState.Intensity, Targets.Num());
		for (const FEmotionBlendShapeTarget& T : Targets)
		{
			UE_LOG(LogTemp, Log, TEXT("  -> Setting morph '%s' to %.2f"), *T.BlendShapeName.ToString(), T.TargetValue);
		}
		LastLoggedEmotion = CurrentState.PrimaryEmotion;
	}

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
		CurrentValue = FMath::FInterpTo(CurrentValue, TargetValue, DeltaTime, InterpolationSpeed);

		// Apply to skeletal mesh
		CachedSkeletalMesh->SetMorphTarget(MorphName, CurrentValue);
	}

	// Remove blend shapes that have reached zero and are no longer in the target set
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
