#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPCConfigDataAsset.h"
#include "NPCCharacter.generated.h"

class UNPCSubsystemComponent;
class UDialogueComponent;
class UEmotionComponent;
class UFacialRecognitionComponent;
class UGestureRecognitionComponent;
class UNPCInventoryComponent;
class UMetahumanAnimComponent;
class UNPCLipSyncComponent;
class UFallbackManagerComponent;
class UWhisperSTTComponent;
class UElevenLabsTTSComponent;

/**
 * Base Metahuman NPC actor that owns all subsystem components.
 *
 * Central design: every subsystem is a UActorComponent attached here.
 * To create a new NPC archetype, assign a different UNPCConfigDataAsset.
 * For procedural generation, spawn this actor and configure components at runtime.
 */
UCLASS(BlueprintType, Blueprintable)
class LLM_NPC_API ANPCCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ANPCCharacter();

	/** The NPC archetype configuration. Drives personality, prompts, and references. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC|Config")
	UNPCConfigDataAsset* NPCConfig;

	// ---- Subsystem Components ----

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC|Subsystems")
	TObjectPtr<UDialogueComponent> DialogueComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC|Subsystems")
	TObjectPtr<UEmotionComponent> EmotionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC|Subsystems")
	TObjectPtr<UFacialRecognitionComponent> FacialRecognitionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC|Subsystems")
	TObjectPtr<UGestureRecognitionComponent> GestureRecognitionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC|Subsystems")
	TObjectPtr<UNPCInventoryComponent> InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC|Subsystems")
	TObjectPtr<UMetahumanAnimComponent> MetahumanAnimComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC|Subsystems")
	TObjectPtr<UNPCLipSyncComponent> LipSyncComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC|Subsystems")
	TObjectPtr<UWhisperSTTComponent> WhisperSTTComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC|Subsystems")
	TObjectPtr<UElevenLabsTTSComponent> ElevenLabsTTSComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC|Subsystems")
	TObjectPtr<UFallbackManagerComponent> FallbackManagerComponent;

	/** Initialize all subsystems with the assigned NPC config. */
	UFUNCTION(BlueprintCallable, Category = "NPC")
	void InitializeNPC();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	/** Called when DialogueComponent receives a Claude response — forwards text to TTS. */
	UFUNCTION()
	void OnDialogueResponse(const FString& ResponseText, EEmotionType NPCEmotionHint, bool bShouldGiveItem, FName ItemID);

	/** Returns a stability modifier for the given emotion. Lower = more expressive voice. */
	float GetEmotionStabilityModifier(EEmotionType Emotion) const;
};
