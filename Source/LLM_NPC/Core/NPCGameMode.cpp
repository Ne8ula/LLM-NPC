#include "NPCGameMode.h"
#include "NPCPlayerController.h"
#include "NPCDialogueHUD.h"
#include "NPCCharacter.h"
#include "NPCGraphDataAsset.h"
#include "LLM_NPC/Dialogue/DialogueComponent.h"
#include "Kismet/GameplayStatics.h"

ANPCGameMode::ANPCGameMode()
{
	PlayerControllerClass = ANPCPlayerController::StaticClass();
	HUDClass = ANPCDialogueHUD::StaticClass();
}

void ANPCGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (!ActiveGraph)
	{
		return;
	}

	// Push the active graph to every NPC in the level and resolve each NPC's GraphNodeID.
	// This runs before NPCCharacter::BeginPlay() in most cases because the GameMode is
	// created first — but DialogueComponent also has a lazy fallback in InitializeSubsystem().
	TArray<AActor*> NPCActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANPCCharacter::StaticClass(), NPCActors);

	for (AActor* Actor : NPCActors)
	{
		ANPCCharacter* NPC = Cast<ANPCCharacter>(Actor);
		if (!NPC || !NPC->NPCConfig)
		{
			continue;
		}

		// Override the graph reference on the config asset (runtime only — does not save to disk).
		NPC->NPCConfig->GraphDataAsset = ActiveGraph;

		// Resolve GraphNodeID by matching NPCConfig display name against graph node names.
		if (NPC->DialogueComponent)
		{
			const FString NPCName = NPC->NPCConfig->NPCName.ToString();
			for (const FNPCGraphNode& Node : ActiveGraph->Nodes)
			{
				if (Node.NPCName == NPCName || Node.NPCID.ToString() == NPCName)
				{
					NPC->DialogueComponent->GraphNodeID = Node.NPCID;
					UE_LOG(LogTemp, Log,
						TEXT("NPCGameMode: '%s' matched graph node '%s' (NPCID=%s)"),
						*NPCName, *Node.NPCName, *Node.NPCID.ToString());
					break;
				}
			}

			if (NPC->DialogueComponent->GraphNodeID.IsNone())
			{
				UE_LOG(LogTemp, Warning,
					TEXT("NPCGameMode: No graph node found for NPC '%s'. Check that NPCConfig->NPCName matches a graph node NPCName."),
					*NPCName);
			}
		}
	}
}
