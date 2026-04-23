#pragma once

#include "CoreMinimal.h"
#include "LLM_NPC/Core/NPCSubsystemComponent.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "TemplateAnimationDriverComponent.generated.h"

class UEmotionComponent;
class USkeletalMeshComponent;
class UAnimInstance;

/**
 * MetaHuman template-animation names as baked into the MetaHuman Creator asset.
 *
 * NOTE: these strings MUST match the MetaHuman enum spelling exactly —
 * including the typo "Suprise". If MetaHuman Creator fixes the typo in a
 * future release, update BuildNameForTemplate() to match.
 */
UENUM(BlueprintType)
enum class EMetahumanTemplateAnim : uint8
{
	Idle,
	AngerA,
	AngerB,
	FearA,
	FearB,
	HappyA,
	HappyB,
	SadA,
	SadB,
	SupriseA,
	SupriseB,
};

/**
 * Drives the MetaHuman's template face + body animations from emotion state.
 *
 * Each Plutchik emotion maps to one template pool (e.g. Joy → HappyA/B).
 * On emotion change the component picks a variant ONCE, locks it for the
 * duration of that emotional state, and writes the selection onto the
 * MetaHuman's Face and Body AnimInstances via property reflection.
 *
 * Transitions are smoothed via a short "settle" delay: when the emotion
 * changes, we wait SettleDelaySeconds before swapping the template so the
 * old expression has time to relax visually rather than snap into the new
 * pose mid-stride. Cheap-path transition — no AnimBP edits required. If
 * visually janky in PIE, upgrade to PlaySlotAnimationAsDynamicMontage.
 *
 * Property names to write to are configurable (FaceAnimTypeProperty /
 * FaceTemplateAnimProperty etc.) — discovered once at BeginPlay against
 * the actual MetaHuman AnimInstance.
 */
UCLASS(ClassGroup = (LLMNPC), meta = (BlueprintSpawnableComponent))
class LLM_NPC_API UTemplateAnimationDriverComponent : public UNPCSubsystemComponent
{
	GENERATED_BODY()

public:
	UTemplateAnimationDriverComponent();

	virtual void InitializeSubsystem() override;
	virtual void ShutdownSubsystem() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	// --- Configuration ---

	/**
	 * How long to wait after an emotion change before swapping the template
	 * animation. Gives the old pose a visual beat to relax. Set to 0.0 for
	 * instant hard-swap (useful for debugging the reflection wiring).
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Animation|Template",
		meta = (ClampMin = "0.0", ClampMax = "2.0"))
	float SettleDelaySeconds = 0.2f;

	/** Name of the enum/byte property on the Face AnimInstance that selects the template. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Animation|Template|Reflection")
	FName FaceTemplateAnimProperty = TEXT("Face Template Animation");

	/** Name of the enum/byte property on the Body AnimInstance that selects the template. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Animation|Template|Reflection")
	FName BodyTemplateAnimProperty = TEXT("Body Template Animation");

	/**
	 * Emotion-to-template mapping. Exposed so a NPC personality can override
	 * defaults without a code rebuild (e.g. a stoic NPC might map Joy to Idle).
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Animation|Template|Mapping")
	TMap<EEmotionType, EMetahumanTemplateAnim> EmotionMapPrimary;

	/** Optional B variant per emotion. When set, used 50% of the time. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Animation|Template|Mapping")
	TMap<EEmotionType, EMetahumanTemplateAnim> EmotionMapVariantB;

	/** The template currently locked in for this emotional state. */
	UPROPERTY(BlueprintReadOnly, Category = "NPC|Animation|Template")
	EMetahumanTemplateAnim CurrentLockedTemplate = EMetahumanTemplateAnim::Idle;

	/** Force a re-pick of the variant even if emotion hasn't changed. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Animation|Template")
	void ForceRepickVariant();

private:
	UFUNCTION()
	void HandleEmotionChanged(FEmotionState OldState, FEmotionState NewState);

	/** Pick A or B variant for the given emotion. Called once per emotion change. */
	EMetahumanTemplateAnim PickVariantForEmotion(EEmotionType Emotion) const;

	/** Write the chosen template onto the Face and Body AnimInstances. */
	void ApplyTemplate(EMetahumanTemplateAnim Template);

	/** Find the body SkeletalMesh (skips any mesh whose name contains "Face"). */
	USkeletalMeshComponent* FindBodyMesh(AActor* Actor) const;

	/** Find the face SkeletalMesh (matches the heuristic in MetahumanAnimComponent). */
	USkeletalMeshComponent* FindFaceMesh(AActor* Actor) const;

	/** Write an enum property by name on the given AnimInstance. */
	bool WriteTemplateEnumProperty(UAnimInstance* AnimInstance, FName PropertyName, uint8 EnumValue) const;

	/** Build the default emotion → template map if the user hasn't overridden it. */
	void BuildDefaultEmotionMappings();

	UPROPERTY()
	TObjectPtr<UEmotionComponent> CachedEmotionComp;

	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> CachedFaceMesh;

	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> CachedBodyMesh;

	UPROPERTY()
	TObjectPtr<UAnimInstance> CachedFaceAnimInstance;

	UPROPERTY()
	TObjectPtr<UAnimInstance> CachedBodyAnimInstance;

	/** Last emotion we reacted to — prevents redundant pick/apply during decay. */
	EEmotionType LastHandledEmotion = EEmotionType::Neutral;

	/** Pending template scheduled for apply after SettleDelaySeconds. */
	EMetahumanTemplateAnim PendingTemplate = EMetahumanTemplateAnim::Idle;
	bool bHasPendingTemplate = false;
	float PendingApplyTime = 0.0f;
};
