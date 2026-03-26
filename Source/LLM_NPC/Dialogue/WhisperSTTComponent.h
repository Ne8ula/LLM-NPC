#pragma once

#include "CoreMinimal.h"
#include "LLM_NPC/Core/NPCSubsystemComponent.h"
#include "HAL/CriticalSection.h"
#include "WhisperSTTComponent.generated.h"

namespace Audio { class FAudioCapture; struct FCaptureDeviceInfo; }

/** Delegate fired when a transcript is ready from speech-to-text. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTranscriptReady, const FString&, Transcript);

/** Delegate fired when recording state changes. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRecordingStateChanged, bool, bIsRecording);

/**
 * Speech-to-text component using OpenAI Whisper API (cloud).
 *
 * Hold V key to record, release to transcribe.
 * Uses Audio::FAudioCapture (low-level) to capture microphone samples directly,
 * encodes as WAV, sends to OpenAI /v1/audio/transcriptions.
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

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	/** Probe for available capture devices and log them. Returns true if at least one found. */
	bool ProbeAudioDevices();

	/** Encode recorded audio as WAV bytes for upload. */
	TArray<uint8> EncodeAsWAV(const TArray<float>& AudioData, int32 InSampleRate, int32 NumChannels) const;

	/** Send WAV data to OpenAI Whisper API. */
	void SendToWhisperAPI(const TArray<uint8>& WAVData);

	/** Handle HTTP response from OpenAI. */
	void OnWhisperResponseReceived(bool bWasSuccessful, int32 ResponseCode, const FString& ResponseBody);

	/** Low-level audio capture handle. */
	TUniquePtr<Audio::FAudioCapture> AudioCapture;

	/** Recorded audio samples — written from audio thread, read from game thread. */
	TArray<float> RecordedSamples;

	/** Lock for thread-safe access to RecordedSamples. */
	FCriticalSection SamplesLock;

	/** Recording state. */
	bool bIsRecording = false;
	bool bDeviceAvailable = false;

	/** OpenAI API key. */
	FString OpenAIAPIKey;

	/** Sample rate for recording. */
	int32 SampleRate = 16000;

	/** Actual sample rate of the capture device (may differ from target). */
	int32 DeviceSampleRate = 0;
};
