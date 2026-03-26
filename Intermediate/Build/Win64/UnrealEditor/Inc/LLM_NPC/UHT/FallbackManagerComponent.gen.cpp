// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Fallback/FallbackManagerComponent.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeFallbackManagerComponent() {}

// ********** Begin Cross Module References ********************************************************
LLM_NPC_API UClass* Z_Construct_UClass_UFallbackManagerComponent();
LLM_NPC_API UClass* Z_Construct_UClass_UFallbackManagerComponent_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UNPCSubsystemComponent();
LLM_NPC_API UEnum* Z_Construct_UEnum_LLM_NPC_EDegradationLevel();
LLM_NPC_API UEnum* Z_Construct_UEnum_LLM_NPC_EDialogueInputMode();
LLM_NPC_API UEnum* Z_Construct_UEnum_LLM_NPC_EManipulationInputMode();
LLM_NPC_API UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnInputModeChanged__DelegateSignature();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FOnInputModeChanged ***************************************************
struct Z_Construct_UDelegateFunction_LLM_NPC_OnInputModeChanged__DelegateSignature_Statics
{
	struct _Script_LLM_NPC_eventOnInputModeChanged_Parms
	{
		FString ModeName;
		bool bAvailable;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Fallback/FallbackManagerComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnInputModeChanged constinit property declarations *******************
	static const UECodeGen_Private::FStrPropertyParams NewProp_ModeName;
	static void NewProp_bAvailable_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAvailable;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FOnInputModeChanged constinit property declarations *********************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FOnInputModeChanged Property Definitions ******************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UDelegateFunction_LLM_NPC_OnInputModeChanged__DelegateSignature_Statics::NewProp_ModeName = { "ModeName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_LLM_NPC_eventOnInputModeChanged_Parms, ModeName), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UDelegateFunction_LLM_NPC_OnInputModeChanged__DelegateSignature_Statics::NewProp_bAvailable_SetBit(void* Obj)
{
	((_Script_LLM_NPC_eventOnInputModeChanged_Parms*)Obj)->bAvailable = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UDelegateFunction_LLM_NPC_OnInputModeChanged__DelegateSignature_Statics::NewProp_bAvailable = { "bAvailable", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(_Script_LLM_NPC_eventOnInputModeChanged_Parms), &Z_Construct_UDelegateFunction_LLM_NPC_OnInputModeChanged__DelegateSignature_Statics::NewProp_bAvailable_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_LLM_NPC_OnInputModeChanged__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LLM_NPC_OnInputModeChanged__DelegateSignature_Statics::NewProp_ModeName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LLM_NPC_OnInputModeChanged__DelegateSignature_Statics::NewProp_bAvailable,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnInputModeChanged__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FOnInputModeChanged Property Definitions ********************************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_LLM_NPC_OnInputModeChanged__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_LLM_NPC, nullptr, "OnInputModeChanged__DelegateSignature", 	Z_Construct_UDelegateFunction_LLM_NPC_OnInputModeChanged__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnInputModeChanged__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_LLM_NPC_OnInputModeChanged__DelegateSignature_Statics::_Script_LLM_NPC_eventOnInputModeChanged_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnInputModeChanged__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_LLM_NPC_OnInputModeChanged__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_LLM_NPC_OnInputModeChanged__DelegateSignature_Statics::_Script_LLM_NPC_eventOnInputModeChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnInputModeChanged__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_LLM_NPC_OnInputModeChanged__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnInputModeChanged_DelegateWrapper(const FMulticastScriptDelegate& OnInputModeChanged, const FString& ModeName, bool bAvailable)
{
	struct _Script_LLM_NPC_eventOnInputModeChanged_Parms
	{
		FString ModeName;
		bool bAvailable;
	};
	_Script_LLM_NPC_eventOnInputModeChanged_Parms Parms;
	Parms.ModeName=ModeName;
	Parms.bAvailable=bAvailable ? true : false;
	OnInputModeChanged.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnInputModeChanged *****************************************************

// ********** Begin Enum EDegradationLevel *********************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EDegradationLevel;
static UEnum* EDegradationLevel_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EDegradationLevel.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EDegradationLevel.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_LLM_NPC_EDegradationLevel, (UObject*)Z_Construct_UPackage__Script_LLM_NPC(), TEXT("EDegradationLevel"));
	}
	return Z_Registration_Info_UEnum_EDegradationLevel.OuterSingleton;
}
template<> LLM_NPC_NON_ATTRIBUTED_API UEnum* StaticEnum<EDegradationLevel>()
{
	return EDegradationLevel_StaticEnum();
}
struct Z_Construct_UEnum_LLM_NPC_EDegradationLevel_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Degradation priority levels, from most capable to least.\n */" },
#endif
		{ "Full.DisplayName", "Full (Camera + Mic)" },
		{ "Full.Name", "EDegradationLevel::Full" },
		{ "Minimal.DisplayName", "Minimal (Text + Keyboard)" },
		{ "Minimal.Name", "EDegradationLevel::Minimal" },
		{ "ModuleRelativePath", "Fallback/FallbackManagerComponent.h" },
		{ "NoCamera.DisplayName", "No Camera (Mic only)" },
		{ "NoCamera.Name", "EDegradationLevel::NoCamera" },
		{ "NoMic.DisplayName", "No Mic (Camera only)" },
		{ "NoMic.Name", "EDegradationLevel::NoMic" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Degradation priority levels, from most capable to least." },
#endif
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EDegradationLevel::Full", (int64)EDegradationLevel::Full },
		{ "EDegradationLevel::NoCamera", (int64)EDegradationLevel::NoCamera },
		{ "EDegradationLevel::NoMic", (int64)EDegradationLevel::NoMic },
		{ "EDegradationLevel::Minimal", (int64)EDegradationLevel::Minimal },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_LLM_NPC_EDegradationLevel_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_LLM_NPC_EDegradationLevel_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_LLM_NPC,
	nullptr,
	"EDegradationLevel",
	"EDegradationLevel",
	Z_Construct_UEnum_LLM_NPC_EDegradationLevel_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_LLM_NPC_EDegradationLevel_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_LLM_NPC_EDegradationLevel_Statics::Enum_MetaDataParams), Z_Construct_UEnum_LLM_NPC_EDegradationLevel_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_LLM_NPC_EDegradationLevel()
{
	if (!Z_Registration_Info_UEnum_EDegradationLevel.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EDegradationLevel.InnerSingleton, Z_Construct_UEnum_LLM_NPC_EDegradationLevel_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EDegradationLevel.InnerSingleton;
}
// ********** End Enum EDegradationLevel ***********************************************************

// ********** Begin Class UFallbackManagerComponent Function CheckDeviceAvailability ***************
struct Z_Construct_UFunction_UFallbackManagerComponent_CheckDeviceAvailability_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Fallback" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Force a re-check of hardware availability. */" },
#endif
		{ "ModuleRelativePath", "Fallback/FallbackManagerComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Force a re-check of hardware availability." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function CheckDeviceAvailability constinit property declarations ***************
// ********** End Function CheckDeviceAvailability constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFallbackManagerComponent_CheckDeviceAvailability_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UFallbackManagerComponent, nullptr, "CheckDeviceAvailability", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UFallbackManagerComponent_CheckDeviceAvailability_Statics::Function_MetaDataParams), Z_Construct_UFunction_UFallbackManagerComponent_CheckDeviceAvailability_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UFallbackManagerComponent_CheckDeviceAvailability()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFallbackManagerComponent_CheckDeviceAvailability_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UFallbackManagerComponent::execCheckDeviceAvailability)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->CheckDeviceAvailability();
	P_NATIVE_END;
}
// ********** End Class UFallbackManagerComponent Function CheckDeviceAvailability *****************

// ********** Begin Class UFallbackManagerComponent Function GetCurrentDegradationLevel ************
struct Z_Construct_UFunction_UFallbackManagerComponent_GetCurrentDegradationLevel_Statics
{
	struct FallbackManagerComponent_eventGetCurrentDegradationLevel_Parms
	{
		EDegradationLevel ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Fallback" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get the current degradation level. */" },
#endif
		{ "ModuleRelativePath", "Fallback/FallbackManagerComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get the current degradation level." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetCurrentDegradationLevel constinit property declarations ************
	static const UECodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetCurrentDegradationLevel constinit property declarations **************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetCurrentDegradationLevel Property Definitions ***********************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UFallbackManagerComponent_GetCurrentDegradationLevel_Statics::NewProp_ReturnValue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UFallbackManagerComponent_GetCurrentDegradationLevel_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FallbackManagerComponent_eventGetCurrentDegradationLevel_Parms, ReturnValue), Z_Construct_UEnum_LLM_NPC_EDegradationLevel, METADATA_PARAMS(0, nullptr) }; // 76750131
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFallbackManagerComponent_GetCurrentDegradationLevel_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFallbackManagerComponent_GetCurrentDegradationLevel_Statics::NewProp_ReturnValue_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFallbackManagerComponent_GetCurrentDegradationLevel_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UFallbackManagerComponent_GetCurrentDegradationLevel_Statics::PropPointers) < 2048);
// ********** End Function GetCurrentDegradationLevel Property Definitions *************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFallbackManagerComponent_GetCurrentDegradationLevel_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UFallbackManagerComponent, nullptr, "GetCurrentDegradationLevel", 	Z_Construct_UFunction_UFallbackManagerComponent_GetCurrentDegradationLevel_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UFallbackManagerComponent_GetCurrentDegradationLevel_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UFallbackManagerComponent_GetCurrentDegradationLevel_Statics::FallbackManagerComponent_eventGetCurrentDegradationLevel_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UFallbackManagerComponent_GetCurrentDegradationLevel_Statics::Function_MetaDataParams), Z_Construct_UFunction_UFallbackManagerComponent_GetCurrentDegradationLevel_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UFallbackManagerComponent_GetCurrentDegradationLevel_Statics::FallbackManagerComponent_eventGetCurrentDegradationLevel_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UFallbackManagerComponent_GetCurrentDegradationLevel()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFallbackManagerComponent_GetCurrentDegradationLevel_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UFallbackManagerComponent::execGetCurrentDegradationLevel)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(EDegradationLevel*)Z_Param__Result=P_THIS->GetCurrentDegradationLevel();
	P_NATIVE_END;
}
// ********** End Class UFallbackManagerComponent Function GetCurrentDegradationLevel **************

// ********** Begin Class UFallbackManagerComponent Function SetDialogueMode ***********************
struct Z_Construct_UFunction_UFallbackManagerComponent_SetDialogueMode_Statics
{
	struct FallbackManagerComponent_eventSetDialogueMode_Parms
	{
		EDialogueInputMode NewMode;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Fallback" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Manually set the dialogue input mode (T=text, V=voice). */" },
#endif
		{ "ModuleRelativePath", "Fallback/FallbackManagerComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Manually set the dialogue input mode (T=text, V=voice)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetDialogueMode constinit property declarations ***********************
	static const UECodeGen_Private::FBytePropertyParams NewProp_NewMode_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_NewMode;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetDialogueMode constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetDialogueMode Property Definitions **********************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UFallbackManagerComponent_SetDialogueMode_Statics::NewProp_NewMode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UFallbackManagerComponent_SetDialogueMode_Statics::NewProp_NewMode = { "NewMode", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FallbackManagerComponent_eventSetDialogueMode_Parms, NewMode), Z_Construct_UEnum_LLM_NPC_EDialogueInputMode, METADATA_PARAMS(0, nullptr) }; // 4223634033
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFallbackManagerComponent_SetDialogueMode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFallbackManagerComponent_SetDialogueMode_Statics::NewProp_NewMode_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFallbackManagerComponent_SetDialogueMode_Statics::NewProp_NewMode,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UFallbackManagerComponent_SetDialogueMode_Statics::PropPointers) < 2048);
// ********** End Function SetDialogueMode Property Definitions ************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFallbackManagerComponent_SetDialogueMode_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UFallbackManagerComponent, nullptr, "SetDialogueMode", 	Z_Construct_UFunction_UFallbackManagerComponent_SetDialogueMode_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UFallbackManagerComponent_SetDialogueMode_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UFallbackManagerComponent_SetDialogueMode_Statics::FallbackManagerComponent_eventSetDialogueMode_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UFallbackManagerComponent_SetDialogueMode_Statics::Function_MetaDataParams), Z_Construct_UFunction_UFallbackManagerComponent_SetDialogueMode_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UFallbackManagerComponent_SetDialogueMode_Statics::FallbackManagerComponent_eventSetDialogueMode_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UFallbackManagerComponent_SetDialogueMode()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFallbackManagerComponent_SetDialogueMode_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UFallbackManagerComponent::execSetDialogueMode)
{
	P_GET_ENUM(EDialogueInputMode,Z_Param_NewMode);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetDialogueMode(EDialogueInputMode(Z_Param_NewMode));
	P_NATIVE_END;
}
// ********** End Class UFallbackManagerComponent Function SetDialogueMode *************************

// ********** Begin Class UFallbackManagerComponent Function SetManipulationMode *******************
struct Z_Construct_UFunction_UFallbackManagerComponent_SetManipulationMode_Statics
{
	struct FallbackManagerComponent_eventSetManipulationMode_Parms
	{
		EManipulationInputMode NewMode;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Fallback" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Manually set the manipulation input mode (G=gesture, K=keyboard). */" },
#endif
		{ "ModuleRelativePath", "Fallback/FallbackManagerComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Manually set the manipulation input mode (G=gesture, K=keyboard)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetManipulationMode constinit property declarations *******************
	static const UECodeGen_Private::FBytePropertyParams NewProp_NewMode_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_NewMode;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetManipulationMode constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetManipulationMode Property Definitions ******************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UFallbackManagerComponent_SetManipulationMode_Statics::NewProp_NewMode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UFallbackManagerComponent_SetManipulationMode_Statics::NewProp_NewMode = { "NewMode", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FallbackManagerComponent_eventSetManipulationMode_Parms, NewMode), Z_Construct_UEnum_LLM_NPC_EManipulationInputMode, METADATA_PARAMS(0, nullptr) }; // 2676813440
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFallbackManagerComponent_SetManipulationMode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFallbackManagerComponent_SetManipulationMode_Statics::NewProp_NewMode_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFallbackManagerComponent_SetManipulationMode_Statics::NewProp_NewMode,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UFallbackManagerComponent_SetManipulationMode_Statics::PropPointers) < 2048);
// ********** End Function SetManipulationMode Property Definitions ********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFallbackManagerComponent_SetManipulationMode_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UFallbackManagerComponent, nullptr, "SetManipulationMode", 	Z_Construct_UFunction_UFallbackManagerComponent_SetManipulationMode_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UFallbackManagerComponent_SetManipulationMode_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UFallbackManagerComponent_SetManipulationMode_Statics::FallbackManagerComponent_eventSetManipulationMode_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UFallbackManagerComponent_SetManipulationMode_Statics::Function_MetaDataParams), Z_Construct_UFunction_UFallbackManagerComponent_SetManipulationMode_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UFallbackManagerComponent_SetManipulationMode_Statics::FallbackManagerComponent_eventSetManipulationMode_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UFallbackManagerComponent_SetManipulationMode()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFallbackManagerComponent_SetManipulationMode_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UFallbackManagerComponent::execSetManipulationMode)
{
	P_GET_ENUM(EManipulationInputMode,Z_Param_NewMode);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetManipulationMode(EManipulationInputMode(Z_Param_NewMode));
	P_NATIVE_END;
}
// ********** End Class UFallbackManagerComponent Function SetManipulationMode *********************

// ********** Begin Class UFallbackManagerComponent ************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UFallbackManagerComponent;
UClass* UFallbackManagerComponent::GetPrivateStaticClass()
{
	using TClass = UFallbackManagerComponent;
	if (!Z_Registration_Info_UClass_UFallbackManagerComponent.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("FallbackManagerComponent"),
			Z_Registration_Info_UClass_UFallbackManagerComponent.InnerSingleton,
			StaticRegisterNativesUFallbackManagerComponent,
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
	return Z_Registration_Info_UClass_UFallbackManagerComponent.InnerSingleton;
}
UClass* Z_Construct_UClass_UFallbackManagerComponent_NoRegister()
{
	return UFallbackManagerComponent::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UFallbackManagerComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "LLMNPC" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Monitors hardware availability (microphone, camera) and automatically switches\n * input modes when devices become unavailable.\n *\n * Degradation priority: Full -> No camera -> No mic -> Minimal.\n *\n * Toggle support via input actions:\n *   T = switch to Text dialogue, V = switch to Voice dialogue,\n *   G = switch to Gesture manipulation, K = switch to Keyboard/Mouse manipulation.\n */" },
#endif
		{ "IncludePath", "Fallback/FallbackManagerComponent.h" },
		{ "ModuleRelativePath", "Fallback/FallbackManagerComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Monitors hardware availability (microphone, camera) and automatically switches\ninput modes when devices become unavailable.\n\nDegradation priority: Full -> No camera -> No mic -> Minimal.\n\nToggle support via input actions:\n  T = switch to Text dialogue, V = switch to Voice dialogue,\n  G = switch to Gesture manipulation, K = switch to Keyboard/Mouse manipulation." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnInputModeChanged_MetaData[] = {
		{ "Category", "NPC|Fallback" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Broadcast when an input mode changes due to device availability or manual toggle. */" },
#endif
		{ "ModuleRelativePath", "Fallback/FallbackManagerComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Broadcast when an input mode changes due to device availability or manual toggle." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PollIntervalSeconds_MetaData[] = {
		{ "Category", "NPC|Fallback" },
		{ "ClampMin", "0.5" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Interval in seconds between hardware availability polls. */" },
#endif
		{ "ModuleRelativePath", "Fallback/FallbackManagerComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Interval in seconds between hardware availability polls." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentDegradationLevel_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Current degradation level. */" },
#endif
		{ "ModuleRelativePath", "Fallback/FallbackManagerComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Current degradation level." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UFallbackManagerComponent constinit property declarations ****************
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnInputModeChanged;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PollIntervalSeconds;
	static const UECodeGen_Private::FBytePropertyParams NewProp_CurrentDegradationLevel_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_CurrentDegradationLevel;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UFallbackManagerComponent constinit property declarations ******************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("CheckDeviceAvailability"), .Pointer = &UFallbackManagerComponent::execCheckDeviceAvailability },
		{ .NameUTF8 = UTF8TEXT("GetCurrentDegradationLevel"), .Pointer = &UFallbackManagerComponent::execGetCurrentDegradationLevel },
		{ .NameUTF8 = UTF8TEXT("SetDialogueMode"), .Pointer = &UFallbackManagerComponent::execSetDialogueMode },
		{ .NameUTF8 = UTF8TEXT("SetManipulationMode"), .Pointer = &UFallbackManagerComponent::execSetManipulationMode },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UFallbackManagerComponent_CheckDeviceAvailability, "CheckDeviceAvailability" }, // 1141157386
		{ &Z_Construct_UFunction_UFallbackManagerComponent_GetCurrentDegradationLevel, "GetCurrentDegradationLevel" }, // 2433642521
		{ &Z_Construct_UFunction_UFallbackManagerComponent_SetDialogueMode, "SetDialogueMode" }, // 314057672
		{ &Z_Construct_UFunction_UFallbackManagerComponent_SetManipulationMode, "SetManipulationMode" }, // 2738312701
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFallbackManagerComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UFallbackManagerComponent_Statics

// ********** Begin Class UFallbackManagerComponent Property Definitions ***************************
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UFallbackManagerComponent_Statics::NewProp_OnInputModeChanged = { "OnInputModeChanged", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UFallbackManagerComponent, OnInputModeChanged), Z_Construct_UDelegateFunction_LLM_NPC_OnInputModeChanged__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnInputModeChanged_MetaData), NewProp_OnInputModeChanged_MetaData) }; // 2149788421
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UFallbackManagerComponent_Statics::NewProp_PollIntervalSeconds = { "PollIntervalSeconds", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UFallbackManagerComponent, PollIntervalSeconds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PollIntervalSeconds_MetaData), NewProp_PollIntervalSeconds_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UFallbackManagerComponent_Statics::NewProp_CurrentDegradationLevel_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UFallbackManagerComponent_Statics::NewProp_CurrentDegradationLevel = { "CurrentDegradationLevel", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UFallbackManagerComponent, CurrentDegradationLevel), Z_Construct_UEnum_LLM_NPC_EDegradationLevel, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentDegradationLevel_MetaData), NewProp_CurrentDegradationLevel_MetaData) }; // 76750131
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UFallbackManagerComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFallbackManagerComponent_Statics::NewProp_OnInputModeChanged,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFallbackManagerComponent_Statics::NewProp_PollIntervalSeconds,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFallbackManagerComponent_Statics::NewProp_CurrentDegradationLevel_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFallbackManagerComponent_Statics::NewProp_CurrentDegradationLevel,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UFallbackManagerComponent_Statics::PropPointers) < 2048);
// ********** End Class UFallbackManagerComponent Property Definitions *****************************
UObject* (*const Z_Construct_UClass_UFallbackManagerComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UNPCSubsystemComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UFallbackManagerComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UFallbackManagerComponent_Statics::ClassParams = {
	&UFallbackManagerComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UFallbackManagerComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UFallbackManagerComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UFallbackManagerComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UFallbackManagerComponent_Statics::Class_MetaDataParams)
};
void UFallbackManagerComponent::StaticRegisterNativesUFallbackManagerComponent()
{
	UClass* Class = UFallbackManagerComponent::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UFallbackManagerComponent_Statics::Funcs));
}
UClass* Z_Construct_UClass_UFallbackManagerComponent()
{
	if (!Z_Registration_Info_UClass_UFallbackManagerComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UFallbackManagerComponent.OuterSingleton, Z_Construct_UClass_UFallbackManagerComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UFallbackManagerComponent.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UFallbackManagerComponent);
UFallbackManagerComponent::~UFallbackManagerComponent() {}
// ********** End Class UFallbackManagerComponent **************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_FallbackManagerComponent_h__Script_LLM_NPC_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EDegradationLevel_StaticEnum, TEXT("EDegradationLevel"), &Z_Registration_Info_UEnum_EDegradationLevel, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 76750131U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UFallbackManagerComponent, UFallbackManagerComponent::StaticClass, TEXT("UFallbackManagerComponent"), &Z_Registration_Info_UClass_UFallbackManagerComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UFallbackManagerComponent), 478157463U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_FallbackManagerComponent_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_FallbackManagerComponent_h__Script_LLM_NPC_580636191{
	TEXT("/Script/LLM_NPC"),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_FallbackManagerComponent_h__Script_LLM_NPC_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_FallbackManagerComponent_h__Script_LLM_NPC_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_FallbackManagerComponent_h__Script_LLM_NPC_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_FallbackManagerComponent_h__Script_LLM_NPC_Statics::EnumInfo),
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
