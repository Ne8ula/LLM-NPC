#include "MetahumanAnimComponent.h"
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

	// Cache the skeletal mesh component from the owner
	if (AActor* Owner = GetOwner())
	{
		CachedSkeletalMesh = Owner->FindComponentByClass<USkeletalMeshComponent>();
		if (!CachedSkeletalMesh)
		{
			UE_LOG(LogTemp, Warning, TEXT("MetahumanAnim: No USkeletalMeshComponent found on owner '%s'"),
				*Owner->GetName());
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

	// Read the current emotion state from the Emotion subsystem on the same actor
	FEmotionState CurrentState;
	if (AActor* Owner = GetOwner())
	{
		TArray<UActorComponent*> Components;
		Owner->GetComponents(UNPCSubsystemComponent::StaticClass(), Components);
		for (UActorComponent* Comp : Components)
		{
			if (Comp && Comp->GetClass()->GetName().Contains(TEXT("Emotion")))
			{
				// Read the CurrentEmotionState property via reflection
				if (FStructProperty* StateProp = CastField<FStructProperty>(
					Comp->GetClass()->FindPropertyByName(TEXT("CurrentEmotionState"))))
				{
					const FEmotionState* StatePtr = StateProp->ContainerPtrToValuePtr<FEmotionState>(Comp);
					if (StatePtr)
					{
						CurrentState = *StatePtr;
					}
				}
				break;
			}
		}
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
