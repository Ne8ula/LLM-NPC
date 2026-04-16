#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NPCGameMode.generated.h"

class UNPCGraphDataAsset;

/**
 * Game mode that sets up the NPC interaction system automatically.
 * Uses NPCPlayerController (T key input) and NPCDialogueHUD (chat overlay).
 *
 * Set this as the GameMode Override in your level's World Settings.
 *
 * For THRESHOLD: set ActiveGraph to DA_Graph_ThresholdDefault (or a procedurally generated
 * graph asset). BeginPlay() will push the graph reference to every ANPCCharacter in the level
 * and resolve each NPC's GraphNodeID by name-matching against graph nodes.
 */
UCLASS()
class LLM_NPC_API ANPCGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANPCGameMode();

	/**
	 * The active social graph for this playthrough.
	 * Set in World Settings → GameMode class defaults for Threshold_Compound.umap.
	 * When valid, all ANPCCharacter actors in the level receive this graph and have
	 * their DialogueComponent::GraphNodeID resolved before InitializeSubsystem() completes.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "THRESHOLD")
	TObjectPtr<class UNPCGraphDataAsset> ActiveGraph;

protected:
	virtual void BeginPlay() override;
};
