#include "EmotionComponent.h"
#include "EmotionStateMachine.h"
#include "EmotionGraphDataAsset.h"
#include "LLM_NPC/Core/NPCConfigDataAsset.h"

UEmotionComponent::UEmotionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SubsystemName = TEXT("EmotionEngine");
}

void UEmotionComponent::InitializeSubsystem()
{
	Super::InitializeSubsystem();

	// Attempt to find NPCConfigDataAsset on the owning actor
	const UNPCConfigDataAsset* Config = nullptr;

	if (AActor* Owner = GetOwner())
	{
		// Look for config as a property on the actor or its components
		// Convention: actors store a reference to their NPCConfig
		// For now, we check for a property named "NPCConfig" on the owner
		if (const FProperty* Prop = Owner->GetClass()->FindPropertyByName(TEXT("NPCConfig")))
		{
			if (const FObjectProperty* ObjProp = CastField<FObjectProperty>(Prop))
			{
				Config = Cast<UNPCConfigDataAsset>(ObjProp->GetObjectPropertyValue_InContainer(Owner));
			}
		}
	}

	if (Config)
	{
		LoadFromConfig(Config);
	}
	else
	{
		// No config found — create a default state machine with no rules
		UE_LOG(LogTemp, Warning, TEXT("EmotionComponent: No NPCConfig found on owner. Creating default state machine."));
		StateMachine = NewObject<UEmotionStateMachine>(this);

		FEmotionState DefaultState;
		DefaultState.PrimaryEmotion = EEmotionType::Neutral;
		DefaultState.Intensity = 0.0f;
		DefaultState.PAD = EmotionPADDefaults::Neutral;
		StateMachine->SetCurrentState(DefaultState);

		StateMachine->OnEmotionStateChanged.AddDynamic(this, &UEmotionComponent::HandleEmotionStateChanged);
	}

	bIsAvailable = (StateMachine != nullptr);
	UE_LOG(LogTemp, Log, TEXT("EmotionEngine initialized. Available: %s"), bIsAvailable ? TEXT("true") : TEXT("false"));
}

void UEmotionComponent::ShutdownSubsystem()
{
	if (StateMachine)
	{
		StateMachine->OnEmotionStateChanged.RemoveDynamic(this, &UEmotionComponent::HandleEmotionStateChanged);
		StateMachine = nullptr;
	}

	Super::ShutdownSubsystem();
}

void UEmotionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (StateMachine && bIsAvailable)
	{
		StateMachine->Tick(DeltaTime);
	}
}

void UEmotionComponent::ProcessSignal(const FEmotionSignal& Signal)
{
	if (StateMachine && bIsAvailable)
	{
		StateMachine->ProcessSignal(Signal);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("EmotionComponent::ProcessSignal - State machine not available."));
	}
}

FEmotionState UEmotionComponent::GetCurrentEmotionState() const
{
	if (StateMachine)
	{
		return StateMachine->GetCurrentState();
	}

	return FEmotionState();
}

void UEmotionComponent::LoadFromConfig(const UNPCConfigDataAsset* Config)
{
	if (!Config)
	{
		return;
	}

	// Try to load the emotion graph data asset
	UEmotionGraphDataAsset* GraphAsset = Config->EmotionGraphAsset.LoadSynchronous();

	if (GraphAsset)
	{
		StateMachine = GraphAsset->CreateStateMachine(this);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("EmotionComponent: EmotionGraphAsset not set in config. Creating default state machine."));
		StateMachine = NewObject<UEmotionStateMachine>(this);

		FEmotionState DefaultState;
		DefaultState.PrimaryEmotion = Config->DefaultEmotion;
		DefaultState.Intensity = Config->DefaultIntensity;
		DefaultState.PAD = EmotionPADDefaults::GetCanonicalPAD(Config->DefaultEmotion);
		DefaultState.PAD = FPADVector(
			DefaultState.PAD.Pleasure * Config->DefaultIntensity,
			DefaultState.PAD.Arousal * Config->DefaultIntensity,
			DefaultState.PAD.Dominance * Config->DefaultIntensity
		);
		StateMachine->SetCurrentState(DefaultState);
	}

	if (StateMachine)
	{
		// Apply archetype transition costs
		StateMachine->EmotionTransitionCosts = Config->EmotionTransitionCosts;
		StateMachine->DecayRate = Config->EmotionDecayRate;
		StateMachine->NeutralThreshold = Config->NeutralThreshold;

		// Bind state change delegate
		StateMachine->OnEmotionStateChanged.AddDynamic(this, &UEmotionComponent::HandleEmotionStateChanged);
	}
}

void UEmotionComponent::HandleEmotionStateChanged(FEmotionState OldState, FEmotionState NewState)
{
	UE_LOG(LogTemp, Log, TEXT("EmotionEngine: %s (%.2f) -> %s (%.2f)"),
		*UEnum::GetValueAsString(OldState.PrimaryEmotion), OldState.Intensity,
		*UEnum::GetValueAsString(NewState.PrimaryEmotion), NewState.Intensity);

	// Re-broadcast on the component's own delegate for external listeners
	OnEmotionChanged.Broadcast(OldState, NewState);
}
