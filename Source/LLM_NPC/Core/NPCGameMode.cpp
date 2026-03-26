#include "NPCGameMode.h"
#include "NPCPlayerController.h"
#include "NPCDialogueHUD.h"

ANPCGameMode::ANPCGameMode()
{
	PlayerControllerClass = ANPCPlayerController::StaticClass();
	HUDClass = ANPCDialogueHUD::StaticClass();
}
