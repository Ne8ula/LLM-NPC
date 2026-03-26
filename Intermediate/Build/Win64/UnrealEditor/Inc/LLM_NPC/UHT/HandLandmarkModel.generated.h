// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Gesture/HandLandmarkModel.h"

#ifdef LLM_NPC_HandLandmarkModel_generated_h
#error "HandLandmarkModel.generated.h already included, missing '#pragma once' in HandLandmarkModel.h"
#endif
#define LLM_NPC_HandLandmarkModel_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UHandLandmarkModel *******************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_HandLandmarkModel_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execIsModelLoaded); \
	DECLARE_FUNCTION(execDetectHandLandmarks); \
	DECLARE_FUNCTION(execLoadModel);


struct Z_Construct_UClass_UHandLandmarkModel_Statics;
LLM_NPC_API UClass* Z_Construct_UClass_UHandLandmarkModel_NoRegister();

#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_HandLandmarkModel_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUHandLandmarkModel(); \
	friend struct ::Z_Construct_UClass_UHandLandmarkModel_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend LLM_NPC_API UClass* ::Z_Construct_UClass_UHandLandmarkModel_NoRegister(); \
public: \
	DECLARE_CLASS2(UHandLandmarkModel, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LLM_NPC"), Z_Construct_UClass_UHandLandmarkModel_NoRegister) \
	DECLARE_SERIALIZER(UHandLandmarkModel)


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_HandLandmarkModel_h_14_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UHandLandmarkModel(UHandLandmarkModel&&) = delete; \
	UHandLandmarkModel(const UHandLandmarkModel&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UHandLandmarkModel); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UHandLandmarkModel); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UHandLandmarkModel)


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_HandLandmarkModel_h_11_PROLOG
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_HandLandmarkModel_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_HandLandmarkModel_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_HandLandmarkModel_h_14_INCLASS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_HandLandmarkModel_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UHandLandmarkModel;

// ********** End Class UHandLandmarkModel *********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_HandLandmarkModel_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
