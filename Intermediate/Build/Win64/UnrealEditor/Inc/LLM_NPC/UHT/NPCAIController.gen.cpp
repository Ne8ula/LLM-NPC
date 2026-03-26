// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Core/NPCAIController.h"
#include "LLM_NPC/Core/NPCTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeNPCAIController() {}

// ********** Begin Cross Module References ********************************************************
AIMODULE_API UClass* Z_Construct_UClass_AAIController();
LLM_NPC_API UClass* Z_Construct_UClass_ANPCAIController();
LLM_NPC_API UClass* Z_Construct_UClass_ANPCAIController_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_ANPCCharacter_NoRegister();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FDetectedUserEmotion();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ANPCAIController Function HandleUserInput ********************************
struct Z_Construct_UFunction_ANPCAIController_HandleUserInput_Statics
{
	struct NPCAIController_eventHandleUserInput_Parms
	{
		FString UserMessage;
		FDetectedUserEmotion UserEmotion;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Dialogue" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Process a user message (from voice STT or text input). */" },
#endif
		{ "ModuleRelativePath", "Core/NPCAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Process a user message (from voice STT or text input)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UserMessage_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UserEmotion_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function HandleUserInput constinit property declarations ***********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_UserMessage;
	static const UECodeGen_Private::FStructPropertyParams NewProp_UserEmotion;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HandleUserInput constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HandleUserInput Property Definitions **********************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_ANPCAIController_HandleUserInput_Statics::NewProp_UserMessage = { "UserMessage", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NPCAIController_eventHandleUserInput_Parms, UserMessage), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UserMessage_MetaData), NewProp_UserMessage_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ANPCAIController_HandleUserInput_Statics::NewProp_UserEmotion = { "UserEmotion", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NPCAIController_eventHandleUserInput_Parms, UserEmotion), Z_Construct_UScriptStruct_FDetectedUserEmotion, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UserEmotion_MetaData), NewProp_UserEmotion_MetaData) }; // 3137125811
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ANPCAIController_HandleUserInput_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ANPCAIController_HandleUserInput_Statics::NewProp_UserMessage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ANPCAIController_HandleUserInput_Statics::NewProp_UserEmotion,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ANPCAIController_HandleUserInput_Statics::PropPointers) < 2048);
// ********** End Function HandleUserInput Property Definitions ************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ANPCAIController_HandleUserInput_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ANPCAIController, nullptr, "HandleUserInput", 	Z_Construct_UFunction_ANPCAIController_HandleUserInput_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ANPCAIController_HandleUserInput_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_ANPCAIController_HandleUserInput_Statics::NPCAIController_eventHandleUserInput_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ANPCAIController_HandleUserInput_Statics::Function_MetaDataParams), Z_Construct_UFunction_ANPCAIController_HandleUserInput_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ANPCAIController_HandleUserInput_Statics::NPCAIController_eventHandleUserInput_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ANPCAIController_HandleUserInput()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ANPCAIController_HandleUserInput_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ANPCAIController::execHandleUserInput)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_UserMessage);
	P_GET_STRUCT_REF(FDetectedUserEmotion,Z_Param_Out_UserEmotion);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleUserInput(Z_Param_UserMessage,Z_Param_Out_UserEmotion);
	P_NATIVE_END;
}
// ********** End Class ANPCAIController Function HandleUserInput **********************************

// ********** Begin Class ANPCAIController *********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_ANPCAIController;
UClass* ANPCAIController::GetPrivateStaticClass()
{
	using TClass = ANPCAIController;
	if (!Z_Registration_Info_UClass_ANPCAIController.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("NPCAIController"),
			Z_Registration_Info_UClass_ANPCAIController.InnerSingleton,
			StaticRegisterNativesANPCAIController,
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
	return Z_Registration_Info_UClass_ANPCAIController.InnerSingleton;
}
UClass* Z_Construct_UClass_ANPCAIController_NoRegister()
{
	return ANPCAIController::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ANPCAIController_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Orchestrator AI controller for the NPC.\n * Routes input between subsystems, coordinates turn-taking,\n * and manages the dialogue loop:\n *   User input \xe2\x86\x92 assemble context \xe2\x86\x92 Claude API \xe2\x86\x92 process response \xe2\x86\x92 animate\n */" },
#endif
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "Core/NPCAIController.h" },
		{ "ModuleRelativePath", "Core/NPCAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Orchestrator AI controller for the NPC.\nRoutes input between subsystems, coordinates turn-taking,\nand manages the dialogue loop:\n  User input \xe2\x86\x92 assemble context \xe2\x86\x92 Claude API \xe2\x86\x92 process response \xe2\x86\x92 animate" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NPCCharacter_MetaData[] = {
		{ "ModuleRelativePath", "Core/NPCAIController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class ANPCAIController constinit property declarations *************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NPCCharacter;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ANPCAIController constinit property declarations ***************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("HandleUserInput"), .Pointer = &ANPCAIController::execHandleUserInput },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ANPCAIController_HandleUserInput, "HandleUserInput" }, // 438735022
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ANPCAIController>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_ANPCAIController_Statics

// ********** Begin Class ANPCAIController Property Definitions ************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ANPCAIController_Statics::NewProp_NPCCharacter = { "NPCCharacter", nullptr, (EPropertyFlags)0x0144000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ANPCAIController, NPCCharacter), Z_Construct_UClass_ANPCCharacter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NPCCharacter_MetaData), NewProp_NPCCharacter_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ANPCAIController_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ANPCAIController_Statics::NewProp_NPCCharacter,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ANPCAIController_Statics::PropPointers) < 2048);
// ********** End Class ANPCAIController Property Definitions **************************************
UObject* (*const Z_Construct_UClass_ANPCAIController_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AAIController,
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ANPCAIController_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ANPCAIController_Statics::ClassParams = {
	&ANPCAIController::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_ANPCAIController_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_ANPCAIController_Statics::PropPointers),
	0,
	0x009002A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ANPCAIController_Statics::Class_MetaDataParams), Z_Construct_UClass_ANPCAIController_Statics::Class_MetaDataParams)
};
void ANPCAIController::StaticRegisterNativesANPCAIController()
{
	UClass* Class = ANPCAIController::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_ANPCAIController_Statics::Funcs));
}
UClass* Z_Construct_UClass_ANPCAIController()
{
	if (!Z_Registration_Info_UClass_ANPCAIController.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ANPCAIController.OuterSingleton, Z_Construct_UClass_ANPCAIController_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ANPCAIController.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ANPCAIController);
ANPCAIController::~ANPCAIController() {}
// ********** End Class ANPCAIController ***********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCAIController_h__Script_LLM_NPC_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ANPCAIController, ANPCAIController::StaticClass, TEXT("ANPCAIController"), &Z_Registration_Info_UClass_ANPCAIController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ANPCAIController), 429263745U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCAIController_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCAIController_h__Script_LLM_NPC_932949595{
	TEXT("/Script/LLM_NPC"),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCAIController_h__Script_LLM_NPC_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCAIController_h__Script_LLM_NPC_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
