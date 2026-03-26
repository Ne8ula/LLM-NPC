#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NPCSubsystemComponent.generated.h"

/**
 * Abstract base class for all NPC subsystem components.
 * Each subsystem (Dialogue, Emotion, Vision, Gesture, Inventory, Animation, Fallback)
 * derives from this to provide a uniform lifecycle and availability interface.
 *
 * Design principle: Component-over-inheritance. Every subsystem is a UActorComponent
 * that can be attached to any Metahuman actor, enabling procedural NPC generation.
 */
UCLASS(Abstract, ClassGroup = (LLMNPC), meta = (BlueprintSpawnableComponent))
class FLLM_NPC_API UNPCSubsystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNPCSubsystemComponent();

	/**
	 * Initialize the subsystem. Called after all components are registered.
	 * Override in derived classes to set up resources.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Subsystem")
	virtual void InitializeSubsystem();

	/**
	 * Shut down the subsystem. Release resources.
	 * Override in derived classes for cleanup.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Subsystem")
	virtual void ShutdownSubsystem();

	/**
	 * Check if the subsystem is currently available and functional.
	 * Used by the Fallback system to detect when hardware is missing.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Subsystem")
	virtual bool IsSubsystemAvailable() const;

	/** Human-readable name for this subsystem (for logging/debugging). */
	UFUNCTION(BlueprintCallable, Category = "NPC|Subsystem")
	FString GetSubsystemName() const { return SubsystemName; }

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "NPC|Subsystem")
	FString SubsystemName = TEXT("BaseSubsystem");

	UPROPERTY(BlueprintReadOnly, Category = "NPC|Subsystem")
	bool bIsInitialized = false;

	UPROPERTY(BlueprintReadOnly, Category = "NPC|Subsystem")
	bool bIsAvailable = false;
};
