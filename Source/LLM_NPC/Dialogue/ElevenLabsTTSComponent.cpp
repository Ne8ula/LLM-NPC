#include "ElevenLabsTTSComponent.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundWaveProcedural.h"
#include "Engine/World.h"
#include "Async/Async.h"

UElevenLabsTTSComponent::UElevenLabsTTSComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SubsystemName = TEXT("ElevenLabsTTS");
}

void UElevenLabsTTSComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UElevenLabsTTSComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	StopSpeaking();
	ShutdownSubsystem();
	Super::EndPlay(EndPlayReason);
}

void UElevenLabsTTSComponent::InitializeSubsystem()
{
	Super::InitializeSubsystem();

	LoadAPIKey();

	// Create audio playback component
	AActor* Owner = GetOwner();
	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("ElevenLabsTTSComponent: No owner actor."));
		bIsAvailable = false;
		return;
	}

	AudioPlaybackComponent = NewObject<UAudioComponent>(Owner);
	if (AudioPlaybackComponent)
	{
		AudioPlaybackComponent->RegisterComponent();
		AudioPlaybackComponent->bAutoActivate = false;
		AudioPlaybackComponent->bAutoDestroy = false;
		AudioPlaybackComponent->OnAudioFinished.AddDynamic(this, &UElevenLabsTTSComponent::OnAudioPlaybackFinished);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ElevenLabsTTSComponent: Failed to create AudioComponent."));
		bIsAvailable = false;
		return;
	}

	if (bAPIKeyConfigured)
	{
		bIsAvailable = true;
		bIsInitialized = true;
		UE_LOG(LogTemp, Log, TEXT("ElevenLabsTTSComponent: Initialized successfully."));
	}
	else
	{
		bIsAvailable = false;
		UE_LOG(LogTemp, Warning, TEXT("ElevenLabsTTSComponent: No API key configured. TTS will not be available."));
	}
}

void UElevenLabsTTSComponent::ShutdownSubsystem()
{
	StopSpeaking();

	if (AudioPlaybackComponent)
	{
		AudioPlaybackComponent->OnAudioFinished.RemoveDynamic(this, &UElevenLabsTTSComponent::OnAudioPlaybackFinished);
		AudioPlaybackComponent->DestroyComponent();
		AudioPlaybackComponent = nullptr;
	}

	CurrentSoundWave = nullptr;
	bIsAvailable = false;
	bIsInitialized = false;

	Super::ShutdownSubsystem();
}

bool UElevenLabsTTSComponent::IsSubsystemAvailable() const
{
	return bIsAvailable && bAPIKeyConfigured;
}

void UElevenLabsTTSComponent::LoadAPIKey()
{
	// Try environment variable first
	FString EnvKey = FPlatformMisc::GetEnvironmentVariable(TEXT("ELEVENLABS_API_KEY"));
	if (!EnvKey.IsEmpty())
	{
		APIKey = EnvKey;
		bAPIKeyConfigured = true;
		UE_LOG(LogTemp, Log, TEXT("ElevenLabsTTSComponent: API key loaded from environment variable."));
		return;
	}

	// Fallback: try config file
	FString ConfigKey;
	if (GConfig && GConfig->GetString(TEXT("/Script/LLM_NPC.ElevenLabsSettings"), TEXT("APIKey"), ConfigKey, GGameIni))
	{
		APIKey = ConfigKey;
		bAPIKeyConfigured = true;
		UE_LOG(LogTemp, Log, TEXT("ElevenLabsTTSComponent: API key loaded from project settings."));
		return;
	}

	bAPIKeyConfigured = false;
	UE_LOG(LogTemp, Warning, TEXT("ElevenLabsTTSComponent: No API key found. Set ELEVENLABS_API_KEY environment variable."));
}

void UElevenLabsTTSComponent::SpeakText(const FString& Text, const FString& VoiceID, float Stability, float SimilarityBoost)
{
	if (!IsSubsystemAvailable())
	{
		UE_LOG(LogTemp, Warning, TEXT("ElevenLabsTTSComponent: Cannot speak - subsystem not available."));
		return;
	}

	if (Text.IsEmpty())
	{
		return;
	}

	// Stop any current playback
	StopSpeaking();

	// Resolve parameters
	FString ResolvedVoiceID = VoiceID.IsEmpty() ? DefaultVoiceID : VoiceID;
	float ResolvedStability = Stability < 0.0f ? DefaultStability : Stability;
	float ResolvedSimilarityBoost = SimilarityBoost < 0.0f ? DefaultSimilarityBoost : SimilarityBoost;

	if (ResolvedVoiceID.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("ElevenLabsTTSComponent: No voice ID specified."));
		return;
	}

	// Build and send HTTP request
	FString URL = BuildAPIURL(ResolvedVoiceID);
	FString RequestBody = BuildRequestBody(Text, ResolvedStability, ResolvedSimilarityBoost);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(URL);
	HttpRequest->SetVerb(TEXT("POST"));
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	HttpRequest->SetHeader(TEXT("xi-api-key"), APIKey);
	HttpRequest->SetHeader(TEXT("Accept"), TEXT("audio/pcm"));
	HttpRequest->SetContentAsString(RequestBody);

	TWeakObjectPtr<UElevenLabsTTSComponent> WeakThis(this);
	HttpRequest->OnProcessRequestComplete().BindLambda(
		[WeakThis](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
		{
			if (!WeakThis.IsValid())
			{
				return;
			}

			if (!bConnectedSuccessfully || !Response.IsValid())
			{
				UE_LOG(LogTemp, Error, TEXT("ElevenLabsTTSComponent: TTS request failed - connection error."));
				return;
			}

			int32 ResponseCode = Response->GetResponseCode();
			if (ResponseCode != 200)
			{
				UE_LOG(LogTemp, Error, TEXT("ElevenLabsTTSComponent: TTS request failed with code %d: %s"),
					ResponseCode, *Response->GetContentAsString());
				return;
			}

			TArray<uint8> AudioBytes = Response->GetContent();
			WeakThis->HandleTTSResponse(true, ResponseCode, AudioBytes);
		}
	);

	HttpRequest->ProcessRequest();
}

void UElevenLabsTTSComponent::StopSpeaking()
{
	if (AudioPlaybackComponent && bIsSpeaking)
	{
		AudioPlaybackComponent->Stop();
		bIsSpeaking = false;
		OnSpeechFinished.Broadcast();
	}

	CurrentSoundWave = nullptr;
}

bool UElevenLabsTTSComponent::IsSpeaking() const
{
	return bIsSpeaking;
}

FString UElevenLabsTTSComponent::BuildAPIURL(const FString& VoiceID) const
{
	return FString::Printf(TEXT("%s/text-to-speech/%s?output_format=%s"),
		*APIBaseURL, *VoiceID, *OutputFormat);
}

FString UElevenLabsTTSComponent::BuildRequestBody(const FString& Text, float Stability, float SimilarityBoost) const
{
	TSharedPtr<FJsonObject> RootObject = MakeShared<FJsonObject>();
	RootObject->SetStringField(TEXT("text"), Text);
	RootObject->SetStringField(TEXT("model_id"), ModelID);

	TSharedPtr<FJsonObject> VoiceSettings = MakeShared<FJsonObject>();
	VoiceSettings->SetNumberField(TEXT("stability"), Stability);
	VoiceSettings->SetNumberField(TEXT("similarity_boost"), SimilarityBoost);
	VoiceSettings->SetNumberField(TEXT("style"), StyleExaggeration);
	VoiceSettings->SetBoolField(TEXT("use_speaker_boost"), true);
	RootObject->SetObjectField(TEXT("voice_settings"), VoiceSettings);

	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(RootObject.ToSharedRef(), Writer);

	return OutputString;
}

void UElevenLabsTTSComponent::HandleTTSResponse(bool bWasSuccessful, int32 ResponseCode, const TArray<uint8>& AudioBytes)
{
	if (!bWasSuccessful || AudioBytes.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("ElevenLabsTTSComponent: No audio data received."));
		return;
	}

	// Dispatch everything to the game thread — both the delegate broadcast and audio playback
	TWeakObjectPtr<UElevenLabsTTSComponent> WeakThis(this);
	AsyncTask(ENamedThreads::GameThread, [WeakThis, AudioBytes]()
	{
		if (!WeakThis.IsValid())
		{
			return;
		}

		// Broadcast raw audio data for lip sync (PCM 24000 Hz, 16-bit mono)
		WeakThis->OnTTSAudioDataReceived.Broadcast(AudioBytes, 24000);

		// Play the audio
		WeakThis->PlayAudioFromPCM(AudioBytes);
	});
}

void UElevenLabsTTSComponent::PlayAudioFromPCM(const TArray<uint8>& PCMData)
{
	if (!AudioPlaybackComponent)
	{
		return;
	}

	// Create procedural sound wave
	CurrentSoundWave = NewObject<USoundWaveProcedural>(this);
	if (!CurrentSoundWave)
	{
		UE_LOG(LogTemp, Error, TEXT("ElevenLabsTTSComponent: Failed to create USoundWaveProcedural."));
		return;
	}

	// Configure for PCM 24000 Hz, 16-bit, mono
	CurrentSoundWave->SetSampleRate(24000);
	CurrentSoundWave->NumChannels = 1;
	CurrentSoundWave->Duration = static_cast<float>(PCMData.Num()) / (24000.0f * 2.0f); // 16-bit = 2 bytes per sample
	CurrentSoundWave->SoundGroup = SOUNDGROUP_Voice;
	CurrentSoundWave->bLooping = false;

	// Queue the PCM data
	CurrentSoundWave->QueueAudio(PCMData.GetData(), PCMData.Num());

	// Play through the audio component
	AudioPlaybackComponent->SetSound(CurrentSoundWave);
	AudioPlaybackComponent->Play();

	bIsSpeaking = true;
	OnSpeechStarted.Broadcast();

	UE_LOG(LogTemp, Verbose, TEXT("ElevenLabsTTSComponent: Playing TTS audio (%.2fs, %d bytes)."),
		CurrentSoundWave->Duration, PCMData.Num());
}

void UElevenLabsTTSComponent::OnAudioPlaybackFinished()
{
	bIsSpeaking = false;
	CurrentSoundWave = nullptr;
	OnSpeechFinished.Broadcast();

	UE_LOG(LogTemp, Verbose, TEXT("ElevenLabsTTSComponent: Speech playback finished."));
}
