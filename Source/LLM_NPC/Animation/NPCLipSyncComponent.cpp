#include "NPCLipSyncComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Sound/SoundWave.h"

UNPCLipSyncComponent::UNPCLipSyncComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SubsystemName = TEXT("LipSync");
}

void UNPCLipSyncComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UNPCLipSyncComponent::InitializeSubsystem()
{
	Super::InitializeSubsystem();

	// Cache the skeletal mesh component from the owner
	if (AActor* Owner = GetOwner())
	{
		CachedSkeletalMesh = Owner->FindComponentByClass<USkeletalMeshComponent>();
		if (!CachedSkeletalMesh)
		{
			UE_LOG(LogTemp, Warning, TEXT("LipSync: No USkeletalMeshComponent found on owner '%s'"),
				*Owner->GetName());
		}
	}
}

void UNPCLipSyncComponent::ShutdownSubsystem()
{
	StopLipSync();
	Super::ShutdownSubsystem();
}

void UNPCLipSyncComponent::StartLipSync(USoundWave* AudioSource)
{
	if (!AudioSource)
	{
		UE_LOG(LogTemp, Warning, TEXT("LipSync: Cannot start - null AudioSource"));
		return;
	}

	AActor* Owner = GetOwner();
	if (!Owner)
	{
		return;
	}

	// Stop any existing lip sync
	StopLipSync();

	// Create or reuse an audio component
	ActiveAudioComponent = Owner->FindComponentByClass<UAudioComponent>();
	if (!ActiveAudioComponent)
	{
		ActiveAudioComponent = NewObject<UAudioComponent>(Owner, TEXT("LipSyncAudio"));
		ActiveAudioComponent->RegisterComponent();
		ActiveAudioComponent->AttachToComponent(
			Owner->GetRootComponent(),
			FAttachmentTransformRules::KeepRelativeTransform);
	}

	ActiveAudioComponent->SetSound(AudioSource);
	ActiveAudioComponent->Play();

	bIsLipSyncActive = true;
	UE_LOG(LogTemp, Log, TEXT("LipSync: Started lip sync playback"));
}

void UNPCLipSyncComponent::StopLipSync()
{
	bIsLipSyncActive = false;
	TargetMouthOpenValue = 0.0f;

	if (ActiveAudioComponent && ActiveAudioComponent->IsPlaying())
	{
		ActiveAudioComponent->Stop();
	}

	// Reset morph target
	if (CachedSkeletalMesh)
	{
		CachedSkeletalMesh->SetMorphTarget(MouthOpenBlendShape, 0.0f);
	}
	CurrentMouthOpenValue = 0.0f;

	UE_LOG(LogTemp, Log, TEXT("LipSync: Stopped lip sync"));
}

void UNPCLipSyncComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!CachedSkeletalMesh)
	{
		return;
	}

	if (bIsLipSyncActive && ActiveAudioComponent && ActiveAudioComponent->IsPlaying())
	{
		// Simple amplitude-based viseme driver (placeholder for OVRLipSync).
		// Sample the audio component's current envelope / attenuation as a proxy
		// for amplitude. In production this would be replaced with phoneme analysis.
		float Amplitude = 0.0f;

		// Use the audio component's envelope follower value if available.
		// GetAudioComponentEnvelopeValue is not always reliable, so we also
		// check if the component is actively producing sound.
		if (ActiveAudioComponent->IsPlaying())
		{
			// Approximate amplitude from the audio component's internal state.
			// This is a simplified placeholder — a real implementation would use
			// an FFT or OVRLipSync phoneme analysis.
			const float RawAmplitude = ActiveAudioComponent->GetPlaybackPercentage();

			// Generate a pseudo-amplitude using a sine wave modulated by time
			// to simulate mouth movement when real amplitude data is not available.
			const float Time = GetWorld()->GetTimeSeconds();
			Amplitude = FMath::Abs(FMath::Sin(Time * 12.0f)) *
				FMath::Abs(FMath::Sin(Time * 5.3f)) * 0.8f + 0.1f;
			Amplitude = FMath::Clamp(Amplitude * Sensitivity, 0.0f, 1.0f);
		}

		TargetMouthOpenValue = Amplitude;
	}
	else if (bIsLipSyncActive)
	{
		// Audio finished playing
		bIsLipSyncActive = false;
		TargetMouthOpenValue = 0.0f;
	}
	else
	{
		TargetMouthOpenValue = 0.0f;
	}

	// Smoothly interpolate toward target
	CurrentMouthOpenValue = FMath::FInterpTo(
		CurrentMouthOpenValue, TargetMouthOpenValue, DeltaTime, LipSyncInterpolationSpeed);

	CachedSkeletalMesh->SetMorphTarget(MouthOpenBlendShape, CurrentMouthOpenValue);
}
