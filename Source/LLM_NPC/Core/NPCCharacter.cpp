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
	TTSComponent = CreateDefaultSubobject<UElevenLabsTTSComponent>(TEXT("TTSComponent"));
}

void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitializeNPC();
}

void ANPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Drive lip sync from text-based viseme estimation
	if (MetahumanAnimComponent && ElevenLabsTTSComponent)
	{
		bool bTTSSpeaking = ElevenLabsTTSComponent->IsSpeaking();
		UAudioComponent* AudioComp = ElevenLabsTTSComponent->GetAudioComponent();
		bool bAudioPlaying = AudioComp && AudioComp->IsPlaying();

		if (bTTSSpeaking && bAudioPlaying && !CurrentSpeechText.IsEmpty())
		{
			if (!bIsSpeaking)
			{
				// Speech just started
				bIsSpeaking = true;
				SpeechStartTime = GetWorld()->GetTimeSeconds();
			}

			// Estimate current position in text
			// ElevenLabs speaks at roughly 13-15 characters per second
			float ElapsedTime = GetWorld()->GetTimeSeconds() - SpeechStartTime;
			float CharsPerSecond = 14.0f;
			int32 EstimatedCharIndex = FMath::FloorToInt(ElapsedTime * CharsPerSecond);

			if (EstimatedCharIndex < CurrentSpeechText.Len())
			{
				// Look at current and neighboring characters for smoother visemes
				TCHAR CurrentChar = FChar::ToLower(CurrentSpeechText[EstimatedCharIndex]);
				float TargetJaw = GetVisemeJawOpen(CurrentChar);

				// Add slight randomness for natural variation
				float Noise = FMath::Sin(ElapsedTime * 23.0f) * 0.03f;
				TargetJaw = FMath::Clamp(TargetJaw + Noise, 0.0f, 0.4f);

				MetahumanAnimComponent->SetLipSyncJawOpen(TargetJaw);
			}
			else
			{
				// Past end of text, close mouth
				MetahumanAnimComponent->SetLipSyncJawOpen(0.0f);
			}
		}
		else
		{
			if (bIsSpeaking)
			{
				bIsSpeaking = false;
				CurrentSpeechText.Empty();
			}
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

		// Store the text for viseme-based lip sync
		CurrentSpeechText = ResponseText;
		bIsSpeaking = false; // Will be set true on next Tick when audio starts

		ElevenLabsTTSComponent->SpeakText(ResponseText, VoiceID, Stability, SimilarityBoost);
	}
}

float ANPCCharacter::GetVisemeJawOpen(TCHAR Char) const
{
	switch (Char)
	{
	// Wide open vowels
	case 'a': return 0.35f;
	case 'o': return 0.30f;

	// Medium open vowels
	case 'e': return 0.20f;
	case 'i': return 0.18f;
	case 'u': return 0.15f;

	// Closed lip consonants (M, B, P) — lips together
	case 'm': return 0.0f;
	case 'b': return 0.0f;
	case 'p': return 0.0f;

	// Lip-teeth consonants (F, V)
	case 'f': return 0.05f;
	case 'v': return 0.05f;

	// Dental/tongue consonants — slight opening
	case 't': return 0.08f;
	case 'd': return 0.08f;
	case 'n': return 0.08f;
	case 'l': return 0.10f;
	case 'r': return 0.12f;
	case 'z': return 0.07f;
	case 's': return 0.06f;

	// Back consonants — medium
	case 'k': return 0.12f;
	case 'g': return 0.12f;

	// Rounded consonants
	case 'w': return 0.15f;

	// H — open, breathy
	case 'h': return 0.20f;

	// Y — medium
	case 'y': return 0.15f;

	// Fricatives
	case 'j': return 0.12f;
	case 'c': return 0.10f;
	case 'x': return 0.08f;
	case 'q': return 0.10f;

	// Space/punctuation — brief close
	case ' ': return 0.02f;
	case '.': return 0.0f;
	case ',': return 0.02f;
	case '!': return 0.0f;
	case '?': return 0.0f;

	// Default for unknown characters
	default: return 0.10f;
	}
}
