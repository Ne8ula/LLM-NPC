#include "NPCEyeTrackingComponent.h"
#include "MetahumanAnimComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UNPCEyeTrackingComponent::UNPCEyeTrackingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PostUpdateWork;
	SubsystemName = TEXT("EyeTracking");
}

void UNPCEyeTrackingComponent::InitializeSubsystem()
{
	Super::InitializeSubsystem();

	if (AActor* Owner = GetOwner())
	{
		CachedAnimComp = Owner->FindComponentByClass<UMetahumanAnimComponent>();
		if (!CachedAnimComp.IsValid())
		{
			UE_LOG(LogTemp, Warning,
				TEXT("EyeTracking: no UMetahumanAnimComponent on %s — eye tracking will be inert"),
				*Owner->GetName());
		}
	}
}

void UNPCEyeTrackingComponent::ShutdownSubsystem()
{
	// Zero all eye-look curves so we don't leave the eyes locked at the last
	// tracked direction during teardown.
	if (UMetahumanAnimComponent* Anim = CachedAnimComp.Get())
	{
		Anim->SetFaceCurve(FName("eyeLookOut_L"),  0.0f);
		Anim->SetFaceCurve(FName("eyeLookOut_R"),  0.0f);
		Anim->SetFaceCurve(FName("eyeLookIn_L"),   0.0f);
		Anim->SetFaceCurve(FName("eyeLookIn_R"),   0.0f);
		Anim->SetFaceCurve(FName("eyeLookUp_L"),   0.0f);
		Anim->SetFaceCurve(FName("eyeLookUp_R"),   0.0f);
		Anim->SetFaceCurve(FName("eyeLookDown_L"), 0.0f);
		Anim->SetFaceCurve(FName("eyeLookDown_R"), 0.0f);
	}

	CurrentEyeYawNorm   = 0.0f;
	CurrentEyePitchNorm = 0.0f;

	Super::ShutdownSubsystem();
}

bool UNPCEyeTrackingComponent::ComputeYawPitchToPlayer(float& OutYawDeg, float& OutPitchDeg) const
{
	AActor* Owner = GetOwner();
	if (!Owner) return false;

	APlayerCameraManager* CamMgr = UGameplayStatics::GetPlayerCameraManager(this, 0);
	if (!CamMgr) return false;

	const FVector CameraLoc = CamMgr->GetCameraLocation();

	// Origin: head bone on the body mesh if available, else actor location +
	// approximate head height. Head bone is anatomically correct; the fallback
	// avoids a silent failure on Blueprint pawns that haven't bound the mesh.
	FVector HeadLoc = Owner->GetActorLocation() + FVector(0, 0, 70.0f);
	if (ACharacter* OwnerChar = Cast<ACharacter>(Owner))
	{
		if (USkeletalMeshComponent* Body = OwnerChar->GetMesh())
		{
			if (Body->DoesSocketExist(HeadBoneName))
			{
				HeadLoc = Body->GetSocketLocation(HeadBoneName);
			}
		}
	}

	FVector ToTarget = CameraLoc - HeadLoc;
	if (ToTarget.IsNearlyZero())
	{
		OutYawDeg = 0.0f;
		OutPitchDeg = 0.0f;
		return true;
	}
	ToTarget.Normalize();

	// Express the direction in the actor's local frame. Using actor forward as
	// the reference (rather than head bone forward) avoids a feedback loop
	// with body-motion head-turn additives — eye targeting math stays stable
	// while the head turns, and eyes still track the camera correctly because
	// the eye-look curves are applied relative to the head's evaluated pose.
	const FVector Forward = Owner->GetActorForwardVector();
	const FVector Right   = Owner->GetActorRightVector();
	const FVector Up      = Owner->GetActorUpVector();

	const float FwdComp   = FVector::DotProduct(ToTarget, Forward);
	const float RightComp = FVector::DotProduct(ToTarget, Right);
	const float UpComp    = FVector::DotProduct(ToTarget, Up);

	OutYawDeg   = FMath::RadiansToDegrees(FMath::Atan2(RightComp, FwdComp));
	OutPitchDeg = FMath::RadiansToDegrees(FMath::Asin(FMath::Clamp(UpComp, -1.0f, 1.0f)));
	return true;
}

void UNPCEyeTrackingComponent::ApplyEyeLookCurves()
{
	UMetahumanAnimComponent* Anim = CachedAnimComp.Get();
	if (!Anim) return;

	// Split signed normalized values into the four 0..1 ARKit pairs.
	// Per-eye semantics: Out = away from the nose, In = toward the nose.
	// NPC's right (positive yaw):  RightEye outward + LeftEye inward.
	// NPC's left  (negative yaw):  LeftEye outward  + RightEye inward.
	const float YawRight = FMath::Max(0.0f,  CurrentEyeYawNorm);
	const float YawLeft  = FMath::Max(0.0f, -CurrentEyeYawNorm);
	const float PitchUp  = FMath::Max(0.0f,  CurrentEyePitchNorm);
	const float PitchDn  = FMath::Max(0.0f, -CurrentEyePitchNorm);

	Anim->SetFaceCurve(FName("eyeLookOut_R"), YawRight);
	Anim->SetFaceCurve(FName("eyeLookIn_L"),  YawRight);

	Anim->SetFaceCurve(FName("eyeLookOut_L"), YawLeft);
	Anim->SetFaceCurve(FName("eyeLookIn_R"),  YawLeft);

	Anim->SetFaceCurve(FName("eyeLookUp_L"),   PitchUp);
	Anim->SetFaceCurve(FName("eyeLookUp_R"),   PitchUp);
	Anim->SetFaceCurve(FName("eyeLookDown_L"), PitchDn);
	Anim->SetFaceCurve(FName("eyeLookDown_R"), PitchDn);
}

void UNPCEyeTrackingComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsInitialized || !bEyeTrackingEnabled)
	{
		// Decay back to neutral when disabled mid-game so we don't leave the
		// eyes pinned at the last tracked direction.
		if (!FMath::IsNearlyZero(CurrentEyeYawNorm) || !FMath::IsNearlyZero(CurrentEyePitchNorm))
		{
			CurrentEyeYawNorm   = FMath::FInterpTo(CurrentEyeYawNorm,   0.0f, DeltaTime, ReturnSmoothingSpeed);
			CurrentEyePitchNorm = FMath::FInterpTo(CurrentEyePitchNorm, 0.0f, DeltaTime, ReturnSmoothingSpeed);
			ApplyEyeLookCurves();
		}
		return;
	}

	// Re-acquire MetahumanAnim if it came online after our InitializeSubsystem
	// (component BeginPlay order isn't guaranteed).
	if (!CachedAnimComp.IsValid())
	{
		if (AActor* Owner = GetOwner())
		{
			CachedAnimComp = Owner->FindComponentByClass<UMetahumanAnimComponent>();
		}
		if (!CachedAnimComp.IsValid()) return;
	}

	float YawDeg   = 0.0f;
	float PitchDeg = 0.0f;
	const bool bHaveTarget = ComputeYawPitchToPlayer(YawDeg, PitchDeg);

	float TargetYawNorm   = 0.0f;
	float TargetPitchNorm = 0.0f;
	float SmoothingSpeed  = ReturnSmoothingSpeed;

	if (bHaveTarget
		&& FMath::Abs(YawDeg)   <= PeripheralYawDeg
		&& FMath::Abs(PitchDeg) <= PeripheralPitchDeg)
	{
		// Inside cone — clamp to physical eye range, normalize to [-1, 1].
		const float ClampedYaw   = FMath::Clamp(YawDeg,   -MaxEyeYawDeg,   MaxEyeYawDeg);
		const float ClampedPitch = FMath::Clamp(PitchDeg, -MaxEyePitchDeg, MaxEyePitchDeg);
		TargetYawNorm   = ClampedYaw   / MaxEyeYawDeg;
		TargetPitchNorm = ClampedPitch / MaxEyePitchDeg;
		SmoothingSpeed  = TrackingSmoothingSpeed;
	}

	CurrentEyeYawNorm   = FMath::FInterpTo(CurrentEyeYawNorm,   TargetYawNorm,   DeltaTime, SmoothingSpeed);
	CurrentEyePitchNorm = FMath::FInterpTo(CurrentEyePitchNorm, TargetPitchNorm, DeltaTime, SmoothingSpeed);

	ApplyEyeLookCurves();
}
