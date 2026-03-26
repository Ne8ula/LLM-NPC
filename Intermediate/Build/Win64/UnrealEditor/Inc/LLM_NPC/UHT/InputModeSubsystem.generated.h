// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Fallback/InputModeSubsystem.h"

#ifdef LLM_NPC_InputModeSubsystem_generated_h
#error "InputModeSubsystem.generated.h already included, missing '#pragma once' in InputModeSubsystem.h"
#endif
#define LLM_NPC_InputModeSubsystem_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class EDialogueInputMode : uint8;
enum class EManipulationInputMode : uint8;

// ********** Begin Delegate FOnDialogueInputModeChanged *******************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_InputModeSubsystem_h_8_DELEGATE \
LLM_NPC_API void FOnDialogueInputModeChanged_DelegateWrapper(const FMulticastScriptDelegate& OnDialogueInputModeChanged);


// ********** End Delegate FOnDialogueInputModeChanged *********************************************

// ********** Begin Delegate FOnManipulationInputModeChanged ***************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_InputModeSubsystem_h_9_DELEGATE \
LLM_NPC_API void FOnManipulationInputModeChanged_DelegateWrapper(const FMulticastScriptDelegate& OnManipulationInputModeChanged);


// ********** End Delegate FOnManipulationInputModeChanged *****************************************

// ********** Begin Class UInputModeSubsystem ******************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_InputModeSubsystem_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execSetManipulationInput); \
	DECLARE_FUNCTION(execGetActiveManipulationInput); \
	DECLARE_FUNCTION(execSetDialogueInput); \
	DECLARE_FUNCTION(execGetActiveDialogueInput);


struct Z_Construct_UClass_UInputModeSubsystem_Statics;
LLM_NPC_API UClass* Z_Construct_UClass_UInputModeSubsystem_NoRegister();

#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_InputModeSubsystem_h_21_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUInputModeSubsystem(); \
	friend struct ::Z_Construct_UClass_UInputModeSubsystem_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend LLM_NPC_API UClass* ::Z_Construct_UClass_UInputModeSubsystem_NoRegister(); \
public: \
	DECLARE_CLASS2(UInputModeSubsystem, UGameInstanceSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LLM_NPC"), Z_Construct_UClass_UInputModeSubsystem_NoRegister) \
	DECLARE_SERIALIZER(UInputModeSubsystem)


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_InputModeSubsystem_h_21_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UInputModeSubsystem(); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UInputModeSubsystem(UInputModeSubsystem&&) = delete; \
	UInputModeSubsystem(const UInputModeSubsystem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UInputModeSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UInputModeSubsystem); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UInputModeSubsystem) \
	NO_API virtual ~UInputModeSubsystem();


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_InputModeSubsystem_h_18_PROLOG
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_InputModeSubsystem_h_21_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_InputModeSubsystem_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_InputModeSubsystem_h_21_INCLASS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_InputModeSubsystem_h_21_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UInputModeSubsystem;

// ********** End Class UInputModeSubsystem ********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_InputModeSubsystem_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
