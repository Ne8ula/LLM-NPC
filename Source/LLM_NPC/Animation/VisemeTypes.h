#pragma once

#include "CoreMinimal.h"
#include "VisemeTypes.generated.h"

/**
 * 15 Oculus-style visemes.
 *
 * These are the mouth shapes the lip sync system emits. Each viseme maps
 * to a small set of MetaHuman ARKit-named face curves via
 * FPhonemeVisemeMapper::VisemeToCurves().
 */
UENUM(BlueprintType)
enum class EViseme : uint8
{
	SIL UMETA(DisplayName = "Silence"),
	PP  UMETA(DisplayName = "PP (p/b/m)"),
	FF  UMETA(DisplayName = "FF (f/v)"),
	TH  UMETA(DisplayName = "TH (th)"),
	DD  UMETA(DisplayName = "DD (t/d/n/l)"),
	KK  UMETA(DisplayName = "KK (k/g)"),
	CH  UMETA(DisplayName = "CH (ch/j/sh)"),
	SS  UMETA(DisplayName = "SS (s/z)"),
	NN  UMETA(DisplayName = "NN (n/ng)"),
	RR  UMETA(DisplayName = "RR (r)"),
	AA  UMETA(DisplayName = "AA (a)"),
	E   UMETA(DisplayName = "E (e)"),
	IH  UMETA(DisplayName = "IH (i)"),
	OH  UMETA(DisplayName = "OH (o)"),
	OU  UMETA(DisplayName = "OU (u/w)"),
};

/** One keyframe in a viseme schedule. */
USTRUCT(BlueprintType)
struct FVisemeKey
{
	GENERATED_BODY()

	/** Time in seconds from the start of playback. */
	UPROPERTY(BlueprintReadOnly, Category = "Viseme")
	float TimeSec = 0.0f;

	/** Viseme active at this time. */
	UPROPERTY(BlueprintReadOnly, Category = "Viseme")
	EViseme Viseme = EViseme::SIL;

	/** Peak weight for this key (0..1). */
	UPROPERTY(BlueprintReadOnly, Category = "Viseme")
	float Weight = 1.0f;

	FVisemeKey() = default;
	FVisemeKey(float InTime, EViseme InViseme, float InWeight)
		: TimeSec(InTime), Viseme(InViseme), Weight(InWeight) {}
};

/** A complete sequence of viseme keys for one TTS utterance. */
USTRUCT(BlueprintType)
struct FVisemeSchedule
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Viseme")
	TArray<FVisemeKey> Keys;

	/** Total duration of the utterance in seconds. */
	UPROPERTY(BlueprintReadOnly, Category = "Viseme")
	float TotalDuration = 0.0f;

	bool IsValid() const { return Keys.Num() > 0 && TotalDuration > 0.0f; }

	void Reset()
	{
		Keys.Reset();
		TotalDuration = 0.0f;
	}
};
