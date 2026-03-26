// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Core/NPCCharacter.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeNPCCharacter() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
LLM_NPC_API UClass* Z_Construct_UClass_ANPCCharacter();
LLM_NPC_API UClass* Z_Construct_UClass_ANPCCharacter_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UDialogueComponent_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UEmotionComponent_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UFacialRecognitionComponent_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UFallbackManagerComponent_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UGestureRecognitionComponent_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UMetahumanAnimComponent_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UNPCConfigDataAsset_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UNPCInventoryComponent_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UNPCLipSyncComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ANPCCharacter Function InitializeNPC *************************************
struct Z_Construct_UFunction_ANPCCharacter_InitializeNPC_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Initialize all subsystems with the assigned NPC config. */" },
#endif
		{ "ModuleRelativePath", "Core/NPCCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Initialize all subsystems with the assigned NPC config." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function InitializeNPC constinit property declarations *************************
// ********** End Function InitializeNPC constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ANPCCharacter_InitializeNPC_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ANPCCharacter, nullptr, "InitializeNPC", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ANPCCharacter_InitializeNPC_Statics::Function_MetaDataParams), Z_Construct_UFunction_ANPCCharacter_InitializeNPC_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ANPCCharacter_InitializeNPC()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ANPCCharacter_InitializeNPC_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ANPCCharacter::execInitializeNPC)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->InitializeNPC();
	P_NATIVE_END;
}
// ********** End Class ANPCCharacter Function InitializeNPC ***************************************

// ********** Begin Class ANPCCharacter ************************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_ANPCCharacter;
UClass* ANPCCharacter::GetPrivateStaticClass()
{
	using TClass = ANPCCharacter;
	if (!Z_Registration_Info_UClass_ANPCCharacter.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("NPCCharacter"),
			Z_Registration_Info_UClass_ANPCCharacter.InnerSingleton,
			StaticRegisterNativesANPCCharacter,
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
	return Z_Registration_Info_UClass_ANPCCharacter.InnerSingleton;
}
UClass* Z_Construct_UClass_ANPCCharacter_NoRegister()
{
	return ANPCCharacter::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ANPCCharacter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Base Metahuman NPC actor that owns all subsystem components.\n *\n * Central design: every subsystem is a UActorComponent attached here.\n * To create a new NPC archetype, assign a different UNPCConfigDataAsset.\n * For procedural generation, spawn this actor and configure components at runtime.\n */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Core/NPCCharacter.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Core/NPCCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Base Metahuman NPC actor that owns all subsystem components.\n\nCentral design: every subsystem is a UActorComponent attached here.\nTo create a new NPC archetype, assign a different UNPCConfigDataAsset.\nFor procedural generation, spawn this actor and configure components at runtime." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NPCConfig_MetaData[] = {
		{ "Category", "NPC|Config" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The NPC archetype configuration. Drives personality, prompts, and references. */" },
#endif
		{ "ModuleRelativePath", "Core/NPCCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The NPC archetype configuration. Drives personality, prompts, and references." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DialogueComponent_MetaData[] = {
		{ "Category", "NPC|Subsystems" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ---- Subsystem Components ----\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Core/NPCCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "---- Subsystem Components ----" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EmotionComponent_MetaData[] = {
		{ "Category", "NPC|Subsystems" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Core/NPCCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FacialRecognitionComponent_MetaData[] = {
		{ "Category", "NPC|Subsystems" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Core/NPCCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GestureRecognitionComponent_MetaData[] = {
		{ "Category", "NPC|Subsystems" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Core/NPCCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InventoryComponent_MetaData[] = {
		{ "Category", "NPC|Subsystems" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Core/NPCCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MetahumanAnimComponent_MetaData[] = {
		{ "Category", "NPC|Subsystems" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Core/NPCCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LipSyncComponent_MetaData[] = {
		{ "Category", "NPC|Subsystems" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Core/NPCCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FallbackManagerComponent_MetaData[] = {
		{ "Category", "NPC|Subsystems" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Core/NPCCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class ANPCCharacter constinit property declarations ****************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NPCConfig;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DialogueComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_EmotionComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FacialRecognitionComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_GestureRecognitionComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InventoryComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MetahumanAnimComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LipSyncComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FallbackManagerComponent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ANPCCharacter constinit property declarations ******************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("InitializeNPC"), .Pointer = &ANPCCharacter::execInitializeNPC },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ANPCCharacter_InitializeNPC, "InitializeNPC" }, // 2308749606
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ANPCCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_ANPCCharacter_Statics

// ********** Begin Class ANPCCharacter Property Definitions ***************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ANPCCharacter_Statics::NewProp_NPCConfig = { "NPCConfig", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ANPCCharacter, NPCConfig), Z_Construct_UClass_UNPCConfigDataAsset_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NPCConfig_MetaData), NewProp_NPCConfig_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ANPCCharacter_Statics::NewProp_DialogueComponent = { "DialogueComponent", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ANPCCharacter, DialogueComponent), Z_Construct_UClass_UDialogueComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DialogueComponent_MetaData), NewProp_DialogueComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ANPCCharacter_Statics::NewProp_EmotionComponent = { "EmotionComponent", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ANPCCharacter, EmotionComponent), Z_Construct_UClass_UEmotionComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EmotionComponent_MetaData), NewProp_EmotionComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ANPCCharacter_Statics::NewProp_FacialRecognitionComponent = { "FacialRecognitionComponent", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ANPCCharacter, FacialRecognitionComponent), Z_Construct_UClass_UFacialRecognitionComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FacialRecognitionComponent_MetaData), NewProp_FacialRecognitionComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ANPCCharacter_Statics::NewProp_GestureRecognitionComponent = { "GestureRecognitionComponent", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ANPCCharacter, GestureRecognitionComponent), Z_Construct_UClass_UGestureRecognitionComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GestureRecognitionComponent_MetaData), NewProp_GestureRecognitionComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ANPCCharacter_Statics::NewProp_InventoryComponent = { "InventoryComponent", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ANPCCharacter, InventoryComponent), Z_Construct_UClass_UNPCInventoryComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InventoryComponent_MetaData), NewProp_InventoryComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ANPCCharacter_Statics::NewProp_MetahumanAnimComponent = { "MetahumanAnimComponent", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ANPCCharacter, MetahumanAnimComponent), Z_Construct_UClass_UMetahumanAnimComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MetahumanAnimComponent_MetaData), NewProp_MetahumanAnimComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ANPCCharacter_Statics::NewProp_LipSyncComponent = { "LipSyncComponent", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ANPCCharacter, LipSyncComponent), Z_Construct_UClass_UNPCLipSyncComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LipSyncComponent_MetaData), NewProp_LipSyncComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ANPCCharacter_Statics::NewProp_FallbackManagerComponent = { "FallbackManagerComponent", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ANPCCharacter, FallbackManagerComponent), Z_Construct_UClass_UFallbackManagerComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FallbackManagerComponent_MetaData), NewProp_FallbackManagerComponent_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ANPCCharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ANPCCharacter_Statics::NewProp_NPCConfig,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ANPCCharacter_Statics::NewProp_DialogueComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ANPCCharacter_Statics::NewProp_EmotionComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ANPCCharacter_Statics::NewProp_FacialRecognitionComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ANPCCharacter_Statics::NewProp_GestureRecognitionComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ANPCCharacter_Statics::NewProp_InventoryComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ANPCCharacter_Statics::NewProp_MetahumanAnimComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ANPCCharacter_Statics::NewProp_LipSyncComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ANPCCharacter_Statics::NewProp_FallbackManagerComponent,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ANPCCharacter_Statics::PropPointers) < 2048);
// ********** End Class ANPCCharacter Property Definitions *****************************************
UObject* (*const Z_Construct_UClass_ANPCCharacter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ANPCCharacter_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ANPCCharacter_Statics::ClassParams = {
	&ANPCCharacter::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_ANPCCharacter_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_ANPCCharacter_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ANPCCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_ANPCCharacter_Statics::Class_MetaDataParams)
};
void ANPCCharacter::StaticRegisterNativesANPCCharacter()
{
	UClass* Class = ANPCCharacter::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_ANPCCharacter_Statics::Funcs));
}
UClass* Z_Construct_UClass_ANPCCharacter()
{
	if (!Z_Registration_Info_UClass_ANPCCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ANPCCharacter.OuterSingleton, Z_Construct_UClass_ANPCCharacter_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ANPCCharacter.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ANPCCharacter);
ANPCCharacter::~ANPCCharacter() {}
// ********** End Class ANPCCharacter **************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCCharacter_h__Script_LLM_NPC_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ANPCCharacter, ANPCCharacter::StaticClass, TEXT("ANPCCharacter"), &Z_Registration_Info_UClass_ANPCCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ANPCCharacter), 373128312U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCCharacter_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCCharacter_h__Script_LLM_NPC_2395019191{
	TEXT("/Script/LLM_NPC"),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCCharacter_h__Script_LLM_NPC_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCCharacter_h__Script_LLM_NPC_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
