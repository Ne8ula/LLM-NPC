#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FLLM_NPCModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
