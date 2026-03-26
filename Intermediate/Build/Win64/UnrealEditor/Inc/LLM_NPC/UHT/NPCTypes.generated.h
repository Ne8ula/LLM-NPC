// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Core/NPCTypes.h"

#ifdef LLM_NPC_NPCTypes_generated_h
#error "NPCTypes.generated.h already included, missing '#pragma once' in NPCTypes.h"
#endif
#define LLM_NPC_NPCTypes_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FPADVector ********************************************************
struct Z_Construct_UScriptStruct_FPADVector_Statics;
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCTypes_h_49_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FPADVector_Statics; \
	static class UScriptStruct* StaticStruct();


struct FPADVector;
// ********** End ScriptStruct FPADVector **********************************************************

// ********** Begin ScriptStruct FEmotionState *****************************************************
struct Z_Construct_UScriptStruct_FEmotionState_Statics;
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCTypes_h_126_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FEmotionState_Statics; \
	static class UScriptStruct* StaticStruct();


struct FEmotionState;
// ********** End ScriptStruct FEmotionState *******************************************************

// ********** Begin ScriptStruct FNPCMessage *******************************************************
struct Z_Construct_UScriptStruct_FNPCMessage_Statics;
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCTypes_h_155_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FNPCMessage_Statics; \
	static class UScriptStruct* StaticStruct();


struct FNPCMessage;
// ********** End ScriptStruct FNPCMessage *********************************************************

// ********** Begin ScriptStruct FDetectedUserEmotion **********************************************
struct Z_Construct_UScriptStruct_FDetectedUserEmotion_Statics;
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCTypes_h_182_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FDetectedUserEmotion_Statics; \
	static class UScriptStruct* StaticStruct();


struct FDetectedUserEmotion;
// ********** End ScriptStruct FDetectedUserEmotion ************************************************

// ********** Begin ScriptStruct FGestureInput *****************************************************
struct Z_Construct_UScriptStruct_FGestureInput_Statics;
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCTypes_h_212_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FGestureInput_Statics; \
	static class UScriptStruct* StaticStruct();


struct FGestureInput;
// ********** End ScriptStruct FGestureInput *******************************************************

// ********** Begin ScriptStruct FEmotionSignal ****************************************************
struct Z_Construct_UScriptStruct_FEmotionSignal_Statics;
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCTypes_h_234_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FEmotionSignal_Statics; \
	static class UScriptStruct* StaticStruct();


struct FEmotionSignal;
// ********** End ScriptStruct FEmotionSignal ******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCTypes_h

// ********** Begin Enum EEmotionType **************************************************************
#define FOREACH_ENUM_EEMOTIONTYPE(op) \
	op(EEmotionType::Neutral) \
	op(EEmotionType::Joy) \
	op(EEmotionType::Sadness) \
	op(EEmotionType::Anger) \
	op(EEmotionType::Fear) \
	op(EEmotionType::Surprise) \
	op(EEmotionType::Disgust) \
	op(EEmotionType::Trust) \
	op(EEmotionType::Anticipation) 

enum class EEmotionType : uint8;
template<> struct TIsUEnumClass<EEmotionType> { enum { Value = true }; };
template<> LLM_NPC_NON_ATTRIBUTED_API UEnum* StaticEnum<EEmotionType>();
// ********** End Enum EEmotionType ****************************************************************

// ********** Begin Enum EDialogueInputMode ********************************************************
#define FOREACH_ENUM_EDIALOGUEINPUTMODE(op) \
	op(EDialogueInputMode::Voice) \
	op(EDialogueInputMode::Text) 

enum class EDialogueInputMode : uint8;
template<> struct TIsUEnumClass<EDialogueInputMode> { enum { Value = true }; };
template<> LLM_NPC_NON_ATTRIBUTED_API UEnum* StaticEnum<EDialogueInputMode>();
// ********** End Enum EDialogueInputMode **********************************************************

// ********** Begin Enum EManipulationInputMode ****************************************************
#define FOREACH_ENUM_EMANIPULATIONINPUTMODE(op) \
	op(EManipulationInputMode::Gesture) \
	op(EManipulationInputMode::KeyboardMouse) 

enum class EManipulationInputMode : uint8;
template<> struct TIsUEnumClass<EManipulationInputMode> { enum { Value = true }; };
template<> LLM_NPC_NON_ATTRIBUTED_API UEnum* StaticEnum<EManipulationInputMode>();
// ********** End Enum EManipulationInputMode ******************************************************

// ********** Begin Enum EGestureType **************************************************************
#define FOREACH_ENUM_EGESTURETYPE(op) \
	op(EGestureType::None) \
	op(EGestureType::Pinch) \
	op(EGestureType::Spread) \
	op(EGestureType::Rotate) \
	op(EGestureType::Spindle) 

enum class EGestureType : uint8;
template<> struct TIsUEnumClass<EGestureType> { enum { Value = true }; };
template<> LLM_NPC_NON_ATTRIBUTED_API UEnum* StaticEnum<EGestureType>();
// ********** End Enum EGestureType ****************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
