#pragma once

#include "CoreMinimal.h"
#include "VisemeTypes.h"

/**
 * Rule-based grapheme → viseme mapper.
 *
 * Consumes ElevenLabs character alignment (a string of characters plus per-char
 * start/duration in seconds) and emits an FVisemeSchedule suitable for runtime
 * playback by UNPCLipSyncComponent.
 *
 * Not a real phonetic analyzer — it covers common English digraphs (th, sh,
 * ch, ph, ng) and single letters. Unknown/punctuation characters map to SIL.
 */
class LLM_NPC_API FPhonemeVisemeMapper
{
public:
	/**
	 * Map a single character (with look-ahead for digraphs) to a viseme.
	 * @param Char      The current character (case is ignored).
	 * @param NextChar  The following character for digraph lookups, or 0 if none.
	 */
	static EViseme GraphemeToViseme(TCHAR Char, TCHAR NextChar);

	/**
	 * True if the previous character and the current character form a digraph
	 * (th/sh/ch/ph/ng). Used by BuildSchedule to skip the second character of
	 * a digraph so the digraph viseme is only emitted once.
	 */
	static bool IsSecondCharOfDigraph(TCHAR PrevChar, TCHAR Char);

	/**
	 * Build a viseme schedule from ElevenLabs alignment data.
	 *
	 * @param Characters      Concatenated characters of the utterance.
	 * @param StartTimesSec   Start time of each character, in seconds.
	 * @param DurationsSec    Duration of each character, in seconds.
	 * @return A schedule where each key's TimeSec is the midpoint of its
	 *         source character, runs of identical visemes are collapsed, and
	 *         a SIL key is inserted when the inter-character gap exceeds 80 ms.
	 */
	static FVisemeSchedule BuildSchedule(
		const FString& Characters,
		const TArray<float>& StartTimesSec,
		const TArray<float>& DurationsSec);

	/**
	 * Global viseme → (curve name, target weight) table.
	 * Returns a reference to a static singleton, safe to keep by reference.
	 */
	static const TMap<EViseme, TArray<TPair<FName, float>>>& VisemeToCurves();
};
