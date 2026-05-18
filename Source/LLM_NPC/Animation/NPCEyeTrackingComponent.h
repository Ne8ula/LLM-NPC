#pragma once

#include "CoreMinimal.h"
#include "LLM_NPC/Core/NPCSubsystemComponent.h"
#include "NPCEyeTrackingComponent.generated.h"

class UMetahumanAnimComponent;

/**
 * Drives the MetaHuman's eyes to look at the active player camera while the
 * camera is inside the NPC's peripheral cone. Outside that cone the eyes
 * smoothly return to their default forward gaze.
 *
 * Eye look is written through UMetahumanAnimComponent::SetFaceCurve so it
 * shares the proven Set-Control reflection bridge. The curves it owns
 * (eyeLookOut_L/R, eyeLookIn_L/R, eyeLookUp_L/R, eyeLookDown_L/R) are not
 * touched by the emotion or viseme pipelines, so there is no contention.
 */
UCLASS(ClassGroup = (LLMNPC), meta = (BlueprintSpawnableComponent))
class LLM_NPC_API UNPCEyeTrackingComponent : public UNPCSubsystemComponent
{
	GENERATED_BODY()

public:
	UNPCEyeTrackingComponent();

	virtual void InitializeSubsystem() override;
	virtual void ShutdownSubsystem() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|EyeTracking")
	bool bEyeTrackingEnabled = true;

	/** Half-angle of the horizontal peripheral cone in degrees. Outside this
	 *  the eyes return to neutral. Realistic human horizontal periphery is
	 *  ~95° but for an NPC who has clearly disengaged we want them looking
	 *  forward earlier, so default is tighter. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|EyeTracking",
		meta = (ClampMin = "10.0", ClampMax = "120.0"))
	float PeripheralYawDeg = 70.0f;

	/** Half-angle of the vertical peripheral cone in degrees. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|EyeTracking",
		meta = (ClampMin = "5.0", ClampMax = "90.0"))
	float PeripheralPitchDeg = 35.0f;

	/** Maximum eyeball yaw deflection — cap the rotated curve so the eyes
	 *  don't push past their physical range. Real human eyeballs comfortably
	 *  yaw ~30° before the head naturally takes over. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|EyeTracking",
		meta = (ClampMin = "5.0", ClampMax = "45.0"))
	float MaxEyeYawDeg = 30.0f;

	/** Maximum eyeball pitch deflection. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|EyeTracking",
		meta = (ClampMin = "5.0", ClampMax = "40.0"))
	float MaxEyePitchDeg = 25.0f;

	/** FInterpTo speed when the player is inside the peripheral cone. Higher
	 *  feels snappier; lower feels lazier / more thoughtful. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|EyeTracking",
		meta = (ClampMin = "0.5"))
	float TrackingSmoothingSpeed = 8.0f;

	/** FInterpTo speed when returning to neutral. Slower than tracking so the
	 *  drop-off feels natural rather than a hard snap-forward. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|EyeTracking",
		meta = (ClampMin = "0.5"))
	float ReturnSmoothingSpeed = 3.5f;

	/** Head bone on the body skeletal mesh. Used as the eye-tracking origin.
	 *  MetaHuman convention is `head`. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|EyeTracking")
	FName HeadBoneName = FName("head");

private:
	/** Compute signed yaw and pitch (degrees) from the head to the player
	 *  camera, expressed in the actor's local frame. Returns false if no
	 *  player camera was found. */
	bool ComputeYawPitchToPlayer(float& OutYawDeg, float& OutPitchDeg) const;

	/** Push the smoothed yaw/pitch values through the eight ARKit eye-look
	 *  curves on the Face AnimBP. */
	void ApplyEyeLookCurves();

	/** Smoothed normalized yaw in [-1, 1] where +1 = full right. */
	float CurrentEyeYawNorm = 0.0f;

	/** Smoothed normalized pitch in [-1, 1] where +1 = full up. */
	float CurrentEyePitchNorm = 0.0f;

	UPROPERTY()
	TWeakObjectPtr<UMetahumanAnimComponent> CachedAnimComp;
};
