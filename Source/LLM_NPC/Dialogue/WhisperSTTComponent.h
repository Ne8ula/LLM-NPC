#pragma once

#include "CoreMinimal.h"
#include "LLM_NPC/Core/NPCSubsystemComponent.h"
#include "HAL/CriticalSection.h"
#include "WhisperSTTComponent.generated.h"

/** Delegate fired when a transcript is ready from speech-to-text. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTranscriptReady, const FString&, Transcript);

/** Delegate fired when recording state changes. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRecordingStateChanged, bool, bIsRecording);

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

	/** OpenAI API key — loaded from OPENAI_API_KEY environment variable. */
	UFUNCTION(BlueprintCallable, Category = "NPC|STT")
	bool IsAPIKeyConfigured() const { return !OpenAIAPIKey.IsEmpty(); }

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
};
