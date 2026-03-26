#include "EmotionGraphDataAsset.h"
#include "EmotionStateMachine.h"
#include "EmotionTransitionRule.h"

UEmotionStateMachine* UEmotionGraphDataAsset::CreateStateMachine(UObject* Outer) const
{
	if (!Outer)
	{
		UE_LOG(LogTemp, Error, TEXT("EmotionGraphDataAsset::CreateStateMachine - Outer is null"));
		return nullptr;
	}

	UEmotionStateMachine* StateMachine = NewObject<UEmotionStateMachine>(Outer);

	// Create transition rules from edge configs
	for (const FEmotionEdgeConfig& Edge : Edges)
	{
		UEmotionTransitionRule* Rule = NewObject<UEmotionTransitionRule>(StateMachine);
		Rule->TargetEmotion = Edge.TargetEmotion;
		Rule->MinInputStrength = Edge.MinInputStrength;
		Rule->RequiredKeywords = Edge.RequiredKeywords;
		Rule->CooldownTime = Edge.Cooldown;
		Rule->TransitionCost = Edge.Cost;

		StateMachine->TransitionRules.Add(Rule);
	}

	// Set up initial state
	FEmotionState InitialState;
	InitialState.PrimaryEmotion = DefaultEmotion;
	InitialState.Intensity = DefaultIntensity;
	InitialState.PAD = EmotionPADDefaults::GetCanonicalPAD(DefaultEmotion);

	// Apply custom PAD if defined for the default emotion node
	for (const FEmotionNodeConfig& Node : Nodes)
	{
		if (Node.EmotionType == DefaultEmotion && Node.bUseCustomPAD)
		{
			InitialState.PAD = Node.CustomPAD;
			break;
		}
	}

	// Scale PAD by initial intensity
	InitialState.PAD = FPADVector(
		InitialState.PAD.Pleasure * DefaultIntensity,
		InitialState.PAD.Arousal * DefaultIntensity,
		InitialState.PAD.Dominance * DefaultIntensity
	);

	StateMachine->SetCurrentState(InitialState);

	UE_LOG(LogTemp, Log, TEXT("EmotionGraphDataAsset: Created state machine with %d rules, starting at %s"),
		StateMachine->TransitionRules.Num(),
		*UEnum::GetValueAsString(DefaultEmotion));

	return StateMachine;
}
