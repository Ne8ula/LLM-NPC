# LLM-NPC — Claude Code Brain

## Project Overview

**LLM-NPC** is an Unreal Engine 5.7 research prototype implementing a fully conversational, emotionally-aware Metahuman NPC with zero scripted dialogue. The NPC:
- Converses naturally via Claude LLM
- Understands player emotions through computer vision (webcam)
- Responds with expressive facial animation + synthesized voice (ElevenLabs TTS)
- Unlocks inventory items based on emotional state + dialogue keywords

**Key innovation:** All NPC dialogue is model-generated in real-time. Gameplay progression is gated by LLM reasoning about emotional state — not scripted branches.

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
│   │                            # NPCConfigDataAsset, NPCTypes, NPCGameMode, NPCPlayerController
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
- `NPCName`, `NPCDescription`, `SystemPrompt`
- `ClaudeModelID` (default: `claude-sonnet-4-6`), `MaxResponseTokens` (512)
- `ElevenLabsVoiceID`, voice stability (0.0–1.0), similarity boost (0.0–1.0)
- `DefaultEmotion`, `DefaultIntensity`, `EmotionDecayRate`, `NeutralThreshold`
- Per-emotion transition costs (enables personality without code changes)

**`UEmotionGraphDataAsset`** — State machine definition (nodes = emotions, edges = transition rules with costs)

**`UInventoryDataAsset`** — Item catalogue with unlock conditions per item

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
- `FEmotionSignal`: TargetEmotion, Strength, Source
- `FNPCMessage`: Role ("user"/"assistant"), Content, Timestamp, DetectedUserEmotion

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
5. Single NPC only — multi-NPC coordination and shared emotional memory TBD

---

## Working Branch

Current active branch: `claude/continue-llm-npc-api-lwC5j`
Main branch: `main`
