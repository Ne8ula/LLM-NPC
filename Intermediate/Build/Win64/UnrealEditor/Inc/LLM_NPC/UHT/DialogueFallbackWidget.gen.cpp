// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Dialogue/DialogueFallbackWidget.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeDialogueFallbackWidget() {}

// ********** Begin Cross Module References ********************************************************
LLM_NPC_API UClass* Z_Construct_UClass_UDialogueFallbackWidget();
LLM_NPC_API UClass* Z_Construct_UClass_UDialogueFallbackWidget_NoRegister();
LLM_NPC_API UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnTextSubmitted__DelegateSignature();
SLATECORE_API UEnum* Z_Construct_UEnum_SlateCore_ETextCommit();
UMG_API UClass* Z_Construct_UClass_UButton_NoRegister();
UMG_API UClass* Z_Construct_UClass_UEditableTextBox_NoRegister();
UMG_API UClass* Z_Construct_UClass_UTextBlock_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FOnTextSubmitted ******************************************************
struct Z_Construct_UDelegateFunction_LLM_NPC_OnTextSubmitted__DelegateSignature_Statics
{
	struct _Script_LLM_NPC_eventOnTextSubmitted_Parms
	{
		FString SubmittedText;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Delegate fired when the user submits text through the fallback widget. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/DialogueFallbackWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Delegate fired when the user submits text through the fallback widget." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SubmittedText_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnTextSubmitted constinit property declarations **********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_SubmittedText;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FOnTextSubmitted constinit property declarations ************************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FOnTextSubmitted Property Definitions *********************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UDelegateFunction_LLM_NPC_OnTextSubmitted__DelegateSignature_Statics::NewProp_SubmittedText = { "SubmittedText", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_LLM_NPC_eventOnTextSubmitted_Parms, SubmittedText), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SubmittedText_MetaData), NewProp_SubmittedText_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_LLM_NPC_OnTextSubmitted__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LLM_NPC_OnTextSubmitted__DelegateSignature_Statics::NewProp_SubmittedText,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnTextSubmitted__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FOnTextSubmitted Property Definitions ***********************************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_LLM_NPC_OnTextSubmitted__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_LLM_NPC, nullptr, "OnTextSubmitted__DelegateSignature", 	Z_Construct_UDelegateFunction_LLM_NPC_OnTextSubmitted__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnTextSubmitted__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_LLM_NPC_OnTextSubmitted__DelegateSignature_Statics::_Script_LLM_NPC_eventOnTextSubmitted_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnTextSubmitted__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_LLM_NPC_OnTextSubmitted__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_LLM_NPC_OnTextSubmitted__DelegateSignature_Statics::_Script_LLM_NPC_eventOnTextSubmitted_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnTextSubmitted__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_LLM_NPC_OnTextSubmitted__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnTextSubmitted_DelegateWrapper(const FMulticastScriptDelegate& OnTextSubmitted, const FString& SubmittedText)
{
	struct _Script_LLM_NPC_eventOnTextSubmitted_Parms
	{
		FString SubmittedText;
	};
	_Script_LLM_NPC_eventOnTextSubmitted_Parms Parms;
	Parms.SubmittedText=SubmittedText;
	OnTextSubmitted.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnTextSubmitted ********************************************************

// ********** Begin Class UDialogueFallbackWidget Function ClearInput ******************************
struct Z_Construct_UFunction_UDialogueFallbackWidget_ClearInput_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Dialogue|Fallback" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Clear the text input field. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/DialogueFallbackWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Clear the text input field." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ClearInput constinit property declarations ****************************
// ********** End Function ClearInput constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UDialogueFallbackWidget_ClearInput_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UDialogueFallbackWidget, nullptr, "ClearInput", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueFallbackWidget_ClearInput_Statics::Function_MetaDataParams), Z_Construct_UFunction_UDialogueFallbackWidget_ClearInput_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UDialogueFallbackWidget_ClearInput()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UDialogueFallbackWidget_ClearInput_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UDialogueFallbackWidget::execClearInput)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClearInput();
	P_NATIVE_END;
}
// ********** End Class UDialogueFallbackWidget Function ClearInput ********************************

// ********** Begin Class UDialogueFallbackWidget Function FocusInput ******************************
struct Z_Construct_UFunction_UDialogueFallbackWidget_FocusInput_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Dialogue|Fallback" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Set focus to the text input field. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/DialogueFallbackWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Set focus to the text input field." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function FocusInput constinit property declarations ****************************
// ********** End Function FocusInput constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UDialogueFallbackWidget_FocusInput_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UDialogueFallbackWidget, nullptr, "FocusInput", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueFallbackWidget_FocusInput_Statics::Function_MetaDataParams), Z_Construct_UFunction_UDialogueFallbackWidget_FocusInput_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UDialogueFallbackWidget_FocusInput()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UDialogueFallbackWidget_FocusInput_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UDialogueFallbackWidget::execFocusInput)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->FocusInput();
	P_NATIVE_END;
}
// ********** End Class UDialogueFallbackWidget Function FocusInput ********************************

// ********** Begin Class UDialogueFallbackWidget Function HideWidget ******************************
struct Z_Construct_UFunction_UDialogueFallbackWidget_HideWidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Dialogue|Fallback" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Hide the widget with optional animation. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/DialogueFallbackWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Hide the widget with optional animation." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function HideWidget constinit property declarations ****************************
// ********** End Function HideWidget constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UDialogueFallbackWidget_HideWidget_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UDialogueFallbackWidget, nullptr, "HideWidget", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueFallbackWidget_HideWidget_Statics::Function_MetaDataParams), Z_Construct_UFunction_UDialogueFallbackWidget_HideWidget_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UDialogueFallbackWidget_HideWidget()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UDialogueFallbackWidget_HideWidget_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UDialogueFallbackWidget::execHideWidget)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HideWidget();
	P_NATIVE_END;
}
// ********** End Class UDialogueFallbackWidget Function HideWidget ********************************

// ********** Begin Class UDialogueFallbackWidget Function OnSendButtonClicked *********************
struct Z_Construct_UFunction_UDialogueFallbackWidget_OnSendButtonClicked_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Called when the send button is clicked. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/DialogueFallbackWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Called when the send button is clicked." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function OnSendButtonClicked constinit property declarations *******************
// ********** End Function OnSendButtonClicked constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UDialogueFallbackWidget_OnSendButtonClicked_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UDialogueFallbackWidget, nullptr, "OnSendButtonClicked", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueFallbackWidget_OnSendButtonClicked_Statics::Function_MetaDataParams), Z_Construct_UFunction_UDialogueFallbackWidget_OnSendButtonClicked_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UDialogueFallbackWidget_OnSendButtonClicked()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UDialogueFallbackWidget_OnSendButtonClicked_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UDialogueFallbackWidget::execOnSendButtonClicked)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnSendButtonClicked();
	P_NATIVE_END;
}
// ********** End Class UDialogueFallbackWidget Function OnSendButtonClicked ***********************

// ********** Begin Class UDialogueFallbackWidget Function OnTextCommitted *************************
struct Z_Construct_UFunction_UDialogueFallbackWidget_OnTextCommitted_Statics
{
	struct DialogueFallbackWidget_eventOnTextCommitted_Parms
	{
		FText Text;
		TEnumAsByte<ETextCommit::Type> CommitMethod;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Called when the user presses Enter in the text box. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/DialogueFallbackWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Called when the user presses Enter in the text box." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Text_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnTextCommitted constinit property declarations ***********************
	static const UECodeGen_Private::FTextPropertyParams NewProp_Text;
	static const UECodeGen_Private::FBytePropertyParams NewProp_CommitMethod;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function OnTextCommitted constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function OnTextCommitted Property Definitions **********************************
const UECodeGen_Private::FTextPropertyParams Z_Construct_UFunction_UDialogueFallbackWidget_OnTextCommitted_Statics::NewProp_Text = { "Text", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(DialogueFallbackWidget_eventOnTextCommitted_Parms, Text), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Text_MetaData), NewProp_Text_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UDialogueFallbackWidget_OnTextCommitted_Statics::NewProp_CommitMethod = { "CommitMethod", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(DialogueFallbackWidget_eventOnTextCommitted_Parms, CommitMethod), Z_Construct_UEnum_SlateCore_ETextCommit, METADATA_PARAMS(0, nullptr) }; // 1235926667
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UDialogueFallbackWidget_OnTextCommitted_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDialogueFallbackWidget_OnTextCommitted_Statics::NewProp_Text,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDialogueFallbackWidget_OnTextCommitted_Statics::NewProp_CommitMethod,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueFallbackWidget_OnTextCommitted_Statics::PropPointers) < 2048);
// ********** End Function OnTextCommitted Property Definitions ************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UDialogueFallbackWidget_OnTextCommitted_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UDialogueFallbackWidget, nullptr, "OnTextCommitted", 	Z_Construct_UFunction_UDialogueFallbackWidget_OnTextCommitted_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueFallbackWidget_OnTextCommitted_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UDialogueFallbackWidget_OnTextCommitted_Statics::DialogueFallbackWidget_eventOnTextCommitted_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00440401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueFallbackWidget_OnTextCommitted_Statics::Function_MetaDataParams), Z_Construct_UFunction_UDialogueFallbackWidget_OnTextCommitted_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UDialogueFallbackWidget_OnTextCommitted_Statics::DialogueFallbackWidget_eventOnTextCommitted_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDialogueFallbackWidget_OnTextCommitted()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UDialogueFallbackWidget_OnTextCommitted_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UDialogueFallbackWidget::execOnTextCommitted)
{
	P_GET_PROPERTY_REF(FTextProperty,Z_Param_Out_Text);
	P_GET_PROPERTY(FByteProperty,Z_Param_CommitMethod);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnTextCommitted(Z_Param_Out_Text,ETextCommit::Type(Z_Param_CommitMethod));
	P_NATIVE_END;
}
// ********** End Class UDialogueFallbackWidget Function OnTextCommitted ***************************

// ********** Begin Class UDialogueFallbackWidget Function SetInputEnabled *************************
struct Z_Construct_UFunction_UDialogueFallbackWidget_SetInputEnabled_Statics
{
	struct DialogueFallbackWidget_eventSetInputEnabled_Parms
	{
		bool bEnabled;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Dialogue|Fallback" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Enable or disable the input controls. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/DialogueFallbackWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Enable or disable the input controls." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetInputEnabled constinit property declarations ***********************
	static void NewProp_bEnabled_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnabled;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetInputEnabled constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetInputEnabled Property Definitions **********************************
void Z_Construct_UFunction_UDialogueFallbackWidget_SetInputEnabled_Statics::NewProp_bEnabled_SetBit(void* Obj)
{
	((DialogueFallbackWidget_eventSetInputEnabled_Parms*)Obj)->bEnabled = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UDialogueFallbackWidget_SetInputEnabled_Statics::NewProp_bEnabled = { "bEnabled", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(DialogueFallbackWidget_eventSetInputEnabled_Parms), &Z_Construct_UFunction_UDialogueFallbackWidget_SetInputEnabled_Statics::NewProp_bEnabled_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UDialogueFallbackWidget_SetInputEnabled_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDialogueFallbackWidget_SetInputEnabled_Statics::NewProp_bEnabled,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueFallbackWidget_SetInputEnabled_Statics::PropPointers) < 2048);
// ********** End Function SetInputEnabled Property Definitions ************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UDialogueFallbackWidget_SetInputEnabled_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UDialogueFallbackWidget, nullptr, "SetInputEnabled", 	Z_Construct_UFunction_UDialogueFallbackWidget_SetInputEnabled_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueFallbackWidget_SetInputEnabled_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UDialogueFallbackWidget_SetInputEnabled_Statics::DialogueFallbackWidget_eventSetInputEnabled_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueFallbackWidget_SetInputEnabled_Statics::Function_MetaDataParams), Z_Construct_UFunction_UDialogueFallbackWidget_SetInputEnabled_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UDialogueFallbackWidget_SetInputEnabled_Statics::DialogueFallbackWidget_eventSetInputEnabled_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDialogueFallbackWidget_SetInputEnabled()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UDialogueFallbackWidget_SetInputEnabled_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UDialogueFallbackWidget::execSetInputEnabled)
{
	P_GET_UBOOL(Z_Param_bEnabled);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetInputEnabled(Z_Param_bEnabled);
	P_NATIVE_END;
}
// ********** End Class UDialogueFallbackWidget Function SetInputEnabled ***************************

// ********** Begin Class UDialogueFallbackWidget Function SetStatusText ***************************
struct Z_Construct_UFunction_UDialogueFallbackWidget_SetStatusText_Statics
{
	struct DialogueFallbackWidget_eventSetStatusText_Parms
	{
		FString StatusText;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Dialogue|Fallback" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Show a status message (e.g., \"Waiting for response...\"). */" },
#endif
		{ "ModuleRelativePath", "Dialogue/DialogueFallbackWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Show a status message (e.g., \"Waiting for response...\")." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StatusText_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetStatusText constinit property declarations *************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_StatusText;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetStatusText constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetStatusText Property Definitions ************************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UDialogueFallbackWidget_SetStatusText_Statics::NewProp_StatusText = { "StatusText", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(DialogueFallbackWidget_eventSetStatusText_Parms, StatusText), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StatusText_MetaData), NewProp_StatusText_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UDialogueFallbackWidget_SetStatusText_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDialogueFallbackWidget_SetStatusText_Statics::NewProp_StatusText,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueFallbackWidget_SetStatusText_Statics::PropPointers) < 2048);
// ********** End Function SetStatusText Property Definitions **************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UDialogueFallbackWidget_SetStatusText_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UDialogueFallbackWidget, nullptr, "SetStatusText", 	Z_Construct_UFunction_UDialogueFallbackWidget_SetStatusText_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueFallbackWidget_SetStatusText_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UDialogueFallbackWidget_SetStatusText_Statics::DialogueFallbackWidget_eventSetStatusText_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueFallbackWidget_SetStatusText_Statics::Function_MetaDataParams), Z_Construct_UFunction_UDialogueFallbackWidget_SetStatusText_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UDialogueFallbackWidget_SetStatusText_Statics::DialogueFallbackWidget_eventSetStatusText_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDialogueFallbackWidget_SetStatusText()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UDialogueFallbackWidget_SetStatusText_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UDialogueFallbackWidget::execSetStatusText)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_StatusText);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetStatusText(Z_Param_StatusText);
	P_NATIVE_END;
}
// ********** End Class UDialogueFallbackWidget Function SetStatusText *****************************

// ********** Begin Class UDialogueFallbackWidget Function SetVisibleBasedOnVoiceAvailability ******
struct Z_Construct_UFunction_UDialogueFallbackWidget_SetVisibleBasedOnVoiceAvailability_Statics
{
	struct DialogueFallbackWidget_eventSetVisibleBasedOnVoiceAvailability_Parms
	{
		bool bVoiceAvailable;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Dialogue|Fallback" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Set whether the widget should be visible based on voice availability. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/DialogueFallbackWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Set whether the widget should be visible based on voice availability." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetVisibleBasedOnVoiceAvailability constinit property declarations ****
	static void NewProp_bVoiceAvailable_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bVoiceAvailable;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetVisibleBasedOnVoiceAvailability constinit property declarations ******
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetVisibleBasedOnVoiceAvailability Property Definitions ***************
void Z_Construct_UFunction_UDialogueFallbackWidget_SetVisibleBasedOnVoiceAvailability_Statics::NewProp_bVoiceAvailable_SetBit(void* Obj)
{
	((DialogueFallbackWidget_eventSetVisibleBasedOnVoiceAvailability_Parms*)Obj)->bVoiceAvailable = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UDialogueFallbackWidget_SetVisibleBasedOnVoiceAvailability_Statics::NewProp_bVoiceAvailable = { "bVoiceAvailable", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(DialogueFallbackWidget_eventSetVisibleBasedOnVoiceAvailability_Parms), &Z_Construct_UFunction_UDialogueFallbackWidget_SetVisibleBasedOnVoiceAvailability_Statics::NewProp_bVoiceAvailable_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UDialogueFallbackWidget_SetVisibleBasedOnVoiceAvailability_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDialogueFallbackWidget_SetVisibleBasedOnVoiceAvailability_Statics::NewProp_bVoiceAvailable,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueFallbackWidget_SetVisibleBasedOnVoiceAvailability_Statics::PropPointers) < 2048);
// ********** End Function SetVisibleBasedOnVoiceAvailability Property Definitions *****************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UDialogueFallbackWidget_SetVisibleBasedOnVoiceAvailability_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UDialogueFallbackWidget, nullptr, "SetVisibleBasedOnVoiceAvailability", 	Z_Construct_UFunction_UDialogueFallbackWidget_SetVisibleBasedOnVoiceAvailability_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueFallbackWidget_SetVisibleBasedOnVoiceAvailability_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UDialogueFallbackWidget_SetVisibleBasedOnVoiceAvailability_Statics::DialogueFallbackWidget_eventSetVisibleBasedOnVoiceAvailability_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueFallbackWidget_SetVisibleBasedOnVoiceAvailability_Statics::Function_MetaDataParams), Z_Construct_UFunction_UDialogueFallbackWidget_SetVisibleBasedOnVoiceAvailability_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UDialogueFallbackWidget_SetVisibleBasedOnVoiceAvailability_Statics::DialogueFallbackWidget_eventSetVisibleBasedOnVoiceAvailability_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDialogueFallbackWidget_SetVisibleBasedOnVoiceAvailability()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UDialogueFallbackWidget_SetVisibleBasedOnVoiceAvailability_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UDialogueFallbackWidget::execSetVisibleBasedOnVoiceAvailability)
{
	P_GET_UBOOL(Z_Param_bVoiceAvailable);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetVisibleBasedOnVoiceAvailability(Z_Param_bVoiceAvailable);
	P_NATIVE_END;
}
// ********** End Class UDialogueFallbackWidget Function SetVisibleBasedOnVoiceAvailability ********

// ********** Begin Class UDialogueFallbackWidget Function ShowWidget ******************************
struct Z_Construct_UFunction_UDialogueFallbackWidget_ShowWidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Dialogue|Fallback" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Show the widget with optional animation. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/DialogueFallbackWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Show the widget with optional animation." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ShowWidget constinit property declarations ****************************
// ********** End Function ShowWidget constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UDialogueFallbackWidget_ShowWidget_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UDialogueFallbackWidget, nullptr, "ShowWidget", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UDialogueFallbackWidget_ShowWidget_Statics::Function_MetaDataParams), Z_Construct_UFunction_UDialogueFallbackWidget_ShowWidget_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UDialogueFallbackWidget_ShowWidget()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UDialogueFallbackWidget_ShowWidget_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UDialogueFallbackWidget::execShowWidget)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ShowWidget();
	P_NATIVE_END;
}
// ********** End Class UDialogueFallbackWidget Function ShowWidget ********************************

// ********** Begin Class UDialogueFallbackWidget **************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UDialogueFallbackWidget;
UClass* UDialogueFallbackWidget::GetPrivateStaticClass()
{
	using TClass = UDialogueFallbackWidget;
	if (!Z_Registration_Info_UClass_UDialogueFallbackWidget.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("DialogueFallbackWidget"),
			Z_Registration_Info_UClass_UDialogueFallbackWidget.InnerSingleton,
			StaticRegisterNativesUDialogueFallbackWidget,
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
	return Z_Registration_Info_UClass_UDialogueFallbackWidget.InnerSingleton;
}
UClass* Z_Construct_UClass_UDialogueFallbackWidget_NoRegister()
{
	return UDialogueFallbackWidget::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UDialogueFallbackWidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Simple text-input fallback widget for dialogue when voice input is unavailable.\n *\n * Contains an editable text box and a send button. Automatically shows/hides\n * based on whether voice input (WhisperSTTComponent) is available on the\n * interacting NPC.\n */" },
#endif
		{ "IncludePath", "Dialogue/DialogueFallbackWidget.h" },
		{ "ModuleRelativePath", "Dialogue/DialogueFallbackWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple text-input fallback widget for dialogue when voice input is unavailable.\n\nContains an editable text box and a send button. Automatically shows/hides\nbased on whether voice input (WhisperSTTComponent) is available on the\ninteracting NPC." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnTextSubmitted_MetaData[] = {
		{ "Category", "NPC|Dialogue|Fallback" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Fired when the user submits text input. */" },
#endif
		{ "ModuleRelativePath", "Dialogue/DialogueFallbackWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Fired when the user submits text input." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TextInputBox_MetaData[] = {
		{ "BindWidget", "" },
		{ "Category", "DialogueFallbackWidget" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The text input box. Bind in Blueprint or set via BindWidget. */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Dialogue/DialogueFallbackWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The text input box. Bind in Blueprint or set via BindWidget." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SendButton_MetaData[] = {
		{ "BindWidget", "" },
		{ "Category", "DialogueFallbackWidget" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The send button. Bind in Blueprint or set via BindWidget. */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Dialogue/DialogueFallbackWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The send button. Bind in Blueprint or set via BindWidget." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StatusTextBlock_MetaData[] = {
		{ "BindWidgetOptional", "" },
		{ "Category", "DialogueFallbackWidget" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Optional status text display. */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Dialogue/DialogueFallbackWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Optional status text display." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UDialogueFallbackWidget constinit property declarations ******************
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnTextSubmitted;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TextInputBox;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SendButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StatusTextBlock;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDialogueFallbackWidget constinit property declarations ********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("ClearInput"), .Pointer = &UDialogueFallbackWidget::execClearInput },
		{ .NameUTF8 = UTF8TEXT("FocusInput"), .Pointer = &UDialogueFallbackWidget::execFocusInput },
		{ .NameUTF8 = UTF8TEXT("HideWidget"), .Pointer = &UDialogueFallbackWidget::execHideWidget },
		{ .NameUTF8 = UTF8TEXT("OnSendButtonClicked"), .Pointer = &UDialogueFallbackWidget::execOnSendButtonClicked },
		{ .NameUTF8 = UTF8TEXT("OnTextCommitted"), .Pointer = &UDialogueFallbackWidget::execOnTextCommitted },
		{ .NameUTF8 = UTF8TEXT("SetInputEnabled"), .Pointer = &UDialogueFallbackWidget::execSetInputEnabled },
		{ .NameUTF8 = UTF8TEXT("SetStatusText"), .Pointer = &UDialogueFallbackWidget::execSetStatusText },
		{ .NameUTF8 = UTF8TEXT("SetVisibleBasedOnVoiceAvailability"), .Pointer = &UDialogueFallbackWidget::execSetVisibleBasedOnVoiceAvailability },
		{ .NameUTF8 = UTF8TEXT("ShowWidget"), .Pointer = &UDialogueFallbackWidget::execShowWidget },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDialogueFallbackWidget_ClearInput, "ClearInput" }, // 2534614205
		{ &Z_Construct_UFunction_UDialogueFallbackWidget_FocusInput, "FocusInput" }, // 3522533488
		{ &Z_Construct_UFunction_UDialogueFallbackWidget_HideWidget, "HideWidget" }, // 3294115651
		{ &Z_Construct_UFunction_UDialogueFallbackWidget_OnSendButtonClicked, "OnSendButtonClicked" }, // 3065599098
		{ &Z_Construct_UFunction_UDialogueFallbackWidget_OnTextCommitted, "OnTextCommitted" }, // 2138485031
		{ &Z_Construct_UFunction_UDialogueFallbackWidget_SetInputEnabled, "SetInputEnabled" }, // 731563091
		{ &Z_Construct_UFunction_UDialogueFallbackWidget_SetStatusText, "SetStatusText" }, // 2671364315
		{ &Z_Construct_UFunction_UDialogueFallbackWidget_SetVisibleBasedOnVoiceAvailability, "SetVisibleBasedOnVoiceAvailability" }, // 2177932686
		{ &Z_Construct_UFunction_UDialogueFallbackWidget_ShowWidget, "ShowWidget" }, // 2953708610
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDialogueFallbackWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UDialogueFallbackWidget_Statics

// ********** Begin Class UDialogueFallbackWidget Property Definitions *****************************
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UDialogueFallbackWidget_Statics::NewProp_OnTextSubmitted = { "OnTextSubmitted", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDialogueFallbackWidget, OnTextSubmitted), Z_Construct_UDelegateFunction_LLM_NPC_OnTextSubmitted__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnTextSubmitted_MetaData), NewProp_OnTextSubmitted_MetaData) }; // 745917309
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UDialogueFallbackWidget_Statics::NewProp_TextInputBox = { "TextInputBox", nullptr, (EPropertyFlags)0x012408000008001c, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDialogueFallbackWidget, TextInputBox), Z_Construct_UClass_UEditableTextBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TextInputBox_MetaData), NewProp_TextInputBox_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UDialogueFallbackWidget_Statics::NewProp_SendButton = { "SendButton", nullptr, (EPropertyFlags)0x012408000008001c, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDialogueFallbackWidget, SendButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SendButton_MetaData), NewProp_SendButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UDialogueFallbackWidget_Statics::NewProp_StatusTextBlock = { "StatusTextBlock", nullptr, (EPropertyFlags)0x012408000008001c, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDialogueFallbackWidget, StatusTextBlock), Z_Construct_UClass_UTextBlock_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StatusTextBlock_MetaData), NewProp_StatusTextBlock_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UDialogueFallbackWidget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDialogueFallbackWidget_Statics::NewProp_OnTextSubmitted,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDialogueFallbackWidget_Statics::NewProp_TextInputBox,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDialogueFallbackWidget_Statics::NewProp_SendButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDialogueFallbackWidget_Statics::NewProp_StatusTextBlock,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UDialogueFallbackWidget_Statics::PropPointers) < 2048);
// ********** End Class UDialogueFallbackWidget Property Definitions *******************************
UObject* (*const Z_Construct_UClass_UDialogueFallbackWidget_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UDialogueFallbackWidget_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UDialogueFallbackWidget_Statics::ClassParams = {
	&UDialogueFallbackWidget::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UDialogueFallbackWidget_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UDialogueFallbackWidget_Statics::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UDialogueFallbackWidget_Statics::Class_MetaDataParams), Z_Construct_UClass_UDialogueFallbackWidget_Statics::Class_MetaDataParams)
};
void UDialogueFallbackWidget::StaticRegisterNativesUDialogueFallbackWidget()
{
	UClass* Class = UDialogueFallbackWidget::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UDialogueFallbackWidget_Statics::Funcs));
}
UClass* Z_Construct_UClass_UDialogueFallbackWidget()
{
	if (!Z_Registration_Info_UClass_UDialogueFallbackWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDialogueFallbackWidget.OuterSingleton, Z_Construct_UClass_UDialogueFallbackWidget_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UDialogueFallbackWidget.OuterSingleton;
}
UDialogueFallbackWidget::UDialogueFallbackWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDialogueFallbackWidget);
UDialogueFallbackWidget::~UDialogueFallbackWidget() {}
// ********** End Class UDialogueFallbackWidget ****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueFallbackWidget_h__Script_LLM_NPC_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDialogueFallbackWidget, UDialogueFallbackWidget::StaticClass, TEXT("UDialogueFallbackWidget"), &Z_Registration_Info_UClass_UDialogueFallbackWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDialogueFallbackWidget), 782787036U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueFallbackWidget_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueFallbackWidget_h__Script_LLM_NPC_1237077798{
	TEXT("/Script/LLM_NPC"),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueFallbackWidget_h__Script_LLM_NPC_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Dialogue_DialogueFallbackWidget_h__Script_LLM_NPC_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
