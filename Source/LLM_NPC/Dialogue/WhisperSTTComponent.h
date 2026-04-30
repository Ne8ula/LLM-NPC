#pragma once

#include "CoreMinimal.h"
#include "LLM_NPC/Core/NPCSubsystemComponent.h"
#include "HAL/CriticalSection.h"
#include "Engine/TimerHandle.h"
#include "WhisperSTTComponent.generated.h"

class UElevenLabsTTSComponent;

/** Delegate fired when a transcript is ready from speech-to-text. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTranscriptReady, const FString&, Transcript);

/** Delegate fired when recording state changes. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRecordingStateChanged, bool, bIsRecording);

/**
 * Delegate fired immediately before each captured PCM segment is encoded
 * as WAV and sent to Whisper. Carries the raw int16 LE bytes (use the
 * companion SampleRate to interpret). Listeners run synchronously on the
 * game thread, in DispatchSegmentAndContinue. Used by
 * USpeakerIdentificationComponent to compute a spectral fingerprint of
 * the same audio that's about to be transcribed.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPCMCaptured, const TArray<uint8>&, PCMBytes, int32, SampleRate);

/**
 * Speech-to-text component using OpenAI Whisper API (cloud).
 *
 * Hold V key to record, release to transcribe.
 * Uses Windows waveIn API directly for microphone capture (bypasses UE AudioCapture).
 * Encodes as 16-bit 16kHz mono WAV, sends to OpenAI /v1/audio/transcriptions.
 */
UCLASS(ClassGroup = (LLMNPC), meta = (BlueprintSpawnableComponent))
class LLM_NPC_API UWhisperSTTComponent : public UNPCSubsystemComponent
{
	GENERATED_BODY()

public:
	UWhisperSTTComponent();
	~UWhisperSTTComponent();

	virtual void InitializeSubsystem() override;
	virtual void ShutdownSubsystem() override;
	virtual bool IsSubsystemAvailable() const override;

	/** Start recording from microphone. */
	UFUNCTION(BlueprintCallable, Category = "NPC|STT")
	void StartRecording();

	/** Stop recording and send to OpenAI Whisper API for transcription. */
	UFUNCTION(BlueprintCallable, Category = "NPC|STT")
	void StopRecordingAndTranscribe();

	/** Whether currently recording. */
	UFUNCTION(BlueprintCallable, Category = "NPC|STT")
	bool IsRecording() const { return bIsRecording; }

	/** Fired when transcription is complete. */
	UPROPERTY(BlueprintAssignable, Category = "NPC|STT")
	FOnTranscriptReady OnTranscriptReady;

	/** Fired when recording state changes. */
	UPROPERTY(BlueprintAssignable, Category = "NPC|STT")
	FOnRecordingStateChanged OnRecordingStateChanged;

	/** Fired with raw PCM bytes right before WAV encoding. See FOnPCMCaptured. */
	UPROPERTY(BlueprintAssignable, Category = "NPC|STT")
	FOnPCMCaptured OnPCMCaptured;

	/** OpenAI API key — loaded from OPENAI_API_KEY environment variable. */
	UFUNCTION(BlueprintCallable, Category = "NPC|STT")
	bool IsAPIKeyConfigured() const { return !OpenAIAPIKey.IsEmpty(); }

	// ------------------------------------------------------------------
	// Voice Activity Detection (continuous recording with auto-segment)
	// ------------------------------------------------------------------

	/**
	 * When true, recording does not stop on silence — instead, after MinSilenceDurationSec
	 * seconds of silence following at least MinSpeechDurationSec of speech, the current
	 * audio buffer is snapshotted, sent to Whisper, and recording continues fresh. This
	 * gives natural turn-taking: speak, pause, NPC responds, speak again, all without
	 * push-to-talk.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|STT|VAD")
	bool bAutoSegmentOnSilence = true;

	/** Peak amplitude in [0, 1] below which a 200ms window is considered silent. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|STT|VAD",
		meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float SilenceThreshold = 0.02f;

	/** Seconds of continuous silence (after speech) that triggers an auto-segment dispatch. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|STT|VAD",
		meta = (ClampMin = "0.1"))
	float MinSilenceDurationSec = 1.0f;

	/** Minimum speech duration in a segment for it to be eligible for transcription. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|STT|VAD",
		meta = (ClampMin = "0.0"))
	float MinSpeechDurationSec = 0.3f;

	// ------------------------------------------------------------------
	// TTS echo gate — drops mic samples while the sibling NPC is speaking
	// ------------------------------------------------------------------

	/**
	 * Cooldown after the NPC finishes speaking, during which mic samples are
	 * still discarded. Covers room reverb, speaker decay, and any HTTP / audio
	 * pipeline jitter so the trailing tail of NPC speech doesn't sneak into
	 * the next user transcript and get echoed back to Claude.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|STT|EchoGate",
		meta = (ClampMin = "0.0", ClampMax = "5.0"))
	float TTSCooldownSec = 0.4f;

	/** Whether the mic is currently gated (TTS playing or cooldown active). */
	UFUNCTION(BlueprintCallable, Category = "NPC|STT|EchoGate")
	bool IsMicGated() const { return bMicGated; }

	/**
	 * When true, StartRecording is called automatically at the end of
	 * InitializeSubsystem and the mic stays open for the whole PIE session.
	 * Decouples capture lifecycle from per-NPC focus — required for the
	 * single-user vertical slice, where focus flicker (proximity/facing
	 * boundary jitter, chat-overlay mode flips) would otherwise tear down
	 * and restart waveIn every tick, resetting VAD state and producing
	 * 0-byte captures forever after the first NPC turn. Set to false when
	 * multi-NPC scenarios make device contention a real concern.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|STT")
	bool bAutoStartOnInit = true;

protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

private:
	/** Encode recorded PCM as WAV bytes for upload. */
	TArray<uint8> EncodeAsWAV(const TArray<uint8>& PCMData, int32 InSampleRate, int32 NumChannels, int32 BitsPerSample) const;

	/** Send WAV data to OpenAI Whisper API. */
	void SendToWhisperAPI(const TArray<uint8>& WAVData);

	/** Handle HTTP response from OpenAI. */
	void OnWhisperResponseReceived(bool bWasSuccessful, int32 ResponseCode, const FString& ResponseBody);

	/** Recorded PCM bytes — written from waveIn callback thread. */
	TArray<uint8> RecordedPCM;

	/** Lock for thread-safe access to RecordedPCM. */
	FCriticalSection PCMLock;

	/** Opaque handle to waveIn device (HWAVEIN). */
	void* WaveInHandle = nullptr;

	/** Recording state. */
	bool bIsRecording = false;

	/** OpenAI API key. */
	FString OpenAIAPIKey;

	/** Sample rate for recording (matches Whisper expectation). */
	static constexpr int32 SampleRate = 16000;

	/** Number of waveIn buffers for double-buffering. */
	static constexpr int32 NumBuffers = 4;

	/** Size of each buffer in bytes (0.5 seconds of 16-bit mono 16kHz). */
	static constexpr int32 BufferSizeBytes = SampleRate * sizeof(int16) / 2;

	/** waveIn buffer headers (opaque, allocated in .cpp). */
	void* WaveHeaders = nullptr;

	/** Raw buffer memory for waveIn. */
	uint8* BufferMemory = nullptr;

	// --- VAD state ---

	/** Returns the peak |sample| over the last NumSamples of RecordedPCM, normalized to [0,1]. */
	float ComputeRecentPeakAmplitude(int32 NumSamples) const;

	/** Snapshot the current PCM buffer, send it to Whisper, and clear the buffer to continue recording. */
	void DispatchSegmentAndContinue();

	/** Seconds of silence accumulated in the current segment. Reset when speech is detected. */
	float TimeSinceLastSpeechSec = 0.0f;

	/** Seconds of speech accumulated in the current segment. */
	float SpeechDurationSec = 0.0f;

	/** True once the current segment has had any audible speech. */
	bool bSpeechDetectedThisSegment = false;

	// --- TTS echo gate state ---

	/**
	 * Read by the waveIn callback (audio thread) and written from the game
	 * thread on TTS start/finish/cooldown. Aligned bool reads/writes are
	 * atomic on x86/x64; a single stale read can at worst leak one buffer
	 * (~0.5s) of audio at the gate edge — the cooldown absorbs this.
	 */
	bool bMicGated = false;

	/** Timer for the post-speech cooldown window. */
	FTimerHandle MicGateCooldownTimer;

	/** Sibling TTS component we're listening to (resolved once at init). */
	UPROPERTY()
	TWeakObjectPtr<UElevenLabsTTSComponent> CachedGateTTS;

	/** TTS started — gate the mic and drop any in-flight user audio. */
	UFUNCTION()
	void HandleTTSGateStarted();

	/** TTS finished — start the cooldown timer; the gate stays on until it fires. */
	UFUNCTION()
	void HandleTTSGateFinished();

	/** TTS errored — same as finished from the mic's perspective. */
	UFUNCTION()
	void HandleTTSGateError(int32 ResponseCode, const FString& ErrorBody);

	/**
	 * Captures the total speech duration the moment alignment data arrives,
	 * just before TTS playback starts. We schedule the gate-down watchdog
	 * off this duration because UAudioComponent::OnAudioFinished does not
	 * fire reliably for USoundWaveProcedural — the queue drains but the
	 * component thinks more samples might still arrive, so OnSpeechFinished
	 * is never broadcast. Knowing the duration up-front lets us run a
	 * deterministic timer regardless.
	 */
	UFUNCTION()
	void HandleTTSAlignment(const FString& Characters, const TArray<float>& StartTimesSec, const TArray<float>& DurationsSec);

	/** Last total speech duration captured from alignment (seconds). */
	float PendingTTSDurationSec = 0.0f;

	/** Cooldown timer expired — clear residual audio and lift the gate. */
	void HandleTTSGateCooldownExpired();
};
