#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "InputModeSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueInputModeChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnManipulationInputModeChanged);

/**
 * Game-instance-level subsystem that tracks the globally active input modes
 * for dialogue (Voice / Text) and object manipulation (Gesture / KeyboardMouse).
 *
 * The FallbackManagerComponent writes to this subsystem when hardware becomes
 * unavailable.  UI and gameplay systems read from it to adapt their behaviour.
 */
UCLASS()
class LLM_NPC_API UInputModeSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// --- Dialogue input mode ---

	UFUNCTION(BlueprintCallable, Category = "NPC|InputMode")
	EDialogueInputMode GetActiveDialogueInput() const { return ActiveDialogueInput; }

	UFUNCTION(BlueprintCallable, Category = "NPC|InputMode")
	void SetDialogueInput(EDialogueInputMode NewMode);

	// --- Manipulation input mode ---

	UFUNCTION(BlueprintCallable, Category = "NPC|InputMode")
	EManipulationInputMode GetActiveManipulationInput() const { return ActiveManipulationInput; }

	UFUNCTION(BlueprintCallable, Category = "NPC|InputMode")
	void SetManipulationInput(EManipulationInputMode NewMode);

	// --- Delegates ---

	/** Broadcast when the dialogue input mode changes. */
	UPROPERTY(BlueprintAssignable, Category = "NPC|InputMode")
	FOnDialogueInputModeChanged OnDialogueInputModeChanged;

	/** Broadcast when the manipulation input mode changes. */
	UPROPERTY(BlueprintAssignable, Category = "NPC|InputMode")
	FOnManipulationInputModeChanged OnManipulationInputModeChanged;

private:
	UPROPERTY()
	EDialogueInputMode ActiveDialogueInput = EDialogueInputMode::Voice;

	UPROPERTY()
	EManipulationInputMode ActiveManipulationInput = EManipulationInputMode::Gesture;
};
