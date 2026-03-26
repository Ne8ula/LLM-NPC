// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Dialogue/ElevenLabsTTSComponent.h"

#ifdef LLM_NPC_ElevenLabsTTSComponent_generated_h
#error "ElevenLabsTTSComponent.generated.h already included, missing '#pragma once' in ElevenLabsTTSComponent.h"
#endif
#define LLM_NPC_ElevenLabsTTSComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UAudioComponent;

// ********** Begin Delegate FOnSpeechStarted ******************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ElevenLabsTTSComponent_h_11_DELEGATE \
LLM_NPC_API void FOnSpeechStarted_DelegateWrapper(const FMulticastScriptDelegate& OnSpeechStarted);


// ********** End Delegate FOnSpeechStarted ********************************************************

// ********** Begin Delegate FOnSpeechFinished *****************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ElevenLabsTTSComponent_h_14_DELEGATE \
LLM_NPC_API void FOnSpeechFinished_DelegateWrapper(const FMulticastScriptDelegate& OnSpeechFinished);


// ********** End Delegate FOnSpeechFinished *******************************************************

// ********** Begin Delegate FOnTTSAudioDataReceived ***********************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ElevenLabsTTSComponent_h_17_DELEGATE \
LLM_NPC_API void FOnTTSAudioDataReceived_DelegateWrapper(const FMulticastScriptDelegate& OnTTSAudioDataReceived, TArray<uint8> const& AudioData, int32 SampleRate);


// ********** End Delegate FOnTTSAudioDataReceived *************************************************

// ********** Begin Class UElevenLabsTTSComponent **************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ElevenLabsTTSComponent_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnAudioPlaybackFinished); \
	DECLARE_FUNCTION(execGetAudioComponent); \
	DECLARE_FUNCTION(execIsSpeaking); \
	DECLARE_FUNCTION(execStopSpeaking); \
	DECLARE_FUNCTION(execSpeakText);


struct Z_Construct_UClass_UElevenLabsTTSComponent_Statics;
LLM_NPC_API UClass* Z_Construct_UClass_UElevenLabsTTSComponent_NoRegister();

#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ElevenLabsTTSComponent_h_28_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUElevenLabsTTSComponent(); \
	friend struct ::Z_Construct_UClass_UElevenLabsTTSComponent_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend LLM_NPC_API UClass* ::Z_Construct_UClass_UElevenLabsTTSComponent_NoRegister(); \
public: \
	DECLARE_CLASS2(UElevenLabsTTSComponent, UNPCSubsystemComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LLM_NPC"), Z_Construct_UClass_UElevenLabsTTSComponent_NoRegister) \
	DECLARE_SERIALIZER(UElevenLabsTTSComponent)


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ElevenLabsTTSComponent_h_28_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UElevenLabsTTSComponent(UElevenLabsTTSComponent&&) = delete; \
	UElevenLabsTTSComponent(const UElevenLabsTTSComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UElevenLabsTTSComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UElevenLabsTTSComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UElevenLabsTTSComponent) \
	NO_API virtual ~UElevenLabsTTSComponent();


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ElevenLabsTTSComponent_h_25_PROLOG
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ElevenLabsTTSComponent_h_28_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ElevenLabsTTSComponent_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ElevenLabsTTSComponent_h_28_INCLASS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ElevenLabsTTSComponent_h_28_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UElevenLabsTTSComponent;

// ********** End Class UElevenLabsTTSComponent ****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ElevenLabsTTSComponent_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
