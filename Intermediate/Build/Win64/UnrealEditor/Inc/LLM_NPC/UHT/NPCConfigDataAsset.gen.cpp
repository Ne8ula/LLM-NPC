// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Core/NPCConfigDataAsset.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeNPCConfigDataAsset() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UPrimaryDataAsset();
LLM_NPC_API UClass* Z_Construct_UClass_UBlendShapeMappingDataAsset_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UEmotionGraphDataAsset_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UInventoryDataAsset_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UNPCConfigDataAsset();
LLM_NPC_API UClass* Z_Construct_UClass_UNPCConfigDataAsset_NoRegister();
LLM_NPC_API UEnum* Z_Construct_UEnum_LLM_NPC_EEmotionType();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UNPCConfigDataAsset ******************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UNPCConfigDataAsset;
UClass* UNPCConfigDataAsset::GetPrivateStaticClass()
{
	using TClass = UNPCConfigDataAsset;
	if (!Z_Registration_Info_UClass_UNPCConfigDataAsset.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("NPCConfigDataAsset"),
			Z_Registration_Info_UClass_UNPCConfigDataAsset.InnerSingleton,
			StaticRegisterNativesUNPCConfigDataAsset,
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
	return Z_Registration_Info_UClass_UNPCConfigDataAsset.InnerSingleton;
}
UClass* Z_Construct_UClass_UNPCConfigDataAsset_NoRegister()
{
	return UNPCConfigDataAsset::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UNPCConfigDataAsset_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Data asset defining an NPC archetype's personality, system prompt, and configuration.\n * One per NPC type (e.g., DA_NPC_Healer, DA_NPC_Merchant).\n * Designed to be created by designers with zero code changes.\n *\n * This is the primary configuration point for procedural NPC generation:\n * at runtime, fields can be populated from templates and personality parameters.\n */" },
#endif
		{ "IncludePath", "Core/NPCConfigDataAsset.h" },
		{ "ModuleRelativePath", "Core/NPCConfigDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Data asset defining an NPC archetype's personality, system prompt, and configuration.\nOne per NPC type (e.g., DA_NPC_Healer, DA_NPC_Merchant).\nDesigned to be created by designers with zero code changes.\n\nThis is the primary configuration point for procedural NPC generation:\nat runtime, fields can be populated from templates and personality parameters." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NPCName_MetaData[] = {
		{ "Category", "NPC|Identity" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Display name of this NPC archetype. */" },
#endif
		{ "ModuleRelativePath", "Core/NPCConfigDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Display name of this NPC archetype." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NPCDescription_MetaData[] = {
		{ "Category", "NPC|Identity" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Short description of the NPC's role and personality. */" },
#endif
		{ "ModuleRelativePath", "Core/NPCConfigDataAsset.h" },
		{ "MultiLine", "TRUE" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Short description of the NPC's role and personality." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SystemPrompt_MetaData[] = {
		{ "Category", "NPC|Dialogue" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * The system prompt sent to Claude API.\n\x09 * Establishes the \"Magic Circle\" \xe2\x80\x94 NPC exists entirely within the fiction.\n\x09 * Should include: world lore, NPC personality, behavioral rules, response format.\n\x09 *\n\x09 * Leverages the ELIZA Effect: instruct Claude to maintain consistent emotional\n\x09 * personality, reference prior context, and express genuine-seeming reactions.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Core/NPCConfigDataAsset.h" },
		{ "MultiLine", "TRUE" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The system prompt sent to Claude API.\nEstablishes the \"Magic Circle\" \xe2\x80\x94 NPC exists entirely within the fiction.\nShould include: world lore, NPC personality, behavioral rules, response format.\n\nLeverages the ELIZA Effect: instruct Claude to maintain consistent emotional\npersonality, reference prior context, and express genuine-seeming reactions." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxConversationHistory_MetaData[] = {
		{ "Category", "NPC|Dialogue" },
		{ "ClampMax", "50" },
		{ "ClampMin", "1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Maximum number of conversation history messages to include in context. */" },
#endif
		{ "ModuleRelativePath", "Core/NPCConfigDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maximum number of conversation history messages to include in context." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClaudeModelID_MetaData[] = {
		{ "Category", "NPC|Dialogue" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Claude model ID to use (e.g., \"claude-sonnet-4-6\"). */" },
#endif
		{ "ModuleRelativePath", "Core/NPCConfigDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Claude model ID to use (e.g., \"claude-sonnet-4-6\")." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxResponseTokens_MetaData[] = {
		{ "Category", "NPC|Dialogue" },
		{ "ClampMax", "4096" },
		{ "ClampMin", "64" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Max tokens for Claude response. */" },
#endif
		{ "ModuleRelativePath", "Core/NPCConfigDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max tokens for Claude response." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ElevenLabsVoiceID_MetaData[] = {
		{ "Category", "NPC|Voice" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** ElevenLabs voice ID for TTS output. */" },
#endif
		{ "ModuleRelativePath", "Core/NPCConfigDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "ElevenLabs voice ID for TTS output." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VoiceStability_MetaData[] = {
		{ "Category", "NPC|Voice" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Voice stability (0.0 to 1.0). Higher = more consistent. */" },
#endif
		{ "ModuleRelativePath", "Core/NPCConfigDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Voice stability (0.0 to 1.0). Higher = more consistent." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VoiceSimilarityBoost_MetaData[] = {
		{ "Category", "NPC|Voice" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Voice similarity boost (0.0 to 1.0). */" },
#endif
		{ "ModuleRelativePath", "Core/NPCConfigDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Voice similarity boost (0.0 to 1.0)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultEmotion_MetaData[] = {
		{ "Category", "NPC|Emotion" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Default starting emotion for this NPC. */" },
#endif
		{ "ModuleRelativePath", "Core/NPCConfigDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Default starting emotion for this NPC." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultIntensity_MetaData[] = {
		{ "Category", "NPC|Emotion" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Default starting intensity. */" },
#endif
		{ "ModuleRelativePath", "Core/NPCConfigDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Default starting intensity." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EmotionDecayRate_MetaData[] = {
		{ "Category", "NPC|Emotion" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Emotion decay rate per second. When no input signals arrive,\n\x09 * intensity decays toward 0 at this rate.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Core/NPCConfigDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Emotion decay rate per second. When no input signals arrive,\nintensity decays toward 0 at this rate." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NeutralThreshold_MetaData[] = {
		{ "Category", "NPC|Emotion" },
		{ "ClampMax", "0.5" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Intensity threshold below which the NPC transitions to Neutral.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Core/NPCConfigDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Intensity threshold below which the NPC transitions to Neutral." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EmotionTransitionCosts_MetaData[] = {
		{ "Category", "NPC|Emotion" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Per-emotion transition cost multipliers for GOAP-inspired planning.\n\x09 * Higher cost = harder for this NPC to reach that emotion.\n\x09 * E.g., a \"stoic\" NPC has high cost for Sadness, low cost for Neutral.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Core/NPCConfigDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Per-emotion transition cost multipliers for GOAP-inspired planning.\nHigher cost = harder for this NPC to reach that emotion.\nE.g., a \"stoic\" NPC has high cost for Sadness, low cost for Neutral." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EmotionGraphAsset_MetaData[] = {
		{ "Category", "NPC|References" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Emotion graph data asset for this NPC's state machine. */" },
#endif
		{ "ModuleRelativePath", "Core/NPCConfigDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Emotion graph data asset for this NPC's state machine." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InventoryAsset_MetaData[] = {
		{ "Category", "NPC|References" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Inventory data asset for this NPC's hidden items. */" },
#endif
		{ "ModuleRelativePath", "Core/NPCConfigDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Inventory data asset for this NPC's hidden items." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BlendShapeMapAsset_MetaData[] = {
		{ "Category", "NPC|References" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Blend shape mapping data asset for Metahuman animation. */" },
#endif
		{ "ModuleRelativePath", "Core/NPCConfigDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Blend shape mapping data asset for Metahuman animation." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UNPCConfigDataAsset constinit property declarations **********************
	static const UECodeGen_Private::FTextPropertyParams NewProp_NPCName;
	static const UECodeGen_Private::FTextPropertyParams NewProp_NPCDescription;
	static const UECodeGen_Private::FStrPropertyParams NewProp_SystemPrompt;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxConversationHistory;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ClaudeModelID;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxResponseTokens;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ElevenLabsVoiceID;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_VoiceStability;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_VoiceSimilarityBoost;
	static const UECodeGen_Private::FBytePropertyParams NewProp_DefaultEmotion_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_DefaultEmotion;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DefaultIntensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_EmotionDecayRate;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NeutralThreshold;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_EmotionTransitionCosts_ValueProp;
	static const UECodeGen_Private::FBytePropertyParams NewProp_EmotionTransitionCosts_Key_KeyProp_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_EmotionTransitionCosts_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_EmotionTransitionCosts;
	static const UECodeGen_Private::FSoftObjectPropertyParams NewProp_EmotionGraphAsset;
	static const UECodeGen_Private::FSoftObjectPropertyParams NewProp_InventoryAsset;
	static const UECodeGen_Private::FSoftObjectPropertyParams NewProp_BlendShapeMapAsset;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UNPCConfigDataAsset constinit property declarations ************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNPCConfigDataAsset>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UNPCConfigDataAsset_Statics

// ********** Begin Class UNPCConfigDataAsset Property Definitions *********************************
const UECodeGen_Private::FTextPropertyParams Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_NPCName = { "NPCName", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNPCConfigDataAsset, NPCName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NPCName_MetaData), NewProp_NPCName_MetaData) };
const UECodeGen_Private::FTextPropertyParams Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_NPCDescription = { "NPCDescription", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNPCConfigDataAsset, NPCDescription), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NPCDescription_MetaData), NewProp_NPCDescription_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_SystemPrompt = { "SystemPrompt", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNPCConfigDataAsset, SystemPrompt), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SystemPrompt_MetaData), NewProp_SystemPrompt_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_MaxConversationHistory = { "MaxConversationHistory", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNPCConfigDataAsset, MaxConversationHistory), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxConversationHistory_MetaData), NewProp_MaxConversationHistory_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_ClaudeModelID = { "ClaudeModelID", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNPCConfigDataAsset, ClaudeModelID), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClaudeModelID_MetaData), NewProp_ClaudeModelID_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_MaxResponseTokens = { "MaxResponseTokens", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNPCConfigDataAsset, MaxResponseTokens), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxResponseTokens_MetaData), NewProp_MaxResponseTokens_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_ElevenLabsVoiceID = { "ElevenLabsVoiceID", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNPCConfigDataAsset, ElevenLabsVoiceID), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ElevenLabsVoiceID_MetaData), NewProp_ElevenLabsVoiceID_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_VoiceStability = { "VoiceStability", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNPCConfigDataAsset, VoiceStability), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VoiceStability_MetaData), NewProp_VoiceStability_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_VoiceSimilarityBoost = { "VoiceSimilarityBoost", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNPCConfigDataAsset, VoiceSimilarityBoost), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VoiceSimilarityBoost_MetaData), NewProp_VoiceSimilarityBoost_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_DefaultEmotion_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_DefaultEmotion = { "DefaultEmotion", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNPCConfigDataAsset, DefaultEmotion), Z_Construct_UEnum_LLM_NPC_EEmotionType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultEmotion_MetaData), NewProp_DefaultEmotion_MetaData) }; // 1184287893
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_DefaultIntensity = { "DefaultIntensity", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNPCConfigDataAsset, DefaultIntensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultIntensity_MetaData), NewProp_DefaultIntensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_EmotionDecayRate = { "EmotionDecayRate", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNPCConfigDataAsset, EmotionDecayRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EmotionDecayRate_MetaData), NewProp_EmotionDecayRate_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_NeutralThreshold = { "NeutralThreshold", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNPCConfigDataAsset, NeutralThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NeutralThreshold_MetaData), NewProp_NeutralThreshold_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_EmotionTransitionCosts_ValueProp = { "EmotionTransitionCosts", nullptr, (EPropertyFlags)0x0000000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_EmotionTransitionCosts_Key_KeyProp_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_EmotionTransitionCosts_Key_KeyProp = { "EmotionTransitionCosts_Key", nullptr, (EPropertyFlags)0x0000000000000001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UEnum_LLM_NPC_EEmotionType, METADATA_PARAMS(0, nullptr) }; // 1184287893
const UECodeGen_Private::FMapPropertyParams Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_EmotionTransitionCosts = { "EmotionTransitionCosts", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNPCConfigDataAsset, EmotionTransitionCosts), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EmotionTransitionCosts_MetaData), NewProp_EmotionTransitionCosts_MetaData) }; // 1184287893
const UECodeGen_Private::FSoftObjectPropertyParams Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_EmotionGraphAsset = { "EmotionGraphAsset", nullptr, (EPropertyFlags)0x0014000000000015, UECodeGen_Private::EPropertyGenFlags::SoftObject, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNPCConfigDataAsset, EmotionGraphAsset), Z_Construct_UClass_UEmotionGraphDataAsset_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EmotionGraphAsset_MetaData), NewProp_EmotionGraphAsset_MetaData) };
const UECodeGen_Private::FSoftObjectPropertyParams Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_InventoryAsset = { "InventoryAsset", nullptr, (EPropertyFlags)0x0014000000000015, UECodeGen_Private::EPropertyGenFlags::SoftObject, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNPCConfigDataAsset, InventoryAsset), Z_Construct_UClass_UInventoryDataAsset_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InventoryAsset_MetaData), NewProp_InventoryAsset_MetaData) };
const UECodeGen_Private::FSoftObjectPropertyParams Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_BlendShapeMapAsset = { "BlendShapeMapAsset", nullptr, (EPropertyFlags)0x0014000000000015, UECodeGen_Private::EPropertyGenFlags::SoftObject, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNPCConfigDataAsset, BlendShapeMapAsset), Z_Construct_UClass_UBlendShapeMappingDataAsset_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BlendShapeMapAsset_MetaData), NewProp_BlendShapeMapAsset_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UNPCConfigDataAsset_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_NPCName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_NPCDescription,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_SystemPrompt,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_MaxConversationHistory,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_ClaudeModelID,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_MaxResponseTokens,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_ElevenLabsVoiceID,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_VoiceStability,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_VoiceSimilarityBoost,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_DefaultEmotion_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_DefaultEmotion,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_DefaultIntensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_EmotionDecayRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_NeutralThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_EmotionTransitionCosts_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_EmotionTransitionCosts_Key_KeyProp_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_EmotionTransitionCosts_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_EmotionTransitionCosts,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_EmotionGraphAsset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_InventoryAsset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCConfigDataAsset_Statics::NewProp_BlendShapeMapAsset,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNPCConfigDataAsset_Statics::PropPointers) < 2048);
// ********** End Class UNPCConfigDataAsset Property Definitions ***********************************
UObject* (*const Z_Construct_UClass_UNPCConfigDataAsset_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UPrimaryDataAsset,
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNPCConfigDataAsset_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UNPCConfigDataAsset_Statics::ClassParams = {
	&UNPCConfigDataAsset::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UNPCConfigDataAsset_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UNPCConfigDataAsset_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNPCConfigDataAsset_Statics::Class_MetaDataParams), Z_Construct_UClass_UNPCConfigDataAsset_Statics::Class_MetaDataParams)
};
void UNPCConfigDataAsset::StaticRegisterNativesUNPCConfigDataAsset()
{
}
UClass* Z_Construct_UClass_UNPCConfigDataAsset()
{
	if (!Z_Registration_Info_UClass_UNPCConfigDataAsset.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNPCConfigDataAsset.OuterSingleton, Z_Construct_UClass_UNPCConfigDataAsset_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UNPCConfigDataAsset.OuterSingleton;
}
UNPCConfigDataAsset::UNPCConfigDataAsset(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UNPCConfigDataAsset);
UNPCConfigDataAsset::~UNPCConfigDataAsset() {}
// ********** End Class UNPCConfigDataAsset ********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCConfigDataAsset_h__Script_LLM_NPC_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNPCConfigDataAsset, UNPCConfigDataAsset::StaticClass, TEXT("UNPCConfigDataAsset"), &Z_Registration_Info_UClass_UNPCConfigDataAsset, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNPCConfigDataAsset), 2013220001U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCConfigDataAsset_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCConfigDataAsset_h__Script_LLM_NPC_755277917{
	TEXT("/Script/LLM_NPC"),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCConfigDataAsset_h__Script_LLM_NPC_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCConfigDataAsset_h__Script_LLM_NPC_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
