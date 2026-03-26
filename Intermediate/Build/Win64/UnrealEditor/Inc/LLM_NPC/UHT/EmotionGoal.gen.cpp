// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Emotion/EmotionGoal.h"
#include "LLM_NPC/Core/NPCTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeEmotionGoal() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
LLM_NPC_API UClass* Z_Construct_UClass_UEmotionGoal();
LLM_NPC_API UClass* Z_Construct_UClass_UEmotionGoal_NoRegister();
LLM_NPC_API UEnum* Z_Construct_UEnum_LLM_NPC_EEmotionType();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FEmotionState();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UEmotionGoal Function GetCostToReach *************************************
struct Z_Construct_UFunction_UEmotionGoal_GetCostToReach_Statics
{
	struct EmotionGoal_eventGetCostToReach_Parms
	{
		FEmotionState FromState;
		TMap<EEmotionType,float> TransitionCosts;
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Emotion|Goal" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Estimate cost to reach this goal from a given state using A*-like heuristic.\n\x09 * Combines PAD Euclidean distance with per-emotion transition cost multipliers.\n\x09 * @param FromState The starting emotional state.\n\x09 * @param TransitionCosts Per-emotion cost multipliers from the NPC archetype config.\n\x09 * @return Estimated cost (lower = easier to reach).\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionGoal.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Estimate cost to reach this goal from a given state using A*-like heuristic.\nCombines PAD Euclidean distance with per-emotion transition cost multipliers.\n@param FromState The starting emotional state.\n@param TransitionCosts Per-emotion cost multipliers from the NPC archetype config.\n@return Estimated cost (lower = easier to reach)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FromState_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TransitionCosts_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetCostToReach constinit property declarations ************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_FromState;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TransitionCosts_ValueProp;
	static const UECodeGen_Private::FBytePropertyParams NewProp_TransitionCosts_Key_KeyProp_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_TransitionCosts_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_TransitionCosts;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetCostToReach constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetCostToReach Property Definitions ***********************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UEmotionGoal_GetCostToReach_Statics::NewProp_FromState = { "FromState", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EmotionGoal_eventGetCostToReach_Parms, FromState), Z_Construct_UScriptStruct_FEmotionState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FromState_MetaData), NewProp_FromState_MetaData) }; // 1004811449
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UEmotionGoal_GetCostToReach_Statics::NewProp_TransitionCosts_ValueProp = { "TransitionCosts", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UEmotionGoal_GetCostToReach_Statics::NewProp_TransitionCosts_Key_KeyProp_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UEmotionGoal_GetCostToReach_Statics::NewProp_TransitionCosts_Key_KeyProp = { "TransitionCosts_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UEnum_LLM_NPC_EEmotionType, METADATA_PARAMS(0, nullptr) }; // 1184287893
const UECodeGen_Private::FMapPropertyParams Z_Construct_UFunction_UEmotionGoal_GetCostToReach_Statics::NewProp_TransitionCosts = { "TransitionCosts", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EmotionGoal_eventGetCostToReach_Parms, TransitionCosts), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TransitionCosts_MetaData), NewProp_TransitionCosts_MetaData) }; // 1184287893
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UEmotionGoal_GetCostToReach_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EmotionGoal_eventGetCostToReach_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEmotionGoal_GetCostToReach_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEmotionGoal_GetCostToReach_Statics::NewProp_FromState,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEmotionGoal_GetCostToReach_Statics::NewProp_TransitionCosts_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEmotionGoal_GetCostToReach_Statics::NewProp_TransitionCosts_Key_KeyProp_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEmotionGoal_GetCostToReach_Statics::NewProp_TransitionCosts_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEmotionGoal_GetCostToReach_Statics::NewProp_TransitionCosts,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEmotionGoal_GetCostToReach_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionGoal_GetCostToReach_Statics::PropPointers) < 2048);
// ********** End Function GetCostToReach Property Definitions *************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEmotionGoal_GetCostToReach_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UEmotionGoal, nullptr, "GetCostToReach", 	Z_Construct_UFunction_UEmotionGoal_GetCostToReach_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionGoal_GetCostToReach_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UEmotionGoal_GetCostToReach_Statics::EmotionGoal_eventGetCostToReach_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionGoal_GetCostToReach_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEmotionGoal_GetCostToReach_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UEmotionGoal_GetCostToReach_Statics::EmotionGoal_eventGetCostToReach_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UEmotionGoal_GetCostToReach()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEmotionGoal_GetCostToReach_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UEmotionGoal::execGetCostToReach)
{
	P_GET_STRUCT_REF(FEmotionState,Z_Param_Out_FromState);
	P_GET_TMAP_REF(EEmotionType,float,Z_Param_Out_TransitionCosts);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetCostToReach(Z_Param_Out_FromState,Z_Param_Out_TransitionCosts);
	P_NATIVE_END;
}
// ********** End Class UEmotionGoal Function GetCostToReach ***************************************

// ********** Begin Class UEmotionGoal Function IsSatisfied ****************************************
struct Z_Construct_UFunction_UEmotionGoal_IsSatisfied_Statics
{
	struct EmotionGoal_eventIsSatisfied_Parms
	{
		FEmotionState CurrentState;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Emotion|Goal" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Check if the current emotional state satisfies this goal.\n\x09 * Satisfied when the primary emotion matches and intensity is within tolerance.\n\x09 * @param CurrentState The NPC's current emotional state.\n\x09 * @return True if the goal is considered satisfied.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionGoal.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Check if the current emotional state satisfies this goal.\nSatisfied when the primary emotion matches and intensity is within tolerance.\n@param CurrentState The NPC's current emotional state.\n@return True if the goal is considered satisfied." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentState_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsSatisfied constinit property declarations ***************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_CurrentState;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsSatisfied constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsSatisfied Property Definitions **************************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UEmotionGoal_IsSatisfied_Statics::NewProp_CurrentState = { "CurrentState", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EmotionGoal_eventIsSatisfied_Parms, CurrentState), Z_Construct_UScriptStruct_FEmotionState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentState_MetaData), NewProp_CurrentState_MetaData) }; // 1004811449
void Z_Construct_UFunction_UEmotionGoal_IsSatisfied_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((EmotionGoal_eventIsSatisfied_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UEmotionGoal_IsSatisfied_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(EmotionGoal_eventIsSatisfied_Parms), &Z_Construct_UFunction_UEmotionGoal_IsSatisfied_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEmotionGoal_IsSatisfied_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEmotionGoal_IsSatisfied_Statics::NewProp_CurrentState,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEmotionGoal_IsSatisfied_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionGoal_IsSatisfied_Statics::PropPointers) < 2048);
// ********** End Function IsSatisfied Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEmotionGoal_IsSatisfied_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UEmotionGoal, nullptr, "IsSatisfied", 	Z_Construct_UFunction_UEmotionGoal_IsSatisfied_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionGoal_IsSatisfied_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UEmotionGoal_IsSatisfied_Statics::EmotionGoal_eventIsSatisfied_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEmotionGoal_IsSatisfied_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEmotionGoal_IsSatisfied_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UEmotionGoal_IsSatisfied_Statics::EmotionGoal_eventIsSatisfied_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UEmotionGoal_IsSatisfied()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEmotionGoal_IsSatisfied_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UEmotionGoal::execIsSatisfied)
{
	P_GET_STRUCT_REF(FEmotionState,Z_Param_Out_CurrentState);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsSatisfied(Z_Param_Out_CurrentState);
	P_NATIVE_END;
}
// ********** End Class UEmotionGoal Function IsSatisfied ******************************************

// ********** Begin Class UEmotionGoal *************************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UEmotionGoal;
UClass* UEmotionGoal::GetPrivateStaticClass()
{
	using TClass = UEmotionGoal;
	if (!Z_Registration_Info_UClass_UEmotionGoal.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("EmotionGoal"),
			Z_Registration_Info_UClass_UEmotionGoal.InnerSingleton,
			StaticRegisterNativesUEmotionGoal,
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
	return Z_Registration_Info_UClass_UEmotionGoal.InnerSingleton;
}
UClass* Z_Construct_UClass_UEmotionGoal_NoRegister()
{
	return UEmotionGoal::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UEmotionGoal_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * GOAP-style goal defining WHAT emotional state the NPC should reach.\n *\n * Goals are archetype-agnostic: different NPC archetypes share the same goals\n * but have different transition costs, so a \"stoic warrior\" and a \"nervous merchant\"\n * reach the same goal emotion via different paths through PAD space.\n *\n * Cost calculation uses PAD distance + weighted transition cost map,\n * enabling A*-like planning through the emotion graph.\n */" },
#endif
		{ "IncludePath", "Emotion/EmotionGoal.h" },
		{ "ModuleRelativePath", "Emotion/EmotionGoal.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "GOAP-style goal defining WHAT emotional state the NPC should reach.\n\nGoals are archetype-agnostic: different NPC archetypes share the same goals\nbut have different transition costs, so a \"stoic warrior\" and a \"nervous merchant\"\nreach the same goal emotion via different paths through PAD space.\n\nCost calculation uses PAD distance + weighted transition cost map,\nenabling A*-like planning through the emotion graph." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GoalEmotion_MetaData[] = {
		{ "Category", "Emotion|Goal" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The target emotion this goal wants to reach. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionGoal.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The target emotion this goal wants to reach." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GoalIntensity_MetaData[] = {
		{ "Category", "Emotion|Goal" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Desired intensity at the goal emotion. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionGoal.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Desired intensity at the goal emotion." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Priority_MetaData[] = {
		{ "Category", "Emotion|Goal" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Priority of this goal. Higher priority goals are preferred when multiple goals compete. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionGoal.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Priority of this goal. Higher priority goals are preferred when multiple goals compete." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IntensityTolerance_MetaData[] = {
		{ "Category", "Emotion|Goal" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Intensity tolerance for goal satisfaction. */" },
#endif
		{ "ModuleRelativePath", "Emotion/EmotionGoal.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Intensity tolerance for goal satisfaction." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UEmotionGoal constinit property declarations *****************************
	static const UECodeGen_Private::FBytePropertyParams NewProp_GoalEmotion_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_GoalEmotion;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_GoalIntensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Priority;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_IntensityTolerance;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UEmotionGoal constinit property declarations *******************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("GetCostToReach"), .Pointer = &UEmotionGoal::execGetCostToReach },
		{ .NameUTF8 = UTF8TEXT("IsSatisfied"), .Pointer = &UEmotionGoal::execIsSatisfied },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UEmotionGoal_GetCostToReach, "GetCostToReach" }, // 3727876079
		{ &Z_Construct_UFunction_UEmotionGoal_IsSatisfied, "IsSatisfied" }, // 1510859359
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UEmotionGoal>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UEmotionGoal_Statics

// ********** Begin Class UEmotionGoal Property Definitions ****************************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UEmotionGoal_Statics::NewProp_GoalEmotion_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UEmotionGoal_Statics::NewProp_GoalEmotion = { "GoalEmotion", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEmotionGoal, GoalEmotion), Z_Construct_UEnum_LLM_NPC_EEmotionType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GoalEmotion_MetaData), NewProp_GoalEmotion_MetaData) }; // 1184287893
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UEmotionGoal_Statics::NewProp_GoalIntensity = { "GoalIntensity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEmotionGoal, GoalIntensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GoalIntensity_MetaData), NewProp_GoalIntensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UEmotionGoal_Statics::NewProp_Priority = { "Priority", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEmotionGoal, Priority), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Priority_MetaData), NewProp_Priority_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UEmotionGoal_Statics::NewProp_IntensityTolerance = { "IntensityTolerance", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEmotionGoal, IntensityTolerance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IntensityTolerance_MetaData), NewProp_IntensityTolerance_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UEmotionGoal_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionGoal_Statics::NewProp_GoalEmotion_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionGoal_Statics::NewProp_GoalEmotion,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionGoal_Statics::NewProp_GoalIntensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionGoal_Statics::NewProp_Priority,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEmotionGoal_Statics::NewProp_IntensityTolerance,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UEmotionGoal_Statics::PropPointers) < 2048);
// ********** End Class UEmotionGoal Property Definitions ******************************************
UObject* (*const Z_Construct_UClass_UEmotionGoal_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UEmotionGoal_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UEmotionGoal_Statics::ClassParams = {
	&UEmotionGoal::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UEmotionGoal_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UEmotionGoal_Statics::PropPointers),
	0,
	0x003010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UEmotionGoal_Statics::Class_MetaDataParams), Z_Construct_UClass_UEmotionGoal_Statics::Class_MetaDataParams)
};
void UEmotionGoal::StaticRegisterNativesUEmotionGoal()
{
	UClass* Class = UEmotionGoal::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UEmotionGoal_Statics::Funcs));
}
UClass* Z_Construct_UClass_UEmotionGoal()
{
	if (!Z_Registration_Info_UClass_UEmotionGoal.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UEmotionGoal.OuterSingleton, Z_Construct_UClass_UEmotionGoal_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UEmotionGoal.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UEmotionGoal);
UEmotionGoal::~UEmotionGoal() {}
// ********** End Class UEmotionGoal ***************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGoal_h__Script_LLM_NPC_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UEmotionGoal, UEmotionGoal::StaticClass, TEXT("UEmotionGoal"), &Z_Registration_Info_UClass_UEmotionGoal, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UEmotionGoal), 673699721U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGoal_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGoal_h__Script_LLM_NPC_111166368{
	TEXT("/Script/LLM_NPC"),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGoal_h__Script_LLM_NPC_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Emotion_EmotionGoal_h__Script_LLM_NPC_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
