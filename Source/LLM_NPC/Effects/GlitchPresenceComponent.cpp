#include "GlitchPresenceComponent.h"

#include "Components/MeshComponent.h"
#include "GameFramework/Actor.h"
#include "Materials/MaterialInstanceDynamic.h"

UGlitchPresenceComponent::UGlitchPresenceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
	bTickInEditor = true;
}

void UGlitchPresenceComponent::OnRegister()
{
	Super::OnRegister();

	// Init in editor preview worlds so the glitch plays in the viewport without Play.
	// Game worlds defer init to BeginPlay (component lifecycle convention).
	const UWorld* World = GetWorld();
	if (World && !World->IsGameWorld())
	{
		InitializeIfNeeded();
	}
}

void UGlitchPresenceComponent::BeginPlay()
{
	Super::BeginPlay();
	InitializeIfNeeded();
}

void UGlitchPresenceComponent::InitializeIfNeeded()
{
	if (bInitialized)
	{
		return;
	}

	UMeshComponent* Mesh = ResolveMesh();
	if (!Mesh)
	{
		return;
	}

	const int32 SlotCount = Mesh->GetNumMaterials();
	DynamicMaterials.Reset(SlotCount);
	for (int32 SlotIndex = 0; SlotIndex < SlotCount; ++SlotIndex)
	{
		UMaterialInstanceDynamic* MID = Mesh->CreateAndSetMaterialInstanceDynamic(SlotIndex);
		DynamicMaterials.Add(MID);
	}

	bInitialized = true;
	EnterState(bStartHidden ? EGlitchPresenceState::Hidden : EGlitchPresenceState::Visible);
}

void UGlitchPresenceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	StateElapsed += DeltaTime;
	const float Alpha = StateDuration > 0.f ? FMath::Clamp(StateElapsed / StateDuration, 0.f, 1.f) : 1.f;

	const bool bInTransition =
		State == EGlitchPresenceState::GlitchingOut || State == EGlitchPresenceState::GlitchingIn;
	if (bInTransition && SeedRefreshHz > 0.f)
	{
		SeedRefreshAccumulator += DeltaTime;
		const float Period = 1.f / SeedRefreshHz;
		if (SeedRefreshAccumulator >= Period)
		{
			SeedRefreshAccumulator = 0.f;
			RandomiseSeed();
		}
	}

	switch (State)
	{
	case EGlitchPresenceState::Visible:
		if (StateElapsed >= StateDuration)
		{
			EnterState(EGlitchPresenceState::GlitchingOut);
		}
		break;

	case EGlitchPresenceState::GlitchingOut:
		SetGlitchPhase(Alpha);
		if (Alpha >= 1.f)
		{
			EnterState(EGlitchPresenceState::Hidden);
		}
		break;

	case EGlitchPresenceState::Hidden:
		if (StateElapsed >= StateDuration)
		{
			EnterState(EGlitchPresenceState::GlitchingIn);
		}
		break;

	case EGlitchPresenceState::GlitchingIn:
		SetGlitchPhase(1.f - Alpha);
		if (Alpha >= 1.f)
		{
			EnterState(EGlitchPresenceState::Visible);
		}
		break;
	}
}

void UGlitchPresenceComponent::ForceState(EGlitchPresenceState NewState)
{
	EnterState(NewState);
}

void UGlitchPresenceComponent::EnterState(EGlitchPresenceState NewState)
{
	State = NewState;
	StateElapsed = 0.f;
	SeedRefreshAccumulator = 0.f;

	UMeshComponent* Mesh = ResolveMesh();

	switch (NewState)
	{
	case EGlitchPresenceState::Visible:
		StateDuration = FMath::FRandRange(VisibleDurationRange.X, VisibleDurationRange.Y);
		if (Mesh)
		{
			Mesh->SetVisibility(true, true);
		}
		SetGlitchPhase(0.f);
		break;

	case EGlitchPresenceState::GlitchingOut:
		StateDuration = GlitchOutDuration;
		RandomiseSeed();
		SetGlitchPhase(0.f);
		break;

	case EGlitchPresenceState::Hidden:
		StateDuration = FMath::FRandRange(HiddenDurationRange.X, HiddenDurationRange.Y);
		SetGlitchPhase(1.f);
		if (Mesh)
		{
			Mesh->SetVisibility(false, true);
		}
		break;

	case EGlitchPresenceState::GlitchingIn:
		StateDuration = GlitchInDuration;
		RandomiseSeed();
		if (Mesh)
		{
			Mesh->SetVisibility(true, true);
		}
		SetGlitchPhase(1.f);
		break;
	}
}

void UGlitchPresenceComponent::SetGlitchPhase(float Phase)
{
	for (UMaterialInstanceDynamic* MID : DynamicMaterials)
	{
		if (MID)
		{
			MID->SetScalarParameterValue(GlitchPhaseParam, Phase);
		}
	}
}

void UGlitchPresenceComponent::RandomiseSeed()
{
	const float Seed = FMath::FRand() * 1000.f;
	for (UMaterialInstanceDynamic* MID : DynamicMaterials)
	{
		if (MID)
		{
			MID->SetScalarParameterValue(GlitchSeedParam, Seed);
		}
	}
}

UMeshComponent* UGlitchPresenceComponent::ResolveMesh() const
{
	if (TargetMesh)
	{
		return TargetMesh;
	}
	return GetOwner() ? GetOwner()->FindComponentByClass<UMeshComponent>() : nullptr;
}
