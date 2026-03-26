// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Vision/FaceExpressionModel.h"

#ifdef LLM_NPC_FaceExpressionModel_generated_h
#error "FaceExpressionModel.generated.h already included, missing '#pragma once' in FaceExpressionModel.h"
#endif
#define LLM_NPC_FaceExpressionModel_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FDetectedUserEmotion;

// ********** Begin Class UFaceExpressionModel *****************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_FaceExpressionModel_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execIsModelLoaded); \
	DECLARE_FUNCTION(execClassify); \
	DECLARE_FUNCTION(execLoadModel);


struct Z_Construct_UClass_UFaceExpressionModel_Statics;
LLM_NPC_API UClass* Z_Construct_UClass_UFaceExpressionModel_NoRegister();

#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_FaceExpressionModel_h_18_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUFaceExpressionModel(); \
	friend struct ::Z_Construct_UClass_UFaceExpressionModel_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend LLM_NPC_API UClass* ::Z_Construct_UClass_UFaceExpressionModel_NoRegister(); \
public: \
	DECLARE_CLASS2(UFaceExpressionModel, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LLM_NPC"), Z_Construct_UClass_UFaceExpressionModel_NoRegister) \
	DECLARE_SERIALIZER(UFaceExpressionModel)


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_FaceExpressionModel_h_18_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UFaceExpressionModel(UFaceExpressionModel&&) = delete; \
	UFaceExpressionModel(const UFaceExpressionModel&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UFaceExpressionModel); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UFaceExpressionModel); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UFaceExpressionModel) \
	NO_API virtual ~UFaceExpressionModel();


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_FaceExpressionModel_h_15_PROLOG
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_FaceExpressionModel_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_FaceExpressionModel_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_FaceExpressionModel_h_18_INCLASS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_FaceExpressionModel_h_18_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UFaceExpressionModel;

// ********** End Class UFaceExpressionModel *******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_FaceExpressionModel_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
