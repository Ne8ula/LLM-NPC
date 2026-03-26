// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Gesture/GestureClassifier.h"
#include "LLM_NPC/Core/NPCTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeGestureClassifier() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector2D();
LLM_NPC_API UClass* Z_Construct_UClass_UGestureClassifier();
LLM_NPC_API UClass* Z_Construct_UClass_UGestureClassifier_NoRegister();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FGestureInput();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UGestureClassifier Function ClassifyGesture ******************************
struct Z_Construct_UFunction_UGestureClassifier_ClassifyGesture_Statics
{
	struct GestureClassifier_eventClassifyGesture_Parms
	{
		TArray<FVector2D> CurrentLandmarks;
		float DeltaTime;
		FGestureInput ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Gesture" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Classify the current gesture from hand landmarks.\n\x09 * Compares current landmarks against the history buffer to determine\n\x09 * gesture type and magnitude.\n\x09 *\n\x09 * @param CurrentLandmarks  21 normalized (0-1) 2D hand landmarks.\n\x09 * @param DeltaTime         Time since last frame in seconds.\n\x09 * @return Classified gesture with magnitude and confidence.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Gesture/GestureClassifier.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Classify the current gesture from hand landmarks.\nCompares current landmarks against the history buffer to determine\ngesture type and magnitude.\n\n@param CurrentLandmarks  21 normalized (0-1) 2D hand landmarks.\n@param DeltaTime         Time since last frame in seconds.\n@return Classified gesture with magnitude and confidence." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentLandmarks_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ClassifyGesture constinit property declarations ***********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_CurrentLandmarks_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_CurrentLandmarks;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DeltaTime;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ClassifyGesture constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ClassifyGesture Property Definitions **********************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGestureClassifier_ClassifyGesture_Statics::NewProp_CurrentLandmarks_Inner = { "CurrentLandmarks", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UGestureClassifier_ClassifyGesture_Statics::NewProp_CurrentLandmarks = { "CurrentLandmarks", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GestureClassifier_eventClassifyGesture_Parms, CurrentLandmarks), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentLandmarks_MetaData), NewProp_CurrentLandmarks_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGestureClassifier_ClassifyGesture_Statics::NewProp_DeltaTime = { "DeltaTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GestureClassifier_eventClassifyGesture_Parms, DeltaTime), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGestureClassifier_ClassifyGesture_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GestureClassifier_eventClassifyGesture_Parms, ReturnValue), Z_Construct_UScriptStruct_FGestureInput, METADATA_PARAMS(0, nullptr) }; // 3452162926
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGestureClassifier_ClassifyGesture_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGestureClassifier_ClassifyGesture_Statics::NewProp_CurrentLandmarks_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGestureClassifier_ClassifyGesture_Statics::NewProp_CurrentLandmarks,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGestureClassifier_ClassifyGesture_Statics::NewProp_DeltaTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGestureClassifier_ClassifyGesture_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGestureClassifier_ClassifyGesture_Statics::PropPointers) < 2048);
// ********** End Function ClassifyGesture Property Definitions ************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGestureClassifier_ClassifyGesture_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UGestureClassifier, nullptr, "ClassifyGesture", 	Z_Construct_UFunction_UGestureClassifier_ClassifyGesture_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UGestureClassifier_ClassifyGesture_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UGestureClassifier_ClassifyGesture_Statics::GestureClassifier_eventClassifyGesture_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGestureClassifier_ClassifyGesture_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGestureClassifier_ClassifyGesture_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UGestureClassifier_ClassifyGesture_Statics::GestureClassifier_eventClassifyGesture_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGestureClassifier_ClassifyGesture()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGestureClassifier_ClassifyGesture_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGestureClassifier::execClassifyGesture)
{
	P_GET_TARRAY_REF(FVector2D,Z_Param_Out_CurrentLandmarks);
	P_GET_PROPERTY(FFloatProperty,Z_Param_DeltaTime);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FGestureInput*)Z_Param__Result=P_THIS->ClassifyGesture(Z_Param_Out_CurrentLandmarks,Z_Param_DeltaTime);
	P_NATIVE_END;
}
// ********** End Class UGestureClassifier Function ClassifyGesture ********************************

// ********** Begin Class UGestureClassifier Function ClassifyTwoHandGesture ***********************
struct Z_Construct_UFunction_UGestureClassifier_ClassifyTwoHandGesture_Statics
{
	struct GestureClassifier_eventClassifyTwoHandGesture_Parms
	{
		TArray<FVector2D> LeftLandmarks;
		TArray<FVector2D> RightLandmarks;
		float DeltaTime;
		FGestureInput ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Gesture" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Classify gesture when two hands are detected (enables Spindle gesture).\n\x09 * @param LeftLandmarks   21 landmarks for the left hand.\n\x09 * @param RightLandmarks  21 landmarks for the right hand.\n\x09 * @param DeltaTime       Time since last frame in seconds.\n\x09 * @return Classified gesture.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Gesture/GestureClassifier.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Classify gesture when two hands are detected (enables Spindle gesture).\n@param LeftLandmarks   21 landmarks for the left hand.\n@param RightLandmarks  21 landmarks for the right hand.\n@param DeltaTime       Time since last frame in seconds.\n@return Classified gesture." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LeftLandmarks_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RightLandmarks_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ClassifyTwoHandGesture constinit property declarations ****************
	static const UECodeGen_Private::FStructPropertyParams NewProp_LeftLandmarks_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_LeftLandmarks;
	static const UECodeGen_Private::FStructPropertyParams NewProp_RightLandmarks_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_RightLandmarks;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DeltaTime;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ClassifyTwoHandGesture constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ClassifyTwoHandGesture Property Definitions ***************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGestureClassifier_ClassifyTwoHandGesture_Statics::NewProp_LeftLandmarks_Inner = { "LeftLandmarks", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UGestureClassifier_ClassifyTwoHandGesture_Statics::NewProp_LeftLandmarks = { "LeftLandmarks", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GestureClassifier_eventClassifyTwoHandGesture_Parms, LeftLandmarks), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LeftLandmarks_MetaData), NewProp_LeftLandmarks_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGestureClassifier_ClassifyTwoHandGesture_Statics::NewProp_RightLandmarks_Inner = { "RightLandmarks", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UGestureClassifier_ClassifyTwoHandGesture_Statics::NewProp_RightLandmarks = { "RightLandmarks", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GestureClassifier_eventClassifyTwoHandGesture_Parms, RightLandmarks), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RightLandmarks_MetaData), NewProp_RightLandmarks_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGestureClassifier_ClassifyTwoHandGesture_Statics::NewProp_DeltaTime = { "DeltaTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GestureClassifier_eventClassifyTwoHandGesture_Parms, DeltaTime), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGestureClassifier_ClassifyTwoHandGesture_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GestureClassifier_eventClassifyTwoHandGesture_Parms, ReturnValue), Z_Construct_UScriptStruct_FGestureInput, METADATA_PARAMS(0, nullptr) }; // 3452162926
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGestureClassifier_ClassifyTwoHandGesture_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGestureClassifier_ClassifyTwoHandGesture_Statics::NewProp_LeftLandmarks_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGestureClassifier_ClassifyTwoHandGesture_Statics::NewProp_LeftLandmarks,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGestureClassifier_ClassifyTwoHandGesture_Statics::NewProp_RightLandmarks_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGestureClassifier_ClassifyTwoHandGesture_Statics::NewProp_RightLandmarks,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGestureClassifier_ClassifyTwoHandGesture_Statics::NewProp_DeltaTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGestureClassifier_ClassifyTwoHandGesture_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGestureClassifier_ClassifyTwoHandGesture_Statics::PropPointers) < 2048);
// ********** End Function ClassifyTwoHandGesture Property Definitions *****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGestureClassifier_ClassifyTwoHandGesture_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UGestureClassifier, nullptr, "ClassifyTwoHandGesture", 	Z_Construct_UFunction_UGestureClassifier_ClassifyTwoHandGesture_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UGestureClassifier_ClassifyTwoHandGesture_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UGestureClassifier_ClassifyTwoHandGesture_Statics::GestureClassifier_eventClassifyTwoHandGesture_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGestureClassifier_ClassifyTwoHandGesture_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGestureClassifier_ClassifyTwoHandGesture_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UGestureClassifier_ClassifyTwoHandGesture_Statics::GestureClassifier_eventClassifyTwoHandGesture_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGestureClassifier_ClassifyTwoHandGesture()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGestureClassifier_ClassifyTwoHandGesture_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGestureClassifier::execClassifyTwoHandGesture)
{
	P_GET_TARRAY_REF(FVector2D,Z_Param_Out_LeftLandmarks);
	P_GET_TARRAY_REF(FVector2D,Z_Param_Out_RightLandmarks);
	P_GET_PROPERTY(FFloatProperty,Z_Param_DeltaTime);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FGestureInput*)Z_Param__Result=P_THIS->ClassifyTwoHandGesture(Z_Param_Out_LeftLandmarks,Z_Param_Out_RightLandmarks,Z_Param_DeltaTime);
	P_NATIVE_END;
}
// ********** End Class UGestureClassifier Function ClassifyTwoHandGesture *************************

// ********** Begin Class UGestureClassifier Function Reset ****************************************
struct Z_Construct_UFunction_UGestureClassifier_Reset_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Gesture" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Reset the internal state and history buffer. */" },
#endif
		{ "ModuleRelativePath", "Gesture/GestureClassifier.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Reset the internal state and history buffer." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function Reset constinit property declarations *********************************
// ********** End Function Reset constinit property declarations ***********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGestureClassifier_Reset_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UGestureClassifier, nullptr, "Reset", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGestureClassifier_Reset_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGestureClassifier_Reset_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UGestureClassifier_Reset()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGestureClassifier_Reset_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGestureClassifier::execReset)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Reset();
	P_NATIVE_END;
}
// ********** End Class UGestureClassifier Function Reset ******************************************

// ********** Begin Class UGestureClassifier *******************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UGestureClassifier;
UClass* UGestureClassifier::GetPrivateStaticClass()
{
	using TClass = UGestureClassifier;
	if (!Z_Registration_Info_UClass_UGestureClassifier.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("GestureClassifier"),
			Z_Registration_Info_UClass_UGestureClassifier.InnerSingleton,
			StaticRegisterNativesUGestureClassifier,
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
	return Z_Registration_Info_UClass_UGestureClassifier.InnerSingleton;
}
UClass* Z_Construct_UClass_UGestureClassifier_NoRegister()
{
	return UGestureClassifier::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UGestureClassifier_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Pure geometry-based gesture classifier from hand landmarks.\n *\n * Research-backed interaction enhancements:\n * - Go-Go non-linear gain: small movements map 1:1, beyond threshold D\n *   uses Rv = Rr + k*(Rr - D)^2 for reaching distant objects.\n * - PRISM precision: when hand velocity < threshold, magnitude is scaled\n *   down for fine-grained control.\n * - Spring-damper smoothing: virtual spring-damper model compensates for\n *   the lack of haptic feedback in vision-based tracking.\n */" },
#endif
		{ "IncludePath", "Gesture/GestureClassifier.h" },
		{ "ModuleRelativePath", "Gesture/GestureClassifier.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Pure geometry-based gesture classifier from hand landmarks.\n\nResearch-backed interaction enhancements:\n- Go-Go non-linear gain: small movements map 1:1, beyond threshold D\n  uses Rv = Rr + k*(Rr - D)^2 for reaching distant objects.\n- PRISM precision: when hand velocity < threshold, magnitude is scaled\n  down for fine-grained control.\n- Spring-damper smoothing: virtual spring-damper model compensates for\n  the lack of haptic feedback in vision-based tracking." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GoGoThresholdD_MetaData[] = {
		{ "Category", "NPC|Gesture|GoGo" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Go-Go: distance threshold beyond which non-linear gain applies. */" },
#endif
		{ "ModuleRelativePath", "Gesture/GestureClassifier.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Go-Go: distance threshold beyond which non-linear gain applies." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GoGoCoeffK_MetaData[] = {
		{ "Category", "NPC|Gesture|GoGo" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Go-Go: quadratic coefficient for non-linear gain. */" },
#endif
		{ "ModuleRelativePath", "Gesture/GestureClassifier.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Go-Go: quadratic coefficient for non-linear gain." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PRISMVelocityThreshold_MetaData[] = {
		{ "Category", "NPC|Gesture|PRISM" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** PRISM: hand velocity threshold below which precision scaling applies. */" },
#endif
		{ "ModuleRelativePath", "Gesture/GestureClassifier.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "PRISM: hand velocity threshold below which precision scaling applies." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PRISMPrecisionScale_MetaData[] = {
		{ "Category", "NPC|Gesture|PRISM" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** PRISM: scale factor for precision mode (applied when velocity < threshold). */" },
#endif
		{ "ModuleRelativePath", "Gesture/GestureClassifier.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "PRISM: scale factor for precision mode (applied when velocity < threshold)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpringStiffness_MetaData[] = {
		{ "Category", "NPC|Gesture|SpringDamper" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Spring stiffness for spring-damper smoothing. */" },
#endif
		{ "ModuleRelativePath", "Gesture/GestureClassifier.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Spring stiffness for spring-damper smoothing." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DamperCoefficient_MetaData[] = {
		{ "Category", "NPC|Gesture|SpringDamper" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Damping coefficient for spring-damper smoothing. */" },
#endif
		{ "ModuleRelativePath", "Gesture/GestureClassifier.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Damping coefficient for spring-damper smoothing." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PinchThreshold_MetaData[] = {
		{ "Category", "NPC|Gesture" },
		{ "ClampMax", "0.5" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Minimum pinch distance to register as active pinch. */" },
#endif
		{ "ModuleRelativePath", "Gesture/GestureClassifier.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Minimum pinch distance to register as active pinch." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HistoryBufferSize_MetaData[] = {
		{ "Category", "NPC|Gesture" },
		{ "ClampMax", "30" },
		{ "ClampMin", "2" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Number of frames to buffer for velocity computation and noise filtering. */" },
#endif
		{ "ModuleRelativePath", "Gesture/GestureClassifier.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Number of frames to buffer for velocity computation and noise filtering." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UGestureClassifier constinit property declarations ***********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_GoGoThresholdD;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_GoGoCoeffK;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PRISMVelocityThreshold;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PRISMPrecisionScale;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SpringStiffness;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DamperCoefficient;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PinchThreshold;
	static const UECodeGen_Private::FIntPropertyParams NewProp_HistoryBufferSize;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UGestureClassifier constinit property declarations *************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("ClassifyGesture"), .Pointer = &UGestureClassifier::execClassifyGesture },
		{ .NameUTF8 = UTF8TEXT("ClassifyTwoHandGesture"), .Pointer = &UGestureClassifier::execClassifyTwoHandGesture },
		{ .NameUTF8 = UTF8TEXT("Reset"), .Pointer = &UGestureClassifier::execReset },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UGestureClassifier_ClassifyGesture, "ClassifyGesture" }, // 666383900
		{ &Z_Construct_UFunction_UGestureClassifier_ClassifyTwoHandGesture, "ClassifyTwoHandGesture" }, // 2010627264
		{ &Z_Construct_UFunction_UGestureClassifier_Reset, "Reset" }, // 2226655645
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGestureClassifier>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UGestureClassifier_Statics

// ********** Begin Class UGestureClassifier Property Definitions **********************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGestureClassifier_Statics::NewProp_GoGoThresholdD = { "GoGoThresholdD", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGestureClassifier, GoGoThresholdD), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GoGoThresholdD_MetaData), NewProp_GoGoThresholdD_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGestureClassifier_Statics::NewProp_GoGoCoeffK = { "GoGoCoeffK", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGestureClassifier, GoGoCoeffK), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GoGoCoeffK_MetaData), NewProp_GoGoCoeffK_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGestureClassifier_Statics::NewProp_PRISMVelocityThreshold = { "PRISMVelocityThreshold", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGestureClassifier, PRISMVelocityThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PRISMVelocityThreshold_MetaData), NewProp_PRISMVelocityThreshold_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGestureClassifier_Statics::NewProp_PRISMPrecisionScale = { "PRISMPrecisionScale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGestureClassifier, PRISMPrecisionScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PRISMPrecisionScale_MetaData), NewProp_PRISMPrecisionScale_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGestureClassifier_Statics::NewProp_SpringStiffness = { "SpringStiffness", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGestureClassifier, SpringStiffness), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpringStiffness_MetaData), NewProp_SpringStiffness_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGestureClassifier_Statics::NewProp_DamperCoefficient = { "DamperCoefficient", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGestureClassifier, DamperCoefficient), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DamperCoefficient_MetaData), NewProp_DamperCoefficient_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGestureClassifier_Statics::NewProp_PinchThreshold = { "PinchThreshold", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGestureClassifier, PinchThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PinchThreshold_MetaData), NewProp_PinchThreshold_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGestureClassifier_Statics::NewProp_HistoryBufferSize = { "HistoryBufferSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGestureClassifier, HistoryBufferSize), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HistoryBufferSize_MetaData), NewProp_HistoryBufferSize_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGestureClassifier_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGestureClassifier_Statics::NewProp_GoGoThresholdD,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGestureClassifier_Statics::NewProp_GoGoCoeffK,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGestureClassifier_Statics::NewProp_PRISMVelocityThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGestureClassifier_Statics::NewProp_PRISMPrecisionScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGestureClassifier_Statics::NewProp_SpringStiffness,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGestureClassifier_Statics::NewProp_DamperCoefficient,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGestureClassifier_Statics::NewProp_PinchThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGestureClassifier_Statics::NewProp_HistoryBufferSize,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGestureClassifier_Statics::PropPointers) < 2048);
// ********** End Class UGestureClassifier Property Definitions ************************************
UObject* (*const Z_Construct_UClass_UGestureClassifier_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGestureClassifier_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGestureClassifier_Statics::ClassParams = {
	&UGestureClassifier::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UGestureClassifier_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UGestureClassifier_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGestureClassifier_Statics::Class_MetaDataParams), Z_Construct_UClass_UGestureClassifier_Statics::Class_MetaDataParams)
};
void UGestureClassifier::StaticRegisterNativesUGestureClassifier()
{
	UClass* Class = UGestureClassifier::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UGestureClassifier_Statics::Funcs));
}
UClass* Z_Construct_UClass_UGestureClassifier()
{
	if (!Z_Registration_Info_UClass_UGestureClassifier.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGestureClassifier.OuterSingleton, Z_Construct_UClass_UGestureClassifier_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGestureClassifier.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UGestureClassifier);
UGestureClassifier::~UGestureClassifier() {}
// ********** End Class UGestureClassifier *********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_GestureClassifier_h__Script_LLM_NPC_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGestureClassifier, UGestureClassifier::StaticClass, TEXT("UGestureClassifier"), &Z_Registration_Info_UClass_UGestureClassifier, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGestureClassifier), 2862986290U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_GestureClassifier_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_GestureClassifier_h__Script_LLM_NPC_2820230903{
	TEXT("/Script/LLM_NPC"),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_GestureClassifier_h__Script_LLM_NPC_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_GestureClassifier_h__Script_LLM_NPC_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
