#include "InspectableItem.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogInspectableItem, Log, All);

AInspectableItem::AInspectableItem()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create the static mesh component as root
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	RootComponent = ItemMesh;

	// Disable collision on the mesh — physics never interacts with the item.
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Trace-only sphere for the player's E-key line trace. Blocks ECC_Visibility only;
	// ignores Pawn / WorldDynamic / Camera / etc. so the item never obstructs movement
	// or camera but is reliably hittable by Visibility traces.
	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	InteractionSphere->SetupAttachment(RootComponent);
	InteractionSphere->InitSphereRadius(InteractionRadius);
	InteractionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionSphere->SetCollisionObjectType(ECC_WorldDynamic);
	InteractionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionSphere->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	InteractionSphere->SetGenerateOverlapEvents(false);
}

void AInspectableItem::BeginPlay()
{
	Super::BeginPlay();

	// Sync sphere radius to the (possibly designer-edited) UPROPERTY value.
	if (InteractionSphere)
	{
		InteractionSphere->SetSphereRadius(InteractionRadius);
	}

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
