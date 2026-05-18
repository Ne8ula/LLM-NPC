#include "SpeakerIdentificationComponent.h"
#include "WhisperSTTComponent.h"

USpeakerIdentificationComponent::USpeakerIdentificationComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SubsystemName = TEXT("SpeakerID");
}

void USpeakerIdentificationComponent::InitializeSubsystem()
{
	Super::InitializeSubsystem();

	if (AActor* Owner = GetOwner())
	{
		if (UWhisperSTTComponent* STT = Owner->FindComponentByClass<UWhisperSTTComponent>())
		{
			CachedSTT = STT;
			STT->OnPCMCaptured.AddDynamic(this, &USpeakerIdentificationComponent::HandlePCMCaptured);
			UE_LOG(LogTemp, Log,
				TEXT("SpeakerID: bound to Whisper '%s' (matchThreshold=%.2f, maxSpeakers=%d)"),
				*STT->GetName(), MatchThreshold, MaxSpeakers);
		}
		else
		{
			UE_LOG(LogTemp, Warning,
				TEXT("SpeakerID: no UWhisperSTTComponent on %s — speaker ID will be inert"),
				*Owner->GetName());
		}
	}
}

void USpeakerIdentificationComponent::ShutdownSubsystem()
{
	if (UWhisperSTTComponent* STT = CachedSTT.Get())
	{
		STT->OnPCMCaptured.RemoveDynamic(this, &USpeakerIdentificationComponent::HandlePCMCaptured);
	}
	CachedSTT.Reset();
	Super::ShutdownSubsystem();
}

void USpeakerIdentificationComponent::HandlePCMCaptured(const TArray<uint8>& PCMBytes, int32 SampleRate)
{
	// Reinterpret int16 LE bytes as a typed sample array. Whisper's buffer
	// is byte-aligned by construction (16-bit mono frames) so the / 2 is
	// always exact.
	TArray<int16> Samples;
	const int32 NumSamples = PCMBytes.Num() / (int32)sizeof(int16);
	if (NumSamples <= 0)
	{
		return;
	}
	Samples.SetNumUninitialized(NumSamples);
	FMemory::Memcpy(Samples.GetData(), PCMBytes.GetData(), NumSamples * sizeof(int16));

	IdentifyFromPCM(Samples, SampleRate);
}

void USpeakerIdentificationComponent::IdentifyFromPCM(const TArray<int16>& Samples, int32 SampleRate)
{
	// Manual override consumes immediately. Fingerprint is still computed
	// (so the override doubles as a training step on the named profile).
	const FName Override = ManualOverrideTag;
	ManualOverrideTag = NAME_None;

	if (Samples.Num() < MinSamplesForFingerprint && Override.IsNone())
	{
		// Too short to fingerprint reliably. Fall back to last known tag,
		// or Speaker_A if nothing is enrolled yet — keeps the downstream
		// per-speaker memory writes consistent.
		const FName Fallback = LastIdentifiedTag.IsNone() ? FName(TEXT("Speaker_A")) : LastIdentifiedTag;
		LastIdentifiedTag = Fallback;
		// Confidence intentionally unchanged on fallback.
		OnSpeakerIdentified.Broadcast(Fallback, LastConfidence);
		UE_LOG(LogTemp, Log,
			TEXT("SpeakerID: utterance too short (%d samples < %d) — fallback %s"),
			Samples.Num(), MinSamplesForFingerprint, *Fallback.ToString());
		return;
	}

	const TArray<float> Fingerprint = ComputeFingerprint(Samples, SampleRate);

	// Resolve match index even when override is active, so we update the
	// matching profile (or enroll the override tag's profile from scratch).
	int32 BestIdx = INDEX_NONE;
	float BestSim = -1.0f;
	for (int32 i = 0; i < Profiles.Num(); ++i)
	{
		const float Sim = CosineSimilarity(Fingerprint, Profiles[i].Centroid);
		if (Sim > BestSim)
		{
			BestSim = Sim;
			BestIdx = i;
		}
	}

	FName ResolvedTag;
	float ResolvedConfidence = BestSim;

	if (!Override.IsNone())
	{
		// Manual override path: use the override tag, train its profile
		// (creating it if it doesn't exist yet, displacing oldest if at cap).
		ResolvedTag = Override;
		ResolvedConfidence = 1.0f;

		int32 OverrideIdx = INDEX_NONE;
		for (int32 i = 0; i < Profiles.Num(); ++i)
		{
			if (Profiles[i].Tag == Override)
			{
				OverrideIdx = i;
				break;
			}
		}
		if (OverrideIdx == INDEX_NONE)
		{
			if (Profiles.Num() < MaxSpeakers)
			{
				FSpeakerProfile NewProfile;
				NewProfile.Tag = Override;
				NewProfile.Centroid = Fingerprint;
				NewProfile.SampleCount = 1;
				NewProfile.LastSeenTimeSec = (float)FPlatformTime::Seconds();
				Profiles.Add(NewProfile);
			}
			else
			{
				// At cap and the override tag isn't one of them — replace
				// the stalest profile so the demo operator can still pivot.
				int32 StalestIdx = 0;
				for (int32 i = 1; i < Profiles.Num(); ++i)
				{
					if (Profiles[i].LastSeenTimeSec < Profiles[StalestIdx].LastSeenTimeSec)
					{
						StalestIdx = i;
					}
				}
				Profiles[StalestIdx].Tag = Override;
				Profiles[StalestIdx].Centroid = Fingerprint;
				Profiles[StalestIdx].SampleCount = 1;
				Profiles[StalestIdx].LastSeenTimeSec = (float)FPlatformTime::Seconds();
			}
		}
		else
		{
			UpdateProfileCentroid(OverrideIdx, Fingerprint);
		}

		UE_LOG(LogTemp, Log, TEXT("SpeakerID: manual override -> %s"), *ResolvedTag.ToString());
	}
	else if (BestIdx != INDEX_NONE && BestSim >= MatchThreshold)
	{
		// Acoustic match against existing profile.
		ResolvedTag = Profiles[BestIdx].Tag;
		UpdateProfileCentroid(BestIdx, Fingerprint);
		UE_LOG(LogTemp, Log, TEXT("SpeakerID: matched %s (similarity %.2f)"),
			*ResolvedTag.ToString(), BestSim);
	}
	else if (Profiles.Num() < MaxSpeakers)
	{
		// New voice — enroll.
		FSpeakerProfile NewProfile;
		NewProfile.Tag = MakeSpeakerTag(Profiles.Num());
		NewProfile.Centroid = Fingerprint;
		NewProfile.SampleCount = 1;
		NewProfile.LastSeenTimeSec = (float)FPlatformTime::Seconds();
		Profiles.Add(NewProfile);
		ResolvedTag = NewProfile.Tag;
		ResolvedConfidence = 1.0f;
		UE_LOG(LogTemp, Log, TEXT("SpeakerID: enrolled %s (%d/%d profiles)"),
			*ResolvedTag.ToString(), Profiles.Num(), MaxSpeakers);
	}
	else
	{
		// At max enrolled speakers, no acoustic match — pin to the closest
		// existing profile. Prevents a third voice from getting silently
		// dropped (it'll temporarily masquerade as A or B); the operator
		// can hit the 1/2 keys to override if it lands wrong.
		ResolvedTag = Profiles[BestIdx].Tag;
		UE_LOG(LogTemp, Warning,
			TEXT("SpeakerID: at MaxSpeakers, no match (best %.2f<%.2f) — pinning to %s"),
			BestSim, MatchThreshold, *ResolvedTag.ToString());
	}

	LastIdentifiedTag = ResolvedTag;
	LastConfidence = ResolvedConfidence;
	OnSpeakerIdentified.Broadcast(ResolvedTag, ResolvedConfidence);
}

FName USpeakerIdentificationComponent::MakeSpeakerTag(int32 Index)
{
	const TCHAR Letter = (TCHAR)(TEXT('A') + Index);
	return FName(*FString::Printf(TEXT("Speaker_%c"), Letter));
}

void USpeakerIdentificationComponent::UpdateProfileCentroid(int32 ProfileIdx, const TArray<float>& NewFingerprint)
{
	if (!Profiles.IsValidIndex(ProfileIdx)) return;

	FSpeakerProfile& P = Profiles[ProfileIdx];
	if (P.Centroid.Num() != NewFingerprint.Num())
	{
		P.Centroid = NewFingerprint;
		P.SampleCount = 1;
		P.LastSeenTimeSec = (float)FPlatformTime::Seconds();
		return;
	}

	// Sample-count weighted running average. Caps the new sample's weight
	// so the centroid is reasonably stable after a handful of utterances.
	const float NewWeight = 1.0f / (float)(P.SampleCount + 1);
	const float OldWeight = 1.0f - NewWeight;
	for (int32 i = 0; i < P.Centroid.Num(); ++i)
	{
		P.Centroid[i] = OldWeight * P.Centroid[i] + NewWeight * NewFingerprint[i];
	}

	// Re-normalize so the centroid stays unit-length (cosine similarity
	// remains a pure dot product).
	float L2 = 0.0f;
	for (float V : P.Centroid) L2 += V * V;
	L2 = FMath::Sqrt(L2) + 1e-6f;
	for (float& V : P.Centroid) V /= L2;

	P.SampleCount++;
	P.LastSeenTimeSec = (float)FPlatformTime::Seconds();
}

float USpeakerIdentificationComponent::CosineSimilarity(const TArray<float>& A, const TArray<float>& B)
{
	if (A.Num() != B.Num() || A.Num() == 0) return 0.0f;
	float Dot = 0.0f;
	for (int32 i = 0; i < A.Num(); ++i)
	{
		Dot += A[i] * B[i];
	}
	return Dot;
}

TArray<float> USpeakerIdentificationComponent::ComputeFingerprint(const TArray<int16>& Samples, int32 SampleRate)
{
	// Hand-rolled Hann-windowed DFT. Cost: WindowSize * NumBins * 2
	// trig-mults — at 4096 samples and 64 bins ≈ 524k ops per utterance.
	// Once per VAD dispatch (i.e. per user turn). Keeping NumBins tight
	// because we only need 4-band integration; per-bin frequency stays at
	// SampleRate / (2 * NumBins) ≈ 125 Hz, finer than any band edge.
	constexpr int32 WindowSize = 4096;
	constexpr int32 NumBins = 64;

	// Locate the loudest WindowSize-sample chunk in the utterance — VAD
	// dispatches the whole rolling buffer on silence, which means many
	// utterances start with several seconds of room ambient before the
	// user actually speaks. Fingerprinting from sample 0 would compute
	// the spectral signature of silence (slightly different per recording,
	// causing the same speaker to enroll as both Speaker_A and Speaker_B
	// across turns). Striding by ~16 ms blocks keeps the scan cheap.
	int32 BestStart = 0;
	{
		const int32 BlockSize = 256;
		double BestEnergy = -1.0;
		const int32 Limit = FMath::Max(0, Samples.Num() - WindowSize);
		for (int32 Start = 0; Start <= Limit; Start += BlockSize)
		{
			double E = 0.0;
			const int32 End = FMath::Min(Start + WindowSize, Samples.Num());
			for (int32 n = Start; n < End; ++n)
			{
				const float S = (float)Samples[n];
				E += S * S;
			}
			if (E > BestEnergy)
			{
				BestEnergy = E;
				BestStart = Start;
			}
		}
	}

	TArray<float> X;
	X.SetNumZeroed(WindowSize);
	const int32 Available = FMath::Max(0, Samples.Num() - BestStart);
	const int32 N = FMath::Min(Available, WindowSize);
	for (int32 n = 0; n < N; ++n)
	{
		X[n] = (float)Samples[BestStart + n] / 32768.0f;
	}

	// Hann window: w[n] = 0.5 * (1 - cos(2*pi*n/(N-1)))
	for (int32 n = 0; n < WindowSize; ++n)
	{
		const float W = 0.5f * (1.0f - FMath::Cos(2.0f * PI * (float)n / (float)(WindowSize - 1)));
		X[n] *= W;
	}

	// Magnitude spectrum at NumBins bins evenly spaced 0 .. SampleRate/2.
	// Bin k corresponds to angular freq w_k = pi * k / NumBins per sample.
	TArray<float> Magnitudes;
	Magnitudes.SetNumZeroed(NumBins);
	for (int32 k = 0; k < NumBins; ++k)
	{
		const float W = PI * (float)k / (float)NumBins;
		float Re = 0.0f, Im = 0.0f;
		for (int32 n = 0; n < WindowSize; ++n)
		{
			const float Angle = W * (float)n;
			Re += X[n] * FMath::Cos(Angle);
			Im -= X[n] * FMath::Sin(Angle);
		}
		Magnitudes[k] = FMath::Sqrt(Re * Re + Im * Im);
	}

	// Integrate band energies. Band edges: 0, 500, 1500, 3000, 8000 Hz.
	// Bin width = (SampleRate/2) / NumBins. At 16kHz / 64 bins ≈ 125 Hz/bin.
	const float NyquistHz = (float)SampleRate * 0.5f;
	const float BinHz = NyquistHz / (float)NumBins;
	auto BandIdx = [&](float Hz) -> int32
	{
		return FMath::Clamp(FMath::RoundToInt(Hz / BinHz), 0, NumBins);
	};
	const int32 BinEdges[5] = {
		BandIdx(0.0f),
		BandIdx(500.0f),
		BandIdx(1500.0f),
		BandIdx(3000.0f),
		BandIdx(FMath::Min(8000.0f, NyquistHz))
	};

	TArray<float> BandEnergies;
	BandEnergies.SetNumZeroed(4);
	for (int32 b = 0; b < 4; ++b)
	{
		for (int32 k = BinEdges[b]; k < BinEdges[b + 1]; ++k)
		{
			BandEnergies[b] += Magnitudes[k] * Magnitudes[k];
		}
	}

	// L2-normalize so cosine similarity reduces to a dot product.
	float L2 = 0.0f;
	for (float E : BandEnergies) L2 += E * E;
	L2 = FMath::Sqrt(L2) + 1e-6f;
	for (float& E : BandEnergies) E /= L2;

	return BandEnergies;
}
