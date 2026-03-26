// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Gesture/InspectableItem.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeInspectableItem() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_AInspectableItem();
LLM_NPC_API UClass* Z_Construct_UClass_AInspectableItem_NoRegister();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AInspectableItem Function ApplyRotation **********************************
struct Z_Construct_UFunction_AInspectableItem_ApplyRotation_Statics
{
	struct InspectableItem_eventApplyRotation_Parms
	{
		FRotator RotationDelta;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Gesture|Inspect" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Apply a rotation delta to the target rotation.\n\x09 * The actual rotation is smoothly interpolated each tick.\n\x09 * @param RotationDelta  Rotation to add to the target rotation.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Gesture/InspectableItem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Apply a rotation delta to the target rotation.\nThe actual rotation is smoothly interpolated each tick.\n@param RotationDelta  Rotation to add to the target rotation." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ApplyRotation constinit property declarations *************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_RotationDelta;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ApplyRotation constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ApplyRotation Property Definitions ************************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AInspectableItem_ApplyRotation_Statics::NewProp_RotationDelta = { "RotationDelta", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(InspectableItem_eventApplyRotation_Parms, RotationDelta), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AInspectableItem_ApplyRotation_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AInspectableItem_ApplyRotation_Statics::NewProp_RotationDelta,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AInspectableItem_ApplyRotation_Statics::PropPointers) < 2048);
// ********** End Function ApplyRotation Property Definitions **************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AInspectableItem_ApplyRotation_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AInspectableItem, nullptr, "ApplyRotation", 	Z_Construct_UFunction_AInspectableItem_ApplyRotation_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AInspectableItem_ApplyRotation_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_AInspectableItem_ApplyRotation_Statics::InspectableItem_eventApplyRotation_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AInspectableItem_ApplyRotation_Statics::Function_MetaDataParams), Z_Construct_UFunction_AInspectableItem_ApplyRotation_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AInspectableItem_ApplyRotation_Statics::InspectableItem_eventApplyRotation_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AInspectableItem_ApplyRotation()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AInspectableItem_ApplyRotation_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AInspectableItem::execApplyRotation)
{
	P_GET_STRUCT(FRotator,Z_Param_RotationDelta);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ApplyRotation(Z_Param_RotationDelta);
	P_NATIVE_END;
}
// ********** End Class AInspectableItem Function ApplyRotation ************************************

// ********** Begin Class AInspectableItem Function ApplyScale *************************************
struct Z_Construct_UFunction_AInspectableItem_ApplyScale_Statics
{
	struct InspectableItem_eventApplyScale_Parms
	{
		float ScaleDelta;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Gesture|Inspect" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Apply a scale delta to the target scale.\n\x09 * Positive values scale up, negative values scale down.\n\x09 * The actual scale is smoothly interpolated each tick.\n\x09 * @param ScaleDelta  Amount to add to the target uniform scale.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Gesture/InspectableItem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Apply a scale delta to the target scale.\nPositive values scale up, negative values scale down.\nThe actual scale is smoothly interpolated each tick.\n@param ScaleDelta  Amount to add to the target uniform scale." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ApplyScale constinit property declarations ****************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ScaleDelta;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ApplyScale constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ApplyScale Property Definitions ***************************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AInspectableItem_ApplyScale_Statics::NewProp_ScaleDelta = { "ScaleDelta", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(InspectableItem_eventApplyScale_Parms, ScaleDelta), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AInspectableItem_ApplyScale_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AInspectableItem_ApplyScale_Statics::NewProp_ScaleDelta,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AInspectableItem_ApplyScale_Statics::PropPointers) < 2048);
// ********** End Function ApplyScale Property Definitions *****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AInspectableItem_ApplyScale_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AInspectableItem, nullptr, "ApplyScale", 	Z_Construct_UFunction_AInspectableItem_ApplyScale_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AInspectableItem_ApplyScale_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_AInspectableItem_ApplyScale_Statics::InspectableItem_eventApplyScale_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AInspectableItem_ApplyScale_Statics::Function_MetaDataParams), Z_Construct_UFunction_AInspectableItem_ApplyScale_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AInspectableItem_ApplyScale_Statics::InspectableItem_eventApplyScale_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AInspectableItem_ApplyScale()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AInspectableItem_ApplyScale_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AInspectableItem::execApplyScale)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_ScaleDelta);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ApplyScale(Z_Param_ScaleDelta);
	P_NATIVE_END;
}
// ********** End Class AInspectableItem Function ApplyScale ***************************************

// ********** Begin Class AInspectableItem Function ResetTransform *********************************
struct Z_Construct_UFunction_AInspectableItem_ResetTransform_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Gesture|Inspect" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Reset the item to its original transform (scale and rotation).\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Gesture/InspectableItem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Reset the item to its original transform (scale and rotation)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ResetTransform constinit property declarations ************************
// ********** End Function ResetTransform constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AInspectableItem_ResetTransform_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AInspectableItem, nullptr, "ResetTransform", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AInspectableItem_ResetTransform_Statics::Function_MetaDataParams), Z_Construct_UFunction_AInspectableItem_ResetTransform_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AInspectableItem_ResetTransform()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AInspectableItem_ResetTransform_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AInspectableItem::execResetTransform)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ResetTransform();
	P_NATIVE_END;
}
// ********** End Class AInspectableItem Function ResetTransform ***********************************

// ********** Begin Class AInspectableItem *********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_AInspectableItem;
UClass* AInspectableItem::GetPrivateStaticClass()
{
	using TClass = AInspectableItem;
	if (!Z_Registration_Info_UClass_AInspectableItem.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("InspectableItem"),
			Z_Registration_Info_UClass_AInspectableItem.InnerSingleton,
			StaticRegisterNativesAInspectableItem,
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
	return Z_Registration_Info_UClass_AInspectableItem.InnerSingleton;
}
UClass* Z_Construct_UClass_AInspectableItem_NoRegister()
{
	return AInspectableItem::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AInspectableItem_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * An inspectable 3D object rendered in the inspect viewport.\n * Supports smooth scale and rotation manipulation via spring-damper interpolation.\n * Transforms are not applied directly but interpolated each tick toward target values.\n */" },
#endif
		{ "IncludePath", "Gesture/InspectableItem.h" },
		{ "ModuleRelativePath", "Gesture/InspectableItem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "An inspectable 3D object rendered in the inspect viewport.\nSupports smooth scale and rotation manipulation via spring-damper interpolation.\nTransforms are not applied directly but interpolated each tick toward target values." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemMesh_MetaData[] = {
		{ "Category", "NPC|Gesture|Inspect" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The mesh component displayed in the inspect viewport. */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Gesture/InspectableItem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The mesh component displayed in the inspect viewport." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinScale_MetaData[] = {
		{ "Category", "NPC|Gesture|Inspect" },
		{ "ClampMin", "0.01" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Minimum allowed uniform scale. */" },
#endif
		{ "ModuleRelativePath", "Gesture/InspectableItem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Minimum allowed uniform scale." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxScale_MetaData[] = {
		{ "Category", "NPC|Gesture|Inspect" },
		{ "ClampMin", "0.1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Maximum allowed uniform scale. */" },
#endif
		{ "ModuleRelativePath", "Gesture/InspectableItem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maximum allowed uniform scale." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RotationSpeed_MetaData[] = {
		{ "Category", "NPC|Gesture|Inspect" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Base rotation speed multiplier. */" },
#endif
		{ "ModuleRelativePath", "Gesture/InspectableItem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Base rotation speed multiplier." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpringStiffness_MetaData[] = {
		{ "Category", "NPC|Gesture|Inspect|SpringDamper" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Spring stiffness for smooth interpolation toward target transforms. */" },
#endif
		{ "ModuleRelativePath", "Gesture/InspectableItem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Spring stiffness for smooth interpolation toward target transforms." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DamperCoefficient_MetaData[] = {
		{ "Category", "NPC|Gesture|Inspect|SpringDamper" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Damping coefficient for smooth interpolation. */" },
#endif
		{ "ModuleRelativePath", "Gesture/InspectableItem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Damping coefficient for smooth interpolation." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class AInspectableItem constinit property declarations *************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ItemMesh;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MinScale;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxScale;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RotationSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SpringStiffness;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DamperCoefficient;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class AInspectableItem constinit property declarations ***************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("ApplyRotation"), .Pointer = &AInspectableItem::execApplyRotation },
		{ .NameUTF8 = UTF8TEXT("ApplyScale"), .Pointer = &AInspectableItem::execApplyScale },
		{ .NameUTF8 = UTF8TEXT("ResetTransform"), .Pointer = &AInspectableItem::execResetTransform },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AInspectableItem_ApplyRotation, "ApplyRotation" }, // 740395637
		{ &Z_Construct_UFunction_AInspectableItem_ApplyScale, "ApplyScale" }, // 2651026206
		{ &Z_Construct_UFunction_AInspectableItem_ResetTransform, "ResetTransform" }, // 35515170
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AInspectableItem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_AInspectableItem_Statics

// ********** Begin Class AInspectableItem Property Definitions ************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AInspectableItem_Statics::NewProp_ItemMesh = { "ItemMesh", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInspectableItem, ItemMesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ItemMesh_MetaData), NewProp_ItemMesh_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AInspectableItem_Statics::NewProp_MinScale = { "MinScale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInspectableItem, MinScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinScale_MetaData), NewProp_MinScale_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AInspectableItem_Statics::NewProp_MaxScale = { "MaxScale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInspectableItem, MaxScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxScale_MetaData), NewProp_MaxScale_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AInspectableItem_Statics::NewProp_RotationSpeed = { "RotationSpeed", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInspectableItem, RotationSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RotationSpeed_MetaData), NewProp_RotationSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AInspectableItem_Statics::NewProp_SpringStiffness = { "SpringStiffness", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInspectableItem, SpringStiffness), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpringStiffness_MetaData), NewProp_SpringStiffness_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AInspectableItem_Statics::NewProp_DamperCoefficient = { "DamperCoefficient", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInspectableItem, DamperCoefficient), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DamperCoefficient_MetaData), NewProp_DamperCoefficient_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AInspectableItem_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInspectableItem_Statics::NewProp_ItemMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInspectableItem_Statics::NewProp_MinScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInspectableItem_Statics::NewProp_MaxScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInspectableItem_Statics::NewProp_RotationSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInspectableItem_Statics::NewProp_SpringStiffness,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInspectableItem_Statics::NewProp_DamperCoefficient,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AInspectableItem_Statics::PropPointers) < 2048);
// ********** End Class AInspectableItem Property Definitions **************************************
UObject* (*const Z_Construct_UClass_AInspectableItem_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AInspectableItem_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AInspectableItem_Statics::ClassParams = {
	&AInspectableItem::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AInspectableItem_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AInspectableItem_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AInspectableItem_Statics::Class_MetaDataParams), Z_Construct_UClass_AInspectableItem_Statics::Class_MetaDataParams)
};
void AInspectableItem::StaticRegisterNativesAInspectableItem()
{
	UClass* Class = AInspectableItem::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_AInspectableItem_Statics::Funcs));
}
UClass* Z_Construct_UClass_AInspectableItem()
{
	if (!Z_Registration_Info_UClass_AInspectableItem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AInspectableItem.OuterSingleton, Z_Construct_UClass_AInspectableItem_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AInspectableItem.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AInspectableItem);
AInspectableItem::~AInspectableItem() {}
// ********** End Class AInspectableItem ***********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_InspectableItem_h__Script_LLM_NPC_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AInspectableItem, AInspectableItem::StaticClass, TEXT("AInspectableItem"), &Z_Registration_Info_UClass_AInspectableItem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AInspectableItem), 732316474U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_InspectableItem_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_InspectableItem_h__Script_LLM_NPC_1264591357{
	TEXT("/Script/LLM_NPC"),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_InspectableItem_h__Script_LLM_NPC_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_InspectableItem_h__Script_LLM_NPC_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
