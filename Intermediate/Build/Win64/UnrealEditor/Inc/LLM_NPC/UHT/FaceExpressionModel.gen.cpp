// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Vision/FaceExpressionModel.h"
#include "LLM_NPC/Core/NPCTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeFaceExpressionModel() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
LLM_NPC_API UClass* Z_Construct_UClass_UFaceExpressionModel();
LLM_NPC_API UClass* Z_Construct_UClass_UFaceExpressionModel_NoRegister();
LLM_NPC_API UScriptStruct* Z_Construct_UScriptStruct_FDetectedUserEmotion();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UFaceExpressionModel Function Classify ***********************************
struct Z_Construct_UFunction_UFaceExpressionModel_Classify_Statics
{
	struct FaceExpressionModel_eventClassify_Parms
	{
		TArray<uint8> FaceROI;
		int32 Width;
		int32 Height;
		FDetectedUserEmotion ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Vision" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Classify the emotion in a cropped face region of interest.\n\x09 * @param FaceROI  Raw pixel data (BGR) of the cropped face.\n\x09 * @param Width    Width of the face ROI in pixels.\n\x09 * @param Height   Height of the face ROI in pixels.\n\x09 * @return Detected emotion with confidence and probability map.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Vision/FaceExpressionModel.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Classify the emotion in a cropped face region of interest.\n@param FaceROI  Raw pixel data (BGR) of the cropped face.\n@param Width    Width of the face ROI in pixels.\n@param Height   Height of the face ROI in pixels.\n@return Detected emotion with confidence and probability map." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FaceROI_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function Classify constinit property declarations ******************************
	static const UECodeGen_Private::FBytePropertyParams NewProp_FaceROI_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_FaceROI;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Width;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Height;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function Classify constinit property declarations ********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function Classify Property Definitions *****************************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UFaceExpressionModel_Classify_Statics::NewProp_FaceROI_Inner = { "FaceROI", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UFaceExpressionModel_Classify_Statics::NewProp_FaceROI = { "FaceROI", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FaceExpressionModel_eventClassify_Parms, FaceROI), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FaceROI_MetaData), NewProp_FaceROI_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UFaceExpressionModel_Classify_Statics::NewProp_Width = { "Width", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FaceExpressionModel_eventClassify_Parms, Width), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UFaceExpressionModel_Classify_Statics::NewProp_Height = { "Height", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FaceExpressionModel_eventClassify_Parms, Height), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFaceExpressionModel_Classify_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FaceExpressionModel_eventClassify_Parms, ReturnValue), Z_Construct_UScriptStruct_FDetectedUserEmotion, METADATA_PARAMS(0, nullptr) }; // 3137125811
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFaceExpressionModel_Classify_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFaceExpressionModel_Classify_Statics::NewProp_FaceROI_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFaceExpressionModel_Classify_Statics::NewProp_FaceROI,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFaceExpressionModel_Classify_Statics::NewProp_Width,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFaceExpressionModel_Classify_Statics::NewProp_Height,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFaceExpressionModel_Classify_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UFaceExpressionModel_Classify_Statics::PropPointers) < 2048);
// ********** End Function Classify Property Definitions *******************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFaceExpressionModel_Classify_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UFaceExpressionModel, nullptr, "Classify", 	Z_Construct_UFunction_UFaceExpressionModel_Classify_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UFaceExpressionModel_Classify_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UFaceExpressionModel_Classify_Statics::FaceExpressionModel_eventClassify_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UFaceExpressionModel_Classify_Statics::Function_MetaDataParams), Z_Construct_UFunction_UFaceExpressionModel_Classify_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UFaceExpressionModel_Classify_Statics::FaceExpressionModel_eventClassify_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UFaceExpressionModel_Classify()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFaceExpressionModel_Classify_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UFaceExpressionModel::execClassify)
{
	P_GET_TARRAY_REF(uint8,Z_Param_Out_FaceROI);
	P_GET_PROPERTY(FIntProperty,Z_Param_Width);
	P_GET_PROPERTY(FIntProperty,Z_Param_Height);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FDetectedUserEmotion*)Z_Param__Result=P_THIS->Classify(Z_Param_Out_FaceROI,Z_Param_Width,Z_Param_Height);
	P_NATIVE_END;
}
// ********** End Class UFaceExpressionModel Function Classify *************************************

// ********** Begin Class UFaceExpressionModel Function IsModelLoaded ******************************
struct Z_Construct_UFunction_UFaceExpressionModel_IsModelLoaded_Statics
{
	struct FaceExpressionModel_eventIsModelLoaded_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Vision" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Whether a model has been loaded. */" },
#endif
		{ "ModuleRelativePath", "Vision/FaceExpressionModel.h" },
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
void Z_Construct_UFunction_UFaceExpressionModel_IsModelLoaded_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((FaceExpressionModel_eventIsModelLoaded_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFaceExpressionModel_IsModelLoaded_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FaceExpressionModel_eventIsModelLoaded_Parms), &Z_Construct_UFunction_UFaceExpressionModel_IsModelLoaded_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFaceExpressionModel_IsModelLoaded_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFaceExpressionModel_IsModelLoaded_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UFaceExpressionModel_IsModelLoaded_Statics::PropPointers) < 2048);
// ********** End Function IsModelLoaded Property Definitions **************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFaceExpressionModel_IsModelLoaded_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UFaceExpressionModel, nullptr, "IsModelLoaded", 	Z_Construct_UFunction_UFaceExpressionModel_IsModelLoaded_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UFaceExpressionModel_IsModelLoaded_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UFaceExpressionModel_IsModelLoaded_Statics::FaceExpressionModel_eventIsModelLoaded_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UFaceExpressionModel_IsModelLoaded_Statics::Function_MetaDataParams), Z_Construct_UFunction_UFaceExpressionModel_IsModelLoaded_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UFaceExpressionModel_IsModelLoaded_Statics::FaceExpressionModel_eventIsModelLoaded_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UFaceExpressionModel_IsModelLoaded()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFaceExpressionModel_IsModelLoaded_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UFaceExpressionModel::execIsModelLoaded)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsModelLoaded();
	P_NATIVE_END;
}
// ********** End Class UFaceExpressionModel Function IsModelLoaded ********************************

// ********** Begin Class UFaceExpressionModel Function LoadModel **********************************
struct Z_Construct_UFunction_UFaceExpressionModel_LoadModel_Statics
{
	struct FaceExpressionModel_eventLoadModel_Parms
	{
		FString ModelPath;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Vision" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Load the ONNX model from disk.\n\x09 * @param ModelPath  Absolute or project-relative path to the .onnx file.\n\x09 * @return true if the model was loaded successfully.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Vision/FaceExpressionModel.h" },
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
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UFaceExpressionModel_LoadModel_Statics::NewProp_ModelPath = { "ModelPath", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FaceExpressionModel_eventLoadModel_Parms, ModelPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ModelPath_MetaData), NewProp_ModelPath_MetaData) };
void Z_Construct_UFunction_UFaceExpressionModel_LoadModel_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((FaceExpressionModel_eventLoadModel_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFaceExpressionModel_LoadModel_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FaceExpressionModel_eventLoadModel_Parms), &Z_Construct_UFunction_UFaceExpressionModel_LoadModel_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFaceExpressionModel_LoadModel_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFaceExpressionModel_LoadModel_Statics::NewProp_ModelPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFaceExpressionModel_LoadModel_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UFaceExpressionModel_LoadModel_Statics::PropPointers) < 2048);
// ********** End Function LoadModel Property Definitions ******************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFaceExpressionModel_LoadModel_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UFaceExpressionModel, nullptr, "LoadModel", 	Z_Construct_UFunction_UFaceExpressionModel_LoadModel_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UFaceExpressionModel_LoadModel_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UFaceExpressionModel_LoadModel_Statics::FaceExpressionModel_eventLoadModel_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UFaceExpressionModel_LoadModel_Statics::Function_MetaDataParams), Z_Construct_UFunction_UFaceExpressionModel_LoadModel_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UFaceExpressionModel_LoadModel_Statics::FaceExpressionModel_eventLoadModel_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UFaceExpressionModel_LoadModel()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFaceExpressionModel_LoadModel_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UFaceExpressionModel::execLoadModel)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_ModelPath);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->LoadModel(Z_Param_ModelPath);
	P_NATIVE_END;
}
// ********** End Class UFaceExpressionModel Function LoadModel ************************************

// ********** Begin Class UFaceExpressionModel *****************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UFaceExpressionModel;
UClass* UFaceExpressionModel::GetPrivateStaticClass()
{
	using TClass = UFaceExpressionModel;
	if (!Z_Registration_Info_UClass_UFaceExpressionModel.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("FaceExpressionModel"),
			Z_Registration_Info_UClass_UFaceExpressionModel.InnerSingleton,
			StaticRegisterNativesUFaceExpressionModel,
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
	return Z_Registration_Info_UClass_UFaceExpressionModel.InnerSingleton;
}
UClass* Z_Construct_UClass_UFaceExpressionModel_NoRegister()
{
	return UFaceExpressionModel::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UFaceExpressionModel_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Wraps ONNX Runtime inference for facial expression classification.\n * Uses trpakov/vit-face-expression (ViT-base) model from HuggingFace.\n * Preprocesses face ROI to 224x224 RGB and runs a 7-class emotion model.\n * Temporal smoothing via exponential moving average prevents noisy flickering.\n * A new dominant emotion is only reported after persisting for 0.5 seconds.\n */" },
#endif
		{ "IncludePath", "Vision/FaceExpressionModel.h" },
		{ "ModuleRelativePath", "Vision/FaceExpressionModel.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Wraps ONNX Runtime inference for facial expression classification.\nUses trpakov/vit-face-expression (ViT-base) model from HuggingFace.\nPreprocesses face ROI to 224x224 RGB and runs a 7-class emotion model.\nTemporal smoothing via exponential moving average prevents noisy flickering.\nA new dominant emotion is only reported after persisting for 0.5 seconds." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UFaceExpressionModel constinit property declarations *********************
// ********** End Class UFaceExpressionModel constinit property declarations ***********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("Classify"), .Pointer = &UFaceExpressionModel::execClassify },
		{ .NameUTF8 = UTF8TEXT("IsModelLoaded"), .Pointer = &UFaceExpressionModel::execIsModelLoaded },
		{ .NameUTF8 = UTF8TEXT("LoadModel"), .Pointer = &UFaceExpressionModel::execLoadModel },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UFaceExpressionModel_Classify, "Classify" }, // 1492260839
		{ &Z_Construct_UFunction_UFaceExpressionModel_IsModelLoaded, "IsModelLoaded" }, // 836202988
		{ &Z_Construct_UFunction_UFaceExpressionModel_LoadModel, "LoadModel" }, // 691384028
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFaceExpressionModel>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UFaceExpressionModel_Statics
UObject* (*const Z_Construct_UClass_UFaceExpressionModel_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UFaceExpressionModel_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UFaceExpressionModel_Statics::ClassParams = {
	&UFaceExpressionModel::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UFaceExpressionModel_Statics::Class_MetaDataParams), Z_Construct_UClass_UFaceExpressionModel_Statics::Class_MetaDataParams)
};
void UFaceExpressionModel::StaticRegisterNativesUFaceExpressionModel()
{
	UClass* Class = UFaceExpressionModel::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UFaceExpressionModel_Statics::Funcs));
}
UClass* Z_Construct_UClass_UFaceExpressionModel()
{
	if (!Z_Registration_Info_UClass_UFaceExpressionModel.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UFaceExpressionModel.OuterSingleton, Z_Construct_UClass_UFaceExpressionModel_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UFaceExpressionModel.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UFaceExpressionModel);
UFaceExpressionModel::~UFaceExpressionModel() {}
// ********** End Class UFaceExpressionModel *******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_FaceExpressionModel_h__Script_LLM_NPC_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UFaceExpressionModel, UFaceExpressionModel::StaticClass, TEXT("UFaceExpressionModel"), &Z_Registration_Info_UClass_UFaceExpressionModel, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UFaceExpressionModel), 1832557466U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_FaceExpressionModel_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_FaceExpressionModel_h__Script_LLM_NPC_3044955018{
	TEXT("/Script/LLM_NPC"),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_FaceExpressionModel_h__Script_LLM_NPC_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_FaceExpressionModel_h__Script_LLM_NPC_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
