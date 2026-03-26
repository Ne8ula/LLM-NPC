#include "InspectableItem.h"
#include "Components/StaticMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogInspectableItem, Log, All);

AInspectableItem::AInspectableItem()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create the static mesh component as root
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	RootComponent = ItemMesh;

	// Disable collision for inspection viewport
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AInspectableItem::BeginPlay()
{
	Super::BeginPlay();

	// Store initial transform for reset
	InitialScale = GetActorScale3D().X; // Assume uniform scale
	InitialRotation = GetActorRotation();

	CurrentScale = InitialScale;
	CurrentRotation = InitialRotation;
	TargetScale = InitialScale;
	TargetRotation = InitialRotation;
	ScaleVelocity = 0.0f;
	RotationVelocity = FRotator::ZeroRotator;
}

void AInspectableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DeltaTime <= 0.0f)
	{
		return;
	}

	// Spring-damper interpolate scale toward target
	CurrentScale = SpringDamperStep(CurrentScale, TargetScale, ScaleVelocity, DeltaTime);
	CurrentScale = FMath::Clamp(CurrentScale, MinScale, MaxScale);

	// Spring-damper interpolate rotation toward target
	CurrentRotation = SpringDamperStepRotator(CurrentRotation, TargetRotation, RotationVelocity, DeltaTime);

	// Apply interpolated transforms
	SetActorScale3D(FVector(CurrentScale));
	SetActorRotation(CurrentRotation);
}

void AInspectableItem::ApplyScale(float ScaleDelta)
{
	TargetScale = FMath::Clamp(TargetScale + ScaleDelta, MinScale, MaxScale);
}

void AInspectableItem::ApplyRotation(FRotator RotationDelta)
{
	TargetRotation += RotationDelta * RotationSpeed;
	TargetRotation.Normalize();
}

void AInspectableItem::ResetTransform()
{
	TargetScale = InitialScale;
	TargetRotation = InitialRotation;
	// Velocities will naturally settle via spring-damper
}

float AInspectableItem::SpringDamperStep(float Current, float Target, float& Velocity, float DeltaTime) const
{
	// F = -k*(x - target) - c*v
	const float SpringForce = -SpringStiffness * (Current - Target);
	const float DamperForce = -DamperCoefficient * Velocity;
	const float Acceleration = SpringForce + DamperForce;

	Velocity += Acceleration * DeltaTime;
	return Current + Velocity * DeltaTime;
}

FRotator AInspectableItem::SpringDamperStepRotator(const FRotator& Current, const FRotator& Target,
	FRotator& Velocity, float DeltaTime) const
{
	// Apply spring-damper independently to each axis
	FRotator Result;

	float PitchVel = Velocity.Pitch;
	float YawVel = Velocity.Yaw;
	float RollVel = Velocity.Roll;

	Result.Pitch = SpringDamperStep(Current.Pitch, Target.Pitch, PitchVel, DeltaTime);
	Result.Yaw = SpringDamperStep(Current.Yaw, Target.Yaw, YawVel, DeltaTime);
	Result.Roll = SpringDamperStep(Current.Roll, Target.Roll, RollVel, DeltaTime);

	Velocity.Pitch = PitchVel;
	Velocity.Yaw = YawVel;
	Velocity.Roll = RollVel;

	return Result;
}
