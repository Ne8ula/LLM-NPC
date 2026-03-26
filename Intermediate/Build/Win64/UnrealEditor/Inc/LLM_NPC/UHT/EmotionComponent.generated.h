// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Emotion/EmotionComponent.h"

#ifdef LLM_NPC_EmotionComponent_generated_h
#error "EmotionComponent.generated.h already included, missing '#pragma once' in EmotionComponent.h"
#endif
#define LLM_NPC_EmotionComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FEmotionSignal;
struct FEmotionState;

// ********** Begin Delegate FOnEmotionChanged *****************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionComponent_h_13_DELEGATE \
LLM_NPC_API void FOnEmotionChanged_DelegateWrapper(const FMulticastScriptDelegate& OnEmotionChanged, FEmotionState OldState, FEmotionState NewState);


// ********** End Delegate FOnEmotionChanged *******************************************************

// ********** Begin Class UEmotionComponent ********************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionComponent_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execHandleEmotionStateChanged); \
	DECLARE_FUNCTION(execGetCurrentEmotionState); \
	DECLARE_FUNCTION(execProcessSignal);


struct Z_Construct_UClass_UEmotionComponent_Statics;
LLM_NPC_API UClass* Z_Construct_UClass_UEmotionComponent_NoRegister();

#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionComponent_h_28_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUEmotionComponent(); \
	friend struct ::Z_Construct_UClass_UEmotionComponent_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend LLM_NPC_API UClass* ::Z_Construct_UClass_UEmotionComponent_NoRegister(); \
public: \
	DECLARE_CLASS2(UEmotionComponent, UNPCSubsystemComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LLM_NPC"), Z_Construct_UClass_UEmotionComponent_NoRegister) \
	DECLARE_SERIALIZER(UEmotionComponent)


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionComponent_h_28_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UEmotionComponent(UEmotionComponent&&) = delete; \
	UEmotionComponent(const UEmotionComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UEmotionComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UEmotionComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UEmotionComponent) \
	NO_API virtual ~UEmotionComponent();


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionComponent_h_25_PROLOG
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionComponent_h_28_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionComponent_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionComponent_h_28_INCLASS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionComponent_h_28_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UEmotionComponent;

// ********** End Class UEmotionComponent **********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionComponent_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
