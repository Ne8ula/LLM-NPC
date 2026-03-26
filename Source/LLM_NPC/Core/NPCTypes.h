#pragma once

#include "CoreMinimal.h"
#include "NPCTypes.generated.h"

/**
 * Plutchik's Wheel primary emotions + Neutral.
 * Used as discrete labels for inventory triggers, dialogue branching,
 * and Metahuman blend shape lookup.
 */
UENUM(BlueprintType)
enum class EEmotionType : uint8
{
	Neutral       UMETA(DisplayName = "Neutral"),
	Joy           UMETA(DisplayName = "Joy"),
	Sadness       UMETA(DisplayName = "Sadness"),
	Anger         UMETA(DisplayName = "Anger"),
	Fear          UMETA(DisplayName = "Fear"),
	Surprise      UMETA(DisplayName = "Surprise"),
	Disgust       UMETA(DisplayName = "Disgust"),
	Trust         UMETA(DisplayName = "Trust"),
	Anticipation  UMETA(DisplayName = "Anticipation"),
	MAX           UMETA(Hidden)
};

/** Input mode for dialogue interaction. */
UENUM(BlueprintType)
enum class EDialogueInputMode : uint8
{
	Voice    UMETA(DisplayName = "Voice"),
	Text     UMETA(DisplayName = "Text")
};

/** Input mode for object manipulation. */
UENUM(BlueprintType)
enum class EManipulationInputMode : uint8
{
	Gesture       UMETA(DisplayName = "Gesture"),
	KeyboardMouse UMETA(DisplayName = "Keyboard & Mouse")
};

/**
 * PAD (Pleasure-Arousal-Dominance) vector for continuous emotion blending.
 * Each axis ranges from -1.0 to +1.0.
 */
USTRUCT(BlueprintType)
struct LLM_NPC_API FPADVector
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "-1.0", ClampMax = "1.0"))
	float Pleasure = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "-1.0", ClampMax = "1.0"))
	float Arousal = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "-1.0", ClampMax = "1.0"))
	float Dominance = 0.0f;

	FPADVector() = default;
	FPADVector(float InPleasure, float InArousal, float InDominance)
		: Pleasure(InPleasure), Arousal(InArousal), Dominance(InDominance) {}

	/** Euclidean distance to another PAD vector. */
	float DistanceTo(const FPADVector& Other) const
	{
		return FMath::Sqrt(
			FMath::Square(Pleasure - Other.Pleasure) +
			FMath::Square(Arousal - Other.Arousal) +
			FMath::Square(Dominance - Other.Dominance)
		);
	}

	/** Linear interpolation between two PAD vectors. */
	static FPADVector Lerp(const FPADVector& A, const FPADVector& B, float Alpha)
	{
		return FPADVector(
			FMath::Lerp(A.Pleasure, B.Pleasure, Alpha),
			FMath::Lerp(A.Arousal, B.Arousal, Alpha),
			FMath::Lerp(A.Dominance, B.Dominance, Alpha)
		);
	}
};

/**
 * Canonical PAD coordinates for each Plutchik emotion.
 * Used for smooth blending and nearest-emotion lookup.
 */
namespace EmotionPADDefaults
{
	static const FPADVector Neutral      (0.0f,  0.0f,  0.0f);
	static const FPADVector Joy          (0.8f,  0.5f,  0.6f);
	static const FPADVector Sadness      (-0.7f, -0.3f, -0.5f);
	static const FPADVector Anger        (-0.6f,  0.8f,  0.5f);
	static const FPADVector Fear         (-0.7f,  0.7f, -0.7f);
	static const FPADVector Surprise     (0.2f,  0.8f, -0.1f);
	static const FPADVector Disgust      (-0.6f,  0.2f,  0.3f);
	static const FPADVector Trust        (0.6f,  0.1f,  0.3f);
	static const FPADVector Anticipation (0.3f,  0.6f,  0.4f);

	/** Get canonical PAD for a given emotion type. */
	inline FPADVector GetCanonicalPAD(EEmotionType Type)
	{
		switch (Type)
		{
		case EEmotionType::Joy:          return Joy;
		case EEmotionType::Sadness:      return Sadness;
		case EEmotionType::Anger:        return Anger;
		case EEmotionType::Fear:         return Fear;
		case EEmotionType::Surprise:     return Surprise;
		case EEmotionType::Disgust:      return Disgust;
		case EEmotionType::Trust:        return Trust;
		case EEmotionType::Anticipation: return Anticipation;
		default:                         return Neutral;
		}
	}
}

/**
 * Represents the NPC's current emotional state.
 * Combines Plutchik discrete label with PAD continuous vector.
 */
USTRUCT(BlueprintType)
struct LLM_NPC_API FEmotionState
{
	GENERATED_BODY()

	/** Primary discrete emotion (Plutchik). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEmotionType PrimaryEmotion = EEmotionType::Neutral;

	/** Intensity of the primary emotion (0.0 = none, 1.0 = maximum). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float Intensity = 0.0f;

	/** Continuous PAD vector for smooth blending. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPADVector PAD;

	/** Timestamp when this state was entered. */
	UPROPERTY(BlueprintReadOnly)
	float StateEnteredTime = 0.0f;

	/** Duration the NPC has been in this emotional state. */
	float GetStateDuration(float CurrentTime) const
	{
		return CurrentTime - StateEnteredTime;
	}
};

/** A single dialogue message in conversation history. */
USTRUCT(BlueprintType)
struct LLM_NPC_API FNPCMessage
{
	GENERATED_BODY()

	/** Role: "user", "assistant", or "system". */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Role;

	/** Message text content. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Content;

	/** Timestamp of this message. */
	UPROPERTY(BlueprintReadOnly)
	float Timestamp = 0.0f;

	/** Detected user emotion at time of message (if applicable). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEmotionType DetectedUserEmotion = EEmotionType::Neutral;

	/** Confidence of detected user emotion. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float UserEmotionConfidence = 0.0f;
};

/** Detected user emotion from facial recognition. */
USTRUCT(BlueprintType)
struct LLM_NPC_API FDetectedUserEmotion
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	EEmotionType Emotion = EEmotionType::Neutral;

	UPROPERTY(BlueprintReadOnly)
	float Confidence = 0.0f;

	/** Raw probability for each emotion class. */
	UPROPERTY(BlueprintReadOnly)
	TMap<EEmotionType, float> Probabilities;

	UPROPERTY(BlueprintReadOnly)
	float Timestamp = 0.0f;
};

/** Gesture input from hand tracking. */
UENUM(BlueprintType)
enum class EGestureType : uint8
{
	None     UMETA(DisplayName = "None"),
	Pinch    UMETA(DisplayName = "Pinch (Shrink)"),
	Spread   UMETA(DisplayName = "Spread (Enlarge)"),
	Rotate   UMETA(DisplayName = "Rotate"),
	Spindle  UMETA(DisplayName = "Spindle (Two-Hand)")
};

USTRUCT(BlueprintType)
struct LLM_NPC_API FGestureInput
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	EGestureType GestureType = EGestureType::None;

	/** Magnitude of the gesture (scale factor or rotation degrees per frame). */
	UPROPERTY(BlueprintReadOnly)
	float Magnitude = 0.0f;

	/** Confidence of gesture detection. */
	UPROPERTY(BlueprintReadOnly)
	float Confidence = 0.0f;

	/** Delta from last frame for incremental application. */
	UPROPERTY(BlueprintReadOnly)
	float Delta = 0.0f;
};

/** Signal sent to the Emotion Engine to influence NPC emotional state. */
USTRUCT(BlueprintType)
struct LLM_NPC_API FEmotionSignal
{
	GENERATED_BODY()

	/** The emotion this signal pushes toward. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEmotionType TargetEmotion = EEmotionType::Neutral;

	/** Strength of the signal (0.0 to 1.0). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float Strength = 0.0f;

	/** Source identifier for debugging. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Source;
};
