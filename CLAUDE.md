# LLM-NPC — Claude Code Brain

## Project Overview

**LLM-NPC** is an Unreal Engine 5.7 research prototype implementing a fully conversational, emotionally-aware Metahuman NPC with zero scripted dialogue. The NPC:
- Converses naturally via Claude LLM
- Understands player emotions through computer vision (webcam)
- Responds with expressive facial animation + synthesized voice (ElevenLabs TTS)
- Unlocks inventory items based on emotional state + dialogue keywords

**Key innovation:** All NPC dialogue is model-generated in real-time. Gameplay progression is gated by LLM reasoning about emotional state — not scripted branches.

**Active vertical slice:** THRESHOLD — a non-linear, replayable interactive experience with 5 AI NPCs in a Chinese residential compound. Core mechanic: TESTIMONIAL (player verbally relays what one NPC said to another via live Whisper STT; each Claude instance responds to the player's imperfect recollection in real-time). Social graph between NPCs is procedurally generated per run.

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
- `FNPCGraphNode`: NPCID, NPCName, Role, EmotionBaseline, KnowsAboutEvent, WithheldTruth, MisrememberedDetail, PlayerRelationship, ElevenLabsVoiceID, VoiceGender, MetahumanVariantPool, ReflectionAspect (hidden tonal instruction), HiddenTitle ("The One Who..." — post-run reveal only)
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

---

## Active Test Assets

- **Map:** `Content/Maps/MainMap.umap` — single playable scene
- **NPC Blueprint:** `Content/BP_NPC_Test.uasset`
- **Config:** `Content/DA_NPC_Test.uasset` — personality, voice ID, emotion defaults
- **Blend shape map:** `Content/DA_BlendShapeMap_Default.uasset`
- **ONNX models:** `Content/Models/fer_expression.onnx`, `hand_landmark.onnx`

---

## Known Open Issues / Future Work

1. LLM API latency (~1–2s/turn) breaks real-time immersion at scale
2. ONNX model accuracy degrades under variable lighting / partial occlusion
3. PAD emotional state is not persisted between sessions (no database layer)
4. Voice cloning ethics + ElevenLabs licensing for shipped games
5. Single NPC only — multi-NPC refactor (Phase 1) in progress: proximity-based `FocusedNPC` in `NPCPlayerController`, dynamic HUD binding

---

## Working Branch

Current active branch: `claude/continue-llm-npc-api-lwC5j`
Main branch: `main`

---

## THRESHOLD — Vertical Slice Design

### Concept
Non-linear, replayable interactive experience. Player returns to a Chinese residential compound they left years ago. 5 AI NPCs knew them. No plot, no objectives, no tutorial — the experience ends when the player chooses to speak into the empty courtyard (Return Statement).

**Core mechanic — TESTIMONIAL:** Player is the only node connecting 5 AI minds. They carry what one NPC says to another — live via Whisper STT, in their own words, imperfectly. Each receiving Claude instance responds to the player's specific phrasing unpredictably. Impossible without live voice + LLM inference.

**Gesture layer:** Pinch/Spread/Rotate/Spindle (already implemented in `GestureRecognitionComponent`) map to `EGestureIntent` (Withhold/Disclose/Doubt/Synthesise). Injected into Claude context before voice message — modifies HOW testimony is received, not what is said.

**Facial recognition:** Ambient only (non-gating). Player emotion injected into Claude context; NPC may comment on it. No progression lock.

**AI Notepad:** Player carries a 2015-prototype-aesthetic device (`UNPCNotebookSubsystem` — Phase 4). Separate Claude instance, "thinking partner" prompt. Outputs text + JSON graph update `{nodes, edges, certainty}`. Rendered as `WBP_SocialGraph` — unreliable, probabilistic, can hallucinate connections.

**Return Statement:** Player speaks into empty courtyard → summary Claude call with compound-as-witness system prompt → ElevenLabs reverberant neutral voice → Phase 1 Ground Truth reveal → Phase 2 hidden titles reveal.

**Replayability:** Graph Studio scene generates fresh `UNPCGraphDataAsset` per run via Claude API call. Different graph = different people = different truth.

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

### Implementation Phases

| Phase | Status | Scope |
|-------|--------|-------|
| 0 — Type Foundation | **Complete** | `EGestureIntent`, `UNPCGraphDataAsset`, soft-deprecated `SystemPrompt` |
| 1 — Multi-NPC Refactor | **Next** | `NPCPlayerController` proximity focus, `NPCDialogueHUD` dynamic binding |
| 2 — Graph-Driven Prompts | Pending | `BuildSystemPromptFromGraph()`, handcrafted `DA_Graph_ThresholdDefault` |
| 3 — Gesture Layer | Pending | `EGestureIntent` caching + injection in `DialogueComponent` |
| 4 — Notebook Subsystem | Pending | `UNPCNotebookSubsystem`, `WBP_Notebook`, `WBP_SocialGraph` |
| 5 — Graph Studio + Procedural | Pending | Generation scene, Claude JSON → `UNPCGraphDataAsset` |
| 6 — Return Statement | Pending | `UReturnStatementSubsystem`, courtyard trigger, two-phase reveal |
| 7 — Environment + Polish | Pending | `Threshold_Compound.umap`, lighting, ambient audio |

### Key Architecture Changes (vs existing system)

- `SystemPrompt` field in `UNPCConfigDataAsset` → **replaced** by `DialogueComponent::BuildSystemPromptFromGraph(UNPCGraphDataAsset*, FNPCGraphNode&)` (Phase 2)
- `NPCPlayerController` → gains `FocusedNPC`, `UpdateNPCFocus()`, `PendingGestureIntent` (Phase 1)
- `NPCDialogueHUD` → gains `SetFocusedNPC()`, dynamic NPC name label (Phase 1)
- `DialogueComponent::SendUserMessage()` → gains `EGestureIntent` parameter, `BuildAnnotatedContent()` helper (Phase 3)
- `NPCInventoryComponent` — kept in codebase, not used in THRESHOLD NPCs
- New subsystems: `UNPCNotebookSubsystem` (Phase 4), `UReturnStatementSubsystem` (Phase 6)

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
