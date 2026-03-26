// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Animation/BlendShapeMappingDataAsset.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeBlendShapeMappingDataAsset() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UDataAsset();
LLM_NPC_API UClass* Z_Construct_UClass_UBlendShapeMappingDataAsset();
LLM_NPC_API UClass* Z_Construct_UClass_UBlendShapeMappingDataAsset_NoRegister();
LLM_NPC_API UEnum* Z_Construct_UEnum_LLM_NPC_EEmotionType();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FEmotionBlendShapeMapping();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FEmotionBlendShapeTarget();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FEmotionBlendShapeTarget ******************************************
struct Z_Construct_UScriptStruct_FEmotionBlendShapeTarget_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FEmotionBlendShapeTarget); }
	static inline consteval int16 GetStructAlignment() { return alignof(FEmotionBlendShapeTarget); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * A single blend shape target: the name of the morph target and the value it\n * should be driven toward (0-1).\n */" },
#endif
		{ "ModuleRelativePath", "Animation/BlendShapeMappingDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A single blend shape target: the name of the morph target and the value it\nshould be driven toward (0-1)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BlendShapeName_MetaData[] = {
		{ "Category", "Animation|BlendShape" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Name of the morph target on the skeletal mesh (e.g. \"browInnerUp\"). */" },
#endif
		{ "ModuleRelativePath", "Animation/BlendShapeMappingDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Name of the morph target on the skeletal mesh (e.g. \"browInnerUp\")." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetValue_MetaData[] = {
		{ "Category", "Animation|BlendShape" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Target value to drive the morph target toward (0.0 - 1.0). */" },
#endif
		{ "ModuleRelativePath", "Animation/BlendShapeMappingDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Target value to drive the morph target toward (0.0 - 1.0)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FEmotionBlendShapeTarget constinit property declarations **********
	static const UECodeGen_Private::FNamePropertyParams NewProp_BlendShapeName;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TargetValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FEmotionBlendShapeTarget constinit property declarations ************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FEmotionBlendShapeTarget>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FEmotionBlendShapeTarget_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FEmotionBlendShapeTarget;
class UScriptStruct* FEmotionBlendShapeTarget::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FEmotionBlendShapeTarget.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FEmotionBlendShapeTarget.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FEmotionBlendShapeTarget, (UObject*)Z_Construct_UPackage__Script_LLM_NPC(), TEXT("EmotionBlendShapeTarget"));
	}
	return Z_Registration_Info_UScriptStruct_FEmotionBlendShapeTarget.OuterSingleton;
	}

// ********** Begin ScriptStruct FEmotionBlendShapeTarget Property Definitions *********************
const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FEmotionBlendShapeTarget_Statics::NewProp_BlendShapeName = { "BlendShapeName", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEmotionBlendShapeTarget, BlendShapeName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BlendShapeName_MetaData), NewProp_BlendShapeName_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEmotionBlendShapeTarget_Statics::NewProp_TargetValue = { "TargetValue", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEmotionBlendShapeTarget, TargetValue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetValue_MetaData), NewProp_TargetValue_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FEmotionBlendShapeTarget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionBlendShapeTarget_Statics::NewProp_BlendShapeName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionBlendShapeTarget_Statics::NewProp_TargetValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEmotionBlendShapeTarget_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FEmotionBlendShapeTarget Property Definitions ***********************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FEmotionBlendShapeTarget_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
	nullptr,
	&NewStructOps,
	"EmotionBlendShapeTarget",
	Z_Construct_UScriptStruct_FEmotionBlendShapeTarget_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEmotionBlendShapeTarget_Statics::PropPointers),
	sizeof(FEmotionBlendShapeTarget),
	alignof(FEmotionBlendShapeTarget),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEmotionBlendShapeTarget_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FEmotionBlendShapeTarget_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FEmotionBlendShapeTarget()
{
	if (!Z_Registration_Info_UScriptStruct_FEmotionBlendShapeTarget.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FEmotionBlendShapeTarget.InnerSingleton, Z_Construct_UScriptStruct_FEmotionBlendShapeTarget_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FEmotionBlendShapeTarget.InnerSingleton);
}
// ********** End ScriptStruct FEmotionBlendShapeTarget ********************************************

// ********** Begin ScriptStruct FEmotionBlendShapeMapping *****************************************
struct Z_Construct_UScriptStruct_FEmotionBlendShapeMapping_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FEmotionBlendShapeMapping); }
	static inline consteval int16 GetStructAlignment() { return alignof(FEmotionBlendShapeMapping); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Maps an emotion type and intensity range to a set of blend shape targets.\n * Multiple mappings can exist for the same emotion at different intensity bands.\n */" },
#endif
		{ "ModuleRelativePath", "Animation/BlendShapeMappingDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maps an emotion type and intensity range to a set of blend shape targets.\nMultiple mappings can exist for the same emotion at different intensity bands." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EmotionType_MetaData[] = {
		{ "Category", "Animation|BlendShape" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The emotion type this mapping applies to. */" },
#endif
		{ "ModuleRelativePath", "Animation/BlendShapeMappingDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The emotion type this mapping applies to." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinIntensity_MetaData[] = {
		{ "Category", "Animation|BlendShape" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Minimum intensity for this mapping to activate (inclusive). */" },
#endif
		{ "ModuleRelativePath", "Animation/BlendShapeMappingDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Minimum intensity for this mapping to activate (inclusive)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxIntensity_MetaData[] = {
		{ "Category", "Animation|BlendShape" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Maximum intensity for this mapping to activate (inclusive). */" },
#endif
		{ "ModuleRelativePath", "Animation/BlendShapeMappingDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maximum intensity for this mapping to activate (inclusive)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BlendShapeTargets_MetaData[] = {
		{ "Category", "Animation|BlendShape" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Blend shape targets to drive when this mapping is active. */" },
#endif
		{ "ModuleRelativePath", "Animation/BlendShapeMappingDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Blend shape targets to drive when this mapping is active." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FEmotionBlendShapeMapping constinit property declarations *********
	static const UECodeGen_Private::FBytePropertyParams NewProp_EmotionType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_EmotionType;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MinIntensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxIntensity;
	static const UECodeGen_Private::FStructPropertyParams NewProp_BlendShapeTargets_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_BlendShapeTargets;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FEmotionBlendShapeMapping constinit property declarations ***********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FEmotionBlendShapeMapping>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FEmotionBlendShapeMapping_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FEmotionBlendShapeMapping;
class UScriptStruct* FEmotionBlendShapeMapping::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FEmotionBlendShapeMapping.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FEmotionBlendShapeMapping.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FEmotionBlendShapeMapping, (UObject*)Z_Construct_UPackage__Script_LLM_NPC(), TEXT("EmotionBlendShapeMapping"));
	}
	return Z_Registration_Info_UScriptStruct_FEmotionBlendShapeMapping.OuterSingleton;
	}

// ********** Begin ScriptStruct FEmotionBlendShapeMapping Property Definitions ********************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FEmotionBlendShapeMapping_Statics::NewProp_EmotionType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FEmotionBlendShapeMapping_Statics::NewProp_EmotionType = { "EmotionType", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEmotionBlendShapeMapping, EmotionType), Z_Construct_UEnum_LLM_NPC_EEmotionType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EmotionType_MetaData), NewProp_EmotionType_MetaData) }; // 1184287893
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEmotionBlendShapeMapping_Statics::NewProp_MinIntensity = { "MinIntensity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEmotionBlendShapeMapping, MinIntensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinIntensity_MetaData), NewProp_MinIntensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEmotionBlendShapeMapping_Statics::NewProp_MaxIntensity = { "MaxIntensity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEmotionBlendShapeMapping, MaxIntensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxIntensity_MetaData), NewProp_MaxIntensity_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FEmotionBlendShapeMapping_Statics::NewProp_BlendShapeTargets_Inner = { "BlendShapeTargets", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FEmotionBlendShapeTarget, METADATA_PARAMS(0, nullptr) }; // 557991963
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FEmotionBlendShapeMapping_Statics::NewProp_BlendShapeTargets = { "BlendShapeTargets", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEmotionBlendShapeMapping, BlendShapeTargets), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BlendShapeTargets_MetaData), NewProp_BlendShapeTargets_MetaData) }; // 557991963
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FEmotionBlendShapeMapping_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionBlendShapeMapping_Statics::NewProp_EmotionType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionBlendShapeMapping_Statics::NewProp_EmotionType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionBlendShapeMapping_Statics::NewProp_MinIntensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionBlendShapeMapping_Statics::NewProp_MaxIntensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionBlendShapeMapping_Statics::NewProp_BlendShapeTargets_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionBlendShapeMapping_Statics::NewProp_BlendShapeTargets,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEmotionBlendShapeMapping_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FEmotionBlendShapeMapping Property Definitions **********************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FEmotionBlendShapeMapping_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
	nullptr,
	&NewStructOps,
	"EmotionBlendShapeMapping",
	Z_Construct_UScriptStruct_FEmotionBlendShapeMapping_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEmotionBlendShapeMapping_Statics::PropPointers),
	sizeof(FEmotionBlendShapeMapping),
	alignof(FEmotionBlendShapeMapping),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEmotionBlendShapeMapping_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FEmotionBlendShapeMapping_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FEmotionBlendShapeMapping()
{
	if (!Z_Registration_Info_UScriptStruct_FEmotionBlendShapeMapping.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FEmotionBlendShapeMapping.InnerSingleton, Z_Construct_UScriptStruct_FEmotionBlendShapeMapping_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FEmotionBlendShapeMapping.InnerSingleton);
}
// ********** End ScriptStruct FEmotionBlendShapeMapping *******************************************

// ********** Begin Class UBlendShapeMappingDataAsset **********************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UBlendShapeMappingDataAsset;
UClass* UBlendShapeMappingDataAsset::GetPrivateStaticClass()
{
	using TClass = UBlendShapeMappingDataAsset;
	if (!Z_Registration_Info_UClass_UBlendShapeMappingDataAsset.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("BlendShapeMappingDataAsset"),
			Z_Registration_Info_UClass_UBlendShapeMappingDataAsset.InnerSingleton,
			StaticRegisterNativesUBlendShapeMappingDataAsset,
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
	return Z_Registration_Info_UClass_UBlendShapeMappingDataAsset.InnerSingleton;
}
UClass* Z_Construct_UClass_UBlendShapeMappingDataAsset_NoRegister()
{
	return UBlendShapeMappingDataAsset::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UBlendShapeMappingDataAsset_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Data asset that maps NPC emotion states to Metahuman facial blend shapes.\n * Designers configure one per character or share across archetypes with similar rigs.\n */" },
#endif
		{ "IncludePath", "Animation/BlendShapeMappingDataAsset.h" },
		{ "ModuleRelativePath", "Animation/BlendShapeMappingDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Data asset that maps NPC emotion states to Metahuman facial blend shapes.\nDesigners configure one per character or share across archetypes with similar rigs." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Mappings_MetaData[] = {
		{ "Category", "Animation|BlendShape" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** All emotion-to-blend-shape mappings. */" },
#endif
		{ "ModuleRelativePath", "Animation/BlendShapeMappingDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "All emotion-to-blend-shape mappings." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UBlendShapeMappingDataAsset constinit property declarations **************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Mappings_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Mappings;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UBlendShapeMappingDataAsset constinit property declarations ****************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBlendShapeMappingDataAsset>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UBlendShapeMappingDataAsset_Statics

// ********** Begin Class UBlendShapeMappingDataAsset Property Definitions *************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBlendShapeMappingDataAsset_Statics::NewProp_Mappings_Inner = { "Mappings", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FEmotionBlendShapeMapping, METADATA_PARAMS(0, nullptr) }; // 624653367
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UBlendShapeMappingDataAsset_Statics::NewProp_Mappings = { "Mappings", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBlendShapeMappingDataAsset, Mappings), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Mappings_MetaData), NewProp_Mappings_MetaData) }; // 624653367
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBlendShapeMappingDataAsset_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBlendShapeMappingDataAsset_Statics::NewProp_Mappings_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBlendShapeMappingDataAsset_Statics::NewProp_Mappings,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBlendShapeMappingDataAsset_Statics::PropPointers) < 2048);
// ********** End Class UBlendShapeMappingDataAsset Property Definitions ***************************
UObject* (*const Z_Construct_UClass_UBlendShapeMappingDataAsset_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDataAsset,
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBlendShapeMappingDataAsset_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UBlendShapeMappingDataAsset_Statics::ClassParams = {
	&UBlendShapeMappingDataAsset::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UBlendShapeMappingDataAsset_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UBlendShapeMappingDataAsset_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBlendShapeMappingDataAsset_Statics::Class_MetaDataParams), Z_Construct_UClass_UBlendShapeMappingDataAsset_Statics::Class_MetaDataParams)
};
void UBlendShapeMappingDataAsset::StaticRegisterNativesUBlendShapeMappingDataAsset()
{
}
UClass* Z_Construct_UClass_UBlendShapeMappingDataAsset()
{
	if (!Z_Registration_Info_UClass_UBlendShapeMappingDataAsset.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBlendShapeMappingDataAsset.OuterSingleton, Z_Construct_UClass_UBlendShapeMappingDataAsset_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UBlendShapeMappingDataAsset.OuterSingleton;
}
UBlendShapeMappingDataAsset::UBlendShapeMappingDataAsset(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UBlendShapeMappingDataAsset);
UBlendShapeMappingDataAsset::~UBlendShapeMappingDataAsset() {}
// ********** End Class UBlendShapeMappingDataAsset ************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Animation_BlendShapeMappingDataAsset_h__Script_LLM_NPC_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FEmotionBlendShapeTarget::StaticStruct, Z_Construct_UScriptStruct_FEmotionBlendShapeTarget_Statics::NewStructOps, TEXT("EmotionBlendShapeTarget"),&Z_Registration_Info_UScriptStruct_FEmotionBlendShapeTarget, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FEmotionBlendShapeTarget), 557991963U) },
		{ FEmotionBlendShapeMapping::StaticStruct, Z_Construct_UScriptStruct_FEmotionBlendShapeMapping_Statics::NewStructOps, TEXT("EmotionBlendShapeMapping"),&Z_Registration_Info_UScriptStruct_FEmotionBlendShapeMapping, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FEmotionBlendShapeMapping), 624653367U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBlendShapeMappingDataAsset, UBlendShapeMappingDataAsset::StaticClass, TEXT("UBlendShapeMappingDataAsset"), &Z_Registration_Info_UClass_UBlendShapeMappingDataAsset, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBlendShapeMappingDataAsset), 926131708U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Animation_BlendShapeMappingDataAsset_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Animation_BlendShapeMappingDataAsset_h__Script_LLM_NPC_3152431838{
	TEXT("/Script/LLM_NPC"),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Animation_BlendShapeMappingDataAsset_h__Script_LLM_NPC_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Animation_BlendShapeMappingDataAsset_h__Script_LLM_NPC_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Animation_BlendShapeMappingDataAsset_h__Script_LLM_NPC_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Animation_BlendShapeMappingDataAsset_h__Script_LLM_NPC_Statics::ScriptStructInfo),
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
