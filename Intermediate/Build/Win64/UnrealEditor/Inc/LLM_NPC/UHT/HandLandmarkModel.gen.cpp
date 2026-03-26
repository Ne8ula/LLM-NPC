// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Gesture/HandLandmarkModel.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeHandLandmarkModel() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector2D();
LLM_NPC_API UClass* Z_Construct_UClass_UHandLandmarkModel();
LLM_NPC_API UClass* Z_Construct_UClass_UHandLandmarkModel_NoRegister();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UHandLandmarkModel Function DetectHandLandmarks **************************
struct Z_Construct_UFunction_UHandLandmarkModel_DetectHandLandmarks_Statics
{
	struct HandLandmarkModel_eventDetectHandLandmarks_Parms
	{
		TArray<uint8> FrameData;
		int32 Width;
		int32 Height;
		TArray<FVector2D> OutLandmarks;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Gesture" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Detect 21 hand landmarks in the given frame.\n\x09 * @param FrameData     Raw BGR pixel data.\n\x09 * @param Width         Frame width in pixels.\n\x09 * @param Height        Frame height in pixels.\n\x09 * @param OutLandmarks  Output array of 21 normalized (0-1) 2D coordinates.\n\x09 * @return true if a hand was detected with landmarks.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Gesture/HandLandmarkModel.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Detect 21 hand landmarks in the given frame.\n@param FrameData     Raw BGR pixel data.\n@param Width         Frame width in pixels.\n@param Height        Frame height in pixels.\n@param OutLandmarks  Output array of 21 normalized (0-1) 2D coordinates.\n@return true if a hand was detected with landmarks." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FrameData_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function DetectHandLandmarks constinit property declarations *******************
	static const UECodeGen_Private::FBytePropertyParams NewProp_FrameData_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_FrameData;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Width;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Height;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OutLandmarks_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_OutLandmarks;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function DetectHandLandmarks constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function DetectHandLandmarks Property Definitions ******************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UHandLandmarkModel_DetectHandLandmarks_Statics::NewProp_FrameData_Inner = { "FrameData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UHandLandmarkModel_DetectHandLandmarks_Statics::NewProp_FrameData = { "FrameData", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HandLandmarkModel_eventDetectHandLandmarks_Parms, FrameData), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FrameData_MetaData), NewProp_FrameData_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UHandLandmarkModel_DetectHandLandmarks_Statics::NewProp_Width = { "Width", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HandLandmarkModel_eventDetectHandLandmarks_Parms, Width), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UHandLandmarkModel_DetectHandLandmarks_Statics::NewProp_Height = { "Height", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HandLandmarkModel_eventDetectHandLandmarks_Parms, Height), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UHandLandmarkModel_DetectHandLandmarks_Statics::NewProp_OutLandmarks_Inner = { "OutLandmarks", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UHandLandmarkModel_DetectHandLandmarks_Statics::NewProp_OutLandmarks = { "OutLandmarks", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HandLandmarkModel_eventDetectHandLandmarks_Parms, OutLandmarks), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UHandLandmarkModel_DetectHandLandmarks_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((HandLandmarkModel_eventDetectHandLandmarks_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UHandLandmarkModel_DetectHandLandmarks_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(HandLandmarkModel_eventDetectHandLandmarks_Parms), &Z_Construct_UFunction_UHandLandmarkModel_DetectHandLandmarks_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHandLandmarkModel_DetectHandLandmarks_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHandLandmarkModel_DetectHandLandmarks_Statics::NewProp_FrameData_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHandLandmarkModel_DetectHandLandmarks_Statics::NewProp_FrameData,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHandLandmarkModel_DetectHandLandmarks_Statics::NewProp_Width,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHandLandmarkModel_DetectHandLandmarks_Statics::NewProp_Height,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHandLandmarkModel_DetectHandLandmarks_Statics::NewProp_OutLandmarks_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHandLandmarkModel_DetectHandLandmarks_Statics::NewProp_OutLandmarks,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHandLandmarkModel_DetectHandLandmarks_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UHandLandmarkModel_DetectHandLandmarks_Statics::PropPointers) < 2048);
// ********** End Function DetectHandLandmarks Property Definitions ********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHandLandmarkModel_DetectHandLandmarks_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UHandLandmarkModel, nullptr, "DetectHandLandmarks", 	Z_Construct_UFunction_UHandLandmarkModel_DetectHandLandmarks_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UHandLandmarkModel_DetectHandLandmarks_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UHandLandmarkModel_DetectHandLandmarks_Statics::HandLandmarkModel_eventDetectHandLandmarks_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHandLandmarkModel_DetectHandLandmarks_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHandLandmarkModel_DetectHandLandmarks_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UHandLandmarkModel_DetectHandLandmarks_Statics::HandLandmarkModel_eventDetectHandLandmarks_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UHandLandmarkModel_DetectHandLandmarks()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHandLandmarkModel_DetectHandLandmarks_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UHandLandmarkModel::execDetectHandLandmarks)
{
	P_GET_TARRAY_REF(uint8,Z_Param_Out_FrameData);
	P_GET_PROPERTY(FIntProperty,Z_Param_Width);
	P_GET_PROPERTY(FIntProperty,Z_Param_Height);
	P_GET_TARRAY_REF(FVector2D,Z_Param_Out_OutLandmarks);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->DetectHandLandmarks(Z_Param_Out_FrameData,Z_Param_Width,Z_Param_Height,Z_Param_Out_OutLandmarks);
	P_NATIVE_END;
}
// ********** End Class UHandLandmarkModel Function DetectHandLandmarks ****************************

// ********** Begin Class UHandLandmarkModel Function IsModelLoaded ********************************
struct Z_Construct_UFunction_UHandLandmarkModel_IsModelLoaded_Statics
{
	struct HandLandmarkModel_eventIsModelLoaded_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Gesture" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Whether a model has been loaded. */" },
#endif
		{ "ModuleRelativePath", "Gesture/HandLandmarkModel.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Whether a model has been loaded." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function IsModelLoaded constinit property declarations *************************
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsModelLoaded constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsModelLoaded Property Definitions ************************************
void Z_Construct_UFunction_UHandLandmarkModel_IsModelLoaded_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((HandLandmarkModel_eventIsModelLoaded_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UHandLandmarkModel_IsModelLoaded_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(HandLandmarkModel_eventIsModelLoaded_Parms), &Z_Construct_UFunction_UHandLandmarkModel_IsModelLoaded_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHandLandmarkModel_IsModelLoaded_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHandLandmarkModel_IsModelLoaded_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UHandLandmarkModel_IsModelLoaded_Statics::PropPointers) < 2048);
// ********** End Function IsModelLoaded Property Definitions **************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHandLandmarkModel_IsModelLoaded_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UHandLandmarkModel, nullptr, "IsModelLoaded", 	Z_Construct_UFunction_UHandLandmarkModel_IsModelLoaded_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UHandLandmarkModel_IsModelLoaded_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UHandLandmarkModel_IsModelLoaded_Statics::HandLandmarkModel_eventIsModelLoaded_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHandLandmarkModel_IsModelLoaded_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHandLandmarkModel_IsModelLoaded_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UHandLandmarkModel_IsModelLoaded_Statics::HandLandmarkModel_eventIsModelLoaded_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UHandLandmarkModel_IsModelLoaded()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHandLandmarkModel_IsModelLoaded_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UHandLandmarkModel::execIsModelLoaded)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsModelLoaded();
	P_NATIVE_END;
}
// ********** End Class UHandLandmarkModel Function IsModelLoaded **********************************

// ********** Begin Class UHandLandmarkModel Function LoadModel ************************************
struct Z_Construct_UFunction_UHandLandmarkModel_LoadModel_Statics
{
	struct HandLandmarkModel_eventLoadModel_Parms
	{
		FString ModelPath;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Gesture" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Load the ONNX model from disk.\n\x09 * @param ModelPath  Absolute or project-relative path to the .onnx file.\n\x09 * @return true if the model was loaded successfully.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Gesture/HandLandmarkModel.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Load the ONNX model from disk.\n@param ModelPath  Absolute or project-relative path to the .onnx file.\n@return true if the model was loaded successfully." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ModelPath_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function LoadModel constinit property declarations *****************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_ModelPath;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function LoadModel constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function LoadModel Property Definitions ****************************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UHandLandmarkModel_LoadModel_Statics::NewProp_ModelPath = { "ModelPath", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HandLandmarkModel_eventLoadModel_Parms, ModelPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ModelPath_MetaData), NewProp_ModelPath_MetaData) };
void Z_Construct_UFunction_UHandLandmarkModel_LoadModel_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((HandLandmarkModel_eventLoadModel_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UHandLandmarkModel_LoadModel_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(HandLandmarkModel_eventLoadModel_Parms), &Z_Construct_UFunction_UHandLandmarkModel_LoadModel_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHandLandmarkModel_LoadModel_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHandLandmarkModel_LoadModel_Statics::NewProp_ModelPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHandLandmarkModel_LoadModel_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UHandLandmarkModel_LoadModel_Statics::PropPointers) < 2048);
// ********** End Function LoadModel Property Definitions ******************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHandLandmarkModel_LoadModel_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UHandLandmarkModel, nullptr, "LoadModel", 	Z_Construct_UFunction_UHandLandmarkModel_LoadModel_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UHandLandmarkModel_LoadModel_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UHandLandmarkModel_LoadModel_Statics::HandLandmarkModel_eventLoadModel_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHandLandmarkModel_LoadModel_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHandLandmarkModel_LoadModel_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UHandLandmarkModel_LoadModel_Statics::HandLandmarkModel_eventLoadModel_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UHandLandmarkModel_LoadModel()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHandLandmarkModel_LoadModel_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UHandLandmarkModel::execLoadModel)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_ModelPath);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->LoadModel(Z_Param_ModelPath);
	P_NATIVE_END;
}
// ********** End Class UHandLandmarkModel Function LoadModel **************************************

// ********** Begin Class UHandLandmarkModel *******************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UHandLandmarkModel;
UClass* UHandLandmarkModel::GetPrivateStaticClass()
{
	using TClass = UHandLandmarkModel;
	if (!Z_Registration_Info_UClass_UHandLandmarkModel.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("HandLandmarkModel"),
			Z_Registration_Info_UClass_UHandLandmarkModel.InnerSingleton,
			StaticRegisterNativesUHandLandmarkModel,
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
	return Z_Registration_Info_UClass_UHandLandmarkModel.InnerSingleton;
}
UClass* Z_Construct_UClass_UHandLandmarkModel_NoRegister()
{
	return UHandLandmarkModel::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UHandLandmarkModel_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * ONNX-based hand landmark detection model (MediaPipe-style).\n * Detects 21 hand landmarks and returns them as normalized (0-1) x,y coordinates.\n */" },
#endif
		{ "IncludePath", "Gesture/HandLandmarkModel.h" },
		{ "ModuleRelativePath", "Gesture/HandLandmarkModel.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "ONNX-based hand landmark detection model (MediaPipe-style).\nDetects 21 hand landmarks and returns them as normalized (0-1) x,y coordinates." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UHandLandmarkModel constinit property declarations ***********************
// ********** End Class UHandLandmarkModel constinit property declarations *************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("DetectHandLandmarks"), .Pointer = &UHandLandmarkModel::execDetectHandLandmarks },
		{ .NameUTF8 = UTF8TEXT("IsModelLoaded"), .Pointer = &UHandLandmarkModel::execIsModelLoaded },
		{ .NameUTF8 = UTF8TEXT("LoadModel"), .Pointer = &UHandLandmarkModel::execLoadModel },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UHandLandmarkModel_DetectHandLandmarks, "DetectHandLandmarks" }, // 2842843301
		{ &Z_Construct_UFunction_UHandLandmarkModel_IsModelLoaded, "IsModelLoaded" }, // 3477299612
		{ &Z_Construct_UFunction_UHandLandmarkModel_LoadModel, "LoadModel" }, // 2773226190
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UHandLandmarkModel>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UHandLandmarkModel_Statics
UObject* (*const Z_Construct_UClass_UHandLandmarkModel_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UHandLandmarkModel_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UHandLandmarkModel_Statics::ClassParams = {
	&UHandLandmarkModel::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UHandLandmarkModel_Statics::Class_MetaDataParams), Z_Construct_UClass_UHandLandmarkModel_Statics::Class_MetaDataParams)
};
void UHandLandmarkModel::StaticRegisterNativesUHandLandmarkModel()
{
	UClass* Class = UHandLandmarkModel::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UHandLandmarkModel_Statics::Funcs));
}
UClass* Z_Construct_UClass_UHandLandmarkModel()
{
	if (!Z_Registration_Info_UClass_UHandLandmarkModel.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UHandLandmarkModel.OuterSingleton, Z_Construct_UClass_UHandLandmarkModel_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UHandLandmarkModel.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UHandLandmarkModel);
// ********** End Class UHandLandmarkModel *********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_HandLandmarkModel_h__Script_LLM_NPC_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UHandLandmarkModel, UHandLandmarkModel::StaticClass, TEXT("UHandLandmarkModel"), &Z_Registration_Info_UClass_UHandLandmarkModel, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UHandLandmarkModel), 865383588U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_HandLandmarkModel_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_HandLandmarkModel_h__Script_LLM_NPC_147987935{
	TEXT("/Script/LLM_NPC"),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_HandLandmarkModel_h__Script_LLM_NPC_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_HandLandmarkModel_h__Script_LLM_NPC_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
