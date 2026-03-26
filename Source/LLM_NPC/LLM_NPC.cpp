#include "LLM_NPC.h"
#include "Modules/ModuleManager.h"

void FLLM_NPCModule::StartupModule()
{
	UE_LOG(LogTemp, Log, TEXT("LLM_NPC Module Started"));
}

void FLLM_NPCModule::ShutdownModule()
{
	UE_LOG(LogTemp, Log, TEXT("LLM_NPC Module Shutdown"));
}

IMPLEMENT_PRIMARY_GAME_MODULE(FLLM_NPCModule, LLM_NPC, "LLM_NPC");
