// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Core/NPCSubsystemComponent.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeNPCSubsystemComponent() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
LLM_NPC_API UClass* Z_Construct_UClass_UNPCSubsystemComponent();
LLM_NPC_API UClass* Z_Construct_UClass_UNPCSubsystemComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UNPCSubsystemComponent Function GetSubsystemName *************************
struct Z_Construct_UFunction_UNPCSubsystemComponent_GetSubsystemName_Statics
{
	struct NPCSubsystemComponent_eventGetSubsystemName_Parms
	{
		FString ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Subsystem" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Human-readable name for this subsystem (for logging/debugging). */" },
#endif
		{ "ModuleRelativePath", "Core/NPCSubsystemComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Human-readable name for this subsystem (for logging/debugging)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetSubsystemName constinit property declarations **********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetSubsystemName constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetSubsystemName Property Definitions *********************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UNPCSubsystemComponent_GetSubsystemName_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NPCSubsystemComponent_eventGetSubsystemName_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNPCSubsystemComponent_GetSubsystemName_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNPCSubsystemComponent_GetSubsystemName_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UNPCSubsystemComponent_GetSubsystemName_Statics::PropPointers) < 2048);
// ********** End Function GetSubsystemName Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNPCSubsystemComponent_GetSubsystemName_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UNPCSubsystemComponent, nullptr, "GetSubsystemName", 	Z_Construct_UFunction_UNPCSubsystemComponent_GetSubsystemName_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UNPCSubsystemComponent_GetSubsystemName_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UNPCSubsystemComponent_GetSubsystemName_Statics::NPCSubsystemComponent_eventGetSubsystemName_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNPCSubsystemComponent_GetSubsystemName_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNPCSubsystemComponent_GetSubsystemName_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UNPCSubsystemComponent_GetSubsystemName_Statics::NPCSubsystemComponent_eventGetSubsystemName_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNPCSubsystemComponent_GetSubsystemName()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNPCSubsystemComponent_GetSubsystemName_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNPCSubsystemComponent::execGetSubsystemName)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FString*)Z_Param__Result=P_THIS->GetSubsystemName();
	P_NATIVE_END;
}
// ********** End Class UNPCSubsystemComponent Function GetSubsystemName ***************************

// ********** Begin Class UNPCSubsystemComponent Function InitializeSubsystem **********************
struct Z_Construct_UFunction_UNPCSubsystemComponent_InitializeSubsystem_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Subsystem" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Initialize the subsystem. Called after all components are registered.\n\x09 * Override in derived classes to set up resources.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Core/NPCSubsystemComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Initialize the subsystem. Called after all components are registered.\nOverride in derived classes to set up resources." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function InitializeSubsystem constinit property declarations *******************
// ********** End Function InitializeSubsystem constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNPCSubsystemComponent_InitializeSubsystem_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UNPCSubsystemComponent, nullptr, "InitializeSubsystem", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNPCSubsystemComponent_InitializeSubsystem_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNPCSubsystemComponent_InitializeSubsystem_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UNPCSubsystemComponent_InitializeSubsystem()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNPCSubsystemComponent_InitializeSubsystem_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNPCSubsystemComponent::execInitializeSubsystem)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->InitializeSubsystem();
	P_NATIVE_END;
}
// ********** End Class UNPCSubsystemComponent Function InitializeSubsystem ************************

// ********** Begin Class UNPCSubsystemComponent Function IsSubsystemAvailable *********************
struct Z_Construct_UFunction_UNPCSubsystemComponent_IsSubsystemAvailable_Statics
{
	struct NPCSubsystemComponent_eventIsSubsystemAvailable_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Subsystem" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Check if the subsystem is currently available and functional.\n\x09 * Used by the Fallback system to detect when hardware is missing.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Core/NPCSubsystemComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Check if the subsystem is currently available and functional.\nUsed by the Fallback system to detect when hardware is missing." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function IsSubsystemAvailable constinit property declarations ******************
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsSubsystemAvailable constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsSubsystemAvailable Property Definitions *****************************
void Z_Construct_UFunction_UNPCSubsystemComponent_IsSubsystemAvailable_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((NPCSubsystemComponent_eventIsSubsystemAvailable_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UNPCSubsystemComponent_IsSubsystemAvailable_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(NPCSubsystemComponent_eventIsSubsystemAvailable_Parms), &Z_Construct_UFunction_UNPCSubsystemComponent_IsSubsystemAvailable_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNPCSubsystemComponent_IsSubsystemAvailable_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNPCSubsystemComponent_IsSubsystemAvailable_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UNPCSubsystemComponent_IsSubsystemAvailable_Statics::PropPointers) < 2048);
// ********** End Function IsSubsystemAvailable Property Definitions *******************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNPCSubsystemComponent_IsSubsystemAvailable_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UNPCSubsystemComponent, nullptr, "IsSubsystemAvailable", 	Z_Construct_UFunction_UNPCSubsystemComponent_IsSubsystemAvailable_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UNPCSubsystemComponent_IsSubsystemAvailable_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UNPCSubsystemComponent_IsSubsystemAvailable_Statics::NPCSubsystemComponent_eventIsSubsystemAvailable_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNPCSubsystemComponent_IsSubsystemAvailable_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNPCSubsystemComponent_IsSubsystemAvailable_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UNPCSubsystemComponent_IsSubsystemAvailable_Statics::NPCSubsystemComponent_eventIsSubsystemAvailable_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNPCSubsystemComponent_IsSubsystemAvailable()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNPCSubsystemComponent_IsSubsystemAvailable_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNPCSubsystemComponent::execIsSubsystemAvailable)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsSubsystemAvailable();
	P_NATIVE_END;
}
// ********** End Class UNPCSubsystemComponent Function IsSubsystemAvailable ***********************

// ********** Begin Class UNPCSubsystemComponent Function ShutdownSubsystem ************************
struct Z_Construct_UFunction_UNPCSubsystemComponent_ShutdownSubsystem_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Subsystem" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Shut down the subsystem. Release resources.\n\x09 * Override in derived classes for cleanup.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Core/NPCSubsystemComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Shut down the subsystem. Release resources.\nOverride in derived classes for cleanup." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ShutdownSubsystem constinit property declarations *********************
// ********** End Function ShutdownSubsystem constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNPCSubsystemComponent_ShutdownSubsystem_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UNPCSubsystemComponent, nullptr, "ShutdownSubsystem", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNPCSubsystemComponent_ShutdownSubsystem_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNPCSubsystemComponent_ShutdownSubsystem_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UNPCSubsystemComponent_ShutdownSubsystem()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNPCSubsystemComponent_ShutdownSubsystem_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNPCSubsystemComponent::execShutdownSubsystem)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ShutdownSubsystem();
	P_NATIVE_END;
}
// ********** End Class UNPCSubsystemComponent Function ShutdownSubsystem **************************

// ********** Begin Class UNPCSubsystemComponent ***************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UNPCSubsystemComponent;
UClass* UNPCSubsystemComponent::GetPrivateStaticClass()
{
	using TClass = UNPCSubsystemComponent;
	if (!Z_Registration_Info_UClass_UNPCSubsystemComponent.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("NPCSubsystemComponent"),
			Z_Registration_Info_UClass_UNPCSubsystemComponent.InnerSingleton,
			StaticRegisterNativesUNPCSubsystemComponent,
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
	return Z_Registration_Info_UClass_UNPCSubsystemComponent.InnerSingleton;
}
UClass* Z_Construct_UClass_UNPCSubsystemComponent_NoRegister()
{
	return UNPCSubsystemComponent::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UNPCSubsystemComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "LLMNPC" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Abstract base class for all NPC subsystem components.\n * Each subsystem (Dialogue, Emotion, Vision, Gesture, Inventory, Animation, Fallback)\n * derives from this to provide a uniform lifecycle and availability interface.\n *\n * Design principle: Component-over-inheritance. Every subsystem is a UActorComponent\n * that can be attached to any Metahuman actor, enabling procedural NPC generation.\n */" },
#endif
		{ "IncludePath", "Core/NPCSubsystemComponent.h" },
		{ "ModuleRelativePath", "Core/NPCSubsystemComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Abstract base class for all NPC subsystem components.\nEach subsystem (Dialogue, Emotion, Vision, Gesture, Inventory, Animation, Fallback)\nderives from this to provide a uniform lifecycle and availability interface.\n\nDesign principle: Component-over-inheritance. Every subsystem is a UActorComponent\nthat can be attached to any Metahuman actor, enabling procedural NPC generation." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SubsystemName_MetaData[] = {
		{ "Category", "NPC|Subsystem" },
		{ "ModuleRelativePath", "Core/NPCSubsystemComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsInitialized_MetaData[] = {
		{ "Category", "NPC|Subsystem" },
		{ "ModuleRelativePath", "Core/NPCSubsystemComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsAvailable_MetaData[] = {
		{ "Category", "NPC|Subsystem" },
		{ "ModuleRelativePath", "Core/NPCSubsystemComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UNPCSubsystemComponent constinit property declarations *******************
	static const UECodeGen_Private::FStrPropertyParams NewProp_SubsystemName;
	static void NewProp_bIsInitialized_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsInitialized;
	static void NewProp_bIsAvailable_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsAvailable;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UNPCSubsystemComponent constinit property declarations *********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("GetSubsystemName"), .Pointer = &UNPCSubsystemComponent::execGetSubsystemName },
		{ .NameUTF8 = UTF8TEXT("InitializeSubsystem"), .Pointer = &UNPCSubsystemComponent::execInitializeSubsystem },
		{ .NameUTF8 = UTF8TEXT("IsSubsystemAvailable"), .Pointer = &UNPCSubsystemComponent::execIsSubsystemAvailable },
		{ .NameUTF8 = UTF8TEXT("ShutdownSubsystem"), .Pointer = &UNPCSubsystemComponent::execShutdownSubsystem },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UNPCSubsystemComponent_GetSubsystemName, "GetSubsystemName" }, // 4038458383
		{ &Z_Construct_UFunction_UNPCSubsystemComponent_InitializeSubsystem, "InitializeSubsystem" }, // 3044339210
		{ &Z_Construct_UFunction_UNPCSubsystemComponent_IsSubsystemAvailable, "IsSubsystemAvailable" }, // 3377239546
		{ &Z_Construct_UFunction_UNPCSubsystemComponent_ShutdownSubsystem, "ShutdownSubsystem" }, // 3003275235
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNPCSubsystemComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UNPCSubsystemComponent_Statics

// ********** Begin Class UNPCSubsystemComponent Property Definitions ******************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNPCSubsystemComponent_Statics::NewProp_SubsystemName = { "SubsystemName", nullptr, (EPropertyFlags)0x0020080000010001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNPCSubsystemComponent, SubsystemName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SubsystemName_MetaData), NewProp_SubsystemName_MetaData) };
void Z_Construct_UClass_UNPCSubsystemComponent_Statics::NewProp_bIsInitialized_SetBit(void* Obj)
{
	((UNPCSubsystemComponent*)Obj)->bIsInitialized = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UNPCSubsystemComponent_Statics::NewProp_bIsInitialized = { "bIsInitialized", nullptr, (EPropertyFlags)0x0020080000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UNPCSubsystemComponent), &Z_Construct_UClass_UNPCSubsystemComponent_Statics::NewProp_bIsInitialized_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsInitialized_MetaData), NewProp_bIsInitialized_MetaData) };
void Z_Construct_UClass_UNPCSubsystemComponent_Statics::NewProp_bIsAvailable_SetBit(void* Obj)
{
	((UNPCSubsystemComponent*)Obj)->bIsAvailable = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UNPCSubsystemComponent_Statics::NewProp_bIsAvailable = { "bIsAvailable", nullptr, (EPropertyFlags)0x0020080000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UNPCSubsystemComponent), &Z_Construct_UClass_UNPCSubsystemComponent_Statics::NewProp_bIsAvailable_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsAvailable_MetaData), NewProp_bIsAvailable_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UNPCSubsystemComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCSubsystemComponent_Statics::NewProp_SubsystemName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCSubsystemComponent_Statics::NewProp_bIsInitialized,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCSubsystemComponent_Statics::NewProp_bIsAvailable,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNPCSubsystemComponent_Statics::PropPointers) < 2048);
// ********** End Class UNPCSubsystemComponent Property Definitions ********************************
UObject* (*const Z_Construct_UClass_UNPCSubsystemComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNPCSubsystemComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UNPCSubsystemComponent_Statics::ClassParams = {
	&UNPCSubsystemComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UNPCSubsystemComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UNPCSubsystemComponent_Statics::PropPointers),
	0,
	0x00B000A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNPCSubsystemComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UNPCSubsystemComponent_Statics::Class_MetaDataParams)
};
void UNPCSubsystemComponent::StaticRegisterNativesUNPCSubsystemComponent()
{
	UClass* Class = UNPCSubsystemComponent::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UNPCSubsystemComponent_Statics::Funcs));
}
UClass* Z_Construct_UClass_UNPCSubsystemComponent()
{
	if (!Z_Registration_Info_UClass_UNPCSubsystemComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNPCSubsystemComponent.OuterSingleton, Z_Construct_UClass_UNPCSubsystemComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UNPCSubsystemComponent.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UNPCSubsystemComponent);
UNPCSubsystemComponent::~UNPCSubsystemComponent() {}
// ********** End Class UNPCSubsystemComponent *****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCSubsystemComponent_h__Script_LLM_NPC_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNPCSubsystemComponent, UNPCSubsystemComponent::StaticClass, TEXT("UNPCSubsystemComponent"), &Z_Registration_Info_UClass_UNPCSubsystemComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNPCSubsystemComponent), 1574607394U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCSubsystemComponent_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCSubsystemComponent_h__Script_LLM_NPC_2793120640{
	TEXT("/Script/LLM_NPC"),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCSubsystemComponent_h__Script_LLM_NPC_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCSubsystemComponent_h__Script_LLM_NPC_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
