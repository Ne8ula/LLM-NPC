# LLM-NPC

Claude-powered interactive NPC system for Unreal Engine 5 with Metahuman facial animation, emotion-driven behavior, gesture recognition, and voice interaction.

## Overview

This project implements an interactive NPC prototype that:
- Converses naturally via **Claude API** with voice input (Whisper STT) and expressive voice output (ElevenLabs TTS)
- Uses a **GOAP-inspired Emotion Engine** based on Plutchik's Wheel + PAD continuous space
- Drives **Metahuman facial animations** from the NPC's emotional state via blend shape mapping
- Recognizes **user facial expressions** in real-time via camera (OpenCV + ONNX ML models)
- Supports **gesture-based 3D object manipulation** (pinch/spread/rotate) with research-backed enhancements (Go-Go technique, PRISM precision, spring-damper smoothing)
- Features a **hidden inventory system** where items unlock based on NPC emotional triggers
- Includes a **fallback system** for text input and keyboard/mouse when hardware is unavailable
- Designed for **scalability** — component-based architecture supports procedural NPC generation

## Architecture

```
                     ┌─────────────────────┐
                     │   NPC Controller     │
                     │  (ANPCAIController)  │
                     └──────────┬──────────┘
                                │
    ┌───────────┬───────────┬───┴───┬───────────┬───────────┐
    │           │           │       │           │           │
┌───▼───┐ ┌────▼───┐ ┌────▼──┐ ┌──▼────┐ ┌───▼────┐ ┌───▼─────┐
│Dialogue│ │Emotion │ │Vision │ │Gesture│ │Inven-  │ │Animation│
│ System │ │ Engine │ │(Face) │ │(Hand) │ │tory    │ │ Driver  │
└───┬───┘ └────┬───┘ └───┬──┘ └──┬────┘ └───┬────┘ └───┬─────┘
    │          │         │       │           │           │
Claude API  Plutchik   OpenCV  OpenCV    DataAssets  Metahuman
+ Whisper   + GOAP     +ONNX  +ONNX     + JSON      BlendShapes
+ ElevenLabs Graph
```

## Tech Stack

| Component | Technology |
|---|---|
| Engine | Unreal Engine 5.4 |
| Language | C++ |
| LLM | Claude API (Anthropic Messages API) |
| Speech-to-Text | whisper.cpp (local) |
| Text-to-Speech | ElevenLabs (cloud) |
| Emotion Model | Plutchik's Wheel + PAD continuous space |
| Vision | OpenCV 4.x + ONNX Runtime |
| Character | Metahuman with runtime blend shape control |

## Project Structure

```
Source/LLM_NPC/
├── Core/         NPCCharacter, NPCAIController, NPCSubsystemComponent, NPCConfigDataAsset, NPCTypes
├── Dialogue/     ClaudeAPISubsystem, DialogueComponent, WhisperSTTComponent, ElevenLabsTTSComponent, DialogueFallbackWidget
├── Emotion/      EmotionComponent, EmotionStateMachine, EmotionGoal, EmotionTransitionRule, EmotionGraphDataAsset
├── Vision/       CameraManagerSubsystem, FacialRecognitionComponent, FaceExpressionModel
├── Gesture/      GestureRecognitionComponent, HandLandmarkModel, GestureClassifier, ObjectInspectWidget, InspectableItem
├── Inventory/    NPCInventoryComponent, InventoryTypes, InventoryDataAsset
├── Animation/    MetahumanAnimComponent, BlendShapeMappingDataAsset, NPCLipSyncComponent
└── Fallback/     FallbackManagerComponent, InputModeSubsystem
```

## Prerequisites

- Unreal Engine 5.4+
- Visual Studio 2022 or Rider
- [whisper.cpp](https://github.com/ggerganov/whisper.cpp) compiled as static library
- [OpenCV 4.x](https://opencv.org/) shared libraries
- [ONNX Runtime](https://onnxruntime.ai/) shared libraries
- Anthropic API key (for Claude)
- ElevenLabs API key (for TTS)

## Setup

1. Clone this repository
2. Place third-party libraries in `ThirdParty/` (whisper.cpp, OpenCV, ONNXRuntime) with `include/` and `lib/` subdirectories
3. Download ML models to `Content/Models/`:
   - `ggml-base.en.bin` (Whisper, ~150MB)
   - `fer_expression.onnx` (facial expression, ~10MB)
   - `hand_landmark.onnx` (hand tracking, ~5MB)
4. Set environment variables: `ANTHROPIC_API_KEY`, `ELEVENLABS_API_KEY`
5. Open `LLM_NPC.uproject` in Unreal Engine
6. Build and run

## Research Foundation

This project is informed by research from two NotebookLM knowledge bases:

**LLM NPC Research**: F.E.A.R. GOAP architecture, ELIZA Effect for immersion design, Magic Circle theory for world boundaries, decoupled goals/actions for NPC scalability.

**3D Interaction**: Go-Go technique for non-linear gesture scaling, PRISM precision for fine manipulation, spring-damper smoothing for haptic-less tracking, Spindle technique for bimanual interaction, 3D Bubble Cursor for object selection.
