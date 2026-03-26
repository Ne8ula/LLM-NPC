#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NPCPlayerController.generated.h"

/**
 * Player controller that handles NPC interaction input.
 * Press T to toggle the dialogue text input.
 * Uses WasInputKeyJustPressed polling for UE5.7 Enhanced Input compatibility.
 */
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
};
