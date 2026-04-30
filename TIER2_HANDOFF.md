# Tier 2 Handoff — Memory Archive Vertical Slice

**Status as of:** 2026-04-30 (post-demo, Tier 1 shipped clean)
**Next demo / review:** TBD
**Working branch:** `claude/continue-llm-npc-api-lwC5j` (or a fresh branch off it)
**Budgeted hours:** 2.5
**You are picking up:** Tier 2 of the 5-tier Memory Archive build order, after Tier 0 and Tier 1 landed.

---

## Required reading order (do this before writing any code)

1. **`CLAUDE.md`**, in particular:
   - `Final Review Vertical Slice — "The Memory Archive" (Two-Speaker Pivot, locked 2026-04-29)` — the canonical design doc.
   - `Memory Archive — Tier 0 complete (2026-04-29)` — what landed in Tier 0 (graph nodes, gesture wire-up, §7.5/§7.10 prompt).
   - `Memory Archive — Tier 1 complete (2026-04-30)` — exact list of what just shipped, with line refs. **Read this carefully** — Tier 2 builds directly on the per-speaker maps, the auto-voice flow, and the §7.5 visitors register that are already in place.
   - `Build order` table — confirm Tier 2 row is still `Pending`.
   - `Hard-gated topic matrix` — speaker identification is what makes the per-speaker trust thresholds meaningful. Until Tier 2 ships, every `InspectedBy`/`PresentedBy` write goes to `Speaker_A` and the per-speaker gating in Tier 3 has nothing to differentiate.
2. **`Source/LLM_NPC/Dialogue/WhisperSTTComponent.h` + `.cpp`** — Tier 1 added VAD-driven auto-segment with a `TickComponent` silence detector. The PCM buffer is already being snapshotted under `PCMLock` and dispatched to Whisper. Tier 2 needs to add a hook that broadcasts the snapshotted PCM **before** WAV encoding so a separate component can fingerprint the speaker.
3. **`Source/LLM_NPC/Dialogue/DialogueComponent.h` + `.cpp`**, especially:
   - `BuildAnnotatedContent()` — already prepends held-item, gesture, and emotion annotations. Tier 2 adds a speaker prefix at the start of this chain.
   - `RecordItemInspection(FName ItemID, FName SpeakerID)` and `SendObjectPresentMessage` — both currently take/use `GetDefaultSpeakerID()` which returns `"Speaker_A"`. Tier 2 swaps those call sites to read from the resolved acoustic tag.
   - `BuildSystemPromptFromGraph()` §7.5 Visitors register — already tells Claude to track `Speaker_A` and `Speaker_B` separately when tags are present, gracefully degrading to single-speaker when absent.
4. **`Source/LLM_NPC/Core/NPCPlayerController.h` + `.cpp`**, in particular:
   - `UpdateNPCFocus()` — auto-starts/stops `WhisperSTTComponent`. Tier 2 needs to also bind/unbind the speaker-ID component's PCM listener to the same lifecycle.
   - The Tick block where E/F/Q/LCtrl are handled — same gating pattern (text-input-active check) is where 1/2 override keys go.
5. **The Tier 1 commit on this branch** — review `git log -1 --stat` and `git diff HEAD~1` for the exact set of recent touches. The auto-voice + VAD + held-item annotation flow in particular is the load-bearing wiring Tier 2 extends.

---

## Mission summary

Ship acoustic speaker identification so the Friend can respond differently to two distinct voices in the same session, AND give the demo operator a manual override (1/2 keys) when the acoustic ID gets it wrong. By the end of Tier 2:

- Up to 2 speakers are auto-enrolled by their voice fingerprint on first utterance.
- Subsequent utterances are matched against enrolled profiles by cosine similarity (threshold 0.85). On match, the user message gets prefixed with `[Speaker_A is speaking]` or `[Speaker_B is speaking]` before reaching Claude.
- Per-speaker memory writes (`InspectedBy` / `PresentedBy`) use the resolved tag instead of the `Speaker_A` placeholder.
- The HUD shows a **speaker chip** (top-left) with the active tag + match-confidence bar.
- Pressing **1** or **2** on the keyboard force-overrides the next utterance's tag (demo safety net for noisy mics or when two operators sound similar).
- The Friend's responses audibly differentiate: the §7.5 register is already in the system prompt — once the prefix arrives, Claude has the signal it needs.

Tier 1 already proved end-to-end wiring works for typed/voice messages with `[Currently holding: ...]` and `[Player gesture: ...]` annotations. Tier 2 adds the `[Speaker_X is speaking]` prefix and the upstream component that decides which X to write.

---

## Current state inventory

### What is **already done** (do not redo)

| Item | Where | Status |
|------|-------|--------|
| `WhisperSTTComponent` VAD-driven auto-segment with 1s silence detection | `Source/LLM_NPC/Dialogue/WhisperSTTComponent.cpp` | Done — Tier 1 |
| `RecordedPCM` accumulation under `PCMLock`, snapshotted in `DispatchSegmentAndContinue()` | Same file | Done — Tier 1. The snapshot is the natural source for the PCM hook. |
| `UDialogueComponent::RecordItemInspection(FName ItemID, FName SpeakerID)` | `DialogueComponent.h/.cpp` | Done — Tier 1. Currently called with `GetDefaultSpeakerID()` returning `"Speaker_A"`. |
| `UDialogueComponent::PresentedBy.FindOrAdd(...).Add(GetDefaultSpeakerID())` inside `SendObjectPresentMessage` | `DialogueComponent.cpp:329-336` | Done — Tier 1. Same call-site swap pattern as inspection. |
| §7.5 Visitors register prompt section (Speaker_A / Speaker_B distinct registers, graceful degrade when no tag present) | `DialogueComponent.cpp:512-527` | Done — Tier 0. Already in production, just waiting for the prefix to arrive. |
| `BuildAnnotatedContent` prepends held-item → gesture → emotion → message in canonical order | `DialogueComponent.cpp:617-680` | Done — Tier 1. Speaker tag will be prepended at the very top (before held-item) so Claude reads "who" before "what they're carrying / saying". |
| `LLM_NPC.Build.cs` already lists `EnhancedInput` and `RenderCore` private deps | `Source/LLM_NPC/LLM_NPC.Build.cs` | Done. **Tier 2 must add `SignalProcessing`** (UE's FFT/audio analysis module) for spectral fingerprinting — NOT currently in deps. |
| `ANPCPlayerController::UpdateNPCFocus` calls `WhisperSTTComponent::StartRecording()` / `StopRecordingAndTranscribe()` on focus change | `NPCPlayerController.cpp` | Done — Tier 1. Same hook is where Tier 2 binds/unbinds the speaker-ID component. |
| HUD has `bDialogueVisible = false` default and toggles input mode via T key | `NPCDialogueHUD.h/.cpp` | Done — Tier 1. Tier 2 adds a draw block for the speaker chip. |

### What is **NOT yet done** (Tier 2 owns these)

| Item | Probable home | Notes |
|------|---------------|-------|
| `WhisperSTTComponent::OnPCMCaptured` delegate | `WhisperSTTComponent.h/.cpp` | Broadcast `(const TArray<int16>& Samples, int32 SampleRate)` from inside `DispatchSegmentAndContinue()` immediately before `EncodeAsWAV` — same snapshot, broadcast first then encode-and-send. The `RecordedPCM` is `TArray<uint8>` of int16 LE samples; reinterpret-cast in the broadcast or expose a typed view. |
| **NEW** `USpeakerIdentificationComponent` | `Source/LLM_NPC/Dialogue/SpeakerIdentificationComponent.h/.cpp` | Component on `ANPCCharacter` (sibling of `WhisperSTTComponent`). Computes a spectral-band-energy fingerprint from incoming PCM, manages `TArray<FSpeakerProfile>` (max 2 for the slice), exposes `OnSpeakerIdentified(FName Tag, float Confidence)` delegate. See "Open design choices" below for the fingerprint scheme. |
| `FSpeakerProfile` USTRUCT | Same component header | `FName Tag` (e.g. `Speaker_A`); `TArray<float> Centroid` (4-dim band-energy vector or 13-dim MFCC); `int32 SampleCount` (utterances accumulated into the centroid); `float LastSeenTimeSec`. |
| `[Speaker_X is speaking]` prefix in `BuildAnnotatedContent` | `DialogueComponent.cpp` | Pre-pend before held-item annotation. Get the active speaker from the same source the controller uses for the HUD chip. |
| Manual override keys 1/2 | `ANPCPlayerController::Tick` | Same edge-detection pattern as E/F/Q/LCtrl. Gated on `bTextActive == false`. Sets a controller field `OverrideSpeakerTag` (FName) consumed once on the next utterance dispatch. |
| Speaker chip on HUD | `ANPCDialogueHUD::DrawHUD` | Top-left rect, one of two states: `SPEAKER A · 0.92` / `SPEAKER B · 0.71`. Only drawn when overlay is visible. |
| `ANPCCharacter` adds `USpeakerIdentificationComponent` as default subobject | `NPCCharacter.cpp` constructor | Mirror the existing `WhisperSTTComponent` add. |
| `ANPCPlayerController::UpdateNPCFocus` binds `WhisperSTTComponent::OnPCMCaptured` to the focused NPC's `USpeakerIdentificationComponent::IdentifyFromPCM` | `NPCPlayerController.cpp` | Same bind/unbind pattern as `OnGestureDetected`. |
| `LLM_NPC.Build.cs` — add `SignalProcessing` private dependency | `Source/LLM_NPC/LLM_NPC.Build.cs` | Required for `Audio::FFFTAlgorithm`. CLAUDE.md's Tier 0 file-modified table noted this as a Tier 2 task. |

### What is **explicitly out of scope** for Tier 2

- Per-speaker trust estimate, §7.7 branch hint, §7.9 climax instruction — Tier 3.
- Closing card, consent indicator on HUD — Tier 3.
- `UMemoryArchiveLogger` — Tier 3.
- More than 2 speakers — design says "up to 4" in CLAUDE.md long-term, but for this slice cap at 2 (`Speaker_A` and `Speaker_B`). Constants in component, easy to bump later.
- Dynamic re-enrollment / forgetting / TTL — profiles persist for the PIE session, are wiped on `ClearConversationHistory`. Tier 6 (Return Statement) handles longer-term clearing.

---

## Open design choices (decide early; don't agonise)

### 1. Fingerprint scheme — spectral-band-energy vs MFCC

Both work. **CLAUDE.md design doc says spectral-band-energy** (4-dim: 0–500 / 500–1500 / 1500–3000 / 3000–8000 Hz) using UE's `Audio::FFFTAlgorithm` from the `SignalProcessing` module. **Recommendation: stick with spectral-band-energy.**

Reasons:
- Cheaper: 256-pt FFT per utterance, four band integrations, normalize by total energy → 4 floats.
- More than enough discrimination for 2 distinct speakers in a controlled demo. Cosine similarity > 0.85 reliably matches; < 0.65 reliably says "different speaker."
- MFCC is more robust to noise/channel variation but adds a mel-filterbank pass + DCT for marginal benefit when you only need to tell two operators apart.
- Fits the 2.5-hour budget. MFCC won't.

If the spectral fingerprint proves unreliable in playtest, Tier 3 can swap the fingerprint without touching anything else — `IdentifyFromPCM` is the only public API.

### 2. Auto-enrollment trigger

Two options:
- **(a)** First utterance ever → `Speaker_A`. Second utterance whose similarity to A is below the match threshold → `Speaker_B`. Subsequent utterances match against both.
- **(b)** Always enroll the first two distinct utterances within the first N seconds of the session.

**Recommendation: (a).** Simpler, doesn't need a session timer, gracefully handles the case where the same operator speaks both first utterances (similarity stays high, no `Speaker_B` is ever created until a genuinely different voice arrives).

### 3. Cosine similarity threshold

Design doc says `0.85`. **Use that as default**, expose as a UPROPERTY (`MatchThreshold`) so it can be tuned in editor.

For dissimilar speakers (different gender / strong pitch difference), 0.85 is conservative — matches will be ~0.92+. For similar speakers (same gender, similar register), you may need to drop to 0.75 to avoid spurious `Speaker_B` enrollments. Test with the actual demo operators.

### 4. Where the speaker tag lives between identification and prompt assembly

Two options:
- **(a)** `USpeakerIdentificationComponent` exposes a `LastIdentifiedSpeaker` field. Controller reads it when dispatching the user message.
- **(b)** Component fires `OnSpeakerIdentified` delegate, controller caches the tag in `PendingSpeakerTag` field (mirrors existing `PendingGestureIntent`), HUD pulls it from the controller for the chip + threading into `SendUserMessage`.

**Recommendation: (b).** Mirrors the proven Tier 1 pattern for gesture intent and held item. The controller is already the single source of truth for "current input context."

Add `FName PendingSpeakerTag = NAME_None;` to `ANPCPlayerController` next to `PendingGestureIntent`. Cleared on consume, just like gesture.

### 5. Manual override semantics

User presses **1** while in NPC vicinity → next utterance gets tagged `Speaker_A` regardless of acoustic match. Same for **2** → `Speaker_B`. Override is consumed on next dispatch, not sticky.

Edge case: user presses 1, never speaks, walks away. The override clears on focus loss (free to do; mirrors `PendingGestureIntent` reset in `UpdateNPCFocus`).

---

## Per-speaker memory data shape

`UDialogueComponent` already has the maps. **Do not change shapes.** Tier 2 just changes the SpeakerID source from `GetDefaultSpeakerID()` to the resolved tag.

```cpp
// Already in place from Tier 1 — DO NOT touch:
TMap<FName, TSet<FName>> InspectedBy;
TMap<FName, TSet<FName>> PresentedBy;
void RecordItemInspection(FName ItemID, FName SpeakerID);  // unchanged signature
static FName GetDefaultSpeakerID();  // returns "Speaker_A" — KEEP for fallback
```

**What changes in Tier 2:**

- In `ANPCPlayerController::PickupItem`, replace `UDialogueComponent::GetDefaultSpeakerID()` with the resolved tag pulled from `USpeakerIdentificationComponent::GetActiveSpeakerTag()` or `PendingSpeakerTag` (whichever you wire). Fall back to `GetDefaultSpeakerID()` if the speaker-ID component is unavailable or hasn't identified anyone yet.
- In `UDialogueComponent::SendObjectPresentMessage`, the `PresentedBy.FindOrAdd(...).Add(GetDefaultSpeakerID())` line gets the same swap.
- New: in `BuildAnnotatedContent`, pre-pend `[Speaker_A is speaking]` or `[Speaker_B is speaking]` (or omit entirely when no tag is resolved — the §7.5 prompt already handles the missing-tag case).

---

## Suggested order of operations

1. **PCM hook in WhisperSTT (~20 min).** Add `FOnPCMCaptured` delegate. Broadcast inside `DispatchSegmentAndContinue` right before `EncodeAsWAV`. Compile. Verify with a temp `UE_LOG` that fires when each segment dispatches with the correct sample count. Risk-free — doesn't change any existing behavior.

2. **`USpeakerIdentificationComponent` skeleton (~30 min).** Header with `FSpeakerProfile`, public `IdentifyFromPCM(const TArray<int16>&, int32 SampleRate)`, `OnSpeakerIdentified` delegate, `MatchThreshold` UPROPERTY (default 0.85), `MaxSpeakers` UPROPERTY (default 2). Empty bodies — just compile. Add `SignalProcessing` to `LLM_NPC.Build.cs`. Compile.

3. **Spectral fingerprint impl (~45 min).** In `IdentifyFromPCM`:
   - Convert int16 PCM → float [-1, 1] (just `samples[i] / 32768.0f`).
   - Window the first ~1 second (16000 samples) — pad with zeros if shorter, take first 16000 if longer.
   - Take 256-pt FFT chunks, sum magnitude over each. Or do one FFT of a Hann-windowed full segment.
   - Integrate magnitude over the 4 frequency bands; normalize by total energy → 4-element centroid.
   - Compare via cosine similarity to existing profiles. Match if best > `MatchThreshold`. Otherwise enroll new profile if `Profiles.Num() < MaxSpeakers`. Fallback to `Speaker_A` if max reached.
   - Fire `OnSpeakerIdentified(MatchedTag, BestSimilarity)`.
   - Use `Audio::FFFTAlgorithm::Create` from `SignalProcessing`. There's a UE example in `Engine/Plugins/AudioCapture` if you need a reference.

4. **Wire it up (~20 min).** `ANPCCharacter` constructor adds the new component. `ANPCPlayerController::UpdateNPCFocus` binds `WhisperSTTComponent::OnPCMCaptured` → `USpeakerIdentificationComponent::IdentifyFromPCM` on focus gain, and `OnSpeakerIdentified` → controller's `OnSpeakerIdentified` (caches `PendingSpeakerTag`). Unbind on focus loss. Mirror the existing gesture-bind pattern.

5. **`[Speaker_X]` prefix in BuildAnnotatedContent (~10 min).** Add an FName `SpeakerTag` parameter to `BuildAnnotatedContent` (defaults to `NAME_None`). If set, prepend `[Speaker_X is speaking]\n` at the top of the prefix. Update both `SendUserMessage` and `SendObjectPresentMessage` to thread the tag through. HUD's `SubmitChatMessage` pulls `PC->PendingSpeakerTag` and consumes it (set to `NAME_None`) the same way it consumes gesture.

6. **Per-speaker map writes use real tag (~5 min).** Find the two call sites of `GetDefaultSpeakerID()` (one in controller's `PickupItem`, one in `SendObjectPresentMessage`). Replace with the resolved tag, falling back to `GetDefaultSpeakerID()` when null.

7. **Manual 1/2 override (~10 min).** In Tick, after the LCtrl block, two press-edge handlers (`b1KeyWasDown` / `b2KeyWasDown`). On press, set `PendingSpeakerTag = "Speaker_A"` or `"Speaker_B"`. Gated on `!bTextActive`.

8. **HUD speaker chip (~20 min).** New `DrawHUD` block top-left, ~150×30 px panel, draws `SPEAKER A · 0.92` (tag from controller's last-identified, similarity from same source). Hide when overlay is hidden. Match the existing dialogue panel's color palette.

9. **Smoke test (~30 min, mostly two operators speaking).** Two distinct voices PIE-test:
   - First utterance → `Speaker_A` enrolled; chip shows `SPEAKER A`.
   - Second voice speaks → `Speaker_B` enrolled; chip flips.
   - First voice speaks again → re-matched as `Speaker_A`; chip flips back.
   - Press **2** before speaking → next utterance forced to `Speaker_B` regardless of voice.
   - Verify Output Log shows `[Speaker_X]` in the user message body sent to Claude.
   - Pick up Letter, present (F): log line should show the active speaker writing to `PresentedBy[letter]`.
   - Verify the Friend's response treats Speaker_A and Speaker_B differently per §7.5 — slower / less defended for A, more pressed for B.

---

## Cut order if you fall behind

If Tier 2 is overrunning, cut in this order (per CLAUDE.md):

1. **First to drop:** acoustic fingerprint. Ship manual-only — keys 1 and 2 are the speaker selector. The Friend still gets `[Speaker_A is speaking]` / `[Speaker_B is speaking]` in her context; just no automatic ID. The §7.5 register still produces differentiated responses.
2. **Second:** speaker chip on HUD. Trust+verify via Output Log instead.
3. **Third:** auto-enrollment. Hard-code that key 1 enrolls Speaker_A and key 2 enrolls Speaker_B at first press; afterward they just toggle.

**Never cut:** the `[Speaker_X is speaking]` prefix actually reaching `BuildAnnotatedContent`. That is the single keystone for Tier 3's per-speaker trust math — without per-utterance tags, Tier 3 has nothing to differentiate.

---

## Verification at the end of the session

Before pausing for handoff, smoke-check in PIE on the work machine with **two distinct operator voices** (or one operator + a phone playing pre-recorded audio):

- [ ] PIE → walk near Friend → Output Log shows `WhisperSTT[VAD]` segment dispatches AND `SpeakerIdentification: enrolled Speaker_A` after the first utterance.
- [ ] Speak with the second voice → Output Log shows `enrolled Speaker_B` (not re-identified as A).
- [ ] First voice speaks again → log shows `matched Speaker_A (similarity 0.9x)`, NOT a third enrollment.
- [ ] HUD chip shows the right tag + a similarity bar that varies between matches.
- [ ] Press **2**, then speak → log shows `manual override -> Speaker_B`. Chip flips.
- [ ] Pick up an item with Speaker_A active → `DialogueComponent: <item> inspected by Speaker_A` log line.
- [ ] Pick up the same item with Speaker_B active → `inspected by Speaker_B` log line. The `InspectedBy[<item>]` set now has both members.
- [ ] Present an item to the Friend with Speaker_A active → her response should land in the Speaker_A register (slower, less defended).
- [ ] Present a different item with Speaker_B active → response in Speaker_B register (presses more, feels the weight).
- [ ] Quit PIE, restart, repeat one cycle to confirm profiles cleanly re-enroll (no stale state).

If any of these fail, leave a clear note at the top of this file (or a new `TIER2_STATUS.md`) describing what works, what doesn't, and where the next session should resume.

---

## Constraints

- **Platform:** Windows 11. Speaker-ID work uses UE's `SignalProcessing` module which is cross-platform; no platform-specific code paths needed.
- **Engine:** UE 5.7. `Audio::FFFTAlgorithm` API exists in 5.7. Don't pull in anything from the experimental `MetaSound` plugin — `SignalProcessing` is the stable path.
- **No new microphone capture.** Tier 1's `WhisperSTTComponent` is already capturing at 16 kHz mono int16 — that's exactly what spectral fingerprinting wants. Just hook the existing buffer.
- **Build environment:** the user is on Visual Studio 2026 Insiders toolchain. Tier 1 had recurring "Live Coding active" build blocks — close the editor fully before VS builds, and don't expect Live Coding to handle new UPROPERTYs / UCLASS / new components. Full close + Build LLM_NPC + reopen for any structural change.
- **Don't merge Tier 3 work into Tier 2.** Tier 3 (per-speaker trust math, branch hint, climax instruction, logger, closing card) lives in its own session. Tier 2's job is just: enrol speakers, prefix messages, write per-speaker memory with the resolved tag.

---

## Reference: where Tier 1 left things plumbed

- **`PendingGestureIntent` / `GetHeldItem()` pattern** on `ANPCPlayerController` — Tier 2's `PendingSpeakerTag` should mirror this exactly. Cached on the controller, consumed once on dispatch, cleared on focus loss.
- **`OnTranscriptReady` → `HUD::SubmitChatMessage` → `SendUserMessage`** flow — Tier 2's speaker tag rides this same pipe, threaded through HUD just like gesture and held item.
- **`OnPCMCaptured` is the new fork point** — it broadcasts the same PCM blob that's about to be encoded for Whisper. Tier 2's speaker-ID component runs in parallel on that blob; Whisper still gets its WAV. Two independent listeners on the same audio.
- **§7.5 Visitors register prompt** is in production from Tier 0 and gracefully degrades to single-speaker when no tag is present. The moment Tier 2's prefix arrives, the prompt section starts working without any further prompt edits.

---

## When you finish (or when time runs out)

1. Commit cleanly with a message like `tier 2: acoustic speaker ID + 1/2 override + speaker chip + per-speaker memory writes`.
2. Update `CLAUDE.md`'s build-order table — change Tier 2's `Status` cell to `Complete (date)` or `Partial — see TIER2_STATUS.md`.
3. Add a `Memory Archive — Tier 2 complete (date)` block under the existing Tier 1 block in `CLAUDE.md`, mirroring the format with line-ref links to the changes.
4. Write `TIER3_HANDOFF.md` if a fourth session will pick up Tier 3.
5. Tell the user what works, what doesn't, and what the smoke test showed — particularly with the two-voice operator setup, since that's hard to PIE-test without two real people.

The slice already demos coherently from end of Tier 1 (single speaker treated as `Speaker_A`). Tier 2 turns on the actual two-voice differentiation. Land it cleanly first; everything past it is upside.
