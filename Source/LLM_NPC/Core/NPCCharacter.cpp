#include "NPCCharacter.h"
#include "NPCSubsystemComponent.h"
#include "LLM_NPC/Dialogue/DialogueComponent.h"
#include "LLM_NPC/Emotion/EmotionComponent.h"
#include "LLM_NPC/Vision/FacialRecognitionComponent.h"
#include "LLM_NPC/Gesture/GestureRecognitionComponent.h"
#include "LLM_NPC/Inventory/NPCInventoryComponent.h"
#include "LLM_NPC/Animation/MetahumanAnimComponent.h"
#include "LLM_NPC/Animation/NPCLipSyncComponent.h"
#include "LLM_NPC/Dialogue/WhisperSTTComponent.h"
#include "LLM_NPC/Dialogue/ElevenLabsTTSComponent.h"
#include "LLM_NPC/Fallback/FallbackManagerComponent.h"

ANPCCharacter::ANPCCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create all subsystem components
	DialogueComponent = CreateDefaultSubobject<UDialogueComponent>(TEXT("DialogueComponent"));
	EmotionComponent = CreateDefaultSubobject<UEmotionComponent>(TEXT("EmotionComponent"));
	FacialRecognitionComponent = CreateDefaultSubobject<UFacialRecognitionComponent>(TEXT("FacialRecognitionComponent"));
	GestureRecognitionComponent = CreateDefaultSubobject<UGestureRecognitionComponent>(TEXT("GestureRecognitionComponent"));
	InventoryComponent = CreateDefaultSubobject<UNPCInventoryComponent>(TEXT("InventoryComponent"));
	MetahumanAnimComponent = CreateDefaultSubobject<UMetahumanAnimComponent>(TEXT("MetahumanAnimComponent"));
	LipSyncComponent = CreateDefaultSubobject<UNPCLipSyncComponent>(TEXT("LipSyncComponent"));
	WhisperSTTComponent = CreateDefaultSubobject<UWhisperSTTComponent>(TEXT("WhisperSTTComponent"));
	ElevenLabsTTSComponent = CreateDefaultSubobject<UElevenLabsTTSComponent>(TEXT("ElevenLabsTTSComponent"));
	FallbackManagerComponent = CreateDefaultSubobject<UFallbackManagerComponent>(TEXT("FallbackManagerComponent"));
}

void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitializeNPC();
}

void ANPCCharacter::InitializeNPC()
{
	if (!NPCConfig)
	{
		UE_LOG(LogTemp, Warning, TEXT("ANPCCharacter::InitializeNPC - No NPCConfig assigned to %s"), *GetName());
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("ANPCCharacter::InitializeNPC - Initializing NPC: %s"), *NPCConfig->NPCName.ToString());

	// Wire dialogue responses to TTS so the NPC speaks aloud
	if (DialogueComponent && ElevenLabsTTSComponent && ElevenLabsTTSComponent->IsSubsystemAvailable())
	{
		DialogueComponent->OnDialogueResponseReceived.AddDynamic(this, &ANPCCharacter::OnDialogueResponse);
		UE_LOG(LogTemp, Log, TEXT("ANPCCharacter: Wired dialogue responses to ElevenLabs TTS."));
	}
}

FString ANPCCharacter::GetEmotionVoiceCue(EEmotionType Emotion) const
{
	switch (Emotion)
	{
	case EEmotionType::Joy:
		return TEXT("(speaking warmly and happily) ");
	case EEmotionType::Sadness:
		return TEXT("(speaking softly and sadly, with a heavy heart) ");
	case EEmotionType::Anger:
		return TEXT("(speaking firmly and with frustration) ");
	case EEmotionType::Fear:
		return TEXT("(speaking nervously and with worry) ");
	case EEmotionType::Surprise:
		return TEXT("(speaking with wide-eyed astonishment) ");
	case EEmotionType::Disgust:
		return TEXT("(speaking with revulsion and distaste) ");
	case EEmotionType::Trust:
		return TEXT("(speaking gently and reassuringly) ");
	case EEmotionType::Anticipation:
		return TEXT("(speaking eagerly and with excitement) ");
	default:
		return TEXT("");
	}
}

void ANPCCharacter::OnDialogueResponse(const FString& ResponseText, EEmotionType NPCEmotionHint, bool bShouldGiveItem, FName ItemID)
{
	if (ElevenLabsTTSComponent && ElevenLabsTTSComponent->IsSubsystemAvailable() && !ResponseText.IsEmpty())
	{
		// Use voice config from NPCConfig if available
		FString VoiceID;
		float Stability = 0.5f;
		float SimilarityBoost = 0.75f;

		if (NPCConfig)
		{
			VoiceID = NPCConfig->ElevenLabsVoiceID;
			Stability = NPCConfig->VoiceStability;
			SimilarityBoost = NPCConfig->VoiceSimilarityBoost;
		}

		// Prepend emotional voice cue so ElevenLabs inflects accordingly
		FString EmotionCue = GetEmotionVoiceCue(NPCEmotionHint);
		FString TTSText = EmotionCue + ResponseText;

		UE_LOG(LogTemp, Log, TEXT("ANPCCharacter: TTS with emotion '%s': %s"),
			*UEnum::GetValueAsString(NPCEmotionHint), *TTSText.Left(80));

		ElevenLabsTTSComponent->SpeakText(TTSText, VoiceID, Stability, SimilarityBoost);
	}
}
