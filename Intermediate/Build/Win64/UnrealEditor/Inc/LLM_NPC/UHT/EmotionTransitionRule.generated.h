// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Emotion/EmotionTransitionRule.h"

#ifdef LLM_NPC_EmotionTransitionRule_generated_h
#error "EmotionTransitionRule.generated.h already included, missing '#pragma once' in EmotionTransitionRule.h"
#endif
#define LLM_NPC_EmotionTransitionRule_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FEmotionSignal;

// ********** Begin Class UEmotionTransitionRule ***************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionTransitionRule_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetTransitionCost); \
	DECLARE_FUNCTION(execEvaluateRule);


struct Z_Construct_UClass_UEmotionTransitionRule_Statics;
LLM_NPC_API UClass* Z_Construct_UClass_UEmotionTransitionRule_NoRegister();

#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionTransitionRule_h_20_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUEmotionTransitionRule(); \
	friend struct ::Z_Construct_UClass_UEmotionTransitionRule_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend LLM_NPC_API UClass* ::Z_Construct_UClass_UEmotionTransitionRule_NoRegister(); \
public: \
	DECLARE_CLASS2(UEmotionTransitionRule, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LLM_NPC"), Z_Construct_UClass_UEmotionTransitionRule_NoRegister) \
	DECLARE_SERIALIZER(UEmotionTransitionRule)


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionTransitionRule_h_20_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UEmotionTransitionRule(UEmotionTransitionRule&&) = delete; \
	UEmotionTransitionRule(const UEmotionTransitionRule&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UEmotionTransitionRule); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UEmotionTransitionRule); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UEmotionTransitionRule) \
	NO_API virtual ~UEmotionTransitionRule();


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionTransitionRule_h_17_PROLOG
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionTransitionRule_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionTransitionRule_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionTransitionRule_h_20_INCLASS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionTransitionRule_h_20_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UEmotionTransitionRule;

// ********** End Class UEmotionTransitionRule *****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionTransitionRule_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
