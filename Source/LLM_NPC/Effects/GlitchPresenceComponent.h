#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GlitchPresenceComponent.generated.h"

class UMeshComponent;
class UMaterialInstanceDynamic;

UENUM(BlueprintType)
enum class EGlitchPresenceState : uint8
{
	Visible,
	GlitchingOut,
	Hidden,
	GlitchingIn
};

/**
 * Drives a periodic appear/disappear cycle on a mesh with a glitch transition.
 * The mesh is fully opaque while visible and fully hidden (SetVisibility false) in the off phase.
 * Glitch visuals during the transition are produced by a material that reads the GlitchPhase
 * and GlitchSeed scalar parameters this component sets on the mesh's material instances.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LLM_NPC_API UGlitchPresenceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UGlitchPresenceComponent();

	/** Optional explicit target. If unset, the first UMeshComponent on the owner is used. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Glitch")
	TObjectPtr<UMeshComponent> TargetMesh;

	/** Material scalar parameter driven from 0 (visible) to 1 (hidden). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Glitch|Material")
	FName GlitchPhaseParam = TEXT("GlitchPhase");

	/** Material scalar parameter re-randomised at the start of each transition. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Glitch|Material")
	FName GlitchSeedParam = TEXT("GlitchSeed");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Glitch|Timing", meta = (ClampMin = "0.1"))
	FVector2D VisibleDurationRange = FVector2D(20.f, 40.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Glitch|Timing", meta = (ClampMin = "0.1"))
	FVector2D HiddenDurationRange = FVector2D(0.3f, 0.8f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Glitch|Timing", meta = (ClampMin = "0.05"))
	float GlitchOutDuration = 0.4f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Glitch|Timing", meta = (ClampMin = "0.05"))
	float GlitchInDuration = 0.4f;

	/** Rate at which GlitchSeed is re-randomised during transitions. Higher = more strobe-like. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Glitch|Timing", meta = (ClampMin = "0.0"))
	float SeedRefreshHz = 20.f;

	/** If true, the cycle begins in the Hidden phase. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Glitch")
	bool bStartHidden = false;

	/** Force the component into a specific state. Useful for scripted events. */
	UFUNCTION(BlueprintCallable, Category = "Glitch")
	void ForceState(EGlitchPresenceState NewState);

	virtual void OnRegister() override;
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(Transient)
	TArray<TObjectPtr<UMaterialInstanceDynamic>> DynamicMaterials;

	EGlitchPresenceState State = EGlitchPresenceState::Visible;
	float StateElapsed = 0.f;
	float StateDuration = 0.f;
	float SeedRefreshAccumulator = 0.f;
	bool bInitialized = false;

	void InitializeIfNeeded();
	void EnterState(EGlitchPresenceState NewState);
	void SetGlitchPhase(float Phase);
	void RandomiseSeed();
	UMeshComponent* ResolveMesh() const;
};
