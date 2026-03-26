// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Emotion/EmotionGoal.h"

#ifdef LLM_NPC_EmotionGoal_generated_h
#error "EmotionGoal.generated.h already included, missing '#pragma once' in EmotionGoal.h"
#endif
#define LLM_NPC_EmotionGoal_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class EEmotionType : uint8;
struct FEmotionState;

// ********** Begin Class UEmotionGoal *************************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGoal_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetCostToReach); \
	DECLARE_FUNCTION(execIsSatisfied);


struct Z_Construct_UClass_UEmotionGoal_Statics;
LLM_NPC_API UClass* Z_Construct_UClass_UEmotionGoal_NoRegister();

#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGoal_h_21_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUEmotionGoal(); \
	friend struct ::Z_Construct_UClass_UEmotionGoal_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend LLM_NPC_API UClass* ::Z_Construct_UClass_UEmotionGoal_NoRegister(); \
public: \
	DECLARE_CLASS2(UEmotionGoal, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LLM_NPC"), Z_Construct_UClass_UEmotionGoal_NoRegister) \
	DECLARE_SERIALIZER(UEmotionGoal)


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGoal_h_21_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UEmotionGoal(UEmotionGoal&&) = delete; \
	UEmotionGoal(const UEmotionGoal&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UEmotionGoal); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UEmotionGoal); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UEmotionGoal) \
	NO_API virtual ~UEmotionGoal();


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGoal_h_18_PROLOG
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGoal_h_21_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGoal_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGoal_h_21_INCLASS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGoal_h_21_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UEmotionGoal;

// ********** End Class UEmotionGoal ***************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGoal_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
