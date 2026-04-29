#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InspectableItem.generated.h"

class USphereComponent;

/**
 * An inspectable 3D object rendered in the inspect viewport.
 * Supports smooth scale and rotation manipulation via spring-damper interpolation.
 * Transforms are not applied directly but interpolated each tick toward target values.
 *
 * Carries narrative fields (ItemDisplayName / ItemWorldDescription / NPCKnowledgeText / ItemID)
 * consumed by UDialogueComponent::SendObjectPresentMessage when the player presents the item to an NPC.
 * The item also exposes a USphereComponent (QueryOnly, blocks ECC_Visibility) used by the player
 * controller's line trace to detect pickable items in range.
 */
UCLASS(BlueprintType)
class LLM_NPC_API AInspectableItem : public AActor
{
	GENERATED_BODY()

public:
	AInspectableItem();

	/**
	 * Apply a scale delta to the target scale.
	 * Positive values scale up, negative values scale down.
	 * The actual scale is smoothly interpolated each tick.
	 * @param ScaleDelta  Amount to add to the target uniform scale.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Gesture|Inspect")
	void ApplyScale(float ScaleDelta);

	/**
	 * Apply a rotation delta to the target rotation.
	 * The actual rotation is smoothly interpolated each tick.
	 * @param RotationDelta  Rotation to add to the target rotation.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Gesture|Inspect")
	void ApplyRotation(FRotator RotationDelta);

	/**
	 * Reset the item to its original transform (scale and rotation).
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Gesture|Inspect")
	void ResetTransform();

	// ------------------------------------------------------------------
	// Properties
	// ------------------------------------------------------------------

	/** The mesh component displayed in the inspect viewport. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC|Gesture|Inspect")
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	/**
	 * Trace-only sphere used by the player controller's line trace to detect pickable items.
	 * QueryOnly + blocks ECC_Visibility only; ignores all other channels.
	 * The mesh itself remains NoCollision so the item never pushes anything physically.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC|Inspect")
	TObjectPtr<USphereComponent> InteractionSphere;

	/** Radius (cm) of the interaction sphere around the item. Tune per-item if mesh size varies. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Inspect", meta = (ClampMin = "1.0"))
	float InteractionRadius = 40.0f;

	// ------------------------------------------------------------------
	// Narrative fields — consumed by UDialogueComponent on Present
	// ------------------------------------------------------------------

	/** Stable identifier referenced by topic-gates in the NPC graph (e.g. "folded_note"). Lowercase, snake_case. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Inspect|Narrative")
	FName ItemID;

	/** Short human-readable name shown on the inspect HUD hint and used in the Claude payload. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Inspect|Narrative")
	FString ItemDisplayName;

	/**
	 * Description of the item from the operator's external perspective — what the player sees
	 * when they pick it up or present it. Injected verbatim into the Claude turn as
	 * "They see: {ItemWorldDescription}".
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Inspect|Narrative", meta = (MultiLine = true))
	FString ItemWorldDescription;

	/**
	 * The NPC's private relationship to this object — what only they know. Injected verbatim
	 * into the Claude turn as "Your private knowledge of this object: {NPCKnowledgeText}".
	 * Never shown to the player; only surfaced through the NPC's voice if the LLM chooses to.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Inspect|Narrative", meta = (MultiLine = true))
	FString NPCKnowledgeText;

	/** Minimum allowed uniform scale. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Gesture|Inspect", meta = (ClampMin = "0.01"))
	float MinScale = 0.1f;

	/** Maximum allowed uniform scale. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Gesture|Inspect", meta = (ClampMin = "0.1"))
	float MaxScale = 5.0f;

	/** Base rotation speed multiplier. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Gesture|Inspect")
	float RotationSpeed = 1.0f;

	/** Spring stiffness for smooth interpolation toward target transforms. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Gesture|Inspect|SpringDamper")
	float SpringStiffness = 40.0f;

	/** Damping coefficient for smooth interpolation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Gesture|Inspect|SpringDamper")
	float DamperCoefficient = 8.0f;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	/**
	 * Spring-damper step for a single float value.
	 * @return Updated current value after applying spring-damper forces.
	 */
	float SpringDamperStep(float Current, float Target, float& Velocity, float DeltaTime) const;

	/**
	 * Spring-damper step for a rotator.
	 * Operates on each axis independently.
	 */
	FRotator SpringDamperStepRotator(const FRotator& Current, const FRotator& Target,
		FRotator& Velocity, float DeltaTime) const;

	// Target values (set by ApplyScale/ApplyRotation, interpolated toward each tick)
	float TargetScale = 1.0f;
	FRotator TargetRotation = FRotator::ZeroRotator;

	// Current interpolated values
	float CurrentScale = 1.0f;
	FRotator CurrentRotation = FRotator::ZeroRotator;

	// Spring-damper velocity state
	float ScaleVelocity = 0.0f;
	FRotator RotationVelocity = FRotator::ZeroRotator;

	// Initial transform for reset
	float InitialScale = 1.0f;
	FRotator InitialRotation = FRotator::ZeroRotator;
};
