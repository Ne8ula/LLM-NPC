// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Vision/FacialRecognitionComponent.h"
#include "LLM_NPC/Core/NPCTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeFacialRecognitionComponent() {}

// ********** Begin Cross Module References ********************************************************
LLM_NPC_API UClass* Z_Construct_UClass_UFaceExpressionModel_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UFacialRecognitionComponent();
LLM_NPC_API UClass* Z_Construct_UClass_UFacialRecognitionComponent_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UNPCSubsystemComponent();
LLM_NPC_API UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnUserEmotionDetected__DelegateSignature();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FDetectedUserEmotion();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FOnUserEmotionDetected ************************************************
struct Z_Construct_UDelegateFunction_LLM_NPC_OnUserEmotionDetected__DelegateSignature_Statics
{
	struct _Script_LLM_NPC_eventOnUserEmotionDetected_Parms
	{
		FDetectedUserEmotion DetectedEmotion;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Vision/FacialRecognitionComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnUserEmotionDetected constinit property declarations ****************
	static const UECodeGen_Private::FStructPropertyParams NewProp_DetectedEmotion;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FOnUserEmotionDetected constinit property declarations ******************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FOnUserEmotionDetected Property Definitions ***************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_LLM_NPC_OnUserEmotionDetected__DelegateSignature_Statics::NewProp_DetectedEmotion = { "DetectedEmotion", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_LLM_NPC_eventOnUserEmotionDetected_Parms, DetectedEmotion), Z_Construct_UScriptStruct_FDetectedUserEmotion, METADATA_PARAMS(0, nullptr) }; // 3137125811
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_LLM_NPC_OnUserEmotionDetected__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LLM_NPC_OnUserEmotionDetected__DelegateSignature_Statics::NewProp_DetectedEmotion,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnUserEmotionDetected__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FOnUserEmotionDetected Property Definitions *****************************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_LLM_NPC_OnUserEmotionDetected__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_LLM_NPC, nullptr, "OnUserEmotionDetected__DelegateSignature", 	Z_Construct_UDelegateFunction_LLM_NPC_OnUserEmotionDetected__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnUserEmotionDetected__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_LLM_NPC_OnUserEmotionDetected__DelegateSignature_Statics::_Script_LLM_NPC_eventOnUserEmotionDetected_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LLM_NPC_OnUserEmotionDetected__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_LLM_NPC_OnUserEmotionDetected__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_LLM_NPC_OnUserEmotionDetected__DelegateSignature_Statics::_Script_LLM_NPC_eventOnUserEmotionDetected_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_LLM_NPC_OnUserEmotionDetected__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_LLM_NPC_OnUserEmotionDetected__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnUserEmotionDetected_DelegateWrapper(const FMulticastScriptDelegate& OnUserEmotionDetected, FDetectedUserEmotion DetectedEmotion)
{
	struct _Script_LLM_NPC_eventOnUserEmotionDetected_Parms
	{
		FDetectedUserEmotion DetectedEmotion;
	};
	_Script_LLM_NPC_eventOnUserEmotionDetected_Parms Parms;
	Parms.DetectedEmotion=DetectedEmotion;
	OnUserEmotionDetected.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnUserEmotionDetected **************************************************

// ********** Begin Class UFacialRecognitionComponent **********************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UFacialRecognitionComponent;
UClass* UFacialRecognitionComponent::GetPrivateStaticClass()
{
	using TClass = UFacialRecognitionComponent;
	if (!Z_Registration_Info_UClass_UFacialRecognitionComponent.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("FacialRecognitionComponent"),
			Z_Registration_Info_UClass_UFacialRecognitionComponent.InnerSingleton,
			StaticRegisterNativesUFacialRecognitionComponent,
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
	return Z_Registration_Info_UClass_UFacialRecognitionComponent.InnerSingleton;
}
UClass* Z_Construct_UClass_UFacialRecognitionComponent_NoRegister()
{
	return UFacialRecognitionComponent::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UFacialRecognitionComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "LLMNPC" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * NPC subsystem component that reads camera frames, detects faces via\n * OpenCV DNN, and classifies facial expressions through an ONNX model.\n * Processes at ~10 FPS using a timer (not tick-based) to avoid overloading\n * the game thread.\n */" },
#endif
		{ "IncludePath", "Vision/FacialRecognitionComponent.h" },
		{ "ModuleRelativePath", "Vision/FacialRecognitionComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "NPC subsystem component that reads camera frames, detects faces via\nOpenCV DNN, and classifies facial expressions through an ONNX model.\nProcesses at ~10 FPS using a timer (not tick-based) to avoid overloading\nthe game thread." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnUserEmotionDetected_MetaData[] = {
		{ "Category", "NPC|Vision" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Fired when a user emotion is detected from the camera feed. */" },
#endif
		{ "ModuleRelativePath", "Vision/FacialRecognitionComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Fired when a user emotion is detected from the camera feed." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ExpressionModelPath_MetaData[] = {
		{ "Category", "NPC|Vision" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Path to the facial expression ONNX model. */" },
#endif
		{ "ModuleRelativePath", "Vision/FacialRecognitionComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Path to the facial expression ONNX model." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FaceDetectionModelPath_MetaData[] = {
		{ "Category", "NPC|Vision" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Path to the OpenCV DNN face detection model (Caffe or TensorFlow). */" },
#endif
		{ "ModuleRelativePath", "Vision/FacialRecognitionComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Path to the OpenCV DNN face detection model (Caffe or TensorFlow)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FaceDetectionConfigPath_MetaData[] = {
		{ "Category", "NPC|Vision" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Path to the face detection model config (prototxt). */" },
#endif
		{ "ModuleRelativePath", "Vision/FacialRecognitionComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Path to the face detection model config (prototxt)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FaceDetectionConfidence_MetaData[] = {
		{ "Category", "NPC|Vision" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Minimum confidence threshold for face detection. */" },
#endif
		{ "ModuleRelativePath", "Vision/FacialRecognitionComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Minimum confidence threshold for face detection." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProcessingInterval_MetaData[] = {
		{ "Category", "NPC|Vision" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.016" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Processing rate in seconds (default ~10 FPS = 0.1s interval). */" },
#endif
		{ "ModuleRelativePath", "Vision/FacialRecognitionComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Processing rate in seconds (default ~10 FPS = 0.1s interval)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ExpressionModel_MetaData[] = {
		{ "ModuleRelativePath", "Vision/FacialRecognitionComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UFacialRecognitionComponent constinit property declarations **************
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnUserEmotionDetected;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ExpressionModelPath;
	static const UECodeGen_Private::FStrPropertyParams NewProp_FaceDetectionModelPath;
	static const UECodeGen_Private::FStrPropertyParams NewProp_FaceDetectionConfigPath;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FaceDetectionConfidence;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ProcessingInterval;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ExpressionModel;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UFacialRecognitionComponent constinit property declarations ****************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFacialRecognitionComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UFacialRecognitionComponent_Statics

// ********** Begin Class UFacialRecognitionComponent Property Definitions *************************
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UFacialRecognitionComponent_Statics::NewProp_OnUserEmotionDetected = { "OnUserEmotionDetected", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UFacialRecognitionComponent, OnUserEmotionDetected), Z_Construct_UDelegateFunction_LLM_NPC_OnUserEmotionDetected__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnUserEmotionDetected_MetaData), NewProp_OnUserEmotionDetected_MetaData) }; // 3142127288
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UFacialRecognitionComponent_Statics::NewProp_ExpressionModelPath = { "ExpressionModelPath", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UFacialRecognitionComponent, ExpressionModelPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ExpressionModelPath_MetaData), NewProp_ExpressionModelPath_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UFacialRecognitionComponent_Statics::NewProp_FaceDetectionModelPath = { "FaceDetectionModelPath", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UFacialRecognitionComponent, FaceDetectionModelPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FaceDetectionModelPath_MetaData), NewProp_FaceDetectionModelPath_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UFacialRecognitionComponent_Statics::NewProp_FaceDetectionConfigPath = { "FaceDetectionConfigPath", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UFacialRecognitionComponent, FaceDetectionConfigPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FaceDetectionConfigPath_MetaData), NewProp_FaceDetectionConfigPath_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UFacialRecognitionComponent_Statics::NewProp_FaceDetectionConfidence = { "FaceDetectionConfidence", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UFacialRecognitionComponent, FaceDetectionConfidence), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FaceDetectionConfidence_MetaData), NewProp_FaceDetectionConfidence_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UFacialRecognitionComponent_Statics::NewProp_ProcessingInterval = { "ProcessingInterval", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UFacialRecognitionComponent, ProcessingInterval), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProcessingInterval_MetaData), NewProp_ProcessingInterval_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UFacialRecognitionComponent_Statics::NewProp_ExpressionModel = { "ExpressionModel", nullptr, (EPropertyFlags)0x0144000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UFacialRecognitionComponent, ExpressionModel), Z_Construct_UClass_UFaceExpressionModel_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ExpressionModel_MetaData), NewProp_ExpressionModel_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UFacialRecognitionComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFacialRecognitionComponent_Statics::NewProp_OnUserEmotionDetected,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFacialRecognitionComponent_Statics::NewProp_ExpressionModelPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFacialRecognitionComponent_Statics::NewProp_FaceDetectionModelPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFacialRecognitionComponent_Statics::NewProp_FaceDetectionConfigPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFacialRecognitionComponent_Statics::NewProp_FaceDetectionConfidence,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFacialRecognitionComponent_Statics::NewProp_ProcessingInterval,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFacialRecognitionComponent_Statics::NewProp_ExpressionModel,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UFacialRecognitionComponent_Statics::PropPointers) < 2048);
// ********** End Class UFacialRecognitionComponent Property Definitions ***************************
UObject* (*const Z_Construct_UClass_UFacialRecognitionComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UNPCSubsystemComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UFacialRecognitionComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UFacialRecognitionComponent_Statics::ClassParams = {
	&UFacialRecognitionComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UFacialRecognitionComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UFacialRecognitionComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UFacialRecognitionComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UFacialRecognitionComponent_Statics::Class_MetaDataParams)
};
void UFacialRecognitionComponent::StaticRegisterNativesUFacialRecognitionComponent()
{
}
UClass* Z_Construct_UClass_UFacialRecognitionComponent()
{
	if (!Z_Registration_Info_UClass_UFacialRecognitionComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UFacialRecognitionComponent.OuterSingleton, Z_Construct_UClass_UFacialRecognitionComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UFacialRecognitionComponent.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UFacialRecognitionComponent);
UFacialRecognitionComponent::~UFacialRecognitionComponent() {}
// ********** End Class UFacialRecognitionComponent ************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_FacialRecognitionComponent_h__Script_LLM_NPC_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UFacialRecognitionComponent, UFacialRecognitionComponent::StaticClass, TEXT("UFacialRecognitionComponent"), &Z_Registration_Info_UClass_UFacialRecognitionComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UFacialRecognitionComponent), 2922434529U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_FacialRecognitionComponent_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_FacialRecognitionComponent_h__Script_LLM_NPC_3152459155{
	TEXT("/Script/LLM_NPC"),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_FacialRecognitionComponent_h__Script_LLM_NPC_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_FacialRecognitionComponent_h__Script_LLM_NPC_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
