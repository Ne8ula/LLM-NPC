// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Dialogue/ElevenLabsTTSComponent.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeElevenLabsTTSComponent() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UAudioComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USoundWaveProcedural_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UElevenLabsTTSComponent();
LLM_NPC_API UClass* Z_Construct_UClass_UElevenLabsTTSComponent_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UNPCSubsystemComponent();
LLM_NPC_API UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnSpeechFinished__DelegateSignature();
LLM_NPC_API UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnSpeechStarted__DelegateSignature();
LLM_NPC_API UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnTTSAudioDataReceived__DelegateSignature();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FOnSpeechStarted ******************************************************
struct Z_Construct_UDelegateFunction_LLM_NPC_OnSpeechStarted__DelegateSignature_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Delegate fired when TTS speech playback starts. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ElevenLabsTTSComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Delegate fired when TTS speech playback starts." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnSpeechStarted constinit property declarations **********************
// ********** End Delegate FOnSpeechStarted constinit property declarations ************************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_LLM_NPC_OnSpeechStarted__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_LLM_NPC, nullptr, "OnSpeechStarted__DelegateSignature", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnSpeechStarted__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_LLM_NPC_OnSpeechStarted__DelegateSignature_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnSpeechStarted__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_LLM_NPC_OnSpeechStarted__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnSpeechStarted_DelegateWrapper(const FMulticastScriptDelegate& OnSpeechStarted)
{
	OnSpeechStarted.ProcessMulticastDelegate<UObject>(NULL);
}
// ********** End Delegate FOnSpeechStarted ********************************************************

// ********** Begin Delegate FOnSpeechFinished *****************************************************
struct Z_Construct_UDelegateFunction_LLM_NPC_OnSpeechFinished__DelegateSignature_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Delegate fired when TTS speech playback finishes. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ElevenLabsTTSComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Delegate fired when TTS speech playback finishes." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnSpeechFinished constinit property declarations *********************
// ********** End Delegate FOnSpeechFinished constinit property declarations ***********************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_LLM_NPC_OnSpeechFinished__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_LLM_NPC, nullptr, "OnSpeechFinished__DelegateSignature", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnSpeechFinished__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_LLM_NPC_OnSpeechFinished__DelegateSignature_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnSpeechFinished__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_LLM_NPC_OnSpeechFinished__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnSpeechFinished_DelegateWrapper(const FMulticastScriptDelegate& OnSpeechFinished)
{
	OnSpeechFinished.ProcessMulticastDelegate<UObject>(NULL);
}
// ********** End Delegate FOnSpeechFinished *******************************************************

// ********** Begin Delegate FOnTTSAudioDataReceived ***********************************************
struct Z_Construct_UDelegateFunction_LLM_NPC_OnTTSAudioDataReceived__DelegateSignature_Statics
{
	struct _Script_LLM_NPC_eventOnTTSAudioDataReceived_Parms
	{
		TArray<uint8> AudioData;
		int32 SampleRate;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Delegate fired when raw audio data is received (for lip sync). */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ElevenLabsTTSComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Delegate fired when raw audio data is received (for lip sync)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AudioData_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnTTSAudioDataReceived constinit property declarations ***************
	static const UECodeGen_Private::FBytePropertyParams NewProp_AudioData_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_AudioData;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SampleRate;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FOnTTSAudioDataReceived constinit property declarations *****************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FOnTTSAudioDataReceived Property Definitions **************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UDelegateFunction_LLM_NPC_OnTTSAudioDataReceived__DelegateSignature_Statics::NewProp_AudioData_Inner = { "AudioData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UDelegateFunction_LLM_NPC_OnTTSAudioDataReceived__DelegateSignature_Statics::NewProp_AudioData = { "AudioData", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_LLM_NPC_eventOnTTSAudioDataReceived_Parms, AudioData), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AudioData_MetaData), NewProp_AudioData_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UDelegateFunction_LLM_NPC_OnTTSAudioDataReceived__DelegateSignature_Statics::NewProp_SampleRate = { "SampleRate", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_LLM_NPC_eventOnTTSAudioDataReceived_Parms, SampleRate), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_LLM_NPC_OnTTSAudioDataReceived__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LLM_NPC_OnTTSAudioDataReceived__DelegateSignature_Statics::NewProp_AudioData_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LLM_NPC_OnTTSAudioDataReceived__DelegateSignature_Statics::NewProp_AudioData,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LLM_NPC_OnTTSAudioDataReceived__DelegateSignature_Statics::NewProp_SampleRate,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnTTSAudioDataReceived__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FOnTTSAudioDataReceived Property Definitions ****************************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_LLM_NPC_OnTTSAudioDataReceived__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_LLM_NPC, nullptr, "OnTTSAudioDataReceived__DelegateSignature", 	Z_Construct_UDelegateFunction_LLM_NPC_OnTTSAudioDataReceived__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnTTSAudioDataReceived__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_LLM_NPC_OnTTSAudioDataReceived__DelegateSignature_Statics::_Script_LLM_NPC_eventOnTTSAudioDataReceived_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00530000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnTTSAudioDataReceived__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_LLM_NPC_OnTTSAudioDataReceived__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_LLM_NPC_OnTTSAudioDataReceived__DelegateSignature_Statics::_Script_LLM_NPC_eventOnTTSAudioDataReceived_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnTTSAudioDataReceived__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_LLM_NPC_OnTTSAudioDataReceived__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnTTSAudioDataReceived_DelegateWrapper(const FMulticastScriptDelegate& OnTTSAudioDataReceived, TArray<uint8> const& AudioData, int32 SampleRate)
{
	struct _Script_LLM_NPC_eventOnTTSAudioDataReceived_Parms
	{
		TArray<uint8> AudioData;
		int32 SampleRate;
	};
	_Script_LLM_NPC_eventOnTTSAudioDataReceived_Parms Parms;
	Parms.AudioData=AudioData;
	Parms.SampleRate=SampleRate;
	OnTTSAudioDataReceived.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnTTSAudioDataReceived *************************************************

// ********** Begin Class UElevenLabsTTSComponent Function GetAudioComponent ***********************
struct Z_Construct_UFunction_UElevenLabsTTSComponent_GetAudioComponent_Statics
{
	struct ElevenLabsTTSComponent_eventGetAudioComponent_Parms
	{
		UAudioComponent* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|TTS" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get the UAudioComponent used for playback (useful for spatial audio setup). */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ElevenLabsTTSComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get the UAudioComponent used for playback (useful for spatial audio setup)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetAudioComponent constinit property declarations *********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetAudioComponent constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetAudioComponent Property Definitions ********************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UElevenLabsTTSComponent_GetAudioComponent_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000080588, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ElevenLabsTTSComponent_eventGetAudioComponent_Parms, ReturnValue), Z_Construct_UClass_UAudioComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReturnValue_MetaData), NewProp_ReturnValue_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UElevenLabsTTSComponent_GetAudioComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UElevenLabsTTSComponent_GetAudioComponent_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UElevenLabsTTSComponent_GetAudioComponent_Statics::PropPointers) < 2048);
// ********** End Function GetAudioComponent Property Definitions **********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UElevenLabsTTSComponent_GetAudioComponent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UElevenLabsTTSComponent, nullptr, "GetAudioComponent", 	Z_Construct_UFunction_UElevenLabsTTSComponent_GetAudioComponent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UElevenLabsTTSComponent_GetAudioComponent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UElevenLabsTTSComponent_GetAudioComponent_Statics::ElevenLabsTTSComponent_eventGetAudioComponent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UElevenLabsTTSComponent_GetAudioComponent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UElevenLabsTTSComponent_GetAudioComponent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UElevenLabsTTSComponent_GetAudioComponent_Statics::ElevenLabsTTSComponent_eventGetAudioComponent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UElevenLabsTTSComponent_GetAudioComponent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UElevenLabsTTSComponent_GetAudioComponent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UElevenLabsTTSComponent::execGetAudioComponent)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UAudioComponent**)Z_Param__Result=P_THIS->GetAudioComponent();
	P_NATIVE_END;
}
// ********** End Class UElevenLabsTTSComponent Function GetAudioComponent *************************

// ********** Begin Class UElevenLabsTTSComponent Function IsSpeaking ******************************
struct Z_Construct_UFunction_UElevenLabsTTSComponent_IsSpeaking_Statics
{
	struct ElevenLabsTTSComponent_eventIsSpeaking_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|TTS" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Whether speech is currently playing. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ElevenLabsTTSComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Whether speech is currently playing." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function IsSpeaking constinit property declarations ****************************
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsSpeaking constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsSpeaking Property Definitions ***************************************
void Z_Construct_UFunction_UElevenLabsTTSComponent_IsSpeaking_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((ElevenLabsTTSComponent_eventIsSpeaking_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UElevenLabsTTSComponent_IsSpeaking_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ElevenLabsTTSComponent_eventIsSpeaking_Parms), &Z_Construct_UFunction_UElevenLabsTTSComponent_IsSpeaking_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UElevenLabsTTSComponent_IsSpeaking_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UElevenLabsTTSComponent_IsSpeaking_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UElevenLabsTTSComponent_IsSpeaking_Statics::PropPointers) < 2048);
// ********** End Function IsSpeaking Property Definitions *****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UElevenLabsTTSComponent_IsSpeaking_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UElevenLabsTTSComponent, nullptr, "IsSpeaking", 	Z_Construct_UFunction_UElevenLabsTTSComponent_IsSpeaking_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UElevenLabsTTSComponent_IsSpeaking_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UElevenLabsTTSComponent_IsSpeaking_Statics::ElevenLabsTTSComponent_eventIsSpeaking_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UElevenLabsTTSComponent_IsSpeaking_Statics::Function_MetaDataParams), Z_Construct_UFunction_UElevenLabsTTSComponent_IsSpeaking_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UElevenLabsTTSComponent_IsSpeaking_Statics::ElevenLabsTTSComponent_eventIsSpeaking_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UElevenLabsTTSComponent_IsSpeaking()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UElevenLabsTTSComponent_IsSpeaking_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UElevenLabsTTSComponent::execIsSpeaking)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsSpeaking();
	P_NATIVE_END;
}
// ********** End Class UElevenLabsTTSComponent Function IsSpeaking ********************************

// ********** Begin Class UElevenLabsTTSComponent Function OnAudioPlaybackFinished *****************
struct Z_Construct_UFunction_UElevenLabsTTSComponent_OnAudioPlaybackFinished_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Callback when audio playback finishes. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ElevenLabsTTSComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Callback when audio playback finishes." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function OnAudioPlaybackFinished constinit property declarations ***************
// ********** End Function OnAudioPlaybackFinished constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UElevenLabsTTSComponent_OnAudioPlaybackFinished_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UElevenLabsTTSComponent, nullptr, "OnAudioPlaybackFinished", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UElevenLabsTTSComponent_OnAudioPlaybackFinished_Statics::Function_MetaDataParams), Z_Construct_UFunction_UElevenLabsTTSComponent_OnAudioPlaybackFinished_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UElevenLabsTTSComponent_OnAudioPlaybackFinished()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UElevenLabsTTSComponent_OnAudioPlaybackFinished_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UElevenLabsTTSComponent::execOnAudioPlaybackFinished)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnAudioPlaybackFinished();
	P_NATIVE_END;
}
// ********** End Class UElevenLabsTTSComponent Function OnAudioPlaybackFinished *******************

// ********** Begin Class UElevenLabsTTSComponent Function SpeakText *******************************
struct Z_Construct_UFunction_UElevenLabsTTSComponent_SpeakText_Statics
{
	struct ElevenLabsTTSComponent_eventSpeakText_Parms
	{
		FString Text;
		FString VoiceID;
		float Stability;
		float SimilarityBoost;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|TTS" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Convert text to speech and play it.\n\x09 *\n\x09 * @param Text              The text to speak.\n\x09 * @param VoiceID           ElevenLabs voice ID. If empty, uses the default from config.\n\x09 * @param Stability         Voice stability (0.0-1.0). Negative uses default.\n\x09 * @param SimilarityBoost   Voice similarity boost (0.0-1.0). Negative uses default.\n\x09 */" },
#endif
		{ "CPP_Default_SimilarityBoost", "-1.000000" },
		{ "CPP_Default_Stability", "-1.000000" },
		{ "CPP_Default_VoiceID", "" },
		{ "ModuleRelativePath", "Dialogue/ElevenLabsTTSComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Convert text to speech and play it.\n\n@param Text              The text to speak.\n@param VoiceID           ElevenLabs voice ID. If empty, uses the default from config.\n@param Stability         Voice stability (0.0-1.0). Negative uses default.\n@param SimilarityBoost   Voice similarity boost (0.0-1.0). Negative uses default." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Text_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VoiceID_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function SpeakText constinit property declarations *****************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Text;
	static const UECodeGen_Private::FStrPropertyParams NewProp_VoiceID;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Stability;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SimilarityBoost;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SpeakText constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SpeakText Property Definitions ****************************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UElevenLabsTTSComponent_SpeakText_Statics::NewProp_Text = { "Text", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ElevenLabsTTSComponent_eventSpeakText_Parms, Text), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Text_MetaData), NewProp_Text_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UElevenLabsTTSComponent_SpeakText_Statics::NewProp_VoiceID = { "VoiceID", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ElevenLabsTTSComponent_eventSpeakText_Parms, VoiceID), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VoiceID_MetaData), NewProp_VoiceID_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UElevenLabsTTSComponent_SpeakText_Statics::NewProp_Stability = { "Stability", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ElevenLabsTTSComponent_eventSpeakText_Parms, Stability), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UElevenLabsTTSComponent_SpeakText_Statics::NewProp_SimilarityBoost = { "SimilarityBoost", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ElevenLabsTTSComponent_eventSpeakText_Parms, SimilarityBoost), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UElevenLabsTTSComponent_SpeakText_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UElevenLabsTTSComponent_SpeakText_Statics::NewProp_Text,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UElevenLabsTTSComponent_SpeakText_Statics::NewProp_VoiceID,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UElevenLabsTTSComponent_SpeakText_Statics::NewProp_Stability,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UElevenLabsTTSComponent_SpeakText_Statics::NewProp_SimilarityBoost,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UElevenLabsTTSComponent_SpeakText_Statics::PropPointers) < 2048);
// ********** End Function SpeakText Property Definitions ******************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UElevenLabsTTSComponent_SpeakText_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UElevenLabsTTSComponent, nullptr, "SpeakText", 	Z_Construct_UFunction_UElevenLabsTTSComponent_SpeakText_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UElevenLabsTTSComponent_SpeakText_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UElevenLabsTTSComponent_SpeakText_Statics::ElevenLabsTTSComponent_eventSpeakText_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UElevenLabsTTSComponent_SpeakText_Statics::Function_MetaDataParams), Z_Construct_UFunction_UElevenLabsTTSComponent_SpeakText_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UElevenLabsTTSComponent_SpeakText_Statics::ElevenLabsTTSComponent_eventSpeakText_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UElevenLabsTTSComponent_SpeakText()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UElevenLabsTTSComponent_SpeakText_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UElevenLabsTTSComponent::execSpeakText)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_Text);
	P_GET_PROPERTY(FStrProperty,Z_Param_VoiceID);
	P_GET_PROPERTY(FFloatProperty,Z_Param_Stability);
	P_GET_PROPERTY(FFloatProperty,Z_Param_SimilarityBoost);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SpeakText(Z_Param_Text,Z_Param_VoiceID,Z_Param_Stability,Z_Param_SimilarityBoost);
	P_NATIVE_END;
}
// ********** End Class UElevenLabsTTSComponent Function SpeakText *********************************

// ********** Begin Class UElevenLabsTTSComponent Function StopSpeaking ****************************
struct Z_Construct_UFunction_UElevenLabsTTSComponent_StopSpeaking_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|TTS" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Stop any currently playing speech. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ElevenLabsTTSComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Stop any currently playing speech." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function StopSpeaking constinit property declarations **************************
// ********** End Function StopSpeaking constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UElevenLabsTTSComponent_StopSpeaking_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UElevenLabsTTSComponent, nullptr, "StopSpeaking", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UElevenLabsTTSComponent_StopSpeaking_Statics::Function_MetaDataParams), Z_Construct_UFunction_UElevenLabsTTSComponent_StopSpeaking_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UElevenLabsTTSComponent_StopSpeaking()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UElevenLabsTTSComponent_StopSpeaking_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UElevenLabsTTSComponent::execStopSpeaking)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->StopSpeaking();
	P_NATIVE_END;
}
// ********** End Class UElevenLabsTTSComponent Function StopSpeaking ******************************

// ********** Begin Class UElevenLabsTTSComponent **************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UElevenLabsTTSComponent;
UClass* UElevenLabsTTSComponent::GetPrivateStaticClass()
{
	using TClass = UElevenLabsTTSComponent;
	if (!Z_Registration_Info_UClass_UElevenLabsTTSComponent.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("ElevenLabsTTSComponent"),
			Z_Registration_Info_UClass_UElevenLabsTTSComponent.InnerSingleton,
			StaticRegisterNativesUElevenLabsTTSComponent,
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
	return Z_Registration_Info_UClass_UElevenLabsTTSComponent.InnerSingleton;
}
UClass* Z_Construct_UClass_UElevenLabsTTSComponent_NoRegister()
{
	return UElevenLabsTTSComponent::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UElevenLabsTTSComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "LLMNPC" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Text-to-Speech component using the ElevenLabs API.\n *\n * Sends text to ElevenLabs, receives audio bytes, creates a USoundWaveProcedural,\n * and plays it through a UAudioComponent. Audio data is also broadcast for lip sync.\n */" },
#endif
		{ "IncludePath", "Dialogue/ElevenLabsTTSComponent.h" },
		{ "ModuleRelativePath", "Dialogue/ElevenLabsTTSComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Text-to-Speech component using the ElevenLabs API.\n\nSends text to ElevenLabs, receives audio bytes, creates a USoundWaveProcedural,\nand plays it through a UAudioComponent. Audio data is also broadcast for lip sync." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnSpeechStarted_MetaData[] = {
		{ "Category", "NPC|TTS" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Fired when speech playback starts. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ElevenLabsTTSComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Fired when speech playback starts." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnSpeechFinished_MetaData[] = {
		{ "Category", "NPC|TTS" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Fired when speech playback finishes. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ElevenLabsTTSComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Fired when speech playback finishes." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnTTSAudioDataReceived_MetaData[] = {
		{ "Category", "NPC|TTS" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Fired when raw audio data is received. Used by lip sync components. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ElevenLabsTTSComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Fired when raw audio data is received. Used by lip sync components." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultVoiceID_MetaData[] = {
		{ "Category", "NPC|TTS|Config" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Default ElevenLabs voice ID (can be overridden per call). */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ElevenLabsTTSComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Default ElevenLabs voice ID (can be overridden per call)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultStability_MetaData[] = {
		{ "Category", "NPC|TTS|Config" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Default voice stability. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ElevenLabsTTSComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Default voice stability." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultSimilarityBoost_MetaData[] = {
		{ "Category", "NPC|TTS|Config" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Default voice similarity boost. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ElevenLabsTTSComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Default voice similarity boost." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ModelID_MetaData[] = {
		{ "Category", "NPC|TTS|Config" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Audio output model ID (e.g., \"eleven_multilingual_v2\"). */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ElevenLabsTTSComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Audio output model ID (e.g., \"eleven_multilingual_v2\")." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OutputFormat_MetaData[] = {
		{ "Category", "NPC|TTS|Config" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Output audio format. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ElevenLabsTTSComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Output audio format." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AudioPlaybackComponent_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Audio component for playback. */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Dialogue/ElevenLabsTTSComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Audio component for playback." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentSoundWave_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Currently playing procedural sound wave. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ElevenLabsTTSComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Currently playing procedural sound wave." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UElevenLabsTTSComponent constinit property declarations ******************
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnSpeechStarted;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnSpeechFinished;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnTTSAudioDataReceived;
	static const UECodeGen_Private::FStrPropertyParams NewProp_DefaultVoiceID;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DefaultStability;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DefaultSimilarityBoost;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ModelID;
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutputFormat;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AudioPlaybackComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CurrentSoundWave;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UElevenLabsTTSComponent constinit property declarations ********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("GetAudioComponent"), .Pointer = &UElevenLabsTTSComponent::execGetAudioComponent },
		{ .NameUTF8 = UTF8TEXT("IsSpeaking"), .Pointer = &UElevenLabsTTSComponent::execIsSpeaking },
		{ .NameUTF8 = UTF8TEXT("OnAudioPlaybackFinished"), .Pointer = &UElevenLabsTTSComponent::execOnAudioPlaybackFinished },
		{ .NameUTF8 = UTF8TEXT("SpeakText"), .Pointer = &UElevenLabsTTSComponent::execSpeakText },
		{ .NameUTF8 = UTF8TEXT("StopSpeaking"), .Pointer = &UElevenLabsTTSComponent::execStopSpeaking },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UElevenLabsTTSComponent_GetAudioComponent, "GetAudioComponent" }, // 1171665040
		{ &Z_Construct_UFunction_UElevenLabsTTSComponent_IsSpeaking, "IsSpeaking" }, // 2735649807
		{ &Z_Construct_UFunction_UElevenLabsTTSComponent_OnAudioPlaybackFinished, "OnAudioPlaybackFinished" }, // 44341525
		{ &Z_Construct_UFunction_UElevenLabsTTSComponent_SpeakText, "SpeakText" }, // 2982902147
		{ &Z_Construct_UFunction_UElevenLabsTTSComponent_StopSpeaking, "StopSpeaking" }, // 4074216434
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UElevenLabsTTSComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UElevenLabsTTSComponent_Statics

// ********** Begin Class UElevenLabsTTSComponent Property Definitions *****************************
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_OnSpeechStarted = { "OnSpeechStarted", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UElevenLabsTTSComponent, OnSpeechStarted), Z_Construct_UDelegateFunction_LLM_NPC_OnSpeechStarted__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnSpeechStarted_MetaData), NewProp_OnSpeechStarted_MetaData) }; // 1504547028
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_OnSpeechFinished = { "OnSpeechFinished", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UElevenLabsTTSComponent, OnSpeechFinished), Z_Construct_UDelegateFunction_LLM_NPC_OnSpeechFinished__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnSpeechFinished_MetaData), NewProp_OnSpeechFinished_MetaData) }; // 4293094348
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_OnTTSAudioDataReceived = { "OnTTSAudioDataReceived", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UElevenLabsTTSComponent, OnTTSAudioDataReceived), Z_Construct_UDelegateFunction_LLM_NPC_OnTTSAudioDataReceived__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnTTSAudioDataReceived_MetaData), NewProp_OnTTSAudioDataReceived_MetaData) }; // 293502155
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_DefaultVoiceID = { "DefaultVoiceID", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UElevenLabsTTSComponent, DefaultVoiceID), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultVoiceID_MetaData), NewProp_DefaultVoiceID_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_DefaultStability = { "DefaultStability", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UElevenLabsTTSComponent, DefaultStability), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultStability_MetaData), NewProp_DefaultStability_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_DefaultSimilarityBoost = { "DefaultSimilarityBoost", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UElevenLabsTTSComponent, DefaultSimilarityBoost), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultSimilarityBoost_MetaData), NewProp_DefaultSimilarityBoost_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_ModelID = { "ModelID", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UElevenLabsTTSComponent, ModelID), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ModelID_MetaData), NewProp_ModelID_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_OutputFormat = { "OutputFormat", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UElevenLabsTTSComponent, OutputFormat), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OutputFormat_MetaData), NewProp_OutputFormat_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_AudioPlaybackComponent = { "AudioPlaybackComponent", nullptr, (EPropertyFlags)0x0144000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UElevenLabsTTSComponent, AudioPlaybackComponent), Z_Construct_UClass_UAudioComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AudioPlaybackComponent_MetaData), NewProp_AudioPlaybackComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_CurrentSoundWave = { "CurrentSoundWave", nullptr, (EPropertyFlags)0x0144000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UElevenLabsTTSComponent, CurrentSoundWave), Z_Construct_UClass_USoundWaveProcedural_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentSoundWave_MetaData), NewProp_CurrentSoundWave_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UElevenLabsTTSComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_OnSpeechStarted,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_OnSpeechFinished,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_OnTTSAudioDataReceived,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_DefaultVoiceID,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_DefaultStability,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_DefaultSimilarityBoost,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_ModelID,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_OutputFormat,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_AudioPlaybackComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_CurrentSoundWave,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UElevenLabsTTSComponent_Statics::PropPointers) < 2048);
// ********** End Class UElevenLabsTTSComponent Property Definitions *******************************
UObject* (*const Z_Construct_UClass_UElevenLabsTTSComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UNPCSubsystemComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UElevenLabsTTSComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UElevenLabsTTSComponent_Statics::ClassParams = {
	&UElevenLabsTTSComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UElevenLabsTTSComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UElevenLabsTTSComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UElevenLabsTTSComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UElevenLabsTTSComponent_Statics::Class_MetaDataParams)
};
void UElevenLabsTTSComponent::StaticRegisterNativesUElevenLabsTTSComponent()
{
	UClass* Class = UElevenLabsTTSComponent::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UElevenLabsTTSComponent_Statics::Funcs));
}
UClass* Z_Construct_UClass_UElevenLabsTTSComponent()
{
	if (!Z_Registration_Info_UClass_UElevenLabsTTSComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UElevenLabsTTSComponent.OuterSingleton, Z_Construct_UClass_UElevenLabsTTSComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UElevenLabsTTSComponent.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UElevenLabsTTSComponent);
UElevenLabsTTSComponent::~UElevenLabsTTSComponent() {}
// ********** End Class UElevenLabsTTSComponent ****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ElevenLabsTTSComponent_h__Script_LLM_NPC_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UElevenLabsTTSComponent, UElevenLabsTTSComponent::StaticClass, TEXT("UElevenLabsTTSComponent"), &Z_Registration_Info_UClass_UElevenLabsTTSComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UElevenLabsTTSComponent), 3081196279U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ElevenLabsTTSComponent_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ElevenLabsTTSComponent_h__Script_LLM_NPC_1702321208{
	TEXT("/Script/LLM_NPC"),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ElevenLabsTTSComponent_h__Script_LLM_NPC_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ElevenLabsTTSComponent_h__Script_LLM_NPC_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
