#pragma once

#include "CoreMinimal.h"
#include "LLM_NPC/Core/NPCSubsystemComponent.h"
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"
#include "WhisperSTTComponent.generated.h"

class UAudioCaptureComponent;

/** Delegate fired when a transcript is ready from speech-to-text. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTranscriptReady, const FString&, Transcript);

/** Delegate fired when voice activity is detected (started/stopped speaking). */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVoiceActivityChanged, bool, bIsSpeaking);

/**
 * Background worker thread for whisper.cpp inference.
 * Runs STT on captured audio buffers without blocking the game thread.
 */
class FLLM_NPC_API FWhisperInferenceWorker : public FRunnable
{
public:
	FWhisperInferenceWorker();
	virtual ~FWhisperInferenceWorker();

	// --- FRunnable Interface ---
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;

	/** Load the whisper model from disk. Returns true on success. */
	bool LoadModel(const FString& ModelPath, const FString& Language);

	/** Queue an audio buffer for transcription. */
	void QueueAudioBuffer(TArray<float>&& AudioData, int32 SampleRate);

	/** Check if a transcript result is available. Thread-safe. */
	bool HasResult() const;

	/** Retrieve and clear the latest transcript result. Thread-safe. */
	FString ConsumeResult();

	/** Whether the worker is currently processing audio. */
	bool IsProcessing() const;

private:
	/** Opaque pointer to whisper context. */
	void* WhisperContext = nullptr;

	/** Queued audio data for processing. */
	TArray<float> PendingAudioBuffer;
	int32 PendingSampleRate = 16000;

	/** Result string from latest transcription. */
	FString TranscriptResult;

	/** Synchronization. */
	mutable FCriticalSection DataMutex;
	FEvent* WorkAvailableEvent = nullptr;

	/** Thread control. */
	TAtomic<bool> bShouldStop{false};
	TAtomic<bool> bHasPendingWork{false};
	TAtomic<bool> bHasResult{false};
	TAtomic<bool> bIsProcessing{false};

	/** Model configuration. */
	FString ModelLanguage;
};

/**
 * Speech-to-text component using whisper.cpp for local inference.
 *
 * Captures microphone audio via UAudioCaptureComponent, performs energy-based
 * Voice Activity Detection (VAD), and sends detected speech segments to a
 * background worker thread for transcription.
 */
UCLASS(ClassGroup = (LLMNPC), meta = (BlueprintSpawnableComponent))
class FLLM_NPC_API UWhisperSTTComponent : public UNPCSubsystemComponent
{
	GENERATED_BODY()

public:
	UWhisperSTTComponent();

	// --- UNPCSubsystemComponent Interface ---
	virtual void InitializeSubsystem() override;
	virtual void ShutdownSubsystem() override;
	virtual bool IsSubsystemAvailable() const override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Start listening for speech input. */
	UFUNCTION(BlueprintCallable, Category = "NPC|STT")
	void StartListening();

	/** Stop listening for speech input. */
	UFUNCTION(BlueprintCallable, Category = "NPC|STT")
	void StopListening();

	/** Whether the component is actively listening. */
	UFUNCTION(BlueprintCallable, Category = "NPC|STT")
	bool IsListening() const { return bIsListening; }

	/** Fired when a transcription is complete. */
	UPROPERTY(BlueprintAssignable, Category = "NPC|STT")
	FOnTranscriptReady OnTranscriptReady;

	/** Fired when voice activity changes (started/stopped speaking). */
	UPROPERTY(BlueprintAssignable, Category = "NPC|STT")
	FOnVoiceActivityChanged OnVoiceActivityChanged;

	// --- Configuration ---

	/** Path to the whisper.cpp model file (relative to Content directory). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|STT|Config")
	FString WhisperModelPath = TEXT("Models/ggml-base.en.bin");

	/** Language code for transcription (e.g., "en" for English). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|STT|Config")
	FString Language = TEXT("en");

	/** Audio sample rate in Hz. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|STT|Config")
	int32 SampleRate = 16000;

	/** Energy threshold for Voice Activity Detection. Audio below this is considered silence. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|STT|Config", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float VADEnergyThreshold = 0.01f;

	/** Duration of silence (seconds) required to trigger end-of-speech. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|STT|Config", meta = (ClampMin = "0.1", ClampMax = "5.0"))
	float SilenceDuration = 1.5f;

	/** Minimum speech duration (seconds) to avoid processing noise bursts. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|STT|Config", meta = (ClampMin = "0.1", ClampMax = "5.0"))
	float MinSpeechDuration = 0.3f;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	/** Callback for audio capture data. */
	void OnAudioGenerate(const float* InAudio, int32 NumSamples);

	/** Process VAD on accumulated audio samples. */
	void ProcessVAD();

	/** Calculate RMS energy of an audio buffer. */
	float CalculateRMSEnergy(const TArray<float>& AudioBuffer) const;

	/** Send accumulated speech buffer to the inference worker. */
	void SubmitSpeechForTranscription();

	/** Audio capture component for microphone input. */
	UPROPERTY()
	TObjectPtr<UAudioCaptureComponent> AudioCaptureComponent;

	/** Background inference worker. */
	TUniquePtr<FWhisperInferenceWorker> InferenceWorker;

	/** Thread running the inference worker. */
	TUniquePtr<FRunnableThread> InferenceThread;

	/** Accumulated audio samples for current speech segment. */
	TArray<float> SpeechBuffer;

	/** Small rolling buffer for VAD energy calculation. */
	TArray<float> VADBuffer;

	/** Whether we are currently listening. */
	bool bIsListening = false;

	/** Whether voice activity is currently detected. */
	bool bIsSpeaking = false;

	/** Accumulator for silence duration. */
	float SilenceAccumulator = 0.0f;

	/** Accumulator for speech duration. */
	float SpeechAccumulator = 0.0f;

	/** Whether the microphone was successfully initialized. */
	bool bMicrophoneAvailable = false;
};
