#include "NPCDialogueHUD.h"
#include "NPCDialogueOverlay.h"
#include "Blueprint/UserWidget.h"

void ANPCDialogueHUD::BeginPlay()
{
	Super::BeginPlay();

	// Create the dialogue overlay widget
	if (APlayerController* PC = GetOwningPlayerController())
	{
		DialogueOverlay = CreateWidget<UNPCDialogueOverlay>(PC, UNPCDialogueOverlay::StaticClass());
		if (DialogueOverlay)
		{
			DialogueOverlay->AddToViewport(10);
			UE_LOG(LogTemp, Log, TEXT("NPCDialogueHUD: Dialogue overlay created"));
		}
	}
}

void ANPCDialogueHUD::ToggleDialogueInput()
{
	if (DialogueOverlay)
	{
		DialogueOverlay->ToggleInput();
	}
}
