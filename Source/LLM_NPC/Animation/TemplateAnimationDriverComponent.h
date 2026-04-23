#pragma once

#include "CoreMinimal.h"
#include "LLM_NPC/Core/NPCSubsystemComponent.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "TemplateAnimationDriverComponent.generated.h"

class UEmotionComponent;
class UDialogueComponent;
class USkeletalMeshComponent;
class UAnimInstance;
class UAnimSequence;

/**
 * MetaHuman template-animation identifiers. Naming preserved from the
 * MetaHuman Creator preview dropdown (including the typo "Suprise").
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
 * One template's Face + Body clip pair. Resolved lazily from soft object
 * paths — the plugin clips live at
 * /MetaHumanCharacter/Optional/Animation/TemplateAnimations/Expression_Loops/
 * but NPC authors can override per-character (e.g. Friend uses _f_ female
 * variants; a male NPC would use _m_ clips).
 */
USTRUCT(BlueprintType)
struct FMetahumanTemplateClipRef
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Template|Clips")
	TSoftObjectPtr<UAnimSequence> FaceClip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Template|Clips")
	TSoftObjectPtr<UAnimSequence> BodyClip;
};

/**
 * Drives the MetaHuman's emotion-driven face + body animations.
 *
 * Each Plutchik emotion maps to one template pool (e.g. Joy → HappyA/B).
 * On emotion change the component picks a variant ONCE, locks it for the
 * duration of that emotional state, and plays the associated UAnimSequence
 * clips on the Face + Body meshes as dynamic montages on the Default slot.
 *
 * Why montages and not enum-reflection:
 *  - UE 5.7's UAF MetaHuman pipeline does NOT expose runtime template-switch
 *    enums on any AnimInstance. The "Face Template Animation" dropdown in
 *    the MetaHuman Character editor is an editor-only preview selector that
 *    bakes one clip at Assembly time.
 *  - The underlying clips exist as standalone UAnimSequence assets in the
 *    MetaHumanCharacter plugin, playable via PlaySlotAnimationAsDynamicMontage
 *    against any compatible AnimInstance — no custom AnimBP required.
 *  - See the plan doc section "E.0b — Path 1 attempted" for the full
 *    investigation.
 *
 * Transitions are smoothed via a short "settle" delay (outgoing pose relaxes
 * before incoming stamps in) and a montage blend-in/out of SettleDelaySeconds.
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
	 * Crossfade time between emotion templates — used as the montage blend-in
	 * and blend-out duration. With real montage-based playback (see
	 * FaceSlotAnimBP / BodySlotAnimBP below) this produces a true A→B blend
	 * between templates. The old SettleDelaySeconds-as-deferred-apply logic
	 * was removed; montages cross-blend themselves.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Animation|Template",
		meta = (ClampMin = "0.0", ClampMax = "3.0"))
	float SettleDelaySeconds = 0.6f;

	/**
	 * Slot name to play the emotion montage on. Must match a Slot node in the
	 * AnimBP assigned to FaceSlotAnimBP / BodySlotAnimBP.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Animation|Template")
	FName MontageSlotName = TEXT("DefaultSlot");

	/**
	 * Minimal AnimBP with a Slot node to host emotion-montage playback on
	 * the Face mesh. Required for crossfade: UAF MetaHumans ship with a
	 * post-process AnimBP only and no primary AnimInstance; PlayAnimation
	 * would hard-swap, but a real AnimBP with a Slot node gives us
	 * PlaySlotAnimationAsDynamicMontage with blend-in/out.
	 *
	 * If null, the driver falls back to PlayAnimation (hard-swap, no blend).
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Animation|Template|Slot")
	TSoftClassPtr<UAnimInstance> FaceSlotAnimBP;

	/** Same as FaceSlotAnimBP, for the Body mesh. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Animation|Template|Slot")
	TSoftClassPtr<UAnimInstance> BodySlotAnimBP;

	/**
	 * Emotion-to-template mapping. A NPC personality can override defaults
	 * without a code rebuild (e.g. a stoic NPC might map Joy to Idle).
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Animation|Template|Mapping")
	TMap<EEmotionType, EMetahumanTemplateAnim> EmotionMapPrimary;

	/** Optional B variant per emotion. When set, used 50% of the time. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Animation|Template|Mapping")
	TMap<EEmotionType, EMetahumanTemplateAnim> EmotionMapVariantB;

	/**
	 * Clip map — Face + Body AnimSequence per template. Pre-populated from
	 * the MetaHumanCharacter plugin's female (_f_) variants; override per NPC
	 * for male voice + frame (swap to _m_ clips).
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Animation|Template|Clips")
	TMap<EMetahumanTemplateAnim, FMetahumanTemplateClipRef> ClipMap;

	/** The template currently locked in for this emotional state. */
	UPROPERTY(BlueprintReadOnly, Category = "NPC|Animation|Template")
	EMetahumanTemplateAnim CurrentLockedTemplate = EMetahumanTemplateAnim::Idle;

	/** Force a re-pick of the variant even if emotion hasn't changed. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Animation|Template")
	void ForceRepickVariant();

	/**
	 * When true (default), templates switch based on Claude's directly-parsed
	 * emotion on each dialogue response (DialogueComponent::
	 * OnDialogueResponseReceived). Bypasses EmotionComponent's state-machine
	 * decay, which can lag several minutes behind what Claude just said she's
	 * feeling. When false, falls back to EmotionComponent::OnEmotionChanged.
	 *
	 * EmotionComponent is unaffected either way — it still drives voice
	 * modulation, FACS curves, and other downstream systems. Only the
	 * template animation selection is decoupled.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Animation|Template")
	bool bDriveFromDialogueResponse = true;

private:
	UFUNCTION()
	void HandleEmotionChanged(FEmotionState OldState, FEmotionState NewState);

	UFUNCTION()
	void HandleDialogueResponse(const FString& ResponseText, EEmotionType NPCEmotionHint,
		bool bShouldGiveItem, FName ItemID);

	/** Pick A or B variant for the given emotion. Called once per emotion change. */
	EMetahumanTemplateAnim PickVariantForEmotion(EEmotionType Emotion) const;

	/** Play the chosen template's clips on Face + Body as dynamic montages. */
	void ApplyTemplate(EMetahumanTemplateAnim Template);

	/** Stop emotion montages on both meshes — used when collapsing to Idle. */
	void StopAllEmotionMontages();

	/** Find the body SkeletalMesh (skips any mesh whose name contains "Face"). */
	USkeletalMeshComponent* FindBodyMesh(AActor* Actor) const;

	/** Find the face SkeletalMesh (matches the heuristic in MetahumanAnimComponent). */
	USkeletalMeshComponent* FindFaceMesh(AActor* Actor) const;

	/** Build the default emotion → template map. */
	void BuildDefaultEmotionMappings();

	/** Build the default clip map pointing at the MetaHumanCharacter plugin clips. */
	void BuildDefaultClipMappings();

	/** Build the default slot-AnimBP soft pointers for Friend's setup. */
	void BuildDefaultSlotAnimBPs();

	/** Install the slot AnimBP on the mesh if the mesh has no primary AnimInstance yet. */
	void InstallSlotAnimBP(USkeletalMeshComponent* Mesh, TSoftClassPtr<UAnimInstance>& SlotClassPtr, const TCHAR* Tag);

	UPROPERTY()
	TObjectPtr<UEmotionComponent> CachedEmotionComp;

	UPROPERTY()
	TObjectPtr<UDialogueComponent> CachedDialogueComp;

	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> CachedFaceMesh;

	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> CachedBodyMesh;

	/** Last emotion we reacted to — prevents redundant pick/apply during decay. */
	EEmotionType LastHandledEmotion = EEmotionType::Neutral;
};
