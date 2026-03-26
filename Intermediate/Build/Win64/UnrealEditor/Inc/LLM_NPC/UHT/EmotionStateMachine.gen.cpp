// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Emotion/EmotionStateMachine.h"
#include "LLM_NPC/Core/NPCTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeEmotionStateMachine() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
LLM_NPC_API UClass* Z_Construct_UClass_UEmotionStateMachine();
LLM_NPC_API UClass* Z_Construct_UClass_UEmotionStateMachine_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UEmotionTransitionRule_NoRegister();
LLM_NPC_API UEnum* Z_Construct_UEnum_LLM_NPC_EEmotionType();
LLM_NPC_API UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionStateChanged__DelegateSignature();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FEmotionSignal();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FEmotionState();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FPADVector();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FOnEmotionStateChanged ************************************************
struct Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionStateChanged__DelegateSignature_Statics
{
	struct _Script_LLM_NPC_eventOnEmotionStateChanged_Parms
	{
		FEmotionState OldState;
		FEmotionState NewState;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Delegate fired when the emotion state changes. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionStateMachine.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Delegate fired when the emotion state changes." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnEmotionStateChanged constinit property declarations ****************
	static const UECodeGen_Private::FStructPropertyParams NewProp_OldState;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NewState;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FOnEmotionStateChanged constinit property declarations ******************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FOnEmotionStateChanged Property Definitions ***************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionStateChanged__DelegateSignature_Statics::NewProp_OldState = { "OldState", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_LLM_NPC_eventOnEmotionStateChanged_Parms, OldState), Z_Construct_UScriptStruct_FEmotionState, METADATA_PARAMS(0, nullptr) }; // 1004811449
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionStateChanged__DelegateSignature_Statics::NewProp_NewState = { "NewState", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_LLM_NPC_eventOnEmotionStateChanged_Parms, NewState), Z_Construct_UScriptStruct_FEmotionState, METADATA_PARAMS(0, nullptr) }; // 1004811449
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionStateChanged__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionStateChanged__DelegateSignature_Statics::NewProp_OldState,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionStateChanged__DelegateSignature_Statics::NewProp_NewState,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionStateChanged__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FOnEmotionStateChanged Property Definitions *****************************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionStateChanged__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_LLM_NPC, nullptr, "OnEmotionStateChanged__DelegateSignature", 	Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionStateChanged__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionStateChanged__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionStateChanged__DelegateSignature_Statics::_Script_LLM_NPC_eventOnEmotionStateChanged_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionStateChanged__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionStateChanged__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionStateChanged__DelegateSignature_Statics::_Script_LLM_NPC_eventOnEmotionStateChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionStateChanged__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionStateChanged__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnEmotionStateChanged_DelegateWrapper(const FMulticastScriptDelegate& OnEmotionStateChanged, FEmotionState OldState, FEmotionState NewState)
{
	struct _Script_LLM_NPC_eventOnEmotionStateChanged_Parms
	{
		FEmotionState OldState;
		FEmotionState NewState;
	};
	_Script_LLM_NPC_eventOnEmotionStateChanged_Parms Parms;
	Parms.OldState=OldState;
	Parms.NewState=NewState;
	OnEmotionStateChanged.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnEmotionStateChanged **************************************************

// ********** Begin Class UEmotionStateMachine Function FindBestTransition *************************
struct Z_Construct_UFunction_UEmotionStateMachine_FindBestTransition_Statics
{
	struct EmotionStateMachine_eventFindBestTransition_Parms
	{
		FEmotionSignal Signal;
		EEmotionType ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Emotion|StateMachine" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Find the best transition target for a given signal using A*-like cost search.\n\x09 * @param Signal The signal to evaluate.\n\x09 * @return The best target emotion type, or current emotion if no valid transition found.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionStateMachine.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Find the best transition target for a given signal using A*-like cost search.\n@param Signal The signal to evaluate.\n@return The best target emotion type, or current emotion if no valid transition found." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Signal_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function FindBestTransition constinit property declarations ********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Signal;
	static const UECodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function FindBestTransition constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function FindBestTransition Property Definitions *******************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UEmotionStateMachine_FindBestTransition_Statics::NewProp_Signal = { "Signal", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EmotionStateMachine_eventFindBestTransition_Parms, Signal), Z_Construct_UScriptStruct_FEmotionSignal, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Signal_MetaData), NewProp_Signal_MetaData) }; // 2625116487
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UEmotionStateMachine_FindBestTransition_Statics::NewProp_ReturnValue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UEmotionStateMachine_FindBestTransition_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EmotionStateMachine_eventFindBestTransition_Parms, ReturnValue), Z_Construct_UEnum_LLM_NPC_EEmotionType, METADATA_PARAMS(0, nullptr) }; // 1184287893
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEmotionStateMachine_FindBestTransition_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEmotionStateMachine_FindBestTransition_Statics::NewProp_Signal,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEmotionStateMachine_FindBestTransition_Statics::NewProp_ReturnValue_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEmotionStateMachine_FindBestTransition_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionStateMachine_FindBestTransition_Statics::PropPointers) < 2048);
// ********** End Function FindBestTransition Property Definitions *********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEmotionStateMachine_FindBestTransition_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UEmotionStateMachine, nullptr, "FindBestTransition", 	Z_Construct_UFunction_UEmotionStateMachine_FindBestTransition_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionStateMachine_FindBestTransition_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UEmotionStateMachine_FindBestTransition_Statics::EmotionStateMachine_eventFindBestTransition_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionStateMachine_FindBestTransition_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEmotionStateMachine_FindBestTransition_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UEmotionStateMachine_FindBestTransition_Statics::EmotionStateMachine_eventFindBestTransition_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UEmotionStateMachine_FindBestTransition()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEmotionStateMachine_FindBestTransition_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UEmotionStateMachine::execFindBestTransition)
{
	P_GET_STRUCT_REF(FEmotionSignal,Z_Param_Out_Signal);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(EEmotionType*)Z_Param__Result=P_THIS->FindBestTransition(Z_Param_Out_Signal);
	P_NATIVE_END;
}
// ********** End Class UEmotionStateMachine Function FindBestTransition ***************************

// ********** Begin Class UEmotionStateMachine Function GetCurrentState ****************************
struct Z_Construct_UFunction_UEmotionStateMachine_GetCurrentState_Statics
{
	struct EmotionStateMachine_eventGetCurrentState_Parms
	{
		FEmotionState ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Emotion|StateMachine" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get the current emotional state. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionStateMachine.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get the current emotional state." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetCurrentState constinit property declarations ***********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetCurrentState constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetCurrentState Property Definitions **********************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UEmotionStateMachine_GetCurrentState_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EmotionStateMachine_eventGetCurrentState_Parms, ReturnValue), Z_Construct_UScriptStruct_FEmotionState, METADATA_PARAMS(0, nullptr) }; // 1004811449
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEmotionStateMachine_GetCurrentState_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEmotionStateMachine_GetCurrentState_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionStateMachine_GetCurrentState_Statics::PropPointers) < 2048);
// ********** End Function GetCurrentState Property Definitions ************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEmotionStateMachine_GetCurrentState_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UEmotionStateMachine, nullptr, "GetCurrentState", 	Z_Construct_UFunction_UEmotionStateMachine_GetCurrentState_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionStateMachine_GetCurrentState_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UEmotionStateMachine_GetCurrentState_Statics::EmotionStateMachine_eventGetCurrentState_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionStateMachine_GetCurrentState_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEmotionStateMachine_GetCurrentState_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UEmotionStateMachine_GetCurrentState_Statics::EmotionStateMachine_eventGetCurrentState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UEmotionStateMachine_GetCurrentState()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEmotionStateMachine_GetCurrentState_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UEmotionStateMachine::execGetCurrentState)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FEmotionState*)Z_Param__Result=P_THIS->GetCurrentState();
	P_NATIVE_END;
}
// ********** End Class UEmotionStateMachine Function GetCurrentState ******************************

// ********** Begin Class UEmotionStateMachine Function ProcessSignal ******************************
struct Z_Construct_UFunction_UEmotionStateMachine_ProcessSignal_Statics
{
	struct EmotionStateMachine_eventProcessSignal_Parms
	{
		FEmotionSignal Signal;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Emotion|StateMachine" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Process an incoming emotion signal.\n\x09 * Evaluates all transition rules and fires the lowest-cost valid transition.\n\x09 * @param Signal The emotion signal to process.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionStateMachine.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Process an incoming emotion signal.\nEvaluates all transition rules and fires the lowest-cost valid transition.\n@param Signal The emotion signal to process." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Signal_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ProcessSignal constinit property declarations *************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Signal;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ProcessSignal constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ProcessSignal Property Definitions ************************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UEmotionStateMachine_ProcessSignal_Statics::NewProp_Signal = { "Signal", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EmotionStateMachine_eventProcessSignal_Parms, Signal), Z_Construct_UScriptStruct_FEmotionSignal, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Signal_MetaData), NewProp_Signal_MetaData) }; // 2625116487
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEmotionStateMachine_ProcessSignal_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEmotionStateMachine_ProcessSignal_Statics::NewProp_Signal,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionStateMachine_ProcessSignal_Statics::PropPointers) < 2048);
// ********** End Function ProcessSignal Property Definitions **************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEmotionStateMachine_ProcessSignal_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UEmotionStateMachine, nullptr, "ProcessSignal", 	Z_Construct_UFunction_UEmotionStateMachine_ProcessSignal_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionStateMachine_ProcessSignal_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UEmotionStateMachine_ProcessSignal_Statics::EmotionStateMachine_eventProcessSignal_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionStateMachine_ProcessSignal_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEmotionStateMachine_ProcessSignal_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UEmotionStateMachine_ProcessSignal_Statics::EmotionStateMachine_eventProcessSignal_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UEmotionStateMachine_ProcessSignal()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEmotionStateMachine_ProcessSignal_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UEmotionStateMachine::execProcessSignal)
{
	P_GET_STRUCT_REF(FEmotionSignal,Z_Param_Out_Signal);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ProcessSignal(Z_Param_Out_Signal);
	P_NATIVE_END;
}
// ********** End Class UEmotionStateMachine Function ProcessSignal ********************************

// ********** Begin Class UEmotionStateMachine Function Tick ***************************************
struct Z_Construct_UFunction_UEmotionStateMachine_Tick_Statics
{
	struct EmotionStateMachine_eventTick_Parms
	{
		float DeltaTime;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Emotion|StateMachine" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Tick the state machine: handles intensity decay and PAD interpolation.\n\x09 * Called each frame by the owning EmotionComponent.\n\x09 * @param DeltaTime Frame delta time in seconds.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionStateMachine.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Tick the state machine: handles intensity decay and PAD interpolation.\nCalled each frame by the owning EmotionComponent.\n@param DeltaTime Frame delta time in seconds." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function Tick constinit property declarations **********************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DeltaTime;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function Tick constinit property declarations ************************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function Tick Property Definitions *********************************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UEmotionStateMachine_Tick_Statics::NewProp_DeltaTime = { "DeltaTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EmotionStateMachine_eventTick_Parms, DeltaTime), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEmotionStateMachine_Tick_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEmotionStateMachine_Tick_Statics::NewProp_DeltaTime,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionStateMachine_Tick_Statics::PropPointers) < 2048);
// ********** End Function Tick Property Definitions ***********************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEmotionStateMachine_Tick_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UEmotionStateMachine, nullptr, "Tick", 	Z_Construct_UFunction_UEmotionStateMachine_Tick_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionStateMachine_Tick_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UEmotionStateMachine_Tick_Statics::EmotionStateMachine_eventTick_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionStateMachine_Tick_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEmotionStateMachine_Tick_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UEmotionStateMachine_Tick_Statics::EmotionStateMachine_eventTick_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UEmotionStateMachine_Tick()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEmotionStateMachine_Tick_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UEmotionStateMachine::execTick)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_DeltaTime);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Tick(Z_Param_DeltaTime);
	P_NATIVE_END;
}
// ********** End Class UEmotionStateMachine Function Tick *****************************************

// ********** Begin Class UEmotionStateMachine *****************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UEmotionStateMachine;
UClass* UEmotionStateMachine::GetPrivateStaticClass()
{
	using TClass = UEmotionStateMachine;
	if (!Z_Registration_Info_UClass_UEmotionStateMachine.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("EmotionStateMachine"),
			Z_Registration_Info_UClass_UEmotionStateMachine.InnerSingleton,
			StaticRegisterNativesUEmotionStateMachine,
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
	return Z_Registration_Info_UClass_UEmotionStateMachine.InnerSingleton;
}
UClass* Z_Construct_UClass_UEmotionStateMachine_NoRegister()
{
	return UEmotionStateMachine::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UEmotionStateMachine_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Graph-based emotion finite state machine.\n * Nodes = emotion states (Plutchik types), edges = transition rules with A*-weighted costs.\n *\n * Mirrors the F.E.A.R. GOAP architecture: a minimal node set with goal-driven transitions.\n * Instead of pre-authored animation trees, the planner searches for the lowest-cost\n * emotional transition given the NPC's archetype cost profile.\n *\n * Intensity decays toward 0 at a configurable rate. When intensity drops below\n * the neutral threshold (default 0.1), the machine transitions to Neutral.\n * The PAD vector interpolates smoothly; the discrete emotion label is updated\n * to the nearest canonical PAD point.\n */" },
#endif
		{ "IncludePath", "Emotion/EmotionStateMachine.h" },
		{ "ModuleRelativePath", "Emotion/EmotionStateMachine.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Graph-based emotion finite state machine.\nNodes = emotion states (Plutchik types), edges = transition rules with A*-weighted costs.\n\nMirrors the F.E.A.R. GOAP architecture: a minimal node set with goal-driven transitions.\nInstead of pre-authored animation trees, the planner searches for the lowest-cost\nemotional transition given the NPC's archetype cost profile.\n\nIntensity decays toward 0 at a configurable rate. When intensity drops below\nthe neutral threshold (default 0.1), the machine transitions to Neutral.\nThe PAD vector interpolates smoothly; the discrete emotion label is updated\nto the nearest canonical PAD point." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnEmotionStateChanged_MetaData[] = {
		{ "Category", "Emotion|StateMachine" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Fired when the emotion state changes. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionStateMachine.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Fired when the emotion state changes." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TransitionRules_MetaData[] = {
		{ "Category", "Emotion|StateMachine" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** All transition rules in this emotion graph. */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Emotion/EmotionStateMachine.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "All transition rules in this emotion graph." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EmotionTransitionCosts_MetaData[] = {
		{ "Category", "Emotion|StateMachine" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Per-emotion transition cost multipliers (from NPC archetype). */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionStateMachine.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Per-emotion transition cost multipliers (from NPC archetype)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DecayRate_MetaData[] = {
		{ "Category", "Emotion|StateMachine" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Rate at which intensity decays per second. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionStateMachine.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Rate at which intensity decays per second." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NeutralThreshold_MetaData[] = {
		{ "Category", "Emotion|StateMachine" },
		{ "ClampMax", "0.5" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Intensity threshold below which the NPC transitions to Neutral. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionStateMachine.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Intensity threshold below which the NPC transitions to Neutral." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PADInterpSpeed_MetaData[] = {
		{ "Category", "Emotion|StateMachine" },
		{ "ClampMax", "10.0" },
		{ "ClampMin", "0.1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Speed of PAD vector interpolation (alpha per second). */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionStateMachine.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Speed of PAD vector interpolation (alpha per second)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentState_MetaData[] = {
		{ "Category", "Emotion|StateMachine" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The NPC's current emotional state. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionStateMachine.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The NPC's current emotional state." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LastTransitionTime_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** World time of the last emotion transition (for cooldown tracking). */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionStateMachine.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "World time of the last emotion transition (for cooldown tracking)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetPAD_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Target PAD vector we are interpolating toward. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionStateMachine.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Target PAD vector we are interpolating toward." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UEmotionStateMachine constinit property declarations *********************
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnEmotionStateChanged;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TransitionRules_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_TransitionRules;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_EmotionTransitionCosts_ValueProp;
	static const UECodeGen_Private::FBytePropertyParams NewProp_EmotionTransitionCosts_Key_KeyProp_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_EmotionTransitionCosts_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_EmotionTransitionCosts;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DecayRate;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NeutralThreshold;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PADInterpSpeed;
	static const UECodeGen_Private::FStructPropertyParams NewProp_CurrentState;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LastTransitionTime;
	static const UECodeGen_Private::FStructPropertyParams NewProp_TargetPAD;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UEmotionStateMachine constinit property declarations ***********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("FindBestTransition"), .Pointer = &UEmotionStateMachine::execFindBestTransition },
		{ .NameUTF8 = UTF8TEXT("GetCurrentState"), .Pointer = &UEmotionStateMachine::execGetCurrentState },
		{ .NameUTF8 = UTF8TEXT("ProcessSignal"), .Pointer = &UEmotionStateMachine::execProcessSignal },
		{ .NameUTF8 = UTF8TEXT("Tick"), .Pointer = &UEmotionStateMachine::execTick },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UEmotionStateMachine_FindBestTransition, "FindBestTransition" }, // 3767724826
		{ &Z_Construct_UFunction_UEmotionStateMachine_GetCurrentState, "GetCurrentState" }, // 2065160840
		{ &Z_Construct_UFunction_UEmotionStateMachine_ProcessSignal, "ProcessSignal" }, // 4152369374
		{ &Z_Construct_UFunction_UEmotionStateMachine_Tick, "Tick" }, // 268425909
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UEmotionStateMachine>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UEmotionStateMachine_Statics

// ********** Begin Class UEmotionStateMachine Property Definitions ********************************
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UEmotionStateMachine_Statics::NewProp_OnEmotionStateChanged = { "OnEmotionStateChanged", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEmotionStateMachine, OnEmotionStateChanged), Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionStateChanged__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnEmotionStateChanged_MetaData), NewProp_OnEmotionStateChanged_MetaData) }; // 1224031460
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UEmotionStateMachine_Statics::NewProp_TransitionRules_Inner = { "TransitionRules", nullptr, (EPropertyFlags)0x0104000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UEmotionTransitionRule_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UEmotionStateMachine_Statics::NewProp_TransitionRules = { "TransitionRules", nullptr, (EPropertyFlags)0x011400800000001c, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEmotionStateMachine, TransitionRules), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TransitionRules_MetaData), NewProp_TransitionRules_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UEmotionStateMachine_Statics::NewProp_EmotionTransitionCosts_ValueProp = { "EmotionTransitionCosts", nullptr, (EPropertyFlags)0x0000000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UEmotionStateMachine_Statics::NewProp_EmotionTransitionCosts_Key_KeyProp_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UEmotionStateMachine_Statics::NewProp_EmotionTransitionCosts_Key_KeyProp = { "EmotionTransitionCosts_Key", nullptr, (EPropertyFlags)0x0000000000000001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UEnum_LLM_NPC_EEmotionType, METADATA_PARAMS(0, nullptr) }; // 1184287893
const UECodeGen_Private::FMapPropertyParams Z_Construct_UClass_UEmotionStateMachine_Statics::NewProp_EmotionTransitionCosts = { "EmotionTransitionCosts", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEmotionStateMachine, EmotionTransitionCosts), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EmotionTransitionCosts_MetaData), NewProp_EmotionTransitionCosts_MetaData) }; // 1184287893
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UEmotionStateMachine_Statics::NewProp_DecayRate = { "DecayRate", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEmotionStateMachine, DecayRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DecayRate_MetaData), NewProp_DecayRate_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UEmotionStateMachine_Statics::NewProp_NeutralThreshold = { "NeutralThreshold", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEmotionStateMachine, NeutralThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NeutralThreshold_MetaData), NewProp_NeutralThreshold_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UEmotionStateMachine_Statics::NewProp_PADInterpSpeed = { "PADInterpSpeed", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEmotionStateMachine, PADInterpSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PADInterpSpeed_MetaData), NewProp_PADInterpSpeed_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UEmotionStateMachine_Statics::NewProp_CurrentState = { "CurrentState", nullptr, (EPropertyFlags)0x0020080000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEmotionStateMachine, CurrentState), Z_Construct_UScriptStruct_FEmotionState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentState_MetaData), NewProp_CurrentState_MetaData) }; // 1004811449
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UEmotionStateMachine_Statics::NewProp_LastTransitionTime = { "LastTransitionTime", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEmotionStateMachine, LastTransitionTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LastTransitionTime_MetaData), NewProp_LastTransitionTime_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UEmotionStateMachine_Statics::NewProp_TargetPAD = { "TargetPAD", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEmotionStateMachine, TargetPAD), Z_Construct_UScriptStruct_FPADVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetPAD_MetaData), NewProp_TargetPAD_MetaData) }; // 3806868039
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UEmotionStateMachine_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionStateMachine_Statics::NewProp_OnEmotionStateChanged,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionStateMachine_Statics::NewProp_TransitionRules_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionStateMachine_Statics::NewProp_TransitionRules,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionStateMachine_Statics::NewProp_EmotionTransitionCosts_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionStateMachine_Statics::NewProp_EmotionTransitionCosts_Key_KeyProp_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionStateMachine_Statics::NewProp_EmotionTransitionCosts_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionStateMachine_Statics::NewProp_EmotionTransitionCosts,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionStateMachine_Statics::NewProp_DecayRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionStateMachine_Statics::NewProp_NeutralThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionStateMachine_Statics::NewProp_PADInterpSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionStateMachine_Statics::NewProp_CurrentState,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionStateMachine_Statics::NewProp_LastTransitionTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionStateMachine_Statics::NewProp_TargetPAD,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UEmotionStateMachine_Statics::PropPointers) < 2048);
// ********** End Class UEmotionStateMachine Property Definitions **********************************
UObject* (*const Z_Construct_UClass_UEmotionStateMachine_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UEmotionStateMachine_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UEmotionStateMachine_Statics::ClassParams = {
	&UEmotionStateMachine::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UEmotionStateMachine_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UEmotionStateMachine_Statics::PropPointers),
	0,
	0x009000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UEmotionStateMachine_Statics::Class_MetaDataParams), Z_Construct_UClass_UEmotionStateMachine_Statics::Class_MetaDataParams)
};
void UEmotionStateMachine::StaticRegisterNativesUEmotionStateMachine()
{
	UClass* Class = UEmotionStateMachine::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UEmotionStateMachine_Statics::Funcs));
}
UClass* Z_Construct_UClass_UEmotionStateMachine()
{
	if (!Z_Registration_Info_UClass_UEmotionStateMachine.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UEmotionStateMachine.OuterSingleton, Z_Construct_UClass_UEmotionStateMachine_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UEmotionStateMachine.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UEmotionStateMachine);
UEmotionStateMachine::~UEmotionStateMachine() {}
// ********** End Class UEmotionStateMachine *******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionStateMachine_h__Script_LLM_NPC_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UEmotionStateMachine, UEmotionStateMachine::StaticClass, TEXT("UEmotionStateMachine"), &Z_Registration_Info_UClass_UEmotionStateMachine, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UEmotionStateMachine), 3000370041U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionStateMachine_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionStateMachine_h__Script_LLM_NPC_3898415655{
	TEXT("/Script/LLM_NPC"),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionStateMachine_h__Script_LLM_NPC_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionStateMachine_h__Script_LLM_NPC_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
