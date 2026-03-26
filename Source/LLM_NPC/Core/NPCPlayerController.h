#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NPCPlayerController.generated.h"

UCLASS()
class LLM_NPC_API ANPCPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ANPCPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;

private:
	void ToggleDialogueInput();

	bool bTKeyWasDown = false;
	bool bDialogueVisible = false;
};
