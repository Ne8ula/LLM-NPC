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

	/** Audio output model ID (e.g., "eleven_multilingual_v2"). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|TTS|Config")
	FString ModelID = TEXT("eleven_multilingual_v2");

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

	/** Whether the API key is configured. */
	bool bAPIKeyConfigured = false;
};
