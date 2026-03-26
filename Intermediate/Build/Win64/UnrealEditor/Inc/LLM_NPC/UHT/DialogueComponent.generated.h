// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Dialogue/DialogueComponent.h"

#ifdef LLM_NPC_DialogueComponent_generated_h
#error "DialogueComponent.generated.h already included, missing '#pragma once' in DialogueComponent.h"
#endif
#define LLM_NPC_DialogueComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class EEmotionType : uint8;
struct FClaudeAPIResponse;
struct FDetectedUserEmotion;
struct FNPCMessage;

// ********** Begin Delegate FOnDialogueResponseReceived *******************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueComponent_h_19_DELEGATE \
LLM_NPC_API void FOnDialogueResponseReceived_DelegateWrapper(const FMulticastScriptDelegate& OnDialogueResponseReceived, const FString& ResponseText, EEmotionType NPCEmotionHint, bool bShouldGiveItem, FName ItemID);


// ********** End Delegate FOnDialogueResponseReceived *********************************************

// ********** Begin Delegate FOnDialogueHistoryCleared *********************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueComponent_h_22_DELEGATE \
LLM_NPC_API void FOnDialogueHistoryCleared_DelegateWrapper(const FMulticastScriptDelegate& OnDialogueHistoryCleared);


// ********** End Delegate FOnDialogueHistoryCleared ***********************************************

// ********** Begin Class UDialogueComponent *******************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueComponent_h_34_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnClaudeResponseReceived); \
	DECLARE_FUNCTION(execIsWaitingForResponse); \
	DECLARE_FUNCTION(execGetConversationLength); \
	DECLARE_FUNCTION(execGetConversationHistory); \
	DECLARE_FUNCTION(execClearConversationHistory); \
	DECLARE_FUNCTION(execSendUserMessage);


struct Z_Construct_UClass_UDialogueComponent_Statics;
LLM_NPC_API UClass* Z_Construct_UClass_UDialogueComponent_NoRegister();

#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueComponent_h_34_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUDialogueComponent(); \
	friend struct ::Z_Construct_UClass_UDialogueComponent_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend LLM_NPC_API UClass* ::Z_Construct_UClass_UDialogueComponent_NoRegister(); \
public: \
	DECLARE_CLASS2(UDialogueComponent, UNPCSubsystemComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LLM_NPC"), Z_Construct_UClass_UDialogueComponent_NoRegister) \
	DECLARE_SERIALIZER(UDialogueComponent)


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueComponent_h_34_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UDialogueComponent(UDialogueComponent&&) = delete; \
	UDialogueComponent(const UDialogueComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UDialogueComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UDialogueComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UDialogueComponent) \
	NO_API virtual ~UDialogueComponent();


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueComponent_h_31_PROLOG
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueComponent_h_34_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueComponent_h_34_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueComponent_h_34_INCLASS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueComponent_h_34_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UDialogueComponent;

// ********** End Class UDialogueComponent *********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueComponent_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
