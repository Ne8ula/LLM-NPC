// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Inventory/InventoryTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeInventoryTypes() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UStaticMesh_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
LLM_NPC_API UEnum* Z_Construct_UEnum_LLM_NPC_EEmotionType();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FEmotionUnlockCondition();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FInventoryItem();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FEmotionUnlockCondition *******************************************
struct Z_Construct_UScriptStruct_FEmotionUnlockCondition_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FEmotionUnlockCondition); }
	static inline consteval int16 GetStructAlignment() { return alignof(FEmotionUnlockCondition); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Condition that must be met (emotion type + intensity + duration + optional keywords)\n * before an inventory item becomes unlocked.\n */" },
#endif
		{ "ModuleRelativePath", "Inventory/InventoryTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Condition that must be met (emotion type + intensity + duration + optional keywords)\nbefore an inventory item becomes unlocked." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RequiredEmotion_MetaData[] = {
		{ "Category", "Inventory|Unlock" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The emotion the player must evoke in the NPC. */" },
#endif
		{ "ModuleRelativePath", "Inventory/InventoryTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The emotion the player must evoke in the NPC." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinIntensity_MetaData[] = {
		{ "Category", "Inventory|Unlock" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Minimum intensity the emotion must reach. */" },
#endif
		{ "ModuleRelativePath", "Inventory/InventoryTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Minimum intensity the emotion must reach." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinDurationSeconds_MetaData[] = {
		{ "Category", "Inventory|Unlock" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** How long (seconds) the emotion must be sustained at or above MinIntensity. */" },
#endif
		{ "ModuleRelativePath", "Inventory/InventoryTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "How long (seconds) the emotion must be sustained at or above MinIntensity." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OptionalKeywords_MetaData[] = {
		{ "Category", "Inventory|Unlock" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Optional keywords that must appear in recent dialogue to satisfy this condition. */" },
#endif
		{ "ModuleRelativePath", "Inventory/InventoryTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Optional keywords that must appear in recent dialogue to satisfy this condition." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bRequireAllKeywords_MetaData[] = {
		{ "Category", "Inventory|Unlock" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** If true, ALL keywords must be present; otherwise ANY one suffices. */" },
#endif
		{ "ModuleRelativePath", "Inventory/InventoryTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If true, ALL keywords must be present; otherwise ANY one suffices." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FEmotionUnlockCondition constinit property declarations ***********
	static const UECodeGen_Private::FBytePropertyParams NewProp_RequiredEmotion_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_RequiredEmotion;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MinIntensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MinDurationSeconds;
	static const UECodeGen_Private::FStrPropertyParams NewProp_OptionalKeywords_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_OptionalKeywords;
	static void NewProp_bRequireAllKeywords_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bRequireAllKeywords;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FEmotionUnlockCondition constinit property declarations *************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FEmotionUnlockCondition>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FEmotionUnlockCondition_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FEmotionUnlockCondition;
class UScriptStruct* FEmotionUnlockCondition::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FEmotionUnlockCondition.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FEmotionUnlockCondition.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FEmotionUnlockCondition, (UObject*)Z_Construct_UPackage__Script_LLM_NPC(), TEXT("EmotionUnlockCondition"));
	}
	return Z_Registration_Info_UScriptStruct_FEmotionUnlockCondition.OuterSingleton;
	}

// ********** Begin ScriptStruct FEmotionUnlockCondition Property Definitions **********************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FEmotionUnlockCondition_Statics::NewProp_RequiredEmotion_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FEmotionUnlockCondition_Statics::NewProp_RequiredEmotion = { "RequiredEmotion", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEmotionUnlockCondition, RequiredEmotion), Z_Construct_UEnum_LLM_NPC_EEmotionType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RequiredEmotion_MetaData), NewProp_RequiredEmotion_MetaData) }; // 1184287893
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEmotionUnlockCondition_Statics::NewProp_MinIntensity = { "MinIntensity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEmotionUnlockCondition, MinIntensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinIntensity_MetaData), NewProp_MinIntensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEmotionUnlockCondition_Statics::NewProp_MinDurationSeconds = { "MinDurationSeconds", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEmotionUnlockCondition, MinDurationSeconds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinDurationSeconds_MetaData), NewProp_MinDurationSeconds_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FEmotionUnlockCondition_Statics::NewProp_OptionalKeywords_Inner = { "OptionalKeywords", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FEmotionUnlockCondition_Statics::NewProp_OptionalKeywords = { "OptionalKeywords", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEmotionUnlockCondition, OptionalKeywords), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OptionalKeywords_MetaData), NewProp_OptionalKeywords_MetaData) };
void Z_Construct_UScriptStruct_FEmotionUnlockCondition_Statics::NewProp_bRequireAllKeywords_SetBit(void* Obj)
{
	((FEmotionUnlockCondition*)Obj)->bRequireAllKeywords = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FEmotionUnlockCondition_Statics::NewProp_bRequireAllKeywords = { "bRequireAllKeywords", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FEmotionUnlockCondition), &Z_Construct_UScriptStruct_FEmotionUnlockCondition_Statics::NewProp_bRequireAllKeywords_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bRequireAllKeywords_MetaData), NewProp_bRequireAllKeywords_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FEmotionUnlockCondition_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionUnlockCondition_Statics::NewProp_RequiredEmotion_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionUnlockCondition_Statics::NewProp_RequiredEmotion,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionUnlockCondition_Statics::NewProp_MinIntensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionUnlockCondition_Statics::NewProp_MinDurationSeconds,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionUnlockCondition_Statics::NewProp_OptionalKeywords_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionUnlockCondition_Statics::NewProp_OptionalKeywords,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEmotionUnlockCondition_Statics::NewProp_bRequireAllKeywords,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEmotionUnlockCondition_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FEmotionUnlockCondition Property Definitions ************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FEmotionUnlockCondition_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
	nullptr,
	&NewStructOps,
	"EmotionUnlockCondition",
	Z_Construct_UScriptStruct_FEmotionUnlockCondition_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEmotionUnlockCondition_Statics::PropPointers),
	sizeof(FEmotionUnlockCondition),
	alignof(FEmotionUnlockCondition),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEmotionUnlockCondition_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FEmotionUnlockCondition_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FEmotionUnlockCondition()
{
	if (!Z_Registration_Info_UScriptStruct_FEmotionUnlockCondition.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FEmotionUnlockCondition.InnerSingleton, Z_Construct_UScriptStruct_FEmotionUnlockCondition_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FEmotionUnlockCondition.InnerSingleton);
}
// ********** End ScriptStruct FEmotionUnlockCondition *********************************************

// ********** Begin ScriptStruct FInventoryItem ****************************************************
struct Z_Construct_UScriptStruct_FInventoryItem_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FInventoryItem); }
	static inline consteval int16 GetStructAlignment() { return alignof(FInventoryItem); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * A single item an NPC can give to the player when unlock conditions are met.\n */" },
#endif
		{ "ModuleRelativePath", "Inventory/InventoryTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A single item an NPC can give to the player when unlock conditions are met." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemID_MetaData[] = {
		{ "Category", "Inventory|Item" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Unique identifier for this item. */" },
#endif
		{ "ModuleRelativePath", "Inventory/InventoryTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Unique identifier for this item." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DisplayName_MetaData[] = {
		{ "Category", "Inventory|Item" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Localised display name shown to the player. */" },
#endif
		{ "ModuleRelativePath", "Inventory/InventoryTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Localised display name shown to the player." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Description_MetaData[] = {
		{ "Category", "Inventory|Item" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Localised description shown in the inspect panel. */" },
#endif
		{ "ModuleRelativePath", "Inventory/InventoryTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Localised description shown in the inspect panel." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InspectMesh_MetaData[] = {
		{ "Category", "Inventory|Item" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Mesh displayed when the player inspects the item in 3D. */" },
#endif
		{ "ModuleRelativePath", "Inventory/InventoryTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Mesh displayed when the player inspects the item in 3D." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Icon_MetaData[] = {
		{ "Category", "Inventory|Item" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** 2D icon for UI display. */" },
#endif
		{ "ModuleRelativePath", "Inventory/InventoryTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "2D icon for UI display." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UnlockConditions_MetaData[] = {
		{ "Category", "Inventory|Item" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** All conditions that must be satisfied to unlock this item. */" },
#endif
		{ "ModuleRelativePath", "Inventory/InventoryTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "All conditions that must be satisfied to unlock this item." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUnlocked_MetaData[] = {
		{ "Category", "Inventory|Item" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Whether the item has been unlocked (conditions met). */" },
#endif
		{ "ModuleRelativePath", "Inventory/InventoryTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Whether the item has been unlocked (conditions met)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bGivenToPlayer_MetaData[] = {
		{ "Category", "Inventory|Item" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Whether the item has been handed to the player. */" },
#endif
		{ "ModuleRelativePath", "Inventory/InventoryTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Whether the item has been handed to the player." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FInventoryItem constinit property declarations ********************
	static const UECodeGen_Private::FNamePropertyParams NewProp_ItemID;
	static const UECodeGen_Private::FTextPropertyParams NewProp_DisplayName;
	static const UECodeGen_Private::FTextPropertyParams NewProp_Description;
	static const UECodeGen_Private::FSoftObjectPropertyParams NewProp_InspectMesh;
	static const UECodeGen_Private::FSoftObjectPropertyParams NewProp_Icon;
	static const UECodeGen_Private::FStructPropertyParams NewProp_UnlockConditions_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_UnlockConditions;
	static void NewProp_bUnlocked_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUnlocked;
	static void NewProp_bGivenToPlayer_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bGivenToPlayer;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FInventoryItem constinit property declarations **********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FInventoryItem>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FInventoryItem_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FInventoryItem;
class UScriptStruct* FInventoryItem::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FInventoryItem.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FInventoryItem.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FInventoryItem, (UObject*)Z_Construct_UPackage__Script_LLM_NPC(), TEXT("InventoryItem"));
	}
	return Z_Registration_Info_UScriptStruct_FInventoryItem.OuterSingleton;
	}

// ********** Begin ScriptStruct FInventoryItem Property Definitions *******************************
const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FInventoryItem_Statics::NewProp_ItemID = { "ItemID", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FInventoryItem, ItemID), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ItemID_MetaData), NewProp_ItemID_MetaData) };
const UECodeGen_Private::FTextPropertyParams Z_Construct_UScriptStruct_FInventoryItem_Statics::NewProp_DisplayName = { "DisplayName", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FInventoryItem, DisplayName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DisplayName_MetaData), NewProp_DisplayName_MetaData) };
const UECodeGen_Private::FTextPropertyParams Z_Construct_UScriptStruct_FInventoryItem_Statics::NewProp_Description = { "Description", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FInventoryItem, Description), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Description_MetaData), NewProp_Description_MetaData) };
const UECodeGen_Private::FSoftObjectPropertyParams Z_Construct_UScriptStruct_FInventoryItem_Statics::NewProp_InspectMesh = { "InspectMesh", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::SoftObject, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FInventoryItem, InspectMesh), Z_Construct_UClass_UStaticMesh_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InspectMesh_MetaData), NewProp_InspectMesh_MetaData) };
const UECodeGen_Private::FSoftObjectPropertyParams Z_Construct_UScriptStruct_FInventoryItem_Statics::NewProp_Icon = { "Icon", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::SoftObject, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FInventoryItem, Icon), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Icon_MetaData), NewProp_Icon_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FInventoryItem_Statics::NewProp_UnlockConditions_Inner = { "UnlockConditions", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FEmotionUnlockCondition, METADATA_PARAMS(0, nullptr) }; // 839693928
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FInventoryItem_Statics::NewProp_UnlockConditions = { "UnlockConditions", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FInventoryItem, UnlockConditions), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UnlockConditions_MetaData), NewProp_UnlockConditions_MetaData) }; // 839693928
void Z_Construct_UScriptStruct_FInventoryItem_Statics::NewProp_bUnlocked_SetBit(void* Obj)
{
	((FInventoryItem*)Obj)->bUnlocked = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FInventoryItem_Statics::NewProp_bUnlocked = { "bUnlocked", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FInventoryItem), &Z_Construct_UScriptStruct_FInventoryItem_Statics::NewProp_bUnlocked_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUnlocked_MetaData), NewProp_bUnlocked_MetaData) };
void Z_Construct_UScriptStruct_FInventoryItem_Statics::NewProp_bGivenToPlayer_SetBit(void* Obj)
{
	((FInventoryItem*)Obj)->bGivenToPlayer = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FInventoryItem_Statics::NewProp_bGivenToPlayer = { "bGivenToPlayer", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FInventoryItem), &Z_Construct_UScriptStruct_FInventoryItem_Statics::NewProp_bGivenToPlayer_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bGivenToPlayer_MetaData), NewProp_bGivenToPlayer_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FInventoryItem_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FInventoryItem_Statics::NewProp_ItemID,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FInventoryItem_Statics::NewProp_DisplayName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FInventoryItem_Statics::NewProp_Description,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FInventoryItem_Statics::NewProp_InspectMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FInventoryItem_Statics::NewProp_Icon,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FInventoryItem_Statics::NewProp_UnlockConditions_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FInventoryItem_Statics::NewProp_UnlockConditions,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FInventoryItem_Statics::NewProp_bUnlocked,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FInventoryItem_Statics::NewProp_bGivenToPlayer,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FInventoryItem_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FInventoryItem Property Definitions *********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FInventoryItem_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
	nullptr,
	&NewStructOps,
	"InventoryItem",
	Z_Construct_UScriptStruct_FInventoryItem_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FInventoryItem_Statics::PropPointers),
	sizeof(FInventoryItem),
	alignof(FInventoryItem),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FInventoryItem_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FInventoryItem_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FInventoryItem()
{
	if (!Z_Registration_Info_UScriptStruct_FInventoryItem.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FInventoryItem.InnerSingleton, Z_Construct_UScriptStruct_FInventoryItem_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FInventoryItem.InnerSingleton);
}
// ********** End ScriptStruct FInventoryItem ******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Inventory_InventoryTypes_h__Script_LLM_NPC_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FEmotionUnlockCondition::StaticStruct, Z_Construct_UScriptStruct_FEmotionUnlockCondition_Statics::NewStructOps, TEXT("EmotionUnlockCondition"),&Z_Registration_Info_UScriptStruct_FEmotionUnlockCondition, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FEmotionUnlockCondition), 839693928U) },
		{ FInventoryItem::StaticStruct, Z_Construct_UScriptStruct_FInventoryItem_Statics::NewStructOps, TEXT("InventoryItem"),&Z_Registration_Info_UScriptStruct_FInventoryItem, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FInventoryItem), 1158787168U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Inventory_InventoryTypes_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Inventory_InventoryTypes_h__Script_LLM_NPC_3594403708{
	TEXT("/Script/LLM_NPC"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Inventory_InventoryTypes_h__Script_LLM_NPC_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Inventory_InventoryTypes_h__Script_LLM_NPC_Statics::ScriptStructInfo),
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
