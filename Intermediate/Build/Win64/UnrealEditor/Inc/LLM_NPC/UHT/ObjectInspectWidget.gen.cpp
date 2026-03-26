// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Gesture/ObjectInspectWidget.h"
#include "LLM_NPC/Core/NPCTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeObjectInspectWidget() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector2D();
LLM_NPC_API UClass* Z_Construct_UClass_AInspectableItem_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UObjectInspectWidget();
LLM_NPC_API UClass* Z_Construct_UClass_UObjectInspectWidget_NoRegister();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FGestureInput();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UObjectInspectWidget Function ApplyGestureInput **************************
struct Z_Construct_UFunction_UObjectInspectWidget_ApplyGestureInput_Statics
{
	struct ObjectInspectWidget_eventApplyGestureInput_Parms
	{
		FGestureInput Input;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Gesture|Inspect" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Apply gesture-based input to the inspected item.\n\x09 * Pinch -> scale down, Spread -> scale up, Rotate -> rotate.\n\x09 * @param Input  The detected gesture input.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Gesture/ObjectInspectWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Apply gesture-based input to the inspected item.\nPinch -> scale down, Spread -> scale up, Rotate -> rotate.\n@param Input  The detected gesture input." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Input_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ApplyGestureInput constinit property declarations *********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Input;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ApplyGestureInput constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ApplyGestureInput Property Definitions ********************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UObjectInspectWidget_ApplyGestureInput_Statics::NewProp_Input = { "Input", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ObjectInspectWidget_eventApplyGestureInput_Parms, Input), Z_Construct_UScriptStruct_FGestureInput, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Input_MetaData), NewProp_Input_MetaData) }; // 3452162926
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UObjectInspectWidget_ApplyGestureInput_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UObjectInspectWidget_ApplyGestureInput_Statics::NewProp_Input,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UObjectInspectWidget_ApplyGestureInput_Statics::PropPointers) < 2048);
// ********** End Function ApplyGestureInput Property Definitions **********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UObjectInspectWidget_ApplyGestureInput_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UObjectInspectWidget, nullptr, "ApplyGestureInput", 	Z_Construct_UFunction_UObjectInspectWidget_ApplyGestureInput_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UObjectInspectWidget_ApplyGestureInput_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UObjectInspectWidget_ApplyGestureInput_Statics::ObjectInspectWidget_eventApplyGestureInput_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UObjectInspectWidget_ApplyGestureInput_Statics::Function_MetaDataParams), Z_Construct_UFunction_UObjectInspectWidget_ApplyGestureInput_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UObjectInspectWidget_ApplyGestureInput_Statics::ObjectInspectWidget_eventApplyGestureInput_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UObjectInspectWidget_ApplyGestureInput()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UObjectInspectWidget_ApplyGestureInput_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UObjectInspectWidget::execApplyGestureInput)
{
	P_GET_STRUCT_REF(FGestureInput,Z_Param_Out_Input);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ApplyGestureInput(Z_Param_Out_Input);
	P_NATIVE_END;
}
// ********** End Class UObjectInspectWidget Function ApplyGestureInput ****************************

// ********** Begin Class UObjectInspectWidget Function ApplyMouseInput ****************************
struct Z_Construct_UFunction_UObjectInspectWidget_ApplyMouseInput_Statics
{
	struct ObjectInspectWidget_eventApplyMouseInput_Parms
	{
		FVector2D MouseDelta;
		float ScrollDelta;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Gesture|Inspect" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Apply mouse/keyboard input to the inspected item.\n\x09 * Mouse drag rotates, scroll wheel scales.\n\x09 * @param MouseDelta  Mouse movement delta (X = yaw, Y = pitch).\n\x09 * @param ScrollDelta Scroll wheel delta (positive = scale up).\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Gesture/ObjectInspectWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Apply mouse/keyboard input to the inspected item.\nMouse drag rotates, scroll wheel scales.\n@param MouseDelta  Mouse movement delta (X = yaw, Y = pitch).\n@param ScrollDelta Scroll wheel delta (positive = scale up)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ApplyMouseInput constinit property declarations ***********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_MouseDelta;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ScrollDelta;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ApplyMouseInput constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ApplyMouseInput Property Definitions **********************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UObjectInspectWidget_ApplyMouseInput_Statics::NewProp_MouseDelta = { "MouseDelta", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ObjectInspectWidget_eventApplyMouseInput_Parms, MouseDelta), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UObjectInspectWidget_ApplyMouseInput_Statics::NewProp_ScrollDelta = { "ScrollDelta", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ObjectInspectWidget_eventApplyMouseInput_Parms, ScrollDelta), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UObjectInspectWidget_ApplyMouseInput_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UObjectInspectWidget_ApplyMouseInput_Statics::NewProp_MouseDelta,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UObjectInspectWidget_ApplyMouseInput_Statics::NewProp_ScrollDelta,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UObjectInspectWidget_ApplyMouseInput_Statics::PropPointers) < 2048);
// ********** End Function ApplyMouseInput Property Definitions ************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UObjectInspectWidget_ApplyMouseInput_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UObjectInspectWidget, nullptr, "ApplyMouseInput", 	Z_Construct_UFunction_UObjectInspectWidget_ApplyMouseInput_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UObjectInspectWidget_ApplyMouseInput_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UObjectInspectWidget_ApplyMouseInput_Statics::ObjectInspectWidget_eventApplyMouseInput_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UObjectInspectWidget_ApplyMouseInput_Statics::Function_MetaDataParams), Z_Construct_UFunction_UObjectInspectWidget_ApplyMouseInput_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UObjectInspectWidget_ApplyMouseInput_Statics::ObjectInspectWidget_eventApplyMouseInput_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UObjectInspectWidget_ApplyMouseInput()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UObjectInspectWidget_ApplyMouseInput_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UObjectInspectWidget::execApplyMouseInput)
{
	P_GET_STRUCT(FVector2D,Z_Param_MouseDelta);
	P_GET_PROPERTY(FFloatProperty,Z_Param_ScrollDelta);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ApplyMouseInput(Z_Param_MouseDelta,Z_Param_ScrollDelta);
	P_NATIVE_END;
}
// ********** End Class UObjectInspectWidget Function ApplyMouseInput ******************************

// ********** Begin Class UObjectInspectWidget Function GetInspectItem *****************************
struct Z_Construct_UFunction_UObjectInspectWidget_GetInspectItem_Statics
{
	struct ObjectInspectWidget_eventGetInspectItem_Parms
	{
		AInspectableItem* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Gesture|Inspect" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get the currently inspected item. */" },
#endif
		{ "ModuleRelativePath", "Gesture/ObjectInspectWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get the currently inspected item." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetInspectItem constinit property declarations ************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetInspectItem constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetInspectItem Property Definitions ***********************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UObjectInspectWidget_GetInspectItem_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ObjectInspectWidget_eventGetInspectItem_Parms, ReturnValue), Z_Construct_UClass_AInspectableItem_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UObjectInspectWidget_GetInspectItem_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UObjectInspectWidget_GetInspectItem_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UObjectInspectWidget_GetInspectItem_Statics::PropPointers) < 2048);
// ********** End Function GetInspectItem Property Definitions *************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UObjectInspectWidget_GetInspectItem_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UObjectInspectWidget, nullptr, "GetInspectItem", 	Z_Construct_UFunction_UObjectInspectWidget_GetInspectItem_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UObjectInspectWidget_GetInspectItem_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UObjectInspectWidget_GetInspectItem_Statics::ObjectInspectWidget_eventGetInspectItem_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UObjectInspectWidget_GetInspectItem_Statics::Function_MetaDataParams), Z_Construct_UFunction_UObjectInspectWidget_GetInspectItem_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UObjectInspectWidget_GetInspectItem_Statics::ObjectInspectWidget_eventGetInspectItem_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UObjectInspectWidget_GetInspectItem()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UObjectInspectWidget_GetInspectItem_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UObjectInspectWidget::execGetInspectItem)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(AInspectableItem**)Z_Param__Result=P_THIS->GetInspectItem();
	P_NATIVE_END;
}
// ********** End Class UObjectInspectWidget Function GetInspectItem *******************************

// ********** Begin Class UObjectInspectWidget Function HasInspectItem *****************************
struct Z_Construct_UFunction_UObjectInspectWidget_HasInspectItem_Statics
{
	struct ObjectInspectWidget_eventHasInspectItem_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Gesture|Inspect" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Whether an item is currently being inspected. */" },
#endif
		{ "ModuleRelativePath", "Gesture/ObjectInspectWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Whether an item is currently being inspected." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function HasInspectItem constinit property declarations ************************
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HasInspectItem constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HasInspectItem Property Definitions ***********************************
void Z_Construct_UFunction_UObjectInspectWidget_HasInspectItem_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((ObjectInspectWidget_eventHasInspectItem_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UObjectInspectWidget_HasInspectItem_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ObjectInspectWidget_eventHasInspectItem_Parms), &Z_Construct_UFunction_UObjectInspectWidget_HasInspectItem_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UObjectInspectWidget_HasInspectItem_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UObjectInspectWidget_HasInspectItem_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UObjectInspectWidget_HasInspectItem_Statics::PropPointers) < 2048);
// ********** End Function HasInspectItem Property Definitions *************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UObjectInspectWidget_HasInspectItem_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UObjectInspectWidget, nullptr, "HasInspectItem", 	Z_Construct_UFunction_UObjectInspectWidget_HasInspectItem_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UObjectInspectWidget_HasInspectItem_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UObjectInspectWidget_HasInspectItem_Statics::ObjectInspectWidget_eventHasInspectItem_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UObjectInspectWidget_HasInspectItem_Statics::Function_MetaDataParams), Z_Construct_UFunction_UObjectInspectWidget_HasInspectItem_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UObjectInspectWidget_HasInspectItem_Statics::ObjectInspectWidget_eventHasInspectItem_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UObjectInspectWidget_HasInspectItem()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UObjectInspectWidget_HasInspectItem_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UObjectInspectWidget::execHasInspectItem)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->HasInspectItem();
	P_NATIVE_END;
}
// ********** End Class UObjectInspectWidget Function HasInspectItem *******************************

// ********** Begin Class UObjectInspectWidget Function SetInspectItem *****************************
struct Z_Construct_UFunction_UObjectInspectWidget_SetInspectItem_Statics
{
	struct ObjectInspectWidget_eventSetInspectItem_Parms
	{
		AInspectableItem* Item;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Gesture|Inspect" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Set the item to inspect in the 3D viewport.\n\x09 * @param Item  The inspectable actor to display.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Gesture/ObjectInspectWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Set the item to inspect in the 3D viewport.\n@param Item  The inspectable actor to display." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetInspectItem constinit property declarations ************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Item;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetInspectItem constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetInspectItem Property Definitions ***********************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UObjectInspectWidget_SetInspectItem_Statics::NewProp_Item = { "Item", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ObjectInspectWidget_eventSetInspectItem_Parms, Item), Z_Construct_UClass_AInspectableItem_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UObjectInspectWidget_SetInspectItem_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UObjectInspectWidget_SetInspectItem_Statics::NewProp_Item,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UObjectInspectWidget_SetInspectItem_Statics::PropPointers) < 2048);
// ********** End Function SetInspectItem Property Definitions *************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UObjectInspectWidget_SetInspectItem_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UObjectInspectWidget, nullptr, "SetInspectItem", 	Z_Construct_UFunction_UObjectInspectWidget_SetInspectItem_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UObjectInspectWidget_SetInspectItem_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UObjectInspectWidget_SetInspectItem_Statics::ObjectInspectWidget_eventSetInspectItem_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UObjectInspectWidget_SetInspectItem_Statics::Function_MetaDataParams), Z_Construct_UFunction_UObjectInspectWidget_SetInspectItem_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UObjectInspectWidget_SetInspectItem_Statics::ObjectInspectWidget_eventSetInspectItem_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UObjectInspectWidget_SetInspectItem()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UObjectInspectWidget_SetInspectItem_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UObjectInspectWidget::execSetInspectItem)
{
	P_GET_OBJECT(AInspectableItem,Z_Param_Item);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetInspectItem(Z_Param_Item);
	P_NATIVE_END;
}
// ********** End Class UObjectInspectWidget Function SetInspectItem *******************************

// ********** Begin Class UObjectInspectWidget *****************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UObjectInspectWidget;
UClass* UObjectInspectWidget::GetPrivateStaticClass()
{
	using TClass = UObjectInspectWidget;
	if (!Z_Registration_Info_UClass_UObjectInspectWidget.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("ObjectInspectWidget"),
			Z_Registration_Info_UClass_UObjectInspectWidget.InnerSingleton,
			StaticRegisterNativesUObjectInspectWidget,
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
	return Z_Registration_Info_UClass_UObjectInspectWidget.InnerSingleton;
}
UClass* Z_Construct_UClass_UObjectInspectWidget_NoRegister()
{
	return UObjectInspectWidget::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UObjectInspectWidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Widget providing a 3D viewport for inspecting objects.\n * Features a 3D Bubble Cursor (semi-transparent selection sphere indicator).\n * Accepts gesture input (pinch/spread/rotate) or traditional keyboard/mouse input\n * for manipulating the inspected object.\n */" },
#endif
		{ "IncludePath", "Gesture/ObjectInspectWidget.h" },
		{ "ModuleRelativePath", "Gesture/ObjectInspectWidget.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Widget providing a 3D viewport for inspecting objects.\nFeatures a 3D Bubble Cursor (semi-transparent selection sphere indicator).\nAccepts gesture input (pinch/spread/rotate) or traditional keyboard/mouse input\nfor manipulating the inspected object." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BubbleCursorRadius_MetaData[] = {
		{ "Category", "NPC|Gesture|BubbleCursor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Radius of the 3D Bubble Cursor selection sphere. */" },
#endif
		{ "ModuleRelativePath", "Gesture/ObjectInspectWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Radius of the 3D Bubble Cursor selection sphere." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BubbleCursorColor_MetaData[] = {
		{ "Category", "NPC|Gesture|BubbleCursor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Color of the Bubble Cursor sphere indicator. */" },
#endif
		{ "ModuleRelativePath", "Gesture/ObjectInspectWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Color of the Bubble Cursor sphere indicator." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bShowBubbleCursor_MetaData[] = {
		{ "Category", "NPC|Gesture|BubbleCursor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Whether the Bubble Cursor is visible. */" },
#endif
		{ "ModuleRelativePath", "Gesture/ObjectInspectWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Whether the Bubble Cursor is visible." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GestureScaleSensitivity_MetaData[] = {
		{ "Category", "NPC|Gesture|Inspect" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Scale sensitivity for gesture-based scaling. */" },
#endif
		{ "ModuleRelativePath", "Gesture/ObjectInspectWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Scale sensitivity for gesture-based scaling." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GestureRotationSensitivity_MetaData[] = {
		{ "Category", "NPC|Gesture|Inspect" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Rotation sensitivity for gesture-based rotation (degrees per unit). */" },
#endif
		{ "ModuleRelativePath", "Gesture/ObjectInspectWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Rotation sensitivity for gesture-based rotation (degrees per unit)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ScrollScaleSensitivity_MetaData[] = {
		{ "Category", "NPC|Gesture|Inspect" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Scale sensitivity for scroll wheel. */" },
#endif
		{ "ModuleRelativePath", "Gesture/ObjectInspectWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Scale sensitivity for scroll wheel." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MouseRotationSensitivity_MetaData[] = {
		{ "Category", "NPC|Gesture|Inspect" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Rotation sensitivity for mouse drag (degrees per pixel). */" },
#endif
		{ "ModuleRelativePath", "Gesture/ObjectInspectWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Rotation sensitivity for mouse drag (degrees per pixel)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentItem_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The item currently being inspected. */" },
#endif
		{ "ModuleRelativePath", "Gesture/ObjectInspectWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The item currently being inspected." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UObjectInspectWidget constinit property declarations *********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BubbleCursorRadius;
	static const UECodeGen_Private::FStructPropertyParams NewProp_BubbleCursorColor;
	static void NewProp_bShowBubbleCursor_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShowBubbleCursor;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_GestureScaleSensitivity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_GestureRotationSensitivity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ScrollScaleSensitivity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MouseRotationSensitivity;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CurrentItem;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UObjectInspectWidget constinit property declarations ***********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("ApplyGestureInput"), .Pointer = &UObjectInspectWidget::execApplyGestureInput },
		{ .NameUTF8 = UTF8TEXT("ApplyMouseInput"), .Pointer = &UObjectInspectWidget::execApplyMouseInput },
		{ .NameUTF8 = UTF8TEXT("GetInspectItem"), .Pointer = &UObjectInspectWidget::execGetInspectItem },
		{ .NameUTF8 = UTF8TEXT("HasInspectItem"), .Pointer = &UObjectInspectWidget::execHasInspectItem },
		{ .NameUTF8 = UTF8TEXT("SetInspectItem"), .Pointer = &UObjectInspectWidget::execSetInspectItem },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UObjectInspectWidget_ApplyGestureInput, "ApplyGestureInput" }, // 3333459037
		{ &Z_Construct_UFunction_UObjectInspectWidget_ApplyMouseInput, "ApplyMouseInput" }, // 4042881721
		{ &Z_Construct_UFunction_UObjectInspectWidget_GetInspectItem, "GetInspectItem" }, // 1111536128
		{ &Z_Construct_UFunction_UObjectInspectWidget_HasInspectItem, "HasInspectItem" }, // 3823441453
		{ &Z_Construct_UFunction_UObjectInspectWidget_SetInspectItem, "SetInspectItem" }, // 2609306245
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UObjectInspectWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UObjectInspectWidget_Statics

// ********** Begin Class UObjectInspectWidget Property Definitions ********************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UObjectInspectWidget_Statics::NewProp_BubbleCursorRadius = { "BubbleCursorRadius", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UObjectInspectWidget, BubbleCursorRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BubbleCursorRadius_MetaData), NewProp_BubbleCursorRadius_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UObjectInspectWidget_Statics::NewProp_BubbleCursorColor = { "BubbleCursorColor", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UObjectInspectWidget, BubbleCursorColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BubbleCursorColor_MetaData), NewProp_BubbleCursorColor_MetaData) };
void Z_Construct_UClass_UObjectInspectWidget_Statics::NewProp_bShowBubbleCursor_SetBit(void* Obj)
{
	((UObjectInspectWidget*)Obj)->bShowBubbleCursor = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UObjectInspectWidget_Statics::NewProp_bShowBubbleCursor = { "bShowBubbleCursor", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UObjectInspectWidget), &Z_Construct_UClass_UObjectInspectWidget_Statics::NewProp_bShowBubbleCursor_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bShowBubbleCursor_MetaData), NewProp_bShowBubbleCursor_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UObjectInspectWidget_Statics::NewProp_GestureScaleSensitivity = { "GestureScaleSensitivity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UObjectInspectWidget, GestureScaleSensitivity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GestureScaleSensitivity_MetaData), NewProp_GestureScaleSensitivity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UObjectInspectWidget_Statics::NewProp_GestureRotationSensitivity = { "GestureRotationSensitivity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UObjectInspectWidget, GestureRotationSensitivity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GestureRotationSensitivity_MetaData), NewProp_GestureRotationSensitivity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UObjectInspectWidget_Statics::NewProp_ScrollScaleSensitivity = { "ScrollScaleSensitivity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UObjectInspectWidget, ScrollScaleSensitivity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ScrollScaleSensitivity_MetaData), NewProp_ScrollScaleSensitivity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UObjectInspectWidget_Statics::NewProp_MouseRotationSensitivity = { "MouseRotationSensitivity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UObjectInspectWidget, MouseRotationSensitivity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MouseRotationSensitivity_MetaData), NewProp_MouseRotationSensitivity_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UObjectInspectWidget_Statics::NewProp_CurrentItem = { "CurrentItem", nullptr, (EPropertyFlags)0x0144000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UObjectInspectWidget, CurrentItem), Z_Construct_UClass_AInspectableItem_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentItem_MetaData), NewProp_CurrentItem_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UObjectInspectWidget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UObjectInspectWidget_Statics::NewProp_BubbleCursorRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UObjectInspectWidget_Statics::NewProp_BubbleCursorColor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UObjectInspectWidget_Statics::NewProp_bShowBubbleCursor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UObjectInspectWidget_Statics::NewProp_GestureScaleSensitivity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UObjectInspectWidget_Statics::NewProp_GestureRotationSensitivity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UObjectInspectWidget_Statics::NewProp_ScrollScaleSensitivity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UObjectInspectWidget_Statics::NewProp_MouseRotationSensitivity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UObjectInspectWidget_Statics::NewProp_CurrentItem,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UObjectInspectWidget_Statics::PropPointers) < 2048);
// ********** End Class UObjectInspectWidget Property Definitions **********************************
UObject* (*const Z_Construct_UClass_UObjectInspectWidget_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UObjectInspectWidget_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UObjectInspectWidget_Statics::ClassParams = {
	&UObjectInspectWidget::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UObjectInspectWidget_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UObjectInspectWidget_Statics::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UObjectInspectWidget_Statics::Class_MetaDataParams), Z_Construct_UClass_UObjectInspectWidget_Statics::Class_MetaDataParams)
};
void UObjectInspectWidget::StaticRegisterNativesUObjectInspectWidget()
{
	UClass* Class = UObjectInspectWidget::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UObjectInspectWidget_Statics::Funcs));
}
UClass* Z_Construct_UClass_UObjectInspectWidget()
{
	if (!Z_Registration_Info_UClass_UObjectInspectWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UObjectInspectWidget.OuterSingleton, Z_Construct_UClass_UObjectInspectWidget_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UObjectInspectWidget.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UObjectInspectWidget);
UObjectInspectWidget::~UObjectInspectWidget() {}
// ********** End Class UObjectInspectWidget *******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_ObjectInspectWidget_h__Script_LLM_NPC_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UObjectInspectWidget, UObjectInspectWidget::StaticClass, TEXT("UObjectInspectWidget"), &Z_Registration_Info_UClass_UObjectInspectWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UObjectInspectWidget), 3177243739U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_ObjectInspectWidget_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_ObjectInspectWidget_h__Script_LLM_NPC_1682648794{
	TEXT("/Script/LLM_NPC"),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_ObjectInspectWidget_h__Script_LLM_NPC_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_ObjectInspectWidget_h__Script_LLM_NPC_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
