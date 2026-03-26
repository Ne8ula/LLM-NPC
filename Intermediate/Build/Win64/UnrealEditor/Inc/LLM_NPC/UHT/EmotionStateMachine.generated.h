// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Emotion/EmotionStateMachine.h"

#ifdef LLM_NPC_EmotionStateMachine_generated_h
#error "EmotionStateMachine.generated.h already included, missing '#pragma once' in EmotionStateMachine.h"
#endif
#define LLM_NPC_EmotionStateMachine_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class EEmotionType : uint8;
struct FEmotionSignal;
struct FEmotionState;

// ********** Begin Delegate FOnEmotionStateChanged ************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionStateMachine_h_11_DELEGATE \
LLM_NPC_API void FOnEmotionStateChanged_DelegateWrapper(const FMulticastScriptDelegate& OnEmotionStateChanged, FEmotionState OldState, FEmotionState NewState);


// ********** End Delegate FOnEmotionStateChanged **************************************************

// ********** Begin Class UEmotionStateMachine *****************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionStateMachine_h_29_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetCurrentState); \
	DECLARE_FUNCTION(execFindBestTransition); \
	DECLARE_FUNCTION(execTick); \
	DECLARE_FUNCTION(execProcessSignal);


struct Z_Construct_UClass_UEmotionStateMachine_Statics;
LLM_NPC_API UClass* Z_Construct_UClass_UEmotionStateMachine_NoRegister();

#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionStateMachine_h_29_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUEmotionStateMachine(); \
	friend struct ::Z_Construct_UClass_UEmotionStateMachine_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend LLM_NPC_API UClass* ::Z_Construct_UClass_UEmotionStateMachine_NoRegister(); \
public: \
	DECLARE_CLASS2(UEmotionStateMachine, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LLM_NPC"), Z_Construct_UClass_UEmotionStateMachine_NoRegister) \
	DECLARE_SERIALIZER(UEmotionStateMachine)


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionStateMachine_h_29_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UEmotionStateMachine(UEmotionStateMachine&&) = delete; \
	UEmotionStateMachine(const UEmotionStateMachine&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UEmotionStateMachine); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UEmotionStateMachine); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UEmotionStateMachine) \
	NO_API virtual ~UEmotionStateMachine();


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionStateMachine_h_26_PROLOG
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionStateMachine_h_29_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionStateMachine_h_29_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionStateMachine_h_29_INCLASS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionStateMachine_h_29_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UEmotionStateMachine;

// ********** End Class UEmotionStateMachine *******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionStateMachine_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
