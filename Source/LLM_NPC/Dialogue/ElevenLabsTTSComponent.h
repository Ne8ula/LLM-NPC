#pragma once

#include "CoreMinimal.h"
#include "LLM_NPC/Core/NPCSubsystemComponent.h"
#include "ElevenLabsTTSComponent.generated.h"

class UAudioComponent;
class USoundWaveProcedural;

/** Delegate fired when TTS speech playback starts. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpeechStarted);

/** Delegate fired when TTS speech playback finishes. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpeechFinished);

/** Delegate fired when raw audio data is received (for lip sync). */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTTSAudioDataReceived, const TArray<uint8>&, AudioData, int32, SampleRate);

/** Delegate fired when character-level alignment data is received from ElevenLabs (for viseme lip sync). */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnTTSAlignmentReceived, const FString&, Characters, const TArray<float>&, StartTimesSec, const TArray<float>&, DurationsSec);

/**
 * Delegate fired when a TTS HTTP request fails — non-200 response, parse
 * failure, or audio creation failure. ResponseCode is the HTTP status (or
 * a negative internal code: -1 parse, -2 audio_create). ErrorBody is the
 * raw response body from ElevenLabs or an internal reason string.
 *
 * Subscribers should treat this as "speech is NOT happening" and clear any
 * speaking/thinking state they were holding. Used by UNPCLipSyncComponent
 * to StopLipSync cleanly, UMetahumanAnimComponent to clear the thinking
 * face pose, and UNPCBodyMotionComponent to return the body to idle.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSpeechError, int32, ResponseCode, const FString&, ErrorBody);

/**
 * Text-to-Speech component using the ElevenLabs API.
 *
 * Sends text to ElevenLabs, receives audio bytes, creates a USoundWaveProcedural,
 * and plays it through a UAudioComponent. Audio data is also broadcast for lip sync.
 */
UCLASS(ClassGroup = (LLMNPC), meta = (BlueprintSpawnableComponent))
class LLM_NPC_API UElevenLabsTTSComponent : public UNPCSubsystemComponent
{
	GENERATED_BODY()

public:
	UElevenLabsTTSComponent();

	// --- UNPCSubsystemComponent Interface ---
	virtual void InitializeSubsystem() override;
	virtual void ShutdownSubsystem() override;
	virtual bool IsSubsystemAvailable() const override;

	/**
	 * Convert text to speech and play it.
	 *
	 * @param Text              The text to speak.
	 * @param VoiceID           ElevenLabs voice ID. If empty, uses the default from config.
	 * @param Stability         Voice stability (0.0-1.0). Negative uses default.
	 * @param SimilarityBoost   Voice similarity boost (0.0-1.0). Negative uses default.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|TTS")
	void SpeakText(const FString& Text, const FString& VoiceID = TEXT(""), float Stability = -1.0f, float SimilarityBoost = -1.0f);

	/** Stop any currently playing speech. */
	UFUNCTION(BlueprintCallable, Category = "NPC|TTS")
	void StopSpeaking();

	/** Whether speech is currently playing. */
	UFUNCTION(BlueprintCallable, Category = "NPC|TTS")
	bool IsSpeaking() const;

	/** Fired when speech playback starts. */
	UPROPERTY(BlueprintAssignable, Category = "NPC|TTS")
	FOnSpeechStarted OnSpeechStarted;

	/** Fired when speech playback finishes. */
	UPROPERTY(BlueprintAssignable, Category = "NPC|TTS")
	FOnSpeechFinished OnSpeechFinished;

	/** Fired when raw audio data is received. Used by lip sync components. */
	UPROPERTY(BlueprintAssignable, Category = "NPC|TTS")
	FOnTTSAudioDataReceived OnTTSAudioDataReceived;

	/** Fired when ElevenLabs character-level alignment data is received. Broadcast before audio playback starts. */
	UPROPERTY(BlueprintAssignable, Category = "NPC|TTS")
	FOnTTSAlignmentReceived OnTTSAlignmentReceived;

	/** Fired when a TTS request fails. Subscribers should clear any speaking/thinking state. */
	UPROPERTY(BlueprintAssignable, Category = "NPC|TTS")
	FOnSpeechError OnSpeechError;

	/**
	 * Seconds elapsed since the current TTS utterance started playing.
	 * Returns 0 if nothing is playing. Uses a wall-clock timestamp captured
	 * at Play() because USoundWaveProcedural does not expose a reliable
	 * playback cursor.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|TTS")
	float GetPlaybackElapsedSeconds() const;

	// --- Configuration ---

	/** Default ElevenLabs voice ID (can be overridden per call). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|TTS|Config")
	FString DefaultVoiceID;

	/** Default voice stability. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|TTS|Config", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float DefaultStability = 0.5f;

	/** Default voice similarity boost. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|TTS|Config", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float DefaultSimilarityBoost = 0.75f;

	/** Style exaggeration (0.0 = none, 1.0 = max). Higher values make emotional speech more pronounced. Requires v2 model. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|TTS|Config", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float StyleExaggeration = 0.5f;

	/** Audio output model ID. Default is eleven_flash_v2_5 which costs 0.5 credits
	 *  per character (vs 1.0 for multilingual_v2) and has lower latency. English
	 *  quality is comparable; set back to eleven_multilingual_v2 for best non-English
	 *  quality if you have the credit budget. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|TTS|Config")
	FString ModelID = TEXT("eleven_flash_v2_5");

	/** Output audio format. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|TTS|Config")
	FString OutputFormat = TEXT("pcm_24000");

	/** Get the UAudioComponent used for playback (useful for spatial audio setup). */
	UFUNCTION(BlueprintCallable, Category = "NPC|TTS")
	UAudioComponent* GetAudioComponent() const { return AudioPlaybackComponent; }

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	/** Load ElevenLabs API key from environment variable or config. */
	void LoadAPIKey();

	/** Build the ElevenLabs API URL for a given voice ID. */
	FString BuildAPIURL(const FString& VoiceID) const;

	/** Build the JSON request body. */
	FString BuildRequestBody(const FString& Text, float Stability, float SimilarityBoost) const;

	/** Handle the TTS HTTP response. */
	void HandleTTSResponse(bool bWasSuccessful, int32 ResponseCode, const TArray<uint8>& AudioBytes);

	/** Create a USoundWaveProcedural from raw PCM audio data and play it. */
	void PlayAudioFromPCM(const TArray<uint8>& PCMData);

	/** Parse the JSON body returned by the /with-timestamps endpoint into PCM bytes + alignment arrays. */
	bool ParseTimestampedResponse(
		const FString& JsonBody,
		TArray<uint8>& OutPCM,
		FString& OutCharacters,
		TArray<float>& OutStartTimesSec,
		TArray<float>& OutDurationsSec) const;

	/** Callback when audio playback finishes. */
	UFUNCTION()
	void OnAudioPlaybackFinished();

	/** ElevenLabs API key. */
	FString APIKey;

	/** Base URL for the ElevenLabs API. */
	FString APIBaseURL = TEXT("https://api.elevenlabs.io/v1");

	/** Audio component for playback. */
	UPROPERTY()
	TObjectPtr<UAudioComponent> AudioPlaybackComponent;

	/** Currently playing procedural sound wave. */
	UPROPERTY()
	TObjectPtr<USoundWaveProcedural> CurrentSoundWave;

	/** Whether speech is currently being played. */
	bool bIsSpeaking = false;

	/** Wall-clock timestamp (FPlatformTime::Seconds) captured when Play() was called. 0 when idle. */
	double PlaybackStartWallTime = 0.0;

	/** Whether the API key is configured. */
	bool bAPIKeyConfigured = false;

	/**
	 * Monotonically incrementing version counter for in-flight TTS requests.
	 * Incremented on every SpeakText() call; captured in the HTTP callback closure.
	 * If the response version doesn't match PendingRequestVersion the response is stale
	 * (a newer SpeakText was called in the interim) and is discarded without playback.
	 * Prevents double-playback when two callers both invoke SpeakText on the same frame.
	 */
	int32 PendingRequestVersion = 0;
};
