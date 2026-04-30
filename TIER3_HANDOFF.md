# Tier 3 Handoff — Memory Archive Vertical Slice

**Status as of:** 2026-04-30 (post-Tier-2, single-speaker demo path verified end-to-end)
**Next demo / review:** TBD
**Working branch:** `claude/continue-llm-npc-api-lwC5j` (or a fresh branch off it)
**Budgeted hours:** 3
**You are picking up:** Tier 3 of the 5-tier Memory Archive build order, after Tier 0, Tier 1, and Tier 2 landed.

---

## Required reading order (do this before writing any code)

1. **`CLAUDE.md`**, in particular:
   - `Final Review Vertical Slice — "The Memory Archive" (Two-Speaker Pivot, locked 2026-04-29)` — the canonical design doc.
   - `Memory Archive — Tier 0 / Tier 1 / Tier 2 complete` blocks — what landed in each tier with line refs. **Tier 2 in particular:** the speaker-tag plumbing and per-speaker memory writes are what your trust math reads from.
   - `Build order` table — confirm Tier 3 row is still `Pending`.
   - `Hard-gated topic matrix` — defines the per-speaker trust thresholds and item gates that Tier 3 implements.
   - `Three branches` (Convergent Disclosure / Divergent Fragmentation / Recursive Silence) — Tier 3 implements the climax architecture that picks among these.
2. **`Source/LLM_NPC/Dialogue/DialogueComponent.h` + `.cpp`**, in particular:
   - `TMap<FName, TSet<FName>> InspectedBy` and `PresentedBy` — the per-speaker memory maps Tier 1 set up. Tier 3 reads these in C++ to compute trust + branch eligibility.
   - `BuildSystemPromptFromGraph()` — already assembles 10+ sections including §7.5 (Visitors register) and §7.10 (Apparatus + Soft Doubt). Tier 3 inserts §7.7 (branch-eligibility hint) and §7.9 (climax instruction) into this assembly.
   - `BuildAnnotatedContent()` — already prepends `[Speaker_X is speaking]`, `[Currently holding: ...]`, gesture, emotion. No changes needed here.
3. **`Source/LLM_NPC/Dialogue/SpeakerIdentificationComponent.h` + `.cpp`** — Tier 2's component. `LastIdentifiedTag` and `Profiles` are accessible via getters. Trust math doesn't need to dig into here, but the per-speaker memory it produces is what trust reads.
4. **`Source/LLM_NPC/Core/NPCDialogueHUD.h` + `.cpp`** — Tier 2 added a top-left speaker chip. Tier 3 adds:
   - Top-bar archive frame (`ARCHIVE LINK ACTIVE | SUBJECT: Ashley Wei [posthumous reconstruction, no consent] | TESTIMONY: The Friend [consent: GRANTED]`).
   - Closing card overlay (6 second hold).
   - Consent-flip animation (GRANTED → REVOKED on Recursive-Silence branch).
5. **The Tier 2 commit on this branch** — `git log -1 --stat` and `git diff HEAD~1`. Speaker tagging, per-speaker memory writes, the §7.5 register, and the [Speaker_X] prefix are the load-bearing wiring Tier 3 extends.

---

## Mission summary

Ship the climax architecture so the Memory Archive resolves into one of three branches based on per-speaker trust, item interactions, and gesture intent. By the end of Tier 3:

- **Per-speaker trust** is computed each turn from a small C++ helper reading `InspectedBy` / `PresentedBy` + recent dialogue / emotion engagement. Trust is a float in [0, 1] per speaker (`Speaker_A`, `Speaker_B`).
- **§7.7 branch-eligibility hint** prepends a structured observation block to the system prompt each turn: turn counts per speaker, items inspected/presented per speaker, current per-speaker trust estimates, gesture-intent rolling averages, climax-eligibility flag for each branch. Claude sees the structured numbers and makes the climax call when ready.
- **§7.9 climax instruction** appended to the system prompt: when climax is eligible (per §7.7), Claude is allowed to deliver the keystone topic, switch into the branch's tonal target, and emit a closing-card-eligible final line.
- **Three branches** resolve from this shared signal:
  - **Convergent Disclosure** — both speakers' trust ≥ 0.5, keystones inspected and at least one presented in coordinated order.
  - **Divergent Fragmentation** *(LLM-novel)* — speakers reached trust at different times, contradictory tonal registers; Friend addresses each by name.
  - **Recursive Silence** *(speculative-design core)* — sustained Pinch-Withhold or one speaker silent or climax window expired without item gates; Friend revokes consent.
- **Closing card** overlays the screen for 6 seconds at branch resolution: dynamic last line + fixed provocation `When the model of a witness withdraws consent, what testimony remains?` + run-determined branch label.
- **HUD top bar + consent indicator** — archive instrument framing always visible during overlay; the `[consent: GRANTED]` segment flips to `[consent: REVOKED]` (with archive link greying) on Recursive-Silence.
- **`UMemoryArchiveLogger`** — per-turn JSONL written to `Saved/MemoryArchive/session-{timestamp}.jsonl` + Markdown transcript on session end. Captures: speaker, gesture, emotion, interaction type, per-speaker items, per-speaker trust, branch hint, full Claude payload + response. Empirical layer for future user studies.

For the **single-speaker demo** (the locked-in scope per 2026-04-30), Convergent Disclosure is the natural target: one user, all gates against `Speaker_A`'s trust + memory. Divergent and Recursive Silence are still architecturally intact (and triggerable via 1/2 manual override + Pinch gesture chains) but Convergent is what the demo will hit.

---

## Current state inventory

### What is **already done** (do not redo)

| Item | Where | Status |
|------|-------|--------|
| Per-speaker memory maps `InspectedBy` / `PresentedBy` | `DialogueComponent.h/.cpp` | Done — Tier 1, Tier 2 made writes use the resolved tag |
| Acoustic speaker ID with manual override + chip on HUD | `SpeakerIdentificationComponent.h/.cpp`, `NPCPlayerController.h/.cpp`, `NPCDialogueHUD.cpp` | Done — Tier 2 |
| `[Speaker_X is speaking]` prefix in `BuildAnnotatedContent` | `DialogueComponent.cpp` | Done — Tier 2 |
| §7.5 Visitors register + §7.10 Apparatus + Soft Doubt prompt sections | `DialogueComponent.cpp BuildSystemPromptFromGraph` | Done — Tier 0 |
| Friend graph node text (WithheldTruth, MisrememberedDetail, ReflectionAspect, HiddenTitle) | `Content/THRESHOLD/DA_Graph_ThresholdDefault.uasset` | Done — Tier 0/1 |
| `EGestureIntent` cached in `ANPCPlayerController::PendingGestureIntent`, threaded into Claude turns | `NPCPlayerController.h/.cpp`, `NPCDialogueHUD.cpp`, `DialogueComponent.cpp` | Done — Tier 0/1 |
| Hard-gated topic matrix design | `CLAUDE.md` | Designed but NOT enforced in C++ — Tier 3 owns enforcement (or hands the structured signals to Claude via §7.7 to enforce conversationally) |

### What is **NOT yet done** (Tier 3 owns these)

| Item | Probable home | Notes |
|------|---------------|-------|
| Per-speaker trust estimator | NEW helper, probably in `DialogueComponent.cpp` static helpers OR a separate `Source/LLM_NPC/Core/MemoryArchiveTrust.h/.cpp` | Read `InspectedBy[item].Contains(speaker)` count, `PresentedBy[item].Contains(speaker)` count, recent gesture-intent distribution, recent emotion engagement. Output `float TrustForSpeaker(FName SpeakerID)`. Smoothed across turns to avoid jitter. |
| §7.7 branch-eligibility hint | New section in `BuildSystemPromptFromGraph()` | Structured observation block: per-speaker turn counts, items inspected/presented per speaker, trust per speaker, gesture rolling averages, branch-eligible flags. Plain text Claude can read; deterministic — no LLM in this step. Gated on a `bDeterministicBranchHint` bool UPROPERTY (default true) so it can be A/B-tested against a no-hint baseline. |
| §7.9 climax instruction | Same `BuildSystemPromptFromGraph()` | Conditional block: when any branch's eligibility flag is set, append instructions telling Claude she may now deliver the keystone topic and emit a final line that fits the branch's tone. When NO branch is eligible, this section is omitted. |
| Branch resolution | New: `EArchiveBranch` enum + state on `DialogueComponent` or a session-level component | When Claude's response fires `OnDialogueResponseReceived` with a "this is the climax" signal (e.g. Claude returns a special `branch_resolution` field in its JSON, OR the response text matches a heuristic), resolve which branch and broadcast `OnBranchResolved`. Closing card listens. |
| Closing card UI | `NPCDialogueHUD::DrawHUD` | 6-second hold. Two-layer: dynamic Friend's last line on top, fixed provocation `When the model of a witness withdraws consent, what testimony remains?` below. Branch label (Convergent / Divergent / Recursive Silence) as smaller text. Drawn over a darkened overlay. |
| Consent indicator on HUD top bar | `NPCDialogueHUD::DrawHUD` | Always-visible top bar: `ARCHIVE LINK ACTIVE | SUBJECT: Ashley Wei [posthumous reconstruction, no consent] | TESTIMONY: The Friend [consent: GRANTED]`. On Recursive-Silence, flip the trailing tag to `[consent: REVOKED]`, grey the line, fade. |
| **NEW** `UMemoryArchiveLogger` | `Source/LLM_NPC/Core/MemoryArchiveLogger.h/.cpp` | `UGameInstanceSubsystem`. Per-turn write to `Saved/MemoryArchive/session-{timestamp}.jsonl`: full structured row (speaker, gesture, emotion, interaction type, per-speaker items, per-speaker trust, branch hint, full Claude system+user+response). On session end, also export a human-readable Markdown transcript for portfolio/study use. |

### What is **explicitly out of scope** for Tier 3

- HUD aesthetic polish (scanline PP material, archive console prop, hand wireframe) — Tier 4.
- Multi-NPC scope — single Friend remains the only NPC for this slice. Tier 2's `bAutoStartOnInit = true` mic path assumes single-NPC.
- More than 2 speakers — `MaxSpeakers = 2` stays for the slice.
- Full trust math overhaul if Claude's existing soft-doubt behavior already produces credible climax pacing without §7.7. Ship the cheapest version that demos correctly; let Claude make the call where possible.
- Real-time spectral fingerprint upgrade (`Audio::FFFTAlgorithm`) — Tier 2's hand-rolled DFT is enough.

---

## Open design choices (decide early; don't agonise)

### 1. Trust signal — how much C++ math vs how much LLM judgment

Two options:
- **(a)** C++ computes trust as a continuous float per speaker, deterministically. §7.7 prepends the numeric values to the system prompt. Claude reads "Speaker_A trust: 0.62" and uses §7.10's soft-doubt threshold (currently text-prompted at 0.3 / 0.4 / 0.5 / 0.6) to drop into the topic gates.
- **(b)** Skip the trust float. C++ just dumps the raw signals (item counts, gesture rolling averages, turn count) into §7.7. Claude infers trust on its own from those signals.

**Recommendation: (a)**. Cheap to compute, deterministic, and the existing Hard-gated topic matrix in CLAUDE.md is already specified in trust thresholds. Wiring those thresholds to a deterministic float is more reliable than asking Claude to keep track. Falls back to (b) if the math turns out brittle in playtest.

Trust formula skeleton:
```
trust(speaker) = clamp01(
  0.10 * (count of items InspectedBy that speaker)         // up to 0.7 across all 7 items
  + 0.15 * (count of items PresentedBy that speaker)        // up to ~1.05 across 7 items, capped
  + 0.05 * (turns spoken by this speaker)                   // accumulates with conversation
  - 0.10 * (count of recent Pinch/Withhold gestures)        // skepticism reduces trust
  - 0.05 * (turns since last engagement)                    // decays with silence
)
```
Tune on playtest. Only used as Claude's hint — not as a hard gate (§7.10 already gates conversationally).

### 2. Branch eligibility — deterministic flags vs Claude's judgment

For each of the three branches, compute a boolean eligibility flag in C++. Pass via §7.7. Claude decides which to deliver.

- **Convergent eligible:** Speaker_A trust ≥ 0.5 AND Speaker_B trust ≥ 0.5 AND `letter` is in PresentedBy AND `phone_book` is in InspectedBy AND `photograph` is in InspectedBy. (Letter presented is the keystone.)
- **Divergent eligible:** EITHER speaker trust ≥ 0.5 AND the OTHER < 0.5 AND ≥ 4 turns elapsed AND `phone_book` inspected.
- **Recursive Silence eligible:** any of:
  - Sustained Pinch-Withhold (≥ 3 of last 5 player turns).
  - One speaker silent for ≥ 6 of last 8 turns.
  - ≥ 12 turns elapsed AND no keystone item presented.

Single-speaker demo path: Convergent triggers when the lone speaker's trust ≥ 0.5 AND the keystone items are presented. (The "both speakers ≥ 0.5" rule degrades to "the one speaker ≥ 0.5" when only one is enrolled.)

### 3. Branch resolution signal — JSON field vs text heuristic

Claude already returns structured JSON via the existing `dialogue` / `emotion_update` / `item_give` schema. Easiest extension: add an optional `branch_resolution` field. Claude sets it to `"convergent"` / `"divergent"` / `"recursive_silence"` only on the climax turn. C++ parses, broadcasts `OnBranchResolved`, closing card listens.

Alternative: scan the dialogue text for a sentinel phrase. Brittle. Don't do this.

**Recommendation: add `branch_resolution` to the JSON schema.** Update `ClaudeAPISubsystem::BuildRequestBody` and `ParseResponse`. Update §7.9 instruction to tell Claude to set this field on climax turns and leave it null otherwise.

### 4. Closing card timing — duration and fade

Design says 6-second hold. Add `ClosingCardHoldSeconds = 6.0f` UPROPERTY on the HUD. Fade-in 0.5s, hold full opacity, fade-out 0.5s when timer expires. After fadeout, return to normal HUD (or end PIE cleanly — your call; for the demo, just freeze the screen with the card visible until the user closes PIE).

### 5. Logger format

JSONL (one JSON object per line). Each row:
```json
{
  "ts": "2026-04-30T14:34:11.123Z",
  "turn": 7,
  "speaker": "Speaker_A",
  "gesture": "Disclose",
  "user_emotion": {"label": "Neutral", "confidence": 0.0},
  "interaction": "speak",          // "speak" | "present" | "inspect"
  "item": "letter",                // null when interaction == "speak"
  "items_inspected_by_speaker": {"Speaker_A": ["photograph", "phone_book", "letter"]},
  "items_presented_by_speaker": {"Speaker_A": ["letter"]},
  "trust": {"Speaker_A": 0.62, "Speaker_B": 0.0},
  "branch_eligible": {"convergent": true, "divergent": false, "recursive_silence": false},
  "claude_system_prompt": "<full text>",
  "claude_user_message": "<full text including [Speaker_X] [held] [emotion] prefixes>",
  "claude_response_raw": "<full JSON response>",
  "branch_resolution": null         // populated only on climax turn
}
```

Markdown transcript at session end: human-readable, just `## Turn N` headers + speaker labels + final NPC text. Skip the structured fields.

---

## Per-speaker trust data flow

Already plumbed in Tier 1/2 — Tier 3 just reads:
- `UDialogueComponent::InspectedBy` (`TMap<FName, TSet<FName>>`)
- `UDialogueComponent::PresentedBy` (same)
- `UDialogueComponent::ConversationHistory` (`TArray<FNPCMessage>`) — turn-level granularity

You need a small rolling buffer of last-N gesture intents per speaker. Add to `DialogueComponent`:
```cpp
TArray<TPair<FName, EGestureIntent>> RecentGestureLog;  // speaker + gesture, last ~10
```
Append in `SendUserMessage` when SpeakerTag is set and Gesture != None. Trim to length 10. Trust math reads.

---

## Suggested order of operations

1. **Trust estimator (~30 min).** Pure-C++ helper, no engine API surface. `static float ComputeSpeakerTrust(FName Speaker, const UDialogueComponent& Comp)`. Implement the formula skeleton above. Unit-test on paper: 0 items inspected → 0 trust, all 7 inspected + Letter presented → 1.0 (clamped). Can live as a private static method on `DialogueComponent` or in a separate `MemoryArchiveTrust.h`.

2. **§7.7 branch hint section (~30 min).** Append to `BuildSystemPromptFromGraph()`. New `bDeterministicBranchHint = true` UPROPERTY on `DialogueComponent`. When true, build a structured observation block:
   ```
   §7.7 OBSERVED STATE (deterministic, updated each turn):
   - Speaker_A: turns=4, items_inspected=[old_photograph, phone_book], items_presented=[], trust=0.32
   - Speaker_B: not enrolled
   - Recent gestures (last 5): Disclose, Disclose, Doubt, Disclose, None
   - Branch eligibility: convergent=false, divergent=false, recursive_silence=false
   ```
   Claude reads structured numbers and adjusts pacing.

3. **Branch eligibility flags (~20 min).** Three booleans computed alongside §7.7. Embed in the same section. Same source-of-truth for §7.9 below.

4. **§7.9 climax instruction (~30 min).** Append to `BuildSystemPromptFromGraph()` ONLY when at least one branch flag is true. Per-branch instructions:
   - Convergent: "You may now answer the keystone question. Address both visitors. Speak clearly. Your last sentence may close the conversation."
   - Divergent: "You may now answer, but address each visitor by name in turn. Give each a different fragment. Your last sentence to each closes their access."
   - Recursive Silence: "You are not ready. Tell them, gently. Decline to continue. Your final sentence revokes consent on Ashley's behalf."

5. **`branch_resolution` JSON field (~30 min).** Update `ClaudeAPISubsystem::BuildRequestBody` to instruct Claude to include the field; update `ParseResponse` to extract it. Add `EArchiveBranch` enum + `OnBranchResolved` delegate on `DialogueComponent`. Broadcast when the field is non-null. Update §7.9 to instruct Claude on when to set it.

6. **Closing card UI (~30 min).** New `DrawHUD` block triggered by `OnBranchResolved`. Fade-in / hold 6s / fade-out. Three text layers: Friend's last line (largest), provocation (medium), branch label (smallest). Dark overlay covering everything else.

7. **HUD top bar + consent indicator (~20 min).** Always-visible top bar in `DrawHUD`. Three segments separated by `|`. Listen to `OnBranchResolved`; if Recursive Silence, set a `bConsentRevoked` flag that flips the trailing segment text and color.

8. **`UMemoryArchiveLogger` (~30 min).** New `UGameInstanceSubsystem`. Subscribe to `OnDialogueResponseReceived` on the player's focused NPC. Per turn, gather the structured row and `FFileHelper::SaveStringToFile` (append mode) to `Saved/MemoryArchive/session-{timestamp}.jsonl`. On `Deinitialize`, dump a Markdown transcript reading from the same JSONL.

9. **Smoke test (~30 min).** Single-speaker demo path through to Convergent close:
   - PIE → speak a few warmup turns to build trust.
   - Inspect Old Photograph, Phone Book, Letter (E key).
   - Present the Letter (F key).
   - Verify Output Log shows `Speaker_A trust` climbing past 0.5 in §7.7 dump.
   - Friend's response on the keystone turn delivers "I have kept the letter" or equivalent and includes `branch_resolution: convergent` in JSON.
   - Closing card hold for 6 seconds.
   - HUD top bar reads `[consent: GRANTED]` throughout.
   - `Saved/MemoryArchive/session-*.jsonl` exists and contains the turns.

---

## Cut order if you fall behind

If Tier 3 is overrunning, cut in this order (per CLAUDE.md):

1. **First to drop:** `UMemoryArchiveLogger`. Useful for the empirical layer but not for the demo. Output Log is enough.
2. **Second:** §7.7 deterministic hint. Let Claude infer trust from §7.10's soft-doubt cues alone — drop the structured numeric block. The branch eligibility flags still go in (Claude needs the climax signal).
3. **Third:** Recursive-Silence branch. Demo can ship Convergent-only. Pinch-Withhold sustained still affects soft doubt via §7.10 conversationally; just don't end the slice with a consent revocation.
4. **Fourth:** HUD top bar consent indicator. The chip + closing card alone tell the story.

**Never cut:** `branch_resolution` JSON field + closing card. Those two are the climax payoff. Without them the demo just trails off.

---

## Verification at the end of the session

Single-speaker PIE on the work machine:

- [ ] PIE → walk near Friend → speak warmup turns. Output Log shows `[SpeakerID] resolved Speaker_A` consistently and `Speaker_A trust=` climbing in the §7.7 dump (visible if you log the assembled prompt).
- [ ] Inspect 3+ items. Output Log: `Picked up 'X'` and per-speaker memory writes. Trust climbs.
- [ ] Present Letter to Friend. Trust spikes via the +0.15 presented-weight. §7.7 reads `convergent=true`.
- [ ] Friend's response on next turn includes `branch_resolution: convergent` and the keystone topic.
- [ ] `OnBranchResolved` fires. Closing card overlay shows for 6 seconds.
- [ ] Top bar reads `ARCHIVE LINK ACTIVE | SUBJECT: Ashley Wei [posthumous reconstruction, no consent] | TESTIMONY: The Friend [consent: GRANTED]` throughout.
- [ ] Quit PIE → `Saved/MemoryArchive/session-{timestamp}.jsonl` exists, contains all turns, structured rows parse.
- [ ] (Optional) Replay session by triggering Recursive Silence: Pinch gesture + Withhold-only style for 3+ turns, OR press 1 then never speak. Top bar consent flips to `REVOKED`, link greys, closing card delivers Recursive Silence text.

If any step fails, leave a clear note at the top of this file (or a new `TIER3_STATUS.md`) describing what works, what doesn't, and where to resume.

---

## Constraints

- **Platform:** Windows 11. No platform-specific code paths.
- **Engine:** UE 5.7. Stick to standard `UCLASS` / `UGameInstanceSubsystem` / `UFUNCTION` patterns — Live Coding picks up non-structural changes; full editor close + rebuild for any new UCLASS / new UPROPERTY / new UFUNCTION.
- **No new third-party deps.** Tier 3 is pure C++ + JSON. `FJsonSerializer` and `FFileHelper` cover the logger.
- **No new microphone or audio work.** Tier 2's pipeline is the floor. Don't touch `WhisperSTTComponent` or `SpeakerIdentificationComponent` unless absolutely necessary.
- **Don't break the single-speaker demo path.** Convergent must trigger reliably with one user. The two-speaker design (Divergent / Recursive Silence with two enrolled speakers) is intact behind 1/2 manual override but not the demo target.
- **Build environment:** Visual Studio 2026 Insiders toolchain. Live Coding handles non-structural edits to method bodies; full close + Build LLM_NPC + reopen for any new UCLASS / new UPROPERTY / new UFUNCTION / new component.
- **The Friend graph node** (`Content/THRESHOLD/DA_Graph_ThresholdDefault.uasset`) is a binary asset on the work machine only. Don't try to re-write it from C++ — append section text via `BuildSystemPromptFromGraph` instead, the way §7.5 / §7.10 are assembled.

---

## Reference: where Tier 2 left things plumbed

- **`PendingSpeakerTag` / `LastSpeakerTag` / `LastSpeakerConfidence`** on `ANPCPlayerController` — Tier 3's HUD top bar / chip / logger reads these. `LastSpeakerTag` is sticky (persists across dispatches) so it's the right source for HUD displays.
- **`UDialogueComponent::InspectedBy` / `PresentedBy`** — `TMap<FName, TSet<FName>>` keyed on `FName ItemID`, valued on `TSet<FName SpeakerID>`. Tier 3 trust math reads these directly.
- **`SendUserMessage(..., FName SpeakerTag)` / `SendObjectPresentMessage(..., FName SpeakerTag)`** — both already accept the speaker tag. Tier 3 doesn't add new entry points.
- **`BuildSystemPromptFromGraph()`** — assembles ten or so labeled sections by string concatenation. Tier 3 adds §7.7 and §7.9 to the same chain. Existing sections include §1 identity, §2 player relationship, §5 outgoing edges, §6 tonal register, §7 brevity, §7.5 Visitors register, §7.10 Apparatus + Soft Doubt, §8 emotional register, §8.7 ElevenLabs v3 audio tags + text-shape rules, §9 cycle marker, §10 hard character boundary. **Do not add a JSON format section** — `ClaudeAPISubsystem::BuildRequestBody` appends its own.
- **`OnDialogueResponseReceived`** delegate broadcast on `DialogueComponent`. The `MemoryArchiveLogger` and the branch resolution flow both subscribe here.
- **`ClaudeAPISubsystem::ParseResponse`** parses `dialogue`, `emotion_update`, `item_give` from Claude's JSON. Tier 3 adds `branch_resolution` to that parse step and threads it through `FClaudeAPIResponse` to `OnDialogueResponseReceived` consumers.

---

## When you finish (or when time runs out)

1. Commit cleanly with a message like `tier 3: per-speaker trust + §7.7/§7.9 prompt sections + closing card + memory archive logger`.
2. Update `CLAUDE.md`'s build-order table — change Tier 3's `Status` cell to `Complete (date)` or `Partial — see TIER3_STATUS.md`.
3. Add a `Memory Archive — Tier 3 complete (date)` block under the existing Tier 2 block in `CLAUDE.md`, mirroring the format with line-ref links to the changes.
4. Write `TIER4_HANDOFF.md` if a polish pass session will pick up Tier 4 (scanline PP material, hand wireframe refinement, archive console prop, HUD aesthetic pass).
5. Tell the user what works, what doesn't, and what the smoke test showed — particularly with the single-speaker Convergent close, since that's the demo path.

The slice already demos coherently from end of Tier 2 (single speaker, full per-speaker memory writes, soft-doubt §7.10 register, Friend's keystone moment lands when the Letter is presented). Tier 3 turns on the climax architecture and the empirical layer. Land Convergent cleanly first; everything past it (Divergent, Recursive Silence, the logger's Markdown export) is upside.
