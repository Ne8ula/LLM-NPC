#include "WhisperSTTComponent.h"
#include "AudioCapture.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

UWhisperSTTComponent::UWhisperSTTComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SubsystemName = TEXT("VoiceInput");
}

UWhisperSTTComponent::~UWhisperSTTComponent()
{
	// Ensure capture stream is closed before destruction
	if (AudioCapture)
	{
		if (AudioCapture->IsStreamOpen())
		{
			AudioCapture->StopStream();
			AudioCapture->CloseStream();
		}
	}
}

void UWhisperSTTComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWhisperSTTComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (bIsRecording && AudioCapture)
	{
		AudioCapture->StopStream();
		AudioCapture->CloseStream();
		bIsRecording = false;
	}
	Super::EndPlay(EndPlayReason);
}

void UWhisperSTTComponent::InitializeSubsystem()
{
	Super::InitializeSubsystem();

	// Load OpenAI API key from environment
	OpenAIAPIKey = FPlatformMisc::GetEnvironmentVariable(TEXT("OPENAI_API_KEY"));
	if (OpenAIAPIKey.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("WhisperSTT: No OPENAI_API_KEY environment variable found. Voice input disabled."));
		bIsAvailable = false;
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("WhisperSTT: OpenAI API key loaded."));

	// Probe for audio capture devices
	bDeviceAvailable = ProbeAudioDevices();

	if (!bDeviceAvailable)
	{
		UE_LOG(LogTemp, Warning, TEXT("WhisperSTT: No audio capture devices found. Voice input disabled."));
		UE_LOG(LogTemp, Warning, TEXT("WhisperSTT: Ensure a microphone is connected and the AudioCapture plugin is enabled."));
		bIsAvailable = false;
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("WhisperSTT: Voice input available. Hold V to record, release to transcribe."));
	bIsAvailable = true;
}

bool UWhisperSTTComponent::ProbeAudioDevices()
{
	AudioCapture = MakeUnique<Audio::FAudioCapture>();

	TArray<Audio::FCaptureDeviceInfo> Devices;
	AudioCapture->GetCaptureDevicesAvailable(Devices);

	if (Devices.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("WhisperSTT: GetCaptureDevicesAvailable returned 0 devices."));
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("WhisperSTT: Found %d audio capture device(s):"), Devices.Num());
	for (int32 i = 0; i < Devices.Num(); ++i)
	{
		UE_LOG(LogTemp, Log, TEXT("  [%d] %s (Channels: %d, SampleRate: %d)"),
			i, *Devices[i].DeviceName, Devices[i].InputChannels, Devices[i].PreferredSampleRate);
	}

	// Use the default device's sample rate
	DeviceSampleRate = Devices[0].PreferredSampleRate;
	if (DeviceSampleRate <= 0)
	{
		DeviceSampleRate = 44100; // Reasonable fallback
	}

	return true;
}

void UWhisperSTTComponent::ShutdownSubsystem()
{
	if (AudioCapture && AudioCapture->IsStreamOpen())
	{
		AudioCapture->StopStream();
		AudioCapture->CloseStream();
	}
	bIsRecording = false;
	RecordedSamples.Empty();
	Super::ShutdownSubsystem();
}

bool UWhisperSTTComponent::IsSubsystemAvailable() const
{
	return bIsAvailable && !OpenAIAPIKey.IsEmpty() && bDeviceAvailable;
}

void UWhisperSTTComponent::StartRecording()
{
	if (bIsRecording || !bIsAvailable)
	{
		return;
	}

	if (!AudioCapture)
	{
		UE_LOG(LogTemp, Error, TEXT("WhisperSTT: AudioCapture not initialized."));
		return;
	}

	// Close any previous stream
	if (AudioCapture->IsStreamOpen())
	{
		AudioCapture->StopStream();
		AudioCapture->CloseStream();
	}

	{
		FScopeLock Lock(&SamplesLock);
		RecordedSamples.Empty();
		RecordedSamples.Reserve(DeviceSampleRate * 30); // Pre-allocate for up to 30 seconds
	}

	// Open capture stream with sample callback
	Audio::FAudioCaptureDeviceParams Params;
	// Params default to device index 0 (default mic)

	Audio::FOnAudioCaptureFunction OnCapture = [this](const void* InBuffer, int32 NumFrames, int32 InNumChannels, int32 InSampleRate, double StreamTime, bool bOverflow)
	{
		if (!bIsRecording)
		{
			return;
		}

		// Capture actual device sample rate on first callback
		if (DeviceSampleRate != InSampleRate && InSampleRate > 0)
		{
			DeviceSampleRate = InSampleRate;
		}

		const float* InAudio = static_cast<const float*>(InBuffer);

		FScopeLock Lock(&SamplesLock);

		// Mix down to mono and append
		for (int32 Frame = 0; Frame < NumFrames; ++Frame)
		{
			float Sample = 0.0f;
			for (int32 Ch = 0; Ch < InNumChannels; ++Ch)
			{
				Sample += InAudio[Frame * InNumChannels + Ch];
			}
			Sample /= FMath::Max(InNumChannels, 1);
			RecordedSamples.Add(Sample);
		}
	};

	// Third param is NumFramesDesired per callback (buffer size), not sample rate
	bool bOpened = AudioCapture->OpenAudioCaptureStream(Params, MoveTemp(OnCapture), 1024);
	if (!bOpened)
	{
		UE_LOG(LogTemp, Error, TEXT("WhisperSTT: Failed to open audio capture stream."));
		return;
	}

	bool bStarted = AudioCapture->StartStream();
	if (!bStarted)
	{
		UE_LOG(LogTemp, Error, TEXT("WhisperSTT: Failed to start audio capture stream."));
		AudioCapture->CloseStream();
		return;
	}

	bIsRecording = true;
	OnRecordingStateChanged.Broadcast(true);
	UE_LOG(LogTemp, Log, TEXT("WhisperSTT: Recording started (device sample rate: %d Hz)..."), DeviceSampleRate);
}

void UWhisperSTTComponent::StopRecordingAndTranscribe()
{
	if (!bIsRecording)
	{
		return;
	}

	bIsRecording = false;
	OnRecordingStateChanged.Broadcast(false);

	if (AudioCapture && AudioCapture->IsStreamOpen())
	{
		AudioCapture->StopStream();
		AudioCapture->CloseStream();
	}

	// Copy samples under lock
	TArray<float> CapturedSamples;
	{
		FScopeLock Lock(&SamplesLock);
		CapturedSamples = MoveTemp(RecordedSamples);
		RecordedSamples.Empty();
	}

	UE_LOG(LogTemp, Log, TEXT("WhisperSTT: Recording stopped. Captured %d samples (%.1f seconds at %d Hz)."),
		CapturedSamples.Num(),
		CapturedSamples.Num() > 0 ? (float)CapturedSamples.Num() / DeviceSampleRate : 0.0f,
		DeviceSampleRate);

	// Need at least ~0.5 seconds of audio
	int32 MinSamples = DeviceSampleRate / 2;
	if (CapturedSamples.Num() < MinSamples)
	{
		UE_LOG(LogTemp, Warning, TEXT("WhisperSTT: Recording too short (%d samples, need %d), ignoring."),
			CapturedSamples.Num(), MinSamples);
		return;
	}

	// Resample to 16kHz if device captures at a different rate (Whisper expects 16kHz)
	TArray<float> FinalSamples;
	if (DeviceSampleRate != SampleRate && DeviceSampleRate > 0)
	{
		float Ratio = (float)SampleRate / (float)DeviceSampleRate;
		int32 OutputLen = FMath::CeilToInt(CapturedSamples.Num() * Ratio);
		FinalSamples.SetNumUninitialized(OutputLen);

		for (int32 i = 0; i < OutputLen; ++i)
		{
			float SrcIndex = (float)i / Ratio;
			int32 Idx0 = FMath::FloorToInt(SrcIndex);
			int32 Idx1 = FMath::Min(Idx0 + 1, CapturedSamples.Num() - 1);
			float Frac = SrcIndex - (float)Idx0;
			FinalSamples[i] = FMath::Lerp(CapturedSamples[Idx0], CapturedSamples[Idx1], Frac);
		}

		UE_LOG(LogTemp, Log, TEXT("WhisperSTT: Resampled %d -> %d samples (%d Hz -> %d Hz)."),
			CapturedSamples.Num(), FinalSamples.Num(), DeviceSampleRate, SampleRate);
	}
	else
	{
		FinalSamples = MoveTemp(CapturedSamples);
	}

	// Encode as WAV and send to API
	TArray<uint8> WAVData = EncodeAsWAV(FinalSamples, SampleRate, 1);
	SendToWhisperAPI(WAVData);
}

TArray<uint8> UWhisperSTTComponent::EncodeAsWAV(const TArray<float>& AudioData, int32 InSampleRate, int32 NumChannels) const
{
	TArray<uint8> WAVBytes;

	const int32 BitsPerSample = 16;
	const int32 BytesPerSample = BitsPerSample / 8;
	const int32 DataSize = AudioData.Num() * BytesPerSample;
	const int32 FileSize = 44 + DataSize;

	WAVBytes.SetNumUninitialized(FileSize);
	uint8* Ptr = WAVBytes.GetData();

	// RIFF header
	FMemory::Memcpy(Ptr, "RIFF", 4); Ptr += 4;
	int32 ChunkSize = FileSize - 8;
	FMemory::Memcpy(Ptr, &ChunkSize, 4); Ptr += 4;
	FMemory::Memcpy(Ptr, "WAVE", 4); Ptr += 4;

	// fmt sub-chunk
	FMemory::Memcpy(Ptr, "fmt ", 4); Ptr += 4;
	int32 SubChunk1Size = 16;
	FMemory::Memcpy(Ptr, &SubChunk1Size, 4); Ptr += 4;
	int16 AudioFormat = 1;
	FMemory::Memcpy(Ptr, &AudioFormat, 2); Ptr += 2;
	int16 Channels = (int16)NumChannels;
	FMemory::Memcpy(Ptr, &Channels, 2); Ptr += 2;
	FMemory::Memcpy(Ptr, &InSampleRate, 4); Ptr += 4;
	int32 ByteRate = InSampleRate * NumChannels * BytesPerSample;
	FMemory::Memcpy(Ptr, &ByteRate, 4); Ptr += 4;
	int16 BlockAlign = NumChannels * BytesPerSample;
	FMemory::Memcpy(Ptr, &BlockAlign, 2); Ptr += 2;
	int16 BPS = BitsPerSample;
	FMemory::Memcpy(Ptr, &BPS, 2); Ptr += 2;

	// data sub-chunk
	FMemory::Memcpy(Ptr, "data", 4); Ptr += 4;
	FMemory::Memcpy(Ptr, &DataSize, 4); Ptr += 4;

	// Convert float to 16-bit PCM
	for (int32 i = 0; i < AudioData.Num(); ++i)
	{
		float Sample = FMath::Clamp(AudioData[i], -1.0f, 1.0f);
		int16 PCMSample = (int16)(Sample * 32767.0f);
		FMemory::Memcpy(Ptr, &PCMSample, 2);
		Ptr += 2;
	}

	return WAVBytes;
}

void UWhisperSTTComponent::SendToWhisperAPI(const TArray<uint8>& WAVData)
{
	UE_LOG(LogTemp, Log, TEXT("WhisperSTT: Sending %d bytes to OpenAI Whisper API..."), WAVData.Num());

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(TEXT("https://api.openai.com/v1/audio/transcriptions"));
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *OpenAIAPIKey));

	// Build multipart form data
	FString Boundary = TEXT("----UE5WhisperBoundary");
	Request->SetHeader(TEXT("Content-Type"), FString::Printf(TEXT("multipart/form-data; boundary=%s"), *Boundary));

	TArray<uint8> PostData;

	auto AppendString = [&PostData](const FString& Str)
	{
		FTCHARToUTF8 UTF8(*Str);
		PostData.Append((const uint8*)UTF8.Get(), UTF8.Length());
	};

	// File field
	AppendString(FString::Printf(TEXT("--%s\r\n"), *Boundary));
	AppendString(TEXT("Content-Disposition: form-data; name=\"file\"; filename=\"audio.wav\"\r\n"));
	AppendString(TEXT("Content-Type: audio/wav\r\n\r\n"));
	PostData.Append(WAVData);
	AppendString(TEXT("\r\n"));

	// Model field
	AppendString(FString::Printf(TEXT("--%s\r\n"), *Boundary));
	AppendString(TEXT("Content-Disposition: form-data; name=\"model\"\r\n\r\n"));
	AppendString(TEXT("whisper-1\r\n"));

	// Language field
	AppendString(FString::Printf(TEXT("--%s\r\n"), *Boundary));
	AppendString(TEXT("Content-Disposition: form-data; name=\"language\"\r\n\r\n"));
	AppendString(TEXT("en\r\n"));

	// Closing boundary
	AppendString(FString::Printf(TEXT("--%s--\r\n"), *Boundary));

	Request->SetContent(PostData);

	TWeakObjectPtr<UWhisperSTTComponent> WeakThis(this);
	Request->OnProcessRequestComplete().BindLambda(
		[WeakThis](FHttpRequestPtr Req, FHttpResponsePtr Resp, bool bSuccess)
		{
			if (!WeakThis.IsValid())
			{
				return;
			}

			if (!bSuccess || !Resp.IsValid())
			{
				UE_LOG(LogTemp, Error, TEXT("WhisperSTT: HTTP request failed."));
				return;
			}
			WeakThis->OnWhisperResponseReceived(bSuccess, Resp->GetResponseCode(), Resp->GetContentAsString());
		}
	);

	Request->ProcessRequest();
}

void UWhisperSTTComponent::OnWhisperResponseReceived(bool bWasSuccessful, int32 ResponseCode, const FString& ResponseBody)
{
	if (ResponseCode != 200)
	{
		UE_LOG(LogTemp, Error, TEXT("WhisperSTT: API error %d: %s"), ResponseCode, *ResponseBody);
		return;
	}

	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseBody);

	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("WhisperSTT: Failed to parse response JSON."));
		return;
	}

	FString Transcript;
	if (JsonObject->TryGetStringField(TEXT("text"), Transcript))
	{
		Transcript = Transcript.TrimStartAndEnd();
		if (!Transcript.IsEmpty())
		{
			UE_LOG(LogTemp, Log, TEXT("WhisperSTT: Transcript: \"%s\""), *Transcript);
			OnTranscriptReady.Broadcast(Transcript);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("WhisperSTT: Empty transcript (silence)."));
		}
	}
}
