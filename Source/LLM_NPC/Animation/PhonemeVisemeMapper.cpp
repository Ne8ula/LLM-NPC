#include "PhonemeVisemeMapper.h"

namespace
{
	constexpr float GDigraphSilenceGapSec = 0.080f;

	/**
	 * Co-articulation: bilabial closure visemes (PP) and labiodental closures
	 * (FF) are pushed BACKWARDS in time so the lips begin closing during the
	 * preceding vowel, rather than at the literal moment the consonant is
	 * pronounced. Without this, ElevenLabs's tight 30–50 ms consonant
	 * durations don't give the smoothing layer enough time to fully close
	 * the lips before the next vowel pulls them open again.
	 */
	constexpr float GClosureAnticipationSec = 0.050f;

	FORCEINLINE TCHAR ToLowerChar(TCHAR C)
	{
		return FChar::ToLower(C);
	}

	FORCEINLINE bool IsClosureViseme(EViseme V)
	{
		return V == EViseme::PP || V == EViseme::FF;
	}
}

EViseme FPhonemeVisemeMapper::GraphemeToViseme(TCHAR Char, TCHAR NextChar)
{
	const TCHAR C = ToLowerChar(Char);
	const TCHAR N = ToLowerChar(NextChar);

	// Digraphs — look ahead one character.
	if (C == TEXT('t') && N == TEXT('h')) return EViseme::TH;
	if (C == TEXT('s') && N == TEXT('h')) return EViseme::CH;   // "sh" → CH viseme
	if (C == TEXT('c') && N == TEXT('h')) return EViseme::CH;
	if (C == TEXT('p') && N == TEXT('h')) return EViseme::FF;   // "ph" → FF
	if (C == TEXT('n') && N == TEXT('g')) return EViseme::NN;   // "ng" → NN

	// Single letters.
	switch (C)
	{
		case TEXT('p'): case TEXT('b'): case TEXT('m'):
			return EViseme::PP;

		case TEXT('f'): case TEXT('v'):
			return EViseme::FF;

		case TEXT('t'): case TEXT('d'): case TEXT('l'):
			return EViseme::DD;

		case TEXT('k'): case TEXT('g'): case TEXT('c'): case TEXT('q'): case TEXT('x'):
			return EViseme::KK;

		case TEXT('j'):
			return EViseme::CH;

		case TEXT('s'): case TEXT('z'):
			return EViseme::SS;

		case TEXT('n'):
			return EViseme::NN;

		case TEXT('r'):
			return EViseme::RR;

		case TEXT('a'):
			return EViseme::AA;

		case TEXT('e'):
			return EViseme::E;

		case TEXT('i'): case TEXT('y'):
			return EViseme::IH;

		case TEXT('o'):
			return EViseme::OH;

		case TEXT('u'): case TEXT('w'):
			return EViseme::OU;

		case TEXT('h'):
			// Lone 'h' is mostly breathy — treat as a mild open vowel.
			return EViseme::AA;

		default:
			return EViseme::SIL;
	}
}

bool FPhonemeVisemeMapper::IsSecondCharOfDigraph(TCHAR PrevChar, TCHAR Char)
{
	const TCHAR P = ToLowerChar(PrevChar);
	const TCHAR C = ToLowerChar(Char);

	if (C == TEXT('h'))
	{
		return P == TEXT('t') || P == TEXT('s') || P == TEXT('c') || P == TEXT('p');
	}
	if (C == TEXT('g') && P == TEXT('n'))
	{
		return true;
	}
	return false;
}

FVisemeSchedule FPhonemeVisemeMapper::BuildSchedule(
	const FString& Characters,
	const TArray<float>& StartTimesSec,
	const TArray<float>& DurationsSec)
{
	FVisemeSchedule Schedule;

	const int32 Count = Characters.Len();
	if (Count == 0 || StartTimesSec.Num() != Count || DurationsSec.Num() != Count)
	{
		return Schedule;
	}

	Schedule.Keys.Reserve(Count);

	TCHAR PrevChar = 0;
	EViseme LastEmittedViseme = EViseme::SIL;
	float LastEmittedEndTime = 0.0f;

	for (int32 i = 0; i < Count; ++i)
	{
		const TCHAR Char = Characters[i];
		const TCHAR NextChar = (i + 1 < Count) ? Characters[i + 1] : TEXT('\0');

		const float Start = StartTimesSec[i];
		const float Duration = FMath::Max(0.0f, DurationsSec[i]);
		const float Mid = Start + (Duration * 0.5f);
		const float End = Start + Duration;

		// Skip the second character of a digraph — its viseme was already
		// emitted on the previous iteration.
		if (IsSecondCharOfDigraph(PrevChar, Char))
		{
			PrevChar = Char;
			LastEmittedEndTime = FMath::Max(LastEmittedEndTime, End);
			continue;
		}

		const EViseme V = GraphemeToViseme(Char, NextChar);

		// Insert a SIL key if there's a noticeable gap since the last voiced key.
		if (Schedule.Keys.Num() > 0
			&& V != EViseme::SIL
			&& (Start - LastEmittedEndTime) > GDigraphSilenceGapSec)
		{
			const float SilTime = LastEmittedEndTime + 0.5f * (Start - LastEmittedEndTime);
			Schedule.Keys.Add(FVisemeKey(SilTime, EViseme::SIL, 1.0f));
			LastEmittedViseme = EViseme::SIL;
		}

		// Collapse runs of the same viseme — bump the existing key's end time
		// instead of appending a duplicate.
		if (V == LastEmittedViseme && Schedule.Keys.Num() > 0)
		{
			LastEmittedEndTime = FMath::Max(LastEmittedEndTime, End);
			PrevChar = Char;
			continue;
		}

		// Anticipatory co-articulation: closure visemes start forming during
		// the preceding vowel. Pull the keyframe back in time, but never
		// before the previously-emitted key (otherwise we'd reorder).
		float KeyTime = Mid;
		if (IsClosureViseme(V))
		{
			KeyTime = FMath::Max(0.0f, Mid - GClosureAnticipationSec);
			if (Schedule.Keys.Num() > 0)
			{
				const float MinTime = Schedule.Keys.Last().TimeSec + 0.005f;
				KeyTime = FMath::Max(KeyTime, MinTime);
			}
		}

		Schedule.Keys.Add(FVisemeKey(KeyTime, V, 1.0f));
		LastEmittedViseme = V;
		LastEmittedEndTime = End;
		PrevChar = Char;
	}

	if (StartTimesSec.Num() > 0)
	{
		const float LastStart = StartTimesSec.Last();
		const float LastDuration = FMath::Max(0.0f, DurationsSec.Last());
		Schedule.TotalDuration = LastStart + LastDuration;
	}

	// Append a trailing SIL so the mouth closes cleanly at the end.
	if (Schedule.Keys.Num() > 0 && Schedule.Keys.Last().Viseme != EViseme::SIL)
	{
		Schedule.Keys.Add(FVisemeKey(Schedule.TotalDuration, EViseme::SIL, 1.0f));
	}

	return Schedule;
}

const TMap<EViseme, TArray<TPair<FName, float>>>& FPhonemeVisemeMapper::VisemeToCurves()
{
	static TMap<EViseme, TArray<TPair<FName, float>>> Table;
	static bool bBuilt = false;
	if (bBuilt)
	{
		return Table;
	}
	bBuilt = true;

	// Curve names match the MetaHuman Face AnimBP's CTRL_expressions_* FACS
	// controls discovered via UAnimInstance::GetAllCurveNames() at init time.
	// This particular MetaHuman exposes a slim set of 13 mouth controls — we
	// have jawOpen, lip stretch, corner pull, lips-together (closure),
	// upper-lip raise, and lower-lip depress, but no funnel or pucker. The
	// table approximates rounded-mouth visemes (OH/OU) using lipsTogether +
	// reduced jaw rather than a true pucker.

	const FName JawOpen          = FName("CTRL_expressions_jawOpen");
	const FName StretchL         = FName("CTRL_expressions_mouthStretchL");
	const FName StretchR         = FName("CTRL_expressions_mouthStretchR");
	const FName CornerPullL      = FName("CTRL_expressions_mouthCornerPullL");
	const FName CornerPullR      = FName("CTRL_expressions_mouthCornerPullR");
	const FName LipsTogetherUL   = FName("CTRL_expressions_mouthLipsTogetherUL");
	const FName LipsTogetherUR   = FName("CTRL_expressions_mouthLipsTogetherUR");
	const FName LipsTogetherDL   = FName("CTRL_expressions_mouthLipsTogetherDL");
	const FName LipsTogetherDR   = FName("CTRL_expressions_mouthLipsTogetherDR");
	const FName UpperLipRaiseL   = FName("CTRL_expressions_mouthUpperLipRaiseL");
	const FName UpperLipRaiseR   = FName("CTRL_expressions_mouthUpperLipRaiseR");
	const FName LowerLipDepressL = FName("CTRL_expressions_mouthLowerLipDepressL");
	const FName LowerLipDepressR = FName("CTRL_expressions_mouthLowerLipDepressR");

	Table.Add(EViseme::SIL, {});

	// Calibrated for natural conversational speech: jaw rarely exceeds ~0.45.
	// Closure curves (LipsTogether*) stay near 1.0 because they need to
	// fully shut the mouth to read visually — they get asymmetric smoothing
	// in NPCLipSyncComponent (fast attack, slow decay) so they actually
	// register before the next vowel pulls the lips back open.

	// PP (p, b, m) — full lip closure. Jaw stays neutral.
	Table.Add(EViseme::PP, {
		{LipsTogetherUL, 1.00f}, {LipsTogetherUR, 1.00f},
		{LipsTogetherDL, 1.00f}, {LipsTogetherDR, 1.00f},
	});

	// FF (f, v) — lower lip tucks under upper teeth.
	Table.Add(EViseme::FF, {
		{UpperLipRaiseL, 0.40f}, {UpperLipRaiseR, 0.40f},
		{LipsTogetherDL, 0.65f}, {LipsTogetherDR, 0.65f},
	});

	// TH (th) — the visible part of "th" is the tongue, which we have no
	// control for. The lips/jaw barely change between vowel→TH→vowel in
	// real speech, so we use a value close to the average vowel range so
	// the consonant looks like a slight pause in the vowel motion instead
	// of dipping into a distinct narrow pose. Removed lowerLipDepress
	// because that lip drop was the source of the "popping in/out" feel.
	Table.Add(EViseme::TH, {
		{JawOpen,             0.20f},
	});

	// DD (t, d, n, l) — same reasoning as TH: stay close to vowel range
	// so brief consonant transitions don't look like jaw dips.
	Table.Add(EViseme::DD, {
		{JawOpen,             0.18f},
	});

	// KK (k, g) — back-of-mouth consonant. Slightly more opening than TH/DD
	// because there's a real (small) jaw drop on real K/G sounds.
	Table.Add(EViseme::KK, {
		{JawOpen,             0.22f},
	});

	// CH (ch, sh, j) — partial closure with mild raise.
	Table.Add(EViseme::CH, {
		{LipsTogetherUL, 0.55f}, {LipsTogetherUR, 0.55f},
		{LipsTogetherDL, 0.55f}, {LipsTogetherDR, 0.55f},
		{UpperLipRaiseL, 0.15f}, {UpperLipRaiseR, 0.15f},
	});

	// SS (s, z) — narrow mouth with stretched corners. Bumped jaw a touch
	// so the SS doesn't drop the jaw to almost-zero between vowels (which
	// caused the "popping shut and back open" feel).
	Table.Add(EViseme::SS, {
		{StretchL,    0.40f}, {StretchR,    0.40f},
		{CornerPullL, 0.22f}, {CornerPullR, 0.22f},
		{JawOpen,     0.14f},
	});

	// NN (n, ng) — minimal-shape consonant. Stay near vowel jaw range.
	Table.Add(EViseme::NN, {
		{JawOpen,             0.16f},
	});

	// RR (r) — approximate R with partial closure and slight jaw. We keep
	// the closure here because the lip rounding IS visually distinctive
	// for an R sound, but the value is small so it reads as a hint not a pose.
	Table.Add(EViseme::RR, {
		{JawOpen,        0.16f},
		{LipsTogetherUL, 0.22f}, {LipsTogetherUR, 0.22f},
		{LipsTogetherDL, 0.22f}, {LipsTogetherDR, 0.22f},
	});

	// AA (a) — most open vowel. Was 0.85, way too cartoonish for speech.
	Table.Add(EViseme::AA, {
		{JawOpen,             0.42f},
		{LowerLipDepressL,    0.30f}, {LowerLipDepressR, 0.30f},
	});

	// E (e) — medium-narrow open, mild stretch.
	Table.Add(EViseme::E, {
		{JawOpen,     0.26f},
		{StretchL,    0.30f}, {StretchR,    0.30f},
		{CornerPullL, 0.18f}, {CornerPullR, 0.18f},
	});

	// IH (i, y) — narrow open, wider stretch.
	Table.Add(EViseme::IH, {
		{JawOpen,     0.10f},
		{StretchL,    0.45f}, {StretchR,    0.45f},
		{CornerPullL, 0.30f}, {CornerPullR, 0.30f},
	});

	// OH (o) — moderate open, partial round (faked via lipsTogether).
	Table.Add(EViseme::OH, {
		{JawOpen,        0.30f},
		{LipsTogetherUL, 0.25f}, {LipsTogetherUR, 0.25f},
		{LipsTogetherDL, 0.25f}, {LipsTogetherDR, 0.25f},
	});

	// OU (u, w) — partial closure approximating a pucker.
	Table.Add(EViseme::OU, {
		{JawOpen,        0.10f},
		{LipsTogetherUL, 0.65f}, {LipsTogetherUR, 0.65f},
		{LipsTogetherDL, 0.65f}, {LipsTogetherDR, 0.65f},
	});

	return Table;
}
