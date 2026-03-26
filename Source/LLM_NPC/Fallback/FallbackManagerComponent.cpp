#include "FallbackManagerComponent.h"
#include "InputModeSubsystem.h"
#include "LLM_NPC/Core/NPCSubsystemComponent.h"
#include "TimerManager.h"
#include "Engine/GameInstance.h"

UFallbackManagerComponent::UFallbackManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SubsystemName = TEXT("FallbackManager");
}

void UFallbackManagerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UFallbackManagerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(DevicePollTimerHandle);
	}
	Super::EndPlay(EndPlayReason);
}

void UFallbackManagerComponent::InitializeSubsystem()
{
	Super::InitializeSubsystem();

	// Run an initial device check
	CheckDeviceAvailability();

	// Start periodic polling
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
			DevicePollTimerHandle,
			this,
			&UFallbackManagerComponent::PollDevices,
			PollIntervalSeconds,
			true // Looping
		);
	}

	UE_LOG(LogTemp, Log, TEXT("FallbackManager: Initialized, polling every %.1f seconds"), PollIntervalSeconds);
}

void UFallbackManagerComponent::ShutdownSubsystem()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(DevicePollTimerHandle);
	}

	Super::ShutdownSubsystem();
}

void UFallbackManagerComponent::PollDevices()
{
	CheckDeviceAvailability();
}

void UFallbackManagerComponent::CheckDeviceAvailability()
{
	const bool bMicAvailable = IsMicrophoneAvailable();
	const bool bCameraAvailable = IsCameraAvailable();

	// Detect transitions and fire delegates
	if (bMicAvailable != bLastMicAvailable)
	{
		bLastMicAvailable = bMicAvailable;
		OnInputModeChanged.Broadcast(TEXT("Microphone"), bMicAvailable);
		UE_LOG(LogTemp, Log, TEXT("FallbackManager: Microphone %s"),
			bMicAvailable ? TEXT("available") : TEXT("unavailable"));
	}

	if (bCameraAvailable != bLastCameraAvailable)
	{
		bLastCameraAvailable = bCameraAvailable;
		OnInputModeChanged.Broadcast(TEXT("Camera"), bCameraAvailable);
		UE_LOG(LogTemp, Log, TEXT("FallbackManager: Camera %s"),
			bCameraAvailable ? TEXT("available") : TEXT("unavailable"));
	}

	UpdateDegradationLevel(bMicAvailable, bCameraAvailable);
}

void UFallbackManagerComponent::UpdateDegradationLevel(bool bMicAvailable, bool bCameraAvailable)
{
	EDegradationLevel NewLevel;

	if (bMicAvailable && bCameraAvailable)
	{
		NewLevel = EDegradationLevel::Full;
	}
	else if (bMicAvailable && !bCameraAvailable)
	{
		NewLevel = EDegradationLevel::NoCamera;
	}
	else if (!bMicAvailable && bCameraAvailable)
	{
		NewLevel = EDegradationLevel::NoMic;
	}
	else
	{
		NewLevel = EDegradationLevel::Minimal;
	}

	if (NewLevel != CurrentDegradationLevel)
	{
		CurrentDegradationLevel = NewLevel;
		UE_LOG(LogTemp, Log, TEXT("FallbackManager: Degradation level changed to %d"),
			static_cast<uint8>(CurrentDegradationLevel));

		// Auto-switch input modes via the InputModeSubsystem
		UInputModeSubsystem* InputSubsystem = GetInputModeSubsystem();
		if (!InputSubsystem)
		{
			return;
		}

		switch (CurrentDegradationLevel)
		{
		case EDegradationLevel::Full:
			InputSubsystem->SetDialogueInput(EDialogueInputMode::Voice);
			InputSubsystem->SetManipulationInput(EManipulationInputMode::Gesture);
			break;

		case EDegradationLevel::NoCamera:
			// Camera lost — fall back to keyboard/mouse for manipulation,
			// keep voice for dialogue.
			InputSubsystem->SetDialogueInput(EDialogueInputMode::Voice);
			InputSubsystem->SetManipulationInput(EManipulationInputMode::KeyboardMouse);
			break;

		case EDegradationLevel::NoMic:
			// Mic lost — fall back to text for dialogue, keep gesture.
			InputSubsystem->SetDialogueInput(EDialogueInputMode::Text);
			InputSubsystem->SetManipulationInput(EManipulationInputMode::Gesture);
			break;

		case EDegradationLevel::Minimal:
			InputSubsystem->SetDialogueInput(EDialogueInputMode::Text);
			InputSubsystem->SetManipulationInput(EManipulationInputMode::KeyboardMouse);
			break;
		}
	}
}

void UFallbackManagerComponent::SetDialogueMode(EDialogueInputMode NewMode)
{
	if (UInputModeSubsystem* InputSubsystem = GetInputModeSubsystem())
	{
		InputSubsystem->SetDialogueInput(NewMode);
		OnInputModeChanged.Broadcast(
			NewMode == EDialogueInputMode::Voice ? TEXT("Voice") : TEXT("Text"),
			true);
	}
}

void UFallbackManagerComponent::SetManipulationMode(EManipulationInputMode NewMode)
{
	if (UInputModeSubsystem* InputSubsystem = GetInputModeSubsystem())
	{
		InputSubsystem->SetManipulationInput(NewMode);
		OnInputModeChanged.Broadcast(
			NewMode == EManipulationInputMode::Gesture ? TEXT("Gesture") : TEXT("KeyboardMouse"),
			true);
	}
}

UInputModeSubsystem* UFallbackManagerComponent::GetInputModeSubsystem() const
{
	if (const UWorld* World = GetWorld())
	{
		if (UGameInstance* GI = World->GetGameInstance())
		{
			return GI->GetSubsystem<UInputModeSubsystem>();
		}
	}
	return nullptr;
}

bool UFallbackManagerComponent::IsMicrophoneAvailable() const
{
	// Check for a WhisperSTT or similar speech subsystem on the same actor
	if (const AActor* Owner = GetOwner())
	{
		TArray<UActorComponent*> Components;
		Owner->GetComponents(UNPCSubsystemComponent::StaticClass(), Components);
		for (const UActorComponent* Comp : Components)
		{
			if (Comp && (Comp->GetClass()->GetName().Contains(TEXT("WhisperSTT")) ||
				Comp->GetClass()->GetName().Contains(TEXT("Speech"))))
			{
				const UNPCSubsystemComponent* Subsystem = Cast<UNPCSubsystemComponent>(Comp);
				if (Subsystem)
				{
					return Subsystem->IsSubsystemAvailable();
				}
			}
		}
	}

	// If no speech subsystem found, assume mic is not available
	return false;
}

bool UFallbackManagerComponent::IsCameraAvailable() const
{
	// Check for a CameraManager or Vision subsystem on the same actor
	if (const AActor* Owner = GetOwner())
	{
		TArray<UActorComponent*> Components;
		Owner->GetComponents(UNPCSubsystemComponent::StaticClass(), Components);
		for (const UActorComponent* Comp : Components)
		{
			if (Comp && (Comp->GetClass()->GetName().Contains(TEXT("Camera")) ||
				Comp->GetClass()->GetName().Contains(TEXT("Vision"))))
			{
				const UNPCSubsystemComponent* Subsystem = Cast<UNPCSubsystemComponent>(Comp);
				if (Subsystem)
				{
					return Subsystem->IsSubsystemAvailable();
				}
			}
		}
	}

	// If no vision subsystem found, assume camera is not available
	return false;
}
