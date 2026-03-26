#include "InputModeSubsystem.h"

void UInputModeSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	ActiveDialogueInput = EDialogueInputMode::Voice;
	ActiveManipulationInput = EManipulationInputMode::Gesture;

	UE_LOG(LogTemp, Log, TEXT("InputModeSubsystem: Initialized with Voice + Gesture defaults"));
}

void UInputModeSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UInputModeSubsystem::SetDialogueInput(EDialogueInputMode NewMode)
{
	if (ActiveDialogueInput != NewMode)
	{
		const EDialogueInputMode OldMode = ActiveDialogueInput;
		ActiveDialogueInput = NewMode;

		UE_LOG(LogTemp, Log, TEXT("InputModeSubsystem: Dialogue input changed from %d to %d"),
			static_cast<uint8>(OldMode), static_cast<uint8>(NewMode));

		OnDialogueInputModeChanged.Broadcast();
	}
}

void UInputModeSubsystem::SetManipulationInput(EManipulationInputMode NewMode)
{
	if (ActiveManipulationInput != NewMode)
	{
		const EManipulationInputMode OldMode = ActiveManipulationInput;
		ActiveManipulationInput = NewMode;

		UE_LOG(LogTemp, Log, TEXT("InputModeSubsystem: Manipulation input changed from %d to %d"),
			static_cast<uint8>(OldMode), static_cast<uint8>(NewMode));

		OnManipulationInputModeChanged.Broadcast();
	}
}
