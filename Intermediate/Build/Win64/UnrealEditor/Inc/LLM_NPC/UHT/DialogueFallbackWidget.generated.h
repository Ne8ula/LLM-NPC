// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Dialogue/DialogueFallbackWidget.h"

#ifdef LLM_NPC_DialogueFallbackWidget_generated_h
#error "DialogueFallbackWidget.generated.h already included, missing '#pragma once' in DialogueFallbackWidget.h"
#endif
#define LLM_NPC_DialogueFallbackWidget_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Delegate FOnTextSubmitted ******************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueFallbackWidget_h_13_DELEGATE \
LLM_NPC_API void FOnTextSubmitted_DelegateWrapper(const FMulticastScriptDelegate& OnTextSubmitted, const FString& SubmittedText);


// ********** End Delegate FOnTextSubmitted ********************************************************

// ********** Begin Class UDialogueFallbackWidget **************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueFallbackWidget_h_25_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnTextCommitted); \
	DECLARE_FUNCTION(execOnSendButtonClicked); \
	DECLARE_FUNCTION(execSetInputEnabled); \
	DECLARE_FUNCTION(execSetStatusText); \
	DECLARE_FUNCTION(execFocusInput); \
	DECLARE_FUNCTION(execClearInput); \
	DECLARE_FUNCTION(execSetVisibleBasedOnVoiceAvailability); \
	DECLARE_FUNCTION(execHideWidget); \
	DECLARE_FUNCTION(execShowWidget);


struct Z_Construct_UClass_UDialogueFallbackWidget_Statics;
LLM_NPC_API UClass* Z_Construct_UClass_UDialogueFallbackWidget_NoRegister();

#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueFallbackWidget_h_25_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUDialogueFallbackWidget(); \
	friend struct ::Z_Construct_UClass_UDialogueFallbackWidget_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend LLM_NPC_API UClass* ::Z_Construct_UClass_UDialogueFallbackWidget_NoRegister(); \
public: \
	DECLARE_CLASS2(UDialogueFallbackWidget, UUserWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LLM_NPC"), Z_Construct_UClass_UDialogueFallbackWidget_NoRegister) \
	DECLARE_SERIALIZER(UDialogueFallbackWidget)


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueFallbackWidget_h_25_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UDialogueFallbackWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UDialogueFallbackWidget(UDialogueFallbackWidget&&) = delete; \
	UDialogueFallbackWidget(const UDialogueFallbackWidget&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UDialogueFallbackWidget); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UDialogueFallbackWidget); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UDialogueFallbackWidget) \
	NO_API virtual ~UDialogueFallbackWidget();


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueFallbackWidget_h_22_PROLOG
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueFallbackWidget_h_25_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueFallbackWidget_h_25_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueFallbackWidget_h_25_INCLASS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueFallbackWidget_h_25_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UDialogueFallbackWidget;

// ********** End Class UDialogueFallbackWidget ****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueFallbackWidget_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
