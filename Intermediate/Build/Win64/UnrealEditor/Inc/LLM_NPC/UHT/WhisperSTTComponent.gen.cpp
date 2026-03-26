// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Dialogue/WhisperSTTComponent.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeWhisperSTTComponent() {}

// ********** Begin Cross Module References ********************************************************
AUDIOCAPTURE_API UClass* Z_Construct_UClass_UAudioCaptureComponent_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UNPCSubsystemComponent();
LLM_NPC_API UClass* Z_Construct_UClass_UWhisperSTTComponent();
LLM_NPC_API UClass* Z_Construct_UClass_UWhisperSTTComponent_NoRegister();
LLM_NPC_API UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnTranscriptReady__DelegateSignature();
LLM_NPC_API UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnVoiceActivityChanged__DelegateSignature();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FOnTranscriptReady ****************************************************
struct Z_Construct_UDelegateFunction_LLM_NPC_OnTranscriptReady__DelegateSignature_Statics
{
	struct _Script_LLM_NPC_eventOnTranscriptReady_Parms
	{
		FString Transcript;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Delegate fired when a transcript is ready from speech-to-text. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/WhisperSTTComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Delegate fired when a transcript is ready from speech-to-text." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Transcript_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnTranscriptReady constinit property declarations ********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Transcript;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FOnTranscriptReady constinit property declarations **********************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FOnTranscriptReady Property Definitions *******************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UDelegateFunction_LLM_NPC_OnTranscriptReady__DelegateSignature_Statics::NewProp_Transcript = { "Transcript", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_LLM_NPC_eventOnTranscriptReady_Parms, Transcript), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Transcript_MetaData), NewProp_Transcript_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_LLM_NPC_OnTranscriptReady__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LLM_NPC_OnTranscriptReady__DelegateSignature_Statics::NewProp_Transcript,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnTranscriptReady__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FOnTranscriptReady Property Definitions *********************************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_LLM_NPC_OnTranscriptReady__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_LLM_NPC, nullptr, "OnTranscriptReady__DelegateSignature", 	Z_Construct_UDelegateFunction_LLM_NPC_OnTranscriptReady__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnTranscriptReady__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_LLM_NPC_OnTranscriptReady__DelegateSignature_Statics::_Script_LLM_NPC_eventOnTranscriptReady_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnTranscriptReady__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_LLM_NPC_OnTranscriptReady__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_LLM_NPC_OnTranscriptReady__DelegateSignature_Statics::_Script_LLM_NPC_eventOnTranscriptReady_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnTranscriptReady__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_LLM_NPC_OnTranscriptReady__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnTranscriptReady_DelegateWrapper(const FMulticastScriptDelegate& OnTranscriptReady, const FString& Transcript)
{
	struct _Script_LLM_NPC_eventOnTranscriptReady_Parms
	{
		FString Transcript;
	};
	_Script_LLM_NPC_eventOnTranscriptReady_Parms Parms;
	Parms.Transcript=Transcript;
	OnTranscriptReady.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnTranscriptReady ******************************************************

// ********** Begin Delegate FOnVoiceActivityChanged ***********************************************
struct Z_Construct_UDelegateFunction_LLM_NPC_OnVoiceActivityChanged__DelegateSignature_Statics
{
	struct _Script_LLM_NPC_eventOnVoiceActivityChanged_Parms
	{
		bool bIsSpeaking;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Delegate fired when voice activity is detected (started/stopped speaking). */" },
#endif
		{ "ModuleRelativePath", "Dialogue/WhisperSTTComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Delegate fired when voice activity is detected (started/stopped speaking)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnVoiceActivityChanged constinit property declarations ***************
	static void NewProp_bIsSpeaking_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsSpeaking;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FOnVoiceActivityChanged constinit property declarations *****************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FOnVoiceActivityChanged Property Definitions **************************
void Z_Construct_UDelegateFunction_LLM_NPC_OnVoiceActivityChanged__DelegateSignature_Statics::NewProp_bIsSpeaking_SetBit(void* Obj)
{
	((_Script_LLM_NPC_eventOnVoiceActivityChanged_Parms*)Obj)->bIsSpeaking = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UDelegateFunction_LLM_NPC_OnVoiceActivityChanged__DelegateSignature_Statics::NewProp_bIsSpeaking = { "bIsSpeaking", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(_Script_LLM_NPC_eventOnVoiceActivityChanged_Parms), &Z_Construct_UDelegateFunction_LLM_NPC_OnVoiceActivityChanged__DelegateSignature_Statics::NewProp_bIsSpeaking_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_LLM_NPC_OnVoiceActivityChanged__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LLM_NPC_OnVoiceActivityChanged__DelegateSignature_Statics::NewProp_bIsSpeaking,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnVoiceActivityChanged__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FOnVoiceActivityChanged Property Definitions ****************************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_LLM_NPC_OnVoiceActivityChanged__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_LLM_NPC, nullptr, "OnVoiceActivityChanged__DelegateSignature", 	Z_Construct_UDelegateFunction_LLM_NPC_OnVoiceActivityChanged__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnVoiceActivityChanged__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_LLM_NPC_OnVoiceActivityChanged__DelegateSignature_Statics::_Script_LLM_NPC_eventOnVoiceActivityChanged_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnVoiceActivityChanged__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_LLM_NPC_OnVoiceActivityChanged__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_LLM_NPC_OnVoiceActivityChanged__DelegateSignature_Statics::_Script_LLM_NPC_eventOnVoiceActivityChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnVoiceActivityChanged__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_LLM_NPC_OnVoiceActivityChanged__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnVoiceActivityChanged_DelegateWrapper(const FMulticastScriptDelegate& OnVoiceActivityChanged, bool bIsSpeaking)
{
	struct _Script_LLM_NPC_eventOnVoiceActivityChanged_Parms
	{
		bool bIsSpeaking;
	};
	_Script_LLM_NPC_eventOnVoiceActivityChanged_Parms Parms;
	Parms.bIsSpeaking=bIsSpeaking ? true : false;
	OnVoiceActivityChanged.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnVoiceActivityChanged *************************************************

// ********** Begin Class UWhisperSTTComponent Function IsListening ********************************
struct Z_Construct_UFunction_UWhisperSTTComponent_IsListening_Statics
{
	struct WhisperSTTComponent_eventIsListening_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|STT" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Whether the component is actively listening. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/WhisperSTTComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Whether the component is actively listening." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function IsListening constinit property declarations ***************************
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsListening constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsListening Property Definitions **************************************
void Z_Construct_UFunction_UWhisperSTTComponent_IsListening_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((WhisperSTTComponent_eventIsListening_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UWhisperSTTComponent_IsListening_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(WhisperSTTComponent_eventIsListening_Parms), &Z_Construct_UFunction_UWhisperSTTComponent_IsListening_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UWhisperSTTComponent_IsListening_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UWhisperSTTComponent_IsListening_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UWhisperSTTComponent_IsListening_Statics::PropPointers) < 2048);
// ********** End Function IsListening Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UWhisperSTTComponent_IsListening_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UWhisperSTTComponent, nullptr, "IsListening", 	Z_Construct_UFunction_UWhisperSTTComponent_IsListening_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UWhisperSTTComponent_IsListening_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UWhisperSTTComponent_IsListening_Statics::WhisperSTTComponent_eventIsListening_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UWhisperSTTComponent_IsListening_Statics::Function_MetaDataParams), Z_Construct_UFunction_UWhisperSTTComponent_IsListening_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UWhisperSTTComponent_IsListening_Statics::WhisperSTTComponent_eventIsListening_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UWhisperSTTComponent_IsListening()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UWhisperSTTComponent_IsListening_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UWhisperSTTComponent::execIsListening)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsListening();
	P_NATIVE_END;
}
// ********** End Class UWhisperSTTComponent Function IsListening **********************************

// ********** Begin Class UWhisperSTTComponent Function StartListening *****************************
struct Z_Construct_UFunction_UWhisperSTTComponent_StartListening_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|STT" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Start listening for speech input. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/WhisperSTTComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Start listening for speech input." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function StartListening constinit property declarations ************************
// ********** End Function StartListening constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UWhisperSTTComponent_StartListening_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UWhisperSTTComponent, nullptr, "StartListening", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UWhisperSTTComponent_StartListening_Statics::Function_MetaDataParams), Z_Construct_UFunction_UWhisperSTTComponent_StartListening_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UWhisperSTTComponent_StartListening()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UWhisperSTTComponent_StartListening_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UWhisperSTTComponent::execStartListening)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->StartListening();
	P_NATIVE_END;
}
// ********** End Class UWhisperSTTComponent Function StartListening *******************************

// ********** Begin Class UWhisperSTTComponent Function StopListening ******************************
struct Z_Construct_UFunction_UWhisperSTTComponent_StopListening_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|STT" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Stop listening for speech input. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/WhisperSTTComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Stop listening for speech input." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function StopListening constinit property declarations *************************
// ********** End Function StopListening constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UWhisperSTTComponent_StopListening_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UWhisperSTTComponent, nullptr, "StopListening", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UWhisperSTTComponent_StopListening_Statics::Function_MetaDataParams), Z_Construct_UFunction_UWhisperSTTComponent_StopListening_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UWhisperSTTComponent_StopListening()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UWhisperSTTComponent_StopListening_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UWhisperSTTComponent::execStopListening)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->StopListening();
	P_NATIVE_END;
}
// ********** End Class UWhisperSTTComponent Function StopListening ********************************

// ********** Begin Class UWhisperSTTComponent *****************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UWhisperSTTComponent;
UClass* UWhisperSTTComponent::GetPrivateStaticClass()
{
	using TClass = UWhisperSTTComponent;
	if (!Z_Registration_Info_UClass_UWhisperSTTComponent.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("WhisperSTTComponent"),
			Z_Registration_Info_UClass_UWhisperSTTComponent.InnerSingleton,
			StaticRegisterNativesUWhisperSTTComponent,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UWhisperSTTComponent.InnerSingleton;
}
UClass* Z_Construct_UClass_UWhisperSTTComponent_NoRegister()
{
	return UWhisperSTTComponent::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UWhisperSTTComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "LLMNPC" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Speech-to-text component using whisper.cpp for local inference.\n *\n * Captures microphone audio via UAudioCaptureComponent, performs energy-based\n * Voice Activity Detection (VAD), and sends detected speech segments to a\n * background worker thread for transcription.\n */" },
#endif
		{ "IncludePath", "Dialogue/WhisperSTTComponent.h" },
		{ "ModuleRelativePath", "Dialogue/WhisperSTTComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Speech-to-text component using whisper.cpp for local inference.\n\nCaptures microphone audio via UAudioCaptureComponent, performs energy-based\nVoice Activity Detection (VAD), and sends detected speech segments to a\nbackground worker thread for transcription." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnTranscriptReady_MetaData[] = {
		{ "Category", "NPC|STT" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Fired when a transcription is complete. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/WhisperSTTComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Fired when a transcription is complete." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnVoiceActivityChanged_MetaData[] = {
		{ "Category", "NPC|STT" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Fired when voice activity changes (started/stopped speaking). */" },
#endif
		{ "ModuleRelativePath", "Dialogue/WhisperSTTComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Fired when voice activity changes (started/stopped speaking)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WhisperModelPath_MetaData[] = {
		{ "Category", "NPC|STT|Config" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Path to the whisper.cpp model file (relative to Content directory). */" },
#endif
		{ "ModuleRelativePath", "Dialogue/WhisperSTTComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Path to the whisper.cpp model file (relative to Content directory)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Language_MetaData[] = {
		{ "Category", "NPC|STT|Config" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Language code for transcription (e.g., \"en\" for English). */" },
#endif
		{ "ModuleRelativePath", "Dialogue/WhisperSTTComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Language code for transcription (e.g., \"en\" for English)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SampleRate_MetaData[] = {
		{ "Category", "NPC|STT|Config" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Audio sample rate in Hz. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/WhisperSTTComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Audio sample rate in Hz." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VADEnergyThreshold_MetaData[] = {
		{ "Category", "NPC|STT|Config" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Energy threshold for Voice Activity Detection. Audio below this is considered silence. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/WhisperSTTComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Energy threshold for Voice Activity Detection. Audio below this is considered silence." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SilenceDuration_MetaData[] = {
		{ "Category", "NPC|STT|Config" },
		{ "ClampMax", "5.0" },
		{ "ClampMin", "0.1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Duration of silence (seconds) required to trigger end-of-speech. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/WhisperSTTComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Duration of silence (seconds) required to trigger end-of-speech." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinSpeechDuration_MetaData[] = {
		{ "Category", "NPC|STT|Config" },
		{ "ClampMax", "5.0" },
		{ "ClampMin", "0.1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Minimum speech duration (seconds) to avoid processing noise bursts. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/WhisperSTTComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Minimum speech duration (seconds) to avoid processing noise bursts." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AudioCaptureComponent_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Audio capture component for microphone input. */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Dialogue/WhisperSTTComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Audio capture component for microphone input." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UWhisperSTTComponent constinit property declarations *********************
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnTranscriptReady;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnVoiceActivityChanged;
	static const UECodeGen_Private::FStrPropertyParams NewProp_WhisperModelPath;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Language;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SampleRate;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_VADEnergyThreshold;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SilenceDuration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MinSpeechDuration;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AudioCaptureComponent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UWhisperSTTComponent constinit property declarations ***********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("IsListening"), .Pointer = &UWhisperSTTComponent::execIsListening },
		{ .NameUTF8 = UTF8TEXT("StartListening"), .Pointer = &UWhisperSTTComponent::execStartListening },
		{ .NameUTF8 = UTF8TEXT("StopListening"), .Pointer = &UWhisperSTTComponent::execStopListening },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UWhisperSTTComponent_IsListening, "IsListening" }, // 3362891604
		{ &Z_Construct_UFunction_UWhisperSTTComponent_StartListening, "StartListening" }, // 1441672176
		{ &Z_Construct_UFunction_UWhisperSTTComponent_StopListening, "StopListening" }, // 145375786
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UWhisperSTTComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UWhisperSTTComponent_Statics

// ********** Begin Class UWhisperSTTComponent Property Definitions ********************************
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UWhisperSTTComponent_Statics::NewProp_OnTranscriptReady = { "OnTranscriptReady", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UWhisperSTTComponent, OnTranscriptReady), Z_Construct_UDelegateFunction_LLM_NPC_OnTranscriptReady__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnTranscriptReady_MetaData), NewProp_OnTranscriptReady_MetaData) }; // 4026011059
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UWhisperSTTComponent_Statics::NewProp_OnVoiceActivityChanged = { "OnVoiceActivityChanged", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UWhisperSTTComponent, OnVoiceActivityChanged), Z_Construct_UDelegateFunction_LLM_NPC_OnVoiceActivityChanged__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnVoiceActivityChanged_MetaData), NewProp_OnVoiceActivityChanged_MetaData) }; // 3842633548
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UWhisperSTTComponent_Statics::NewProp_WhisperModelPath = { "WhisperModelPath", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UWhisperSTTComponent, WhisperModelPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WhisperModelPath_MetaData), NewProp_WhisperModelPath_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UWhisperSTTComponent_Statics::NewProp_Language = { "Language", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UWhisperSTTComponent, Language), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Language_MetaData), NewProp_Language_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UWhisperSTTComponent_Statics::NewProp_SampleRate = { "SampleRate", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UWhisperSTTComponent, SampleRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SampleRate_MetaData), NewProp_SampleRate_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UWhisperSTTComponent_Statics::NewProp_VADEnergyThreshold = { "VADEnergyThreshold", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UWhisperSTTComponent, VADEnergyThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VADEnergyThreshold_MetaData), NewProp_VADEnergyThreshold_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UWhisperSTTComponent_Statics::NewProp_SilenceDuration = { "SilenceDuration", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UWhisperSTTComponent, SilenceDuration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SilenceDuration_MetaData), NewProp_SilenceDuration_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UWhisperSTTComponent_Statics::NewProp_MinSpeechDuration = { "MinSpeechDuration", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UWhisperSTTComponent, MinSpeechDuration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinSpeechDuration_MetaData), NewProp_MinSpeechDuration_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UWhisperSTTComponent_Statics::NewProp_AudioCaptureComponent = { "AudioCaptureComponent", nullptr, (EPropertyFlags)0x0144000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UWhisperSTTComponent, AudioCaptureComponent), Z_Construct_UClass_UAudioCaptureComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AudioCaptureComponent_MetaData), NewProp_AudioCaptureComponent_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UWhisperSTTComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UWhisperSTTComponent_Statics::NewProp_OnTranscriptReady,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UWhisperSTTComponent_Statics::NewProp_OnVoiceActivityChanged,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UWhisperSTTComponent_Statics::NewProp_WhisperModelPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UWhisperSTTComponent_Statics::NewProp_Language,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UWhisperSTTComponent_Statics::NewProp_SampleRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UWhisperSTTComponent_Statics::NewProp_VADEnergyThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UWhisperSTTComponent_Statics::NewProp_SilenceDuration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UWhisperSTTComponent_Statics::NewProp_MinSpeechDuration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UWhisperSTTComponent_Statics::NewProp_AudioCaptureComponent,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UWhisperSTTComponent_Statics::PropPointers) < 2048);
// ********** End Class UWhisperSTTComponent Property Definitions **********************************
UObject* (*const Z_Construct_UClass_UWhisperSTTComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UNPCSubsystemComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UWhisperSTTComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UWhisperSTTComponent_Statics::ClassParams = {
	&UWhisperSTTComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UWhisperSTTComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UWhisperSTTComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UWhisperSTTComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UWhisperSTTComponent_Statics::Class_MetaDataParams)
};
void UWhisperSTTComponent::StaticRegisterNativesUWhisperSTTComponent()
{
	UClass* Class = UWhisperSTTComponent::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UWhisperSTTComponent_Statics::Funcs));
}
UClass* Z_Construct_UClass_UWhisperSTTComponent()
{
	if (!Z_Registration_Info_UClass_UWhisperSTTComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UWhisperSTTComponent.OuterSingleton, Z_Construct_UClass_UWhisperSTTComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UWhisperSTTComponent.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UWhisperSTTComponent);
UWhisperSTTComponent::~UWhisperSTTComponent() {}
// ********** End Class UWhisperSTTComponent *******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_WhisperSTTComponent_h__Script_LLM_NPC_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UWhisperSTTComponent, UWhisperSTTComponent::StaticClass, TEXT("UWhisperSTTComponent"), &Z_Registration_Info_UClass_UWhisperSTTComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UWhisperSTTComponent), 1212344207U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_WhisperSTTComponent_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_WhisperSTTComponent_h__Script_LLM_NPC_29258209{
	TEXT("/Script/LLM_NPC"),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_WhisperSTTComponent_h__Script_LLM_NPC_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_WhisperSTTComponent_h__Script_LLM_NPC_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
