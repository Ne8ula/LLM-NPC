// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Emotion/EmotionComponent.h"
#include "LLM_NPC/Core/NPCTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeEmotionComponent() {}

// ********** Begin Cross Module References ********************************************************
LLM_NPC_API UClass* Z_Construct_UClass_UEmotionComponent();
LLM_NPC_API UClass* Z_Construct_UClass_UEmotionComponent_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UEmotionStateMachine_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UNPCSubsystemComponent();
LLM_NPC_API UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionChanged__DelegateSignature();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FEmotionSignal();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FEmotionState();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FOnEmotionChanged *****************************************************
struct Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionChanged__DelegateSignature_Statics
{
	struct _Script_LLM_NPC_eventOnEmotionChanged_Parms
	{
		FEmotionState OldState;
		FEmotionState NewState;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Delegate fired when the EmotionComponent detects a state change. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Delegate fired when the EmotionComponent detects a state change." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnEmotionChanged constinit property declarations *********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_OldState;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NewState;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FOnEmotionChanged constinit property declarations ***********************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FOnEmotionChanged Property Definitions ********************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionChanged__DelegateSignature_Statics::NewProp_OldState = { "OldState", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_LLM_NPC_eventOnEmotionChanged_Parms, OldState), Z_Construct_UScriptStruct_FEmotionState, METADATA_PARAMS(0, nullptr) }; // 1004811449
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionChanged__DelegateSignature_Statics::NewProp_NewState = { "NewState", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_LLM_NPC_eventOnEmotionChanged_Parms, NewState), Z_Construct_UScriptStruct_FEmotionState, METADATA_PARAMS(0, nullptr) }; // 1004811449
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionChanged__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionChanged__DelegateSignature_Statics::NewProp_OldState,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionChanged__DelegateSignature_Statics::NewProp_NewState,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionChanged__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FOnEmotionChanged Property Definitions **********************************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionChanged__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_LLM_NPC, nullptr, "OnEmotionChanged__DelegateSignature", 	Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionChanged__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionChanged__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionChanged__DelegateSignature_Statics::_Script_LLM_NPC_eventOnEmotionChanged_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionChanged__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionChanged__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionChanged__DelegateSignature_Statics::_Script_LLM_NPC_eventOnEmotionChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionChanged__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionChanged__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnEmotionChanged_DelegateWrapper(const FMulticastScriptDelegate& OnEmotionChanged, FEmotionState OldState, FEmotionState NewState)
{
	struct _Script_LLM_NPC_eventOnEmotionChanged_Parms
	{
		FEmotionState OldState;
		FEmotionState NewState;
	};
	_Script_LLM_NPC_eventOnEmotionChanged_Parms Parms;
	Parms.OldState=OldState;
	Parms.NewState=NewState;
	OnEmotionChanged.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnEmotionChanged *******************************************************

// ********** Begin Class UEmotionComponent Function GetCurrentEmotionState ************************
struct Z_Construct_UFunction_UEmotionComponent_GetCurrentEmotionState_Statics
{
	struct EmotionComponent_eventGetCurrentEmotionState_Parms
	{
		FEmotionState ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Emotion" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Get the NPC's current emotional state.\n\x09 * @return The current FEmotionState.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get the NPC's current emotional state.\n@return The current FEmotionState." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetCurrentEmotionState constinit property declarations ****************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetCurrentEmotionState constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetCurrentEmotionState Property Definitions ***************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UEmotionComponent_GetCurrentEmotionState_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EmotionComponent_eventGetCurrentEmotionState_Parms, ReturnValue), Z_Construct_UScriptStruct_FEmotionState, METADATA_PARAMS(0, nullptr) }; // 1004811449
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEmotionComponent_GetCurrentEmotionState_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEmotionComponent_GetCurrentEmotionState_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionComponent_GetCurrentEmotionState_Statics::PropPointers) < 2048);
// ********** End Function GetCurrentEmotionState Property Definitions *****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEmotionComponent_GetCurrentEmotionState_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UEmotionComponent, nullptr, "GetCurrentEmotionState", 	Z_Construct_UFunction_UEmotionComponent_GetCurrentEmotionState_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionComponent_GetCurrentEmotionState_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UEmotionComponent_GetCurrentEmotionState_Statics::EmotionComponent_eventGetCurrentEmotionState_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionComponent_GetCurrentEmotionState_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEmotionComponent_GetCurrentEmotionState_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UEmotionComponent_GetCurrentEmotionState_Statics::EmotionComponent_eventGetCurrentEmotionState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UEmotionComponent_GetCurrentEmotionState()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEmotionComponent_GetCurrentEmotionState_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UEmotionComponent::execGetCurrentEmotionState)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FEmotionState*)Z_Param__Result=P_THIS->GetCurrentEmotionState();
	P_NATIVE_END;
}
// ********** End Class UEmotionComponent Function GetCurrentEmotionState **************************

// ********** Begin Class UEmotionComponent Function HandleEmotionStateChanged *********************
struct Z_Construct_UFunction_UEmotionComponent_HandleEmotionStateChanged_Statics
{
	struct EmotionComponent_eventHandleEmotionStateChanged_Parms
	{
		FEmotionState OldState;
		FEmotionState NewState;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Callback bound to the state machine's OnEmotionStateChanged delegate. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Callback bound to the state machine's OnEmotionStateChanged delegate." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function HandleEmotionStateChanged constinit property declarations *************
	static const UECodeGen_Private::FStructPropertyParams NewProp_OldState;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NewState;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HandleEmotionStateChanged constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HandleEmotionStateChanged Property Definitions ************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UEmotionComponent_HandleEmotionStateChanged_Statics::NewProp_OldState = { "OldState", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EmotionComponent_eventHandleEmotionStateChanged_Parms, OldState), Z_Construct_UScriptStruct_FEmotionState, METADATA_PARAMS(0, nullptr) }; // 1004811449
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UEmotionComponent_HandleEmotionStateChanged_Statics::NewProp_NewState = { "NewState", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EmotionComponent_eventHandleEmotionStateChanged_Parms, NewState), Z_Construct_UScriptStruct_FEmotionState, METADATA_PARAMS(0, nullptr) }; // 1004811449
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEmotionComponent_HandleEmotionStateChanged_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEmotionComponent_HandleEmotionStateChanged_Statics::NewProp_OldState,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEmotionComponent_HandleEmotionStateChanged_Statics::NewProp_NewState,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionComponent_HandleEmotionStateChanged_Statics::PropPointers) < 2048);
// ********** End Function HandleEmotionStateChanged Property Definitions **************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEmotionComponent_HandleEmotionStateChanged_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UEmotionComponent, nullptr, "HandleEmotionStateChanged", 	Z_Construct_UFunction_UEmotionComponent_HandleEmotionStateChanged_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionComponent_HandleEmotionStateChanged_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UEmotionComponent_HandleEmotionStateChanged_Statics::EmotionComponent_eventHandleEmotionStateChanged_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionComponent_HandleEmotionStateChanged_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEmotionComponent_HandleEmotionStateChanged_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UEmotionComponent_HandleEmotionStateChanged_Statics::EmotionComponent_eventHandleEmotionStateChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UEmotionComponent_HandleEmotionStateChanged()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEmotionComponent_HandleEmotionStateChanged_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UEmotionComponent::execHandleEmotionStateChanged)
{
	P_GET_STRUCT(FEmotionState,Z_Param_OldState);
	P_GET_STRUCT(FEmotionState,Z_Param_NewState);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleEmotionStateChanged(Z_Param_OldState,Z_Param_NewState);
	P_NATIVE_END;
}
// ********** End Class UEmotionComponent Function HandleEmotionStateChanged ***********************

// ********** Begin Class UEmotionComponent Function ProcessSignal *********************************
struct Z_Construct_UFunction_UEmotionComponent_ProcessSignal_Statics
{
	struct EmotionComponent_eventProcessSignal_Parms
	{
		FEmotionSignal Signal;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Emotion" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Process an incoming emotion signal by forwarding it to the state machine.\n\x09 * @param Signal The emotion signal to process.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Process an incoming emotion signal by forwarding it to the state machine.\n@param Signal The emotion signal to process." },
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
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UEmotionComponent_ProcessSignal_Statics::NewProp_Signal = { "Signal", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EmotionComponent_eventProcessSignal_Parms, Signal), Z_Construct_UScriptStruct_FEmotionSignal, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Signal_MetaData), NewProp_Signal_MetaData) }; // 2625116487
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEmotionComponent_ProcessSignal_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEmotionComponent_ProcessSignal_Statics::NewProp_Signal,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionComponent_ProcessSignal_Statics::PropPointers) < 2048);
// ********** End Function ProcessSignal Property Definitions **************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEmotionComponent_ProcessSignal_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UEmotionComponent, nullptr, "ProcessSignal", 	Z_Construct_UFunction_UEmotionComponent_ProcessSignal_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionComponent_ProcessSignal_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UEmotionComponent_ProcessSignal_Statics::EmotionComponent_eventProcessSignal_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionComponent_ProcessSignal_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEmotionComponent_ProcessSignal_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UEmotionComponent_ProcessSignal_Statics::EmotionComponent_eventProcessSignal_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UEmotionComponent_ProcessSignal()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEmotionComponent_ProcessSignal_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UEmotionComponent::execProcessSignal)
{
	P_GET_STRUCT_REF(FEmotionSignal,Z_Param_Out_Signal);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ProcessSignal(Z_Param_Out_Signal);
	P_NATIVE_END;
}
// ********** End Class UEmotionComponent Function ProcessSignal ***********************************

// ********** Begin Class UEmotionComponent ********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UEmotionComponent;
UClass* UEmotionComponent::GetPrivateStaticClass()
{
	using TClass = UEmotionComponent;
	if (!Z_Registration_Info_UClass_UEmotionComponent.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("EmotionComponent"),
			Z_Registration_Info_UClass_UEmotionComponent.InnerSingleton,
			StaticRegisterNativesUEmotionComponent,
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
	return Z_Registration_Info_UClass_UEmotionComponent.InnerSingleton;
}
UClass* Z_Construct_UClass_UEmotionComponent_NoRegister()
{
	return UEmotionComponent::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UEmotionComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "LLMNPC" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * NPC subsystem component that owns and drives the Emotion Engine.\n *\n * Loads an EmotionGraphDataAsset from the NPC's config, instantiates the\n * EmotionStateMachine, and ticks it each frame for decay and PAD interpolation.\n * Other subsystems (Dialogue, Vision, Gesture) send FEmotionSignals via\n * ProcessSignal() to influence the NPC's emotional state.\n *\n * SubsystemName = \"EmotionEngine\"\n */" },
#endif
		{ "IncludePath", "Emotion/EmotionComponent.h" },
		{ "ModuleRelativePath", "Emotion/EmotionComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "NPC subsystem component that owns and drives the Emotion Engine.\n\nLoads an EmotionGraphDataAsset from the NPC's config, instantiates the\nEmotionStateMachine, and ticks it each frame for decay and PAD interpolation.\nOther subsystems (Dialogue, Vision, Gesture) send FEmotionSignals via\nProcessSignal() to influence the NPC's emotional state.\n\nSubsystemName = \"EmotionEngine\"" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnEmotionChanged_MetaData[] = {
		{ "Category", "NPC|Emotion" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Delegate broadcast when the emotion state changes. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Delegate broadcast when the emotion state changes." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StateMachine_MetaData[] = {
		{ "Category", "NPC|Emotion" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The active state machine (created at initialization). */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The active state machine (created at initialization)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UEmotionComponent constinit property declarations ************************
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnEmotionChanged;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StateMachine;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UEmotionComponent constinit property declarations **************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("GetCurrentEmotionState"), .Pointer = &UEmotionComponent::execGetCurrentEmotionState },
		{ .NameUTF8 = UTF8TEXT("HandleEmotionStateChanged"), .Pointer = &UEmotionComponent::execHandleEmotionStateChanged },
		{ .NameUTF8 = UTF8TEXT("ProcessSignal"), .Pointer = &UEmotionComponent::execProcessSignal },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UEmotionComponent_GetCurrentEmotionState, "GetCurrentEmotionState" }, // 240098207
		{ &Z_Construct_UFunction_UEmotionComponent_HandleEmotionStateChanged, "HandleEmotionStateChanged" }, // 1384234915
		{ &Z_Construct_UFunction_UEmotionComponent_ProcessSignal, "ProcessSignal" }, // 2431054087
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UEmotionComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UEmotionComponent_Statics

// ********** Begin Class UEmotionComponent Property Definitions ***********************************
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UEmotionComponent_Statics::NewProp_OnEmotionChanged = { "OnEmotionChanged", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEmotionComponent, OnEmotionChanged), Z_Construct_UDelegateFunction_LLM_NPC_OnEmotionChanged__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnEmotionChanged_MetaData), NewProp_OnEmotionChanged_MetaData) }; // 3385913400
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UEmotionComponent_Statics::NewProp_StateMachine = { "StateMachine", nullptr, (EPropertyFlags)0x0114000000000014, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEmotionComponent, StateMachine), Z_Construct_UClass_UEmotionStateMachine_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StateMachine_MetaData), NewProp_StateMachine_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UEmotionComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionComponent_Statics::NewProp_OnEmotionChanged,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionComponent_Statics::NewProp_StateMachine,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UEmotionComponent_Statics::PropPointers) < 2048);
// ********** End Class UEmotionComponent Property Definitions *************************************
UObject* (*const Z_Construct_UClass_UEmotionComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UNPCSubsystemComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UEmotionComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UEmotionComponent_Statics::ClassParams = {
	&UEmotionComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UEmotionComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UEmotionComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UEmotionComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UEmotionComponent_Statics::Class_MetaDataParams)
};
void UEmotionComponent::StaticRegisterNativesUEmotionComponent()
{
	UClass* Class = UEmotionComponent::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UEmotionComponent_Statics::Funcs));
}
UClass* Z_Construct_UClass_UEmotionComponent()
{
	if (!Z_Registration_Info_UClass_UEmotionComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UEmotionComponent.OuterSingleton, Z_Construct_UClass_UEmotionComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UEmotionComponent.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UEmotionComponent);
UEmotionComponent::~UEmotionComponent() {}
// ********** End Class UEmotionComponent **********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionComponent_h__Script_LLM_NPC_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UEmotionComponent, UEmotionComponent::StaticClass, TEXT("UEmotionComponent"), &Z_Registration_Info_UClass_UEmotionComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UEmotionComponent), 2256491480U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionComponent_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionComponent_h__Script_LLM_NPC_1177467080{
	TEXT("/Script/LLM_NPC"),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionComponent_h__Script_LLM_NPC_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionComponent_h__Script_LLM_NPC_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
