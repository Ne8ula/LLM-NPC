#include "ElevenLabsTTSComponent.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/Base64.h"
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
	HttpRequest->SetHeader(TEXT("Accept"), TEXT("application/json"));
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
				// Broadcast error so lip sync, thinking face, and body motion
				// can reset state instead of latching on forever. Dispatch to
				// game thread: OnSpeechError is a dynamic multicast delegate
				// and must be invoked on the game thread.
				AsyncTask(ENamedThreads::GameThread, [WeakThis]()
				{
					if (WeakThis.IsValid())
					{
						WeakThis->OnSpeechError.Broadcast(-3, TEXT("connection_error"));
					}
				});
				return;
			}

			int32 ResponseCode = Response->GetResponseCode();
			if (ResponseCode != 200)
			{
				const FString ResponseBody = Response->GetContentAsString();
				UE_LOG(LogTemp, Error, TEXT("ElevenLabsTTSComponent: TTS request failed with code %d: %s"),
					ResponseCode, *ResponseBody);
				AsyncTask(ENamedThreads::GameThread, [WeakThis, ResponseCode, ResponseBody]()
				{
					if (WeakThis.IsValid())
					{
						WeakThis->OnSpeechError.Broadcast(ResponseCode, ResponseBody);
					}
				});
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
		PlaybackStartWallTime = 0.0;
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
	// /with-timestamps returns a JSON body containing base64 audio plus
	// character-level alignment used by the lip sync system.
	return FString::Printf(TEXT("%s/text-to-speech/%s/with-timestamps?output_format=%s"),
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
	// Local helper: broadcast an internal error on the game thread so
	// subscribers (lip sync / thinking face / body motion) recover cleanly.
	TWeakObjectPtr<UElevenLabsTTSComponent> WeakSelf(this);
	auto BroadcastInternalError = [WeakSelf](int32 Code, const FString& Reason)
	{
		AsyncTask(ENamedThreads::GameThread, [WeakSelf, Code, Reason]()
		{
			if (WeakSelf.IsValid())
			{
				WeakSelf->OnSpeechError.Broadcast(Code, Reason);
			}
		});
	};

	if (!bWasSuccessful || AudioBytes.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("ElevenLabsTTSComponent: No response body received."));
		BroadcastInternalError(-1, TEXT("empty_response"));
		return;
	}

	// Response body is JSON: { audio_base64, alignment, normalized_alignment }.
	// Copy into a null-terminated buffer before converting — the HTTP body
	// is not null-terminated and the alignment field may contain UTF-8.
	TArray<uint8> NullTerminated = AudioBytes;
	NullTerminated.Add(0);
	const FString JsonBody(UTF8_TO_TCHAR(reinterpret_cast<const ANSICHAR*>(NullTerminated.GetData())));

	TArray<uint8> PCMBytes;
	FString Characters;
	TArray<float> StartTimesSec;
	TArray<float> DurationsSec;

	if (!ParseTimestampedResponse(JsonBody, PCMBytes, Characters, StartTimesSec, DurationsSec))
	{
		UE_LOG(LogTemp, Error, TEXT("ElevenLabsTTSComponent: Failed to parse /with-timestamps response."));
		BroadcastInternalError(-1, TEXT("parse_failure"));
		return;
	}

	if (PCMBytes.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("ElevenLabsTTSComponent: Response contained no audio data."));
		BroadcastInternalError(-2, TEXT("no_audio"));
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("ElevenLabsTTSComponent: Received %d PCM bytes, %d aligned chars."),
		PCMBytes.Num(), Characters.Len());

	// Dispatch to the game thread: broadcast alignment first (so lip sync can build
	// its schedule before the clock starts), then raw audio, then play.
	TWeakObjectPtr<UElevenLabsTTSComponent> WeakThis(this);
	AsyncTask(ENamedThreads::GameThread,
		[WeakThis, PCMBytes = MoveTemp(PCMBytes), Characters, StartTimesSec, DurationsSec]()
	{
		if (!WeakThis.IsValid())
		{
			return;
		}

		// Alignment first — lip sync subscribers use this to build the viseme schedule.
		if (Characters.Len() > 0)
		{
			WeakThis->OnTTSAlignmentReceived.Broadcast(Characters, StartTimesSec, DurationsSec);
		}

		// Legacy raw-audio delegate (PCM 24000 Hz, 16-bit mono).
		WeakThis->OnTTSAudioDataReceived.Broadcast(PCMBytes, 24000);

		// Play the audio.
		WeakThis->PlayAudioFromPCM(PCMBytes);
	});
}

bool UElevenLabsTTSComponent::ParseTimestampedResponse(
	const FString& JsonBody,
	TArray<uint8>& OutPCM,
	FString& OutCharacters,
	TArray<float>& OutStartTimesSec,
	TArray<float>& OutDurationsSec) const
{
	OutPCM.Reset();
	OutCharacters.Reset();
	OutStartTimesSec.Reset();
	OutDurationsSec.Reset();

	TSharedPtr<FJsonObject> Root;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonBody);
	if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
	{
		return false;
	}

	// audio_base64 — required.
	FString AudioBase64;
	if (!Root->TryGetStringField(TEXT("audio_base64"), AudioBase64) || AudioBase64.IsEmpty())
	{
		return false;
	}
	if (!FBase64::Decode(AudioBase64, OutPCM))
	{
		return false;
	}

	// Alignment — prefer normalized_alignment, fall back to alignment. Both optional.
	const TSharedPtr<FJsonObject>* AlignmentObj = nullptr;
	if (!Root->TryGetObjectField(TEXT("normalized_alignment"), AlignmentObj) || !AlignmentObj || !AlignmentObj->IsValid())
	{
		if (!Root->TryGetObjectField(TEXT("alignment"), AlignmentObj) || !AlignmentObj || !AlignmentObj->IsValid())
		{
			// Audio still valid, just no alignment — return true so playback proceeds.
			return true;
		}
	}

	const TArray<TSharedPtr<FJsonValue>>* CharsArr = nullptr;
	const TArray<TSharedPtr<FJsonValue>>* StartArr = nullptr;
	const TArray<TSharedPtr<FJsonValue>>* EndArr = nullptr;

	(*AlignmentObj)->TryGetArrayField(TEXT("characters"), CharsArr);
	(*AlignmentObj)->TryGetArrayField(TEXT("character_start_times_seconds"), StartArr);
	(*AlignmentObj)->TryGetArrayField(TEXT("character_end_times_seconds"), EndArr);

	if (!CharsArr || !StartArr || !EndArr)
	{
		return true; // audio OK, alignment missing
	}

	const int32 Count = CharsArr->Num();
	if (Count == 0 || StartArr->Num() != Count || EndArr->Num() != Count)
	{
		return true;
	}

	OutCharacters.Reserve(Count);
	OutStartTimesSec.Reserve(Count);
	OutDurationsSec.Reserve(Count);

	for (int32 i = 0; i < Count; ++i)
	{
		FString CharStr = (*CharsArr)[i]->AsString();
		const TCHAR C = CharStr.Len() > 0 ? CharStr[0] : TEXT(' ');
		const float Start = static_cast<float>((*StartArr)[i]->AsNumber());
		const float End   = static_cast<float>((*EndArr)[i]->AsNumber());
		const float Dur   = FMath::Max(0.0f, End - Start);

		OutCharacters.AppendChar(C);
		OutStartTimesSec.Add(Start);
		OutDurationsSec.Add(Dur);
	}

	return true;
}

float UElevenLabsTTSComponent::GetPlaybackElapsedSeconds() const
{
	if (!bIsSpeaking || PlaybackStartWallTime <= 0.0)
	{
		return 0.0f;
	}
	return static_cast<float>(FPlatformTime::Seconds() - PlaybackStartWallTime);
}

void UElevenLabsTTSComponent::PlayAudioFromPCM(const TArray<uint8>& PCMData)
{
	if (!AudioPlaybackComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("ElevenLabsTTSComponent: PlayAudioFromPCM — no AudioPlaybackComponent."));
		OnSpeechError.Broadcast(-2, TEXT("audio_create_failure"));
		return;
	}

	// Create procedural sound wave
	CurrentSoundWave = NewObject<USoundWaveProcedural>(this);
	if (!CurrentSoundWave)
	{
		UE_LOG(LogTemp, Error, TEXT("ElevenLabsTTSComponent: Failed to create USoundWaveProcedural."));
		OnSpeechError.Broadcast(-2, TEXT("audio_create_failure"));
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

	// Capture wall-clock start time for GetPlaybackElapsedSeconds().
	// USoundWaveProcedural does not expose a reliable playback cursor, so the
	// lip sync sampler reads elapsed time via this wall-clock value instead.
	PlaybackStartWallTime = FPlatformTime::Seconds();

	bIsSpeaking = true;
	OnSpeechStarted.Broadcast();

	UE_LOG(LogTemp, Verbose, TEXT("ElevenLabsTTSComponent: Playing TTS audio (%.2fs, %d bytes)."),
		CurrentSoundWave->Duration, PCMData.Num());
}

void UElevenLabsTTSComponent::OnAudioPlaybackFinished()
{
	bIsSpeaking = false;
	PlaybackStartWallTime = 0.0;
	CurrentSoundWave = nullptr;
	OnSpeechFinished.Broadcast();

	UE_LOG(LogTemp, Verbose, TEXT("ElevenLabsTTSComponent: Speech playback finished."));
}
