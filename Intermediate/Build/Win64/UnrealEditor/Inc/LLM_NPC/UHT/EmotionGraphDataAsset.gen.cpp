// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Emotion/EmotionGraphDataAsset.h"
#include "LLM_NPC/Core/NPCTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeEmotionGraphDataAsset() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UDataAsset();
LLM_NPC_API UClass* Z_Construct_UClass_UEmotionGraphDataAsset();
LLM_NPC_API UClass* Z_Construct_UClass_UEmotionGraphDataAsset_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UEmotionStateMachine_NoRegister();
LLM_NPC_API UEnum* Z_Construct_UEnum_LLM_NPC_EEmotionType();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FEmotionEdgeConfig();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FEmotionNodeConfig();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FPADVector();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FEmotionNodeConfig ************************************************
struct Z_Construct_UScriptStruct_FEmotionNodeConfig_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FEmotionNodeConfig); }
	static inline consteval int16 GetStructAlignment() { return alignof(FEmotionNodeConfig); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Configuration for a single node in the emotion graph.\n * Each node represents one emotion type with optional overrides.\n */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionGraphDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Configuration for a single node in the emotion graph.\nEach node represents one emotion type with optional overrides." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EmotionType_MetaData[] = {
		{ "Category", "Emotion|Graph" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The emotion type this node represents. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionGraphDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The emotion type this node represents." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseCustomPAD_MetaData[] = {
		{ "Category", "Emotion|Graph" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** If true, use CustomPAD instead of the canonical PAD for this emotion. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionGraphDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If true, use CustomPAD instead of the canonical PAD for this emotion." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CustomPAD_MetaData[] = {
		{ "Category", "Emotion|Graph" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Custom PAD override for this emotion node. Only used if bUseCustomPAD is true. */" },
#endif
		{ "EditCondition", "bUseCustomPAD" },
		{ "ModuleRelativePath", "Emotion/EmotionGraphDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Custom PAD override for this emotion node. Only used if bUseCustomPAD is true." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CustomDecayRate_MetaData[] = {
		{ "Category", "Emotion|Graph" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Custom decay rate override. 0 means use the default from NPCConfig. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionGraphDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Custom decay rate override. 0 means use the default from NPCConfig." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FEmotionNodeConfig constinit property declarations ****************
	static const UECodeGen_Private::FBytePropertyParams NewProp_EmotionType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_EmotionType;
	static void NewProp_bUseCustomPAD_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseCustomPAD;
	static const UECodeGen_Private::FStructPropertyParams NewProp_CustomPAD;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CustomDecayRate;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FEmotionNodeConfig constinit property declarations ******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FEmotionNodeConfig>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FEmotionNodeConfig_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FEmotionNodeConfig;
class UScriptStruct* FEmotionNodeConfig::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FEmotionNodeConfig.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FEmotionNodeConfig.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FEmotionNodeConfig, (UObject*)Z_Construct_UPackage__Script_LLM_NPC(), TEXT("EmotionNodeConfig"));
	}
	return Z_Registration_Info_UScriptStruct_FEmotionNodeConfig.OuterSingleton;
	}

// ********** Begin ScriptStruct FEmotionNodeConfig Property Definitions ***************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FEmotionNodeConfig_Statics::NewProp_EmotionType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FEmotionNodeConfig_Statics::NewProp_EmotionType = { "EmotionType", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEmotionNodeConfig, EmotionType), Z_Construct_UEnum_LLM_NPC_EEmotionType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EmotionType_MetaData), NewProp_EmotionType_MetaData) }; // 1184287893
void Z_Construct_UScriptStruct_FEmotionNodeConfig_Statics::NewProp_bUseCustomPAD_SetBit(void* Obj)
{
	((FEmotionNodeConfig*)Obj)->bUseCustomPAD = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FEmotionNodeConfig_Statics::NewProp_bUseCustomPAD = { "bUseCustomPAD", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FEmotionNodeConfig), &Z_Construct_UScriptStruct_FEmotionNodeConfig_Statics::NewProp_bUseCustomPAD_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseCustomPAD_MetaData), NewProp_bUseCustomPAD_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FEmotionNodeConfig_Statics::NewProp_CustomPAD = { "CustomPAD", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEmotionNodeConfig, CustomPAD), Z_Construct_UScriptStruct_FPADVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CustomPAD_MetaData), NewProp_CustomPAD_MetaData) }; // 3806868039
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEmotionNodeConfig_Statics::NewProp_CustomDecayRate = { "CustomDecayRate", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEmotionNodeConfig, CustomDecayRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CustomDecayRate_MetaData), NewProp_CustomDecayRate_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FEmotionNodeConfig_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionNodeConfig_Statics::NewProp_EmotionType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionNodeConfig_Statics::NewProp_EmotionType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionNodeConfig_Statics::NewProp_bUseCustomPAD,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionNodeConfig_Statics::NewProp_CustomPAD,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionNodeConfig_Statics::NewProp_CustomDecayRate,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEmotionNodeConfig_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FEmotionNodeConfig Property Definitions *****************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FEmotionNodeConfig_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
	nullptr,
	&NewStructOps,
	"EmotionNodeConfig",
	Z_Construct_UScriptStruct_FEmotionNodeConfig_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEmotionNodeConfig_Statics::PropPointers),
	sizeof(FEmotionNodeConfig),
	alignof(FEmotionNodeConfig),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEmotionNodeConfig_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FEmotionNodeConfig_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FEmotionNodeConfig()
{
	if (!Z_Registration_Info_UScriptStruct_FEmotionNodeConfig.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FEmotionNodeConfig.InnerSingleton, Z_Construct_UScriptStruct_FEmotionNodeConfig_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FEmotionNodeConfig.InnerSingleton);
}
// ********** End ScriptStruct FEmotionNodeConfig **************************************************

// ********** Begin ScriptStruct FEmotionEdgeConfig ************************************************
struct Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FEmotionEdgeConfig); }
	static inline consteval int16 GetStructAlignment() { return alignof(FEmotionEdgeConfig); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Configuration for a single edge (transition) in the emotion graph.\n * Connects a source emotion to a target emotion with conditions and cost.\n */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionGraphDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Configuration for a single edge (transition) in the emotion graph.\nConnects a source emotion to a target emotion with conditions and cost." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SourceEmotion_MetaData[] = {
		{ "Category", "Emotion|Graph" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The source emotion state this edge originates from. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionGraphDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The source emotion state this edge originates from." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetEmotion_MetaData[] = {
		{ "Category", "Emotion|Graph" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The target emotion state this edge leads to. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionGraphDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The target emotion state this edge leads to." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinInputStrength_MetaData[] = {
		{ "Category", "Emotion|Graph" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Minimum signal strength required for this transition. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionGraphDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Minimum signal strength required for this transition." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RequiredKeywords_MetaData[] = {
		{ "Category", "Emotion|Graph" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Keywords required in the signal source for this transition. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionGraphDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Keywords required in the signal source for this transition." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Cost_MetaData[] = {
		{ "Category", "Emotion|Graph" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Base transition cost for A*-like search. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionGraphDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Base transition cost for A*-like search." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Cooldown_MetaData[] = {
		{ "Category", "Emotion|Graph" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Cooldown time in seconds between firings of this edge. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionGraphDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Cooldown time in seconds between firings of this edge." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FEmotionEdgeConfig constinit property declarations ****************
	static const UECodeGen_Private::FBytePropertyParams NewProp_SourceEmotion_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_SourceEmotion;
	static const UECodeGen_Private::FBytePropertyParams NewProp_TargetEmotion_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_TargetEmotion;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MinInputStrength;
	static const UECodeGen_Private::FStrPropertyParams NewProp_RequiredKeywords_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_RequiredKeywords;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Cost;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Cooldown;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FEmotionEdgeConfig constinit property declarations ******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FEmotionEdgeConfig>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FEmotionEdgeConfig;
class UScriptStruct* FEmotionEdgeConfig::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FEmotionEdgeConfig.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FEmotionEdgeConfig.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FEmotionEdgeConfig, (UObject*)Z_Construct_UPackage__Script_LLM_NPC(), TEXT("EmotionEdgeConfig"));
	}
	return Z_Registration_Info_UScriptStruct_FEmotionEdgeConfig.OuterSingleton;
	}

// ********** Begin ScriptStruct FEmotionEdgeConfig Property Definitions ***************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics::NewProp_SourceEmotion_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics::NewProp_SourceEmotion = { "SourceEmotion", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEmotionEdgeConfig, SourceEmotion), Z_Construct_UEnum_LLM_NPC_EEmotionType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SourceEmotion_MetaData), NewProp_SourceEmotion_MetaData) }; // 1184287893
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics::NewProp_TargetEmotion_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics::NewProp_TargetEmotion = { "TargetEmotion", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEmotionEdgeConfig, TargetEmotion), Z_Construct_UEnum_LLM_NPC_EEmotionType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetEmotion_MetaData), NewProp_TargetEmotion_MetaData) }; // 1184287893
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics::NewProp_MinInputStrength = { "MinInputStrength", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEmotionEdgeConfig, MinInputStrength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinInputStrength_MetaData), NewProp_MinInputStrength_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics::NewProp_RequiredKeywords_Inner = { "RequiredKeywords", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics::NewProp_RequiredKeywords = { "RequiredKeywords", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEmotionEdgeConfig, RequiredKeywords), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RequiredKeywords_MetaData), NewProp_RequiredKeywords_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics::NewProp_Cost = { "Cost", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEmotionEdgeConfig, Cost), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Cost_MetaData), NewProp_Cost_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics::NewProp_Cooldown = { "Cooldown", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEmotionEdgeConfig, Cooldown), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Cooldown_MetaData), NewProp_Cooldown_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics::NewProp_SourceEmotion_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics::NewProp_SourceEmotion,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics::NewProp_TargetEmotion_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics::NewProp_TargetEmotion,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics::NewProp_MinInputStrength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics::NewProp_RequiredKeywords_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics::NewProp_RequiredKeywords,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics::NewProp_Cost,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics::NewProp_Cooldown,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FEmotionEdgeConfig Property Definitions *****************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
	nullptr,
	&NewStructOps,
	"EmotionEdgeConfig",
	Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics::PropPointers),
	sizeof(FEmotionEdgeConfig),
	alignof(FEmotionEdgeConfig),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FEmotionEdgeConfig()
{
	if (!Z_Registration_Info_UScriptStruct_FEmotionEdgeConfig.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FEmotionEdgeConfig.InnerSingleton, Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FEmotionEdgeConfig.InnerSingleton);
}
// ********** End ScriptStruct FEmotionEdgeConfig **************************************************

// ********** Begin Class UEmotionGraphDataAsset Function CreateStateMachine ***********************
struct Z_Construct_UFunction_UEmotionGraphDataAsset_CreateStateMachine_Statics
{
	struct EmotionGraphDataAsset_eventCreateStateMachine_Parms
	{
		UObject* Outer;
		UEmotionStateMachine* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Emotion|Graph" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Instantiate a fully configured EmotionStateMachine from this data asset.\n\x09 * Creates transition rule UObjects for each edge and configures the initial state.\n\x09 * @param Outer The outer object for the created state machine and rules.\n\x09 * @return A new EmotionStateMachine instance, or nullptr if creation fails.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionGraphDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Instantiate a fully configured EmotionStateMachine from this data asset.\nCreates transition rule UObjects for each edge and configures the initial state.\n@param Outer The outer object for the created state machine and rules.\n@return A new EmotionStateMachine instance, or nullptr if creation fails." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function CreateStateMachine constinit property declarations ********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Outer;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function CreateStateMachine constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function CreateStateMachine Property Definitions *******************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UEmotionGraphDataAsset_CreateStateMachine_Statics::NewProp_Outer = { "Outer", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EmotionGraphDataAsset_eventCreateStateMachine_Parms, Outer), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UEmotionGraphDataAsset_CreateStateMachine_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EmotionGraphDataAsset_eventCreateStateMachine_Parms, ReturnValue), Z_Construct_UClass_UEmotionStateMachine_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEmotionGraphDataAsset_CreateStateMachine_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEmotionGraphDataAsset_CreateStateMachine_Statics::NewProp_Outer,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEmotionGraphDataAsset_CreateStateMachine_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionGraphDataAsset_CreateStateMachine_Statics::PropPointers) < 2048);
// ********** End Function CreateStateMachine Property Definitions *********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEmotionGraphDataAsset_CreateStateMachine_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UEmotionGraphDataAsset, nullptr, "CreateStateMachine", 	Z_Construct_UFunction_UEmotionGraphDataAsset_CreateStateMachine_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionGraphDataAsset_CreateStateMachine_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UEmotionGraphDataAsset_CreateStateMachine_Statics::EmotionGraphDataAsset_eventCreateStateMachine_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionGraphDataAsset_CreateStateMachine_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEmotionGraphDataAsset_CreateStateMachine_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UEmotionGraphDataAsset_CreateStateMachine_Statics::EmotionGraphDataAsset_eventCreateStateMachine_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UEmotionGraphDataAsset_CreateStateMachine()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEmotionGraphDataAsset_CreateStateMachine_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UEmotionGraphDataAsset::execCreateStateMachine)
{
	P_GET_OBJECT(UObject,Z_Param_Outer);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UEmotionStateMachine**)Z_Param__Result=P_THIS->CreateStateMachine(Z_Param_Outer);
	P_NATIVE_END;
}
// ********** End Class UEmotionGraphDataAsset Function CreateStateMachine *************************

// ********** Begin Class UEmotionGraphDataAsset ***************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UEmotionGraphDataAsset;
UClass* UEmotionGraphDataAsset::GetPrivateStaticClass()
{
	using TClass = UEmotionGraphDataAsset;
	if (!Z_Registration_Info_UClass_UEmotionGraphDataAsset.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("EmotionGraphDataAsset"),
			Z_Registration_Info_UClass_UEmotionGraphDataAsset.InnerSingleton,
			StaticRegisterNativesUEmotionGraphDataAsset,
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
	return Z_Registration_Info_UClass_UEmotionGraphDataAsset.InnerSingleton;
}
UClass* Z_Construct_UClass_UEmotionGraphDataAsset_NoRegister()
{
	return UEmotionGraphDataAsset::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UEmotionGraphDataAsset_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Data asset defining the complete emotion graph for an NPC archetype.\n * Serialized as nodes (emotion types) and edges (transition rules).\n *\n * Designed for future UEdGraph visual editor integration:\n * nodes map to graph editor nodes, edges map to connections.\n * At runtime, instantiates an EmotionStateMachine.\n */" },
#endif
		{ "IncludePath", "Emotion/EmotionGraphDataAsset.h" },
		{ "ModuleRelativePath", "Emotion/EmotionGraphDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Data asset defining the complete emotion graph for an NPC archetype.\nSerialized as nodes (emotion types) and edges (transition rules).\n\nDesigned for future UEdGraph visual editor integration:\nnodes map to graph editor nodes, edges map to connections.\nAt runtime, instantiates an EmotionStateMachine." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Nodes_MetaData[] = {
		{ "Category", "Emotion|Graph" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** All emotion nodes in this graph. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionGraphDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "All emotion nodes in this graph." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Edges_MetaData[] = {
		{ "Category", "Emotion|Graph" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** All transition edges in this graph. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionGraphDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "All transition edges in this graph." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultEmotion_MetaData[] = {
		{ "Category", "Emotion|Graph" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The default starting emotion for NPCs using this graph. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionGraphDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The default starting emotion for NPCs using this graph." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultIntensity_MetaData[] = {
		{ "Category", "Emotion|Graph" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Default starting intensity. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionGraphDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Default starting intensity." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UEmotionGraphDataAsset constinit property declarations *******************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Nodes_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Nodes;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Edges_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Edges;
	static const UECodeGen_Private::FBytePropertyParams NewProp_DefaultEmotion_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_DefaultEmotion;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DefaultIntensity;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UEmotionGraphDataAsset constinit property declarations *********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("CreateStateMachine"), .Pointer = &UEmotionGraphDataAsset::execCreateStateMachine },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UEmotionGraphDataAsset_CreateStateMachine, "CreateStateMachine" }, // 204657884
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UEmotionGraphDataAsset>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UEmotionGraphDataAsset_Statics

// ********** Begin Class UEmotionGraphDataAsset Property Definitions ******************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UEmotionGraphDataAsset_Statics::NewProp_Nodes_Inner = { "Nodes", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FEmotionNodeConfig, METADATA_PARAMS(0, nullptr) }; // 3302010854
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UEmotionGraphDataAsset_Statics::NewProp_Nodes = { "Nodes", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEmotionGraphDataAsset, Nodes), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Nodes_MetaData), NewProp_Nodes_MetaData) }; // 3302010854
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UEmotionGraphDataAsset_Statics::NewProp_Edges_Inner = { "Edges", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FEmotionEdgeConfig, METADATA_PARAMS(0, nullptr) }; // 217918080
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UEmotionGraphDataAsset_Statics::NewProp_Edges = { "Edges", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEmotionGraphDataAsset, Edges), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Edges_MetaData), NewProp_Edges_MetaData) }; // 217918080
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UEmotionGraphDataAsset_Statics::NewProp_DefaultEmotion_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UEmotionGraphDataAsset_Statics::NewProp_DefaultEmotion = { "DefaultEmotion", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEmotionGraphDataAsset, DefaultEmotion), Z_Construct_UEnum_LLM_NPC_EEmotionType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultEmotion_MetaData), NewProp_DefaultEmotion_MetaData) }; // 1184287893
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UEmotionGraphDataAsset_Statics::NewProp_DefaultIntensity = { "DefaultIntensity", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEmotionGraphDataAsset, DefaultIntensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultIntensity_MetaData), NewProp_DefaultIntensity_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UEmotionGraphDataAsset_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionGraphDataAsset_Statics::NewProp_Nodes_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionGraphDataAsset_Statics::NewProp_Nodes,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionGraphDataAsset_Statics::NewProp_Edges_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionGraphDataAsset_Statics::NewProp_Edges,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionGraphDataAsset_Statics::NewProp_DefaultEmotion_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionGraphDataAsset_Statics::NewProp_DefaultEmotion,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionGraphDataAsset_Statics::NewProp_DefaultIntensity,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UEmotionGraphDataAsset_Statics::PropPointers) < 2048);
// ********** End Class UEmotionGraphDataAsset Property Definitions ********************************
UObject* (*const Z_Construct_UClass_UEmotionGraphDataAsset_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDataAsset,
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UEmotionGraphDataAsset_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UEmotionGraphDataAsset_Statics::ClassParams = {
	&UEmotionGraphDataAsset::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UEmotionGraphDataAsset_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UEmotionGraphDataAsset_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UEmotionGraphDataAsset_Statics::Class_MetaDataParams), Z_Construct_UClass_UEmotionGraphDataAsset_Statics::Class_MetaDataParams)
};
void UEmotionGraphDataAsset::StaticRegisterNativesUEmotionGraphDataAsset()
{
	UClass* Class = UEmotionGraphDataAsset::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UEmotionGraphDataAsset_Statics::Funcs));
}
UClass* Z_Construct_UClass_UEmotionGraphDataAsset()
{
	if (!Z_Registration_Info_UClass_UEmotionGraphDataAsset.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UEmotionGraphDataAsset.OuterSingleton, Z_Construct_UClass_UEmotionGraphDataAsset_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UEmotionGraphDataAsset.OuterSingleton;
}
UEmotionGraphDataAsset::UEmotionGraphDataAsset(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UEmotionGraphDataAsset);
UEmotionGraphDataAsset::~UEmotionGraphDataAsset() {}
// ********** End Class UEmotionGraphDataAsset *****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGraphDataAsset_h__Script_LLM_NPC_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FEmotionNodeConfig::StaticStruct, Z_Construct_UScriptStruct_FEmotionNodeConfig_Statics::NewStructOps, TEXT("EmotionNodeConfig"),&Z_Registration_Info_UScriptStruct_FEmotionNodeConfig, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FEmotionNodeConfig), 3302010854U) },
		{ FEmotionEdgeConfig::StaticStruct, Z_Construct_UScriptStruct_FEmotionEdgeConfig_Statics::NewStructOps, TEXT("EmotionEdgeConfig"),&Z_Registration_Info_UScriptStruct_FEmotionEdgeConfig, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FEmotionEdgeConfig), 217918080U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UEmotionGraphDataAsset, UEmotionGraphDataAsset::StaticClass, TEXT("UEmotionGraphDataAsset"), &Z_Registration_Info_UClass_UEmotionGraphDataAsset, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UEmotionGraphDataAsset), 958925121U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGraphDataAsset_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGraphDataAsset_h__Script_LLM_NPC_3679380019{
	TEXT("/Script/LLM_NPC"),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGraphDataAsset_h__Script_LLM_NPC_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGraphDataAsset_h__Script_LLM_NPC_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGraphDataAsset_h__Script_LLM_NPC_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGraphDataAsset_h__Script_LLM_NPC_Statics::ScriptStructInfo),
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
