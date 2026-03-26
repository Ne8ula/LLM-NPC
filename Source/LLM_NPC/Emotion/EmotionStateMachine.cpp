#include "EmotionStateMachine.h"
#include "EmotionTransitionRule.h"
#include "Engine/World.h"

UEmotionStateMachine::UEmotionStateMachine()
{
	CurrentState.PrimaryEmotion = EEmotionType::Neutral;
	CurrentState.Intensity = 0.0f;
	CurrentState.PAD = EmotionPADDefaults::Neutral;
	CurrentState.StateEnteredTime = 0.0f;
	TargetPAD = EmotionPADDefaults::Neutral;
}

void UEmotionStateMachine::ProcessSignal(const FEmotionSignal& Signal)
{
	const EEmotionType BestTarget = FindBestTransition(Signal);

	if (BestTarget == CurrentState.PrimaryEmotion && BestTarget != Signal.TargetEmotion)
	{
		// No valid transition found; boost intensity of current state instead
		CurrentState.Intensity = FMath::Clamp(CurrentState.Intensity + Signal.Strength * 0.25f, 0.0f, 1.0f);
		return;
	}

	if (BestTarget == CurrentState.PrimaryEmotion)
	{
		// Same emotion — reinforce intensity
		const float NewIntensity = FMath::Clamp(CurrentState.Intensity + Signal.Strength, 0.0f, 1.0f);
		CurrentState.Intensity = NewIntensity;

		// Update target PAD toward the reinforced emotion
		const FPADVector CanonicalPAD = EmotionPADDefaults::GetCanonicalPAD(BestTarget);
		TargetPAD = FPADVector(
			CanonicalPAD.Pleasure * NewIntensity,
			CanonicalPAD.Arousal * NewIntensity,
			CanonicalPAD.Dominance * NewIntensity
		);
	}
	else
	{
		// Transition to a new emotion
		TransitionTo(BestTarget, FMath::Clamp(Signal.Strength, 0.0f, 1.0f));
	}
}

void UEmotionStateMachine::Tick(float DeltaTime)
{
	if (DeltaTime <= 0.0f)
	{
		return;
	}

	// --- Intensity Decay ---
	if (CurrentState.PrimaryEmotion != EEmotionType::Neutral)
	{
		CurrentState.Intensity -= DecayRate * DeltaTime;

		if (CurrentState.Intensity <= NeutralThreshold)
		{
			TransitionTo(EEmotionType::Neutral, 0.0f);
			return;
		}

		// Update target PAD to reflect decayed intensity
		const FPADVector CanonicalPAD = EmotionPADDefaults::GetCanonicalPAD(CurrentState.PrimaryEmotion);
		TargetPAD = FPADVector(
			CanonicalPAD.Pleasure * CurrentState.Intensity,
			CanonicalPAD.Arousal * CurrentState.Intensity,
			CanonicalPAD.Dominance * CurrentState.Intensity
		);
	}

	// --- PAD Interpolation ---
	const float InterpAlpha = FMath::Clamp(PADInterpSpeed * DeltaTime, 0.0f, 1.0f);
	CurrentState.PAD = FPADVector::Lerp(CurrentState.PAD, TargetPAD, InterpAlpha);
}

EEmotionType UEmotionStateMachine::FindBestTransition(const FEmotionSignal& Signal) const
{
	const float TimeSinceLastTransition = GetCurrentTime() - LastTransitionTime;

	EEmotionType BestEmotion = CurrentState.PrimaryEmotion;
	float BestCost = MAX_FLT;

	for (const TObjectPtr<UEmotionTransitionRule>& Rule : TransitionRules)
	{
		if (!Rule || !Rule->EvaluateRule(Signal, TimeSinceLastTransition))
		{
			continue;
		}

		// Compute effective cost: rule cost * archetype cost multiplier + PAD distance
		float EffectiveCost = Rule->GetTransitionCost();

		// Apply per-emotion cost multiplier from NPC archetype
		const float* CostMultiplierPtr = EmotionTransitionCosts.Find(Rule->TargetEmotion);
		if (CostMultiplierPtr)
		{
			EffectiveCost *= *CostMultiplierPtr;
		}

		// Add PAD distance as heuristic component
		const FPADVector TargetCanonicalPAD = EmotionPADDefaults::GetCanonicalPAD(Rule->TargetEmotion);
		EffectiveCost += CurrentState.PAD.DistanceTo(TargetCanonicalPAD);

		if (EffectiveCost < BestCost)
		{
			BestCost = EffectiveCost;
			BestEmotion = Rule->TargetEmotion;
		}
	}

	return BestEmotion;
}

void UEmotionStateMachine::SetCurrentState(const FEmotionState& NewState)
{
	CurrentState = NewState;
	TargetPAD = NewState.PAD;
	LastTransitionTime = GetCurrentTime();
}

void UEmotionStateMachine::TransitionTo(EEmotionType NewEmotion, float NewIntensity)
{
	const FEmotionState OldState = CurrentState;

	CurrentState.PrimaryEmotion = NewEmotion;
	CurrentState.Intensity = FMath::Clamp(NewIntensity, 0.0f, 1.0f);
	CurrentState.StateEnteredTime = GetCurrentTime();

	// Set target PAD for smooth interpolation
	const FPADVector CanonicalPAD = EmotionPADDefaults::GetCanonicalPAD(NewEmotion);
	TargetPAD = FPADVector(
		CanonicalPAD.Pleasure * CurrentState.Intensity,
		CanonicalPAD.Arousal * CurrentState.Intensity,
		CanonicalPAD.Dominance * CurrentState.Intensity
	);

	LastTransitionTime = GetCurrentTime();

	// Fire delegate
	OnEmotionStateChanged.Broadcast(OldState, CurrentState);
}

EEmotionType UEmotionStateMachine::ClassifyPAD(const FPADVector& PAD) const
{
	EEmotionType NearestEmotion = EEmotionType::Neutral;
	float NearestDistance = MAX_FLT;

	// Iterate all emotion types and find nearest canonical PAD
	for (uint8 i = 0; i < static_cast<uint8>(EEmotionType::MAX); ++i)
	{
		const EEmotionType EmotionType = static_cast<EEmotionType>(i);
		const FPADVector CanonicalPAD = EmotionPADDefaults::GetCanonicalPAD(EmotionType);
		const float Distance = PAD.DistanceTo(CanonicalPAD);

		if (Distance < NearestDistance)
		{
			NearestDistance = Distance;
			NearestEmotion = EmotionType;
		}
	}

	return NearestEmotion;
}

float UEmotionStateMachine::GetCurrentTime() const
{
	if (const UWorld* World = GetWorld())
	{
		return World->GetTimeSeconds();
	}

	return static_cast<float>(FPlatformTime::Seconds());
}
