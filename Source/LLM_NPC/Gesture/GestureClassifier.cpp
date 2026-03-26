#include "GestureClassifier.h"
#include "HAL/PlatformTime.h"

DEFINE_LOG_CATEGORY_STATIC(LogGestureClassifier, Log, All);

UGestureClassifier::UGestureClassifier()
{
}

FGestureInput UGestureClassifier::ClassifyGesture(const TArray<FVector2D>& CurrentLandmarks, float DeltaTime)
{
	FGestureInput Result;
	Result.GestureType = EGestureType::None;
	Result.Magnitude = 0.0f;
	Result.Confidence = 0.0f;
	Result.Delta = 0.0f;

	if (CurrentLandmarks.Num() < 21 || DeltaTime <= 0.0f)
	{
		return Result;
	}

	// Compute current frame metrics
	const float CurrentPinchDist = ComputePinchDistance(CurrentLandmarks);
	const float CurrentAngle = ComputeThumbIndexAngle(CurrentLandmarks);
	const FVector2D CurrentCentroid = ComputeCentroid(CurrentLandmarks);

	// Add to history buffer
	FLandmarkFrame Frame;
	Frame.Landmarks = CurrentLandmarks;
	Frame.PinchDistance = CurrentPinchDist;
	Frame.ThumbIndexAngle = CurrentAngle;
	Frame.Centroid = CurrentCentroid;
	Frame.Timestamp = FPlatformTime::Seconds();

	HistoryBuffer.Add(Frame);
	if (HistoryBuffer.Num() > HistoryBufferSize)
	{
		HistoryBuffer.RemoveAt(0);
	}

	// Need at least 2 frames for delta computation
	if (HistoryBuffer.Num() < 2)
	{
		PreviousPinchDistance = CurrentPinchDist;
		PreviousAngle = CurrentAngle;
		return Result;
	}

	// Compute hand velocity for PRISM precision
	const float HandVelocity = ComputeHandVelocity();

	// Compute deltas
	const float PinchDelta = CurrentPinchDist - PreviousPinchDistance;
	const float AngleDelta = CurrentAngle - PreviousAngle;

	// Determine gesture type based on landmark geometry
	const bool bIsPinching = CurrentPinchDist < PinchThreshold;
	const float AbsPinchDelta = FMath::Abs(PinchDelta);
	const float AbsAngleDelta = FMath::Abs(AngleDelta);

	if (bIsPinching && AbsAngleDelta > 0.02f)
	{
		// Rotation detected while pinching
		Result.GestureType = EGestureType::Rotate;
		float RawMagnitude = AngleDelta;

		// Apply Go-Go gain
		RawMagnitude = FMath::Sign(RawMagnitude) * ApplyGoGoGain(FMath::Abs(RawMagnitude));

		// Apply PRISM precision
		RawMagnitude = ApplyPRISMPrecision(RawMagnitude, HandVelocity);

		// Apply spring-damper smoothing
		float NewVelocity = 0.0f;
		SmoothedAngle = SmoothedAngle; // preserve state
		float SmoothedValue = ApplySpringDamperSmoothing(RawMagnitude, SmoothedAngle, AngleVelocity, DeltaTime, NewVelocity);
		SmoothedAngle = SmoothedValue;
		AngleVelocity = NewVelocity;

		Result.Magnitude = SmoothedValue;
		Result.Delta = SmoothedValue;
		Result.Confidence = FMath::Clamp(1.0f - CurrentPinchDist / PinchThreshold, 0.0f, 1.0f);
	}
	else if (AbsPinchDelta > 0.005f)
	{
		// Pinch or spread gesture
		Result.GestureType = PinchDelta < 0.0f ? EGestureType::Pinch : EGestureType::Spread;
		float RawMagnitude = PinchDelta;

		// Apply Go-Go gain
		RawMagnitude = FMath::Sign(RawMagnitude) * ApplyGoGoGain(FMath::Abs(RawMagnitude));

		// Apply PRISM precision
		RawMagnitude = ApplyPRISMPrecision(RawMagnitude, HandVelocity);

		// Apply spring-damper smoothing
		float NewVelocity = 0.0f;
		float SmoothedValue = ApplySpringDamperSmoothing(RawMagnitude, SmoothedMagnitude, MagnitudeVelocity, DeltaTime, NewVelocity);
		SmoothedMagnitude = SmoothedValue;
		MagnitudeVelocity = NewVelocity;

		Result.Magnitude = FMath::Abs(SmoothedValue);
		Result.Delta = SmoothedValue;
		Result.Confidence = FMath::Clamp(AbsPinchDelta * 10.0f, 0.0f, 1.0f);
	}

	PreviousPinchDistance = CurrentPinchDist;
	PreviousAngle = CurrentAngle;

	return Result;
}

FGestureInput UGestureClassifier::ClassifyTwoHandGesture(const TArray<FVector2D>& LeftLandmarks,
	const TArray<FVector2D>& RightLandmarks, float DeltaTime)
{
	FGestureInput Result;
	Result.GestureType = EGestureType::None;
	Result.Magnitude = 0.0f;
	Result.Confidence = 0.0f;
	Result.Delta = 0.0f;

	if (LeftLandmarks.Num() < 21 || RightLandmarks.Num() < 21 || DeltaTime <= 0.0f)
	{
		return Result;
	}

	// Compute centroids of both hands
	const FVector2D LeftCentroid = ComputeCentroid(LeftLandmarks);
	const FVector2D RightCentroid = ComputeCentroid(RightLandmarks);

	// Distance and angle between the two hand centroids
	const float TwoHandDistance = FVector2D::Distance(LeftCentroid, RightCentroid);
	const FVector2D HandDiff = RightCentroid - LeftCentroid;
	const float TwoHandAngle = FMath::Atan2(HandDiff.Y, HandDiff.X);

	if (PreviousTwoHandDistance > 0.0f)
	{
		const float DistanceDelta = TwoHandDistance - PreviousTwoHandDistance;
		const float AngleDelta = TwoHandAngle - PreviousTwoHandAngle;

		Result.GestureType = EGestureType::Spindle;

		// Combine distance and angle deltas for spindle magnitude
		float RawMagnitude = DistanceDelta;

		// Apply Go-Go gain
		RawMagnitude = FMath::Sign(RawMagnitude) * ApplyGoGoGain(FMath::Abs(RawMagnitude));

		// Apply spring-damper smoothing
		float NewVelocity = 0.0f;
		float SmoothedValue = ApplySpringDamperSmoothing(RawMagnitude, SmoothedMagnitude, MagnitudeVelocity, DeltaTime, NewVelocity);
		SmoothedMagnitude = SmoothedValue;
		MagnitudeVelocity = NewVelocity;

		Result.Magnitude = FMath::Abs(SmoothedValue);
		Result.Delta = SmoothedValue;
		Result.Confidence = FMath::Clamp(FMath::Abs(DistanceDelta) * 5.0f + FMath::Abs(AngleDelta) * 2.0f, 0.0f, 1.0f);
	}

	PreviousTwoHandDistance = TwoHandDistance;
	PreviousTwoHandAngle = TwoHandAngle;

	return Result;
}

void UGestureClassifier::Reset()
{
	HistoryBuffer.Empty();
	SmoothedMagnitude = 0.0f;
	MagnitudeVelocity = 0.0f;
	SmoothedAngle = 0.0f;
	AngleVelocity = 0.0f;
	PreviousPinchDistance = 0.0f;
	PreviousAngle = 0.0f;
	PreviousTwoHandDistance = 0.0f;
	PreviousTwoHandAngle = 0.0f;
}

float UGestureClassifier::ComputePinchDistance(const TArray<FVector2D>& Landmarks) const
{
	if (Landmarks.Num() <= FMath::Max(ThumbTip, IndexTip))
	{
		return 1.0f;
	}
	return FVector2D::Distance(Landmarks[ThumbTip], Landmarks[IndexTip]);
}

float UGestureClassifier::ComputeThumbIndexAngle(const TArray<FVector2D>& Landmarks) const
{
	if (Landmarks.Num() <= FMath::Max(ThumbTip, IndexTip))
	{
		return 0.0f;
	}
	const FVector2D Diff = Landmarks[IndexTip] - Landmarks[ThumbTip];
	return FMath::Atan2(Diff.Y, Diff.X);
}

float UGestureClassifier::ComputeHandVelocity() const
{
	if (HistoryBuffer.Num() < 2)
	{
		return 0.0f;
	}

	const FLandmarkFrame& Current = HistoryBuffer.Last();
	const FLandmarkFrame& Previous = HistoryBuffer[HistoryBuffer.Num() - 2];

	const double TimeDelta = Current.Timestamp - Previous.Timestamp;
	if (TimeDelta <= 0.0)
	{
		return 0.0f;
	}

	const float Distance = FVector2D::Distance(Current.Centroid, Previous.Centroid);
	return Distance / static_cast<float>(TimeDelta);
}

float UGestureClassifier::ApplyGoGoGain(float RawMagnitude) const
{
	// Go-Go: Rv = Rr for Rr <= D; Rv = Rr + k*(Rr - D)^2 for Rr > D
	if (RawMagnitude <= GoGoThresholdD)
	{
		return RawMagnitude;
	}

	const float Excess = RawMagnitude - GoGoThresholdD;
	return RawMagnitude + GoGoCoeffK * Excess * Excess;
}

float UGestureClassifier::ApplyPRISMPrecision(float Magnitude, float Velocity) const
{
	// When hand velocity is below threshold, scale down for fine control
	if (Velocity < PRISMVelocityThreshold)
	{
		const float BlendFactor = Velocity / FMath::Max(PRISMVelocityThreshold, SMALL_NUMBER);
		const float Scale = FMath::Lerp(PRISMPrecisionScale, 1.0f, BlendFactor);
		return Magnitude * Scale;
	}
	return Magnitude;
}

float UGestureClassifier::ApplySpringDamperSmoothing(float TargetValue, float CurrentValue,
	float CurrentVelocity, float DeltaTime, float& OutNewVelocity) const
{
	// Spring-damper: F = -k*(x - target) - c*v
	// a = F (mass = 1)
	const float SpringForce = -SpringStiffness * (CurrentValue - TargetValue);
	const float DamperForce = -DamperCoefficient * CurrentVelocity;
	const float Acceleration = SpringForce + DamperForce;

	OutNewVelocity = CurrentVelocity + Acceleration * DeltaTime;
	return CurrentValue + OutNewVelocity * DeltaTime;
}

FVector2D UGestureClassifier::ComputeCentroid(const TArray<FVector2D>& Landmarks)
{
	if (Landmarks.Num() == 0)
	{
		return FVector2D::ZeroVector;
	}

	FVector2D Sum = FVector2D::ZeroVector;
	for (const FVector2D& Point : Landmarks)
	{
		Sum += Point;
	}
	return Sum / static_cast<float>(Landmarks.Num());
}
