#include "NPCGameMode.h"
#include "NPCPlayerController.h"
#include "NPCDialogueHUD.h"
#include "NPCCharacter.h"
#include "NPCGraphDataAsset.h"
#include "LLM_NPC/Dialogue/DialogueComponent.h"
#include "LLM_NPC/Effects/GlitchPresenceComponent.h"
#include "Components/MeshComponent.h"
#include "Kismet/GameplayStatics.h"

#if WITH_EDITOR
#include "Editor.h"
#endif

ANPCGameMode::ANPCGameMode()
{
	PlayerControllerClass = ANPCPlayerController::StaticClass();
	HUDClass = ANPCDialogueHUD::StaticClass();
}

void ANPCGameMode::BeginPlay()
{
	Super::BeginPlay();

	ApplyGlitchPresenceByTag();

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

		// Sync the DialogueComponent's NPCConfig to the character's NPCConfig.
		// The DialogueComponent may have a stale NPCConfig set from Blueprint defaults
		// (e.g., DA_NPC_Test). Overwriting it here before InitializeSubsystem() runs
		// ensures it uses the correct per-NPC config, not the Blueprint class default.
		if (NPC->DialogueComponent)
		{
			NPC->DialogueComponent->NPCConfig = NPC->NPCConfig;
		}

		// Runtime tuning — applied here so they affect all THRESHOLD NPCs without
		// needing to edit each DA_Threshold_* asset individually.
		// Emotion decay: very slow so a triggered emotion lasts the full conversation.
		NPC->NPCConfig->EmotionDecayRate = 0.003f;   // ~300s from 1.0 to threshold
		NPC->NPCConfig->NeutralThreshold = 0.03f;    // lowers the floor; emotion persists longer
		// Response length: 150 tokens ~ 1–2 sentences.
		NPC->NPCConfig->MaxResponseTokens = 150;
		// Voice expressiveness: lower stability = more emotive, less monotone.
		NPC->NPCConfig->VoiceStability = 0.3f;

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

void ANPCGameMode::ApplyGlitchPresenceByTag()
{
	if (GlitchPresenceTag.IsNone())
	{
		return;
	}

	UWorld* World = GetWorld();

#if WITH_EDITOR
	// When called from the Details panel button, 'this' is the CDO and GetWorld() is null.
	// Resolve the active editor world so the scan can run in the viewport preview.
	if ((!World || !World->IsGameWorld()) && GEditor)
	{
		World = GEditor->GetEditorWorldContext().World();
	}
#endif

	if (!World)
	{
		return;
	}

	TArray<AActor*> TaggedActors;
	UGameplayStatics::GetAllActorsWithTag(World, GlitchPresenceTag, TaggedActors);

	int32 Added = 0;
	for (AActor* Actor : TaggedActors)
	{
		if (!Actor)
		{
			continue;
		}
		if (Actor->FindComponentByClass<UGlitchPresenceComponent>())
		{
			continue;
		}
		if (!Actor->FindComponentByClass<UMeshComponent>())
		{
			UE_LOG(LogTemp, Warning,
				TEXT("NPCGameMode: Actor '%s' has tag '%s' but no UMeshComponent — glitch skipped."),
				*Actor->GetName(), *GlitchPresenceTag.ToString());
			continue;
		}

		UGlitchPresenceComponent* Comp = NewObject<UGlitchPresenceComponent>(Actor);
		Comp->RegisterComponent();
		Actor->AddInstanceComponent(Comp);
		++Added;
	}

	if (Added > 0)
	{
		UE_LOG(LogTemp, Log,
			TEXT("NPCGameMode: Added UGlitchPresenceComponent to %d actor(s) tagged '%s'."),
			Added, *GlitchPresenceTag.ToString());
	}
}
