#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NPCBodyIdleAnimInstance.generated.h"

/**
 * Minimal UAnimInstance subclass assigned to the body skeletal mesh when it
 * has no user-provided AnimClass.
 *
 * Why it exists: UNPCBodyMotionComponent needs the mesh's anim pipeline to
 * run every frame so that USkeletalMeshComponent::FinalizeBoneTransform is
 * called and USkinnedMeshComponent::OnBoneTransformsFinalizedMC broadcasts.
 * Without an AnimInstance, the engine short-circuits that path and the
 * delegate never fires — which means our procedural bone offsets never get
 * a chance to run.
 *
 * This class has no Blueprint graph and no overrides. The engine's default
 * behavior for an AnimInstance with no anim graph is "output the reference
 * pose every frame" — exactly what we want as a neutral base layer.
 * UNPCBodyMotionComponent then writes procedural bone rotations on top via
 * the finalize delegate.
 *
 * If the body mesh already has an AnimClass assigned (e.g. a MetaHuman body
 * AnimBP or a custom rig), UNPCBodyMotionComponent leaves it alone.
 */
UCLASS()
class LLM_NPC_API UNPCBodyIdleAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
};
