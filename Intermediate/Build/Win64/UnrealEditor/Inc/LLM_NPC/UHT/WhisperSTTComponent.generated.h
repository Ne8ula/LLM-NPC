// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Dialogue/WhisperSTTComponent.h"

#ifdef LLM_NPC_WhisperSTTComponent_generated_h
#error "WhisperSTTComponent.generated.h already included, missing '#pragma once' in WhisperSTTComponent.h"
#endif
#define LLM_NPC_WhisperSTTComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Delegate FOnTranscriptReady ****************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_WhisperSTTComponent_h_12_DELEGATE \
LLM_NPC_API void FOnTranscriptReady_DelegateWrapper(const FMulticastScriptDelegate& OnTranscriptReady, const FString& Transcript);


// ********** End Delegate FOnTranscriptReady ******************************************************

// ********** Begin Delegate FOnVoiceActivityChanged ***********************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_WhisperSTTComponent_h_15_DELEGATE \
LLM_NPC_API void FOnVoiceActivityChanged_DelegateWrapper(const FMulticastScriptDelegate& OnVoiceActivityChanged, bool bIsSpeaking);


// ********** End Delegate FOnVoiceActivityChanged *************************************************

// ********** Begin Class UWhisperSTTComponent *****************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_WhisperSTTComponent_h_83_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execIsListening); \
	DECLARE_FUNCTION(execStopListening); \
	DECLARE_FUNCTION(execStartListening);


struct Z_Construct_UClass_UWhisperSTTComponent_Statics;
LLM_NPC_API UClass* Z_Construct_UClass_UWhisperSTTComponent_NoRegister();

#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_WhisperSTTComponent_h_83_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUWhisperSTTComponent(); \
	friend struct ::Z_Construct_UClass_UWhisperSTTComponent_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend LLM_NPC_API UClass* ::Z_Construct_UClass_UWhisperSTTComponent_NoRegister(); \
public: \
	DECLARE_CLASS2(UWhisperSTTComponent, UNPCSubsystemComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LLM_NPC"), Z_Construct_UClass_UWhisperSTTComponent_NoRegister) \
	DECLARE_SERIALIZER(UWhisperSTTComponent)


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_WhisperSTTComponent_h_83_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UWhisperSTTComponent(UWhisperSTTComponent&&) = delete; \
	UWhisperSTTComponent(const UWhisperSTTComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UWhisperSTTComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UWhisperSTTComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UWhisperSTTComponent) \
	NO_API virtual ~UWhisperSTTComponent();


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_WhisperSTTComponent_h_80_PROLOG
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_WhisperSTTComponent_h_83_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_WhisperSTTComponent_h_83_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_WhisperSTTComponent_h_83_INCLASS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_WhisperSTTComponent_h_83_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UWhisperSTTComponent;

// ********** End Class UWhisperSTTComponent *******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_WhisperSTTComponent_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
