// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Inventory/NPCInventoryComponent.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "LLM_NPC/Inventory/InventoryTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeNPCInventoryComponent() {}

// ********** Begin Cross Module References ********************************************************
LLM_NPC_API UClass* Z_Construct_UClass_UInventoryDataAsset_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UNPCInventoryComponent();
LLM_NPC_API UClass* Z_Construct_UClass_UNPCInventoryComponent_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UNPCSubsystemComponent();
LLM_NPC_API UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnItemGiven__DelegateSignature();
LLM_NPC_API UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnItemUnlocked__DelegateSignature();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FEmotionState();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FInventoryItem();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FOnItemUnlocked *******************************************************
struct Z_Construct_UDelegateFunction_LLM_NPC_OnItemUnlocked__DelegateSignature_Statics
{
	struct _Script_LLM_NPC_eventOnItemUnlocked_Parms
	{
		FName ItemID;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Inventory/NPCInventoryComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnItemUnlocked constinit property declarations ***********************
	static const UECodeGen_Private::FNamePropertyParams NewProp_ItemID;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FOnItemUnlocked constinit property declarations *************************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FOnItemUnlocked Property Definitions **********************************
const UECodeGen_Private::FNamePropertyParams Z_Construct_UDelegateFunction_LLM_NPC_OnItemUnlocked__DelegateSignature_Statics::NewProp_ItemID = { "ItemID", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_LLM_NPC_eventOnItemUnlocked_Parms, ItemID), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_LLM_NPC_OnItemUnlocked__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LLM_NPC_OnItemUnlocked__DelegateSignature_Statics::NewProp_ItemID,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnItemUnlocked__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FOnItemUnlocked Property Definitions ************************************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_LLM_NPC_OnItemUnlocked__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_LLM_NPC, nullptr, "OnItemUnlocked__DelegateSignature", 	Z_Construct_UDelegateFunction_LLM_NPC_OnItemUnlocked__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnItemUnlocked__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_LLM_NPC_OnItemUnlocked__DelegateSignature_Statics::_Script_LLM_NPC_eventOnItemUnlocked_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnItemUnlocked__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_LLM_NPC_OnItemUnlocked__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_LLM_NPC_OnItemUnlocked__DelegateSignature_Statics::_Script_LLM_NPC_eventOnItemUnlocked_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnItemUnlocked__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_LLM_NPC_OnItemUnlocked__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnItemUnlocked_DelegateWrapper(const FMulticastScriptDelegate& OnItemUnlocked, FName ItemID)
{
	struct _Script_LLM_NPC_eventOnItemUnlocked_Parms
	{
		FName ItemID;
	};
	_Script_LLM_NPC_eventOnItemUnlocked_Parms Parms;
	Parms.ItemID=ItemID;
	OnItemUnlocked.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnItemUnlocked *********************************************************

// ********** Begin Delegate FOnItemGiven **********************************************************
struct Z_Construct_UDelegateFunction_LLM_NPC_OnItemGiven__DelegateSignature_Statics
{
	struct _Script_LLM_NPC_eventOnItemGiven_Parms
	{
		FName ItemID;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Inventory/NPCInventoryComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnItemGiven constinit property declarations **************************
	static const UECodeGen_Private::FNamePropertyParams NewProp_ItemID;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FOnItemGiven constinit property declarations ****************************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FOnItemGiven Property Definitions *************************************
const UECodeGen_Private::FNamePropertyParams Z_Construct_UDelegateFunction_LLM_NPC_OnItemGiven__DelegateSignature_Statics::NewProp_ItemID = { "ItemID", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_LLM_NPC_eventOnItemGiven_Parms, ItemID), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_LLM_NPC_OnItemGiven__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LLM_NPC_OnItemGiven__DelegateSignature_Statics::NewProp_ItemID,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnItemGiven__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FOnItemGiven Property Definitions ***************************************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_LLM_NPC_OnItemGiven__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_LLM_NPC, nullptr, "OnItemGiven__DelegateSignature", 	Z_Construct_UDelegateFunction_LLM_NPC_OnItemGiven__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnItemGiven__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_LLM_NPC_OnItemGiven__DelegateSignature_Statics::_Script_LLM_NPC_eventOnItemGiven_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnItemGiven__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_LLM_NPC_OnItemGiven__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_LLM_NPC_OnItemGiven__DelegateSignature_Statics::_Script_LLM_NPC_eventOnItemGiven_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnItemGiven__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_LLM_NPC_OnItemGiven__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnItemGiven_DelegateWrapper(const FMulticastScriptDelegate& OnItemGiven, FName ItemID)
{
	struct _Script_LLM_NPC_eventOnItemGiven_Parms
	{
		FName ItemID;
	};
	_Script_LLM_NPC_eventOnItemGiven_Parms Parms;
	Parms.ItemID=ItemID;
	OnItemGiven.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnItemGiven ************************************************************

// ********** Begin Class UNPCInventoryComponent Function CheckUnlockConditions ********************
struct Z_Construct_UFunction_UNPCInventoryComponent_CheckUnlockConditions_Statics
{
	struct NPCInventoryComponent_eventCheckUnlockConditions_Parms
	{
		FEmotionState CurrentState;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Inventory" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Evaluate unlock conditions for every item against the current emotion state.\n\x09 * Called automatically when the emotion state changes.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Inventory/NPCInventoryComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Evaluate unlock conditions for every item against the current emotion state.\nCalled automatically when the emotion state changes." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentState_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function CheckUnlockConditions constinit property declarations *****************
	static const UECodeGen_Private::FStructPropertyParams NewProp_CurrentState;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function CheckUnlockConditions constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function CheckUnlockConditions Property Definitions ****************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UNPCInventoryComponent_CheckUnlockConditions_Statics::NewProp_CurrentState = { "CurrentState", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NPCInventoryComponent_eventCheckUnlockConditions_Parms, CurrentState), Z_Construct_UScriptStruct_FEmotionState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentState_MetaData), NewProp_CurrentState_MetaData) }; // 1004811449
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNPCInventoryComponent_CheckUnlockConditions_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNPCInventoryComponent_CheckUnlockConditions_Statics::NewProp_CurrentState,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UNPCInventoryComponent_CheckUnlockConditions_Statics::PropPointers) < 2048);
// ********** End Function CheckUnlockConditions Property Definitions ******************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNPCInventoryComponent_CheckUnlockConditions_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UNPCInventoryComponent, nullptr, "CheckUnlockConditions", 	Z_Construct_UFunction_UNPCInventoryComponent_CheckUnlockConditions_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UNPCInventoryComponent_CheckUnlockConditions_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UNPCInventoryComponent_CheckUnlockConditions_Statics::NPCInventoryComponent_eventCheckUnlockConditions_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNPCInventoryComponent_CheckUnlockConditions_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNPCInventoryComponent_CheckUnlockConditions_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UNPCInventoryComponent_CheckUnlockConditions_Statics::NPCInventoryComponent_eventCheckUnlockConditions_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNPCInventoryComponent_CheckUnlockConditions()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNPCInventoryComponent_CheckUnlockConditions_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNPCInventoryComponent::execCheckUnlockConditions)
{
	P_GET_STRUCT_REF(FEmotionState,Z_Param_Out_CurrentState);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->CheckUnlockConditions(Z_Param_Out_CurrentState);
	P_NATIVE_END;
}
// ********** End Class UNPCInventoryComponent Function CheckUnlockConditions **********************

// ********** Begin Class UNPCInventoryComponent Function GetUnlockedItems *************************
struct Z_Construct_UFunction_UNPCInventoryComponent_GetUnlockedItems_Statics
{
	struct NPCInventoryComponent_eventGetUnlockedItems_Parms
	{
		TArray<FInventoryItem> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Inventory" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Return all items that have been unlocked (regardless of whether they have been given). */" },
#endif
		{ "ModuleRelativePath", "Inventory/NPCInventoryComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Return all items that have been unlocked (regardless of whether they have been given)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetUnlockedItems constinit property declarations **********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetUnlockedItems constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetUnlockedItems Property Definitions *********************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UNPCInventoryComponent_GetUnlockedItems_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FInventoryItem, METADATA_PARAMS(0, nullptr) }; // 1158787168
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UNPCInventoryComponent_GetUnlockedItems_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NPCInventoryComponent_eventGetUnlockedItems_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) }; // 1158787168
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNPCInventoryComponent_GetUnlockedItems_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNPCInventoryComponent_GetUnlockedItems_Statics::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNPCInventoryComponent_GetUnlockedItems_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UNPCInventoryComponent_GetUnlockedItems_Statics::PropPointers) < 2048);
// ********** End Function GetUnlockedItems Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNPCInventoryComponent_GetUnlockedItems_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UNPCInventoryComponent, nullptr, "GetUnlockedItems", 	Z_Construct_UFunction_UNPCInventoryComponent_GetUnlockedItems_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UNPCInventoryComponent_GetUnlockedItems_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UNPCInventoryComponent_GetUnlockedItems_Statics::NPCInventoryComponent_eventGetUnlockedItems_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNPCInventoryComponent_GetUnlockedItems_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNPCInventoryComponent_GetUnlockedItems_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UNPCInventoryComponent_GetUnlockedItems_Statics::NPCInventoryComponent_eventGetUnlockedItems_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNPCInventoryComponent_GetUnlockedItems()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNPCInventoryComponent_GetUnlockedItems_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNPCInventoryComponent::execGetUnlockedItems)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<FInventoryItem>*)Z_Param__Result=P_THIS->GetUnlockedItems();
	P_NATIVE_END;
}
// ********** End Class UNPCInventoryComponent Function GetUnlockedItems ***************************

// ********** Begin Class UNPCInventoryComponent Function HandleEmotionStateChanged ****************
struct Z_Construct_UFunction_UNPCInventoryComponent_HandleEmotionStateChanged_Statics
{
	struct NPCInventoryComponent_eventHandleEmotionStateChanged_Parms
	{
		FEmotionState OldState;
		FEmotionState NewState;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Callback bound to the Emotion subsystem's OnEmotionStateChanged delegate. */" },
#endif
		{ "ModuleRelativePath", "Inventory/NPCInventoryComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Callback bound to the Emotion subsystem's OnEmotionStateChanged delegate." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function HandleEmotionStateChanged constinit property declarations *************
	static const UECodeGen_Private::FStructPropertyParams NewProp_OldState;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NewState;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HandleEmotionStateChanged constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HandleEmotionStateChanged Property Definitions ************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UNPCInventoryComponent_HandleEmotionStateChanged_Statics::NewProp_OldState = { "OldState", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NPCInventoryComponent_eventHandleEmotionStateChanged_Parms, OldState), Z_Construct_UScriptStruct_FEmotionState, METADATA_PARAMS(0, nullptr) }; // 1004811449
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UNPCInventoryComponent_HandleEmotionStateChanged_Statics::NewProp_NewState = { "NewState", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NPCInventoryComponent_eventHandleEmotionStateChanged_Parms, NewState), Z_Construct_UScriptStruct_FEmotionState, METADATA_PARAMS(0, nullptr) }; // 1004811449
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNPCInventoryComponent_HandleEmotionStateChanged_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNPCInventoryComponent_HandleEmotionStateChanged_Statics::NewProp_OldState,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNPCInventoryComponent_HandleEmotionStateChanged_Statics::NewProp_NewState,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UNPCInventoryComponent_HandleEmotionStateChanged_Statics::PropPointers) < 2048);
// ********** End Function HandleEmotionStateChanged Property Definitions **************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNPCInventoryComponent_HandleEmotionStateChanged_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UNPCInventoryComponent, nullptr, "HandleEmotionStateChanged", 	Z_Construct_UFunction_UNPCInventoryComponent_HandleEmotionStateChanged_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UNPCInventoryComponent_HandleEmotionStateChanged_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UNPCInventoryComponent_HandleEmotionStateChanged_Statics::NPCInventoryComponent_eventHandleEmotionStateChanged_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNPCInventoryComponent_HandleEmotionStateChanged_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNPCInventoryComponent_HandleEmotionStateChanged_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UNPCInventoryComponent_HandleEmotionStateChanged_Statics::NPCInventoryComponent_eventHandleEmotionStateChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNPCInventoryComponent_HandleEmotionStateChanged()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNPCInventoryComponent_HandleEmotionStateChanged_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNPCInventoryComponent::execHandleEmotionStateChanged)
{
	P_GET_STRUCT(FEmotionState,Z_Param_OldState);
	P_GET_STRUCT(FEmotionState,Z_Param_NewState);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleEmotionStateChanged(Z_Param_OldState,Z_Param_NewState);
	P_NATIVE_END;
}
// ********** End Class UNPCInventoryComponent Function HandleEmotionStateChanged ******************

// ********** Begin Class UNPCInventoryComponent Function TryGiveItem ******************************
struct Z_Construct_UFunction_UNPCInventoryComponent_TryGiveItem_Statics
{
	struct NPCInventoryComponent_eventTryGiveItem_Parms
	{
		FName ItemID;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Inventory" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Mark an item as given to the player and broadcast OnItemGiven.\n\x09 * Only succeeds if the item is unlocked and has not already been given.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Inventory/NPCInventoryComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Mark an item as given to the player and broadcast OnItemGiven.\nOnly succeeds if the item is unlocked and has not already been given." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function TryGiveItem constinit property declarations ***************************
	static const UECodeGen_Private::FNamePropertyParams NewProp_ItemID;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function TryGiveItem constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function TryGiveItem Property Definitions **************************************
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UNPCInventoryComponent_TryGiveItem_Statics::NewProp_ItemID = { "ItemID", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NPCInventoryComponent_eventTryGiveItem_Parms, ItemID), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNPCInventoryComponent_TryGiveItem_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNPCInventoryComponent_TryGiveItem_Statics::NewProp_ItemID,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UNPCInventoryComponent_TryGiveItem_Statics::PropPointers) < 2048);
// ********** End Function TryGiveItem Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNPCInventoryComponent_TryGiveItem_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UNPCInventoryComponent, nullptr, "TryGiveItem", 	Z_Construct_UFunction_UNPCInventoryComponent_TryGiveItem_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UNPCInventoryComponent_TryGiveItem_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UNPCInventoryComponent_TryGiveItem_Statics::NPCInventoryComponent_eventTryGiveItem_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNPCInventoryComponent_TryGiveItem_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNPCInventoryComponent_TryGiveItem_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UNPCInventoryComponent_TryGiveItem_Statics::NPCInventoryComponent_eventTryGiveItem_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNPCInventoryComponent_TryGiveItem()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNPCInventoryComponent_TryGiveItem_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNPCInventoryComponent::execTryGiveItem)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_ItemID);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->TryGiveItem(Z_Param_ItemID);
	P_NATIVE_END;
}
// ********** End Class UNPCInventoryComponent Function TryGiveItem ********************************

// ********** Begin Class UNPCInventoryComponent Function UpdateKeywords ***************************
struct Z_Construct_UFunction_UNPCInventoryComponent_UpdateKeywords_Statics
{
	struct NPCInventoryComponent_eventUpdateKeywords_Parms
	{
		FString DialogueText;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Inventory" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Feed dialogue text so that keyword-based unlock conditions can be checked.\n\x09 * Typically called by the Dialogue subsystem whenever a new message is received.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Inventory/NPCInventoryComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Feed dialogue text so that keyword-based unlock conditions can be checked.\nTypically called by the Dialogue subsystem whenever a new message is received." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DialogueText_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function UpdateKeywords constinit property declarations ************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_DialogueText;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function UpdateKeywords constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function UpdateKeywords Property Definitions ***********************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UNPCInventoryComponent_UpdateKeywords_Statics::NewProp_DialogueText = { "DialogueText", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NPCInventoryComponent_eventUpdateKeywords_Parms, DialogueText), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DialogueText_MetaData), NewProp_DialogueText_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNPCInventoryComponent_UpdateKeywords_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNPCInventoryComponent_UpdateKeywords_Statics::NewProp_DialogueText,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UNPCInventoryComponent_UpdateKeywords_Statics::PropPointers) < 2048);
// ********** End Function UpdateKeywords Property Definitions *************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNPCInventoryComponent_UpdateKeywords_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UNPCInventoryComponent, nullptr, "UpdateKeywords", 	Z_Construct_UFunction_UNPCInventoryComponent_UpdateKeywords_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UNPCInventoryComponent_UpdateKeywords_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UNPCInventoryComponent_UpdateKeywords_Statics::NPCInventoryComponent_eventUpdateKeywords_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNPCInventoryComponent_UpdateKeywords_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNPCInventoryComponent_UpdateKeywords_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UNPCInventoryComponent_UpdateKeywords_Statics::NPCInventoryComponent_eventUpdateKeywords_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNPCInventoryComponent_UpdateKeywords()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNPCInventoryComponent_UpdateKeywords_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNPCInventoryComponent::execUpdateKeywords)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_DialogueText);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->UpdateKeywords(Z_Param_DialogueText);
	P_NATIVE_END;
}
// ********** End Class UNPCInventoryComponent Function UpdateKeywords *****************************

// ********** Begin Class UNPCInventoryComponent ***************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UNPCInventoryComponent;
UClass* UNPCInventoryComponent::GetPrivateStaticClass()
{
	using TClass = UNPCInventoryComponent;
	if (!Z_Registration_Info_UClass_UNPCInventoryComponent.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("NPCInventoryComponent"),
			Z_Registration_Info_UClass_UNPCInventoryComponent.InnerSingleton,
			StaticRegisterNativesUNPCInventoryComponent,
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
	return Z_Registration_Info_UClass_UNPCInventoryComponent.InnerSingleton;
}
UClass* Z_Construct_UClass_UNPCInventoryComponent_NoRegister()
{
	return UNPCInventoryComponent::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UNPCInventoryComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "LLMNPC" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Manages the NPC's item inventory and emotion-driven unlock system.\n *\n * Listens to the Emotion subsystem's OnEmotionStateChanged delegate and tracks\n * how long each unlock condition has been continuously satisfied.  When all\n * conditions for an item are met the item is unlocked and the NPC can give it\n * to the player.\n */" },
#endif
		{ "IncludePath", "Inventory/NPCInventoryComponent.h" },
		{ "ModuleRelativePath", "Inventory/NPCInventoryComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Manages the NPC's item inventory and emotion-driven unlock system.\n\nListens to the Emotion subsystem's OnEmotionStateChanged delegate and tracks\nhow long each unlock condition has been continuously satisfied.  When all\nconditions for an item are met the item is unlocked and the NPC can give it\nto the player." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnItemUnlocked_MetaData[] = {
		{ "Category", "NPC|Inventory" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Broadcast when an item transitions from locked to unlocked. */" },
#endif
		{ "ModuleRelativePath", "Inventory/NPCInventoryComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Broadcast when an item transitions from locked to unlocked." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnItemGiven_MetaData[] = {
		{ "Category", "NPC|Inventory" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Broadcast when an unlocked item is given to the player. */" },
#endif
		{ "ModuleRelativePath", "Inventory/NPCInventoryComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Broadcast when an unlocked item is given to the player." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InventoryDataAssetRef_MetaData[] = {
		{ "Category", "NPC|Inventory" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Data asset defining the item catalogue for this NPC. */" },
#endif
		{ "ModuleRelativePath", "Inventory/NPCInventoryComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Data asset defining the item catalogue for this NPC." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LoadedInventoryData_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Loaded inventory data asset (runtime). */" },
#endif
		{ "ModuleRelativePath", "Inventory/NPCInventoryComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Loaded inventory data asset (runtime)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RuntimeItems_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Runtime copy of items so we can mutate unlock/given state. */" },
#endif
		{ "ModuleRelativePath", "Inventory/NPCInventoryComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Runtime copy of items so we can mutate unlock/given state." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UNPCInventoryComponent constinit property declarations *******************
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnItemUnlocked;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnItemGiven;
	static const UECodeGen_Private::FSoftObjectPropertyParams NewProp_InventoryDataAssetRef;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LoadedInventoryData;
	static const UECodeGen_Private::FStructPropertyParams NewProp_RuntimeItems_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_RuntimeItems;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UNPCInventoryComponent constinit property declarations *********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("CheckUnlockConditions"), .Pointer = &UNPCInventoryComponent::execCheckUnlockConditions },
		{ .NameUTF8 = UTF8TEXT("GetUnlockedItems"), .Pointer = &UNPCInventoryComponent::execGetUnlockedItems },
		{ .NameUTF8 = UTF8TEXT("HandleEmotionStateChanged"), .Pointer = &UNPCInventoryComponent::execHandleEmotionStateChanged },
		{ .NameUTF8 = UTF8TEXT("TryGiveItem"), .Pointer = &UNPCInventoryComponent::execTryGiveItem },
		{ .NameUTF8 = UTF8TEXT("UpdateKeywords"), .Pointer = &UNPCInventoryComponent::execUpdateKeywords },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UNPCInventoryComponent_CheckUnlockConditions, "CheckUnlockConditions" }, // 1293570672
		{ &Z_Construct_UFunction_UNPCInventoryComponent_GetUnlockedItems, "GetUnlockedItems" }, // 797506180
		{ &Z_Construct_UFunction_UNPCInventoryComponent_HandleEmotionStateChanged, "HandleEmotionStateChanged" }, // 3722554724
		{ &Z_Construct_UFunction_UNPCInventoryComponent_TryGiveItem, "TryGiveItem" }, // 738719942
		{ &Z_Construct_UFunction_UNPCInventoryComponent_UpdateKeywords, "UpdateKeywords" }, // 72064817
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNPCInventoryComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UNPCInventoryComponent_Statics

// ********** Begin Class UNPCInventoryComponent Property Definitions ******************************
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UNPCInventoryComponent_Statics::NewProp_OnItemUnlocked = { "OnItemUnlocked", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNPCInventoryComponent, OnItemUnlocked), Z_Construct_UDelegateFunction_LLM_NPC_OnItemUnlocked__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnItemUnlocked_MetaData), NewProp_OnItemUnlocked_MetaData) }; // 1555971747
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UNPCInventoryComponent_Statics::NewProp_OnItemGiven = { "OnItemGiven", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNPCInventoryComponent, OnItemGiven), Z_Construct_UDelegateFunction_LLM_NPC_OnItemGiven__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnItemGiven_MetaData), NewProp_OnItemGiven_MetaData) }; // 3863114232
const UECodeGen_Private::FSoftObjectPropertyParams Z_Construct_UClass_UNPCInventoryComponent_Statics::NewProp_InventoryDataAssetRef = { "InventoryDataAssetRef", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::SoftObject, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNPCInventoryComponent, InventoryDataAssetRef), Z_Construct_UClass_UInventoryDataAsset_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InventoryDataAssetRef_MetaData), NewProp_InventoryDataAssetRef_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UNPCInventoryComponent_Statics::NewProp_LoadedInventoryData = { "LoadedInventoryData", nullptr, (EPropertyFlags)0x0144000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNPCInventoryComponent, LoadedInventoryData), Z_Construct_UClass_UInventoryDataAsset_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LoadedInventoryData_MetaData), NewProp_LoadedInventoryData_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UNPCInventoryComponent_Statics::NewProp_RuntimeItems_Inner = { "RuntimeItems", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FInventoryItem, METADATA_PARAMS(0, nullptr) }; // 1158787168
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UNPCInventoryComponent_Statics::NewProp_RuntimeItems = { "RuntimeItems", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNPCInventoryComponent, RuntimeItems), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RuntimeItems_MetaData), NewProp_RuntimeItems_MetaData) }; // 1158787168
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UNPCInventoryComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCInventoryComponent_Statics::NewProp_OnItemUnlocked,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCInventoryComponent_Statics::NewProp_OnItemGiven,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCInventoryComponent_Statics::NewProp_InventoryDataAssetRef,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCInventoryComponent_Statics::NewProp_LoadedInventoryData,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCInventoryComponent_Statics::NewProp_RuntimeItems_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCInventoryComponent_Statics::NewProp_RuntimeItems,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNPCInventoryComponent_Statics::PropPointers) < 2048);
// ********** End Class UNPCInventoryComponent Property Definitions ********************************
UObject* (*const Z_Construct_UClass_UNPCInventoryComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UNPCSubsystemComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNPCInventoryComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UNPCInventoryComponent_Statics::ClassParams = {
	&UNPCInventoryComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UNPCInventoryComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UNPCInventoryComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNPCInventoryComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UNPCInventoryComponent_Statics::Class_MetaDataParams)
};
void UNPCInventoryComponent::StaticRegisterNativesUNPCInventoryComponent()
{
	UClass* Class = UNPCInventoryComponent::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UNPCInventoryComponent_Statics::Funcs));
}
UClass* Z_Construct_UClass_UNPCInventoryComponent()
{
	if (!Z_Registration_Info_UClass_UNPCInventoryComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNPCInventoryComponent.OuterSingleton, Z_Construct_UClass_UNPCInventoryComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UNPCInventoryComponent.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UNPCInventoryComponent);
UNPCInventoryComponent::~UNPCInventoryComponent() {}
// ********** End Class UNPCInventoryComponent *****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Inventory_NPCInventoryComponent_h__Script_LLM_NPC_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNPCInventoryComponent, UNPCInventoryComponent::StaticClass, TEXT("UNPCInventoryComponent"), &Z_Registration_Info_UClass_UNPCInventoryComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNPCInventoryComponent), 1475262279U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Inventory_NPCInventoryComponent_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Inventory_NPCInventoryComponent_h__Script_LLM_NPC_3217814731{
	TEXT("/Script/LLM_NPC"),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Inventory_NPCInventoryComponent_h__Script_LLM_NPC_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Inventory_NPCInventoryComponent_h__Script_LLM_NPC_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
