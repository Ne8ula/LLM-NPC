#include "NPCLipSyncComponent.h"
#include "MetahumanAnimComponent.h"
#include "PhonemeVisemeMapper.h"
#include "LLM_NPC/Dialogue/ElevenLabsTTSComponent.h"
#include "GameFramework/Actor.h"

namespace
{
	/** Closure curves get asymmetric attack/decay smoothing so the closure
	 *  registers visually before the next vowel pulls the lips open. */
	FORCEINLINE bool IsClosureCurveName(FName Name)
	{
		// Cheap substring check on the FName's string. The MetaHuman closure
		// curves all share the "LipsTogether" prefix in CTRL_expressions_*.
		const FString S = Name.ToString();
		return S.Contains(TEXT("LipsTogether"));
	}
}

UNPCLipSyncComponent::UNPCLipSyncComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	// Run after the emotion / face curves in MetahumanAnimComponent so viseme
	// curves are the last word on mouth controls during speech.
	PrimaryComponentTick.TickGroup = TG_PostUpdateWork;
	SubsystemName = TEXT("LipSync");
}

void UNPCLipSyncComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UNPCLipSyncComponent::InitializeSubsystem()
{
	Super::InitializeSubsystem();

	AActor* Owner = GetOwner();
	if (!Owner)
	{
		return;
	}

	CachedMetahumanAnim = Owner->FindComponentByClass<UMetahumanAnimComponent>();
	if (!CachedMetahumanAnim.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("LipSync: No UMetahumanAnimComponent on owner '%s' — viseme curves will not reach the face."),
			*Owner->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("LipSync: Bound to MetahumanAnim %p on owner '%s'"),
			CachedMetahumanAnim.Get(), *Owner->GetName());
	}

	CachedTTS = Owner->FindComponentByClass<UElevenLabsTTSComponent>();
	if (CachedTTS.IsValid())
	{
		CachedTTS->OnTTSAlignmentReceived.AddDynamic(this, &UNPCLipSyncComponent::HandleTTSAlignmentReceived);
		CachedTTS->OnSpeechFinished.AddDynamic(this, &UNPCLipSyncComponent::HandleSpeechFinished);
		UE_LOG(LogTemp, Log, TEXT("LipSync: Subscribed to TTS component %p (name='%s') on owner '%s'"),
			CachedTTS.Get(), *CachedTTS->GetName(), *Owner->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("LipSync: No UElevenLabsTTSComponent on owner — lip sync will be idle."));
	}
}

void UNPCLipSyncComponent::ShutdownSubsystem()
{
	if (CachedTTS.IsValid())
	{
		CachedTTS->OnTTSAlignmentReceived.RemoveDynamic(this, &UNPCLipSyncComponent::HandleTTSAlignmentReceived);
		CachedTTS->OnSpeechFinished.RemoveDynamic(this, &UNPCLipSyncComponent::HandleSpeechFinished);
	}

	StopLipSync();
	Super::ShutdownSubsystem();
}

void UNPCLipSyncComponent::StartLipSync(USoundWave* /*AudioSource*/)
{
	UE_LOG(LogTemp, Log, TEXT("LipSync: StartLipSync(SoundWave) is a no-op — lip sync now runs from TTS alignment data."));
}

void UNPCLipSyncComponent::StopLipSync()
{
	bScheduleActive = false;
	bFadingOut = false;
	FadeOutTimeRemaining = 0.0f;
	ActiveSchedule.Reset();
	LastKeyIndex = 0;

	// Zero out any curves we were driving.
	if (CachedMetahumanAnim.IsValid() && (LastCurves.Num() > 0 || SmoothedCurves.Num() > 0))
	{
		TMap<FName, float> Empty;
		CachedMetahumanAnim->SetVisemeCurves(Empty);
	}
	LastCurves.Reset();
	SmoothedCurves.Reset();
}

void UNPCLipSyncComponent::HandleTTSAlignmentReceived(
	const FString& Characters,
	const TArray<float>& StartTimesSec,
	const TArray<float>& DurationsSec)
{
	ActiveSchedule = FPhonemeVisemeMapper::BuildSchedule(Characters, StartTimesSec, DurationsSec);
	LastKeyIndex = 0;
	bScheduleActive = ActiveSchedule.IsValid();
	bFadingOut = false;
	FadeOutTimeRemaining = 0.0f;

	UE_LOG(LogTemp, Log, TEXT("LipSync: Built viseme schedule — %d keys, %.2fs duration."),
		ActiveSchedule.Keys.Num(), ActiveSchedule.TotalDuration);
}

void UNPCLipSyncComponent::HandleSpeechFinished()
{
	if (bScheduleActive)
	{
		// Begin a short fade-out so the mouth closes cleanly even if the
		// schedule ended before the audio.
		bScheduleActive = false;
		bFadingOut = true;
		FadeOutTimeRemaining = EndFadeOutSec;
	}
}

TMap<FName, float> UNPCLipSyncComponent::SampleScheduleAt(float ScheduleTime)
{
	TMap<FName, float> Result;

	const TArray<FVisemeKey>& Keys = ActiveSchedule.Keys;
	const int32 NumKeys = Keys.Num();
	if (NumKeys == 0)
	{
		return Result;
	}

	// Find the bracketing keys [A, B] such that A.TimeSec <= ScheduleTime < B.TimeSec.
	// LastKeyIndex is a hint from the previous tick — linear scan forward from there.
	int32 Idx = FMath::Clamp(LastKeyIndex, 0, NumKeys - 1);
	while (Idx + 1 < NumKeys && Keys[Idx + 1].TimeSec <= ScheduleTime)
	{
		++Idx;
	}
	while (Idx > 0 && Keys[Idx].TimeSec > ScheduleTime)
	{
		--Idx;
	}

	const FVisemeKey& KeyA = Keys[Idx];
	const FVisemeKey& KeyB = (Idx + 1 < NumKeys) ? Keys[Idx + 1] : Keys[Idx];

	// Continuous interpolation across the FULL interval between adjacent keys.
	// No "dead zone" — the moment we leave KeyA we begin moving toward KeyB,
	// arriving exactly at KeyB.TimeSec. Smoothstep easing (3α² − 2α³) gives a
	// natural ease-in/ease-out feel instead of constant velocity.
	float RawAlpha = 0.0f;
	if (KeyB.TimeSec > KeyA.TimeSec)
	{
		RawAlpha = FMath::Clamp(
			(ScheduleTime - KeyA.TimeSec) / (KeyB.TimeSec - KeyA.TimeSec),
			0.0f, 1.0f);
	}
	const float Alpha = RawAlpha * RawAlpha * (3.0f - 2.0f * RawAlpha);

	const TMap<EViseme, TArray<TPair<FName, float>>>& Table = FPhonemeVisemeMapper::VisemeToCurves();
	const TArray<TPair<FName, float>>* CurvesA = Table.Find(KeyA.Viseme);
	const TArray<TPair<FName, float>>* CurvesB = Table.Find(KeyB.Viseme);

	// True linear interpolation between viseme poses: take the union of curve
	// names from both visemes and lerp each one independently from
	// (its A-value or 0) to (its B-value or 0). This produces a real morph
	// from one mouth shape into the next, instead of layering both shapes
	// on top of each other (which is what max-blend did).
	TSet<FName> AllNames;
	if (CurvesA)
	{
		for (const TPair<FName, float>& Pair : *CurvesA)
		{
			AllNames.Add(Pair.Key);
		}
	}
	if (CurvesB)
	{
		for (const TPair<FName, float>& Pair : *CurvesB)
		{
			AllNames.Add(Pair.Key);
		}
	}

	for (const FName& Name : AllNames)
	{
		float ValA = 0.0f;
		float ValB = 0.0f;
		if (CurvesA)
		{
			for (const TPair<FName, float>& Pair : *CurvesA)
			{
				if (Pair.Key == Name) { ValA = Pair.Value; break; }
			}
		}
		if (CurvesB)
		{
			for (const TPair<FName, float>& Pair : *CurvesB)
			{
				if (Pair.Key == Name) { ValB = Pair.Value; break; }
			}
		}

		const float ScaledA = ValA * KeyA.Weight;
		const float ScaledB = ValB * KeyB.Weight;
		const float Lerped  = FMath::Lerp(ScaledA, ScaledB, Alpha);
		if (Lerped > 0.0f)
		{
			Result.Add(Name, Lerped);
		}
	}

	LastKeyIndex = Idx;
	return Result;
}

void UNPCLipSyncComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!CachedMetahumanAnim.IsValid())
	{
		return;
	}

	// --- Step 1: figure out the raw target curves for this frame. ---
	// While the schedule is active, sample it. Otherwise (idle or fading out),
	// the target is "all zeros" and the smoothing layer naturally decays.
	TMap<FName, float> TargetCurves;
	bool bAnyTargetThisFrame = false;

	if (bScheduleActive && ActiveSchedule.IsValid())
	{
		float ScheduleTime = 0.0f;
		if (CachedTTS.IsValid())
		{
			ScheduleTime = CachedTTS->GetPlaybackElapsedSeconds();
		}

		// DIAGNOSTIC: log first tick of a new schedule + one tick per second so
		// we can confirm the sampler is running and see the jawOpen curve
		// evolving. Reads the *smoothed* jawOpen value (post step 2).
		static float LastLoggedScheduleTime = -1.0f;
		const bool bFirstTickOfSchedule = (LastLoggedScheduleTime < 0.0f);
		if (bFirstTickOfSchedule
			|| FMath::Floor(ScheduleTime) > FMath::Floor(LastLoggedScheduleTime))
		{
			const TMap<FName, float> Preview = SampleScheduleAt(ScheduleTime);
			const float PeekJaw = Preview.Contains(FName("CTRL_expressions_jawOpen"))
				? Preview[FName("CTRL_expressions_jawOpen")] : 0.0f;
			UE_LOG(LogTemp, Log,
				TEXT("LipSync.Tick: t=%.3f/%.3f keys=%d jawOpen=%.3f numCurves=%d TTSSpeaking=%d"),
				ScheduleTime, ActiveSchedule.TotalDuration, ActiveSchedule.Keys.Num(),
				PeekJaw, Preview.Num(),
				(CachedTTS.IsValid() && CachedTTS->IsSpeaking()) ? 1 : 0);
		}
		LastLoggedScheduleTime = ScheduleTime;

		// Past the end — start the fade-out (smoothing handles the actual decay).
		if (ScheduleTime > ActiveSchedule.TotalDuration + 0.05f)
		{
			bScheduleActive = false;
			bFadingOut = true;
			FadeOutTimeRemaining = EndFadeOutSec;
			LastLoggedScheduleTime = -1.0f;
		}
		else
		{
			TargetCurves = SampleScheduleAt(ScheduleTime);
			LastCurves = TargetCurves;
			bAnyTargetThisFrame = TargetCurves.Num() > 0;

			static bool bLoggedFirstPush = false;
			if (!bLoggedFirstPush && bAnyTargetThisFrame)
			{
				bLoggedFirstPush = true;
				FString CurveSummary;
				for (const TPair<FName, float>& P : TargetCurves)
				{
					CurveSummary += FString::Printf(TEXT("%s=%.2f "), *P.Key.ToString(), P.Value);
				}
				UE_LOG(LogTemp, Log,
					TEXT("LipSync.Tick: FIRST curve push at t=%.3f → %s"),
					ScheduleTime, *CurveSummary);
			}
		}
	}

	// --- Step 2: smooth every active curve toward its target via exponential
	// damping (FInterpTo). Curves not in TargetCurves decay toward 0.
	//
	// Closure curves (lipsTogether*) use ASYMMETRIC smoothing:
	//   - Fast attack speed when the target is rising → lips snap shut.
	//   - Slow decay speed when the target is falling → closure lingers.
	// This makes consonant closures (M, B, P) actually register visually
	// before the next vowel pulls them open. Vowel/jaw curves use the
	// symmetric default speed.
	const bool bShouldDecayAll = !bScheduleActive; // includes fade-out and idle

	// Update / add curves that have a target this frame.
	for (const TPair<FName, float>& Pair : TargetCurves)
	{
		float& Smoothed = SmoothedCurves.FindOrAdd(Pair.Key, 0.0f);
		float Speed = OutputSmoothingSpeed;
		if (IsClosureCurveName(Pair.Key))
		{
			Speed = (Pair.Value > Smoothed) ? ClosureAttackSpeed : ClosureDecaySpeed;
		}
		Smoothed = FMath::FInterpTo(Smoothed, Pair.Value, DeltaTime, Speed);
	}

	// Decay any curve that no longer has a target (or all curves while fading out).
	for (auto It = SmoothedCurves.CreateIterator(); It; ++It)
	{
		const bool bHasTarget = TargetCurves.Contains(It.Key());
		if (bShouldDecayAll || !bHasTarget)
		{
			// Closure curves decay slowly so the closure stays visible after
			// the schedule moves past it.
			const float DecaySpeed = IsClosureCurveName(It.Key())
				? ClosureDecaySpeed
				: OutputSmoothingSpeed;
			It.Value() = FMath::FInterpTo(It.Value(), 0.0f, DeltaTime, DecaySpeed);
			if (FMath::IsNearlyZero(It.Value(), 0.005f))
			{
				It.RemoveCurrent();
			}
		}
	}

	// If we're fading out and everything has decayed, the utterance is done.
	if (bFadingOut && SmoothedCurves.Num() == 0)
	{
		bFadingOut = false;
		ActiveSchedule.Reset();
		LastKeyIndex = 0;
		LastCurves.Reset();
	}

	// --- Step 3: push the smoothed curve set to the face. ---
	// We push every frame that we have any active state (smoothed or target),
	// so the face stays consistent and we never leave stale curves behind.
	if (SmoothedCurves.Num() > 0 || bAnyTargetThisFrame)
	{
		CachedMetahumanAnim->SetVisemeCurves(SmoothedCurves);
	}
}
