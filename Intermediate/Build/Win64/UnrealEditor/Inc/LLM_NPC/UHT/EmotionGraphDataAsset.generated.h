// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Emotion/EmotionGraphDataAsset.h"

#ifdef LLM_NPC_EmotionGraphDataAsset_generated_h
#error "EmotionGraphDataAsset.generated.h already included, missing '#pragma once' in EmotionGraphDataAsset.h"
#endif
#define LLM_NPC_EmotionGraphDataAsset_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UEmotionStateMachine;
class UObject;

// ********** Begin ScriptStruct FEmotionNodeConfig ************************************************
struct Z_Construct_UScriptStruct_FEmotionNodeConfig_Statics;
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGraphDataAsset_h_17_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FEmotionNodeConfig_Statics; \
	static class UScriptStruct* StaticStruct();


struct FEmotionNodeConfig;
// ********** End ScriptStruct FEmotionNodeConfig **************************************************

// ********** Begin ScriptStruct FEmotionEdgeConfig ************************************************
struct Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics;
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGraphDataAsset_h_43_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics; \
	static class UScriptStruct* StaticStruct();


struct FEmotionEdgeConfig;
// ********** End ScriptStruct FEmotionEdgeConfig **************************************************

// ********** Begin Class UEmotionGraphDataAsset ***************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGraphDataAsset_h_81_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execCreateStateMachine);


struct Z_Construct_UClass_UEmotionGraphDataAsset_Statics;
LLM_NPC_API UClass* Z_Construct_UClass_UEmotionGraphDataAsset_NoRegister();

#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGraphDataAsset_h_81_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUEmotionGraphDataAsset(); \
	friend struct ::Z_Construct_UClass_UEmotionGraphDataAsset_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend LLM_NPC_API UClass* ::Z_Construct_UClass_UEmotionGraphDataAsset_NoRegister(); \
public: \
	DECLARE_CLASS2(UEmotionGraphDataAsset, UDataAsset, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LLM_NPC"), Z_Construct_UClass_UEmotionGraphDataAsset_NoRegister) \
	DECLARE_SERIALIZER(UEmotionGraphDataAsset)


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGraphDataAsset_h_81_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UEmotionGraphDataAsset(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UEmotionGraphDataAsset(UEmotionGraphDataAsset&&) = delete; \
	UEmotionGraphDataAsset(const UEmotionGraphDataAsset&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UEmotionGraphDataAsset); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UEmotionGraphDataAsset); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UEmotionGraphDataAsset) \
	NO_API virtual ~UEmotionGraphDataAsset();


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGraphDataAsset_h_78_PROLOG
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGraphDataAsset_h_81_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGraphDataAsset_h_81_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGraphDataAsset_h_81_INCLASS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGraphDataAsset_h_81_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UEmotionGraphDataAsset;

// ********** End Class UEmotionGraphDataAsset *****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGraphDataAsset_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
