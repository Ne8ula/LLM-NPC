// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Dialogue/DialogueComponent.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "LLM_NPC/Dialogue/ClaudeAPISubsystem.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeDialogueComponent() {}

// ********** Begin Cross Module References ********************************************************
LLM_NPC_API UClass* Z_Construct_UClass_UClaudeAPISubsystem_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UDialogueComponent();
LLM_NPC_API UClass* Z_Construct_UClass_UDialogueComponent_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UNPCConfigDataAsset_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UNPCSubsystemComponent();
LLM_NPC_API UEnum* Z_Construct_UEnum_LLM_NPC_EEmotionType();
LLM_NPC_API UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueHistoryCleared__DelegateSignature();
LLM_NPC_API UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueResponseReceived__DelegateSignature();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FClaudeAPIResponse();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FDetectedUserEmotion();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FNPCMessage();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FOnDialogueResponseReceived *******************************************
struct Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueResponseReceived__DelegateSignature_Statics
{
	struct _Script_LLM_NPC_eventOnDialogueResponseReceived_Parms
	{
		FString ResponseText;
		EEmotionType NPCEmotionHint;
		bool bShouldGiveItem;
		FName ItemID;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Delegate fired when a dialogue response is received from Claude. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/DialogueComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Delegate fired when a dialogue response is received from Claude." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ResponseText_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnDialogueResponseReceived constinit property declarations ***********
	static const UECodeGen_Private::FStrPropertyParams NewProp_ResponseText;
	static const UECodeGen_Private::FBytePropertyParams NewProp_NPCEmotionHint_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_NPCEmotionHint;
	static void NewProp_bShouldGiveItem_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldGiveItem;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ItemID;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FOnDialogueResponseReceived constinit property declarations *************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FOnDialogueResponseReceived Property Definitions **********************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueResponseReceived__DelegateSignature_Statics::NewProp_ResponseText = { "ResponseText", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_LLM_NPC_eventOnDialogueResponseReceived_Parms, ResponseText), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ResponseText_MetaData), NewProp_ResponseText_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueResponseReceived__DelegateSignature_Statics::NewProp_NPCEmotionHint_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueResponseReceived__DelegateSignature_Statics::NewProp_NPCEmotionHint = { "NPCEmotionHint", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_LLM_NPC_eventOnDialogueResponseReceived_Parms, NPCEmotionHint), Z_Construct_UEnum_LLM_NPC_EEmotionType, METADATA_PARAMS(0, nullptr) }; // 1184287893
void Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueResponseReceived__DelegateSignature_Statics::NewProp_bShouldGiveItem_SetBit(void* Obj)
{
	((_Script_LLM_NPC_eventOnDialogueResponseReceived_Parms*)Obj)->bShouldGiveItem = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueResponseReceived__DelegateSignature_Statics::NewProp_bShouldGiveItem = { "bShouldGiveItem", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(_Script_LLM_NPC_eventOnDialogueResponseReceived_Parms), &Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueResponseReceived__DelegateSignature_Statics::NewProp_bShouldGiveItem_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueResponseReceived__DelegateSignature_Statics::NewProp_ItemID = { "ItemID", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_LLM_NPC_eventOnDialogueResponseReceived_Parms, ItemID), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueResponseReceived__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueResponseReceived__DelegateSignature_Statics::NewProp_ResponseText,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueResponseReceived__DelegateSignature_Statics::NewProp_NPCEmotionHint_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueResponseReceived__DelegateSignature_Statics::NewProp_NPCEmotionHint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueResponseReceived__DelegateSignature_Statics::NewProp_bShouldGiveItem,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueResponseReceived__DelegateSignature_Statics::NewProp_ItemID,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueResponseReceived__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FOnDialogueResponseReceived Property Definitions ************************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueResponseReceived__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_LLM_NPC, nullptr, "OnDialogueResponseReceived__DelegateSignature", 	Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueResponseReceived__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueResponseReceived__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueResponseReceived__DelegateSignature_Statics::_Script_LLM_NPC_eventOnDialogueResponseReceived_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueResponseReceived__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueResponseReceived__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueResponseReceived__DelegateSignature_Statics::_Script_LLM_NPC_eventOnDialogueResponseReceived_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueResponseReceived__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueResponseReceived__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnDialogueResponseReceived_DelegateWrapper(const FMulticastScriptDelegate& OnDialogueResponseReceived, const FString& ResponseText, EEmotionType NPCEmotionHint, bool bShouldGiveItem, FName ItemID)
{
	struct _Script_LLM_NPC_eventOnDialogueResponseReceived_Parms
	{
		FString ResponseText;
		EEmotionType NPCEmotionHint;
		bool bShouldGiveItem;
		FName ItemID;
	};
	_Script_LLM_NPC_eventOnDialogueResponseReceived_Parms Parms;
	Parms.ResponseText=ResponseText;
	Parms.NPCEmotionHint=NPCEmotionHint;
	Parms.bShouldGiveItem=bShouldGiveItem ? true : false;
	Parms.ItemID=ItemID;
	OnDialogueResponseReceived.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnDialogueResponseReceived *********************************************

// ********** Begin Delegate FOnDialogueHistoryCleared *********************************************
struct Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueHistoryCleared__DelegateSignature_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Delegate fired when the dialogue history is cleared. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/DialogueComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Delegate fired when the dialogue history is cleared." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnDialogueHistoryCleared constinit property declarations *************
// ********** End Delegate FOnDialogueHistoryCleared constinit property declarations ***************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueHistoryCleared__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_LLM_NPC, nullptr, "OnDialogueHistoryCleared__DelegateSignature", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueHistoryCleared__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueHistoryCleared__DelegateSignature_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueHistoryCleared__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueHistoryCleared__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnDialogueHistoryCleared_DelegateWrapper(const FMulticastScriptDelegate& OnDialogueHistoryCleared)
{
	OnDialogueHistoryCleared.ProcessMulticastDelegate<UObject>(NULL);
}
// ********** End Delegate FOnDialogueHistoryCleared ***********************************************

// ********** Begin Class UDialogueComponent Function ClearConversationHistory *********************
struct Z_Construct_UFunction_UDialogueComponent_ClearConversationHistory_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Dialogue" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Clear all conversation history. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/DialogueComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Clear all conversation history." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ClearConversationHistory constinit property declarations **************
// ********** End Function ClearConversationHistory constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UDialogueComponent_ClearConversationHistory_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UDialogueComponent, nullptr, "ClearConversationHistory", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueComponent_ClearConversationHistory_Statics::Function_MetaDataParams), Z_Construct_UFunction_UDialogueComponent_ClearConversationHistory_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UDialogueComponent_ClearConversationHistory()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UDialogueComponent_ClearConversationHistory_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UDialogueComponent::execClearConversationHistory)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClearConversationHistory();
	P_NATIVE_END;
}
// ********** End Class UDialogueComponent Function ClearConversationHistory ***********************

// ********** Begin Class UDialogueComponent Function GetConversationHistory ***********************
struct Z_Construct_UFunction_UDialogueComponent_GetConversationHistory_Statics
{
	struct DialogueComponent_eventGetConversationHistory_Parms
	{
		TArray<FNPCMessage> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Dialogue" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get the current conversation history. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/DialogueComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get the current conversation history." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetConversationHistory constinit property declarations ****************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetConversationHistory constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetConversationHistory Property Definitions ***************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UDialogueComponent_GetConversationHistory_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FNPCMessage, METADATA_PARAMS(0, nullptr) }; // 3120298436
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UDialogueComponent_GetConversationHistory_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000008000582, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(DialogueComponent_eventGetConversationHistory_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReturnValue_MetaData), NewProp_ReturnValue_MetaData) }; // 3120298436
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UDialogueComponent_GetConversationHistory_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDialogueComponent_GetConversationHistory_Statics::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDialogueComponent_GetConversationHistory_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueComponent_GetConversationHistory_Statics::PropPointers) < 2048);
// ********** End Function GetConversationHistory Property Definitions *****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UDialogueComponent_GetConversationHistory_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UDialogueComponent, nullptr, "GetConversationHistory", 	Z_Construct_UFunction_UDialogueComponent_GetConversationHistory_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueComponent_GetConversationHistory_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UDialogueComponent_GetConversationHistory_Statics::DialogueComponent_eventGetConversationHistory_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueComponent_GetConversationHistory_Statics::Function_MetaDataParams), Z_Construct_UFunction_UDialogueComponent_GetConversationHistory_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UDialogueComponent_GetConversationHistory_Statics::DialogueComponent_eventGetConversationHistory_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDialogueComponent_GetConversationHistory()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UDialogueComponent_GetConversationHistory_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UDialogueComponent::execGetConversationHistory)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<FNPCMessage>*)Z_Param__Result=P_THIS->GetConversationHistory();
	P_NATIVE_END;
}
// ********** End Class UDialogueComponent Function GetConversationHistory *************************

// ********** Begin Class UDialogueComponent Function GetConversationLength ************************
struct Z_Construct_UFunction_UDialogueComponent_GetConversationLength_Statics
{
	struct DialogueComponent_eventGetConversationLength_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Dialogue" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get the number of messages in history. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/DialogueComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get the number of messages in history." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetConversationLength constinit property declarations *****************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetConversationLength constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetConversationLength Property Definitions ****************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UDialogueComponent_GetConversationLength_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(DialogueComponent_eventGetConversationLength_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UDialogueComponent_GetConversationLength_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDialogueComponent_GetConversationLength_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueComponent_GetConversationLength_Statics::PropPointers) < 2048);
// ********** End Function GetConversationLength Property Definitions ******************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UDialogueComponent_GetConversationLength_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UDialogueComponent, nullptr, "GetConversationLength", 	Z_Construct_UFunction_UDialogueComponent_GetConversationLength_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueComponent_GetConversationLength_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UDialogueComponent_GetConversationLength_Statics::DialogueComponent_eventGetConversationLength_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueComponent_GetConversationLength_Statics::Function_MetaDataParams), Z_Construct_UFunction_UDialogueComponent_GetConversationLength_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UDialogueComponent_GetConversationLength_Statics::DialogueComponent_eventGetConversationLength_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDialogueComponent_GetConversationLength()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UDialogueComponent_GetConversationLength_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UDialogueComponent::execGetConversationLength)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetConversationLength();
	P_NATIVE_END;
}
// ********** End Class UDialogueComponent Function GetConversationLength **************************

// ********** Begin Class UDialogueComponent Function IsWaitingForResponse *************************
struct Z_Construct_UFunction_UDialogueComponent_IsWaitingForResponse_Statics
{
	struct DialogueComponent_eventIsWaitingForResponse_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Dialogue" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Whether the NPC is currently waiting for a Claude response. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/DialogueComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Whether the NPC is currently waiting for a Claude response." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function IsWaitingForResponse constinit property declarations ******************
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsWaitingForResponse constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsWaitingForResponse Property Definitions *****************************
void Z_Construct_UFunction_UDialogueComponent_IsWaitingForResponse_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((DialogueComponent_eventIsWaitingForResponse_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UDialogueComponent_IsWaitingForResponse_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(DialogueComponent_eventIsWaitingForResponse_Parms), &Z_Construct_UFunction_UDialogueComponent_IsWaitingForResponse_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UDialogueComponent_IsWaitingForResponse_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDialogueComponent_IsWaitingForResponse_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueComponent_IsWaitingForResponse_Statics::PropPointers) < 2048);
// ********** End Function IsWaitingForResponse Property Definitions *******************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UDialogueComponent_IsWaitingForResponse_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UDialogueComponent, nullptr, "IsWaitingForResponse", 	Z_Construct_UFunction_UDialogueComponent_IsWaitingForResponse_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueComponent_IsWaitingForResponse_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UDialogueComponent_IsWaitingForResponse_Statics::DialogueComponent_eventIsWaitingForResponse_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueComponent_IsWaitingForResponse_Statics::Function_MetaDataParams), Z_Construct_UFunction_UDialogueComponent_IsWaitingForResponse_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UDialogueComponent_IsWaitingForResponse_Statics::DialogueComponent_eventIsWaitingForResponse_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDialogueComponent_IsWaitingForResponse()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UDialogueComponent_IsWaitingForResponse_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UDialogueComponent::execIsWaitingForResponse)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsWaitingForResponse();
	P_NATIVE_END;
}
// ********** End Class UDialogueComponent Function IsWaitingForResponse ***************************

// ********** Begin Class UDialogueComponent Function OnClaudeResponseReceived *********************
struct Z_Construct_UFunction_UDialogueComponent_OnClaudeResponseReceived_Statics
{
	struct DialogueComponent_eventOnClaudeResponseReceived_Parms
	{
		FClaudeAPIResponse Response;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Callback when Claude API responds. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/DialogueComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Callback when Claude API responds." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Response_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnClaudeResponseReceived constinit property declarations **************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Response;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function OnClaudeResponseReceived constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function OnClaudeResponseReceived Property Definitions *************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UDialogueComponent_OnClaudeResponseReceived_Statics::NewProp_Response = { "Response", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(DialogueComponent_eventOnClaudeResponseReceived_Parms, Response), Z_Construct_UScriptStruct_FClaudeAPIResponse, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Response_MetaData), NewProp_Response_MetaData) }; // 2514891443
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UDialogueComponent_OnClaudeResponseReceived_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDialogueComponent_OnClaudeResponseReceived_Statics::NewProp_Response,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueComponent_OnClaudeResponseReceived_Statics::PropPointers) < 2048);
// ********** End Function OnClaudeResponseReceived Property Definitions ***************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UDialogueComponent_OnClaudeResponseReceived_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UDialogueComponent, nullptr, "OnClaudeResponseReceived", 	Z_Construct_UFunction_UDialogueComponent_OnClaudeResponseReceived_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueComponent_OnClaudeResponseReceived_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UDialogueComponent_OnClaudeResponseReceived_Statics::DialogueComponent_eventOnClaudeResponseReceived_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00440401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueComponent_OnClaudeResponseReceived_Statics::Function_MetaDataParams), Z_Construct_UFunction_UDialogueComponent_OnClaudeResponseReceived_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UDialogueComponent_OnClaudeResponseReceived_Statics::DialogueComponent_eventOnClaudeResponseReceived_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDialogueComponent_OnClaudeResponseReceived()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UDialogueComponent_OnClaudeResponseReceived_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UDialogueComponent::execOnClaudeResponseReceived)
{
	P_GET_STRUCT_REF(FClaudeAPIResponse,Z_Param_Out_Response);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnClaudeResponseReceived(Z_Param_Out_Response);
	P_NATIVE_END;
}
// ********** End Class UDialogueComponent Function OnClaudeResponseReceived ***********************

// ********** Begin Class UDialogueComponent Function SendUserMessage ******************************
struct Z_Construct_UFunction_UDialogueComponent_SendUserMessage_Statics
{
	struct DialogueComponent_eventSendUserMessage_Parms
	{
		FString UserMessage;
		FDetectedUserEmotion UserEmotion;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Dialogue" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Send a user message to the NPC, including detected user emotion context.\n\x09 * Assembles the full conversation context and routes through ClaudeAPISubsystem.\n\x09 *\n\x09 * @param UserMessage    The player's text input.\n\x09 * @param UserEmotion    Detected emotion from the player (facial recognition or default).\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Dialogue/DialogueComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Send a user message to the NPC, including detected user emotion context.\nAssembles the full conversation context and routes through ClaudeAPISubsystem.\n\n@param UserMessage    The player's text input.\n@param UserEmotion    Detected emotion from the player (facial recognition or default)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UserMessage_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UserEmotion_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function SendUserMessage constinit property declarations ***********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_UserMessage;
	static const UECodeGen_Private::FStructPropertyParams NewProp_UserEmotion;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SendUserMessage constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SendUserMessage Property Definitions **********************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UDialogueComponent_SendUserMessage_Statics::NewProp_UserMessage = { "UserMessage", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(DialogueComponent_eventSendUserMessage_Parms, UserMessage), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UserMessage_MetaData), NewProp_UserMessage_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UDialogueComponent_SendUserMessage_Statics::NewProp_UserEmotion = { "UserEmotion", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(DialogueComponent_eventSendUserMessage_Parms, UserEmotion), Z_Construct_UScriptStruct_FDetectedUserEmotion, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UserEmotion_MetaData), NewProp_UserEmotion_MetaData) }; // 3137125811
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UDialogueComponent_SendUserMessage_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDialogueComponent_SendUserMessage_Statics::NewProp_UserMessage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDialogueComponent_SendUserMessage_Statics::NewProp_UserEmotion,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueComponent_SendUserMessage_Statics::PropPointers) < 2048);
// ********** End Function SendUserMessage Property Definitions ************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UDialogueComponent_SendUserMessage_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UDialogueComponent, nullptr, "SendUserMessage", 	Z_Construct_UFunction_UDialogueComponent_SendUserMessage_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueComponent_SendUserMessage_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UDialogueComponent_SendUserMessage_Statics::DialogueComponent_eventSendUserMessage_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueComponent_SendUserMessage_Statics::Function_MetaDataParams), Z_Construct_UFunction_UDialogueComponent_SendUserMessage_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UDialogueComponent_SendUserMessage_Statics::DialogueComponent_eventSendUserMessage_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDialogueComponent_SendUserMessage()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UDialogueComponent_SendUserMessage_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UDialogueComponent::execSendUserMessage)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_UserMessage);
	P_GET_STRUCT_REF(FDetectedUserEmotion,Z_Param_Out_UserEmotion);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SendUserMessage(Z_Param_UserMessage,Z_Param_Out_UserEmotion);
	P_NATIVE_END;
}
// ********** End Class UDialogueComponent Function SendUserMessage ********************************

// ********** Begin Class UDialogueComponent *******************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UDialogueComponent;
UClass* UDialogueComponent::GetPrivateStaticClass()
{
	using TClass = UDialogueComponent;
	if (!Z_Registration_Info_UClass_UDialogueComponent.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("DialogueComponent"),
			Z_Registration_Info_UClass_UDialogueComponent.InnerSingleton,
			StaticRegisterNativesUDialogueComponent,
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
	return Z_Registration_Info_UClass_UDialogueComponent.InnerSingleton;
}
UClass* Z_Construct_UClass_UDialogueComponent_NoRegister()
{
	return UDialogueComponent::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UDialogueComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "LLMNPC" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Manages dialogue state for a single NPC.\n *\n * Maintains conversation history, assembles context (system prompt + emotion annotations),\n * and routes messages through the ClaudeAPISubsystem. Each NPC actor gets its own\n * DialogueComponent instance.\n */" },
#endif
		{ "IncludePath", "Dialogue/DialogueComponent.h" },
		{ "ModuleRelativePath", "Dialogue/DialogueComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Manages dialogue state for a single NPC.\n\nMaintains conversation history, assembles context (system prompt + emotion annotations),\nand routes messages through the ClaudeAPISubsystem. Each NPC actor gets its own\nDialogueComponent instance." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnDialogueResponseReceived_MetaData[] = {
		{ "Category", "NPC|Dialogue" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Fired when a dialogue response is received. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/DialogueComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Fired when a dialogue response is received." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnDialogueHistoryCleared_MetaData[] = {
		{ "Category", "NPC|Dialogue" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Fired when conversation history is cleared. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/DialogueComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Fired when conversation history is cleared." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NPCConfig_MetaData[] = {
		{ "Category", "NPC|Dialogue" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The NPC configuration data asset providing system prompt and model settings. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/DialogueComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The NPC configuration data asset providing system prompt and model settings." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ConversationHistory_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Conversation history for this NPC. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/DialogueComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Conversation history for this NPC." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CachedClaudeSubsystem_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Cached reference to the ClaudeAPISubsystem. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/DialogueComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Cached reference to the ClaudeAPISubsystem." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UDialogueComponent constinit property declarations ***********************
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnDialogueResponseReceived;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnDialogueHistoryCleared;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NPCConfig;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ConversationHistory_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ConversationHistory;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CachedClaudeSubsystem;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDialogueComponent constinit property declarations *************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("ClearConversationHistory"), .Pointer = &UDialogueComponent::execClearConversationHistory },
		{ .NameUTF8 = UTF8TEXT("GetConversationHistory"), .Pointer = &UDialogueComponent::execGetConversationHistory },
		{ .NameUTF8 = UTF8TEXT("GetConversationLength"), .Pointer = &UDialogueComponent::execGetConversationLength },
		{ .NameUTF8 = UTF8TEXT("IsWaitingForResponse"), .Pointer = &UDialogueComponent::execIsWaitingForResponse },
		{ .NameUTF8 = UTF8TEXT("OnClaudeResponseReceived"), .Pointer = &UDialogueComponent::execOnClaudeResponseReceived },
		{ .NameUTF8 = UTF8TEXT("SendUserMessage"), .Pointer = &UDialogueComponent::execSendUserMessage },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDialogueComponent_ClearConversationHistory, "ClearConversationHistory" }, // 733545102
		{ &Z_Construct_UFunction_UDialogueComponent_GetConversationHistory, "GetConversationHistory" }, // 3337327215
		{ &Z_Construct_UFunction_UDialogueComponent_GetConversationLength, "GetConversationLength" }, // 3147914470
		{ &Z_Construct_UFunction_UDialogueComponent_IsWaitingForResponse, "IsWaitingForResponse" }, // 4238014622
		{ &Z_Construct_UFunction_UDialogueComponent_OnClaudeResponseReceived, "OnClaudeResponseReceived" }, // 3133265944
		{ &Z_Construct_UFunction_UDialogueComponent_SendUserMessage, "SendUserMessage" }, // 2926371485
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDialogueComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UDialogueComponent_Statics

// ********** Begin Class UDialogueComponent Property Definitions **********************************
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UDialogueComponent_Statics::NewProp_OnDialogueResponseReceived = { "OnDialogueResponseReceived", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDialogueComponent, OnDialogueResponseReceived), Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueResponseReceived__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnDialogueResponseReceived_MetaData), NewProp_OnDialogueResponseReceived_MetaData) }; // 898070931
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UDialogueComponent_Statics::NewProp_OnDialogueHistoryCleared = { "OnDialogueHistoryCleared", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDialogueComponent, OnDialogueHistoryCleared), Z_Construct_UDelegateFunction_LLM_NPC_OnDialogueHistoryCleared__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnDialogueHistoryCleared_MetaData), NewProp_OnDialogueHistoryCleared_MetaData) }; // 704566040
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UDialogueComponent_Statics::NewProp_NPCConfig = { "NPCConfig", nullptr, (EPropertyFlags)0x0114000000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDialogueComponent, NPCConfig), Z_Construct_UClass_UNPCConfigDataAsset_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NPCConfig_MetaData), NewProp_NPCConfig_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UDialogueComponent_Statics::NewProp_ConversationHistory_Inner = { "ConversationHistory", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FNPCMessage, METADATA_PARAMS(0, nullptr) }; // 3120298436
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UDialogueComponent_Statics::NewProp_ConversationHistory = { "ConversationHistory", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDialogueComponent, ConversationHistory), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ConversationHistory_MetaData), NewProp_ConversationHistory_MetaData) }; // 3120298436
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UDialogueComponent_Statics::NewProp_CachedClaudeSubsystem = { "CachedClaudeSubsystem", nullptr, (EPropertyFlags)0x0144000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDialogueComponent, CachedClaudeSubsystem), Z_Construct_UClass_UClaudeAPISubsystem_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CachedClaudeSubsystem_MetaData), NewProp_CachedClaudeSubsystem_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UDialogueComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDialogueComponent_Statics::NewProp_OnDialogueResponseReceived,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDialogueComponent_Statics::NewProp_OnDialogueHistoryCleared,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDialogueComponent_Statics::NewProp_NPCConfig,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDialogueComponent_Statics::NewProp_ConversationHistory_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDialogueComponent_Statics::NewProp_ConversationHistory,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDialogueComponent_Statics::NewProp_CachedClaudeSubsystem,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UDialogueComponent_Statics::PropPointers) < 2048);
// ********** End Class UDialogueComponent Property Definitions ************************************
UObject* (*const Z_Construct_UClass_UDialogueComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UNPCSubsystemComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UDialogueComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UDialogueComponent_Statics::ClassParams = {
	&UDialogueComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UDialogueComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UDialogueComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UDialogueComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UDialogueComponent_Statics::Class_MetaDataParams)
};
void UDialogueComponent::StaticRegisterNativesUDialogueComponent()
{
	UClass* Class = UDialogueComponent::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UDialogueComponent_Statics::Funcs));
}
UClass* Z_Construct_UClass_UDialogueComponent()
{
	if (!Z_Registration_Info_UClass_UDialogueComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDialogueComponent.OuterSingleton, Z_Construct_UClass_UDialogueComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UDialogueComponent.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDialogueComponent);
UDialogueComponent::~UDialogueComponent() {}
// ********** End Class UDialogueComponent *********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueComponent_h__Script_LLM_NPC_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDialogueComponent, UDialogueComponent::StaticClass, TEXT("UDialogueComponent"), &Z_Registration_Info_UClass_UDialogueComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDialogueComponent), 3711463255U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueComponent_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueComponent_h__Script_LLM_NPC_3217176712{
	TEXT("/Script/LLM_NPC"),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueComponent_h__Script_LLM_NPC_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueComponent_h__Script_LLM_NPC_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
