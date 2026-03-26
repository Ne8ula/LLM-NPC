// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Animation/MetahumanAnimComponent.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeMetahumanAnimComponent() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_USkeletalMeshComponent_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UBlendShapeMappingDataAsset_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UMetahumanAnimComponent();
LLM_NPC_API UClass* Z_Construct_UClass_UMetahumanAnimComponent_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UNPCSubsystemComponent();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UMetahumanAnimComponent Function UpdateBlendShapes ***********************
struct Z_Construct_UFunction_UMetahumanAnimComponent_UpdateBlendShapes_Statics
{
	struct MetahumanAnimComponent_eventUpdateBlendShapes_Parms
	{
		float DeltaTime;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Animation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Interpolate current blend shape values toward targets.\n\x09 * Called automatically from TickComponent.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Animation/MetahumanAnimComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Interpolate current blend shape values toward targets.\nCalled automatically from TickComponent." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function UpdateBlendShapes constinit property declarations *********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DeltaTime;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function UpdateBlendShapes constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function UpdateBlendShapes Property Definitions ********************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UMetahumanAnimComponent_UpdateBlendShapes_Statics::NewProp_DeltaTime = { "DeltaTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MetahumanAnimComponent_eventUpdateBlendShapes_Parms, DeltaTime), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMetahumanAnimComponent_UpdateBlendShapes_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMetahumanAnimComponent_UpdateBlendShapes_Statics::NewProp_DeltaTime,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMetahumanAnimComponent_UpdateBlendShapes_Statics::PropPointers) < 2048);
// ********** End Function UpdateBlendShapes Property Definitions **********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMetahumanAnimComponent_UpdateBlendShapes_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UMetahumanAnimComponent, nullptr, "UpdateBlendShapes", 	Z_Construct_UFunction_UMetahumanAnimComponent_UpdateBlendShapes_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UMetahumanAnimComponent_UpdateBlendShapes_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UMetahumanAnimComponent_UpdateBlendShapes_Statics::MetahumanAnimComponent_eventUpdateBlendShapes_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMetahumanAnimComponent_UpdateBlendShapes_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMetahumanAnimComponent_UpdateBlendShapes_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UMetahumanAnimComponent_UpdateBlendShapes_Statics::MetahumanAnimComponent_eventUpdateBlendShapes_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMetahumanAnimComponent_UpdateBlendShapes()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMetahumanAnimComponent_UpdateBlendShapes_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMetahumanAnimComponent::execUpdateBlendShapes)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_DeltaTime);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->UpdateBlendShapes(Z_Param_DeltaTime);
	P_NATIVE_END;
}
// ********** End Class UMetahumanAnimComponent Function UpdateBlendShapes *************************

// ********** Begin Class UMetahumanAnimComponent **************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UMetahumanAnimComponent;
UClass* UMetahumanAnimComponent::GetPrivateStaticClass()
{
	using TClass = UMetahumanAnimComponent;
	if (!Z_Registration_Info_UClass_UMetahumanAnimComponent.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("MetahumanAnimComponent"),
			Z_Registration_Info_UClass_UMetahumanAnimComponent.InnerSingleton,
			StaticRegisterNativesUMetahumanAnimComponent,
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
	return Z_Registration_Info_UClass_UMetahumanAnimComponent.InnerSingleton;
}
UClass* Z_Construct_UClass_UMetahumanAnimComponent_NoRegister()
{
	return UMetahumanAnimComponent::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UMetahumanAnimComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "LLMNPC" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Drives Metahuman facial blend shapes based on the NPC's current emotional state.\n *\n * Each tick the component reads the current FEmotionState from the Emotion subsystem,\n * looks up the corresponding blend shape targets in the BlendShapeMappingDataAsset,\n * and smoothly interpolates the skeletal mesh's morph targets toward those values.\n */" },
#endif
		{ "IncludePath", "Animation/MetahumanAnimComponent.h" },
		{ "ModuleRelativePath", "Animation/MetahumanAnimComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Drives Metahuman facial blend shapes based on the NPC's current emotional state.\n\nEach tick the component reads the current FEmotionState from the Emotion subsystem,\nlooks up the corresponding blend shape targets in the BlendShapeMappingDataAsset,\nand smoothly interpolates the skeletal mesh's morph targets toward those values." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BlendShapeMappingAssetRef_MetaData[] = {
		{ "Category", "NPC|Animation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Data asset mapping emotions to blend shape targets. */" },
#endif
		{ "ModuleRelativePath", "Animation/MetahumanAnimComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Data asset mapping emotions to blend shape targets." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InterpolationSpeed_MetaData[] = {
		{ "Category", "NPC|Animation" },
		{ "ClampMin", "0.1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Speed of interpolation toward target blend shape values (higher = faster). */" },
#endif
		{ "ModuleRelativePath", "Animation/MetahumanAnimComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Speed of interpolation toward target blend shape values (higher = faster)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CachedSkeletalMesh_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Cached reference to the owner's skeletal mesh component (face mesh). */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Animation/MetahumanAnimComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Cached reference to the owner's skeletal mesh component (face mesh)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LoadedMappingData_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Loaded blend shape mapping data asset (runtime). */" },
#endif
		{ "ModuleRelativePath", "Animation/MetahumanAnimComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Loaded blend shape mapping data asset (runtime)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UMetahumanAnimComponent constinit property declarations ******************
	static const UECodeGen_Private::FSoftObjectPropertyParams NewProp_BlendShapeMappingAssetRef;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InterpolationSpeed;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CachedSkeletalMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LoadedMappingData;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UMetahumanAnimComponent constinit property declarations ********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("UpdateBlendShapes"), .Pointer = &UMetahumanAnimComponent::execUpdateBlendShapes },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UMetahumanAnimComponent_UpdateBlendShapes, "UpdateBlendShapes" }, // 2215229515
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMetahumanAnimComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UMetahumanAnimComponent_Statics

// ********** Begin Class UMetahumanAnimComponent Property Definitions *****************************
const UECodeGen_Private::FSoftObjectPropertyParams Z_Construct_UClass_UMetahumanAnimComponent_Statics::NewProp_BlendShapeMappingAssetRef = { "BlendShapeMappingAssetRef", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::SoftObject, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMetahumanAnimComponent, BlendShapeMappingAssetRef), Z_Construct_UClass_UBlendShapeMappingDataAsset_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BlendShapeMappingAssetRef_MetaData), NewProp_BlendShapeMappingAssetRef_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UMetahumanAnimComponent_Statics::NewProp_InterpolationSpeed = { "InterpolationSpeed", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMetahumanAnimComponent, InterpolationSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InterpolationSpeed_MetaData), NewProp_InterpolationSpeed_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMetahumanAnimComponent_Statics::NewProp_CachedSkeletalMesh = { "CachedSkeletalMesh", nullptr, (EPropertyFlags)0x0144000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMetahumanAnimComponent, CachedSkeletalMesh), Z_Construct_UClass_USkeletalMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CachedSkeletalMesh_MetaData), NewProp_CachedSkeletalMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMetahumanAnimComponent_Statics::NewProp_LoadedMappingData = { "LoadedMappingData", nullptr, (EPropertyFlags)0x0144000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMetahumanAnimComponent, LoadedMappingData), Z_Construct_UClass_UBlendShapeMappingDataAsset_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LoadedMappingData_MetaData), NewProp_LoadedMappingData_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UMetahumanAnimComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMetahumanAnimComponent_Statics::NewProp_BlendShapeMappingAssetRef,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMetahumanAnimComponent_Statics::NewProp_InterpolationSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMetahumanAnimComponent_Statics::NewProp_CachedSkeletalMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMetahumanAnimComponent_Statics::NewProp_LoadedMappingData,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMetahumanAnimComponent_Statics::PropPointers) < 2048);
// ********** End Class UMetahumanAnimComponent Property Definitions *******************************
UObject* (*const Z_Construct_UClass_UMetahumanAnimComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UNPCSubsystemComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMetahumanAnimComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UMetahumanAnimComponent_Statics::ClassParams = {
	&UMetahumanAnimComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UMetahumanAnimComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UMetahumanAnimComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMetahumanAnimComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UMetahumanAnimComponent_Statics::Class_MetaDataParams)
};
void UMetahumanAnimComponent::StaticRegisterNativesUMetahumanAnimComponent()
{
	UClass* Class = UMetahumanAnimComponent::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UMetahumanAnimComponent_Statics::Funcs));
}
UClass* Z_Construct_UClass_UMetahumanAnimComponent()
{
	if (!Z_Registration_Info_UClass_UMetahumanAnimComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMetahumanAnimComponent.OuterSingleton, Z_Construct_UClass_UMetahumanAnimComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UMetahumanAnimComponent.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UMetahumanAnimComponent);
UMetahumanAnimComponent::~UMetahumanAnimComponent() {}
// ********** End Class UMetahumanAnimComponent ****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Animation_MetahumanAnimComponent_h__Script_LLM_NPC_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UMetahumanAnimComponent, UMetahumanAnimComponent::StaticClass, TEXT("UMetahumanAnimComponent"), &Z_Registration_Info_UClass_UMetahumanAnimComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMetahumanAnimComponent), 1562001173U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Animation_MetahumanAnimComponent_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Animation_MetahumanAnimComponent_h__Script_LLM_NPC_2691220425{
	TEXT("/Script/LLM_NPC"),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Animation_MetahumanAnimComponent_h__Script_LLM_NPC_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Animation_MetahumanAnimComponent_h__Script_LLM_NPC_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
