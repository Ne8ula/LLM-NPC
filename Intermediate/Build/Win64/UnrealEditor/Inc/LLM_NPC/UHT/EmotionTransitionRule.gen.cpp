// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Emotion/EmotionTransitionRule.h"
#include "LLM_NPC/Core/NPCTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeEmotionTransitionRule() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
LLM_NPC_API UClass* Z_Construct_UClass_UEmotionTransitionRule();
LLM_NPC_API UClass* Z_Construct_UClass_UEmotionTransitionRule_NoRegister();
LLM_NPC_API UEnum* Z_Construct_UEnum_LLM_NPC_EEmotionType();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FEmotionSignal();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UEmotionTransitionRule Function EvaluateRule *****************************
struct Z_Construct_UFunction_UEmotionTransitionRule_EvaluateRule_Statics
{
	struct EmotionTransitionRule_eventEvaluateRule_Parms
	{
		FEmotionSignal Signal;
		float TimeSinceLastTransition;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Emotion|Transition" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Evaluate whether this rule should fire given a signal and timing context.\n\x09 * @param Signal The incoming emotion signal to evaluate against.\n\x09 * @param TimeSinceLastTransition Seconds elapsed since the last emotion transition.\n\x09 * @return True if all conditions are met and the rule should fire.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionTransitionRule.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Evaluate whether this rule should fire given a signal and timing context.\n@param Signal The incoming emotion signal to evaluate against.\n@param TimeSinceLastTransition Seconds elapsed since the last emotion transition.\n@return True if all conditions are met and the rule should fire." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Signal_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function EvaluateRule constinit property declarations **************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Signal;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TimeSinceLastTransition;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function EvaluateRule constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function EvaluateRule Property Definitions *************************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UEmotionTransitionRule_EvaluateRule_Statics::NewProp_Signal = { "Signal", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EmotionTransitionRule_eventEvaluateRule_Parms, Signal), Z_Construct_UScriptStruct_FEmotionSignal, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Signal_MetaData), NewProp_Signal_MetaData) }; // 2625116487
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UEmotionTransitionRule_EvaluateRule_Statics::NewProp_TimeSinceLastTransition = { "TimeSinceLastTransition", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EmotionTransitionRule_eventEvaluateRule_Parms, TimeSinceLastTransition), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UEmotionTransitionRule_EvaluateRule_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((EmotionTransitionRule_eventEvaluateRule_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UEmotionTransitionRule_EvaluateRule_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(EmotionTransitionRule_eventEvaluateRule_Parms), &Z_Construct_UFunction_UEmotionTransitionRule_EvaluateRule_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEmotionTransitionRule_EvaluateRule_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEmotionTransitionRule_EvaluateRule_Statics::NewProp_Signal,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEmotionTransitionRule_EvaluateRule_Statics::NewProp_TimeSinceLastTransition,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEmotionTransitionRule_EvaluateRule_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionTransitionRule_EvaluateRule_Statics::PropPointers) < 2048);
// ********** End Function EvaluateRule Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEmotionTransitionRule_EvaluateRule_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UEmotionTransitionRule, nullptr, "EvaluateRule", 	Z_Construct_UFunction_UEmotionTransitionRule_EvaluateRule_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionTransitionRule_EvaluateRule_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UEmotionTransitionRule_EvaluateRule_Statics::EmotionTransitionRule_eventEvaluateRule_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionTransitionRule_EvaluateRule_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEmotionTransitionRule_EvaluateRule_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UEmotionTransitionRule_EvaluateRule_Statics::EmotionTransitionRule_eventEvaluateRule_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UEmotionTransitionRule_EvaluateRule()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEmotionTransitionRule_EvaluateRule_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UEmotionTransitionRule::execEvaluateRule)
{
	P_GET_STRUCT_REF(FEmotionSignal,Z_Param_Out_Signal);
	P_GET_PROPERTY(FFloatProperty,Z_Param_TimeSinceLastTransition);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->EvaluateRule(Z_Param_Out_Signal,Z_Param_TimeSinceLastTransition);
	P_NATIVE_END;
}
// ********** End Class UEmotionTransitionRule Function EvaluateRule *******************************

// ********** Begin Class UEmotionTransitionRule Function GetTransitionCost ************************
struct Z_Construct_UFunction_UEmotionTransitionRule_GetTransitionCost_Statics
{
	struct EmotionTransitionRule_eventGetTransitionCost_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Emotion|Transition" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Get the cost of this transition for A*-like search.\n\x09 * @return The transition cost value.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionTransitionRule.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get the cost of this transition for A*-like search.\n@return The transition cost value." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetTransitionCost constinit property declarations *********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetTransitionCost constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetTransitionCost Property Definitions ********************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UEmotionTransitionRule_GetTransitionCost_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EmotionTransitionRule_eventGetTransitionCost_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEmotionTransitionRule_GetTransitionCost_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEmotionTransitionRule_GetTransitionCost_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionTransitionRule_GetTransitionCost_Statics::PropPointers) < 2048);
// ********** End Function GetTransitionCost Property Definitions **********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEmotionTransitionRule_GetTransitionCost_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UEmotionTransitionRule, nullptr, "GetTransitionCost", 	Z_Construct_UFunction_UEmotionTransitionRule_GetTransitionCost_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionTransitionRule_GetTransitionCost_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UEmotionTransitionRule_GetTransitionCost_Statics::EmotionTransitionRule_eventGetTransitionCost_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionTransitionRule_GetTransitionCost_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEmotionTransitionRule_GetTransitionCost_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UEmotionTransitionRule_GetTransitionCost_Statics::EmotionTransitionRule_eventGetTransitionCost_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UEmotionTransitionRule_GetTransitionCost()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEmotionTransitionRule_GetTransitionCost_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UEmotionTransitionRule::execGetTransitionCost)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetTransitionCost();
	P_NATIVE_END;
}
// ********** End Class UEmotionTransitionRule Function GetTransitionCost **************************

// ********** Begin Class UEmotionTransitionRule ***************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UEmotionTransitionRule;
UClass* UEmotionTransitionRule::GetPrivateStaticClass()
{
	using TClass = UEmotionTransitionRule;
	if (!Z_Registration_Info_UClass_UEmotionTransitionRule.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("EmotionTransitionRule"),
			Z_Registration_Info_UClass_UEmotionTransitionRule.InnerSingleton,
			StaticRegisterNativesUEmotionTransitionRule,
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
	return Z_Registration_Info_UClass_UEmotionTransitionRule.InnerSingleton;
}
UClass* Z_Construct_UClass_UEmotionTransitionRule_NoRegister()
{
	return UEmotionTransitionRule::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UEmotionTransitionRule_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * A single transition rule in the emotion graph.\n * Represents a directed edge from one emotion state to another,\n * with conditions that must be met for the transition to fire.\n *\n * Inspired by F.E.A.R.'s GOAP system: each transition has a cost,\n * enabling A*-like search through emotion space to find the\n * lowest-cost path to a goal emotion.\n */" },
#endif
		{ "IncludePath", "Emotion/EmotionTransitionRule.h" },
		{ "ModuleRelativePath", "Emotion/EmotionTransitionRule.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A single transition rule in the emotion graph.\nRepresents a directed edge from one emotion state to another,\nwith conditions that must be met for the transition to fire.\n\nInspired by F.E.A.R.'s GOAP system: each transition has a cost,\nenabling A*-like search through emotion space to find the\nlowest-cost path to a goal emotion." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetEmotion_MetaData[] = {
		{ "Category", "Emotion|Transition" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The emotion this rule transitions TO. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionTransitionRule.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The emotion this rule transitions TO." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinInputStrength_MetaData[] = {
		{ "Category", "Emotion|Transition" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Minimum signal strength required for this rule to activate. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionTransitionRule.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Minimum signal strength required for this rule to activate." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RequiredKeywords_MetaData[] = {
		{ "Category", "Emotion|Transition" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Keywords that must be present in the signal source for this rule to match.\n\x09 * If empty, any source matches. If populated, at least one keyword must appear.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionTransitionRule.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Keywords that must be present in the signal source for this rule to match.\nIf empty, any source matches. If populated, at least one keyword must appear." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CooldownTime_MetaData[] = {
		{ "Category", "Emotion|Transition" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Minimum time (seconds) that must elapse since the last transition before this rule can fire again. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionTransitionRule.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Minimum time (seconds) that must elapse since the last transition before this rule can fire again." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TransitionCost_MetaData[] = {
		{ "Category", "Emotion|Transition" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Weight/priority of this rule. Lower cost = preferred transition in A* search. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionTransitionRule.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Weight/priority of this rule. Lower cost = preferred transition in A* search." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UEmotionTransitionRule constinit property declarations *******************
	static const UECodeGen_Private::FBytePropertyParams NewProp_TargetEmotion_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_TargetEmotion;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MinInputStrength;
	static const UECodeGen_Private::FStrPropertyParams NewProp_RequiredKeywords_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_RequiredKeywords;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CooldownTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TransitionCost;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UEmotionTransitionRule constinit property declarations *********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("EvaluateRule"), .Pointer = &UEmotionTransitionRule::execEvaluateRule },
		{ .NameUTF8 = UTF8TEXT("GetTransitionCost"), .Pointer = &UEmotionTransitionRule::execGetTransitionCost },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UEmotionTransitionRule_EvaluateRule, "EvaluateRule" }, // 3404370174
		{ &Z_Construct_UFunction_UEmotionTransitionRule_GetTransitionCost, "GetTransitionCost" }, // 2098291729
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UEmotionTransitionRule>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UEmotionTransitionRule_Statics

// ********** Begin Class UEmotionTransitionRule Property Definitions ******************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UEmotionTransitionRule_Statics::NewProp_TargetEmotion_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UEmotionTransitionRule_Statics::NewProp_TargetEmotion = { "TargetEmotion", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEmotionTransitionRule, TargetEmotion), Z_Construct_UEnum_LLM_NPC_EEmotionType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetEmotion_MetaData), NewProp_TargetEmotion_MetaData) }; // 1184287893
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UEmotionTransitionRule_Statics::NewProp_MinInputStrength = { "MinInputStrength", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEmotionTransitionRule, MinInputStrength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinInputStrength_MetaData), NewProp_MinInputStrength_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UEmotionTransitionRule_Statics::NewProp_RequiredKeywords_Inner = { "RequiredKeywords", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UEmotionTransitionRule_Statics::NewProp_RequiredKeywords = { "RequiredKeywords", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEmotionTransitionRule, RequiredKeywords), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RequiredKeywords_MetaData), NewProp_RequiredKeywords_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UEmotionTransitionRule_Statics::NewProp_CooldownTime = { "CooldownTime", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEmotionTransitionRule, CooldownTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CooldownTime_MetaData), NewProp_CooldownTime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UEmotionTransitionRule_Statics::NewProp_TransitionCost = { "TransitionCost", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEmotionTransitionRule, TransitionCost), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TransitionCost_MetaData), NewProp_TransitionCost_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UEmotionTransitionRule_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionTransitionRule_Statics::NewProp_TargetEmotion_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionTransitionRule_Statics::NewProp_TargetEmotion,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionTransitionRule_Statics::NewProp_MinInputStrength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionTransitionRule_Statics::NewProp_RequiredKeywords_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionTransitionRule_Statics::NewProp_RequiredKeywords,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionTransitionRule_Statics::NewProp_CooldownTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionTransitionRule_Statics::NewProp_TransitionCost,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UEmotionTransitionRule_Statics::PropPointers) < 2048);
// ********** End Class UEmotionTransitionRule Property Definitions ********************************
UObject* (*const Z_Construct_UClass_UEmotionTransitionRule_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UEmotionTransitionRule_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UEmotionTransitionRule_Statics::ClassParams = {
	&UEmotionTransitionRule::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UEmotionTransitionRule_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UEmotionTransitionRule_Statics::PropPointers),
	0,
	0x003010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UEmotionTransitionRule_Statics::Class_MetaDataParams), Z_Construct_UClass_UEmotionTransitionRule_Statics::Class_MetaDataParams)
};
void UEmotionTransitionRule::StaticRegisterNativesUEmotionTransitionRule()
{
	UClass* Class = UEmotionTransitionRule::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UEmotionTransitionRule_Statics::Funcs));
}
UClass* Z_Construct_UClass_UEmotionTransitionRule()
{
	if (!Z_Registration_Info_UClass_UEmotionTransitionRule.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UEmotionTransitionRule.OuterSingleton, Z_Construct_UClass_UEmotionTransitionRule_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UEmotionTransitionRule.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UEmotionTransitionRule);
UEmotionTransitionRule::~UEmotionTransitionRule() {}
// ********** End Class UEmotionTransitionRule *****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionTransitionRule_h__Script_LLM_NPC_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UEmotionTransitionRule, UEmotionTransitionRule::StaticClass, TEXT("UEmotionTransitionRule"), &Z_Registration_Info_UClass_UEmotionTransitionRule, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UEmotionTransitionRule), 3698733061U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionTransitionRule_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionTransitionRule_h__Script_LLM_NPC_1312608806{
	TEXT("/Script/LLM_NPC"),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionTransitionRule_h__Script_LLM_NPC_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionTransitionRule_h__Script_LLM_NPC_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
