#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NPCGameMode.generated.h"

/**
 * Game mode that sets up the NPC interaction system automatically.
 * Uses NPCPlayerController (T key input) and NPCDialogueHUD (chat overlay).
 *
 * Set this as the GameMode Override in your level's World Settings.
 */
UCLASS()
class LLM_NPC_API ANPCGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANPCGameMode();
};
