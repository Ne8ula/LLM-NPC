// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Core/NPCTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeNPCTypes() {}

// ********** Begin Cross Module References ********************************************************
LLM_NPC_API UEnum* Z_Construct_UEnum_LLM_NPC_EDialogueInputMode();
LLM_NPC_API UEnum* Z_Construct_UEnum_LLM_NPC_EEmotionType();
LLM_NPC_API UEnum* Z_Construct_UEnum_LLM_NPC_EGestureType();
LLM_NPC_API UEnum* Z_Construct_UEnum_LLM_NPC_EManipulationInputMode();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FDetectedUserEmotion();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FEmotionSignal();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FEmotionState();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FGestureInput();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FNPCMessage();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FPADVector();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EEmotionType **************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EEmotionType;
static UEnum* EEmotionType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EEmotionType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EEmotionType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_LLM_NPC_EEmotionType, (UObject*)Z_Construct_UPackage__Script_LLM_NPC(), TEXT("EEmotionType"));
	}
	return Z_Registration_Info_UEnum_EEmotionType.OuterSingleton;
}
template<> LLM_NPC_NON_ATTRIBUTED_API UEnum* StaticEnum<EEmotionType>()
{
	return EEmotionType_StaticEnum();
}
struct Z_Construct_UEnum_LLM_NPC_EEmotionType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "Anger.DisplayName", "Anger" },
		{ "Anger.Name", "EEmotionType::Anger" },
		{ "Anticipation.DisplayName", "Anticipation" },
		{ "Anticipation.Name", "EEmotionType::Anticipation" },
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Plutchik's Wheel primary emotions + Neutral.\n * Used as discrete labels for inventory triggers, dialogue branching,\n * and Metahuman blend shape lookup.\n */" },
#endif
		{ "Disgust.DisplayName", "Disgust" },
		{ "Disgust.Name", "EEmotionType::Disgust" },
		{ "Fear.DisplayName", "Fear" },
		{ "Fear.Name", "EEmotionType::Fear" },
		{ "Joy.DisplayName", "Joy" },
		{ "Joy.Name", "EEmotionType::Joy" },
		{ "MAX.Hidden", "" },
		{ "MAX.Name", "EEmotionType::MAX" },
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
		{ "Neutral.DisplayName", "Neutral" },
		{ "Neutral.Name", "EEmotionType::Neutral" },
		{ "Sadness.DisplayName", "Sadness" },
		{ "Sadness.Name", "EEmotionType::Sadness" },
		{ "Surprise.DisplayName", "Surprise" },
		{ "Surprise.Name", "EEmotionType::Surprise" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Plutchik's Wheel primary emotions + Neutral.\nUsed as discrete labels for inventory triggers, dialogue branching,\nand Metahuman blend shape lookup." },
#endif
		{ "Trust.DisplayName", "Trust" },
		{ "Trust.Name", "EEmotionType::Trust" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EEmotionType::Neutral", (int64)EEmotionType::Neutral },
		{ "EEmotionType::Joy", (int64)EEmotionType::Joy },
		{ "EEmotionType::Sadness", (int64)EEmotionType::Sadness },
		{ "EEmotionType::Anger", (int64)EEmotionType::Anger },
		{ "EEmotionType::Fear", (int64)EEmotionType::Fear },
		{ "EEmotionType::Surprise", (int64)EEmotionType::Surprise },
		{ "EEmotionType::Disgust", (int64)EEmotionType::Disgust },
		{ "EEmotionType::Trust", (int64)EEmotionType::Trust },
		{ "EEmotionType::Anticipation", (int64)EEmotionType::Anticipation },
		{ "EEmotionType::MAX", (int64)EEmotionType::MAX },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_LLM_NPC_EEmotionType_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_LLM_NPC_EEmotionType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_LLM_NPC,
	nullptr,
	"EEmotionType",
	"EEmotionType",
	Z_Construct_UEnum_LLM_NPC_EEmotionType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_LLM_NPC_EEmotionType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_LLM_NPC_EEmotionType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_LLM_NPC_EEmotionType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_LLM_NPC_EEmotionType()
{
	if (!Z_Registration_Info_UEnum_EEmotionType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EEmotionType.InnerSingleton, Z_Construct_UEnum_LLM_NPC_EEmotionType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EEmotionType.InnerSingleton;
}
// ********** End Enum EEmotionType ****************************************************************

// ********** Begin Enum EDialogueInputMode ********************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EDialogueInputMode;
static UEnum* EDialogueInputMode_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EDialogueInputMode.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EDialogueInputMode.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_LLM_NPC_EDialogueInputMode, (UObject*)Z_Construct_UPackage__Script_LLM_NPC(), TEXT("EDialogueInputMode"));
	}
	return Z_Registration_Info_UEnum_EDialogueInputMode.OuterSingleton;
}
template<> LLM_NPC_NON_ATTRIBUTED_API UEnum* StaticEnum<EDialogueInputMode>()
{
	return EDialogueInputMode_StaticEnum();
}
struct Z_Construct_UEnum_LLM_NPC_EDialogueInputMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Input mode for dialogue interaction. */" },
#endif
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
		{ "Text.DisplayName", "Text" },
		{ "Text.Name", "EDialogueInputMode::Text" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Input mode for dialogue interaction." },
#endif
		{ "Voice.DisplayName", "Voice" },
		{ "Voice.Name", "EDialogueInputMode::Voice" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EDialogueInputMode::Voice", (int64)EDialogueInputMode::Voice },
		{ "EDialogueInputMode::Text", (int64)EDialogueInputMode::Text },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_LLM_NPC_EDialogueInputMode_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_LLM_NPC_EDialogueInputMode_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_LLM_NPC,
	nullptr,
	"EDialogueInputMode",
	"EDialogueInputMode",
	Z_Construct_UEnum_LLM_NPC_EDialogueInputMode_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_LLM_NPC_EDialogueInputMode_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_LLM_NPC_EDialogueInputMode_Statics::Enum_MetaDataParams), Z_Construct_UEnum_LLM_NPC_EDialogueInputMode_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_LLM_NPC_EDialogueInputMode()
{
	if (!Z_Registration_Info_UEnum_EDialogueInputMode.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EDialogueInputMode.InnerSingleton, Z_Construct_UEnum_LLM_NPC_EDialogueInputMode_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EDialogueInputMode.InnerSingleton;
}
// ********** End Enum EDialogueInputMode **********************************************************

// ********** Begin Enum EManipulationInputMode ****************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EManipulationInputMode;
static UEnum* EManipulationInputMode_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EManipulationInputMode.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EManipulationInputMode.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_LLM_NPC_EManipulationInputMode, (UObject*)Z_Construct_UPackage__Script_LLM_NPC(), TEXT("EManipulationInputMode"));
	}
	return Z_Registration_Info_UEnum_EManipulationInputMode.OuterSingleton;
}
template<> LLM_NPC_NON_ATTRIBUTED_API UEnum* StaticEnum<EManipulationInputMode>()
{
	return EManipulationInputMode_StaticEnum();
}
struct Z_Construct_UEnum_LLM_NPC_EManipulationInputMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Input mode for object manipulation. */" },
#endif
		{ "Gesture.DisplayName", "Gesture" },
		{ "Gesture.Name", "EManipulationInputMode::Gesture" },
		{ "KeyboardMouse.DisplayName", "Keyboard & Mouse" },
		{ "KeyboardMouse.Name", "EManipulationInputMode::KeyboardMouse" },
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Input mode for object manipulation." },
#endif
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EManipulationInputMode::Gesture", (int64)EManipulationInputMode::Gesture },
		{ "EManipulationInputMode::KeyboardMouse", (int64)EManipulationInputMode::KeyboardMouse },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_LLM_NPC_EManipulationInputMode_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_LLM_NPC_EManipulationInputMode_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_LLM_NPC,
	nullptr,
	"EManipulationInputMode",
	"EManipulationInputMode",
	Z_Construct_UEnum_LLM_NPC_EManipulationInputMode_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_LLM_NPC_EManipulationInputMode_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_LLM_NPC_EManipulationInputMode_Statics::Enum_MetaDataParams), Z_Construct_UEnum_LLM_NPC_EManipulationInputMode_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_LLM_NPC_EManipulationInputMode()
{
	if (!Z_Registration_Info_UEnum_EManipulationInputMode.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EManipulationInputMode.InnerSingleton, Z_Construct_UEnum_LLM_NPC_EManipulationInputMode_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EManipulationInputMode.InnerSingleton;
}
// ********** End Enum EManipulationInputMode ******************************************************

// ********** Begin ScriptStruct FPADVector ********************************************************
struct Z_Construct_UScriptStruct_FPADVector_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FPADVector); }
	static inline consteval int16 GetStructAlignment() { return alignof(FPADVector); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * PAD (Pleasure-Arousal-Dominance) vector for continuous emotion blending.\n * Each axis ranges from -1.0 to +1.0.\n */" },
#endif
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "PAD (Pleasure-Arousal-Dominance) vector for continuous emotion blending.\nEach axis ranges from -1.0 to +1.0." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Pleasure_MetaData[] = {
		{ "Category", "PADVector" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "-1.0" },
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Arousal_MetaData[] = {
		{ "Category", "PADVector" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "-1.0" },
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Dominance_MetaData[] = {
		{ "Category", "PADVector" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "-1.0" },
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FPADVector constinit property declarations ************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Pleasure;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Arousal;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Dominance;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FPADVector constinit property declarations **************************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FPADVector>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FPADVector_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FPADVector;
class UScriptStruct* FPADVector::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FPADVector.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FPADVector.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FPADVector, (UObject*)Z_Construct_UPackage__Script_LLM_NPC(), TEXT("PADVector"));
	}
	return Z_Registration_Info_UScriptStruct_FPADVector.OuterSingleton;
	}

// ********** Begin ScriptStruct FPADVector Property Definitions ***********************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FPADVector_Statics::NewProp_Pleasure = { "Pleasure", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FPADVector, Pleasure), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Pleasure_MetaData), NewProp_Pleasure_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FPADVector_Statics::NewProp_Arousal = { "Arousal", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FPADVector, Arousal), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Arousal_MetaData), NewProp_Arousal_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FPADVector_Statics::NewProp_Dominance = { "Dominance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FPADVector, Dominance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Dominance_MetaData), NewProp_Dominance_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FPADVector_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPADVector_Statics::NewProp_Pleasure,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPADVector_Statics::NewProp_Arousal,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPADVector_Statics::NewProp_Dominance,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPADVector_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FPADVector Property Definitions *************************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FPADVector_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
	nullptr,
	&NewStructOps,
	"PADVector",
	Z_Construct_UScriptStruct_FPADVector_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPADVector_Statics::PropPointers),
	sizeof(FPADVector),
	alignof(FPADVector),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPADVector_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FPADVector_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FPADVector()
{
	if (!Z_Registration_Info_UScriptStruct_FPADVector.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FPADVector.InnerSingleton, Z_Construct_UScriptStruct_FPADVector_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FPADVector.InnerSingleton);
}
// ********** End ScriptStruct FPADVector **********************************************************

// ********** Begin ScriptStruct FEmotionState *****************************************************
struct Z_Construct_UScriptStruct_FEmotionState_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FEmotionState); }
	static inline consteval int16 GetStructAlignment() { return alignof(FEmotionState); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Represents the NPC's current emotional state.\n * Combines Plutchik discrete label with PAD continuous vector.\n */" },
#endif
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Represents the NPC's current emotional state.\nCombines Plutchik discrete label with PAD continuous vector." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PrimaryEmotion_MetaData[] = {
		{ "Category", "EmotionState" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Primary discrete emotion (Plutchik). */" },
#endif
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Primary discrete emotion (Plutchik)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Intensity_MetaData[] = {
		{ "Category", "EmotionState" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Intensity of the primary emotion (0.0 = none, 1.0 = maximum). */" },
#endif
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Intensity of the primary emotion (0.0 = none, 1.0 = maximum)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PAD_MetaData[] = {
		{ "Category", "EmotionState" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Continuous PAD vector for smooth blending. */" },
#endif
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Continuous PAD vector for smooth blending." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StateEnteredTime_MetaData[] = {
		{ "Category", "EmotionState" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Timestamp when this state was entered. */" },
#endif
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Timestamp when this state was entered." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FEmotionState constinit property declarations *********************
	static const UECodeGen_Private::FBytePropertyParams NewProp_PrimaryEmotion_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_PrimaryEmotion;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Intensity;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PAD;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_StateEnteredTime;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FEmotionState constinit property declarations ***********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FEmotionState>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FEmotionState_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FEmotionState;
class UScriptStruct* FEmotionState::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FEmotionState.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FEmotionState.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FEmotionState, (UObject*)Z_Construct_UPackage__Script_LLM_NPC(), TEXT("EmotionState"));
	}
	return Z_Registration_Info_UScriptStruct_FEmotionState.OuterSingleton;
	}

// ********** Begin ScriptStruct FEmotionState Property Definitions ********************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FEmotionState_Statics::NewProp_PrimaryEmotion_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FEmotionState_Statics::NewProp_PrimaryEmotion = { "PrimaryEmotion", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEmotionState, PrimaryEmotion), Z_Construct_UEnum_LLM_NPC_EEmotionType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PrimaryEmotion_MetaData), NewProp_PrimaryEmotion_MetaData) }; // 1184287893
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEmotionState_Statics::NewProp_Intensity = { "Intensity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEmotionState, Intensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Intensity_MetaData), NewProp_Intensity_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FEmotionState_Statics::NewProp_PAD = { "PAD", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEmotionState, PAD), Z_Construct_UScriptStruct_FPADVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PAD_MetaData), NewProp_PAD_MetaData) }; // 3806868039
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEmotionState_Statics::NewProp_StateEnteredTime = { "StateEnteredTime", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEmotionState, StateEnteredTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StateEnteredTime_MetaData), NewProp_StateEnteredTime_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FEmotionState_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionState_Statics::NewProp_PrimaryEmotion_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionState_Statics::NewProp_PrimaryEmotion,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionState_Statics::NewProp_Intensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionState_Statics::NewProp_PAD,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionState_Statics::NewProp_StateEnteredTime,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEmotionState_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FEmotionState Property Definitions **********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FEmotionState_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
	nullptr,
	&NewStructOps,
	"EmotionState",
	Z_Construct_UScriptStruct_FEmotionState_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEmotionState_Statics::PropPointers),
	sizeof(FEmotionState),
	alignof(FEmotionState),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEmotionState_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FEmotionState_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FEmotionState()
{
	if (!Z_Registration_Info_UScriptStruct_FEmotionState.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FEmotionState.InnerSingleton, Z_Construct_UScriptStruct_FEmotionState_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FEmotionState.InnerSingleton);
}
// ********** End ScriptStruct FEmotionState *******************************************************

// ********** Begin ScriptStruct FNPCMessage *******************************************************
struct Z_Construct_UScriptStruct_FNPCMessage_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FNPCMessage); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNPCMessage); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** A single dialogue message in conversation history. */" },
#endif
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A single dialogue message in conversation history." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Role_MetaData[] = {
		{ "Category", "NPCMessage" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Role: \"user\", \"assistant\", or \"system\". */" },
#endif
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Role: \"user\", \"assistant\", or \"system\"." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Content_MetaData[] = {
		{ "Category", "NPCMessage" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Message text content. */" },
#endif
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Message text content." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Timestamp_MetaData[] = {
		{ "Category", "NPCMessage" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Timestamp of this message. */" },
#endif
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Timestamp of this message." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DetectedUserEmotion_MetaData[] = {
		{ "Category", "NPCMessage" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Detected user emotion at time of message (if applicable). */" },
#endif
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Detected user emotion at time of message (if applicable)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UserEmotionConfidence_MetaData[] = {
		{ "Category", "NPCMessage" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Confidence of detected user emotion. */" },
#endif
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Confidence of detected user emotion." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNPCMessage constinit property declarations ***********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Role;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Content;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Timestamp;
	static const UECodeGen_Private::FBytePropertyParams NewProp_DetectedUserEmotion_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_DetectedUserEmotion;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_UserEmotionConfidence;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNPCMessage constinit property declarations *************************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNPCMessage>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FNPCMessage_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNPCMessage;
class UScriptStruct* FNPCMessage::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FNPCMessage.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FNPCMessage.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNPCMessage, (UObject*)Z_Construct_UPackage__Script_LLM_NPC(), TEXT("NPCMessage"));
	}
	return Z_Registration_Info_UScriptStruct_FNPCMessage.OuterSingleton;
	}

// ********** Begin ScriptStruct FNPCMessage Property Definitions **********************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FNPCMessage_Statics::NewProp_Role = { "Role", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FNPCMessage, Role), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Role_MetaData), NewProp_Role_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FNPCMessage_Statics::NewProp_Content = { "Content", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FNPCMessage, Content), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Content_MetaData), NewProp_Content_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FNPCMessage_Statics::NewProp_Timestamp = { "Timestamp", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FNPCMessage, Timestamp), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Timestamp_MetaData), NewProp_Timestamp_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FNPCMessage_Statics::NewProp_DetectedUserEmotion_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FNPCMessage_Statics::NewProp_DetectedUserEmotion = { "DetectedUserEmotion", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FNPCMessage, DetectedUserEmotion), Z_Construct_UEnum_LLM_NPC_EEmotionType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DetectedUserEmotion_MetaData), NewProp_DetectedUserEmotion_MetaData) }; // 1184287893
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FNPCMessage_Statics::NewProp_UserEmotionConfidence = { "UserEmotionConfidence", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FNPCMessage, UserEmotionConfidence), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UserEmotionConfidence_MetaData), NewProp_UserEmotionConfidence_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FNPCMessage_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNPCMessage_Statics::NewProp_Role,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNPCMessage_Statics::NewProp_Content,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNPCMessage_Statics::NewProp_Timestamp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNPCMessage_Statics::NewProp_DetectedUserEmotion_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNPCMessage_Statics::NewProp_DetectedUserEmotion,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNPCMessage_Statics::NewProp_UserEmotionConfidence,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FNPCMessage_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FNPCMessage Property Definitions ************************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FNPCMessage_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
	nullptr,
	&NewStructOps,
	"NPCMessage",
	Z_Construct_UScriptStruct_FNPCMessage_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FNPCMessage_Statics::PropPointers),
	sizeof(FNPCMessage),
	alignof(FNPCMessage),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FNPCMessage_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FNPCMessage_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FNPCMessage()
{
	if (!Z_Registration_Info_UScriptStruct_FNPCMessage.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNPCMessage.InnerSingleton, Z_Construct_UScriptStruct_FNPCMessage_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNPCMessage.InnerSingleton);
}
// ********** End ScriptStruct FNPCMessage *********************************************************

// ********** Begin ScriptStruct FDetectedUserEmotion **********************************************
struct Z_Construct_UScriptStruct_FDetectedUserEmotion_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FDetectedUserEmotion); }
	static inline consteval int16 GetStructAlignment() { return alignof(FDetectedUserEmotion); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Detected user emotion from facial recognition. */" },
#endif
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Detected user emotion from facial recognition." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Emotion_MetaData[] = {
		{ "Category", "DetectedUserEmotion" },
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Confidence_MetaData[] = {
		{ "Category", "DetectedUserEmotion" },
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Probabilities_MetaData[] = {
		{ "Category", "DetectedUserEmotion" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Raw probability for each emotion class. */" },
#endif
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Raw probability for each emotion class." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Timestamp_MetaData[] = {
		{ "Category", "DetectedUserEmotion" },
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FDetectedUserEmotion constinit property declarations **************
	static const UECodeGen_Private::FBytePropertyParams NewProp_Emotion_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Emotion;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Confidence;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Probabilities_ValueProp;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Probabilities_Key_KeyProp_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Probabilities_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_Probabilities;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Timestamp;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FDetectedUserEmotion constinit property declarations ****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDetectedUserEmotion>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FDetectedUserEmotion_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FDetectedUserEmotion;
class UScriptStruct* FDetectedUserEmotion::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FDetectedUserEmotion.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FDetectedUserEmotion.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDetectedUserEmotion, (UObject*)Z_Construct_UPackage__Script_LLM_NPC(), TEXT("DetectedUserEmotion"));
	}
	return Z_Registration_Info_UScriptStruct_FDetectedUserEmotion.OuterSingleton;
	}

// ********** Begin ScriptStruct FDetectedUserEmotion Property Definitions *************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FDetectedUserEmotion_Statics::NewProp_Emotion_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FDetectedUserEmotion_Statics::NewProp_Emotion = { "Emotion", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FDetectedUserEmotion, Emotion), Z_Construct_UEnum_LLM_NPC_EEmotionType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Emotion_MetaData), NewProp_Emotion_MetaData) }; // 1184287893
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FDetectedUserEmotion_Statics::NewProp_Confidence = { "Confidence", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FDetectedUserEmotion, Confidence), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Confidence_MetaData), NewProp_Confidence_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FDetectedUserEmotion_Statics::NewProp_Probabilities_ValueProp = { "Probabilities", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FDetectedUserEmotion_Statics::NewProp_Probabilities_Key_KeyProp_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FDetectedUserEmotion_Statics::NewProp_Probabilities_Key_KeyProp = { "Probabilities_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UEnum_LLM_NPC_EEmotionType, METADATA_PARAMS(0, nullptr) }; // 1184287893
const UECodeGen_Private::FMapPropertyParams Z_Construct_UScriptStruct_FDetectedUserEmotion_Statics::NewProp_Probabilities = { "Probabilities", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FDetectedUserEmotion, Probabilities), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Probabilities_MetaData), NewProp_Probabilities_MetaData) }; // 1184287893
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FDetectedUserEmotion_Statics::NewProp_Timestamp = { "Timestamp", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FDetectedUserEmotion, Timestamp), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Timestamp_MetaData), NewProp_Timestamp_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FDetectedUserEmotion_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FDetectedUserEmotion_Statics::NewProp_Emotion_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FDetectedUserEmotion_Statics::NewProp_Emotion,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FDetectedUserEmotion_Statics::NewProp_Confidence,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FDetectedUserEmotion_Statics::NewProp_Probabilities_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FDetectedUserEmotion_Statics::NewProp_Probabilities_Key_KeyProp_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FDetectedUserEmotion_Statics::NewProp_Probabilities_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FDetectedUserEmotion_Statics::NewProp_Probabilities,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FDetectedUserEmotion_Statics::NewProp_Timestamp,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FDetectedUserEmotion_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FDetectedUserEmotion Property Definitions ***************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FDetectedUserEmotion_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
	nullptr,
	&NewStructOps,
	"DetectedUserEmotion",
	Z_Construct_UScriptStruct_FDetectedUserEmotion_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FDetectedUserEmotion_Statics::PropPointers),
	sizeof(FDetectedUserEmotion),
	alignof(FDetectedUserEmotion),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FDetectedUserEmotion_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FDetectedUserEmotion_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FDetectedUserEmotion()
{
	if (!Z_Registration_Info_UScriptStruct_FDetectedUserEmotion.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FDetectedUserEmotion.InnerSingleton, Z_Construct_UScriptStruct_FDetectedUserEmotion_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FDetectedUserEmotion.InnerSingleton);
}
// ********** End ScriptStruct FDetectedUserEmotion ************************************************

// ********** Begin Enum EGestureType **************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EGestureType;
static UEnum* EGestureType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EGestureType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EGestureType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_LLM_NPC_EGestureType, (UObject*)Z_Construct_UPackage__Script_LLM_NPC(), TEXT("EGestureType"));
	}
	return Z_Registration_Info_UEnum_EGestureType.OuterSingleton;
}
template<> LLM_NPC_NON_ATTRIBUTED_API UEnum* StaticEnum<EGestureType>()
{
	return EGestureType_StaticEnum();
}
struct Z_Construct_UEnum_LLM_NPC_EGestureType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Gesture input from hand tracking. */" },
#endif
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
		{ "None.DisplayName", "None" },
		{ "None.Name", "EGestureType::None" },
		{ "Pinch.DisplayName", "Pinch (Shrink)" },
		{ "Pinch.Name", "EGestureType::Pinch" },
		{ "Rotate.DisplayName", "Rotate" },
		{ "Rotate.Name", "EGestureType::Rotate" },
		{ "Spindle.DisplayName", "Spindle (Two-Hand)" },
		{ "Spindle.Name", "EGestureType::Spindle" },
		{ "Spread.DisplayName", "Spread (Enlarge)" },
		{ "Spread.Name", "EGestureType::Spread" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Gesture input from hand tracking." },
#endif
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EGestureType::None", (int64)EGestureType::None },
		{ "EGestureType::Pinch", (int64)EGestureType::Pinch },
		{ "EGestureType::Spread", (int64)EGestureType::Spread },
		{ "EGestureType::Rotate", (int64)EGestureType::Rotate },
		{ "EGestureType::Spindle", (int64)EGestureType::Spindle },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_LLM_NPC_EGestureType_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_LLM_NPC_EGestureType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_LLM_NPC,
	nullptr,
	"EGestureType",
	"EGestureType",
	Z_Construct_UEnum_LLM_NPC_EGestureType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_LLM_NPC_EGestureType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_LLM_NPC_EGestureType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_LLM_NPC_EGestureType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_LLM_NPC_EGestureType()
{
	if (!Z_Registration_Info_UEnum_EGestureType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EGestureType.InnerSingleton, Z_Construct_UEnum_LLM_NPC_EGestureType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EGestureType.InnerSingleton;
}
// ********** End Enum EGestureType ****************************************************************

// ********** Begin ScriptStruct FGestureInput *****************************************************
struct Z_Construct_UScriptStruct_FGestureInput_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FGestureInput); }
	static inline consteval int16 GetStructAlignment() { return alignof(FGestureInput); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GestureType_MetaData[] = {
		{ "Category", "GestureInput" },
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Magnitude_MetaData[] = {
		{ "Category", "GestureInput" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Magnitude of the gesture (scale factor or rotation degrees per frame). */" },
#endif
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Magnitude of the gesture (scale factor or rotation degrees per frame)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Confidence_MetaData[] = {
		{ "Category", "GestureInput" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Confidence of gesture detection. */" },
#endif
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Confidence of gesture detection." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Delta_MetaData[] = {
		{ "Category", "GestureInput" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Delta from last frame for incremental application. */" },
#endif
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Delta from last frame for incremental application." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FGestureInput constinit property declarations *********************
	static const UECodeGen_Private::FBytePropertyParams NewProp_GestureType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_GestureType;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Magnitude;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Confidence;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Delta;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FGestureInput constinit property declarations ***********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FGestureInput>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FGestureInput_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FGestureInput;
class UScriptStruct* FGestureInput::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FGestureInput.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FGestureInput.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FGestureInput, (UObject*)Z_Construct_UPackage__Script_LLM_NPC(), TEXT("GestureInput"));
	}
	return Z_Registration_Info_UScriptStruct_FGestureInput.OuterSingleton;
	}

// ********** Begin ScriptStruct FGestureInput Property Definitions ********************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FGestureInput_Statics::NewProp_GestureType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FGestureInput_Statics::NewProp_GestureType = { "GestureType", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGestureInput, GestureType), Z_Construct_UEnum_LLM_NPC_EGestureType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GestureType_MetaData), NewProp_GestureType_MetaData) }; // 3467686549
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FGestureInput_Statics::NewProp_Magnitude = { "Magnitude", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGestureInput, Magnitude), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Magnitude_MetaData), NewProp_Magnitude_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FGestureInput_Statics::NewProp_Confidence = { "Confidence", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGestureInput, Confidence), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Confidence_MetaData), NewProp_Confidence_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FGestureInput_Statics::NewProp_Delta = { "Delta", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGestureInput, Delta), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Delta_MetaData), NewProp_Delta_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FGestureInput_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGestureInput_Statics::NewProp_GestureType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGestureInput_Statics::NewProp_GestureType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGestureInput_Statics::NewProp_Magnitude,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGestureInput_Statics::NewProp_Confidence,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGestureInput_Statics::NewProp_Delta,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGestureInput_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FGestureInput Property Definitions **********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FGestureInput_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
	nullptr,
	&NewStructOps,
	"GestureInput",
	Z_Construct_UScriptStruct_FGestureInput_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGestureInput_Statics::PropPointers),
	sizeof(FGestureInput),
	alignof(FGestureInput),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGestureInput_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FGestureInput_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FGestureInput()
{
	if (!Z_Registration_Info_UScriptStruct_FGestureInput.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FGestureInput.InnerSingleton, Z_Construct_UScriptStruct_FGestureInput_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FGestureInput.InnerSingleton);
}
// ********** End ScriptStruct FGestureInput *******************************************************

// ********** Begin ScriptStruct FEmotionSignal ****************************************************
struct Z_Construct_UScriptStruct_FEmotionSignal_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FEmotionSignal); }
	static inline consteval int16 GetStructAlignment() { return alignof(FEmotionSignal); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Signal sent to the Emotion Engine to influence NPC emotional state. */" },
#endif
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Signal sent to the Emotion Engine to influence NPC emotional state." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetEmotion_MetaData[] = {
		{ "Category", "EmotionSignal" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The emotion this signal pushes toward. */" },
#endif
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The emotion this signal pushes toward." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Strength_MetaData[] = {
		{ "Category", "EmotionSignal" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Strength of the signal (0.0 to 1.0). */" },
#endif
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Strength of the signal (0.0 to 1.0)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Source_MetaData[] = {
		{ "Category", "EmotionSignal" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Source identifier for debugging. */" },
#endif
		{ "ModuleRelativePath", "Core/NPCTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Source identifier for debugging." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FEmotionSignal constinit property declarations ********************
	static const UECodeGen_Private::FBytePropertyParams NewProp_TargetEmotion_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_TargetEmotion;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Strength;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Source;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FEmotionSignal constinit property declarations **********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FEmotionSignal>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FEmotionSignal_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FEmotionSignal;
class UScriptStruct* FEmotionSignal::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FEmotionSignal.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FEmotionSignal.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FEmotionSignal, (UObject*)Z_Construct_UPackage__Script_LLM_NPC(), TEXT("EmotionSignal"));
	}
	return Z_Registration_Info_UScriptStruct_FEmotionSignal.OuterSingleton;
	}

// ********** Begin ScriptStruct FEmotionSignal Property Definitions *******************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FEmotionSignal_Statics::NewProp_TargetEmotion_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FEmotionSignal_Statics::NewProp_TargetEmotion = { "TargetEmotion", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEmotionSignal, TargetEmotion), Z_Construct_UEnum_LLM_NPC_EEmotionType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetEmotion_MetaData), NewProp_TargetEmotion_MetaData) }; // 1184287893
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEmotionSignal_Statics::NewProp_Strength = { "Strength", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEmotionSignal, Strength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Strength_MetaData), NewProp_Strength_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FEmotionSignal_Statics::NewProp_Source = { "Source", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEmotionSignal, Source), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Source_MetaData), NewProp_Source_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FEmotionSignal_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionSignal_Statics::NewProp_TargetEmotion_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionSignal_Statics::NewProp_TargetEmotion,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionSignal_Statics::NewProp_Strength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionSignal_Statics::NewProp_Source,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEmotionSignal_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FEmotionSignal Property Definitions *********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FEmotionSignal_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
	nullptr,
	&NewStructOps,
	"EmotionSignal",
	Z_Construct_UScriptStruct_FEmotionSignal_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEmotionSignal_Statics::PropPointers),
	sizeof(FEmotionSignal),
	alignof(FEmotionSignal),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEmotionSignal_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FEmotionSignal_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FEmotionSignal()
{
	if (!Z_Registration_Info_UScriptStruct_FEmotionSignal.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FEmotionSignal.InnerSingleton, Z_Construct_UScriptStruct_FEmotionSignal_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FEmotionSignal.InnerSingleton);
}
// ********** End ScriptStruct FEmotionSignal ******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCTypes_h__Script_LLM_NPC_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EEmotionType_StaticEnum, TEXT("EEmotionType"), &Z_Registration_Info_UEnum_EEmotionType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1184287893U) },
		{ EDialogueInputMode_StaticEnum, TEXT("EDialogueInputMode"), &Z_Registration_Info_UEnum_EDialogueInputMode, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 4223634033U) },
		{ EManipulationInputMode_StaticEnum, TEXT("EManipulationInputMode"), &Z_Registration_Info_UEnum_EManipulationInputMode, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2676813440U) },
		{ EGestureType_StaticEnum, TEXT("EGestureType"), &Z_Registration_Info_UEnum_EGestureType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3467686549U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FPADVector::StaticStruct, Z_Construct_UScriptStruct_FPADVector_Statics::NewStructOps, TEXT("PADVector"),&Z_Registration_Info_UScriptStruct_FPADVector, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FPADVector), 3806868039U) },
		{ FEmotionState::StaticStruct, Z_Construct_UScriptStruct_FEmotionState_Statics::NewStructOps, TEXT("EmotionState"),&Z_Registration_Info_UScriptStruct_FEmotionState, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FEmotionState), 1004811449U) },
		{ FNPCMessage::StaticStruct, Z_Construct_UScriptStruct_FNPCMessage_Statics::NewStructOps, TEXT("NPCMessage"),&Z_Registration_Info_UScriptStruct_FNPCMessage, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNPCMessage), 3120298436U) },
		{ FDetectedUserEmotion::StaticStruct, Z_Construct_UScriptStruct_FDetectedUserEmotion_Statics::NewStructOps, TEXT("DetectedUserEmotion"),&Z_Registration_Info_UScriptStruct_FDetectedUserEmotion, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDetectedUserEmotion), 3137125811U) },
		{ FGestureInput::StaticStruct, Z_Construct_UScriptStruct_FGestureInput_Statics::NewStructOps, TEXT("GestureInput"),&Z_Registration_Info_UScriptStruct_FGestureInput, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FGestureInput), 3452162926U) },
		{ FEmotionSignal::StaticStruct, Z_Construct_UScriptStruct_FEmotionSignal_Statics::NewStructOps, TEXT("EmotionSignal"),&Z_Registration_Info_UScriptStruct_FEmotionSignal, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FEmotionSignal), 2625116487U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCTypes_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCTypes_h__Script_LLM_NPC_491599441{
	TEXT("/Script/LLM_NPC"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCTypes_h__Script_LLM_NPC_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCTypes_h__Script_LLM_NPC_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCTypes_h__Script_LLM_NPC_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCTypes_h__Script_LLM_NPC_Statics::EnumInfo),
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
