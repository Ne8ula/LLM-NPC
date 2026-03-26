#include "WhisperSTTComponent.h"
#include "AudioCaptureComponent.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

UWhisperSTTComponent::UWhisperSTTComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SubsystemName = TEXT("VoiceInput");
}

void UWhisperSTTComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWhisperSTTComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (bIsRecording)
	{
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

	UE_LOG(LogTemp, Log, TEXT("WhisperSTT: OpenAI API key loaded. Voice input available."));
	UE_LOG(LogTemp, Log, TEXT("WhisperSTT: Hold V to record, release to transcribe."));
	bIsAvailable = true;
	bMicAvailable = true;
}

void UWhisperSTTComponent::ShutdownSubsystem()
{
	bIsRecording = false;
	RecordedSamples.Empty();
	Super::ShutdownSubsystem();
}

bool UWhisperSTTComponent::IsSubsystemAvailable() const
{
	return bIsAvailable && !OpenAIAPIKey.IsEmpty();
}

void UWhisperSTTComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWhisperSTTComponent::StartRecording()
{
	if (bIsRecording || !bIsAvailable)
	{
		return;
	}

	RecordedSamples.Empty();
	bIsRecording = true;
	OnRecordingStateChanged.Broadcast(true);

	UE_LOG(LogTemp, Log, TEXT("WhisperSTT: Recording started..."));

	// Create audio capture if not exists
	if (!AudioCapture && GetOwner())
	{
		AudioCapture = NewObject<UAudioCaptureComponent>(GetOwner());
		if (AudioCapture)
		{
			AudioCapture->RegisterComponent();
		}
	}

	if (AudioCapture)
	{
		AudioCapture->Start();
	}
}

void UWhisperSTTComponent::StopRecordingAndTranscribe()
{
	if (!bIsRecording)
	{
		return;
	}

	bIsRecording = false;
	OnRecordingStateChanged.Broadcast(false);

	if (AudioCapture)
	{
		AudioCapture->Stop();
	}

	UE_LOG(LogTemp, Log, TEXT("WhisperSTT: Recording stopped. Captured %d samples."), RecordedSamples.Num());

	if (RecordedSamples.Num() < SampleRate / 2)
	{
		UE_LOG(LogTemp, Warning, TEXT("WhisperSTT: Recording too short, ignoring."));
		return;
	}

	// Encode as WAV and send to API
	TArray<uint8> WAVData = EncodeAsWAV(RecordedSamples, SampleRate, 1);
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

	Request->OnProcessRequestComplete().BindLambda(
		[this](FHttpRequestPtr Req, FHttpResponsePtr Resp, bool bSuccess)
		{
			if (!bSuccess || !Resp.IsValid())
			{
				UE_LOG(LogTemp, Error, TEXT("WhisperSTT: HTTP request failed."));
				return;
			}
			OnWhisperResponseReceived(bSuccess, Resp->GetResponseCode(), Resp->GetContentAsString());
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
