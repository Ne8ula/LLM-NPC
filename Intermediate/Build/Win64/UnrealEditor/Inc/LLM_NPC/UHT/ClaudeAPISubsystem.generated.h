// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Dialogue/ClaudeAPISubsystem.h"

#ifdef LLM_NPC_ClaudeAPISubsystem_generated_h
#error "ClaudeAPISubsystem.generated.h already included, missing '#pragma once' in ClaudeAPISubsystem.h"
#endif
#define LLM_NPC_ClaudeAPISubsystem_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FClaudeAPIResponse;
struct FNPCMessage;

// ********** Begin ScriptStruct FClaudeAPIResponse ************************************************
struct Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics;
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ClaudeAPISubsystem_h_19_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics; \
	static class UScriptStruct* StaticStruct();


struct FClaudeAPIResponse;
// ********** End ScriptStruct FClaudeAPIResponse **************************************************

// ********** Begin Delegate FOnClaudeResponseReceived *********************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ClaudeAPISubsystem_h_47_DELEGATE \
LLM_NPC_API void FOnClaudeResponseReceived_DelegateWrapper(const FMulticastScriptDelegate& OnClaudeResponseReceived, FClaudeAPIResponse const& Response);


// ********** End Delegate FOnClaudeResponseReceived ***********************************************

// ********** Begin Delegate FOnClaudeRequestComplete **********************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ClaudeAPISubsystem_h_50_DELEGATE \
LLM_NPC_API void FOnClaudeRequestComplete_DelegateWrapper(const FScriptDelegate& OnClaudeRequestComplete, FClaudeAPIResponse const& Response);


// ********** End Delegate FOnClaudeRequestComplete ************************************************

// ********** Begin Class UClaudeAPISubsystem ******************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ClaudeAPISubsystem_h_61_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execSetAPIKey); \
	DECLARE_FUNCTION(execIsAPIKeyConfigured); \
	DECLARE_FUNCTION(execSendMessage);


struct Z_Construct_UClass_UClaudeAPISubsystem_Statics;
LLM_NPC_API UClass* Z_Construct_UClass_UClaudeAPISubsystem_NoRegister();

#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ClaudeAPISubsystem_h_61_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUClaudeAPISubsystem(); \
	friend struct ::Z_Construct_UClass_UClaudeAPISubsystem_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend LLM_NPC_API UClass* ::Z_Construct_UClass_UClaudeAPISubsystem_NoRegister(); \
public: \
	DECLARE_CLASS2(UClaudeAPISubsystem, UGameInstanceSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LLM_NPC"), Z_Construct_UClass_UClaudeAPISubsystem_NoRegister) \
	DECLARE_SERIALIZER(UClaudeAPISubsystem)


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ClaudeAPISubsystem_h_61_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UClaudeAPISubsystem(UClaudeAPISubsystem&&) = delete; \
	UClaudeAPISubsystem(const UClaudeAPISubsystem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UClaudeAPISubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UClaudeAPISubsystem); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UClaudeAPISubsystem) \
	NO_API virtual ~UClaudeAPISubsystem();


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ClaudeAPISubsystem_h_58_PROLOG
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ClaudeAPISubsystem_h_61_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ClaudeAPISubsystem_h_61_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ClaudeAPISubsystem_h_61_INCLASS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ClaudeAPISubsystem_h_61_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UClaudeAPISubsystem;

// ********** End Class UClaudeAPISubsystem ********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ClaudeAPISubsystem_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
