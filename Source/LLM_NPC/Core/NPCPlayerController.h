#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NPCPlayerController.generated.h"

/**
 * Player controller that handles NPC interaction input.
 * Press T to toggle the dialogue text input.
 */
UCLASS()
class LLM_NPC_API ANPCPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ANPCPlayerController();

protected:
	virtual void SetupInputComponent() override;

private:
	/** Toggle dialogue input on T press. */
	void ToggleDialogueInput();
};
