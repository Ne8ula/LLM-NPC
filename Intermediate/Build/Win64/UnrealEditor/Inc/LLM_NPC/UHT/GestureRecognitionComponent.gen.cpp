// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Gesture/GestureRecognitionComponent.h"
#include "LLM_NPC/Core/NPCTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeGestureRecognitionComponent() {}

// ********** Begin Cross Module References ********************************************************
LLM_NPC_API UClass* Z_Construct_UClass_UGestureClassifier_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UGestureRecognitionComponent();
LLM_NPC_API UClass* Z_Construct_UClass_UGestureRecognitionComponent_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UHandLandmarkModel_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UNPCSubsystemComponent();
LLM_NPC_API UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnGestureDetected__DelegateSignature();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FGestureInput();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FOnGestureDetected ****************************************************
struct Z_Construct_UDelegateFunction_LLM_NPC_OnGestureDetected__DelegateSignature_Statics
{
	struct _Script_LLM_NPC_eventOnGestureDetected_Parms
	{
		FGestureInput DetectedGesture;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Gesture/GestureRecognitionComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnGestureDetected constinit property declarations ********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_DetectedGesture;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FOnGestureDetected constinit property declarations **********************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FOnGestureDetected Property Definitions *******************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_LLM_NPC_OnGestureDetected__DelegateSignature_Statics::NewProp_DetectedGesture = { "DetectedGesture", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_LLM_NPC_eventOnGestureDetected_Parms, DetectedGesture), Z_Construct_UScriptStruct_FGestureInput, METADATA_PARAMS(0, nullptr) }; // 3452162926
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_LLM_NPC_OnGestureDetected__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LLM_NPC_OnGestureDetected__DelegateSignature_Statics::NewProp_DetectedGesture,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnGestureDetected__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FOnGestureDetected Property Definitions *********************************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_LLM_NPC_OnGestureDetected__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_LLM_NPC, nullptr, "OnGestureDetected__DelegateSignature", 	Z_Construct_UDelegateFunction_LLM_NPC_OnGestureDetected__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnGestureDetected__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_LLM_NPC_OnGestureDetected__DelegateSignature_Statics::_Script_LLM_NPC_eventOnGestureDetected_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnGestureDetected__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_LLM_NPC_OnGestureDetected__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_LLM_NPC_OnGestureDetected__DelegateSignature_Statics::_Script_LLM_NPC_eventOnGestureDetected_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnGestureDetected__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_LLM_NPC_OnGestureDetected__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnGestureDetected_DelegateWrapper(const FMulticastScriptDelegate& OnGestureDetected, FGestureInput DetectedGesture)
{
	struct _Script_LLM_NPC_eventOnGestureDetected_Parms
	{
		FGestureInput DetectedGesture;
	};
	_Script_LLM_NPC_eventOnGestureDetected_Parms Parms;
	Parms.DetectedGesture=DetectedGesture;
	OnGestureDetected.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnGestureDetected ******************************************************

// ********** Begin Class UGestureRecognitionComponent Function GetGestureClassifier ***************
struct Z_Construct_UFunction_UGestureRecognitionComponent_GetGestureClassifier_Statics
{
	struct GestureRecognitionComponent_eventGetGestureClassifier_Parms
	{
		UGestureClassifier* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Gesture" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Access the gesture classifier for tuning parameters. */" },
#endif
		{ "ModuleRelativePath", "Gesture/GestureRecognitionComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Access the gesture classifier for tuning parameters." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetGestureClassifier constinit property declarations ******************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetGestureClassifier constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetGestureClassifier Property Definitions *****************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGestureRecognitionComponent_GetGestureClassifier_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GestureRecognitionComponent_eventGetGestureClassifier_Parms, ReturnValue), Z_Construct_UClass_UGestureClassifier_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGestureRecognitionComponent_GetGestureClassifier_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGestureRecognitionComponent_GetGestureClassifier_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGestureRecognitionComponent_GetGestureClassifier_Statics::PropPointers) < 2048);
// ********** End Function GetGestureClassifier Property Definitions *******************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGestureRecognitionComponent_GetGestureClassifier_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UGestureRecognitionComponent, nullptr, "GetGestureClassifier", 	Z_Construct_UFunction_UGestureRecognitionComponent_GetGestureClassifier_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UGestureRecognitionComponent_GetGestureClassifier_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UGestureRecognitionComponent_GetGestureClassifier_Statics::GestureRecognitionComponent_eventGetGestureClassifier_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGestureRecognitionComponent_GetGestureClassifier_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGestureRecognitionComponent_GetGestureClassifier_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UGestureRecognitionComponent_GetGestureClassifier_Statics::GestureRecognitionComponent_eventGetGestureClassifier_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGestureRecognitionComponent_GetGestureClassifier()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGestureRecognitionComponent_GetGestureClassifier_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGestureRecognitionComponent::execGetGestureClassifier)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UGestureClassifier**)Z_Param__Result=P_THIS->GetGestureClassifier();
	P_NATIVE_END;
}
// ********** End Class UGestureRecognitionComponent Function GetGestureClassifier *****************

// ********** Begin Class UGestureRecognitionComponent *********************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UGestureRecognitionComponent;
UClass* UGestureRecognitionComponent::GetPrivateStaticClass()
{
	using TClass = UGestureRecognitionComponent;
	if (!Z_Registration_Info_UClass_UGestureRecognitionComponent.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("GestureRecognitionComponent"),
			Z_Registration_Info_UClass_UGestureRecognitionComponent.InnerSingleton,
			StaticRegisterNativesUGestureRecognitionComponent,
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
	return Z_Registration_Info_UClass_UGestureRecognitionComponent.InnerSingleton;
}
UClass* Z_Construct_UClass_UGestureRecognitionComponent_NoRegister()
{
	return UGestureRecognitionComponent::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UGestureRecognitionComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "LLMNPC" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * NPC subsystem component that reads camera frames, detects hand landmarks\n * via an ONNX model, and classifies gestures using geometry-based analysis.\n * Processes at ~15 FPS using a timer (not tick-based).\n */" },
#endif
		{ "IncludePath", "Gesture/GestureRecognitionComponent.h" },
		{ "ModuleRelativePath", "Gesture/GestureRecognitionComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "NPC subsystem component that reads camera frames, detects hand landmarks\nvia an ONNX model, and classifies gestures using geometry-based analysis.\nProcesses at ~15 FPS using a timer (not tick-based)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnGestureDetected_MetaData[] = {
		{ "Category", "NPC|Gesture" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Fired when a gesture is detected from the camera feed. */" },
#endif
		{ "ModuleRelativePath", "Gesture/GestureRecognitionComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Fired when a gesture is detected from the camera feed." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HandLandmarkModelPath_MetaData[] = {
		{ "Category", "NPC|Gesture" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Path to the hand landmark ONNX model. */" },
#endif
		{ "ModuleRelativePath", "Gesture/GestureRecognitionComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Path to the hand landmark ONNX model." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProcessingInterval_MetaData[] = {
		{ "Category", "NPC|Gesture" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.016" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Processing rate in seconds (default ~15 FPS = 0.066s interval). */" },
#endif
		{ "ModuleRelativePath", "Gesture/GestureRecognitionComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Processing rate in seconds (default ~15 FPS = 0.066s interval)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HandLandmarkModel_MetaData[] = {
		{ "ModuleRelativePath", "Gesture/GestureRecognitionComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GestureClassifier_MetaData[] = {
		{ "ModuleRelativePath", "Gesture/GestureRecognitionComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UGestureRecognitionComponent constinit property declarations *************
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnGestureDetected;
	static const UECodeGen_Private::FStrPropertyParams NewProp_HandLandmarkModelPath;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ProcessingInterval;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HandLandmarkModel;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_GestureClassifier;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UGestureRecognitionComponent constinit property declarations ***************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("GetGestureClassifier"), .Pointer = &UGestureRecognitionComponent::execGetGestureClassifier },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UGestureRecognitionComponent_GetGestureClassifier, "GetGestureClassifier" }, // 34635511
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGestureRecognitionComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UGestureRecognitionComponent_Statics

// ********** Begin Class UGestureRecognitionComponent Property Definitions ************************
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UGestureRecognitionComponent_Statics::NewProp_OnGestureDetected = { "OnGestureDetected", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGestureRecognitionComponent, OnGestureDetected), Z_Construct_UDelegateFunction_LLM_NPC_OnGestureDetected__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnGestureDetected_MetaData), NewProp_OnGestureDetected_MetaData) }; // 3419906931
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGestureRecognitionComponent_Statics::NewProp_HandLandmarkModelPath = { "HandLandmarkModelPath", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGestureRecognitionComponent, HandLandmarkModelPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HandLandmarkModelPath_MetaData), NewProp_HandLandmarkModelPath_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGestureRecognitionComponent_Statics::NewProp_ProcessingInterval = { "ProcessingInterval", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGestureRecognitionComponent, ProcessingInterval), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProcessingInterval_MetaData), NewProp_ProcessingInterval_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGestureRecognitionComponent_Statics::NewProp_HandLandmarkModel = { "HandLandmarkModel", nullptr, (EPropertyFlags)0x0144000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGestureRecognitionComponent, HandLandmarkModel), Z_Construct_UClass_UHandLandmarkModel_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HandLandmarkModel_MetaData), NewProp_HandLandmarkModel_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGestureRecognitionComponent_Statics::NewProp_GestureClassifier = { "GestureClassifier", nullptr, (EPropertyFlags)0x0144000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGestureRecognitionComponent, GestureClassifier), Z_Construct_UClass_UGestureClassifier_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GestureClassifier_MetaData), NewProp_GestureClassifier_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGestureRecognitionComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGestureRecognitionComponent_Statics::NewProp_OnGestureDetected,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGestureRecognitionComponent_Statics::NewProp_HandLandmarkModelPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGestureRecognitionComponent_Statics::NewProp_ProcessingInterval,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGestureRecognitionComponent_Statics::NewProp_HandLandmarkModel,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGestureRecognitionComponent_Statics::NewProp_GestureClassifier,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGestureRecognitionComponent_Statics::PropPointers) < 2048);
// ********** End Class UGestureRecognitionComponent Property Definitions **************************
UObject* (*const Z_Construct_UClass_UGestureRecognitionComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UNPCSubsystemComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGestureRecognitionComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGestureRecognitionComponent_Statics::ClassParams = {
	&UGestureRecognitionComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UGestureRecognitionComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UGestureRecognitionComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGestureRecognitionComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UGestureRecognitionComponent_Statics::Class_MetaDataParams)
};
void UGestureRecognitionComponent::StaticRegisterNativesUGestureRecognitionComponent()
{
	UClass* Class = UGestureRecognitionComponent::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UGestureRecognitionComponent_Statics::Funcs));
}
UClass* Z_Construct_UClass_UGestureRecognitionComponent()
{
	if (!Z_Registration_Info_UClass_UGestureRecognitionComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGestureRecognitionComponent.OuterSingleton, Z_Construct_UClass_UGestureRecognitionComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGestureRecognitionComponent.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UGestureRecognitionComponent);
UGestureRecognitionComponent::~UGestureRecognitionComponent() {}
// ********** End Class UGestureRecognitionComponent ***********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_GestureRecognitionComponent_h__Script_LLM_NPC_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGestureRecognitionComponent, UGestureRecognitionComponent::StaticClass, TEXT("UGestureRecognitionComponent"), &Z_Registration_Info_UClass_UGestureRecognitionComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGestureRecognitionComponent), 2568988018U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_GestureRecognitionComponent_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_GestureRecognitionComponent_h__Script_LLM_NPC_4264663749{
	TEXT("/Script/LLM_NPC"),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_GestureRecognitionComponent_h__Script_LLM_NPC_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_GestureRecognitionComponent_h__Script_LLM_NPC_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
