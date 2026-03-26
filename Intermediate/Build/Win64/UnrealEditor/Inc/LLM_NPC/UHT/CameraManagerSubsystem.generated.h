// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Vision/CameraManagerSubsystem.h"

#ifdef LLM_NPC_CameraManagerSubsystem_generated_h
#error "CameraManagerSubsystem.generated.h already included, missing '#pragma once' in CameraManagerSubsystem.h"
#endif
#define LLM_NPC_CameraManagerSubsystem_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UCameraManagerSubsystem **************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_CameraManagerSubsystem_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execIsCameraAvailable); \
	DECLARE_FUNCTION(execGetLatestFrame); \
	DECLARE_FUNCTION(execStopCapture); \
	DECLARE_FUNCTION(execStartCapture);


struct Z_Construct_UClass_UCameraManagerSubsystem_Statics;
LLM_NPC_API UClass* Z_Construct_UClass_UCameraManagerSubsystem_NoRegister();

#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_CameraManagerSubsystem_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUCameraManagerSubsystem(); \
	friend struct ::Z_Construct_UClass_UCameraManagerSubsystem_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend LLM_NPC_API UClass* ::Z_Construct_UClass_UCameraManagerSubsystem_NoRegister(); \
public: \
	DECLARE_CLASS2(UCameraManagerSubsystem, UGameInstanceSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LLM_NPC"), Z_Construct_UClass_UCameraManagerSubsystem_NoRegister) \
	DECLARE_SERIALIZER(UCameraManagerSubsystem)


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_CameraManagerSubsystem_h_19_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UCameraManagerSubsystem(UCameraManagerSubsystem&&) = delete; \
	UCameraManagerSubsystem(const UCameraManagerSubsystem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCameraManagerSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCameraManagerSubsystem); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UCameraManagerSubsystem) \
	NO_API virtual ~UCameraManagerSubsystem();


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_CameraManagerSubsystem_h_16_PROLOG
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_CameraManagerSubsystem_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_CameraManagerSubsystem_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_CameraManagerSubsystem_h_19_INCLASS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_CameraManagerSubsystem_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UCameraManagerSubsystem;

// ********** End Class UCameraManagerSubsystem ****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_CameraManagerSubsystem_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
