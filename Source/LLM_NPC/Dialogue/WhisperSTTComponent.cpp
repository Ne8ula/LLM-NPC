#include "WhisperSTTComponent.h"
#include "AudioCaptureComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/World.h"

#if WITH_WHISPER
#include "whisper.h"
#endif

// =============================================================================
// FWhisperInferenceWorker
// =============================================================================

FWhisperInferenceWorker::FWhisperInferenceWorker()
{
	WorkAvailableEvent = FPlatformProcess::GetSynchEventFromPool(false);
}

FWhisperInferenceWorker::~FWhisperInferenceWorker()
{
#if WITH_WHISPER
	if (WhisperContext)
	{
		whisper_free(static_cast<whisper_context*>(WhisperContext));
		WhisperContext = nullptr;
	}
#endif

	if (WorkAvailableEvent)
	{
		FPlatformProcess::ReturnSynchEventToPool(WorkAvailableEvent);
		WorkAvailableEvent = nullptr;
	}
}

bool FWhisperInferenceWorker::Init()
{
	return WhisperContext != nullptr;
}

uint32 FWhisperInferenceWorker::Run()
{
	while (!bShouldStop)
	{
		// Wait for work to become available
		WorkAvailableEvent->Wait();

		if (bShouldStop)
		{
			break;
		}

		if (!bHasPendingWork)
		{
			continue;
		}

		bIsProcessing = true;

		// Grab the audio data
		TArray<float> AudioData;
		int32 CurrentSampleRate;
		{
			FScopeLock Lock(&DataMutex);
			AudioData = MoveTemp(PendingAudioBuffer);
			CurrentSampleRate = PendingSampleRate;
			bHasPendingWork = false;
		}

		if (AudioData.Num() == 0)
		{
			bIsProcessing = false;
			continue;
		}

#if WITH_WHISPER
		// Configure whisper parameters
		whisper_full_params Params = whisper_full_default_params(WHISPER_SAMPLING_GREEDY);
		Params.language = TCHAR_TO_UTF8(*ModelLanguage);
		Params.n_threads = FMath::Max(1, FPlatformMisc::NumberOfCoresIncludingHyperthreads() / 2);
		Params.print_realtime = false;
		Params.print_progress = false;
		Params.print_timestamps = false;
		Params.single_segment = false;
		Params.no_context = true;

		// Run inference
		int Result = whisper_full(
			static_cast<whisper_context*>(WhisperContext),
			Params,
			AudioData.GetData(),
			AudioData.Num()
		);

		if (Result == 0)
		{
			FString FullTranscript;
			int32 NumSegments = whisper_full_n_segments(static_cast<whisper_context*>(WhisperContext));
			for (int32 i = 0; i < NumSegments; ++i)
			{
				const char* SegmentText = whisper_full_get_segment_text(static_cast<whisper_context*>(WhisperContext), i);
				if (SegmentText)
				{
					FullTranscript += UTF8_TO_TCHAR(SegmentText);
				}
			}

			FullTranscript.TrimStartAndEndInline();

			if (!FullTranscript.IsEmpty())
			{
				FScopeLock Lock(&DataMutex);
				TranscriptResult = FullTranscript;
				bHasResult = true;
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("WhisperInferenceWorker: Transcription failed with code %d"), Result);
		}
#else
		UE_LOG(LogTemp, Warning, TEXT("WhisperInferenceWorker: whisper.cpp not available (WITH_WHISPER=0)."));
#endif

		bIsProcessing = false;
	}

	return 0;
}

void FWhisperInferenceWorker::Stop()
{
	bShouldStop = true;
	if (WorkAvailableEvent)
	{
		WorkAvailableEvent->Trigger();
	}
}

void FWhisperInferenceWorker::Exit()
{
}

bool FWhisperInferenceWorker::LoadModel(const FString& ModelPath, const FString& InLanguage)
{
#if WITH_WHISPER
	ModelLanguage = InLanguage;

	FString FullPath = FPaths::Combine(FPaths::ProjectContentDir(), ModelPath);
	if (!FPaths::FileExists(FullPath))
	{
		UE_LOG(LogTemp, Error, TEXT("WhisperInferenceWorker: Model file not found: %s"), *FullPath);
		return false;
	}

	whisper_context_params ContextParams = whisper_context_default_params();
	WhisperContext = whisper_init_from_file_with_params(TCHAR_TO_UTF8(*FullPath), ContextParams);

	if (!WhisperContext)
	{
		UE_LOG(LogTemp, Error, TEXT("WhisperInferenceWorker: Failed to load whisper model from: %s"), *FullPath);
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("WhisperInferenceWorker: Model loaded successfully from: %s"), *FullPath);
	return true;
#else
	UE_LOG(LogTemp, Warning, TEXT("WhisperInferenceWorker: whisper.cpp not available (WITH_WHISPER=0)."));
	return false;
#endif
}

void FWhisperInferenceWorker::QueueAudioBuffer(TArray<float>&& AudioData, int32 InSampleRate)
{
	FScopeLock Lock(&DataMutex);
	PendingAudioBuffer = MoveTemp(AudioData);
	PendingSampleRate = InSampleRate;
	bHasPendingWork = true;
	WorkAvailableEvent->Trigger();
}

bool FWhisperInferenceWorker::HasResult() const
{
	return bHasResult;
}

FString FWhisperInferenceWorker::ConsumeResult()
{
	FScopeLock Lock(&DataMutex);
	FString Result = MoveTemp(TranscriptResult);
	bHasResult = false;
	return Result;
}

bool FWhisperInferenceWorker::IsProcessing() const
{
	return bIsProcessing;
}

// =============================================================================
// UWhisperSTTComponent
// =============================================================================

UWhisperSTTComponent::UWhisperSTTComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	SubsystemName = TEXT("WhisperSTT");
}

void UWhisperSTTComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWhisperSTTComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	StopListening();
	ShutdownSubsystem();
	Super::EndPlay(EndPlayReason);
}

void UWhisperSTTComponent::InitializeSubsystem()
{
	Super::InitializeSubsystem();

	// Create the audio capture component
	AActor* Owner = GetOwner();
	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("WhisperSTTComponent: No owner actor."));
		bIsAvailable = false;
		return;
	}

	AudioCaptureComponent = NewObject<UAudioCaptureComponent>(Owner);
	if (AudioCaptureComponent)
	{
		AudioCaptureComponent->RegisterComponent();
		bMicrophoneAvailable = true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WhisperSTTComponent: Failed to create AudioCaptureComponent. Microphone not available."));
		bMicrophoneAvailable = false;
		bIsAvailable = false;
		return;
	}

	// Initialize the inference worker and load the model
	InferenceWorker = MakeUnique<FWhisperInferenceWorker>();
	bool bModelLoaded = InferenceWorker->LoadModel(WhisperModelPath, Language);

	if (!bModelLoaded)
	{
		UE_LOG(LogTemp, Warning, TEXT("WhisperSTTComponent: Failed to load whisper model. STT will not be available."));
		bIsAvailable = false;
		return;
	}

	// Start the inference thread
	InferenceThread = TUniquePtr<FRunnableThread>(
		FRunnableThread::Create(
			InferenceWorker.Get(),
			TEXT("WhisperInferenceThread"),
			0,
			TPri_BelowNormal
		)
	);

	if (!InferenceThread)
	{
		UE_LOG(LogTemp, Error, TEXT("WhisperSTTComponent: Failed to create inference thread."));
		bIsAvailable = false;
		return;
	}

	bIsAvailable = true;
	bIsInitialized = true;
	UE_LOG(LogTemp, Log, TEXT("WhisperSTTComponent: Initialized successfully."));
}

void UWhisperSTTComponent::ShutdownSubsystem()
{
	StopListening();

	// Shut down the inference thread
	if (InferenceWorker)
	{
		InferenceWorker->Stop();
	}

	if (InferenceThread)
	{
		InferenceThread->WaitForCompletion();
		InferenceThread.Reset();
	}

	InferenceWorker.Reset();

	if (AudioCaptureComponent)
	{
		AudioCaptureComponent->DestroyComponent();
		AudioCaptureComponent = nullptr;
	}

	bMicrophoneAvailable = false;
	bIsAvailable = false;
	bIsInitialized = false;

	Super::ShutdownSubsystem();
}

bool UWhisperSTTComponent::IsSubsystemAvailable() const
{
	return bIsAvailable && bMicrophoneAvailable && InferenceWorker.IsValid();
}

void UWhisperSTTComponent::StartListening()
{
	if (!IsSubsystemAvailable())
	{
		UE_LOG(LogTemp, Warning, TEXT("WhisperSTTComponent: Cannot start listening - subsystem not available."));
		return;
	}

	if (bIsListening)
	{
		return;
	}

	// Start audio capture
	if (AudioCaptureComponent)
	{
		AudioCaptureComponent->Start();
	}

	SpeechBuffer.Empty();
	VADBuffer.Empty();
	SilenceAccumulator = 0.0f;
	SpeechAccumulator = 0.0f;
	bIsSpeaking = false;
	bIsListening = true;

	SetComponentTickEnabled(true);

	UE_LOG(LogTemp, Log, TEXT("WhisperSTTComponent: Started listening."));
}

void UWhisperSTTComponent::StopListening()
{
	if (!bIsListening)
	{
		return;
	}

	// If we were speaking, submit whatever we have
	if (bIsSpeaking && SpeechBuffer.Num() > 0)
	{
		SubmitSpeechForTranscription();
	}

	if (AudioCaptureComponent)
	{
		AudioCaptureComponent->Stop();
	}

	bIsListening = false;
	bIsSpeaking = false;
	SetComponentTickEnabled(false);

	UE_LOG(LogTemp, Log, TEXT("WhisperSTTComponent: Stopped listening."));
}

void UWhisperSTTComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsListening)
	{
		return;
	}

	// Check for completed transcription results
	if (InferenceWorker && InferenceWorker->HasResult())
	{
		FString Transcript = InferenceWorker->ConsumeResult();
		if (!Transcript.IsEmpty())
		{
			OnTranscriptReady.Broadcast(Transcript);
		}
	}

	// Process VAD on accumulated audio
	ProcessVAD();
}

void UWhisperSTTComponent::OnAudioGenerate(const float* InAudio, int32 NumSamples)
{
	if (!bIsListening || InAudio == nullptr || NumSamples <= 0)
	{
		return;
	}

	// Append to VAD buffer for energy calculation
	int32 OldSize = VADBuffer.Num();
	VADBuffer.SetNum(OldSize + NumSamples);
	FMemory::Memcpy(VADBuffer.GetData() + OldSize, InAudio, NumSamples * sizeof(float));

	// If speaking, also accumulate into speech buffer
	if (bIsSpeaking)
	{
		OldSize = SpeechBuffer.Num();
		SpeechBuffer.SetNum(OldSize + NumSamples);
		FMemory::Memcpy(SpeechBuffer.GetData() + OldSize, InAudio, NumSamples * sizeof(float));
	}
}

void UWhisperSTTComponent::ProcessVAD()
{
	if (VADBuffer.Num() == 0)
	{
		return;
	}

	float Energy = CalculateRMSEnergy(VADBuffer);
	VADBuffer.Empty();

	float DeltaTime = GetWorld() ? GetWorld()->GetDeltaSeconds() : 0.016f;

	if (Energy > VADEnergyThreshold)
	{
		// Voice activity detected
		SilenceAccumulator = 0.0f;

		if (!bIsSpeaking)
		{
			bIsSpeaking = true;
			SpeechAccumulator = 0.0f;
			SpeechBuffer.Empty();
			OnVoiceActivityChanged.Broadcast(true);
		}

		SpeechAccumulator += DeltaTime;
	}
	else
	{
		// Silence
		if (bIsSpeaking)
		{
			SilenceAccumulator += DeltaTime;

			if (SilenceAccumulator >= SilenceDuration)
			{
				// End of speech detected
				bIsSpeaking = false;
				OnVoiceActivityChanged.Broadcast(false);

				// Only transcribe if speech was long enough
				if (SpeechAccumulator >= MinSpeechDuration && SpeechBuffer.Num() > 0)
				{
					SubmitSpeechForTranscription();
				}
				else
				{
					SpeechBuffer.Empty();
				}

				SilenceAccumulator = 0.0f;
				SpeechAccumulator = 0.0f;
			}
		}
	}
}

float UWhisperSTTComponent::CalculateRMSEnergy(const TArray<float>& AudioBuffer) const
{
	if (AudioBuffer.Num() == 0)
	{
		return 0.0f;
	}

	float SumSquares = 0.0f;
	for (float Sample : AudioBuffer)
	{
		SumSquares += Sample * Sample;
	}

	return FMath::Sqrt(SumSquares / static_cast<float>(AudioBuffer.Num()));
}

void UWhisperSTTComponent::SubmitSpeechForTranscription()
{
	if (!InferenceWorker || SpeechBuffer.Num() == 0)
	{
		return;
	}

	// Don't queue if the worker is already processing
	if (InferenceWorker->IsProcessing())
	{
		UE_LOG(LogTemp, Verbose, TEXT("WhisperSTTComponent: Inference worker busy, dropping audio segment."));
		SpeechBuffer.Empty();
		return;
	}

	UE_LOG(LogTemp, Verbose, TEXT("WhisperSTTComponent: Submitting %d samples for transcription."), SpeechBuffer.Num());
	InferenceWorker->QueueAudioBuffer(MoveTemp(SpeechBuffer), SampleRate);
	SpeechBuffer.Empty();
}
