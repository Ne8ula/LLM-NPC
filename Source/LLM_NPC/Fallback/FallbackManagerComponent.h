#pragma once

#include "CoreMinimal.h"
#include "LLM_NPC/Core/NPCSubsystemComponent.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "FallbackManagerComponent.generated.h"

class UInputModeSubsystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInputModeChanged, FString, ModeName, bool, bAvailable);

/**
 * Degradation priority levels, from most capable to least.
 */
UENUM(BlueprintType)
enum class EDegradationLevel : uint8
{
	Full           UMETA(DisplayName = "Full (Camera + Mic)"),
	NoCamera       UMETA(DisplayName = "No Camera (Mic only)"),
	NoMic          UMETA(DisplayName = "No Mic (Camera only)"),
	Minimal        UMETA(DisplayName = "Minimal (Text + Keyboard)")
};

/**
 * Monitors hardware availability (microphone, camera) and automatically switches
 * input modes when devices become unavailable.
 *
 * Degradation priority: Full -> No camera -> No mic -> Minimal.
 *
 * Toggle support via input actions:
 *   T = switch to Text dialogue, V = switch to Voice dialogue,
 *   G = switch to Gesture manipulation, K = switch to Keyboard/Mouse manipulation.
 */
UCLASS(ClassGroup = (LLMNPC), meta = (BlueprintSpawnableComponent))
class FLLM_NPC_API UFallbackManagerComponent : public UNPCSubsystemComponent
{
	GENERATED_BODY()

public:
	UFallbackManagerComponent();

	// --- Lifecycle ---
	virtual void InitializeSubsystem() override;
	virtual void ShutdownSubsystem() override;

	// --- Public API ---

	/** Get the current degradation level. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Fallback")
	EDegradationLevel GetCurrentDegradationLevel() const { return CurrentDegradationLevel; }

	/** Manually set the dialogue input mode (T=text, V=voice). */
	UFUNCTION(BlueprintCallable, Category = "NPC|Fallback")
	void SetDialogueMode(EDialogueInputMode NewMode);

	/** Manually set the manipulation input mode (G=gesture, K=keyboard). */
	UFUNCTION(BlueprintCallable, Category = "NPC|Fallback")
	void SetManipulationMode(EManipulationInputMode NewMode);

	/** Force a re-check of hardware availability. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Fallback")
	void CheckDeviceAvailability();

	// --- Delegates ---

	/** Broadcast when an input mode changes due to device availability or manual toggle. */
	UPROPERTY(BlueprintAssignable, Category = "NPC|Fallback")
	FOnInputModeChanged OnInputModeChanged;

	// --- Configuration ---

	/** Interval in seconds between hardware availability polls. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Fallback",
		meta = (ClampMin = "0.5"))
	float PollIntervalSeconds = 2.0f;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	/** Timer-driven periodic check for mic and camera availability. */
	void PollDevices();

	/** Update the degradation level based on current device states. */
	void UpdateDegradationLevel(bool bMicAvailable, bool bCameraAvailable);

	/** Get the InputModeSubsystem from the game instance. */
	UInputModeSubsystem* GetInputModeSubsystem() const;

	/** Check if a microphone / STT subsystem is available. */
	bool IsMicrophoneAvailable() const;

	/** Check if a camera / vision subsystem is available. */
	bool IsCameraAvailable() const;

	/** Timer handle for periodic device polling. */
	FTimerHandle DevicePollTimerHandle;

	/** Current degradation level. */
	UPROPERTY()
	EDegradationLevel CurrentDegradationLevel = EDegradationLevel::Full;

	/** Cached device states to detect transitions. */
	bool bLastMicAvailable = true;
	bool bLastCameraAvailable = true;
};
