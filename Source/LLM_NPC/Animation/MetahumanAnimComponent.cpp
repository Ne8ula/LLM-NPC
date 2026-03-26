#include "MetahumanAnimComponent.h"
#include "LLM_NPC/Emotion/EmotionComponent.h"
#include "Components/SkeletalMeshComponent.h"

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

		// Find the Face skeletal mesh (Metahumans have separate Face and Body meshes)
		// Look for a component with "Face" in its name, or fall back to first skeletal mesh
		TArray<USkeletalMeshComponent*> SkeletalMeshes;
		Owner->GetComponents<USkeletalMeshComponent>(SkeletalMeshes);

		for (USkeletalMeshComponent* SMC : SkeletalMeshes)
		{
			if (SMC && SMC->GetName().Contains(TEXT("Face")))
			{
				CachedSkeletalMesh = SMC;
				UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: Found Face mesh: %s"), *SMC->GetName());
				break;
			}
		}

		// Fallback to first skeletal mesh if no Face mesh found
		if (!CachedSkeletalMesh && SkeletalMeshes.Num() > 0)
		{
			CachedSkeletalMesh = SkeletalMeshes[0];
			UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: Using fallback mesh: %s"), *CachedSkeletalMesh->GetName());
		}

		if (!CachedSkeletalMesh)
		{
			UE_LOG(LogTemp, Warning, TEXT("MetahumanAnim: No skeletal mesh found on owner '%s'"),
				*Owner->GetName());
		}
		else
		{
			// Log available morph targets for debugging
			if (CachedSkeletalMesh->GetSkeletalMeshAsset())
			{
				TArray<FString> MorphNames;
				CachedSkeletalMesh->GetSkeletalMeshAsset()->GetMorphTargetNames(MorphNames);
				UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: Found %d morph targets on face mesh"), MorphNames.Num());
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
