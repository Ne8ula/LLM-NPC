// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Fallback/InputModeSubsystem.h"
#include "Engine/GameInstance.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeInputModeSubsystem() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UGameInstanceSubsystem();
LLM_NPC_API UClass* Z_Construct_UClass_UInputModeSubsystem();
LLM_NPC_API UClass* Z_Construct_UClass_UInputModeSubsystem_NoRegister();
LLM_NPC_API UEnum* Z_Construct_UEnum_LLM_NPC_EDialogueInputMode();
LLM_NPC_API UEnum* Z_Construct_UEnum_LLM_NPC_EManipulationInputMode();
LLM_NPC_API UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueInputModeChanged__DelegateSignature();
LLM_NPC_API UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnManipulationInputModeChanged__DelegateSignature();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FOnDialogueInputModeChanged *******************************************
struct Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueInputModeChanged__DelegateSignature_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Fallback/InputModeSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnDialogueInputModeChanged constinit property declarations ***********
// ********** End Delegate FOnDialogueInputModeChanged constinit property declarations *************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueInputModeChanged__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_LLM_NPC, nullptr, "OnDialogueInputModeChanged__DelegateSignature", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueInputModeChanged__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueInputModeChanged__DelegateSignature_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueInputModeChanged__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueInputModeChanged__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnDialogueInputModeChanged_DelegateWrapper(const FMulticastScriptDelegate& OnDialogueInputModeChanged)
{
	OnDialogueInputModeChanged.ProcessMulticastDelegate<UObject>(NULL);
}
// ********** End Delegate FOnDialogueInputModeChanged *********************************************

// ********** Begin Delegate FOnManipulationInputModeChanged ***************************************
struct Z_Construct_UDelegateFunction_LLM_NPC_OnManipulationInputModeChanged__DelegateSignature_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Fallback/InputModeSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnManipulationInputModeChanged constinit property declarations *******
// ********** End Delegate FOnManipulationInputModeChanged constinit property declarations *********
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_LLM_NPC_OnManipulationInputModeChanged__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_LLM_NPC, nullptr, "OnManipulationInputModeChanged__DelegateSignature", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnManipulationInputModeChanged__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_LLM_NPC_OnManipulationInputModeChanged__DelegateSignature_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnManipulationInputModeChanged__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_LLM_NPC_OnManipulationInputModeChanged__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnManipulationInputModeChanged_DelegateWrapper(const FMulticastScriptDelegate& OnManipulationInputModeChanged)
{
	OnManipulationInputModeChanged.ProcessMulticastDelegate<UObject>(NULL);
}
// ********** End Delegate FOnManipulationInputModeChanged *****************************************

// ********** Begin Class UInputModeSubsystem Function GetActiveDialogueInput **********************
struct Z_Construct_UFunction_UInputModeSubsystem_GetActiveDialogueInput_Statics
{
	struct InputModeSubsystem_eventGetActiveDialogueInput_Parms
	{
		EDialogueInputMode ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|InputMode" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// --- Dialogue input mode ---\n" },
#endif
		{ "ModuleRelativePath", "Fallback/InputModeSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "--- Dialogue input mode ---" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetActiveDialogueInput constinit property declarations ****************
	static const UECodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetActiveDialogueInput constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetActiveDialogueInput Property Definitions ***************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UInputModeSubsystem_GetActiveDialogueInput_Statics::NewProp_ReturnValue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UInputModeSubsystem_GetActiveDialogueInput_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(InputModeSubsystem_eventGetActiveDialogueInput_Parms, ReturnValue), Z_Construct_UEnum_LLM_NPC_EDialogueInputMode, METADATA_PARAMS(0, nullptr) }; // 4223634033
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UInputModeSubsystem_GetActiveDialogueInput_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UInputModeSubsystem_GetActiveDialogueInput_Statics::NewProp_ReturnValue_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UInputModeSubsystem_GetActiveDialogueInput_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UInputModeSubsystem_GetActiveDialogueInput_Statics::PropPointers) < 2048);
// ********** End Function GetActiveDialogueInput Property Definitions *****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UInputModeSubsystem_GetActiveDialogueInput_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UInputModeSubsystem, nullptr, "GetActiveDialogueInput", 	Z_Construct_UFunction_UInputModeSubsystem_GetActiveDialogueInput_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UInputModeSubsystem_GetActiveDialogueInput_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UInputModeSubsystem_GetActiveDialogueInput_Statics::InputModeSubsystem_eventGetActiveDialogueInput_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UInputModeSubsystem_GetActiveDialogueInput_Statics::Function_MetaDataParams), Z_Construct_UFunction_UInputModeSubsystem_GetActiveDialogueInput_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UInputModeSubsystem_GetActiveDialogueInput_Statics::InputModeSubsystem_eventGetActiveDialogueInput_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UInputModeSubsystem_GetActiveDialogueInput()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UInputModeSubsystem_GetActiveDialogueInput_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UInputModeSubsystem::execGetActiveDialogueInput)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(EDialogueInputMode*)Z_Param__Result=P_THIS->GetActiveDialogueInput();
	P_NATIVE_END;
}
// ********** End Class UInputModeSubsystem Function GetActiveDialogueInput ************************

// ********** Begin Class UInputModeSubsystem Function GetActiveManipulationInput ******************
struct Z_Construct_UFunction_UInputModeSubsystem_GetActiveManipulationInput_Statics
{
	struct InputModeSubsystem_eventGetActiveManipulationInput_Parms
	{
		EManipulationInputMode ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|InputMode" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// --- Manipulation input mode ---\n" },
#endif
		{ "ModuleRelativePath", "Fallback/InputModeSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "--- Manipulation input mode ---" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetActiveManipulationInput constinit property declarations ************
	static const UECodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetActiveManipulationInput constinit property declarations **************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetActiveManipulationInput Property Definitions ***********************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UInputModeSubsystem_GetActiveManipulationInput_Statics::NewProp_ReturnValue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UInputModeSubsystem_GetActiveManipulationInput_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(InputModeSubsystem_eventGetActiveManipulationInput_Parms, ReturnValue), Z_Construct_UEnum_LLM_NPC_EManipulationInputMode, METADATA_PARAMS(0, nullptr) }; // 2676813440
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UInputModeSubsystem_GetActiveManipulationInput_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UInputModeSubsystem_GetActiveManipulationInput_Statics::NewProp_ReturnValue_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UInputModeSubsystem_GetActiveManipulationInput_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UInputModeSubsystem_GetActiveManipulationInput_Statics::PropPointers) < 2048);
// ********** End Function GetActiveManipulationInput Property Definitions *************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UInputModeSubsystem_GetActiveManipulationInput_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UInputModeSubsystem, nullptr, "GetActiveManipulationInput", 	Z_Construct_UFunction_UInputModeSubsystem_GetActiveManipulationInput_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UInputModeSubsystem_GetActiveManipulationInput_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UInputModeSubsystem_GetActiveManipulationInput_Statics::InputModeSubsystem_eventGetActiveManipulationInput_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UInputModeSubsystem_GetActiveManipulationInput_Statics::Function_MetaDataParams), Z_Construct_UFunction_UInputModeSubsystem_GetActiveManipulationInput_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UInputModeSubsystem_GetActiveManipulationInput_Statics::InputModeSubsystem_eventGetActiveManipulationInput_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UInputModeSubsystem_GetActiveManipulationInput()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UInputModeSubsystem_GetActiveManipulationInput_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UInputModeSubsystem::execGetActiveManipulationInput)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(EManipulationInputMode*)Z_Param__Result=P_THIS->GetActiveManipulationInput();
	P_NATIVE_END;
}
// ********** End Class UInputModeSubsystem Function GetActiveManipulationInput ********************

// ********** Begin Class UInputModeSubsystem Function SetDialogueInput ****************************
struct Z_Construct_UFunction_UInputModeSubsystem_SetDialogueInput_Statics
{
	struct InputModeSubsystem_eventSetDialogueInput_Parms
	{
		EDialogueInputMode NewMode;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|InputMode" },
		{ "ModuleRelativePath", "Fallback/InputModeSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetDialogueInput constinit property declarations **********************
	static const UECodeGen_Private::FBytePropertyParams NewProp_NewMode_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_NewMode;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetDialogueInput constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetDialogueInput Property Definitions *********************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UInputModeSubsystem_SetDialogueInput_Statics::NewProp_NewMode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UInputModeSubsystem_SetDialogueInput_Statics::NewProp_NewMode = { "NewMode", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(InputModeSubsystem_eventSetDialogueInput_Parms, NewMode), Z_Construct_UEnum_LLM_NPC_EDialogueInputMode, METADATA_PARAMS(0, nullptr) }; // 4223634033
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UInputModeSubsystem_SetDialogueInput_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UInputModeSubsystem_SetDialogueInput_Statics::NewProp_NewMode_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UInputModeSubsystem_SetDialogueInput_Statics::NewProp_NewMode,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UInputModeSubsystem_SetDialogueInput_Statics::PropPointers) < 2048);
// ********** End Function SetDialogueInput Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UInputModeSubsystem_SetDialogueInput_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UInputModeSubsystem, nullptr, "SetDialogueInput", 	Z_Construct_UFunction_UInputModeSubsystem_SetDialogueInput_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UInputModeSubsystem_SetDialogueInput_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UInputModeSubsystem_SetDialogueInput_Statics::InputModeSubsystem_eventSetDialogueInput_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UInputModeSubsystem_SetDialogueInput_Statics::Function_MetaDataParams), Z_Construct_UFunction_UInputModeSubsystem_SetDialogueInput_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UInputModeSubsystem_SetDialogueInput_Statics::InputModeSubsystem_eventSetDialogueInput_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UInputModeSubsystem_SetDialogueInput()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UInputModeSubsystem_SetDialogueInput_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UInputModeSubsystem::execSetDialogueInput)
{
	P_GET_ENUM(EDialogueInputMode,Z_Param_NewMode);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetDialogueInput(EDialogueInputMode(Z_Param_NewMode));
	P_NATIVE_END;
}
// ********** End Class UInputModeSubsystem Function SetDialogueInput ******************************

// ********** Begin Class UInputModeSubsystem Function SetManipulationInput ************************
struct Z_Construct_UFunction_UInputModeSubsystem_SetManipulationInput_Statics
{
	struct InputModeSubsystem_eventSetManipulationInput_Parms
	{
		EManipulationInputMode NewMode;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|InputMode" },
		{ "ModuleRelativePath", "Fallback/InputModeSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetManipulationInput constinit property declarations ******************
	static const UECodeGen_Private::FBytePropertyParams NewProp_NewMode_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_NewMode;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetManipulationInput constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetManipulationInput Property Definitions *****************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UInputModeSubsystem_SetManipulationInput_Statics::NewProp_NewMode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UInputModeSubsystem_SetManipulationInput_Statics::NewProp_NewMode = { "NewMode", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(InputModeSubsystem_eventSetManipulationInput_Parms, NewMode), Z_Construct_UEnum_LLM_NPC_EManipulationInputMode, METADATA_PARAMS(0, nullptr) }; // 2676813440
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UInputModeSubsystem_SetManipulationInput_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UInputModeSubsystem_SetManipulationInput_Statics::NewProp_NewMode_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UInputModeSubsystem_SetManipulationInput_Statics::NewProp_NewMode,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UInputModeSubsystem_SetManipulationInput_Statics::PropPointers) < 2048);
// ********** End Function SetManipulationInput Property Definitions *******************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UInputModeSubsystem_SetManipulationInput_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UInputModeSubsystem, nullptr, "SetManipulationInput", 	Z_Construct_UFunction_UInputModeSubsystem_SetManipulationInput_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UInputModeSubsystem_SetManipulationInput_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UInputModeSubsystem_SetManipulationInput_Statics::InputModeSubsystem_eventSetManipulationInput_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UInputModeSubsystem_SetManipulationInput_Statics::Function_MetaDataParams), Z_Construct_UFunction_UInputModeSubsystem_SetManipulationInput_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UInputModeSubsystem_SetManipulationInput_Statics::InputModeSubsystem_eventSetManipulationInput_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UInputModeSubsystem_SetManipulationInput()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UInputModeSubsystem_SetManipulationInput_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UInputModeSubsystem::execSetManipulationInput)
{
	P_GET_ENUM(EManipulationInputMode,Z_Param_NewMode);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetManipulationInput(EManipulationInputMode(Z_Param_NewMode));
	P_NATIVE_END;
}
// ********** End Class UInputModeSubsystem Function SetManipulationInput **************************

// ********** Begin Class UInputModeSubsystem ******************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UInputModeSubsystem;
UClass* UInputModeSubsystem::GetPrivateStaticClass()
{
	using TClass = UInputModeSubsystem;
	if (!Z_Registration_Info_UClass_UInputModeSubsystem.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("InputModeSubsystem"),
			Z_Registration_Info_UClass_UInputModeSubsystem.InnerSingleton,
			StaticRegisterNativesUInputModeSubsystem,
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
	return Z_Registration_Info_UClass_UInputModeSubsystem.InnerSingleton;
}
UClass* Z_Construct_UClass_UInputModeSubsystem_NoRegister()
{
	return UInputModeSubsystem::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UInputModeSubsystem_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Game-instance-level subsystem that tracks the globally active input modes\n * for dialogue (Voice / Text) and object manipulation (Gesture / KeyboardMouse).\n *\n * The FallbackManagerComponent writes to this subsystem when hardware becomes\n * unavailable.  UI and gameplay systems read from it to adapt their behaviour.\n */" },
#endif
		{ "IncludePath", "Fallback/InputModeSubsystem.h" },
		{ "ModuleRelativePath", "Fallback/InputModeSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Game-instance-level subsystem that tracks the globally active input modes\nfor dialogue (Voice / Text) and object manipulation (Gesture / KeyboardMouse).\n\nThe FallbackManagerComponent writes to this subsystem when hardware becomes\nunavailable.  UI and gameplay systems read from it to adapt their behaviour." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnDialogueInputModeChanged_MetaData[] = {
		{ "Category", "NPC|InputMode" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Broadcast when the dialogue input mode changes. */" },
#endif
		{ "ModuleRelativePath", "Fallback/InputModeSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Broadcast when the dialogue input mode changes." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnManipulationInputModeChanged_MetaData[] = {
		{ "Category", "NPC|InputMode" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Broadcast when the manipulation input mode changes. */" },
#endif
		{ "ModuleRelativePath", "Fallback/InputModeSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Broadcast when the manipulation input mode changes." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActiveDialogueInput_MetaData[] = {
		{ "ModuleRelativePath", "Fallback/InputModeSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActiveManipulationInput_MetaData[] = {
		{ "ModuleRelativePath", "Fallback/InputModeSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UInputModeSubsystem constinit property declarations **********************
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnDialogueInputModeChanged;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnManipulationInputModeChanged;
	static const UECodeGen_Private::FBytePropertyParams NewProp_ActiveDialogueInput_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ActiveDialogueInput;
	static const UECodeGen_Private::FBytePropertyParams NewProp_ActiveManipulationInput_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ActiveManipulationInput;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UInputModeSubsystem constinit property declarations ************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("GetActiveDialogueInput"), .Pointer = &UInputModeSubsystem::execGetActiveDialogueInput },
		{ .NameUTF8 = UTF8TEXT("GetActiveManipulationInput"), .Pointer = &UInputModeSubsystem::execGetActiveManipulationInput },
		{ .NameUTF8 = UTF8TEXT("SetDialogueInput"), .Pointer = &UInputModeSubsystem::execSetDialogueInput },
		{ .NameUTF8 = UTF8TEXT("SetManipulationInput"), .Pointer = &UInputModeSubsystem::execSetManipulationInput },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UInputModeSubsystem_GetActiveDialogueInput, "GetActiveDialogueInput" }, // 578913442
		{ &Z_Construct_UFunction_UInputModeSubsystem_GetActiveManipulationInput, "GetActiveManipulationInput" }, // 2568649747
		{ &Z_Construct_UFunction_UInputModeSubsystem_SetDialogueInput, "SetDialogueInput" }, // 1321736783
		{ &Z_Construct_UFunction_UInputModeSubsystem_SetManipulationInput, "SetManipulationInput" }, // 3092085859
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UInputModeSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UInputModeSubsystem_Statics

// ********** Begin Class UInputModeSubsystem Property Definitions *********************************
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UInputModeSubsystem_Statics::NewProp_OnDialogueInputModeChanged = { "OnDialogueInputModeChanged", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInputModeSubsystem, OnDialogueInputModeChanged), Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueInputModeChanged__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnDialogueInputModeChanged_MetaData), NewProp_OnDialogueInputModeChanged_MetaData) }; // 1919872677
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UInputModeSubsystem_Statics::NewProp_OnManipulationInputModeChanged = { "OnManipulationInputModeChanged", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInputModeSubsystem, OnManipulationInputModeChanged), Z_Construct_UDelegateFunction_LLM_NPC_OnManipulationInputModeChanged__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnManipulationInputModeChanged_MetaData), NewProp_OnManipulationInputModeChanged_MetaData) }; // 2258343393
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UInputModeSubsystem_Statics::NewProp_ActiveDialogueInput_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UInputModeSubsystem_Statics::NewProp_ActiveDialogueInput = { "ActiveDialogueInput", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInputModeSubsystem, ActiveDialogueInput), Z_Construct_UEnum_LLM_NPC_EDialogueInputMode, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActiveDialogueInput_MetaData), NewProp_ActiveDialogueInput_MetaData) }; // 4223634033
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UInputModeSubsystem_Statics::NewProp_ActiveManipulationInput_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UInputModeSubsystem_Statics::NewProp_ActiveManipulationInput = { "ActiveManipulationInput", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInputModeSubsystem, ActiveManipulationInput), Z_Construct_UEnum_LLM_NPC_EManipulationInputMode, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActiveManipulationInput_MetaData), NewProp_ActiveManipulationInput_MetaData) }; // 2676813440
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UInputModeSubsystem_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInputModeSubsystem_Statics::NewProp_OnDialogueInputModeChanged,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInputModeSubsystem_Statics::NewProp_OnManipulationInputModeChanged,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInputModeSubsystem_Statics::NewProp_ActiveDialogueInput_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInputModeSubsystem_Statics::NewProp_ActiveDialogueInput,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInputModeSubsystem_Statics::NewProp_ActiveManipulationInput_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInputModeSubsystem_Statics::NewProp_ActiveManipulationInput,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UInputModeSubsystem_Statics::PropPointers) < 2048);
// ********** End Class UInputModeSubsystem Property Definitions ***********************************
UObject* (*const Z_Construct_UClass_UInputModeSubsystem_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UGameInstanceSubsystem,
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UInputModeSubsystem_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UInputModeSubsystem_Statics::ClassParams = {
	&UInputModeSubsystem::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UInputModeSubsystem_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UInputModeSubsystem_Statics::PropPointers),
	0,
	0x009000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UInputModeSubsystem_Statics::Class_MetaDataParams), Z_Construct_UClass_UInputModeSubsystem_Statics::Class_MetaDataParams)
};
void UInputModeSubsystem::StaticRegisterNativesUInputModeSubsystem()
{
	UClass* Class = UInputModeSubsystem::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UInputModeSubsystem_Statics::Funcs));
}
UClass* Z_Construct_UClass_UInputModeSubsystem()
{
	if (!Z_Registration_Info_UClass_UInputModeSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UInputModeSubsystem.OuterSingleton, Z_Construct_UClass_UInputModeSubsystem_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UInputModeSubsystem.OuterSingleton;
}
UInputModeSubsystem::UInputModeSubsystem() {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UInputModeSubsystem);
UInputModeSubsystem::~UInputModeSubsystem() {}
// ********** End Class UInputModeSubsystem ********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_InputModeSubsystem_h__Script_LLM_NPC_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UInputModeSubsystem, UInputModeSubsystem::StaticClass, TEXT("UInputModeSubsystem"), &Z_Registration_Info_UClass_UInputModeSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UInputModeSubsystem), 1356500718U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_InputModeSubsystem_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_InputModeSubsystem_h__Script_LLM_NPC_4250970044{
	TEXT("/Script/LLM_NPC"),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_InputModeSubsystem_h__Script_LLM_NPC_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_InputModeSubsystem_h__Script_LLM_NPC_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
