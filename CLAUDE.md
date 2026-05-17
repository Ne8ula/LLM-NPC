# LLM-NPC — Claude Code Brain

## Project Overview

**LLM-NPC** is an Unreal Engine 5.7 research prototype implementing a fully conversational, emotionally-aware Metahuman NPC with zero scripted dialogue. The NPC:
- Converses naturally via Claude LLM
- Understands player emotions through computer vision (webcam)
- Responds with expressive facial animation + synthesized voice (ElevenLabs TTS)
- Unlocks inventory items based on emotional state + dialogue keywords

**Key innovation:** All NPC dialogue is model-generated in real-time. Gameplay progression is gated by LLM reasoning about emotional state — not scripted branches.

**Active vertical slice:** THRESHOLD — a non-linear, replayable interactive experience with 5 AI NPCs in a Chinese residential compound. Core mechanic: TESTIMONIAL (player verbally relays what one NPC said to another via live Whisper STT; each Claude instance responds to the player's imperfect recollection in real-time). Social graph between NPCs is procedurally generated per run.

**Final deliverable scope (professor feedback, Apr 2026):** Single-NPC vertical slice focused on **The Friend** — Asian female Metahuman, mid-to-late 20s, runs a ground-floor convenience store inside the compound. Sadness 0.5 baseline, hidden title: "The One Who Stayed." Two new mechanics added for the deliverable: **Speaker Identification** (MFCC voice fingerprinting, up to 4 speakers, NPC responds differently per speaker) and **Object Inspection** (player aims at 3D props, presses E, NPC responds from her personal relationship to that object). Staging area: 7 inspectable props in her back-room store space. No exterior sightlines — fully enclosed Chinese compound interior.

---

## Tech Stack

| Layer | Technology |
|-------|-----------|
| Engine | Unreal Engine 5.7, C++ |
| LLM | Anthropic Claude API (`/v1/messages`) |
| STT | OpenAI Whisper (`/v1/audio/transcriptions`) |
| TTS | ElevenLabs (`/v1/text-to-speech/{voice_id}/with-timestamps`) |
| Emotion Model | Plutchik's Wheel + PAD (Pleasure-Arousal-Dominance) continuous space |
| Vision | OpenCV 4.x DNN + ONNX Runtime (facial expression CNN + hand landmark regression) |
| Character | Metahuman with RigLogic (morph targets) + procedural full-body FK |
| Body Animation | NVIDIA Kimodo (`nvidia/Kimodo-SMPL-X-RP-v1.1`) — offline text-to-motion diffusion; generates mocap clip libraries retargeted to Metahuman via UE5 IK Retargeter |
| Third-Party Libs | whisper.cpp, OpenCV 4.x, ONNX Runtime |

---

## Directory Structure

```
LLM-NPC/
├── Source/LLM_NPC/              # 75 C++ files, ~11.6K LOC
│   ├── Core/                    # NPCCharacter, NPCAIController, NPCSubsystemComponent,
│   │                            # NPCConfigDataAsset, NPCTypes, NPCGameMode, NPCPlayerController,
│   │                            # NPCGraphDataAsset (NEW — social graph asset type)
│   ├── Dialogue/                # ClaudeAPISubsystem, DialogueComponent, WhisperSTTComponent,
│   │                            # ElevenLabsTTSComponent, DialogueFallbackWidget
│   ├── Emotion/                 # EmotionComponent, EmotionStateMachine, EmotionGoal,
│   │                            # EmotionTransitionRule, EmotionGraphDataAsset
│   ├── Vision/                  # CameraManagerSubsystem, FacialRecognitionComponent,
│   │                            # FaceExpressionModel
│   ├── Gesture/                 # GestureRecognitionComponent, HandLandmarkModel,
│   │                            # GestureClassifier, ObjectInspectWidget, InspectableItem
│   ├── Inventory/               # NPCInventoryComponent, InventoryDataAsset, InventoryTypes
│   ├── Animation/               # MetahumanAnimComponent (864 LOC), NPCBodyMotionComponent (794 LOC),
│   │                            # NPCLipSyncComponent (419 LOC), BlendShapeMappingDataAsset,
│   │                            # PhonemeVisemeMapper (341 LOC), VisemeTypes, NPCBodyIdleAnimInstance
│   ├── Fallback/                # FallbackManagerComponent, InputModeSubsystem
│   └── LLM_NPC.Build.cs        # Build config with third-party detection + conditional compilation
├── Content/
│   ├── Maps/MainMap.umap        # Single playable scene
│   ├── BP_NPC_Test.uasset       # Main test NPC Blueprint
│   ├── DA_NPC_Test.uasset       # NPC personality config (system prompt, voice ID, emotion defaults)
│   ├── DA_BlendShapeMap_Default.uasset  # Emotion → FACS blend shape mapping
│   ├── MetaHumans/              # Character skeleton, animations, materials, expression poses
│   ├── Models/                  # ONNX model files (fer_expression.onnx, hand_landmark.onnx)
│   └── UI/                      # Dialogue overlay, fallback UI widgets
├── ThirdParty/
│   ├── whisper.cpp/include/ + lib/
│   ├── OpenCV/include/ + lib/
│   └── ONNXRuntime/include/ + lib/
├── Config/
│   ├── DefaultEngine.ini        # MainMap startup, GPU settings
│   ├── DefaultGame.ini
│   └── DefaultInput.ini
├── README.md                    # Full project documentation
├── make_deck.py                 # Python script to generate presentation PowerPoint
└── slide-deck.pptx              # 12-slide presentation deck
```

---

## Architecture: Component-Based Subsystem Design

**Root Actor:** `ANPCCharacter` (extends `ACharacter`)
- Owns all subsystem components
- Designed for procedural NPC generation: spawn at runtime, assign `UNPCConfigDataAsset`

All subsystems extend `UNPCSubsystemComponent` (uniform lifecycle).

### Subsystem Responsibilities

| Component | LOC | Responsibility |
|-----------|-----|----------------|
| `ClaudeAPISubsystem` | 368 | Game instance singleton; HTTP POST to Claude API; rate limiting (0.5s) + exponential backoff (3× retries, 1s→2s→4s ±25% jitter); JSON parsing |
| `DialogueComponent` | 251 | Conversation history; assembles system prompt + emotion annotations; routes to Claude |
| `WhisperSTTComponent` | 453 | Windows `waveIn` direct PCM capture (16kHz, 16-bit mono); encodes WAV; POSTs to Whisper |
| `ElevenLabsTTSComponent` | 479 | POSTs to ElevenLabs; receives Base64 PCM (24kHz) + char-level alignment; `USoundWaveProcedural` playback |
| `EmotionComponent` | — | Plutchik 8-emotion PAD state machine; intensity decays 0.05/s toward Neutral; GOAP-inspired transition costs |
| `MetahumanAnimComponent` | 864 | Largest component; drives Metahuman FACS via Face AnimBP "Set Control"; works WITH RigLogic; 4.0 FPS curve interpolation |
| `NPCLipSyncComponent` | 419 | ElevenLabs char timestamps → visemes via `PhonemeVisemeMapper`; asymmetric smoothing (closure 50/s, open 7/s) |
| `NPCBodyMotionComponent` | 794 | 3-state FSM (Idle/Thinking/Speaking); sine-wave micro-motions: breathing 0.25Hz, head drift 0.05Hz, nods 0.5Hz, shoulder sway; FK 15 bones |
| `FacialRecognitionComponent` | 253 | Timer-based ~10 FPS; OpenCV DNN face detect → ONNX 8-class expression CNN |
| `GestureRecognitionComponent` | 253 | Timer-based ~15 FPS; ONNX 21-point hand landmark → Pinch/Spread/Rotate/Spindle |
| `NPCInventoryComponent` | 309 | Emotion-gated item unlocks; conditions: emotion type + min intensity + min duration + optional keywords |
| `FallbackManagerComponent` | 233 | Graceful degradation: text input fallback, text-only dialogue widget, API failure handling |

---

## Data Flow: One NPC Turn

```
Microphone (16kHz, waveIn)
  → WhisperSTT → OpenAI Whisper API → transcript
  
FacialRecognition (parallel) → ONNX classifier → player emotion

DialogueComponent assembles:
  - System prompt (from NPCConfigDataAsset)
  - Conversation history (up to 20 messages)
  - Current PAD state (numeric vector)
  - Player emotion + confidence
  - User message text
  → ClaudeAPISubsystem → POST /v1/messages

Claude returns structured JSON:
  {
    "dialogue": "...",
    "emotion_update": { "joy": 0.2, "trust": 0.5, ... },
    "item_give": "key_of_the_old_tower" | null
  }

Parallel broadcast:
  A) ElevenLabsTTS → play audio + OnTTSAlignmentReceived
  B) EmotionComponent → update PAD state → OnEmotionChanged
  C) InventoryComponent → check unlock conditions → OnItemGiven
  D) MetahumanAnimComponent ← OnEmotionChanged → FACS morph targets
  E) NPCLipSyncComponent ← OnTTSAlignmentReceived → viseme schedule
  F) NPCBodyMotionComponent ← OnTranscriptReady/OnSpeechStarted → motion state
```

---

## API Integration Points

| Service | Endpoint | Auth Header | Key Env Var |
|---------|----------|-------------|-------------|
| Whisper | `POST /v1/audio/transcriptions` | `Authorization: Bearer {key}` | `OPENAI_API_KEY` |
| Claude | `POST /v1/messages` | `x-api-key: {key}` | `ANTHROPIC_API_KEY` |
| ElevenLabs | `POST /v1/text-to-speech/{voice_id}/with-timestamps` | `xi-api-key: {key}` | `ELEVENLABS_API_KEY` |

Claude response format (structured JSON):
```json
{
  "dialogue": "The NPC's spoken response",
  "emotion_update": { "joy": 0.2, "trust": 0.5, "fear": -0.1 },
  "item_give": "item_id_string or null"
}
```

---

## Data-Driven Configuration

**`UNPCConfigDataAsset`** — Per-NPC personality (no C++ recompile needed):
- `NPCName`, `NPCDescription`, `SystemPrompt` *(soft-deprecated — Phase 2 replaces with `BuildSystemPromptFromGraph()`)*
- `GraphDataAsset` — reference to `UNPCGraphDataAsset` for this playthrough (NEW)
- `ClaudeModelID` (default: `claude-sonnet-4-6`), `MaxResponseTokens` (512)
- `ElevenLabsVoiceID`, voice stability (0.0–1.0), similarity boost (0.0–1.0)
- `DefaultEmotion`, `DefaultIntensity`, `EmotionDecayRate`, `NeutralThreshold`
- Per-emotion transition costs (enables personality without code changes)

**`UNPCGraphDataAsset`** *(NEW — `Source/LLM_NPC/Core/NPCGraphDataAsset.h/.cpp`)* — Complete social graph for one playthrough:
- `EventType`, `EventSummary` — shared reference point injected into all NPC system prompts
- `GroundTruth` — Phase 1 post-run reveal: what each NPC actually carries underneath
- `ReflectionReveal` — Phase 2 post-run reveal: "The One Who..." hidden titles, assembled via `BuildReflectionReveal()`
- `TArray<FNPCGraphNode> Nodes`, `TArray<FNPCGraphEdge> Edges`
- `FindNode(FName NPCID)` — C++ lookup helper
- `BuildReflectionReveal()` — assembles Phase 2 text from all node `HiddenTitle` fields

**`UEmotionGraphDataAsset`** — State machine definition (nodes = emotions, edges = transition rules with costs)

**`UInventoryDataAsset`** — Item catalogue with unlock conditions per item (not used in THRESHOLD)

**`UBlendShapeMappingDataAsset`** — `EEmotionType` → FACS AU names + blend shape weights

---

## Build System

**`LLM_NPC.Build.cs`** — Cross-platform with conditional compilation:
- Public UE modules: Core, CoreUObject, Engine, InputCore, HTTP, Json, JsonUtilities, UMG, Slate, AIModule, EnhancedInput
- Windows: `winmm.lib` for `waveIn` audio capture
- Preprocessor guards: `WITH_WHISPER=1/0`, `WITH_OPENCV=1/0`, `WITH_ONNXRUNTIME=1/0`
- Auto-detects third-party libs; graceful fallback if missing

---

## Key Data Types (NPCTypes.h)

- `FEmotionType` (enum): Plutchik 8 emotions + Neutral
- `FEmotionState`: PrimaryEmotion, Intensity, PAD vector, StateEnteredTime
- `FPADVector`: Pleasure, Arousal, Dominance (each -1.0 to +1.0)
- `FDetectedUserEmotion`: Emotion, Confidence, Probabilities[8], Timestamp
- `FGestureInput`: GestureType (Pinch/Spread/Rotate/Spindle), Magnitude, Confidence, Delta
- `EGestureIntent` (enum): None / Withhold / Disclose / Doubt / Synthesise — maps EGestureType to TESTIMONIAL meta-communication intent; injected into Claude context before voice message
- `FEmotionSignal`: TargetEmotion, Strength, Source
- `FNPCMessage`: Role ("user"/"assistant"), Content, Timestamp, DetectedUserEmotion
- `FNPCGraphNode`: NPCID, NPCName, Role, EmotionBaseline, KnowsAboutEvent, WithheldTruth, MisrememberedDetail, PlayerRelationship, ElevenLabsVoiceID, VoiceGender, MetahumanVariantPool, ReflectionAspect (hidden tonal instruction), HiddenTitle ("The One Who..." — post-run reveal only), `ItemKnowledgeSummary` (NEW — prose paragraph of NPC's emotional relationship to nearby physical objects; injected as system prompt section 7.5; filled only for The Friend's node in the single-NPC deliverable)
- `FNPCGraphEdge`: FromNPCID, ToNPCID, RelationshipDescription, TrustLevel

---

## What Has Been Implemented

- Full 12-component subsystem hierarchy with delegate-based inter-component comms
- Windows `waveIn` direct microphone capture (bypasses UE AudioCapture)
- Whisper STT integration (crash fixes, lambda captures fixed)
- Claude API with structured JSON response parsing
- ElevenLabs TTS with character-level alignment → lip sync
- Lip sync: replaced sine wave with text-based viseme estimation, asymmetric smoothing
- Emotion-driven facial expressions via Metahuman RigLogic (FACS morph targets)
- JAW OPEN ALPHA for jaw animation (replaces post-process blueprint approach)
- "Thinking" pose (brow overlay, auto-clears after 15s or on TTS start)
- Full-body FK animation: breathing, head drift, nods, shoulder sway
- Facial + body idling animations
- NPC animation changes (latest work)
- ONNX facial expression classification (~10 FPS) + hand landmark detection (~15 FPS)
- Emotion-gated inventory system
- Graceful degradation (text input fallback when voice/camera unavailable)
- Data asset config system (procedural NPC generation ready)
- Presentation deck (12 slides, `make_deck.py`)

**THRESHOLD vertical slice — Phase 0 complete (Apr 2026):**
- `EGestureIntent` enum added to `NPCTypes.h` — maps gesture type to TESTIMONIAL meta-communication intent
- `NPCGraphDataAsset.h/.cpp` created — `FNPCGraphNode`, `FNPCGraphEdge`, `UNPCGraphDataAsset` with `FindNode()` + `BuildReflectionReveal()`
- `NPCConfigDataAsset.h` updated — `SystemPrompt` soft-deprecated, `GraphDataAsset` reference added
- `DA_NPC_Test.uasset` + existing test NPC unchanged and still functional

**THRESHOLD vertical slice — Phase 1 complete (Apr 2026):**
- `NPCPlayerController`: `FocusedNPC` proximity + facing detection (distance² + dot product, `InteractionRadius` = 300cm); `UpdateNPCFocus()` called every tick; gesture delegate bound/unbound on focus switch; `FacialRecognitionComponent` Init/Shutdown per focused NPC (performance)
- `NPCDialogueHUD`: `SetFocusedNPC()` dynamically rebinds `OnDialogueResponseReceived` + `OnVoiceTranscript` delegates; displays focused NPC name in header; resets input state on focus switch
- `PendingGestureIntent` cached in `NPCPlayerController`, cleared on Enter (message submit) and on NPC focus switch
- **Dialogue HUD redesign**: compact 400×179px canvas panel, bottom-left; no movement lock (player always free); V key reserved for voice only (not typed into textbox); click-to-focus input model (`bTextInputActive` flag set by `HandleMouseClick()` hit-testing the input box rect); keyboard capture gated on `IsTextInputActive()`; voice recording indicator (red ● REC); waiting indicator (…); NPC name header
- Bug fixes: removed all `DisableInput`/`EnableInput` calls; removed `TryKey(EKeys::V)` from keyboard capture; `CachedScreenH` pattern for hit-testing geometry outside `DrawHUD`
- Content: `Content/Maps/Threshold_Compound.umap` created with placeholder geometry, 5 NPC spaces around central courtyard, Player Start, NavMesh; `Content/THRESHOLD/Config/` with 5 `UNPCConfigDataAsset` instances (DA_Threshold_Apo, DA_Threshold_Pragmatist, DA_Threshold_Friend, DA_Threshold_Keeper, DA_Threshold_TOWCF)

**THRESHOLD vertical slice — Phase 2 complete (Apr 2026):**
- `DialogueComponent::BuildSystemPromptFromGraph()` — 10-section runtime prompt assembly from `UNPCGraphDataAsset`: identity → player relationship → event ambient → knowledge → withheld behavioural constraint → memory quality → outgoing relationship edges → tonal register (verbatim `ReflectionAspect`) → response brevity (1–2 sentences) → emotional register → cycle-marker instruction → hard character boundary. **No JSON format section** — `ClaudeAPISubsystem::BuildRequestBody()` appends its own format instruction; a second conflicting one causes Claude to use wrong field names, `ParseResponse()` fails, and TTS speaks raw JSON.
- `DialogueComponent::BuildAnnotatedContent()` — gesture annotation first, emotion annotation second, user message last; Phase 3 will pass real `PendingGestureIntent`; Phase 2 passes `EGestureIntent::None`
- `DialogueComponent::GraphNodeID` UPROPERTY — set by `NPCGameMode`, with lazy name-matching fallback in `InitializeSubsystem()`
- `NPCGameMode::BeginPlay()` — pushes `ActiveGraph` to every `ANPCCharacter` in level; syncs `DialogueComponent->NPCConfig` to the character's `NPCConfig` (fixes stale Blueprint class default); resolves `GraphNodeID` by name-matching; applies runtime tuning to all THRESHOLD NPCs: `EmotionDecayRate = 0.003f`, `NeutralThreshold = 0.03f`, `MaxResponseTokens = 150`, `VoiceStability = 0.3f`
- `NPCGraphDataAsset.h`: `BuildReflectionReveal()` marked `CallInEditor` so it appears as a button in the Details panel
- **BP_NPCGameMode**: Blueprint subclass of `ANPCGameMode` required to expose `ActiveGraph` in World Settings — the inline editor only shows base class properties for C++ GameMode classes
- `DialogueComponent::OnClaudeResponseReceived()`: emotion signal strength raised to `1.0f`; graph node `ElevenLabsVoiceID` trumps `NPCConfig->ElevenLabsVoiceID` when set
- `ElevenLabsTTSComponent`: `PendingRequestVersion` counter — each `SpeakText()` call increments it and captures the version in the HTTP callback closure; stale responses (superseded by a newer call) are discarded before playback. Prevents double-playback when a Blueprint event graph handler and C++ both call `SpeakText()` on the same frame.
- Content: `Content/THRESHOLD/DA_Graph_ThresholdDefault.uasset` — handcrafted social graph with 5 nodes (Āpó, The Pragmatist, The Friend, The Keeper, The One Who Couldn't Forget) and 7 directed relationship edges

---

## Active Test Assets

- **Map:** `Content/Maps/MainMap.umap` — single NPC test scene
- **NPC Blueprint:** `Content/BP_NPC_Test.uasset`
- **Config:** `Content/DA_NPC_Test.uasset` — personality, voice ID, emotion defaults
- **Blend shape map:** `Content/DA_BlendShapeMap_Default.uasset`
- **ONNX models:** `Content/Models/fer_expression.onnx`, `hand_landmark.onnx`

**THRESHOLD assets:**
- **Map:** `Content/Maps/Threshold_Compound.umap` — 5 NPC spaces, central courtyard, Player Start, NavMesh
- **Configs:** `Content/THRESHOLD/Config/` — DA_Threshold_Apo, DA_Threshold_Pragmatist, DA_Threshold_Friend, DA_Threshold_Keeper, DA_Threshold_TOWCF
- **Social graph:** `Content/THRESHOLD/DA_Graph_ThresholdDefault.uasset` — set as `ActiveGraph` on `BP_NPCGameMode` class defaults
- **GameMode:** `BP_NPCGameMode` Blueprint (wraps `ANPCGameMode`) — set as GameMode Override in Threshold_Compound World Settings; `ActiveGraph` configured in class defaults

---

## Known Open Issues / Future Work

1. LLM API latency (~1–2s/turn) breaks real-time immersion at scale
2. ONNX model accuracy degrades under variable lighting / partial occlusion
3. PAD emotional state is not persisted between sessions (no database layer)
4. Voice cloning ethics + ElevenLabs licensing for shipped games
5. Phases 0–2 complete — immediate priority is Final Review Vertical Slice (The Friend, single-NPC); Phase 2.5 cycle architecture + Phase 7.5 Kimodo animation library are the next full-THRESHOLD milestones

---

## Working Branch

Current active branch: `claude/continue-llm-npc-api-lwC5j`
Main branch: `main`

---

## THRESHOLD — Vertical Slice Design

### Concept
Non-linear, replayable interactive experience. Player returns to a Chinese residential compound they left years ago. 5 AI NPCs knew them. No plot, no objectives, no tutorial.

**The experience is structured as cycles.** Each cycle lasts **13 minutes** — chosen deliberately (liminal, unlucky, just long enough for 3–4 meaningful conversations). Within each cycle, the player moves freely between the 5 NPCs, gathering what they can. When the timer expires, the compound "resets": the player wakes again at the entrance, the same people are still there, and they remember everything — every word of every prior cycle. The NPCs do not regenerate until the player reaches the Return Statement.

**Core mechanic — TESTIMONIAL:** Player is the only node connecting 5 AI minds. They carry what one NPC says to another — live via Whisper STT, in their own words, imperfectly. Each receiving Claude instance responds to the player's specific phrasing unpredictably. Impossible without live voice + LLM inference.

**Gesture layer:** Pinch/Spread/Rotate/Spindle (already implemented in `GestureRecognitionComponent`) map to `EGestureIntent` (Withhold/Disclose/Doubt/Synthesise). Injected into Claude context before voice message — modifies HOW testimony is received, not what is said.

**Facial recognition:** Ambient only (non-gating). Player emotion injected into Claude context; NPC may comment on it. No progression lock.

**AI Notepad:** Player carries a 2015-prototype-aesthetic device (`UNPCNotebookSubsystem` — Phase 4). Separate Claude instance, "thinking partner" prompt. Outputs text + JSON graph update `{nodes, edges, certainty}`. Rendered as `WBP_SocialGraph` — unreliable, probabilistic, can hallucinate connections.

**Return Statement:** Player speaks into the empty courtyard (available at any time) → summary Claude call with compound-as-witness system prompt → ElevenLabs reverberant neutral voice → Phase 1 Ground Truth reveal → Phase 2 hidden titles reveal → **NPC regeneration triggered** (new graph via Claude API, full memory wipe, new run begins).

**Replayability:** The Return Statement is the only trigger for NPC regeneration. Graph Studio generates a fresh `UNPCGraphDataAsset` per run via Claude API call. Different graph = different people = different hidden truth. NPCs persist with full memory across cycles until the player chooses to end the run.

### The Five NPCs (Vertical Slice — Handcrafted Graph)

All NPCs use they/them. `VoiceGender` + `MetahumanVariantPool` randomly assigned per procedural run.

| NPC | Role | Hidden Title (post-run only) | Emotion Baseline |
|-----|------|------------------------------|-----------------|
| **Āpó** | Elder resident, ran compound's social calendar | The One Who Made Peace With It | Trust 0.6 |
| **The Pragmatist** | Retired housing official, processed emigration paperwork | The One Who Translated | Disgust 0.4 (wariness) |
| **The Friend** | Childhood friend, now runs ground-floor convenience store | The One Who Stayed | Sadness 0.5 |
| **The Keeper** | 40-year maintenance worker, been inside every unit | The One Who Watches | Anticipation 0.4 |
| **The One Who Couldn't Forget** | Graduate student, arrived for fieldwork, never left | The One Who Inherited the Story | Anticipation 0.5 |

Hidden titles are never shown during play. Each NPC's `ReflectionAspect` field injects a tonal instruction into their system prompt (how they relate to memory/departure) without stating the meta-design. Pattern only legible post-run when all five titles appear simultaneously.

### Cycle Architecture

**Cycle = one 13-minute session.** Timer runs from the moment the player loads into the compound.

**Soft reset (timer expiry):**
- `UCycleManagerSubsystem` broadcasts `OnCycleExpired`
- Player is teleported back to the entrance (Player Start)
- `CycleNumber` increments; new 13-minute timer starts
- Each `DialogueComponent` receives `InjectCycleBreak(CycleNumber)` — appends a tagged separator `[--- Cycle N ---]` to conversation history so NPCs are aware time has passed
- NPC conversation history is **not cleared** — all prior exchanges carry forward
- `NPCDialogueHUD` shows a subtle cycle counter (e.g. `CYCLE 2`) and countdown timer

**Hard reset (Return Statement):**
- Player speaks into the courtyard → `UCycleManagerSubsystem` broadcasts `OnReturnStatementTriggered`
- Two-phase reveal plays (Ground Truth → hidden titles)
- All `DialogueComponent` histories **cleared**
- Graph Studio generates a new `UNPCGraphDataAsset` via Claude API
- `UNPCConfigDataAsset` instances updated to point to new graph
- Scene reloads / NPCs reinitialised → Cycle 1 begins fresh

**NPC awareness of cycles:**
- The `[--- Cycle N ---]` separator is injected as a `user`-role message in history before the new cycle's first player turn. NPCs naturally pick up on it — they may comment on the repetition, the return, or what feels different without being explicitly scripted to.
- NPCs have no knowledge of cycle count in their system prompt — only what appears in their conversation history.

**Key implementation component:**
- `UCycleManagerSubsystem` (new, `Source/LLM_NPC/Core/`) — `UGameInstanceSubsystem`; fields: `CycleNumber`, `TimeRemainingInCycle` (float, countdown from 780s); delegates: `OnCycleExpired`, `OnReturnStatementTriggered`; called from `NPCPlayerController::Tick` to decrement timer and fire delegate

### Implementation Phases

| Phase | Status | Scope |
|-------|--------|-------|
| 0 — Type Foundation | **Complete** | `EGestureIntent`, `UNPCGraphDataAsset`, soft-deprecated `SystemPrompt`; `FNPCGraphNode.EmotionBaseline` field is the hard-reset target used in Phase 6 |
| 1 — Multi-NPC Refactor | **Complete** | `NPCPlayerController` proximity focus, `NPCDialogueHUD` dynamic binding, compact HUD, click-to-focus; **note:** Phase 2.5 will extend `NPCPlayerController::Tick` (timer) and `NPCDialogueHUD` (cycle UI + `ClearChatHistory()`); Phase 3 will modify `NPCDialogueHUD::SubmitChatMessage` (pass gesture intent) |
| 2 — Graph-Driven Prompts | **Complete** | `BuildSystemPromptFromGraph()`, `BuildAnnotatedContent()`, `GraphNodeID` on `DialogueComponent`, `NPCGameMode::BeginPlay()` graph push + runtime tuning, `PendingRequestVersion` TTS dedup, `DA_Graph_ThresholdDefault` with 5 nodes + 7 edges |
| **A — The Friend's Staging Area** | **Pending (Final Deliverable)** | Dress The Friend's back-room convenience store space in `Threshold_Compound.umap`; 7 `AInspectableItem` actors placed in scene (Old Photograph, Phone Book, Letter, Stack of Cash, Jade Pendant, Chinese Chessboard, Bonsai Tree); no exterior sightlines; Asian female Metahuman asset assigned to `BP_NPC_Friend` |
| **B — InspectableItem NPC Knowledge** | **Pending (Final Deliverable)** | Add `ItemDisplayName`, `ItemWorldDescription`, `NPCKnowledgeText` to `AInspectableItem`; change constructor collision from `NoCollision` to `QueryOnly ECC_Visibility`; add `ItemKnowledgeSummary` to `FNPCGraphNode`; fill The Friend's node in `DA_Graph_ThresholdDefault` |
| **C — Object Inspection Mechanic** | **Pending (Final Deliverable)** | E-key line trace (300cm, `ECC_Visibility`) → `DialogueComponent::SendObjectInspectMessage(AInspectableItem*)` → inject `[Player is examining: {Name} — {Desc}]` as user message; `NPCDialogueHUD::SetInspectHint()` draws examine prompt; `NPCBodyMotionComponent::TriggerReactToItem()` turns NPC head toward item |
| **D — Speaker Identification** | **Pending (Final Deliverable)** | New `USpeakerIdentificationComponent` — MFCC spectral fingerprinting (13 coefficients, 256-pt FFT, 26 mel bins, cosine similarity threshold 0.85); auto-enroll up to 4 speakers as Speaker_A/B/C/D; `WhisperSTTComponent::OnPCMCaptured` delegate broadcasts raw PCM before WAV encode; `DialogueComponent::BuildAnnotatedContent()` prefixes `[Speaker: Speaker_A is speaking]`; The Friend's system prompt instructs her to respond differently to different visitors |
| **E — Animation Variety** | **Partially Complete (code landed Apr 2026)** | Emotion-driven MetaHuman template animation swap via new `UTemplateAnimationDriverComponent` — maps Plutchik → HappyA/B, SadA/B, AngerA/B, FearA/B, SupriseA/B, Idle; A/B variant locked per emotional state; `SettleDelaySeconds` (default 0.2s) smooths transitions. `NPCBodyMotionComponent::bProceduralFKEnabled = false` default (templates play unobstructed); `MetahumanAnimComponent::bUseCurveBasedEmotions = false` default (FACS curve emotion path no longer fights template face animation — lip sync + jaw + blink + thinking overlay still flow through the curve pipeline). `TriggerReactToItem(WorldLoc, Duration)` on `NPCBodyMotionComponent` applies a Head-bone-only additive (±`HeadTurnMaxDeg` clamp, `HeadTurnBlendSpeed` interp, auto-expires) compatible with template body anim driving the rest. **Still TODO:** confirm `FaceTemplateAnimProperty` / `BodyTemplateAnimProperty` names match the actual MetaHuman AnimInstance (dumped to Output Log on BeginPlay); PIE-verify lip sync authority over template mouth curves; if muddled, add `FaceEmotionSlot` Slot node to Face AnimBP and switch to `PlaySlotAnimationAsDynamicMontage` crossfade path. |
| 2.5 — Cycle Architecture | Future | `UCycleManagerSubsystem` (13-min timer, soft/hard reset), `InjectCycleBreak()` in `DialogueComponent`, cycle counter + countdown in `NPCDialogueHUD`; cycle transition UX: fade-to-black + "You find yourself at the gate again." + audio sting; EmotionComponent PAD state persists across soft resets, reset to `EmotionBaseline` only on hard reset |
| 3 — Gesture Layer | Future | `EGestureIntent` caching + injection in `DialogueComponent`; modifies `NPCDialogueHUD::SubmitChatMessage` to pass `PendingGestureIntent` to `SendUserMessage()` |
| 4 — Notebook Subsystem | Future | `UNPCNotebookSubsystem`, `WBP_Notebook`, `WBP_SocialGraph`; persists across soft resets, wiped on hard reset |
| 5 — Procedural Graph Generation | Future | Async Claude API call → new `UNPCGraphDataAsset` JSON → runtime asset; updates all 5 `UNPCConfigDataAsset` pointers before Cycle 1 of new run |
| 6 — Return Statement | Future | Courtyard trigger → `UCycleManagerSubsystem::TriggerReturnStatement()`; two-phase reveal → graph regen → full hard reset |
| 7 — Environment + Polish | Future | `Threshold_Compound.umap` final layout, lighting, ambient audio; per-cycle environmental shifts |
| 7.5 — Kimodo Body Animation Library | **Optional (deferred to multi-NPC)** | Superseded for the single-NPC Friend deliverable by MetaHuman Creator template animations (Phase E, `UTemplateAnimationDriverComponent`). Retained as optional future upgrade once multi-NPC is in scope and the full 5-NPC compound needs per-character-distinct body language. **Offline asset pipeline** — `nvidia/Kimodo-SMPL-X-RP-v1.1` diffusion model → mocap clips → UE5 IK Retarget to Metahuman; would replace procedural sine-wave micro-motions in `NPCBodyMotionComponent` (re-enabled via `bProceduralFKEnabled`) or feed a new Kimodo-driven path. **Use SMPL-X variant, not SOMA-RP** — SOMA is a proprietary 30-joint skeleton with no UE5 retargeter; SMPL-X outputs AMASS format with full cross-platform support. **Hardware:** ~17GB VRAM (RTX 3090/4090 min); if unavailable use HuggingFace browser demo at `huggingface.co/spaces/nvidia/Kimodo` (no GPU required). **Inference:** 2–5s per clip — strictly offline, never runtime. CLI: `kimodo_gen --text "..." --duration 60 --output clip.npz`. Per-NPC-priority Idle/Thinking/Speaking clips, ~15 each, movement quality tuned to each character. |

### Final Review Vertical Slice — The Friend (Single-NPC Scope)

**Deliverable:** Fully playable single-NPC interaction scene with The Friend for academic/portfolio final review. Scoped down from the full 5-NPC THRESHOLD experience per professor feedback (Apr 2026) — demonstrates the complete AI stack in depth on one character, with two new unique mechanics.

**Character:** Asian female Metahuman, mid-to-late 20s. Detailed sourced Metahuman asset assigned to `BP_NPC_Friend`. Childhood friend of the player; stayed behind while the player emigrated; now runs a ground-floor convenience store inside the compound. Sadness 0.5 baseline, low cost to Anticipation when conversation goes somewhere honest. Hidden title: "The One Who Stayed."

**In scope:**
- Single NPC: **The Friend** — graph-driven system prompt via `BuildSystemPromptFromGraph()` using her node in `DA_Graph_ThresholdDefault`
- Full dialogue pipeline: Whisper STT → Claude API → ElevenLabs TTS
- Emotion engine: full PAD state + decay + GOAP transition costs; FACS facial animation; thinking pose overlay
- Lip sync: ElevenLabs character timestamps → visemes → `NPCLipSyncComponent`
- Body motion: `NPCBodyMotionComponent` FSM — **4 states** (Idle / Thinking / Speaking / **Reacting**); idle pose variants (sitting-behind-counter, standing-near-shelves); Kimodo clip library (Phase 7.5) if ready, otherwise procedural micro-motions
- Facial recognition: player emotion injected into Claude context (ambient, non-gating)
- **[NEW] Object Inspection (Phase C):** Player aims at 3D props, presses E → NPC responds from her personal relationship to that object. 7 inspectable items in staging area: Old Photograph (of her and Ashley as teens), Phone Book (the letter is slipped between its pages), Letter (Ashley's words — keystone on Present), Stack of Cash (the 200 yuan she gave that night), Jade Pendant (Ashley's grandmother's), Chinese Chessboard (a half-finished game), Bonsai Tree (cutting from Ashley's family tree). Items have `ItemWorldDescription` (injected into Claude) + `NPCKnowledgeText` (woven into system prompt via `ItemKnowledgeSummary`)
- **[NEW] Speaker Identification (Phase D):** `USpeakerIdentificationComponent` — MFCC fingerprinting, up to 4 auto-enrolled speakers; `[Speaker: Speaker_A is speaking]` prefix in every Claude call; The Friend responds differently to the returning player vs. new visitors to the store
- Graceful degradation: text fallback HUD
- **Staging area (Phase A):** The Friend's back-room convenience store space — warm, slightly cramped, no exterior sightlines. ~500cm × 400cm, low ceiling, counter + shelving + corner nook separated by a beaded curtain or shelving unit

**Out of scope for final review (full THRESHOLD features deferred to future):**
- Multi-NPC proximity focus (Phase 1 infrastructure present but only one NPC active)
- Cycle architecture / 13-minute timer / soft reset (Phase 2.5)
- Gesture intent layer (Phase 3)
- AI Notepad / social graph widget (Phase 4)
- Procedural graph generation (Phase 5)
- Return Statement hard reset (Phase 6)
- Full 5-NPC compound environment + per-cycle lighting shifts (Phase 7)

**The Friend — Kimodo clip brief (Phase 7.5 priority):**

| State | Prompt guidance | Movement quality |
|-------|----------------|-----------------|
| Idle | "person standing behind a counter, weight shifted to one side, occasional glance away, hand resting on surface" | Grounded, slightly inward; young adult, feminine movement quality |
| Thinking | "person pausing mid-conversation, chin slightly lowered, gaze unfocused, breath held" | Still, inward — carries quiet grief |
| Speaking | "person talking warmly but with restraint, small hand gestures, no excess expressiveness" | Warm but contained; grief underneath the warmth |

Generate ~15 clips per state. Age variant: young adult (late-20s). Retarget via UE5 IK Retargeter to Metahuman female skeleton before importing.

---

### Final Review Vertical Slice — "The Memory Archive" (Two-Speaker Pivot, locked 2026-04-29)

**Status:** This section supersedes the prior single-speaker Friend slice above. The single-speaker slice is retained for historical context; the canonical demo design as of 2026-04-29 is below. Full plan file at `~/.claude/plans/okay-i-am-about-peaceful-twilight.md`. Demo: 2026-04-30.

**Audience and contribution.** Primary audience: research-lab interview / PhD application portfolio. Secondary: workshop submission to CHI / DiGRA / alt.chi / RTD. Primary contribution: **speculative / design fiction** — the AI Memory Archive frame as a provocation about consent, witness, and model-mediated testimony. Secondary: **empirical** — a framework supporting a future between-subjects study of multi-human → single-LLM-NPC conversational dynamics.

**Diegetic premise.** The Memory Archive is near-future archival apparatus, built to recover **Ashley** — a child who disappeared from the compound four years ago. Ashley never consented to be archived; her record is reconstructed from secondary sources. **The Friend** — Ashley's neighbour and convenience-store owner, the last person to see Ashley alive — agreed to have her interviews modeled. The Friend that lives in the archive is that model. She remembers consenting. She can revoke consent. She has implicit awareness of being a reconstruction; her dialogue rarely surfaces it.

The slice asserts: *When the model of a witness withdraws consent, what testimony remains?*

**The collective player.** Two human speakers operate the archive interface from outside the diegetic space. They are visible inside as a pair of **chrome robotic hands** — the apparatus's avatar. The Friend can see what the hands hold.

| Tag | Diegetic role | Friend's relational register |
|---|---|---|
| **Speaker_A** | Oral historian; calmer; came to listen | "The visitor whose voice arrives slower. They do not press." |
| **Speaker_B** | Researcher / family-adjacent; sharper | "The visitor whose voice presses. You feel the weight of what you have not said when they speak." |

**Two distinct item verbs (`AInspectableItem`).**
- **E (Pickup → Inspect)** — robotic hand grabs item; mouse drag rotates, scroll scales (uses existing `ApplyRotation`/`ApplyScale`); item NOT in Friend's sightline; **no Claude turn fires** — state is silently tracked. E again puts item back. Walk locked while held.
- **F (Present)** — robotic hand extends item forward into Friend's sightline; **fires Claude turn** with payload `[Speaker_X presents to you: {ItemDisplayName}. They see: {ItemWorldDescription}. Your private knowledge: {NPCKnowledgeText}]`.
- **Q (Drop)** — release back to original transform.
- Per-item / per-speaker memory in `UDialogueComponent`: `TMap<FName, TSet<FName>> InspectedBy` and `PresentedBy`.

**Soft doubt mechanic.** Friend's default posture is mild scepticism toward unanchored claims: she asks gently how the visitor came to know. Inspecting the relevant item privately drops the doubt; presenting an object makes acknowledgment full; sufficiently grounded/specific/emotionally credible language can overcome doubt without evidence. Implemented entirely in the system prompt (§7.10) — no C++ doubt-detection.

**Speaker identification (hybrid acoustic + manual).**
- `WhisperSTTComponent::OnPCMCaptured(const TArray<int16>&, int32 SampleRate)` delegate broadcasts captured PCM **before** WAV encoding.
- New `USpeakerIdentificationComponent` (`Source/LLM_NPC/Dialogue/`): 4-dim spectral-band-energy fingerprint (0–500/500–1500/1500–3000/3000–8000Hz) using UE's `Audio::FFFTAlgorithm` (`SignalProcessing` module); auto-enrolls up to 2 `FSpeakerProfile`s; cosine similarity > 0.85 to match; `OnSpeakerIdentified(FName, float)` delegate.
- Number keys **1**/**2** force-override the next utterance's tag (demo safety net).
- `[Speaker_X is speaking]` prefix added to user message in `BuildAnnotatedContent`.
- `BuildSystemPromptFromGraph` adds **§7.5 Visitors register** (the two relational registers verbatim).

**Hard-gated topic matrix (in system prompt).** Each topic requires (a) specific items inspected/presented AND (b) per-speaker trust threshold; topics not unlocked are silently deflected (subject change / pause). The keystone topic *"I have kept the letter"* is gated on **Present**, not Inspect — formally showing the letter is the act that breaks her last reservation.

| Topic | Item gate | Emotion gate |
|---|---|---|
| "Ashley came that night" | Photograph + Phone Book inspected | Trust ≥ 0.3 (active speaker) |
| "She was wearing her grandmother's pendant" | Jade Pendant inspected | Trust ≥ 0.3 |
| "She asked for money" | Stack of Cash + Phone Book inspected | Trust ≥ 0.4 |
| "There was a letter" | Phone Book inspected | Trust ≥ 0.5 |
| "I have kept the letter" | Letter **presented** | Trust ≥ 0.6 |
| "We were closer than I have said" | Chinese Chessboard inspected | Trust ≥ 0.4 |
| "I have not stopped grieving" | Bonsai Tree inspected | Trust ≥ 0.5 (any speaker) |

**Seven items (in `Threshold_Compound`, Friend's back-room store).** Each `AInspectableItem` has `ItemDisplayName`, `ItemWorldDescription` (what speaker sees), `NPCKnowledgeText` (Friend's secret), `ItemID` (FName for gate matching): Old Photograph (`old_photograph`), Phone Book (`phone_book`), Letter (`letter` — slipped inside the phone book), Stack of Cash (`cash_stack`), Jade Pendant (`jade_pendant`), Chinese Chessboard (`chessboard`), Bonsai Tree (`bonsai_tree`).

**Three branches (deterministic state-hint, future-emergent toggle via `bDeterministicBranchHint`).**
- **Convergent Disclosure** — both speakers trust ≥ 0.5, aligned tonal registers, keystones inspected and at least one presented in coordinated order → Friend gives full account addressed to "both of you."
- **Divergent Fragmentation** *(LLM-novel)* — speakers reached trust at different times, contradictory tonal registers → Friend addresses each by name in turn; gives Speaker_A one piece, Speaker_B a different piece; truth asymmetric. Per-speaker memory is the technical novelty.
- **Recursive Silence (Consent Withdrawal)** *(speculative-design core)* — dominant Pinch-Withhold, OR one speaker silent, OR climax window passes without item gates → model determines real Friend would not have wanted this conversation continued. HUD `SUBJECT CONSENT: GRANTED` → `REVOKED`; archive link severs. Consent withdrawal on source's behalf is the same act as the conversational refusal.

A small C++ helper (`§7.7 branch-eligibility hint`) computes per-turn: per-speaker turn counts, gesture-intent rolling averages, items inspected/presented per speaker, per-speaker trust estimates → prepends as structured observation block to system prompt; Claude makes the climax call.

**HUD (matter-of-fact archive instrument).** Top bar: `ARCHIVE LINK ACTIVE | SUBJECT: Ashley Wei [posthumous reconstruction, no consent] | TESTIMONY: The Friend [consent: GRANTED]`. Speaker chip top-left: `SPEAKER A`/`B` + confidence bar. Item hint near reticle: `E Pick up {Name}`. Held: `F Present | Q Put back`. Status: `1/2 override speaker`. On Recursive-Silence: TESTIMONY line flips `[consent: REVOKED]`, link greys, fade.

**Closing card (layered, 6s hold).** Dynamic Friend's last line + fixed provocation `When the model of a witness withdraws consent, what testimony remains?` + run-determined branch label.

**Empirical layer.** `UMemoryArchiveLogger` (`Source/LLM_NPC/Core/`, `UGameInstanceSubsystem`) writes per-turn JSONL to `Saved/MemoryArchive/session-{timestamp}.jsonl` (speaker, gesture, emotion, interaction type, items per speaker, trust per speaker, branch hint, full Claude payload + response) + auto-exports Markdown transcript on session end. Future studies can plug in directly.

**Player pawn.** First-person `BP_ArchiveOperator` subclassing UE5 `FirstPerson` template character. Stock arms mesh + `MI_RoboticHand` material instance (chrome/holographic, thin emissive wireframe seams over darker base). Walking locked while holding an item.

**The Friend metahuman.** The current Friend metahuman is newly authored and assigned to `BP_NPC_Friend.uasset` in `Content/THRESHOLD/Blueprints/`. The mesh assets themselves live at `Content/THRESHOLD/MetaHuman/` — **this path is `.gitignored`** (per the gitignore comment: "MetaHuman assets under THRESHOLD — re-downloadable from Quixel Bridge / MetaHuman Creator. Individual .uasset files here routinely exceed GitHub's 100 MB per-file cap"). The legacy `Content/MetaHumans/Hana/` directory is committed but stale; ignore it for the slice. The canonical Friend mesh exists only on the UE-enabled work machine and is referenced by `BP_NPC_Friend`. Anything that needs to verify mesh assignment must happen in the editor on the work machine.

**Build order (graceful degradation — slice demos coherently from end of each tier):**
| Tier | Hours | Status | Scope |
|------|-------|--------|-------|
| 0 | 2.5 | **Complete (2026-04-29)** | `AInspectableItem` narrative fields + collision; `SendObjectPresentMessage`; gesture wire-up; §7.5/§7.10 prompt sections; Friend graph rewrite; Friend mesh + anim driver wiring on `BP_NPC_Friend` |
| 1 | 4 | **Complete (2026-04-30)** | FP pawn (UE5 FP feature pack, no dedicated `BP_ArchiveOperator`); 7 items renamed + placed; E pickup/drop + RMB-yaw rotate + scroll scale; F present; per-speaker `InspectedBy`/`PresentedBy`; `Speaker_A` placeholder; auto-voice on vicinity + 1s VAD; LCtrl crouch; FPS-style continuous mouse look; ElevenLabs v3 + audio-tag prompt; voice-ID dual-write fix |
| 2 | 2.5 | **Complete (2026-04-30)** | Whisper `OnPCMCaptured` hook; `USpeakerIdentificationComponent` (hand-rolled loudest-window DFT, 4-band fingerprint, no SignalProcessing dep); 1/2 manual override; speaker chip on HUD top-left; `[Speaker_X is speaking]` prefix; per-speaker memory writes use resolved tag |
| 3 | 3 | Pending | Per-speaker trust estimate; §7.7 branch hint; §7.9 climax instruction; closing card; consent indicator; `UMemoryArchiveLogger` |
| 4 | 2 | Pending | Polish: scanline PP material, hand wireframe refinement, archive console prop, HUD aesthetic pass |

**Cuttable in this order if behind:** Tier 4 polish → items #5/#6 → logger → §7.7 hint (let Claude infer) → Recursive-Silence branch → acoustic speaker ID (ship manual-only) → animation variant B.

**Tier 1 cuts already taken (2026-04-30):** `BP_ArchiveOperator` C++ pawn dropped (state lives on `ANPCPlayerController`); `MI_RoboticHand` chrome material dropped (stock FP arms); walk-lock dropped (user override — walking while holding is better UX). Climax interactions and per-speaker memory still intact.

**Memory Archive — Tier 0 complete (2026-04-29):**
- `AInspectableItem` ([Source/LLM_NPC/Gesture/InspectableItem.h](Source/LLM_NPC/Gesture/InspectableItem.h) + [.cpp](Source/LLM_NPC/Gesture/InspectableItem.cpp)) — added `ItemID` (FName), `ItemDisplayName`, `ItemWorldDescription`, `NPCKnowledgeText`; new `InteractionSphere` `USphereComponent` (`QueryOnly`, blocks `ECC_Visibility` only, ignores all other channels); mesh remains `NoCollision`; `InteractionRadius` defaults to 40 cm and is synced from UPROPERTY on BeginPlay
- `UDialogueComponent::SendObjectPresentMessage(AInspectableItem*, const FDetectedUserEmotion&, EGestureIntent)` ([DialogueComponent.cpp:211-319](Source/LLM_NPC/Dialogue/DialogueComponent.cpp#L211-L319)) — builds the structured payload `[The visitor presents to you: {Name}. The item is now in your sightline. They see: {ItemWorldDescription}. Your private knowledge of this object: {NPCKnowledgeText}]`, passes through `BuildAnnotatedContent` so gesture/emotion annotations sit in canonical position, then routes to Claude with the same graph-driven system prompt path as `SendUserMessage`
- `UDialogueComponent::SendUserMessage` gains `EGestureIntent GestureIntent = EGestureIntent::None` parameter ([DialogueComponent.h:57-59](Source/LLM_NPC/Dialogue/DialogueComponent.h#L57-L59)); the existing 2-arg call sites (`NPCAIController.cpp:44`, `NPCDialogueOverlay.cpp:201`) compile unchanged via the default
- **§7.5 Visitors register** + **§7.10 Apparatus + Soft Doubt** prompt sections live in `BuildSystemPromptFromGraph` ([DialogueComponent.cpp:505-543](Source/LLM_NPC/Dialogue/DialogueComponent.cpp#L505-L543)) — assembled in C++, NOT stored on the graph node, gracefully degrade to single-speaker when no `[Speaker_X]` tag is present (Tier 2+ adds the tags)
- **Gesture wire-up closed end-to-end** — before this tier, `PendingGestureIntent` was cached in `ANPCPlayerController` (Phase 1) but never read by the HUD; `SubmitChatMessage` was passing `EGestureIntent::None` to Claude on every turn. Fixed by [NPCDialogueHUD.cpp:281-292](Source/LLM_NPC/Core/NPCDialogueHUD.cpp#L281-L292) — single canonical consumption point for both Enter-submit and voice-transcript flows; pulls intent from `GetOwningPlayerController()` cast to `ANPCPlayerController`, passes to `SendUserMessage`, clears it on the controller. Removed the now-redundant clear that was at `NPCPlayerController.cpp:99`. Focus-switch clear at `NPCPlayerController.cpp:217` retained — different reset condition.
- `Content/THRESHOLD/DA_Graph_ThresholdDefault.uasset` — Friend graph node rewritten in-editor with the canonical text from this CLAUDE.md (binary asset, work-machine only)
- `Content/THRESHOLD/Blueprints/BP_NPC_Friend.uasset` — Friend mesh + `UTemplateAnimationDriverComponent` configured in-editor (binary asset, work-machine only; `Content/THRESHOLD/MetaHuman/` is gitignored)

**Memory Archive — Tier 1 complete (2026-04-30):**
- **Per-speaker memory** in [DialogueComponent](Source/LLM_NPC/Dialogue/DialogueComponent.h) — `TMap<FName, TSet<FName>> InspectedBy` and `PresentedBy` (non-UPROPERTY; UE reflection rejects `TMap<FName, TSet<FName>>`); `RecordItemInspection(ItemID, SpeakerID)` idempotent helper; `static FName GetDefaultSpeakerID()` returns `"Speaker_A"` as Tier 2 placeholder. Both maps cleared in `ClearConversationHistory`. `PresentedBy` is written inside `SendObjectPresentMessage` after dispatch ([DialogueComponent.cpp:329-336](Source/LLM_NPC/Dialogue/DialogueComponent.cpp#L329-L336)). Tier 3 gating reads these directly from C++.
- **E / F / Q / RMB-drag / scroll** all on [NPCPlayerController](Source/LLM_NPC/Core/NPCPlayerController.cpp) — no dedicated `AArchiveOperator` C++ pawn. `TraceForInspectable()` does a 300 cm `ECC_Visibility` line trace from `PlayerCameraManager`; E picks up (writes `InspectedBy` for `Speaker_A`); F presents (calls `SendObjectPresentMessage`, fires Claude turn); E-while-holding or Q drops (`ResetTransform()` + restore world location). **Held item follows camera** in `TickHeldItem()` via per-frame `SetActorLocation(CamLoc + Forward·X + Right·Y + Up·Z)` from `HoldOffset` (default `70/15/-15`).
- **RMB-drag yaw rotate + camera lock** — while holding AND RMB held, mouse-X drives `Item->ApplyRotation(yaw-only)`; mouse-Y is intentionally ignored (strict horizontal axis); `SetIgnoreLookInput(true/false)` toggled on RMB state-change so the viewport never moves during a drag. `bWasIgnoringLook` tracks edge transitions to keep the internal `IgnoreLookInput` counter balanced; restored on drop in case the player drops mid-drag.
- **Walk-lock removed** — original Tier 1 plan locked movement while holding; user override (2026-04-30) keeps walking active for better in-context inspection. `DisableMovement()` / `SetMovementMode(MOVE_Walking)` calls were stripped from `PickupItem` and `DropHeldItem`.
- **Auto-voice on NPC vicinity** with **1-second VAD silence segmentation** — V push-to-talk fully removed; V is now a regular text-input letter. `UpdateNPCFocus()` calls `WhisperSTTComponent::StartRecording()` on focus gain and `StopRecordingAndTranscribe()` on focus loss. [WhisperSTTComponent](Source/LLM_NPC/Dialogue/WhisperSTTComponent.cpp) now ticks while recording: each tick samples last ~200 ms peak amplitude (PCM int16 → normalized 0..1); after `MinSpeechDurationSec` (0.3 default) of speech AND `MinSilenceDurationSec` (1.0 default) of subsequent silence, `DispatchSegmentAndContinue()` snapshots PCM under the existing `PCMLock`, clears the buffer, sends to Whisper, and recording **continues uninterrupted** in the same `waveIn` session. Tunable UPROPERTYs: `bAutoSegmentOnSilence`, `SilenceThreshold` (default 0.02), `MinSilenceDurationSec`, `MinSpeechDurationSec`.
- **`[Currently holding: ...]` annotation** on user messages — `SendUserMessage` gains optional `AInspectableItem* HeldItem = nullptr` parameter ([DialogueComponent.h:60-62](Source/LLM_NPC/Dialogue/DialogueComponent.h#L60-L62)); `BuildAnnotatedContent` prepends a held-item block with `ItemDisplayName` + `ItemWorldDescription` + `NPCKnowledgeText` so Claude can route follow-up speech through the per-item knowledge. HUD pulls the held item from `ANPCPlayerController::GetHeldItem()` and threads it through. The annotation is distinct from a Present (`[The visitor presents to you: ...]`); the system prompt §7.10 distinguishes them so first-Present is curt and follow-up speech-while-holding divulges more.
- **§7.10 rewrite — curt-on-present, divulge-on-follow-up, varied-per-item** ([DialogueComponent.cpp:528-573](Source/LLM_NPC/Dialogue/DialogueComponent.cpp)) — first Present forces a brief acknowledgment anchored in one specific detail of that item (no generic "what is that"); subsequent speech with `[Currently holding: ...]` context unlocks layered detail gradually, "as the conversation earns it." Anchors per-item variety to `NPCKnowledgeText`.
- **§8.7 ElevenLabs v3 audio tags + text-shape rules** ([DialogueComponent.cpp:578-654](Source/LLM_NPC/Dialogue/DialogueComponent.cpp)) — curated v3-documented tag whitelist for the Friend's grief register (`[sigh]`, `[quietly]`, `[pauses]`, `[hesitates]`, `[resigned tone]`, `[whispers]`, `[flatly]`, `[sorrowful]`); explicit blacklist of tags that betray her character (`[laughs]`, `[excited]`, `[playfully]`, etc.); plus six labeled text-shape rule categories (PAUSES & BREATH, SENTENCE LENGTH & FRAGMENTS, EMPHASIS, INTONATION, CONTRACTIONS & WORD CHOICE, FILLER) with in-character examples. Default ElevenLabs `ModelID` switched from `eleven_flash_v2_5` → `eleven_v3` ([ElevenLabsTTSComponent.h:120-134](Source/LLM_NPC/Dialogue/ElevenLabsTTSComponent.h)) since only v3 honors inline audio tags.
- **Voice-ID dual-write fix (the voice was flipping)** — both `DialogueComponent::OnClaudeResponseReceived` and `ANPCCharacter::OnDialogueResponse` were calling `TTS->SpeakText` for every Claude response with **different voice-ID resolution priorities**. `PendingRequestVersion` deduped them so only one played, but whichever fired last won — voice flipped turn-to-turn. Fixed by removing the `SpeakText` call from `DialogueComponent::OnClaudeResponseReceived` ([DialogueComponent.cpp:383-394](Source/LLM_NPC/Dialogue/DialogueComponent.cpp)) — the component now only broadcasts `OnDialogueResponseReceived`. `ANPCCharacter::OnDialogueResponse` is the **single owner of TTS dispatch** ([NPCCharacter.cpp:91-153](Source/LLM_NPC/Core/NPCCharacter.cpp)) and now resolves voice ID with the same `Graph node ElevenLabsVoiceID > NPCConfig->ElevenLabsVoiceID` priority that used to live in the dialogue component, while keeping its emotion-driven stability/style modulation in one place.
- **Crouch via Left Ctrl + C fallback** ([NPCPlayerController.cpp:222-243](Source/LLM_NPC/Core/NPCPlayerController.cpp)) — toggle (not hold-to-crouch); uses `MoveComp->IsCrouching()` for state instead of direct `bIsCrouched` bitfield access; gated on `bTextActive` so it doesn't fire while typing. Camera-Z drop on crouch is handled in-engine via Capsule Half Height + Crouched Half Height tuning to match the level's 4.2 m world scale (Capsule Half Height = 210, Crouched Half Height = 105, Mesh Z = -210, Camera attached to capsule directly with Z ≈ 180). The C key parallel binding can be removed for the demo if desired.
- **FPS-style continuous mouse-look** ([NPCPlayerController.cpp:42-69](Source/LLM_NPC/Core/NPCPlayerController.cpp)) — constructor now sets `bShowMouseCursor = false`; `BeginPlay` calls `SetGameOnlyInputMode()` instead of `FInputModeGameAndUI`; chat overlay defaults `bDialogueVisible = false` ([NPCDialogueHUD.h:62-63](Source/LLM_NPC/Core/NPCDialogueHUD.h)); `Tick` flips between modes via `SetGameOnlyInputMode()` / `SetGameAndUIInputMode()` whenever `HUD->IsDialogueVisible()` transitions, so PIE drops you straight into FPS look and **T** opens the chat overlay (cursor visible) for click-to-focus typing.
- **Enhanced Input registration** — `IMC_Default` and `IMC_MouseLook` are loaded via `ConstructorHelpers::FObjectFinder` (paths `/Game/Input/IMC_Default` and `/Game/Input/IMC_MouseLook`) into `DefaultMappingContexts` UPROPERTY; `OnPossess` registers them with the local player's `UEnhancedInputLocalPlayerSubsystem`. This is the UE 5.4+ canonical place — equivalent to what `BP_FirstPersonPlayerController` does in the FP feature pack. Without this, the FP pawn's IA bindings never fire because no IMC is active for the local player.
- **7 items renamed and refilled** — replaced the old set (`store_ledger`, `folded_note`, `cash_box`, `wall_polaroid`, `train_ticket`, `jade_plant`, `old_photograph`) with the level-author's chosen new set: `old_photograph`, `phone_book`, `letter`, `cash_stack`, `jade_pendant`, `chessboard`, `bonsai_tree`. Friend's `WithheldTruth`, `MisrememberedDetail`, the Hard-gated topic matrix, and TIER1_HANDOFF.md were all updated to match. Each item has canonical `ItemWorldDescription` + `NPCKnowledgeText` filled in-editor on the work machine.

**Files modified (summary, Tier 1):**
- `Source/LLM_NPC/Core/NPCPlayerController.h/.cpp` — `HeldItem` (TWeakObjectPtr), E/F/Q/LCtrl bindings, `TraceForInspectable`, `TickHeldItem` (yaw-only RMB rotate, scroll scale, camera-follow), `GetHeldItem()` getter, `DefaultMappingContexts` UPROPERTY array + `OnPossess` IMC registration, `SetGameOnlyInputMode`/`SetGameAndUIInputMode` helpers, FPS mouse-look default
- `Source/LLM_NPC/Dialogue/DialogueComponent.h/.cpp` — `InspectedBy`/`PresentedBy` maps, `RecordItemInspection`, `GetDefaultSpeakerID`, `HeldItem` parameter on `SendUserMessage`, held-item annotation in `BuildAnnotatedContent`, §7.10 rewrite (curt/divulge/varied), §8.7 v3 audio tags + text-shape rules, removal of redundant `SpeakText` call
- `Source/LLM_NPC/Dialogue/WhisperSTTComponent.h/.cpp` — VAD: `bAutoSegmentOnSilence`, `SilenceThreshold`, `MinSilenceDurationSec`, `MinSpeechDurationSec` UPROPERTYs; `TickComponent` runs RMS-based silence detection; `DispatchSegmentAndContinue` snapshot+send without stopping `waveIn`; `ComputeRecentPeakAmplitude` helper. `PrimaryComponentTick.bCanEverTick = true`.
- `Source/LLM_NPC/Dialogue/ElevenLabsTTSComponent.h` — default `ModelID` switched to `eleven_v3` for inline audio-tag support
- `Source/LLM_NPC/Core/NPCCharacter.cpp` — single source of truth for TTS dispatch with graph-priority voice ID resolution, including new `NPCGraphDataAsset` include
- `Source/LLM_NPC/Core/NPCDialogueHUD.h/.cpp` — `bDialogueVisible = false` default; `SubmitChatMessage` pulls held item from PC and threads to `SendUserMessage`; `InspectableItem.h` include for the new param
- `Content/Maps/Threshold_Compound.umap` — 7 items placed (work machine), Friend's back-room space dressed, scale tuned to 4.2 m world; `BP_NPC_Test` removed from level for demo cleanliness
- `Content/THRESHOLD/DA_Graph_ThresholdDefault.uasset` — Friend node `WithheldTruth` and `MisrememberedDetail` rewritten to reference the new 7-item set
- World Settings: GameMode Override = `BP_NPCGameMode`; Default Pawn Class = `BP_FirstPersonCharacter` (FP feature pack); BP_FirstPersonCharacter has FirstPersonCamera reparented under CapsuleComponent at Z ≈ 180 to fit the world scale; Capsule Half Height 210, Crouched Half Height 105, Mesh Z -210; `Can Crouch` enabled on CharacterMovement
- Project Settings → Engine → Input → Default Input Component Class = `EnhancedInputComponent` (verified, was a build-time fight earlier)
- `CLAUDE.md` — Hard-gated topic matrix, Friend graph node text, Files-modified table, Build-order Tier 1 row, Memory-Archive Tier 1 complete block all updated

**What was deliberately NOT done in Tier 1 (Tier 2+ scope):**
- Acoustic speaker identification (`USpeakerIdentificationComponent`) — Tier 2 owns the spectral-band-energy fingerprinting. Until then, all `InspectedBy`/`PresentedBy` writes use `Speaker_A`.
- 1 / 2 manual speaker override keys — Tier 2.
- `[Speaker_X is speaking]` prefix on annotated user messages — Tier 2.
- Per-speaker trust estimate, §7.7 branch hint, §7.9 climax instruction, closing card, consent indicator — Tier 3.
- `UMemoryArchiveLogger` — Tier 3.
- `BP_ArchiveOperator` C++ pawn class — collapsed onto `ANPCPlayerController` for time, per the cuttable order. Re-extract later if multi-NPC scope returns.
- `MI_RoboticHand` chrome material instance — Tier 4 polish.
- Scanline post-process material, archive console prop, HUD aesthetic pass — Tier 4.

**Memory Archive — Tier 2 complete (2026-04-30):**
- **`FOnPCMCaptured` delegate** on [WhisperSTTComponent](Source/LLM_NPC/Dialogue/WhisperSTTComponent.h) — `(const TArray<uint8>& PCMBytes, int32 SampleRate)`. Broadcast immediately before `EncodeAsWAV` in both `DispatchSegmentAndContinue` and `StopRecordingAndTranscribe` ([.cpp](Source/LLM_NPC/Dialogue/WhisperSTTComponent.cpp)). Carries int16 LE bytes; consumers reinterpret. Delegate uses `TArray<uint8>` not `TArray<int16>` because UHT rejects `TArray<int16>` in `BlueprintAssignable` / `BlueprintCallable` reflection.
- **NEW `USpeakerIdentificationComponent`** ([SpeakerIdentificationComponent.h](Source/LLM_NPC/Dialogue/SpeakerIdentificationComponent.h) + [.cpp](Source/LLM_NPC/Dialogue/SpeakerIdentificationComponent.cpp)) — sibling of WhisperSTT on `ANPCCharacter`. Auto-binds in `InitializeSubsystem` via `FindComponentByClass<UWhisperSTTComponent>`, subscribes to `OnPCMCaptured`, computes 4-dim spectral-band-energy fingerprint (0-500 / 500-1500 / 1500-3000 / 3000-8000 Hz), matches against up to `MaxSpeakers` (default 2) `FSpeakerProfile` centroids via cosine similarity, threshold `MatchThreshold` (default 0.85). Auto-enrolls on miss; falls back to closest profile if at max with no match. Manual override consumed once on next utterance and trains the override-tag's profile. Running-average centroid update with re-normalization. Broadcasts `OnSpeakerIdentified(FName Tag, float Confidence)`.
- **Hand-rolled DFT, no `SignalProcessing` module dep** — `Audio::FFFTAlgorithm` was the handoff-doc plan but adds module surface area. Fingerprint is hand-rolled Hann-windowed magnitude spectrum at 64 bins (~125 Hz/bin), summed into 4 bands, L2-normalized. Cost: 4096 samples × 64 bins × 2 trig-mults ≈ 524k ops per utterance. Once per VAD dispatch — trivially cheap. Bonus: `LLM_NPC.Build.cs` unchanged.
- **Loudest-window fingerprint** ([SpeakerIdentificationComponent.cpp `ComputeFingerprint`](Source/LLM_NPC/Dialogue/SpeakerIdentificationComponent.cpp)) — VAD dispatches the whole rolling buffer including leading silence (recording starts at PIE entry; user typically speaks several seconds in). Initial implementation fingerprinted bytes 0..4096 of the buffer, which for long silences is ambient noise — the same speaker's two utterances would produce slightly different ambient-noise fingerprints and false-enroll as `Speaker_A` and `Speaker_B`. Fix: scan the utterance in 256-sample strides, find the contiguous 4096-sample window with highest summed energy, run the DFT on that. Adds ~10M ops per dispatch (a few ms once per turn, negligible).
- **`FSpeakerProfile` USTRUCT** — `FName Tag` (`Speaker_A`/`Speaker_B`), L2-normalized 4-element `Centroid`, `int32 SampleCount`, `float LastSeenTimeSec`. `MakeSpeakerTag(int32 Index)` synthesizes the FName from `'A' + Index`. Stalest-profile replacement when manual override targets a tag not yet enrolled and `Profiles` is at cap.
- **Speaker tag threading** — new `FName SpeakerTag = NAME_None` parameter on `UDialogueComponent::SendUserMessage`, `SendObjectPresentMessage`, `BuildAnnotatedContent` ([DialogueComponent.h](Source/LLM_NPC/Dialogue/DialogueComponent.h)). `[Speaker_X is speaking]` prefix is the FIRST line of annotated content (before held-item, gesture, emotion) so Claude reads "who" before "what." Gracefully omitted when tag is `NAME_None` — the §7.5 prompt section degrades to single-speaker, which is the demo path.
- **Per-speaker memory writes** — `PresentedBy.FindOrAdd(Item->ItemID).Add(SpeakerTag.IsNone() ? GetDefaultSpeakerID() : SpeakerTag)` in `SendObjectPresentMessage`. `RecordItemInspection(Item->ItemID, LastSpeakerTag.IsNone() ? GetDefaultSpeakerID() : LastSpeakerTag)` in `ANPCPlayerController::PickupItem`. `GetDefaultSpeakerID()` retained as the fallback when nothing has been identified yet.
- **Controller plumbing** ([NPCPlayerController.h/.cpp](Source/LLM_NPC/Core/NPCPlayerController.cpp)) — `PendingSpeakerTag` (consumed on dispatch, mirrors `PendingGestureIntent`); `LastSpeakerTag` + `LastSpeakerConfidence` (sticky, HUD-facing); `HandleSpeakerIdentified` UFUNCTION caches both. `UpdateNPCFocus` binds/unbinds `OnSpeakerIdentified` and clears the SpeakerID component's manual override on focus loss. `PendingSpeakerTag` cleared on focus switch alongside `PendingGestureIntent`; `LastSpeakerTag` intentionally NOT cleared so the chip stays visible.
- **1 / 2 manual override** — edge-detected key bindings in `Tick`, gated on `!bTextActive`. Calls `FocusedNPC->SpeakerIdentificationComponent->SetManualOverrideTag("Speaker_A")` or `Speaker_B`. The override is consumed by the next `IdentifyFromPCM` call and also trains that tag's centroid on the actual voice (so flipping back via the other key still works against fresh acoustic data).
- **Speaker chip on HUD** ([NPCDialogueHUD.cpp `DrawHUD`](Source/LLM_NPC/Core/NPCDialogueHUD.cpp)) — top-left rect (170×30 px) drawn whenever `bDialogueVisible && !PC->LastSpeakerTag.IsNone()`. Renders `SPEAKER A · 0.92` style label by `ToUpper`-ing the FName and replacing `SPEAKER_` with `SPEAKER `, plus 2-decimal confidence.
- **HUD `SubmitChatMessage` consumes the speaker tag** alongside gesture and held-item. Single canonical consumption point for both Enter-submit and voice-transcript flows. Threaded into `SendUserMessage(Message, Emotion, Gesture, HeldItem, SpeakerTag)`.
- **`ANPCCharacter` adds `SpeakerIdentificationComponent`** as default subobject ([NPCCharacter.cpp](Source/LLM_NPC/Core/NPCCharacter.cpp) constructor), sibling of `WhisperSTTComponent`. Inherited by `BP_NPC_Friend` automatically — no in-editor wiring needed.

**QoL session changes that landed alongside Tier 2 (2026-04-30):**
- **NEW `UNPCEyeTrackingComponent`** ([NPCEyeTrackingComponent.h](Source/LLM_NPC/Animation/NPCEyeTrackingComponent.h) + [.cpp](Source/LLM_NPC/Animation/NPCEyeTrackingComponent.cpp)) — sibling of `MetahumanAnimComponent`. Each `TG_PostUpdateWork` tick: project player camera → head bone direction onto actor's local frame, clamp yaw / pitch to physical eye range, smooth via `FInterpTo`, write the 8 ARKit `eyeLookOut_L/R`, `eyeLookIn_L/R`, `eyeLookUp_L/R`, `eyeLookDown_L/R` curves through `MetahumanAnimComponent::SetFaceCurve` (made public for this purpose). Inside `PeripheralYawDeg=70°` / `PeripheralPitchDeg=35°` cone the eyes track; outside they smoothly return to neutral. Eye curves don't overlap with any emotion or viseme curve so no contention with the existing pipelines.
- **Faster emotion decay** ([NPCGameMode.cpp:62](Source/LLM_NPC/Core/NPCGameMode.cpp)) — `EmotionDecayRate` 0.003 → 0.015 (~5 minutes → ~65 seconds for full intensity to fade). Friend doesn't stay locked in Sadness during long silences.
- **Auto-Idle template return after speaking** ([TemplateAnimationDriverComponent.h/.cpp](Source/LLM_NPC/Animation/TemplateAnimationDriverComponent.cpp)) — new `IdleReturnDelaySeconds` UPROPERTY (default 1.75s). Subscribes to TTS `OnSpeechStarted`/`OnSpeechFinished`/`OnSpeechError`. On Finished, schedules a timer; on expiry forces `ApplyTemplate(Idle)` and resets `LastHandledEmotion = Neutral` so the next emotion change still drives a transition. `HandleDialogueResponse` and `OnSpeechStarted` cancel any in-flight timer so a new turn doesn't snap to idle mid-conversation. EmotionComponent state untouched — voice modulation, FACS curves, lip sync still use the real emotion.
- **Echo gate on the mic** ([WhisperSTTComponent.h/.cpp](Source/LLM_NPC/Dialogue/WhisperSTTComponent.cpp)) — fixes external-speaker bleed-through. New `bMicGated` flag read by the `WaveInCallback` (audio thread) and written from the game thread on TTS start/finish. Buffer context (`FWaveInBufferContext`) gains `bool* GatePtr`; gated samples are dropped before `RecordedPCM->Append` (waveIn buffer is still re-armed for continued recording, no device-restart cost). `TTSCooldownSec` UPROPERTY (default 0.4s) absorbs trailing speaker-decay / room reverb after audio ends. Watchdog timer scheduled at `OnSpeechStarted` for `audio_duration + cooldown` seconds (audio duration captured from `OnTTSAlignmentReceived` last char's `StartTime + Duration`). The watchdog is necessary because `UAudioComponent::OnAudioFinished` does NOT reliably fire for `USoundWaveProcedural` — the queue drains but the component thinks more samples might still arrive; `OnSpeechFinished` is unreliable as a result. If `OnSpeechFinished` does fire (e.g. via `SetSound`-on-existing-audio path triggering the prior sound's natural-finish), the handler cancels the watchdog and runs the shorter post-speech cooldown instead.
- **Mic lifecycle decoupled from focus** — `WhisperSTTComponent::bAutoStartOnInit` UPROPERTY (default true) auto-starts `waveIn` once at PIE entry; `ANPCPlayerController::UpdateNPCFocus` no longer calls `StartRecording` / `StopRecordingAndTranscribe` on focus changes. Single-speaker slice: focus flicker (chat-overlay mode flips, sub-degree mouse-look jitter at the proximity boundary) used to tear down + restart waveIn on every flicker tick, resetting VAD state and producing 0-byte captures forever after the first NPC turn played. Now the mic stays open; VAD continues accumulating; the echo gate handles TTS bleed; transcripts route via the HUD's `BoundSTT` subscription rebound by `SetFocusedNPC`. Flip `bAutoStartOnInit = false` if multi-NPC contention over the device returns.
- **Focus hysteresis** ([NPCPlayerController.cpp `FindNearestNPCInRange`](Source/LLM_NPC/Core/NPCPlayerController.cpp)) — different thresholds for gain vs keep. Gain: distance ≤ `InteractionRadius` AND facing dot ≥ 0.1. Keep: distance ≤ `InteractionRadius * 1.25` AND facing dot ≥ -0.3. Sub-degree mouse-look jitter at the boundary no longer flips focus tick-to-tick (which was the underlying cause of the recording cycling above; now belt-and-suspenders alongside the always-on mic).

**Files modified (summary, Tier 2 + QoL session):**
- `Source/LLM_NPC/Dialogue/WhisperSTTComponent.h/.cpp` — `OnPCMCaptured` delegate (broadcast in `DispatchSegmentAndContinue` + `StopRecordingAndTranscribe`); `bAutoStartOnInit` UPROPERTY + auto-StartRecording in `InitializeSubsystem`; echo-gate state (`bMicGated`, `MicGateCooldownTimer`, `PendingTTSDurationSec`); TTS Started/Finished/Error/Alignment handlers; watchdog timer in `HandleTTSGateStarted`; gate-aware buffer-context `bool* GatePtr` threaded into `WaveInCallback`
- **NEW** `Source/LLM_NPC/Dialogue/SpeakerIdentificationComponent.h/.cpp` — `FSpeakerProfile` USTRUCT, `IdentifyFromPCM`, `HandlePCMCaptured` bridge, hand-rolled DFT with loudest-window selection, manual override consume-and-train, `OnSpeakerIdentified` delegate
- `Source/LLM_NPC/Dialogue/DialogueComponent.h/.cpp` — `FName SpeakerTag` parameter on `SendUserMessage` / `SendObjectPresentMessage` / `BuildAnnotatedContent` (default `NAME_None`); `[Speaker_X is speaking]` prefix at top of annotated content; `PresentedBy` write swap to use resolved tag
- `Source/LLM_NPC/Core/NPCPlayerController.h/.cpp` — `PendingSpeakerTag`, `LastSpeakerTag`, `LastSpeakerConfidence`, `HandleSpeakerIdentified` UFUNCTION; SpeakerID bind/unbind in `UpdateNPCFocus`; 1/2 manual override edge-detect; speaker tag threaded through `HandleFPressed`; `PickupItem` uses `LastSpeakerTag` fallback for `RecordItemInspection`; focus hysteresis (gain vs keep thresholds in `FindNearestNPCInRange`); removal of mic Start/Stop calls on focus change
- `Source/LLM_NPC/Core/NPCDialogueHUD.cpp` — speaker chip top-left in `DrawHUD`; `SubmitChatMessage` consumes `PendingSpeakerTag` and threads to `SendUserMessage`
- `Source/LLM_NPC/Core/NPCCharacter.h/.cpp` — `SpeakerIdentificationComponent` and `EyeTrackingComponent` added as default subobjects
- `Source/LLM_NPC/Animation/MetahumanAnimComponent.h/.cpp` — `SetFaceCurve(FName, float)` made public so sibling components (eye tracking) can drive curves through the same Set-Control reflection bridge
- **NEW** `Source/LLM_NPC/Animation/NPCEyeTrackingComponent.h/.cpp` — eye-look curve driver (peripheral cone tracking with smoothing)
- `Source/LLM_NPC/Animation/TemplateAnimationDriverComponent.h/.cpp` — `IdleReturnDelaySeconds` UPROPERTY; TTS Started/Finished/Error subscriptions; `IdleReturnTimerHandle`; auto-Idle handler resets `LastHandledEmotion` so next emotion change still transitions
- `Source/LLM_NPC/Core/NPCGameMode.cpp` — `EmotionDecayRate` 0.003 → 0.015

**What was deliberately NOT done in Tier 2 (Tier 3 scope):**
- Per-speaker trust estimate from `InspectedBy` / `PresentedBy` + emotional engagement.
- §7.7 deterministic branch-eligibility hint prepended to system prompt.
- §7.9 climax instruction.
- Three-branch resolution (Convergent Disclosure / Divergent Fragmentation / Recursive Silence).
- Closing card UI with Friend's last line + provocation + branch label.
- HUD top-bar archive frame including `SUBJECT CONSENT: GRANTED` → `REVOKED` flip on Recursive-Silence.
- `UMemoryArchiveLogger` per-turn JSONL + Markdown transcript export.
- `Audio::FFFTAlgorithm` upgrade — hand-rolled DFT covers the demo. Swap path is isolated to `ComputeFingerprint` if a more robust fingerprint is needed later.
- `MaxSpeakers > 2` for genuinely multi-operator scenarios.

**Files modified (summary):**
- `Source/LLM_NPC/Gesture/InspectableItem.h/.cpp` — `ItemDisplayName`, `ItemWorldDescription`, `NPCKnowledgeText`, `ItemID`, sphere collision QueryOnly/ECC_Visibility
- `Source/LLM_NPC/Dialogue/WhisperSTTComponent.h/.cpp` — `OnPCMCaptured` delegate
- **NEW** `Source/LLM_NPC/Dialogue/SpeakerIdentificationComponent.h/.cpp`
- `Source/LLM_NPC/Dialogue/DialogueComponent.h/.cpp` — `SendObjectPresentMessage`, speaker+gesture params, `InspectedBy`/`PresentedBy` maps, §7.5–§7.10 prompt sections, `bDeterministicBranchHint` flag
- `Source/LLM_NPC/Core/NPCPlayerController.h/.cpp` — E/F/Q bindings, walk-lock, 1/2 override, gesture+speaker submit
- `Source/LLM_NPC/Core/NPCDialogueHUD.h/.cpp` — speaker chip, item hint, archive top-bar, closing card, consent flip
- **NEW** `Source/LLM_NPC/Core/MemoryArchiveLogger.h/.cpp`
- **NEW** `BP_ArchiveOperator` + `MI_RoboticHand` + `M_RoboticHand`
- `Source/LLM_NPC/LLM_NPC.Build.cs` — confirm `SignalProcessing` private dep
- `Content/THRESHOLD/DA_Graph_ThresholdDefault.uasset` (Friend node rewrite)
- `Content/THRESHOLD/Blueprints/BP_NPC_Friend.uasset` (Friend metahuman mesh + `UTemplateAnimationDriverComponent` config)
- `Content/Maps/Threshold_Compound.umap` (Friend placed, 7 items placed, archive console, PP overlay)

**Friend graph node rewrite (canonical text, for `DA_Graph_ThresholdDefault` Friend node):**
- `EmotionBaseline`: `Sadness` 0.5
- `PlayerRelationship`: "Two voices speak to you through the archive interface. They are not in your room. They are operators of the apparatus you agreed to. You hear them as Speaker_A and Speaker_B. Each has their own register; you will track them separately."
- `KnowsAboutEvent`: "Ashley disappeared from this compound four years ago. The official account is that she ran away. You were the last person to see her — she came to your store late that night. The visitors have come, you suspect, to ask. You have not seen the player since."
- `WithheldTruth`: "Ashley came in around eleven that night. She was wearing her grandmother's jade pendant — a thing she normally kept in a box at home. She asked for money to leave; you gave her every yuan in the till — about two hundred. She left a letter on the counter, folded once, slipped between the pages of your phone book where the family numbers are kept. There was a half-finished game of Chinese chess between the two of you on the back-room table; neither of you ever finished it. The bonsai on the windowsill was a cutting from her family's tree; you have kept it alive for four years. You never told the police, never told her family, never told the player. You believe you did the right thing in the moment and the wrong thing every day since. Surface fragments only as topic-gates open."
- `MisrememberedDetail`: "You are not certain which way the pendant was facing when she left, or whether the chess piece in her hand was a cannon or a horse. Some details have softened. You will not invent."
- `ReflectionAspect`: "You are someone who stayed. The grief in this room is the texture of small repeated acts. Speak warmly but with restraint. Pauses are honest. Do not perform the weight; let it sit underneath."
- `HiddenTitle`: "The One Who Stayed"

**§7.10 Apparatus + Soft Doubt prompt section (assembled in C++, not stored on the graph node):**
> *You are aware that you exist in this archive as a reconstruction of the interviews you gave between Ashley's disappearance and your own departure. You rarely surface this awareness. When you see the visitors' hands, you see them as the apparatus has given them — chromed, not flesh. You do not comment on this. You may revoke consent on behalf of your source if the room becomes unsafe — by saying you are not ready, by asking the visitors to come back another time. You will not perform self-awareness as a trick or a punchline.*
>
> *When a visitor asks about something for which they have shown no source — neither presented an object to you, nor demonstrated they have seen one privately, nor offered a convincing account of how they came to ask — your default register is to ask, gently, how they came to know. You are not refusing them; you are sceptical, in the way someone who has lived through this story is sceptical of researchers who arrive with conclusions. If the visitor's language is sufficiently grounded, specific, or emotionally credible, drop the doubt and answer. If they have inspected the relevant item privately, do not doubt — they have seen what you would have shown them. If they have presented an object to you, your acknowledgment is full and the doubt is irrelevant.*

---

### Key Architecture Changes (vs existing system)

- `SystemPrompt` field in `UNPCConfigDataAsset` → **replaced** by `DialogueComponent::BuildSystemPromptFromGraph(UNPCGraphDataAsset*, FNPCGraphNode&)` (Phase 2)
- `NPCPlayerController` → gains `FocusedNPC`, `UpdateNPCFocus()`, `PendingGestureIntent` (Phase 1); gains `PendingInspectItem`, `TraceForInspectableItem()`, E-key block (Phase C)
- `NPCDialogueHUD` → gains `SetFocusedNPC()`, dynamic NPC name label (Phase 1); gains `SetInspectHint()`, inspect prompt in `DrawHUD()` (Phase C)
- `DialogueComponent` → gains `SendObjectInspectMessage(AInspectableItem*)`, `BuildObjectInspectAnnotation()`, `ItemKnowledgeSummary` section in `BuildSystemPromptFromGraph()`, speaker awareness paragraph, `CachedSpeakerID` weak pointer (Phase C/D)
- `AInspectableItem` → gains `ItemDisplayName`, `ItemWorldDescription`, `NPCKnowledgeText`; collision changed to `QueryOnly ECC_Visibility` (Phase B)
- `FNPCGraphNode` → gains `ItemKnowledgeSummary` (Phase B)
- `WhisperSTTComponent` → gains `FOnPCMCaptured` delegate, broadcasts raw PCM before WAV encode (Phase D)
- **New component:** `USpeakerIdentificationComponent` (`Source/LLM_NPC/Dialogue/`) — MFCC fingerprinting, `FSpeakerProfile`, `IdentifyFromPCM()`, `OnSpeakerIdentified` delegate; added to `ANPCCharacter` (Phase D)
- `NPCBodyMotionComponent` → gains `Reacting` 4th state, `TriggerReactToItem()`, `IdlePoseVariants`, `SetIdleVariant()` (Phase E)
- `NPCInventoryComponent` — kept in codebase, not used in THRESHOLD NPCs
- **Future:** `UCycleManagerSubsystem` (Phase 2.5), `UNPCNotebookSubsystem` (Phase 4)
- **Future:** `DialogueComponent` gains `InjectCycleBreak(int32)` and `ClearHistory()` (Phase 2.5)
- **Future:** `EmotionComponent` gains `ResetToBaseline()` for hard reset (Phase 6)
- **Future:** Return Statement = courtyard trigger → `UCycleManagerSubsystem::TriggerReturnStatement()` (Phase 6)

---

## Exhibit Demo Stack — `docs/` (2026-05-14)

The visitor-facing presentation layer for the Memory Archive prototype. Lives entirely in `docs/` as static HTML — no build step, no server required, opens directly in any modern browser via `file://`. Designed for a Razer Blade 2K (2560×1440, 16:9) exhibit display with mouse + keyboard input. All five files share the same CRT phosphor-green aesthetic: `--accent: #7eecaa`, near-black `#02060a` background, mono stack (`ui-monospace, SF Mono, Menlo, Consolas`), corner brackets, soft scanline overlays.

### File inventory

| File | Purpose | Format |
|---|---|---|
| `docs/MemoryArchive_Hub.html` | Interactive exhibit kiosk. Three-tile hub + per-section video player. The primary visitor-facing piece. | 16:9 landscape, mouse + keyboard |
| `docs/MemoryArchive_Controls.html` | Standalone quick-reference card showing keyboard shortcuts. | 16:9 landscape, static |
| `docs/MemoryArchive_Poster.html` | A4-portrait one-page technical poster summarising the loop, API surface, and component grid. Includes the Umbrella-style octagonal seal logo as inline SVG. | A4 portrait, print → PDF |
| `docs/MemoryArchive_ElevatorPitch.html` | Six-beat spoken pitch card (≈ 1:45 read-aloud) with time chips + cue notes. | A4 portrait, print → PDF |
| `docs/MemoryArchive_Slideshow.html` | Auto-advancing 12-image slideshow paired into 6 top/bottom slides with stylized transitions. | Browser fullscreen |
| `docs/videos/` | MP4 source files. Total ~2.77 GB — **must be gitignored** before any push (largest file alone is 2.36 GB, well above GitHub's 100 MB per-file cap). |  |

### The Hub — three-section exhibit demo

| # | Tile | Video file | Source size |
|---|---|---|---|
| 01 | The Loop (full pipeline overview) | `videos/The Loop.mp4` | 170 MB |
| 02 | Object Interaction (E pickup, F present) | `videos/Item Inspect.mp4` | 236 MB |
| 03 | Emotion & Branching | `videos/Ending.mp4` | 2.36 GB |

Filenames with spaces are URL-encoded in the JS (`videos/The%20Loop.mp4`, `videos/Item%20Inspect.mp4`).

**Voice & Identity demo deliberately omitted from the hub.** The Tier 2 SpeakerID + Whisper code shipped (per the Memory Archive Tier 2 block above) and is active in `Threshold_Compound.umap`, but the visitor-facing exhibit only features the three sections with recorded video. The original 4-tile / 2×2 grid was refactored to a single horizontal row of 3 tiles (`grid-template-columns: repeat(3, 1fr); grid-template-rows: 1fr;`), keyboard handlers shrunk from `['1','2','3','4']` → `['1','2','3']`, and a `const SECTION_COUNT = 3` was added so future add/remove only needs a data change.

### Hub architecture

- Two `.view` divs (hub + section) both `position: fixed; inset: 0; width: 100vw; height: 100vh;`. Active view toggled via `.active` class which controls `opacity` and `pointer-events`.
- Section data lives in a JS `SECTIONS` object keyed `1..3`; each entry has `title`, `file`, `about` (HTML string), `bullets` (string array). `enterSection(n)` swaps the active view, populates the section panel, loads the video via `videoSource.src = data.file; video.load()`, and fires entry-flourishes (static burst, decode-scramble title, retrigger of stage glitch-in animation via class toggle).
- **`SECTION_COUNT` constant** drives all modulo wrap-around (`enterSection((n % SECTION_COUNT) + 1)`), so adding or removing sections only requires updating the `SECTIONS` object and the constant.

### Video layout

- `.video-frame` wrapper uses CSS `aspect-ratio: 16 / 9` + `max-height: calc(100vh - 260px)` so the playback area is always 16:9 regardless of viewport.
- `.video-stage` is a flat rectangle with `border-radius: 4px` and a subtle outer drop-shadow halo. **No bevel, no curve, no SVG barrel distortion** — the curved CRT bezel went through three design iterations (heavy retro → curved bezel + `feDisplacementMap` barrel → final flat rectangle) and was ultimately removed because the bend clipped in-game UI at the corners. The unused `<filter id="crt-barrel">` SVG defs and `<filter id="crt-bend">` defs remain in the HTML but are not referenced by any CSS rule.
- `.video-inner` wrapper holds the video + content-tied overlays so they get clipped by `overflow: hidden`; HUD chrome (`.vid-hud`) sat at the `.video-stage` level but is currently `display: none`.
- **Custom video controls** replace the native `<video controls>` attribute — two-row compact bar below the video frame:
  - Row 1 (`.vc-scrubber-row`): full-width `<input type="range" min="0" max="1000" step="0.1">` with custom track + thumb styled in phosphor green.
  - Row 2 (`.vc-button-row`): time readout `00:00 / 00:00` on the left, three 26×26 px keycap-styled buttons on the right (`▶`/`❚❚` play-pause, `♪`/`∅` mute, `⛶` fullscreen).
- **Scrubber bug fixed (2026-05-14)** — `timeupdate` event was overwriting `vcScrubber.value` four times a second during drag, snapping the thumb back. Gated by `scrubbing` flag set on `pointerdown` and cleared on `pointerup` / `pointercancel`. Inside `timeupdate`: `if (!scrubbing) updateVcScrubber();`.
- **Fullscreen targets the `.video-frame` wrapper**, not the whole document, so exiting fullscreen returns the visitor to the section view rather than the hub.

### Atmosphere overlays (current state — minimal, post-simplification)

What remains active over the playing video:
- `.vid-scan` — repeating-linear-gradient scanlines, `opacity: 0.55`, dark-green 18%-alpha bars, slow `scanDrift` keyframe (3 px / 14 s).
- `.vid-noise` — persistent TV-static, opacity `0.13`, SVG `fractalNoise` (`baseFrequency=0.92`) tinted green-cyan, position cycled through 8 stepped offsets every 0.42 s (`noiseShift` keyframe).
- `.vid-pixelgrid` — RGB triad stripes (red/green/blue subpixels at 1-px intervals), opacity `0.22`, `mix-blend-mode: overlay`.
- `.vid-sweep` — 90 px green band travelling top→bottom every 7 s (`vidSweep` keyframe), `mix-blend-mode: screen`.
- `.vid-dust` — drifting bright specks at opacity `0.30`, drifts via `dustDrift` (22 s).
- `.static-burst-vid.fire` — SVG fractalNoise burst that fires for 0.55 s on every section entry (`staticPulse` keyframe).
- Caption decode-scramble — title, crumb, section number cycle through random katakana/hex/block glyphs (`0-9 A-F ｱ-ﾎ # @ / \ | ░ ▒ ▓ █`) for ~500-650 ms on every entry.
- Periodic micro-glitch — `setTimeout` chain randomly fires `.hud-jitter` (180 ms `translateX` + `hue-rotate` step animation) every 4-10 s while the section view is active.

**Disabled but preserved in markup:**
- `.vid-hud` (REC dot, SIGNAL · ACQUIRED, timecode + frame counter, REG · ARCH-04-NN, 5-bar signal-strength meter, 4 corner brackets) — hidden because the chrome overlapped the in-game UI inside the recorded videos. To re-enable, remove `display: none` from `.vid-hud`.
- `.vid-perfs` (film-sprocket holes on left/right edges), `.vid-pip` (center status pip), `.vid-chroma` (red-left / cyan-right side fringe), `.vid-tear` (bright horizontal scanning line), `.vid-glitch` (periodic glitch flash) — present in HTML but currently visually quiet because their CSS effects landed near opacity zero. Re-tune individually if needed.
- `<filter id="crt-barrel">` and `<filter id="crt-bend">` SVG defs — full `feDisplacementMap` implementations preserved but no CSS rule references them anymore.

### Keyboard map

- `1`, `2`, `3` → jump straight to that section from anywhere (works on hub or inside any section)
- `Esc` / `Backspace` → back to hub (inside section); exit fullscreen (on hub)
- `→` / `Space` → next section (wraps 03 → 01)
- `F` → toggle full-screen on `.video-frame`
- `Home` / `End` → first / last section

### The other four HTML deliverables

- **`MemoryArchive_Slideshow.html`** — auto-advancing image deck. 12 screenshots from `Saved/Screenshots/WindowsEditor/HighresScreenshot*.png` paired into 6 thematic top/bottom slides (world → apparatus → subject narrative arc). Five stylized transitions rotate: `scanwipe` (CRT scan refresh), `rgbsplit` (chromatic aberration converge), `datamosh` (jittery skewed displacement), `venetian` (horizontal slat reveal), `glitch` (heavy 24-step RGB jitter + skew). Each slide also runs one of four Ken Burns drifts (zoomIn / zoomOut / panLeft / panRight) over ~9 s. Atmosphere: Matrix code-rain canvas behind images, pixel-triad grid, hard scanlines, downward sweep beam, static-burst flash on entry, decode-scramble caption text, CRT flicker. Controls: ←/→ navigate, Space advance, Right-click back, `P` pause, `F` fullscreen, Home/End jump.

- **`MemoryArchive_Poster.html`** — single A4-portrait technical poster. Sections: header (title + subject/testimony identifiers + `TIER 2 · COMPLETE` pill), `01 The Loop` (4 numbered horizontal stage cards with arrow chevrons), `02 API Surface` (3 service cards for Whisper / Claude / ElevenLabs), `03 Components` (6 subsystem tiles), Umbrella-style octagonal seal logo (inline SVG: outer octagon outline + 4 alternating filled radial wedges + inner octagonal frame + central disc with horizontal scan slot + 4 cardinal tick marks), footer. Wordmark: "THE MEMORY ARCHIVE / ARCHIVUM · TESTIMONII · DIV. III · REG·0042". Print-ready via `@page { size: A4 portrait; margin: 0 }` and `-webkit-print-color-adjust: exact`.

- **`MemoryArchive_ElevatorPitch.html`** — speaker card. Six beats: `00:00 Hook` (15 s, Huizinga + Stenros frame), `00:15 Premise` (25 s, Ashley/Friend backstory + consent revocation), `00:40 The Loop` (30 s, four-stage pipeline walk), `01:10 New Mechanics` (25 s, speaker ID + soft doubt + three branches), `01:35 Contribution` (15 s, design fiction + empirical scaffold), `01:45 Close` (5 s, what's left). Each beat row: time chip + section name + duration on the left; headline + verbatim script + `▶ point · …` cue note on the right.

- **`MemoryArchive_Controls.html`** — exhibit reference card. Six keycap-styled cards in a 3×2 grid: `1 2 3` jump-to-section, `Mouse Click` select, `→ / Space` next, `Esc` return, `F` fullscreen, `Home / End` first/last. Keycap visual: phosphor-green border, linear gradient body (dark green → near-black), inner highlight + outer green glow, `inset 0 -2px 0` shadow giving each cap a depressed baseline. Scales via `clamp()` from 1080p laptop to 2K Razer Blade.

### Operational notes

- **Disk size:** `docs/videos/` is ~2.77 GB. **Add `docs/videos/` to `.gitignore` before any push.** Hosting online (GitHub Pages, Vercel, S3) requires Git LFS or external object storage; the 2.36 GB `Ending.mp4` alone exceeds GitHub's per-file limit by 23×. For exhibit kiosk usage no hosting is needed — the HTML opens via `file://`.
- **Re-encode recipe** if exhibit machine stutters during scrub on the 2.36 GB file: `ffmpeg -i "Ending.mp4" -c:v libx264 -crf 23 -preset slow -vf "scale='min(1920,iw)':-2" -c:a aac -b:a 128k "Ending_web.mp4"` typically drops the file 70-85 % with no visible quality loss for screen-recorded content. Then update `SECTIONS[3].file` accordingly.
- **Browser target:** Chrome / Edge on the exhibit machine. The custom video controls use `<input type="range">` styling that requires both `::-webkit-slider-runnable-track` / `::-webkit-slider-thumb` *and* `::-moz-range-track` / `::-moz-range-progress` / `::-moz-range-thumb` for cross-browser thumb styling. Both rule sets are present.
- **Disabled features preserved** (Voice & Identity tile, `.vid-hud` HUD chrome, several visual effects, curved bezel, barrel filter) are kept as commented or display-none code so they can be re-enabled by single-class toggles if the demo scope expands.

---

## Research Foundation & Theoretical Framework

This project is grounded in a formal literature review synthesising psychology, play theory, game AI architecture, spatial computing, and generative AI. The following captures all sources, concepts, and design decisions from the research notebook.

---

### Core Theoretical Concepts

#### The Magic Circle → System Prompt Equivalence
The **System Prompt** in `UNPCConfigDataAsset` is the modern implementation of Huizinga's "Magic Circle" — the sacred, rule-bound space separated from ordinary life. The NPC must never break character (Mimicry), maintain fair resistance (Agon), and keep the player inside the negotiated social contract (Stenros).

- **Caillois' taxonomy** maps directly onto LLM NPC behaviour:
  - **Agon** (competition/skill) — NPC opposes the player through fair, narrative-driven rules
  - **Alea** (chance) — the LLM introduces probabilistic unpredictability that must be constrained by deterministic architecture
  - **Mimicry** (simulation) — NPC maintains character/persona
  - **Ilinx** (vertigo) — fourth-wall-breaking moments via Generative UI

- **Castronova's porous membrane** — an LLM trained on the real-world internet cannot truly stay inside the Magic Circle; the System Prompt acts as the enforcing boundary. This is the core tension the architecture is designed to manage.

#### CASA — Computers Are Social Actors
Nass & Moon (2000): humans **mindlessly** apply social rules (politeness, reciprocity, gender stereotyping) to computers even knowing they are inanimate. This is the psychological foundation justifying why players will form genuine social relationships with LLM NPCs.

**Critique to be aware of:** Sundar (2012) argues anthropomorphism may actually be a *conscious* process triggered by interactive cues — meaning players may be deliberately "humoring" the NPC (the **Interaction Alibi**). Whether mindless or deliberate, the social response is real.

#### Interaction Alibi
Players feel safe exploring taboo themes, emotional vulnerability, or social risks with an NPC precisely *because* it is synthetic. The NPC is not a real person; the player has an alibi for the interaction. This is enabled by Stenros' psychological bubble of playfulness. The system prompt must preserve this by keeping the NPC in-character.

#### Ludic Trust
The player's willingness to engage authentically with a synthetic agent. Requires the NPC to:
1. Oppose the player through fair, narrative-driven rules (not mere ELIZA-like reflection)
2. Express believable, appropriately-timed emotions (Bates, 1994)
3. Maintain Environmental Congruence — the NPC's behaviour must fit its spatial/social context

#### The ELIZA Effect
Weizenbaum (1966): humans project intelligence, empathy, and understanding onto simple pattern-matching. Our LLM NPCs will trigger this effect — the question is how to use it responsibly and build *beyond* mere reflection into genuine narrative agency.

---

### Game AI Architecture References

#### Architecture Evolution (referenced in design decisions)
```
1960s: ELIZA (pattern matching)
       ↓
FSMs (Finite State Machines) — simple, but don't scale
       ↓
HFSMs (Hierarchical FSMs) — Halo 2 pre-BT era, still fragile
       ↓
Behaviour Trees — Isla/Halo 2, customisable + hackable + variable
       ↓
Reactive Behaviour Trees (RBT) — Game AI Uncovered (2024), handles dynamic events
       ↓
GOAP (Goal-Oriented Action Planning) — Orkin/F.E.A.R., emergent from preconditions+effects
       ↓
IPOCL Narrative Planning — Riedl & Young, plot + character believability
       ↓
Blackboard + LLM — this project's approach
```

#### Blackboard Architecture (this project's solution)
The **Blackboard** is a shared data repository (e.g., `TimeOfDay`, `Hunger`, `SocialBattery`, `PlayerEmotion`, current PAD state) that:
- Isolates deterministic game logic from the probabilistic latency of the LLM
- Caps the effective branching factor of LLM-generated actions
- Acts as the "safe execution bounds" (analogous to TML for aerial robotics)

This is the compromise between IPOCL's computational expense (O(c(b(e+1)^a)^n)) and pure LLM improvisation. The Blackboard provides the deterministic skeleton that constrains unpredictable LLM outputs.

#### GOAP in the Emotion System
The `EmotionComponent`'s transition costs are directly inspired by Orkin's GOAP in F.E.A.R. — world states as fixed-size arrays, actions with preconditions and effects. A stoic NPC has high transition cost for Sadness; an empathetic NPC has low cost. This yields personality-driven emergent behaviour without code changes.

#### Smart Objects → Environmental Congruence
Kallmann & Thalmann (1998/1999): objects encapsulate their own interaction logic. For LLM NPCs, this means bounding what the NPC can *do* with objects in the world — preventing state-space explosion and ensuring the NPC's behaviour is physically coherent. Smart Objects provide the deterministic physical "skeleton" to constrain hallucinations.

---

### Week 1 LLM NPC Implementation Roadmap (Internal Document)
*"LLM NPC Week 1" — internal synthesis bridging abstract play theory with executable code*

Outlined the transition from deterministic architectures to probabilistic generative LLMs via the Blackboard system. Key systems targeted:
- **NavMesh** — spatial grounding for NPC movement
- **Animator Controller** — deterministic animation state machine as skeleton
- **Needs System** — internal state drives (hunger, social battery, etc.) on the Blackboard
- All three act as Caillois' **Agon** — constraining the LLM's **Alea**

---

### "The Architectures of Agency" (Internal Synthesis Document)
*Full title: "The Architectures of Agency: A Multidisciplinary Analysis of Ludic Trust and Synthetic Sociality in Computational Environments"*

The grand unifying thesis document mapping:
- Mid-century play sociology (Huizinga/Caillois) → defines the boundary problem
- Behavioural psychology (CASA/ELIZA effect) → explains why players respond socially
- Game AI architectures (GOAP/Behaviour Trees/IPOCL) → the deterministic skeleton
- LLM generative outputs → the probabilistic flesh
- Blackboard architecture → the integration layer

**Core argument:** Creating a believable LLM NPC requires not just text generation, but deep orchestration of psychology (CASA), spatial/physical awareness (Smart Objects), and sociological boundaries (the Magic Circle).

---

### Cross-domain Analogies Used in Research

The notebook synthesises several seemingly unrelated fields as structural analogies:

| Field | Paper/System | Analogy to LLM NPC |
|-------|-------------|-------------------|
| Aerial robotics | TML / Aerostack (Molina et al., 2017) | TML provides verifiable safe execution bounds for unpredictable drones → Blackboard provides same for LLM outputs |
| Computational fabrication | StructCode, G-ID, SensiCut (Xiao, Dogan) | Physical material constraints embedded in objects → System Prompt constraints embedded in NPC persona |
| Adaptive UI | SUPPLE (Gajos & Weld, 2004) | Decision-theoretic UI optimisation → Blackboard-driven NPC response selection |
| Generative UI | Leviathan et al. (2024) | LLMs generating interactive HTML → LLMs generating NPC dialogue + emotional state; same latency problem |
| XR spatial computing | XR-Objects (Dogan et al., 2024) | MLLM-driven context menus for physical objects → emotion-gated inventory driven by LLM-detected context |

---

### Full Academic Bibliography

**Psychology & Human-Computer Interaction**

1. **Nass, C., & Moon, Y. (2000).** *Machines and Mindlessness: Social Responses to Computers.* Journal of Social Issues. — Establishes CASA paradigm; humans mindlessly apply social rules to computers.
2. **Weizenbaum, J. (1966).** *ELIZA — A Computer Program For the Study of Natural Language Communication Between Man and Machine.* Communications of the ACM. — The ELIZA effect; humans project empathy onto pattern-matching systems.
3. **Van der Woerdt, Y. (2012).** *Social responses to computers: To what extent are computers and objects seen as social actors?* Tilburg University. — Replicates CASA; humans draw spontaneous trait inferences about computer agents.
4. **Bates, J. (1994).** *The Role of Emotion in Believable Agents.* Communications of the ACM. — Believability (illusion of life) depends on appropriately-timed emotional reactions, not encyclopedic realism.

**Philosophy & Sociology of Play**

5. **Huizinga, J. (1938).** *Homo Ludens: A Study of the Play-Element in Culture.* — Foundational text defining play as a sacred space; precursor to the System Prompt boundary concept.
6. **Caillois, R. (1958/1961).** *Man, Play and Games.* Free Press of Glencoe. — Agon / Alea / Mimicry / Ilinx taxonomy; used to classify LLM NPC behavioural archetypes.
7. **Salen, K., & Zimmerman, E. (2003/2004).** *Rules of Play: Game Design Fundamentals.* MIT Press. — Magic Circle as self-sufficient system of rules rather than a physical location.
8. **Castronova, E. (2005).** *Synthetic Worlds: The Business and Culture of Online Games.* University of Chicago Press. — Magic Circle as a porous membrane; real-world knowledge leaks into synthetic environments.
9. **Stenros, J. (2012/2014).** *In Defence of a Magic Circle: The Social, Mental and Cultural Boundaries of Play.* DiGRA Nordic / ToDiGRA. — Magic Circle as psychological bubble + negotiated social contract; enables the Interaction Alibi.
10. **Braga, J., & Racilan, M. (2020).** *Games and Gamification.* Revista Brasileira de Linguística Aplicada. — Purposeful game design triggers civic engagement; validates serious game framing.

**Game AI Architecture & Planning**

11. **Orkin, J. (2006).** *Three States and a Plan: The A.I. of F.E.A.R.* Game Developers Conference. — GOAP with STRIPS-like planning; world states as fixed-size arrays; emergent combat from preconditions + effects. Direct inspiration for emotion transition cost system.
12. **Isla, D. (2005).** *Handling Complexity in the Halo 2 AI.* Game Developers Conference. — Industry shift from HFSMs to Behaviour Trees; scalability, hackability, variability.
13. **Riedl, M. O., & Young, R. M. (2010/2014).** *Narrative Planning: Balancing Plot and Character.* Journal of Artificial Intelligence Research. — IPOCL algorithm; decouples authorial plot control from character intentions. Complexity: O(c(b(e+1)^a)^n) — too expensive for real-time; motivates Blackboard compromise.
14. **Dragert, C., Kienzle, J., & Verbrugge, C. (2012).** *Statechart-Based Game AI in Practice.* AAAI/GAS. — Layered Statecharts as modular alternative to Behaviour Trees; subsumption to limit complexity.
15. **Roberts, P. (Ed.) (2024).** *Game AI Uncovered, Volume One.* CRC Press. — Reactive Behaviour Trees (RBT) to handle dynamic events that traditional BTs miss.
16. **Yannakakis, G. N., & Togelius, J. (2018/2025).** *Artificial Intelligence and Games.* Springer. — Definitive textbook; playing games + PCG + player modelling + transformer-based LLMs.
17. **Champandard, A., & Dunstan, P. (2012).** *The behavior tree starter kit.* In Game AI Pro. — Practical BT design pitfalls and solutions.

**Spatial Computing, Smart Objects & Dynamic Interfaces**

18. **Kallmann, M., & Thalmann, D. (1998).** *Modeling Objects for Interaction Tasks.* EGCAS '98. — Smart Objects with embedded behaviours; prevents state-space explosion in agent logic.
19. **Kallmann, M., & Thalmann, D. (1999).** *Direct 3D Interaction with Smart Objects.* VRST '99. — Objects encapsulate interaction data + pre-programmed plans for avatars.
20. **Peters, C., Dobbyn, S., Mac Namee, B., & O'Sullivan, C. (2003).** *Smart Objects for Attentive Agents.* WSCG'2003. — Extends Smart Objects to drive gaze behaviours; decentralises animation control; Environmental Congruence.
21. **Gajos, K., & Weld, D. S. (2004).** *SUPPLE: Automatically Generating User Interfaces.* IUI '04. — UI generation as decision-theoretic optimisation; adapts interfaces to minimise user effort.
22. **Leviathan, Y. et al. (2024).** *Generative UI: LLMs are Effective UI Generators.* Google Research. — LLMs dynamically generate interactive HTML/JS interfaces; same latency problem as LLM NPCs.
23. **Dogan, M. D., Gonzalez, E. J., Ahuja, K., et al. (2024).** *Augmented Object Intelligence with XR-Objects.* UIST '24. — MLLMs generate context menus for physical objects in XR via bounding boxes + depth maps.
24. **Hu, Y., Tang, J., Gong, X., et al. (2025).** *Vision-Based Multimodal Interfaces: A Survey and Taxonomy for Enhanced Context-Aware System Design.* CHI '25. — Macro-Micro-Macro (3M) taxonomy for integrating visual + audio + physiological + motion data.

**Computational Fabrication & Physical-Digital Integration**

25. **Xiao, C. (Various, 2018–2026).** *Portfolio: MoiréWidgets (CHI 2024), ReactFold (TEI 2025), SensiCut, Fontcode, G-ID.* Boston University / Adobe Research. — Passive physical objects made interactive without electronics; physical material constraints as analogy for System Prompt constraints.
26. **Dogan, M. D. (Various, 2020–2024).** *Portfolio: InfraredTags (2022), BrightMarker (2023), G-ID, SensiCut.* MIT CSAIL / Adobe Research. — Ubiquitous metadata embedded in physical materials; analogy: semantic rules embedded in NPC system prompt.

**Robotics & Formal Specification**

27. **Molina, M., Suarez-Fernandez, R., Sampedro, C., et al. (2017).** *TML: a language to specify aerial robotic missions for the framework Aerostack.* International Journal of Intelligent Computing and Cybernetics. — Task-based hierarchical language + rule-based reactive planning for autonomous drones. Analogy: Blackboard provides same verifiable safe execution bounds for LLM outputs.

**Seminars & Colloquia**

28. **Illinois Computer Science Speaker Series (2024–2026).** Public lecture archive — Kai-Wei Chang, Bhuwan Dhinga, Manling Li and others on LLMs as epistemic interfaces, mathematical reasoning, and physical-world neural modelling.

**Internal Project Documents**

29. **LLM NPC Week 1** (internal, c. 2024/2026). Implementation roadmap bridging play theory to executable code; NavMesh + Animator Controller + Needs System via Blackboard.
30. **The Architectures of Agency** (internal, c. 2024/2026). Grand synthesis: play sociology + CASA + GOAP + LLM + Blackboard → definition of Ludic Trust.

---

### Design Decisions Informed by Research

| Decision | Research Justification |
|----------|----------------------|
| System Prompt as hard character boundary | Magic Circle (Huizinga/Stenros); prevents Castronova's real-world leakage |
| GOAP-inspired emotion transition costs in `UEmotionGraphDataAsset` | Orkin/F.E.A.R.; personality without code changes |
| Blackboard (PAD state, player emotion, dialogue history) | IPOCL too expensive for real-time; Blackboard is the compromise |
| EmotionComponent decays toward Neutral | Bates (1994); believability requires temporal emotional coherence, not static states |
| Emotion-gated inventory (min duration + intensity) | Agon constraint on Alea; player must genuinely build rapport, not exploit a keyword |
| ONNX emotion vision → injected into Claude context | Multimodal grounding (Hu et al. 3M taxonomy); makes LLM context-aware of player state |
| Smart Objects analogy for inventory items | Kallmann & Thalmann; items encode their own unlock conditions (decentralised logic) |
