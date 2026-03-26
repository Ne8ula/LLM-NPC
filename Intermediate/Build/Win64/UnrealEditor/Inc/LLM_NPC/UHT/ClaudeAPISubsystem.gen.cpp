// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Dialogue/ClaudeAPISubsystem.h"
#include "Engine/GameInstance.h"
#include "LLM_NPC/Core/NPCTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeClaudeAPISubsystem() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UGameInstanceSubsystem();
LLM_NPC_API UClass* Z_Construct_UClass_UClaudeAPISubsystem();
LLM_NPC_API UClass* Z_Construct_UClass_UClaudeAPISubsystem_NoRegister();
LLM_NPC_API UEnum* Z_Construct_UEnum_LLM_NPC_EEmotionType();
LLM_NPC_API UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeRequestComplete__DelegateSignature();
LLM_NPC_API UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeResponseReceived__DelegateSignature();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FClaudeAPIResponse();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FNPCMessage();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FClaudeAPIResponse ************************************************
struct Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FClaudeAPIResponse); }
	static inline consteval int16 GetStructAlignment() { return alignof(FClaudeAPIResponse); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Parsed response from the Claude API.\n * Includes the NPC's dialogue text plus structured metadata for emotion and item triggers.\n */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ClaudeAPISubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Parsed response from the Claude API.\nIncludes the NPC's dialogue text plus structured metadata for emotion and item triggers." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ResponseText_MetaData[] = {
		{ "Category", "Claude" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The NPC's dialogue text response. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ClaudeAPISubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The NPC's dialogue text response." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NPCEmotionUpdate_MetaData[] = {
		{ "Category", "Claude" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Emotion hint parsed from Claude's structured output. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ClaudeAPISubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Emotion hint parsed from Claude's structured output." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bShouldGiveItem_MetaData[] = {
		{ "Category", "Claude" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Whether the NPC should give an item to the player. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ClaudeAPISubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Whether the NPC should give an item to the player." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemID_MetaData[] = {
		{ "Category", "Claude" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Item ID if bShouldGiveItem is true. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ClaudeAPISubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Item ID if bShouldGiveItem is true." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bSuccess_MetaData[] = {
		{ "Category", "Claude" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Whether the request was successful. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ClaudeAPISubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Whether the request was successful." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ErrorMessage_MetaData[] = {
		{ "Category", "Claude" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Error message if the request failed. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ClaudeAPISubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Error message if the request failed." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FClaudeAPIResponse constinit property declarations ****************
	static const UECodeGen_Private::FStrPropertyParams NewProp_ResponseText;
	static const UECodeGen_Private::FBytePropertyParams NewProp_NPCEmotionUpdate_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_NPCEmotionUpdate;
	static void NewProp_bShouldGiveItem_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldGiveItem;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ItemID;
	static void NewProp_bSuccess_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSuccess;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ErrorMessage;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FClaudeAPIResponse constinit property declarations ******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FClaudeAPIResponse>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FClaudeAPIResponse;
class UScriptStruct* FClaudeAPIResponse::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FClaudeAPIResponse.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FClaudeAPIResponse.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FClaudeAPIResponse, (UObject*)Z_Construct_UPackage__Script_LLM_NPC(), TEXT("ClaudeAPIResponse"));
	}
	return Z_Registration_Info_UScriptStruct_FClaudeAPIResponse.OuterSingleton;
	}

// ********** Begin ScriptStruct FClaudeAPIResponse Property Definitions ***************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics::NewProp_ResponseText = { "ResponseText", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FClaudeAPIResponse, ResponseText), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ResponseText_MetaData), NewProp_ResponseText_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics::NewProp_NPCEmotionUpdate_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics::NewProp_NPCEmotionUpdate = { "NPCEmotionUpdate", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FClaudeAPIResponse, NPCEmotionUpdate), Z_Construct_UEnum_LLM_NPC_EEmotionType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NPCEmotionUpdate_MetaData), NewProp_NPCEmotionUpdate_MetaData) }; // 1184287893
void Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics::NewProp_bShouldGiveItem_SetBit(void* Obj)
{
	((FClaudeAPIResponse*)Obj)->bShouldGiveItem = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics::NewProp_bShouldGiveItem = { "bShouldGiveItem", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FClaudeAPIResponse), &Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics::NewProp_bShouldGiveItem_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bShouldGiveItem_MetaData), NewProp_bShouldGiveItem_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics::NewProp_ItemID = { "ItemID", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FClaudeAPIResponse, ItemID), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ItemID_MetaData), NewProp_ItemID_MetaData) };
void Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics::NewProp_bSuccess_SetBit(void* Obj)
{
	((FClaudeAPIResponse*)Obj)->bSuccess = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics::NewProp_bSuccess = { "bSuccess", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FClaudeAPIResponse), &Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics::NewProp_bSuccess_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bSuccess_MetaData), NewProp_bSuccess_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics::NewProp_ErrorMessage = { "ErrorMessage", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FClaudeAPIResponse, ErrorMessage), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ErrorMessage_MetaData), NewProp_ErrorMessage_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics::NewProp_ResponseText,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics::NewProp_NPCEmotionUpdate_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics::NewProp_NPCEmotionUpdate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics::NewProp_bShouldGiveItem,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics::NewProp_ItemID,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics::NewProp_bSuccess,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics::NewProp_ErrorMessage,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FClaudeAPIResponse Property Definitions *****************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
	nullptr,
	&NewStructOps,
	"ClaudeAPIResponse",
	Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics::PropPointers),
	sizeof(FClaudeAPIResponse),
	alignof(FClaudeAPIResponse),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FClaudeAPIResponse()
{
	if (!Z_Registration_Info_UScriptStruct_FClaudeAPIResponse.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FClaudeAPIResponse.InnerSingleton, Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FClaudeAPIResponse.InnerSingleton);
}
// ********** End ScriptStruct FClaudeAPIResponse **************************************************

// ********** Begin Delegate FOnClaudeResponseReceived *********************************************
struct Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeResponseReceived__DelegateSignature_Statics
{
	struct _Script_LLM_NPC_eventOnClaudeResponseReceived_Parms
	{
		FClaudeAPIResponse Response;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Delegate fired when a Claude API response is received. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ClaudeAPISubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Delegate fired when a Claude API response is received." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Response_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnClaudeResponseReceived constinit property declarations *************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Response;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FOnClaudeResponseReceived constinit property declarations ***************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FOnClaudeResponseReceived Property Definitions ************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeResponseReceived__DelegateSignature_Statics::NewProp_Response = { "Response", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_LLM_NPC_eventOnClaudeResponseReceived_Parms, Response), Z_Construct_UScriptStruct_FClaudeAPIResponse, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Response_MetaData), NewProp_Response_MetaData) }; // 2514891443
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeResponseReceived__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeResponseReceived__DelegateSignature_Statics::NewProp_Response,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeResponseReceived__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FOnClaudeResponseReceived Property Definitions **************************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeResponseReceived__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_LLM_NPC, nullptr, "OnClaudeResponseReceived__DelegateSignature", 	Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeResponseReceived__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeResponseReceived__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeResponseReceived__DelegateSignature_Statics::_Script_LLM_NPC_eventOnClaudeResponseReceived_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00530000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeResponseReceived__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeResponseReceived__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeResponseReceived__DelegateSignature_Statics::_Script_LLM_NPC_eventOnClaudeResponseReceived_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeResponseReceived__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeResponseReceived__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnClaudeResponseReceived_DelegateWrapper(const FMulticastScriptDelegate& OnClaudeResponseReceived, FClaudeAPIResponse const& Response)
{
	struct _Script_LLM_NPC_eventOnClaudeResponseReceived_Parms
	{
		FClaudeAPIResponse Response;
	};
	_Script_LLM_NPC_eventOnClaudeResponseReceived_Parms Parms;
	Parms.Response=Response;
	OnClaudeResponseReceived.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnClaudeResponseReceived ***********************************************

// ********** Begin Delegate FOnClaudeRequestComplete **********************************************
struct Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeRequestComplete__DelegateSignature_Statics
{
	struct _Script_LLM_NPC_eventOnClaudeRequestComplete_Parms
	{
		FClaudeAPIResponse Response;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Delegate for single-request completion callbacks. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ClaudeAPISubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Delegate for single-request completion callbacks." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Response_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnClaudeRequestComplete constinit property declarations **************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Response;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FOnClaudeRequestComplete constinit property declarations ****************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FOnClaudeRequestComplete Property Definitions *************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeRequestComplete__DelegateSignature_Statics::NewProp_Response = { "Response", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_LLM_NPC_eventOnClaudeRequestComplete_Parms, Response), Z_Construct_UScriptStruct_FClaudeAPIResponse, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Response_MetaData), NewProp_Response_MetaData) }; // 2514891443
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeRequestComplete__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeRequestComplete__DelegateSignature_Statics::NewProp_Response,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeRequestComplete__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FOnClaudeRequestComplete Property Definitions ***************************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeRequestComplete__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_LLM_NPC, nullptr, "OnClaudeRequestComplete__DelegateSignature", 	Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeRequestComplete__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeRequestComplete__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeRequestComplete__DelegateSignature_Statics::_Script_LLM_NPC_eventOnClaudeRequestComplete_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00520000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeRequestComplete__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeRequestComplete__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeRequestComplete__DelegateSignature_Statics::_Script_LLM_NPC_eventOnClaudeRequestComplete_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeRequestComplete__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeRequestComplete__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnClaudeRequestComplete_DelegateWrapper(const FScriptDelegate& OnClaudeRequestComplete, FClaudeAPIResponse const& Response)
{
	struct _Script_LLM_NPC_eventOnClaudeRequestComplete_Parms
	{
		FClaudeAPIResponse Response;
	};
	_Script_LLM_NPC_eventOnClaudeRequestComplete_Parms Parms;
	Parms.Response=Response;
	OnClaudeRequestComplete.ProcessDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnClaudeRequestComplete ************************************************

// ********** Begin Class UClaudeAPISubsystem Function IsAPIKeyConfigured **************************
struct Z_Construct_UFunction_UClaudeAPISubsystem_IsAPIKeyConfigured_Statics
{
	struct ClaudeAPISubsystem_eventIsAPIKeyConfigured_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Claude" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Check if the API key is configured and the subsystem is ready. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ClaudeAPISubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Check if the API key is configured and the subsystem is ready." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function IsAPIKeyConfigured constinit property declarations ********************
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsAPIKeyConfigured constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsAPIKeyConfigured Property Definitions *******************************
void Z_Construct_UFunction_UClaudeAPISubsystem_IsAPIKeyConfigured_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((ClaudeAPISubsystem_eventIsAPIKeyConfigured_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UClaudeAPISubsystem_IsAPIKeyConfigured_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ClaudeAPISubsystem_eventIsAPIKeyConfigured_Parms), &Z_Construct_UFunction_UClaudeAPISubsystem_IsAPIKeyConfigured_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UClaudeAPISubsystem_IsAPIKeyConfigured_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UClaudeAPISubsystem_IsAPIKeyConfigured_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UClaudeAPISubsystem_IsAPIKeyConfigured_Statics::PropPointers) < 2048);
// ********** End Function IsAPIKeyConfigured Property Definitions *********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UClaudeAPISubsystem_IsAPIKeyConfigured_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UClaudeAPISubsystem, nullptr, "IsAPIKeyConfigured", 	Z_Construct_UFunction_UClaudeAPISubsystem_IsAPIKeyConfigured_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UClaudeAPISubsystem_IsAPIKeyConfigured_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UClaudeAPISubsystem_IsAPIKeyConfigured_Statics::ClaudeAPISubsystem_eventIsAPIKeyConfigured_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UClaudeAPISubsystem_IsAPIKeyConfigured_Statics::Function_MetaDataParams), Z_Construct_UFunction_UClaudeAPISubsystem_IsAPIKeyConfigured_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UClaudeAPISubsystem_IsAPIKeyConfigured_Statics::ClaudeAPISubsystem_eventIsAPIKeyConfigured_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UClaudeAPISubsystem_IsAPIKeyConfigured()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UClaudeAPISubsystem_IsAPIKeyConfigured_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UClaudeAPISubsystem::execIsAPIKeyConfigured)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsAPIKeyConfigured();
	P_NATIVE_END;
}
// ********** End Class UClaudeAPISubsystem Function IsAPIKeyConfigured ****************************

// ********** Begin Class UClaudeAPISubsystem Function SendMessage *********************************
struct Z_Construct_UFunction_UClaudeAPISubsystem_SendMessage_Statics
{
	struct ClaudeAPISubsystem_eventSendMessage_Parms
	{
		FString SystemPrompt;
		TArray<FNPCMessage> ConversationHistory;
		FString ModelID;
		int32 MaxTokens;
		FScriptDelegate OnComplete;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Claude" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Send a message to the Claude API using the Anthropic Messages API format.\n\x09 *\n\x09 * @param SystemPrompt     The system prompt establishing NPC personality and rules.\n\x09 * @param ConversationHistory  Array of prior messages for context.\n\x09 * @param ModelID          Claude model identifier (e.g., \"claude-sonnet-4-6\").\n\x09 * @param MaxTokens        Maximum tokens for the response.\n\x09 * @param OnComplete       Callback delegate fired when the response arrives.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ClaudeAPISubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Send a message to the Claude API using the Anthropic Messages API format.\n\n@param SystemPrompt     The system prompt establishing NPC personality and rules.\n@param ConversationHistory  Array of prior messages for context.\n@param ModelID          Claude model identifier (e.g., \"claude-sonnet-4-6\").\n@param MaxTokens        Maximum tokens for the response.\n@param OnComplete       Callback delegate fired when the response arrives." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SystemPrompt_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ConversationHistory_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ModelID_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnComplete_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function SendMessage constinit property declarations ***************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_SystemPrompt;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ConversationHistory_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ConversationHistory;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ModelID;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxTokens;
	static const UECodeGen_Private::FDelegatePropertyParams NewProp_OnComplete;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SendMessage constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SendMessage Property Definitions **************************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UClaudeAPISubsystem_SendMessage_Statics::NewProp_SystemPrompt = { "SystemPrompt", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ClaudeAPISubsystem_eventSendMessage_Parms, SystemPrompt), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SystemPrompt_MetaData), NewProp_SystemPrompt_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UClaudeAPISubsystem_SendMessage_Statics::NewProp_ConversationHistory_Inner = { "ConversationHistory", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FNPCMessage, METADATA_PARAMS(0, nullptr) }; // 3120298436
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UClaudeAPISubsystem_SendMessage_Statics::NewProp_ConversationHistory = { "ConversationHistory", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ClaudeAPISubsystem_eventSendMessage_Parms, ConversationHistory), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ConversationHistory_MetaData), NewProp_ConversationHistory_MetaData) }; // 3120298436
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UClaudeAPISubsystem_SendMessage_Statics::NewProp_ModelID = { "ModelID", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ClaudeAPISubsystem_eventSendMessage_Parms, ModelID), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ModelID_MetaData), NewProp_ModelID_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UClaudeAPISubsystem_SendMessage_Statics::NewProp_MaxTokens = { "MaxTokens", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ClaudeAPISubsystem_eventSendMessage_Parms, MaxTokens), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UClaudeAPISubsystem_SendMessage_Statics::NewProp_OnComplete = { "OnComplete", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ClaudeAPISubsystem_eventSendMessage_Parms, OnComplete), Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeRequestComplete__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnComplete_MetaData), NewProp_OnComplete_MetaData) }; // 2697653787
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UClaudeAPISubsystem_SendMessage_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UClaudeAPISubsystem_SendMessage_Statics::NewProp_SystemPrompt,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UClaudeAPISubsystem_SendMessage_Statics::NewProp_ConversationHistory_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UClaudeAPISubsystem_SendMessage_Statics::NewProp_ConversationHistory,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UClaudeAPISubsystem_SendMessage_Statics::NewProp_ModelID,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UClaudeAPISubsystem_SendMessage_Statics::NewProp_MaxTokens,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UClaudeAPISubsystem_SendMessage_Statics::NewProp_OnComplete,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UClaudeAPISubsystem_SendMessage_Statics::PropPointers) < 2048);
// ********** End Function SendMessage Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UClaudeAPISubsystem_SendMessage_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UClaudeAPISubsystem, nullptr, "SendMessage", 	Z_Construct_UFunction_UClaudeAPISubsystem_SendMessage_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UClaudeAPISubsystem_SendMessage_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UClaudeAPISubsystem_SendMessage_Statics::ClaudeAPISubsystem_eventSendMessage_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UClaudeAPISubsystem_SendMessage_Statics::Function_MetaDataParams), Z_Construct_UFunction_UClaudeAPISubsystem_SendMessage_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UClaudeAPISubsystem_SendMessage_Statics::ClaudeAPISubsystem_eventSendMessage_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UClaudeAPISubsystem_SendMessage()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UClaudeAPISubsystem_SendMessage_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UClaudeAPISubsystem::execSendMessage)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_SystemPrompt);
	P_GET_TARRAY_REF(FNPCMessage,Z_Param_Out_ConversationHistory);
	P_GET_PROPERTY(FStrProperty,Z_Param_ModelID);
	P_GET_PROPERTY(FIntProperty,Z_Param_MaxTokens);
	P_GET_PROPERTY_REF(FDelegateProperty,Z_Param_Out_OnComplete);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SendMessage(Z_Param_SystemPrompt,Z_Param_Out_ConversationHistory,Z_Param_ModelID,Z_Param_MaxTokens,FOnClaudeRequestComplete(Z_Param_Out_OnComplete));
	P_NATIVE_END;
}
// ********** End Class UClaudeAPISubsystem Function SendMessage ***********************************

// ********** Begin Class UClaudeAPISubsystem Function SetAPIKey ***********************************
struct Z_Construct_UFunction_UClaudeAPISubsystem_SetAPIKey_Statics
{
	struct ClaudeAPISubsystem_eventSetAPIKey_Parms
	{
		FString InAPIKey;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Claude" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Set the API key at runtime (overrides environment variable). */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ClaudeAPISubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Set the API key at runtime (overrides environment variable)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InAPIKey_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetAPIKey constinit property declarations *****************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_InAPIKey;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetAPIKey constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetAPIKey Property Definitions ****************************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UClaudeAPISubsystem_SetAPIKey_Statics::NewProp_InAPIKey = { "InAPIKey", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ClaudeAPISubsystem_eventSetAPIKey_Parms, InAPIKey), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InAPIKey_MetaData), NewProp_InAPIKey_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UClaudeAPISubsystem_SetAPIKey_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UClaudeAPISubsystem_SetAPIKey_Statics::NewProp_InAPIKey,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UClaudeAPISubsystem_SetAPIKey_Statics::PropPointers) < 2048);
// ********** End Function SetAPIKey Property Definitions ******************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UClaudeAPISubsystem_SetAPIKey_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UClaudeAPISubsystem, nullptr, "SetAPIKey", 	Z_Construct_UFunction_UClaudeAPISubsystem_SetAPIKey_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UClaudeAPISubsystem_SetAPIKey_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UClaudeAPISubsystem_SetAPIKey_Statics::ClaudeAPISubsystem_eventSetAPIKey_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UClaudeAPISubsystem_SetAPIKey_Statics::Function_MetaDataParams), Z_Construct_UFunction_UClaudeAPISubsystem_SetAPIKey_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UClaudeAPISubsystem_SetAPIKey_Statics::ClaudeAPISubsystem_eventSetAPIKey_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UClaudeAPISubsystem_SetAPIKey()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UClaudeAPISubsystem_SetAPIKey_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UClaudeAPISubsystem::execSetAPIKey)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_InAPIKey);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetAPIKey(Z_Param_InAPIKey);
	P_NATIVE_END;
}
// ********** End Class UClaudeAPISubsystem Function SetAPIKey *************************************

// ********** Begin Class UClaudeAPISubsystem ******************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UClaudeAPISubsystem;
UClass* UClaudeAPISubsystem::GetPrivateStaticClass()
{
	using TClass = UClaudeAPISubsystem;
	if (!Z_Registration_Info_UClass_UClaudeAPISubsystem.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("ClaudeAPISubsystem"),
			Z_Registration_Info_UClass_UClaudeAPISubsystem.InnerSingleton,
			StaticRegisterNativesUClaudeAPISubsystem,
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
	return Z_Registration_Info_UClass_UClaudeAPISubsystem.InnerSingleton;
}
UClass* Z_Construct_UClass_UClaudeAPISubsystem_NoRegister()
{
	return UClaudeAPISubsystem::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UClaudeAPISubsystem_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Singleton game instance subsystem that manages all communication with the Anthropic Claude API.\n *\n * Handles HTTP request construction, rate limiting with exponential backoff,\n * and parsing of structured JSON responses. All NPC dialogue routes through this subsystem.\n */" },
#endif
		{ "IncludePath", "Dialogue/ClaudeAPISubsystem.h" },
		{ "ModuleRelativePath", "Dialogue/ClaudeAPISubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Singleton game instance subsystem that manages all communication with the Anthropic Claude API.\n\nHandles HTTP request construction, rate limiting with exponential backoff,\nand parsing of structured JSON responses. All NPC dialogue routes through this subsystem." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnAnyResponseReceived_MetaData[] = {
		{ "Category", "NPC|Claude" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Broadcast delegate fired for every received response (useful for logging/analytics). */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ClaudeAPISubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Broadcast delegate fired for every received response (useful for logging/analytics)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinRequestInterval_MetaData[] = {
		{ "Category", "NPC|Claude" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Rate limiting: minimum interval between requests (seconds). */" },
#endif
		{ "ModuleRelativePath", "Dialogue/ClaudeAPISubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Rate limiting: minimum interval between requests (seconds)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UClaudeAPISubsystem constinit property declarations **********************
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnAnyResponseReceived;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MinRequestInterval;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UClaudeAPISubsystem constinit property declarations ************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("IsAPIKeyConfigured"), .Pointer = &UClaudeAPISubsystem::execIsAPIKeyConfigured },
		{ .NameUTF8 = UTF8TEXT("SendMessage"), .Pointer = &UClaudeAPISubsystem::execSendMessage },
		{ .NameUTF8 = UTF8TEXT("SetAPIKey"), .Pointer = &UClaudeAPISubsystem::execSetAPIKey },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UClaudeAPISubsystem_IsAPIKeyConfigured, "IsAPIKeyConfigured" }, // 3019050452
		{ &Z_Construct_UFunction_UClaudeAPISubsystem_SendMessage, "SendMessage" }, // 2154191350
		{ &Z_Construct_UFunction_UClaudeAPISubsystem_SetAPIKey, "SetAPIKey" }, // 1919283907
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UClaudeAPISubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UClaudeAPISubsystem_Statics

// ********** Begin Class UClaudeAPISubsystem Property Definitions *********************************
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UClaudeAPISubsystem_Statics::NewProp_OnAnyResponseReceived = { "OnAnyResponseReceived", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UClaudeAPISubsystem, OnAnyResponseReceived), Z_Construct_UDelegateFunction_LLM_NPC_OnClaudeResponseReceived__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnAnyResponseReceived_MetaData), NewProp_OnAnyResponseReceived_MetaData) }; // 4286312025
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UClaudeAPISubsystem_Statics::NewProp_MinRequestInterval = { "MinRequestInterval", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UClaudeAPISubsystem, MinRequestInterval), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinRequestInterval_MetaData), NewProp_MinRequestInterval_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UClaudeAPISubsystem_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UClaudeAPISubsystem_Statics::NewProp_OnAnyResponseReceived,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UClaudeAPISubsystem_Statics::NewProp_MinRequestInterval,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UClaudeAPISubsystem_Statics::PropPointers) < 2048);
// ********** End Class UClaudeAPISubsystem Property Definitions ***********************************
UObject* (*const Z_Construct_UClass_UClaudeAPISubsystem_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UGameInstanceSubsystem,
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UClaudeAPISubsystem_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UClaudeAPISubsystem_Statics::ClassParams = {
	&UClaudeAPISubsystem::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UClaudeAPISubsystem_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UClaudeAPISubsystem_Statics::PropPointers),
	0,
	0x009000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UClaudeAPISubsystem_Statics::Class_MetaDataParams), Z_Construct_UClass_UClaudeAPISubsystem_Statics::Class_MetaDataParams)
};
void UClaudeAPISubsystem::StaticRegisterNativesUClaudeAPISubsystem()
{
	UClass* Class = UClaudeAPISubsystem::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UClaudeAPISubsystem_Statics::Funcs));
}
UClass* Z_Construct_UClass_UClaudeAPISubsystem()
{
	if (!Z_Registration_Info_UClass_UClaudeAPISubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UClaudeAPISubsystem.OuterSingleton, Z_Construct_UClass_UClaudeAPISubsystem_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UClaudeAPISubsystem.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UClaudeAPISubsystem);
UClaudeAPISubsystem::~UClaudeAPISubsystem() {}
// ********** End Class UClaudeAPISubsystem ********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ClaudeAPISubsystem_h__Script_LLM_NPC_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FClaudeAPIResponse::StaticStruct, Z_Construct_UScriptStruct_FClaudeAPIResponse_Statics::NewStructOps, TEXT("ClaudeAPIResponse"),&Z_Registration_Info_UScriptStruct_FClaudeAPIResponse, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FClaudeAPIResponse), 2514891443U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UClaudeAPISubsystem, UClaudeAPISubsystem::StaticClass, TEXT("UClaudeAPISubsystem"), &Z_Registration_Info_UClass_UClaudeAPISubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UClaudeAPISubsystem), 949587756U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ClaudeAPISubsystem_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ClaudeAPISubsystem_h__Script_LLM_NPC_3902389653{
	TEXT("/Script/LLM_NPC"),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ClaudeAPISubsystem_h__Script_LLM_NPC_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ClaudeAPISubsystem_h__Script_LLM_NPC_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ClaudeAPISubsystem_h__Script_LLM_NPC_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_ClaudeAPISubsystem_h__Script_LLM_NPC_Statics::ScriptStructInfo),
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
