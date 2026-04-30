# Tier 1 Handoff — Memory Archive Vertical Slice

**Status as of:** 2026-04-29
**Demo:** 2026-04-30 (tomorrow)
**Working branch:** `claude/continue-llm-npc-api-lwC5j`
**Budgeted hours:** 4
**You are picking up:** Tier 1 of the 5-tier Memory Archive build order, after Tier 0 landed cleanly.

---

## Required reading order (do this before writing any code)

1. **`CLAUDE.md`**, especially:
   - `Final Review Vertical Slice — "The Memory Archive" (Two-Speaker Pivot, locked 2026-04-29)` — the canonical design doc; everything in this handoff is derived from it
   - `Memory Archive — Tier 0 complete (2026-04-29)` — exact list of what just landed, with line refs
   - `Build order` table — all 5 tiers and the cut order if you fall behind
   - `Files modified (summary)` — names every file the slice touches; Tier 1 owns the **NEW** `BP_ArchiveOperator` + `MI_RoboticHand` + `M_RoboticHand` row, the `NPCPlayerController.h/.cpp` E/F/Q row, and the `DialogueComponent.h/.cpp` per-speaker maps row
   - `Seven items` paragraph — the canonical 7 items and where they live in The Friend's back-room store; you'll be referencing names + IDs, not authoring text
   - `Hard-gated topic matrix` — how `ItemID` values feed the Tier 3 gating; you don't implement gating in Tier 1, but the IDs you use must match this matrix exactly
2. **`Source/LLM_NPC/Gesture/InspectableItem.h` + `.cpp`** — Tier 0 added the narrative fields and the `InteractionSphere` (`QueryOnly`, blocks `ECC_Visibility` only). Reuse `ApplyRotation` / `ApplyScale` / `ResetTransform`; don't reinvent them.
3. **`Source/LLM_NPC/Dialogue/DialogueComponent.h` + `.cpp`** — Tier 0 added `SendObjectPresentMessage(AInspectableItem*, const FDetectedUserEmotion&, EGestureIntent)`. You'll wire it to F-key. You'll also add per-speaker `InspectedBy` / `PresentedBy` maps here.
4. **`Source/LLM_NPC/Core/NPCPlayerController.h` + `.cpp`** — already owns `FocusedNPC` (Phase 1), `PendingGestureIntent` (Phase 1), Enter/V/click input (Phase 1), and as of Tier 0 the gesture is consumed inside `NPCDialogueHUD::SubmitChatMessage`. You'll add E / F / Q bindings + walk-lock + line trace here.
5. **The Tier 0 commit on this branch** — review `git log -1 --stat` and `git diff HEAD~1` for the exact set of recent touches before you start.

---

## Mission summary

Ship the player-input + per-speaker-memory plumbing for the Memory Archive demo. By the end of Tier 1 the player should be able to:

- Walk around the Friend's back-room store as the FP archive operator (chrome robotic hands).
- Aim at one of the 7 inspectable items, press **E** to pick it up; walking locks; mouse drag rotates, scroll wheel scales.
- Press **E** again or **Q** to put the item back to its original transform — **no Claude turn fires**.
- Press **F** while holding to extend the item into the Friend's sightline → **fires a Claude turn** via the existing `SendObjectPresentMessage`.
- Have every E and every F recorded per-speaker in `UDialogueComponent::InspectedBy` and `PresentedBy` maps. Until Tier 2 ships speaker ID, treat the active speaker as a constant default `"Speaker_A"` so the maps populate cleanly and Tier 3's gating logic has data to read.

Tier 0 already proved end-to-end wiring works for typed/voice messages with the new prompt. Tier 1 adds the diegetic verbs (Pickup/Present/Drop) and the per-speaker memory the Tier 3 gating will read.

---

## Current state inventory

### What is **already done** (do not redo)

| Item | Where | Status |
|------|-------|--------|
| `AInspectableItem` narrative fields (`ItemID`, `ItemDisplayName`, `ItemWorldDescription`, `NPCKnowledgeText`) | `Source/LLM_NPC/Gesture/InspectableItem.h:74-96` | Done |
| `AInspectableItem::InteractionSphere` (QueryOnly, blocks `ECC_Visibility` only) | `Source/LLM_NPC/Gesture/InspectableItem.cpp:21-28` | Done |
| `ApplyScale` / `ApplyRotation` / `ResetTransform` (spring-damper) | `Source/LLM_NPC/Gesture/InspectableItem.cpp:74-90` | Done — reuse these from Tier 1 input handlers |
| `UDialogueComponent::SendObjectPresentMessage` | `Source/LLM_NPC/Dialogue/DialogueComponent.cpp:211-319` | Done |
| §7.5 Visitors register + §7.10 Apparatus + Soft Doubt in system prompt | `Source/LLM_NPC/Dialogue/DialogueComponent.cpp:505-543` | Done |
| `EGestureIntent` parameter on `SendUserMessage`, threaded through HUD `SubmitChatMessage` | `NPCDialogueHUD.cpp:281-292` + `DialogueComponent.h:57-59` | Done — gesture flows end-to-end now |
| `FocusedNPC`, `PendingGestureIntent`, gesture mapping | `NPCPlayerController.h` + `.cpp` | Phase 1 — preserved |
| `DA_Graph_ThresholdDefault` Friend node rewrite | binary asset, work machine | Done in-editor |
| `BP_NPC_Friend` mesh + anim driver | binary asset, work machine | Done in-editor |

### What is **NOT yet done** (Tier 1 owns these)

| Item | Probable home | Notes |
|------|---------------|-------|
| FP pawn class with chrome robotic hands | New: subclass UE5 `ACharacter` (FirstPerson template) → C++ `AArchiveOperator` is fine, OR pure Blueprint `BP_ArchiveOperator` if simpler given the deadline | Decide which based on what state you need to share with the controller. If most state ends up on the controller anyway, BP-only pawn is acceptable. |
| `MI_RoboticHand` material instance + `M_RoboticHand` master | `Content/Materials/` (or wherever the project keeps materials — check existing convention with `Glob "Content/**/M_*.uasset"`) | Chrome/holographic, thin emissive wireframe seams over darker base. Editor-side work; binary asset on the work machine. |
| **E** binding: line trace + pickup/inspect | `NPCPlayerController` (or `AArchiveOperator`) | 300cm trace on `ECC_Visibility` from camera/pawn forward; if it hits an `AInspectableItem`, attach to robotic hand offset, mark held, **do not** call `SendObjectPresentMessage`. Press E again → call `ResetTransform()` and detach. |
| **F** binding: present held item | Same | Only valid while holding. Calls `FocusedNPC->DialogueComponent->SendObjectPresentMessage(HeldItem, defaultEmotion, PendingGestureIntent)`. After firing, do **not** clear hold — the player can keep the item out, drop with Q, or pick up another. |
| **Q** binding: drop held item | Same | Calls `ResetTransform()` and detaches. |
| **Walk-lock while held** | `AArchiveOperator` or controller | Zero out movement input while `HeldItem != nullptr`. Mouse-look should stay enabled. |
| **Mouse drag → rotate held item** | Same | `ApplyRotation(FRotator(MouseDeltaY, MouseDeltaX, 0) * sensitivity)` — exact axis mapping is a design taste call; pick what feels right. |
| **Scroll wheel → scale held item** | Same | `ApplyScale(WheelDelta * 0.1f)` or similar; the spring-damper smooths it. |
| `UDialogueComponent::InspectedBy` (`TMap<FName, TSet<FName>>`) — keyed by `ItemID`, value is the set of speaker IDs that inspected | `DialogueComponent.h` | UPROPERTY-friendly. |
| `UDialogueComponent::PresentedBy` (same shape) | `DialogueComponent.h` | Populated inside `SendObjectPresentMessage` after the call succeeds. |
| `UDialogueComponent::RecordItemInspection(FName ItemID, FName SpeakerID)` | `DialogueComponent.h` + `.cpp` | Called from the controller on every successful E pickup. Idempotent — `TSet::Add` handles dedup. |
| Place 7 `AInspectableItem` actors in `Content/Maps/Threshold_Compound.umap` with the exact `ItemID` values | binary asset, work machine | Canonical IDs (must match the Hard-gated topic matrix in CLAUDE.md): `old_photograph`, `phone_book`, `letter`, `cash_stack`, `jade_pendant`, `chessboard`, `bonsai_tree`. Display names + descriptions + knowledge text from the Memory Archive plan section. |
| Set `BP_ArchiveOperator` as Default Pawn Class on `BP_NPCGameMode` | binary asset, work machine | Or in `Threshold_Compound` World Settings override. |

### What is **explicitly out of scope** for Tier 1

- Acoustic speaker identification — Tier 2. Until then, **always tag the active speaker as `Speaker_A`** when writing to `InspectedBy` / `PresentedBy`. Keep this as a single `static const FName DefaultSpeakerID(TEXT("Speaker_A"))` constant in `DialogueComponent.cpp` so Tier 2 can swap it for the real speaker tag from `USpeakerIdentificationComponent` in one line.
- 1 / 2 manual override keys — Tier 2.
- `[Speaker_X]` prefix on user messages — Tier 2.
- Per-speaker trust estimate, §7.7 branch hint — Tier 3.
- `UMemoryArchiveLogger` — Tier 3.
- Closing card, consent indicator on HUD — Tier 3.
- Scanline post-process material, hand wireframe refinement — Tier 4.

---

## Open design choices (decide early; don't agonise)

1. **Pawn class in C++ vs. Blueprint-only.** The existing project has C++ for everything important and Blueprints only for asset-references. Recommendation: a thin C++ `AArchiveOperator : public ACharacter` that owns `HeldItem` (TWeakObjectPtr<AInspectableItem>), the line-trace function, the pickup/present/drop methods, and the walk-lock state. The controller calls into it. This matches the rest of the codebase's split. If you can't get the C++ pawn placed correctly in the level in time, fall back to Blueprint and put all logic on the controller.

2. **Where the 4 input bindings live.** The cleanest split is:
   - `ANPCPlayerController` — owns input (`E`, `F`, `Q`, mouse delta, scroll wheel), routes to pawn methods.
   - `AArchiveOperator` — owns held-item state, line-trace logic, transform routing.
   That said, if you're tight on time, putting everything on the controller is acceptable — the existing controller already owns `Tick`, `FocusedNPC`, gesture caching, and all the typing input. Pick whichever you can finish.

3. **Camera setup.** UE5 FirstPerson template uses a `UCameraComponent` attached to the head. Stick with that. The robotic hands are visible because the template's first-person mesh attaches to the camera. You'll be assigning the `MI_RoboticHand` material to that mesh's slots.

4. **Walk-lock implementation.** Two options: (a) zero out `MoveForward` / `MoveRight` axis values while `bIsHoldingItem`; (b) call `Character->GetCharacterMovement()->DisableMovement()` and re-enable on drop. (a) is less invasive — prefer it.

5. **Mouse rotation while held.** When the item is held, the camera should keep working for look (so the player can still see the Friend), but mouse delta should *also* drive item rotation. Option: only route mouse-X/Y to `ApplyRotation` while a modifier key (e.g. RMB held) is down. Or: dedicate mouse-X/Y to item rotation while held and lock camera look. The plan says "mouse drag rotates" — interpret "drag" as RMB-held drag if you want camera-look to stay active. Pick one and document the choice in the commit message.

---

## Per-speaker memory data shape

In `DialogueComponent.h` (public, UPROPERTY for inspector visibility):

```cpp
/** ItemID → set of speaker IDs that have inspected (E-key) this item. */
UPROPERTY(BlueprintReadOnly, Category = "NPC|Dialogue|Memory")
TMap<FName, FInspectionSpeakerSet> InspectedBy;

/** ItemID → set of speaker IDs that have presented (F-key) this item. */
UPROPERTY(BlueprintReadOnly, Category = "NPC|Dialogue|Memory")
TMap<FName, FInspectionSpeakerSet> PresentedBy;
```

UE's reflection system does not support `TMap<FName, TSet<FName>>` directly as a UPROPERTY. Wrap the inner `TSet<FName>` in a `USTRUCT` (`FInspectionSpeakerSet { TSet<FName> Speakers; }`) so it survives reflection. If you don't need editor visibility, you can drop the `UPROPERTY` and the wrapping struct entirely — Tier 3 only needs to read these from C++.

The simplest non-reflective form (recommended unless you need editor inspection):

```cpp
TMap<FName, TSet<FName>> InspectedBy;
TMap<FName, TSet<FName>> PresentedBy;
```

Helpers:
```cpp
void RecordItemInspection(FName ItemID, FName SpeakerID); // E
// PresentedBy is written inside SendObjectPresentMessage after the dispatch — no public helper needed.
```

`ClearConversationHistory` should also `Empty()` both maps so Phase 2.5 cycle resets work later.

---

## Suggested order of operations

1. **Get the maps in place first (~30 min).** Add `InspectedBy` / `PresentedBy` to `UDialogueComponent`, `RecordItemInspection`, write inside `SendObjectPresentMessage`, clear in `ClearConversationHistory`. Compile. This is the deepest dependency for Tier 3 and is risk-free even if the rest slips.

2. **Add E/F/Q + line trace + held state on the controller (~90 min).** Skip the dedicated pawn class for now — use whatever pawn the level currently spawns. Validate: log every successful pickup/present/drop with `UE_LOG`. Manually verify in PIE that pressing F on a held item produces a Claude turn with the structured payload by watching the existing `Presented item '%s'` log in `DialogueComponent.cpp`.

3. **Add walk-lock + mouse drag rotate + scroll scale (~30 min).** Iterate on feel.

4. **Author `AArchiveOperator` C++ pawn + `BP_ArchiveOperator` Blueprint subclass (~45 min, if time).** Move held-item state off the controller and onto the pawn. Set as default pawn class.

5. **`MI_RoboticHand` material + first-person mesh assignment (~30 min).** Editor-side. If you can't ship the chrome look in time, leave the stock template hands — Tier 4 polish covers that.

6. **Place the 7 items in `Threshold_Compound.umap` (work-machine, in-editor).** This is binary-asset work; you can stub it from code by spawning placeholder static-mesh actors at known transforms in `BeginPlay` if you can't get into the editor in time, but the canonical path is editor placement. **Item IDs must match the Hard-gated topic matrix exactly** — `old_photograph`, `phone_book`, `letter`, `cash_stack`, `jade_pendant`, `chessboard`, `bonsai_tree`.

7. **Smoke test the full loop.** Walk → look at item → E → drag-rotate → F → Friend speaks → Q → another item.

---

## Cut order if you fall behind

Per CLAUDE.md, Tier 1 is below Tier 4 polish in priority — meaning **don't sacrifice Tier 1 to do polish**. But if Tier 1 itself is overrunning, here's the in-tier cut order:

1. **First to drop:** chrome robotic-hand material — ship with stock template hands. Visual polish, doesn't affect mechanics.
2. **Second:** dedicated `AArchiveOperator` C++ pawn — collapse all state onto `ANPCPlayerController` if needed.
3. **Third:** mouse-drag rotation and scroll-scale — the spring-damper makes a static held pose acceptable; presenting still works.
4. **Last resort:** drop items #5/#6 from the canonical 7. Per the cuttable order in CLAUDE.md, items `jade_pendant` and `chessboard` are the first content cuts (each gates a single optional topic). The 5 keystone items (`old_photograph`, `phone_book`, `letter`, `cash_stack`, `bonsai_tree`) are required for the climax to land.

**Never cut:** F-key + `SendObjectPresentMessage` invocation + per-speaker `PresentedBy` write. That is the single keystone interaction — no F-present means no demo.

---

## Verification at the end of the session

Before pausing for handoff, smoke-check in PIE on the work machine:

- [ ] Walk around the Friend's back-room store; camera works, no clipping.
- [ ] Aim at the Phone Book, press E. The book lifts to the held position, walking locks, mouse drag rotates it.
- [ ] Press E again (or Q). Phone Book returns to original transform via spring-damper, walk unlocks.
- [ ] Pick up the Letter, press F. The Friend should respond with a Claude turn that references the letter specifically (her `NPCKnowledgeText` for the letter) and break her soft-doubt posture (per §7.10).
- [ ] Pick up another item (e.g. Stack of Cash), press F. Different response; Friend tracks the new item.
- [ ] Run `git diff` and confirm `InspectedBy` / `PresentedBy` are written in `SendObjectPresentMessage` and `RecordItemInspection`.
- [ ] Quit PIE, restart, repeat one cycle to confirm no stale state survives.

If any of these fail, leave a clear note at the top of this file (or a new `TIER1_STATUS.md`) describing what works, what doesn't, and where the next session should resume.

---

## Constraints

- **Platform:** Windows 11. Shell is Bash with PowerShell available; OS-specific code paths exist already (`waveIn` audio capture is Windows-only — see `WhisperSTTComponent`).
- **Engine:** UE5.7. Don't add API calls that exist only in 5.8+ (`SetPostProcessAnimBlueprintClass` is a known gotcha — see commit `21dd7d4`).
- **Binary assets** under `Content/THRESHOLD/MetaHuman/` are gitignored. Anything that needs editor verification must happen on the work machine.
- **Demo deadline 2026-04-30.** If you cannot finish a Tier 1 deliverable cleanly, ship a graceful fallback (e.g. controller-only state with no dedicated pawn class) rather than a half-broken commit. The slice must demo coherently from the end of every tier.
- **Don't merge Tier 2 work into Tier 1.** Tier 2 (acoustic speaker ID, manual 1/2 override) lives in its own session. Use the `Speaker_A` constant placeholder. Tier 3's gating logic reads `InspectedBy` / `PresentedBy`; Tier 1 just has to write to them.

---

## Reference: the 7 canonical items (from CLAUDE.md)

| ItemID | Display name | What goes in `ItemWorldDescription` (operator view) | What goes in `NPCKnowledgeText` (Friend's secret) |
|---|---|---|---|
| `old_photograph` | Old Photograph | (operator-side description) | (Friend's secret) |
| `store_ledger` | Store Ledger | | |
| `folded_note` | Folded Note | | |
| `cash_box` | Cash Box | | |
| `wall_polaroid` | Wall Polaroid | | |
| `train_ticket` | Train Ticket Stub | | |
| `jade_plant` | Jade Plant | | |

The exact narrative text is in CLAUDE.md under the Memory Archive section + the Friend graph node `WithheldTruth` paragraph. **Do not paraphrase** — quote the canonical text into the Inspectable Item details on the work machine.

---

## When you finish (or when time runs out)

1. Commit cleanly with a message like `tier 1: pickup/present/drop verbs + per-speaker memory`.
2. Update CLAUDE.md's build-order table — change the Tier 1 row's `Status` cell to `Complete (date)` or `Partial — see TIER1_STATUS.md`.
3. Add a `Memory Archive — Tier 1 complete (date)` block under the existing Tier 0 block in CLAUDE.md, mirroring the format with line-ref links to the changes.
4. Write `TIER2_HANDOFF.md` if a third session will pick up Tier 2.
5. Tell the user what works, what doesn't, and what the smoke test showed.

Demo is tomorrow. Land Tier 1 cleanly first; everything past it is upside.
