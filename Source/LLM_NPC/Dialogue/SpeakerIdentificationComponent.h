#pragma once

#include "CoreMinimal.h"
#include "LLM_NPC/Core/NPCSubsystemComponent.h"
#include "SpeakerIdentificationComponent.generated.h"

class UWhisperSTTComponent;

/**
 * One enrolled voice. Spectral-band-energy fingerprint, accumulated as a
 * running average across the utterances that matched this profile.
 */
USTRUCT(BlueprintType)
struct FSpeakerProfile
{
	GENERATED_BODY()

	/** Diegetic tag (Speaker_A, Speaker_B). Matches the FNames the system
	 *  prompt / per-speaker memory maps key on. */
	UPROPERTY(BlueprintReadOnly, Category = "NPC|SpeakerID")
	FName Tag;

	/** L2-normalized 4-dim band-energy vector, in band order
	 *  0–500 / 500–1500 / 1500–3000 / 3000–8000 Hz. */
	UPROPERTY(BlueprintReadOnly, Category = "NPC|SpeakerID")
	TArray<float> Centroid;

	/** Number of utterances merged into this centroid (running-average weight). */
	UPROPERTY(BlueprintReadOnly, Category = "NPC|SpeakerID")
	int32 SampleCount = 0;

	/** Wall-clock seconds at last match — useful for stale-profile cleanup later. */
	UPROPERTY(BlueprintReadOnly, Category = "NPC|SpeakerID")
	float LastSeenTimeSec = 0.0f;
};

/** Fired after each IdentifyFromPCM call resolves a tag. Confidence in [0,1]. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSpeakerIdentified, FName, Tag, float, Confidence);

/**
 * Acoustic speaker identification — sibling of UWhisperSTTComponent on
 * ANPCCharacter. Auto-binds to the sibling's OnPCMCaptured delegate at
 * Init; computes a 4-dim spectral-band-energy fingerprint per utterance
 * (hand-rolled DFT, no SignalProcessing module dep), matches against a
 * pool of up to MaxSpeakers FSpeakerProfile centroids via cosine
 * similarity, auto-enrolls a new profile on first miss, and broadcasts
 * OnSpeakerIdentified once the tag is resolved.
 *
 * Manual override: SetManualOverrideTag(Tag) forces the next call to
 * tag the speaker as that name regardless of acoustic match (consumed
 * once). Powers the 1/2 demo keys on ANPCPlayerController.
 *
 * Single-speaker slice note: with one voice in the room, only Speaker_A
 * is ever enrolled. Speaker_B remains an empty slot until a second
 * distinct voice arrives. The §7.5 prompt section degrades gracefully.
 */
UCLASS(ClassGroup = (LLMNPC), meta = (BlueprintSpawnableComponent))
class LLM_NPC_API USpeakerIdentificationComponent : public UNPCSubsystemComponent
{
	GENERATED_BODY()

public:
	USpeakerIdentificationComponent();

	virtual void InitializeSubsystem() override;
	virtual void ShutdownSubsystem() override;

	/**
	 * Compute fingerprint, match against existing profiles, enroll if new,
	 * broadcast OnSpeakerIdentified. Called by HandlePCMCaptured (private)
	 * when the sibling Whisper dispatches a segment. C++-only because
	 * UHT rejects `TArray<int16>` in BlueprintCallable signatures — for
	 * Blueprint-side testing call HandlePCMCaptured with a uint8 buffer.
	 */
	void IdentifyFromPCM(const TArray<int16>& Samples, int32 SampleRate);

	/** Force the next IdentifyFromPCM to tag the speaker as Tag (consumed once). */
	UFUNCTION(BlueprintCallable, Category = "NPC|SpeakerID")
	void SetManualOverrideTag(FName Tag) { ManualOverrideTag = Tag; }

	/** Clear any pending manual override (e.g. on focus loss). */
	UFUNCTION(BlueprintCallable, Category = "NPC|SpeakerID")
	void ClearManualOverride() { ManualOverrideTag = NAME_None; }

	UFUNCTION(BlueprintCallable, Category = "NPC|SpeakerID")
	FName GetLastIdentifiedTag() const { return LastIdentifiedTag; }

	UFUNCTION(BlueprintCallable, Category = "NPC|SpeakerID")
	float GetLastConfidence() const { return LastConfidence; }

	UFUNCTION(BlueprintCallable, Category = "NPC|SpeakerID")
	int32 GetEnrolledSpeakerCount() const { return Profiles.Num(); }

	/** Fired after each identification (acoustic or manual override). */
	UPROPERTY(BlueprintAssignable, Category = "NPC|SpeakerID")
	FOnSpeakerIdentified OnSpeakerIdentified;

	// --- Tunables ---

	/**
	 * Cosine similarity above which an utterance matches an existing profile.
	 * Below this, a new profile is enrolled (if room). Design-doc default
	 * is 0.85; tighten if two operators sound similar, loosen if voices
	 * differ wildly and false-mismatches occur.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|SpeakerID",
		meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float MatchThreshold = 0.85f;

	/**
	 * Maximum simultaneous enrolled speakers. Two for the Memory Archive
	 * slice; bump if more operators interact later.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|SpeakerID",
		meta = (ClampMin = "1", ClampMax = "8"))
	int32 MaxSpeakers = 2;

	/**
	 * Minimum captured samples needed to compute a meaningful fingerprint
	 * (in raw mono samples — not bytes). Below this, the component falls
	 * back to the last identified tag (or Speaker_A if none yet).
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|SpeakerID",
		meta = (ClampMin = "1024"))
	int32 MinSamplesForFingerprint = 4096;

private:
	/** Bridge between Whisper's uint8 PCM broadcast and IdentifyFromPCM(int16). */
	UFUNCTION()
	void HandlePCMCaptured(const TArray<uint8>& PCMBytes, int32 SampleRate);

	/** Synthesize Speaker_A / Speaker_B / ... from a profile index. */
	static FName MakeSpeakerTag(int32 Index);

	/** Hand-rolled Hann-windowed DFT → 4-band energy vector → L2 normalize. */
	static TArray<float> ComputeFingerprint(const TArray<int16>& Samples, int32 SampleRate);

	/** Standard cosine similarity assuming both inputs are L2-normalized. */
	static float CosineSimilarity(const TArray<float>& A, const TArray<float>& B);

	/** Update centroid via sample-count weighted running average + re-normalize. */
	void UpdateProfileCentroid(int32 ProfileIdx, const TArray<float>& NewFingerprint);

	UPROPERTY()
	TArray<FSpeakerProfile> Profiles;

	/** Set by SetManualOverrideTag, consumed (cleared) on next IdentifyFromPCM. */
	UPROPERTY()
	FName ManualOverrideTag = NAME_None;

	UPROPERTY()
	FName LastIdentifiedTag = NAME_None;

	UPROPERTY()
	float LastConfidence = 0.0f;

	UPROPERTY()
	TWeakObjectPtr<UWhisperSTTComponent> CachedSTT;
};
