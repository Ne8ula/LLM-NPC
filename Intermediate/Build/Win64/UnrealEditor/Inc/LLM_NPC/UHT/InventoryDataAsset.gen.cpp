// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Inventory/InventoryDataAsset.h"
#include "LLM_NPC/Inventory/InventoryTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeInventoryDataAsset() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UDataAsset();
LLM_NPC_API UClass* Z_Construct_UClass_UInventoryDataAsset();
LLM_NPC_API UClass* Z_Construct_UClass_UInventoryDataAsset_NoRegister();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FInventoryItem();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UInventoryDataAsset ******************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UInventoryDataAsset;
UClass* UInventoryDataAsset::GetPrivateStaticClass()
{
	using TClass = UInventoryDataAsset;
	if (!Z_Registration_Info_UClass_UInventoryDataAsset.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("InventoryDataAsset"),
			Z_Registration_Info_UClass_UInventoryDataAsset.InnerSingleton,
			StaticRegisterNativesUInventoryDataAsset,
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
	return Z_Registration_Info_UClass_UInventoryDataAsset.InnerSingleton;
}
UClass* Z_Construct_UClass_UInventoryDataAsset_NoRegister()
{
	return UInventoryDataAsset::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UInventoryDataAsset_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Data asset that defines the inventory catalogue for a single NPC archetype.\n * Designers author one of these per NPC to configure which items can be unlocked.\n */" },
#endif
		{ "IncludePath", "Inventory/InventoryDataAsset.h" },
		{ "ModuleRelativePath", "Inventory/InventoryDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Data asset that defines the inventory catalogue for a single NPC archetype.\nDesigners author one of these per NPC to configure which items can be unlocked." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Items_MetaData[] = {
		{ "Category", "Inventory" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** All items this NPC can potentially give to the player. */" },
#endif
		{ "ModuleRelativePath", "Inventory/InventoryDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "All items this NPC can potentially give to the player." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UInventoryDataAsset constinit property declarations **********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Items_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Items;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UInventoryDataAsset constinit property declarations ************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UInventoryDataAsset>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UInventoryDataAsset_Statics

// ********** Begin Class UInventoryDataAsset Property Definitions *********************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UInventoryDataAsset_Statics::NewProp_Items_Inner = { "Items", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FInventoryItem, METADATA_PARAMS(0, nullptr) }; // 1158787168
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UInventoryDataAsset_Statics::NewProp_Items = { "Items", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInventoryDataAsset, Items), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Items_MetaData), NewProp_Items_MetaData) }; // 1158787168
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UInventoryDataAsset_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInventoryDataAsset_Statics::NewProp_Items_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInventoryDataAsset_Statics::NewProp_Items,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UInventoryDataAsset_Statics::PropPointers) < 2048);
// ********** End Class UInventoryDataAsset Property Definitions ***********************************
UObject* (*const Z_Construct_UClass_UInventoryDataAsset_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDataAsset,
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UInventoryDataAsset_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UInventoryDataAsset_Statics::ClassParams = {
	&UInventoryDataAsset::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UInventoryDataAsset_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UInventoryDataAsset_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UInventoryDataAsset_Statics::Class_MetaDataParams), Z_Construct_UClass_UInventoryDataAsset_Statics::Class_MetaDataParams)
};
void UInventoryDataAsset::StaticRegisterNativesUInventoryDataAsset()
{
}
UClass* Z_Construct_UClass_UInventoryDataAsset()
{
	if (!Z_Registration_Info_UClass_UInventoryDataAsset.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UInventoryDataAsset.OuterSingleton, Z_Construct_UClass_UInventoryDataAsset_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UInventoryDataAsset.OuterSingleton;
}
UInventoryDataAsset::UInventoryDataAsset(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UInventoryDataAsset);
UInventoryDataAsset::~UInventoryDataAsset() {}
// ********** End Class UInventoryDataAsset ********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Inventory_InventoryDataAsset_h__Script_LLM_NPC_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UInventoryDataAsset, UInventoryDataAsset::StaticClass, TEXT("UInventoryDataAsset"), &Z_Registration_Info_UClass_UInventoryDataAsset, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UInventoryDataAsset), 295430493U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Inventory_InventoryDataAsset_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Inventory_InventoryDataAsset_h__Script_LLM_NPC_4294401998{
	TEXT("/Script/LLM_NPC"),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Inventory_InventoryDataAsset_h__Script_LLM_NPC_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Inventory_InventoryDataAsset_h__Script_LLM_NPC_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
