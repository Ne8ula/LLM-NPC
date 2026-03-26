#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "GestureClassifier.generated.h"

/**
 * Pure geometry-based gesture classifier from hand landmarks.
 *
 * Research-backed interaction enhancements:
 * - Go-Go non-linear gain: small movements map 1:1, beyond threshold D
 *   uses Rv = Rr + k*(Rr - D)^2 for reaching distant objects.
 * - PRISM precision: when hand velocity < threshold, magnitude is scaled
 *   down for fine-grained control.
 * - Spring-damper smoothing: virtual spring-damper model compensates for
 *   the lack of haptic feedback in vision-based tracking.
 */
UCLASS(BlueprintType)
class FLLM_NPC_API UGestureClassifier : public UObject
{
	GENERATED_BODY()

public:
	UGestureClassifier();

	/**
	 * Classify the current gesture from hand landmarks.
	 * Compares current landmarks against the history buffer to determine
	 * gesture type and magnitude.
	 *
	 * @param CurrentLandmarks  21 normalized (0-1) 2D hand landmarks.
	 * @param DeltaTime         Time since last frame in seconds.
	 * @return Classified gesture with magnitude and confidence.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Gesture")
	FGestureInput ClassifyGesture(const TArray<FVector2D>& CurrentLandmarks, float DeltaTime);

	/**
	 * Classify gesture when two hands are detected (enables Spindle gesture).
	 * @param LeftLandmarks   21 landmarks for the left hand.
	 * @param RightLandmarks  21 landmarks for the right hand.
	 * @param DeltaTime       Time since last frame in seconds.
	 * @return Classified gesture.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Gesture")
	FGestureInput ClassifyTwoHandGesture(const TArray<FVector2D>& LeftLandmarks,
		const TArray<FVector2D>& RightLandmarks, float DeltaTime);

	/** Reset the internal state and history buffer. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Gesture")
	void Reset();

	// ------------------------------------------------------------------
	// Research-backed tuning parameters
	// ------------------------------------------------------------------

	/** Go-Go: distance threshold beyond which non-linear gain applies. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Gesture|GoGo")
	float GoGoThresholdD = 0.3f;

	/** Go-Go: quadratic coefficient for non-linear gain. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Gesture|GoGo")
	float GoGoCoeffK = 6.0f;

	/** PRISM: hand velocity threshold below which precision scaling applies. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Gesture|PRISM")
	float PRISMVelocityThreshold = 0.05f;

	/** PRISM: scale factor for precision mode (applied when velocity < threshold). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Gesture|PRISM")
	float PRISMPrecisionScale = 0.3f;

	/** Spring stiffness for spring-damper smoothing. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Gesture|SpringDamper")
	float SpringStiffness = 50.0f;

	/** Damping coefficient for spring-damper smoothing. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Gesture|SpringDamper")
	float DamperCoefficient = 10.0f;

	/** Minimum pinch distance to register as active pinch. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Gesture", meta = (ClampMin = "0.0", ClampMax = "0.5"))
	float PinchThreshold = 0.08f;

	/** Number of frames to buffer for velocity computation and noise filtering. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Gesture", meta = (ClampMin = "2", ClampMax = "30"))
	int32 HistoryBufferSize = 10;

private:
	// Landmark indices (MediaPipe convention)
	static constexpr int32 ThumbTip = 4;
	static constexpr int32 IndexTip = 8;

	/** Compute distance between thumb tip (4) and index tip (8). */
	float ComputePinchDistance(const TArray<FVector2D>& Landmarks) const;

	/** Compute rotation angle of the thumb-index line relative to horizontal. */
	float ComputeThumbIndexAngle(const TArray<FVector2D>& Landmarks) const;

	/** Compute hand centroid velocity from history. */
	float ComputeHandVelocity() const;

	/** Apply Go-Go non-linear gain to a magnitude value. */
	float ApplyGoGoGain(float RawMagnitude) const;

	/** Apply PRISM precision scaling based on current hand velocity. */
	float ApplyPRISMPrecision(float Magnitude, float Velocity) const;

	/** Apply spring-damper smoothing to a value. */
	float ApplySpringDamperSmoothing(float TargetValue, float CurrentValue, float CurrentVelocity,
		float DeltaTime, float& OutNewVelocity) const;

	// History buffer for temporal analysis
	struct FLandmarkFrame
	{
		TArray<FVector2D> Landmarks;
		float PinchDistance = 0.0f;
		float ThumbIndexAngle = 0.0f;
		FVector2D Centroid = FVector2D::ZeroVector;
		double Timestamp = 0.0;
	};

	TArray<FLandmarkFrame> HistoryBuffer;

	// Spring-damper state
	float SmoothedMagnitude = 0.0f;
	float MagnitudeVelocity = 0.0f;
	float SmoothedAngle = 0.0f;
	float AngleVelocity = 0.0f;

	// Previous pinch distance for delta computation
	float PreviousPinchDistance = 0.0f;
	float PreviousAngle = 0.0f;

	// Two-hand tracking state
	float PreviousTwoHandDistance = 0.0f;
	float PreviousTwoHandAngle = 0.0f;

	/** Compute centroid of all landmarks. */
	static FVector2D ComputeCentroid(const TArray<FVector2D>& Landmarks);
};
