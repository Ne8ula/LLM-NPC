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
#include "Components/AudioComponent.h"

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

void ANPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Drive lip sync from TTS audio playback
	if (MetahumanAnimComponent && ElevenLabsTTSComponent)
	{
		bool bIsSpeaking = ElevenLabsTTSComponent->IsSpeaking();
		UAudioComponent* AudioComp = ElevenLabsTTSComponent->GetAudioComponent();
		bool bAudioPlaying = AudioComp && AudioComp->IsPlaying();

		if (bIsSpeaking && bAudioPlaying)
		{
			const float Time = GetWorld()->GetTimeSeconds();
			// Subtle jaw movement — max ~0.35 for natural speech, not gaping
			float Amplitude = FMath::Abs(FMath::Sin(Time * 10.0f)) *
				FMath::Abs(FMath::Sin(Time * 5.3f)) * 0.25f +
				FMath::Abs(FMath::Sin(Time * 7.1f)) * 0.08f;
			Amplitude = FMath::Clamp(Amplitude, 0.02f, 0.35f);

			MetahumanAnimComponent->SetLipSyncJawOpen(Amplitude);
		}
		else
		{
			MetahumanAnimComponent->SetLipSyncJawOpen(0.0f);
		}
	}
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

float ANPCCharacter::GetEmotionStabilityModifier(EEmotionType Emotion) const
{
	// Lower stability = more expressive/emotional voice in ElevenLabs
	switch (Emotion)
	{
	case EEmotionType::Joy:          return -0.20f;
	case EEmotionType::Sadness:      return -0.25f;
	case EEmotionType::Anger:        return -0.30f;
	case EEmotionType::Fear:         return -0.25f;
	case EEmotionType::Surprise:     return -0.30f;
	case EEmotionType::Disgust:      return -0.20f;
	case EEmotionType::Trust:        return -0.10f;
	case EEmotionType::Anticipation: return -0.20f;
	default:                         return 0.0f;
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

		// Modulate stability based on emotion — lower = more expressive
		float StabilityMod = GetEmotionStabilityModifier(NPCEmotionHint);
		Stability = FMath::Clamp(Stability + StabilityMod, 0.1f, 1.0f);

		// Boost style exaggeration for emotional states
		if (NPCEmotionHint != EEmotionType::Neutral)
		{
			ElevenLabsTTSComponent->StyleExaggeration = FMath::Clamp(0.7f + FMath::Abs(StabilityMod), 0.0f, 1.0f);
		}
		else
		{
			ElevenLabsTTSComponent->StyleExaggeration = 0.3f;
		}

		UE_LOG(LogTemp, Log, TEXT("ANPCCharacter: TTS emotion='%s', stability=%.2f, style=%.2f: %s"),
			*UEnum::GetValueAsString(NPCEmotionHint), Stability, ElevenLabsTTSComponent->StyleExaggeration, *ResponseText.Left(80));

		ElevenLabsTTSComponent->SpeakText(ResponseText, VoiceID, Stability, SimilarityBoost);
	}
}
