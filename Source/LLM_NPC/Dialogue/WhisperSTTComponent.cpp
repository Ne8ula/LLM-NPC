#include "WhisperSTTComponent.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

// Windows multimedia API for direct microphone capture
#include "Windows/AllowWindowsPlatformTypes.h"
#include <windows.h>
#include <mmsystem.h>
#include "Windows/HideWindowsPlatformTypes.h"

// ----------------------------------------------------------------------------
// waveIn callback — runs on a system audio thread
// ----------------------------------------------------------------------------
static void CALLBACK WaveInCallback(HWAVEIN hWaveIn, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
	if (uMsg != WIM_DATA)
	{
		return;
	}

	UWhisperSTTComponent* Comp = reinterpret_cast<UWhisperSTTComponent*>(dwInstance);
	WAVEHDR* Header = reinterpret_cast<WAVEHDR*>(dwParam1);

	if (!Comp || !Header || Header->dwBytesRecorded == 0)
	{
		return;
	}

	if (Comp->IsRecording())
	{
		// Append recorded bytes to the component's buffer (thread-safe via internal lock)
		// We access RecordedPCM and PCMLock through a static friend-like pattern
		// by calling a small helper. But since RecordedPCM/PCMLock are private,
		// we use the publicly-visible IsRecording() plus a direct memory append.
		//
		// NOTE: We store the lock/buffer pointers in the WAVEHDR::dwUser field
		// to avoid needing friendship.
		struct FBufferContext
		{
			TArray<uint8>* PCMPtr;
			FCriticalSection* LockPtr;
		};
		FBufferContext* Ctx = reinterpret_cast<FBufferContext*>(Header->dwUser);
		if (Ctx && Ctx->PCMPtr && Ctx->LockPtr)
		{
			FScopeLock Lock(Ctx->LockPtr);
			Ctx->PCMPtr->Append(reinterpret_cast<const uint8*>(Header->lpData), Header->dwBytesRecorded);
		}

		// Re-add the buffer for continued recording
		waveInAddBuffer(hWaveIn, Header, sizeof(WAVEHDR));
	}
}

// Small context struct stored in WAVEHDR::dwUser
struct FWaveInBufferContext
{
	TArray<uint8>* PCMPtr;
	FCriticalSection* LockPtr;
};

// ----------------------------------------------------------------------------

UWhisperSTTComponent::UWhisperSTTComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SubsystemName = TEXT("VoiceInput");
}

UWhisperSTTComponent::~UWhisperSTTComponent()
{
	if (WaveInHandle)
	{
		waveInStop(reinterpret_cast<HWAVEIN>(WaveInHandle));
		waveInReset(reinterpret_cast<HWAVEIN>(WaveInHandle));

		WAVEHDR* Headers = reinterpret_cast<WAVEHDR*>(WaveHeaders);
		if (Headers)
		{
			for (int32 i = 0; i < NumBuffers; ++i)
			{
				waveInUnprepareHeader(reinterpret_cast<HWAVEIN>(WaveInHandle), &Headers[i], sizeof(WAVEHDR));
				if (Headers[i].dwUser)
				{
					delete reinterpret_cast<FWaveInBufferContext*>(Headers[i].dwUser);
				}
			}
			delete[] Headers;
		}

		waveInClose(reinterpret_cast<HWAVEIN>(WaveInHandle));
		WaveInHandle = nullptr;
	}

	if (BufferMemory)
	{
		delete[] BufferMemory;
		BufferMemory = nullptr;
	}
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

	// Check if any recording devices exist
	UINT NumDevices = waveInGetNumDevs();
	if (NumDevices == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("WhisperSTT: No microphone devices found. Voice input disabled."));
		bIsAvailable = false;
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("WhisperSTT: Found %d microphone device(s)."), NumDevices);

	// Log device names
	for (UINT i = 0; i < NumDevices; ++i)
	{
		WAVEINCAPS caps;
		if (waveInGetDevCaps(i, &caps, sizeof(caps)) == MMSYSERR_NOERROR)
		{
			UE_LOG(LogTemp, Log, TEXT("WhisperSTT:   [%d] %s"), i, caps.szPname);
		}
	}

	UE_LOG(LogTemp, Log, TEXT("WhisperSTT: OpenAI API key loaded. Voice input available."));
	UE_LOG(LogTemp, Log, TEXT("WhisperSTT: Hold V to record, release to transcribe."));
	bIsAvailable = true;
}

void UWhisperSTTComponent::ShutdownSubsystem()
{
	if (bIsRecording)
	{
		bIsRecording = false;
		if (WaveInHandle)
		{
			waveInStop(reinterpret_cast<HWAVEIN>(WaveInHandle));
			waveInReset(reinterpret_cast<HWAVEIN>(WaveInHandle));
		}
	}
	RecordedPCM.Empty();
	Super::ShutdownSubsystem();
}

bool UWhisperSTTComponent::IsSubsystemAvailable() const
{
	return bIsAvailable && !OpenAIAPIKey.IsEmpty();
}

void UWhisperSTTComponent::StartRecording()
{
	if (bIsRecording || !bIsAvailable)
	{
		return;
	}

	// Clear previous recording
	{
		FScopeLock Lock(&PCMLock);
		RecordedPCM.Empty();
		RecordedPCM.Reserve(SampleRate * sizeof(int16) * 30); // 30 seconds max
	}

	// Set up wave format: 16-bit mono PCM at 16kHz
	WAVEFORMATEX wfx = {};
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nChannels = 1;
	wfx.nSamplesPerSec = SampleRate;
	wfx.wBitsPerSample = 16;
	wfx.nBlockAlign = wfx.nChannels * wfx.wBitsPerSample / 8;
	wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;

	// Open default recording device
	HWAVEIN hWaveIn = nullptr;
	MMRESULT result = waveInOpen(
		&hWaveIn,
		WAVE_MAPPER,
		&wfx,
		reinterpret_cast<DWORD_PTR>(&WaveInCallback),
		reinterpret_cast<DWORD_PTR>(this),
		CALLBACK_FUNCTION
	);

	if (result != MMSYSERR_NOERROR)
	{
		UE_LOG(LogTemp, Error, TEXT("WhisperSTT: waveInOpen failed with error %d."), result);
		return;
	}

	WaveInHandle = hWaveIn;

	// Allocate buffers
	BufferMemory = new uint8[BufferSizeBytes * NumBuffers];
	FMemory::Memzero(BufferMemory, BufferSizeBytes * NumBuffers);

	WAVEHDR* Headers = new WAVEHDR[NumBuffers];
	FMemory::Memzero(Headers, sizeof(WAVEHDR) * NumBuffers);
	WaveHeaders = Headers;

	for (int32 i = 0; i < NumBuffers; ++i)
	{
		// Create context for this buffer
		FWaveInBufferContext* Ctx = new FWaveInBufferContext();
		Ctx->PCMPtr = &RecordedPCM;
		Ctx->LockPtr = &PCMLock;

		Headers[i].lpData = reinterpret_cast<LPSTR>(BufferMemory + i * BufferSizeBytes);
		Headers[i].dwBufferLength = BufferSizeBytes;
		Headers[i].dwUser = reinterpret_cast<DWORD_PTR>(Ctx);

		waveInPrepareHeader(hWaveIn, &Headers[i], sizeof(WAVEHDR));
		waveInAddBuffer(hWaveIn, &Headers[i], sizeof(WAVEHDR));
	}

	// Start recording
	result = waveInStart(hWaveIn);
	if (result != MMSYSERR_NOERROR)
	{
		UE_LOG(LogTemp, Error, TEXT("WhisperSTT: waveInStart failed with error %d."), result);
		waveInClose(hWaveIn);
		WaveInHandle = nullptr;
		delete[] Headers;
		WaveHeaders = nullptr;
		delete[] BufferMemory;
		BufferMemory = nullptr;
		return;
	}

	bIsRecording = true;
	OnRecordingStateChanged.Broadcast(true);
	UE_LOG(LogTemp, Log, TEXT("WhisperSTT: Recording started (16kHz mono 16-bit via Windows waveIn)..."));
}

void UWhisperSTTComponent::StopRecordingAndTranscribe()
{
	if (!bIsRecording)
	{
		return;
	}

	bIsRecording = false;
	OnRecordingStateChanged.Broadcast(false);

	HWAVEIN hWaveIn = reinterpret_cast<HWAVEIN>(WaveInHandle);

	// Stop and reset the device (this will flush pending buffers)
	waveInStop(hWaveIn);
	waveInReset(hWaveIn);

	// Unprepare headers and clean up
	WAVEHDR* Headers = reinterpret_cast<WAVEHDR*>(WaveHeaders);
	if (Headers)
	{
		for (int32 i = 0; i < NumBuffers; ++i)
		{
			waveInUnprepareHeader(hWaveIn, &Headers[i], sizeof(WAVEHDR));
			if (Headers[i].dwUser)
			{
				delete reinterpret_cast<FWaveInBufferContext*>(Headers[i].dwUser);
			}
		}
		delete[] Headers;
		WaveHeaders = nullptr;
	}

	waveInClose(hWaveIn);
	WaveInHandle = nullptr;

	if (BufferMemory)
	{
		delete[] BufferMemory;
		BufferMemory = nullptr;
	}

	// Copy PCM data under lock
	TArray<uint8> CapturedPCM;
	{
		FScopeLock Lock(&PCMLock);
		CapturedPCM = MoveTemp(RecordedPCM);
		RecordedPCM.Empty();
	}

	float DurationSec = (float)CapturedPCM.Num() / (SampleRate * sizeof(int16));
	UE_LOG(LogTemp, Log, TEXT("WhisperSTT: Recording stopped. Captured %d bytes (%.1f seconds)."),
		CapturedPCM.Num(), DurationSec);

	// Need at least ~0.5 seconds
	int32 MinBytes = SampleRate * sizeof(int16) / 2;
	if (CapturedPCM.Num() < MinBytes)
	{
		UE_LOG(LogTemp, Warning, TEXT("WhisperSTT: Recording too short, ignoring."));
		return;
	}

	// PCM is already 16-bit 16kHz mono — just add WAV header
	TArray<uint8> WAVData = EncodeAsWAV(CapturedPCM, SampleRate, 1, 16);
	SendToWhisperAPI(WAVData);
}

TArray<uint8> UWhisperSTTComponent::EncodeAsWAV(const TArray<uint8>& PCMData, int32 InSampleRate, int32 NumChannels, int32 BitsPerSample) const
{
	TArray<uint8> WAVBytes;

	const int32 DataSize = PCMData.Num();
	const int32 FileSize = 44 + DataSize;
	const int32 BytesPerSample = BitsPerSample / 8;

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
	int16 AudioFormat = 1; // PCM
	FMemory::Memcpy(Ptr, &AudioFormat, 2); Ptr += 2;
	int16 Channels = (int16)NumChannels;
	FMemory::Memcpy(Ptr, &Channels, 2); Ptr += 2;
	FMemory::Memcpy(Ptr, &InSampleRate, 4); Ptr += 4;
	int32 ByteRate = InSampleRate * NumChannels * BytesPerSample;
	FMemory::Memcpy(Ptr, &ByteRate, 4); Ptr += 4;
	int16 BlockAlign = NumChannels * BytesPerSample;
	FMemory::Memcpy(Ptr, &BlockAlign, 2); Ptr += 2;
	int16 BPS = (int16)BitsPerSample;
	FMemory::Memcpy(Ptr, &BPS, 2); Ptr += 2;

	// data sub-chunk
	FMemory::Memcpy(Ptr, "data", 4); Ptr += 4;
	FMemory::Memcpy(Ptr, &DataSize, 4); Ptr += 4;

	// PCM data is already in the right format — copy directly
	FMemory::Memcpy(Ptr, PCMData.GetData(), DataSize);

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
