// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Vision/CameraManagerSubsystem.h"
#include "Engine/GameInstance.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeCameraManagerSubsystem() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UGameInstanceSubsystem();
LLM_NPC_API UClass* Z_Construct_UClass_UCameraManagerSubsystem();
LLM_NPC_API UClass* Z_Construct_UClass_UCameraManagerSubsystem_NoRegister();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UCameraManagerSubsystem Function GetLatestFrame **************************
struct Z_Construct_UFunction_UCameraManagerSubsystem_GetLatestFrame_Statics
{
	struct CameraManagerSubsystem_eventGetLatestFrame_Parms
	{
		TArray<uint8> OutFrameData;
		int32 OutWidth;
		int32 OutHeight;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Vision" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Get the most recently captured frame (thread-safe read from double buffer).\n\x09 * @param OutFrameData  Raw BGR pixel data.\n\x09 * @param OutWidth      Frame width in pixels.\n\x09 * @param OutHeight     Frame height in pixels.\n\x09 * @return true if a valid frame was available.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Vision/CameraManagerSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get the most recently captured frame (thread-safe read from double buffer).\n@param OutFrameData  Raw BGR pixel data.\n@param OutWidth      Frame width in pixels.\n@param OutHeight     Frame height in pixels.\n@return true if a valid frame was available." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetLatestFrame constinit property declarations ************************
	static const UECodeGen_Private::FBytePropertyParams NewProp_OutFrameData_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_OutFrameData;
	static const UECodeGen_Private::FIntPropertyParams NewProp_OutWidth;
	static const UECodeGen_Private::FIntPropertyParams NewProp_OutHeight;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetLatestFrame constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetLatestFrame Property Definitions ***********************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UCameraManagerSubsystem_GetLatestFrame_Statics::NewProp_OutFrameData_Inner = { "OutFrameData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UCameraManagerSubsystem_GetLatestFrame_Statics::NewProp_OutFrameData = { "OutFrameData", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CameraManagerSubsystem_eventGetLatestFrame_Parms, OutFrameData), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UCameraManagerSubsystem_GetLatestFrame_Statics::NewProp_OutWidth = { "OutWidth", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CameraManagerSubsystem_eventGetLatestFrame_Parms, OutWidth), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UCameraManagerSubsystem_GetLatestFrame_Statics::NewProp_OutHeight = { "OutHeight", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CameraManagerSubsystem_eventGetLatestFrame_Parms, OutHeight), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UCameraManagerSubsystem_GetLatestFrame_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((CameraManagerSubsystem_eventGetLatestFrame_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UCameraManagerSubsystem_GetLatestFrame_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(CameraManagerSubsystem_eventGetLatestFrame_Parms), &Z_Construct_UFunction_UCameraManagerSubsystem_GetLatestFrame_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCameraManagerSubsystem_GetLatestFrame_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCameraManagerSubsystem_GetLatestFrame_Statics::NewProp_OutFrameData_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCameraManagerSubsystem_GetLatestFrame_Statics::NewProp_OutFrameData,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCameraManagerSubsystem_GetLatestFrame_Statics::NewProp_OutWidth,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCameraManagerSubsystem_GetLatestFrame_Statics::NewProp_OutHeight,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCameraManagerSubsystem_GetLatestFrame_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UCameraManagerSubsystem_GetLatestFrame_Statics::PropPointers) < 2048);
// ********** End Function GetLatestFrame Property Definitions *************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCameraManagerSubsystem_GetLatestFrame_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UCameraManagerSubsystem, nullptr, "GetLatestFrame", 	Z_Construct_UFunction_UCameraManagerSubsystem_GetLatestFrame_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UCameraManagerSubsystem_GetLatestFrame_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UCameraManagerSubsystem_GetLatestFrame_Statics::CameraManagerSubsystem_eventGetLatestFrame_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCameraManagerSubsystem_GetLatestFrame_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCameraManagerSubsystem_GetLatestFrame_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UCameraManagerSubsystem_GetLatestFrame_Statics::CameraManagerSubsystem_eventGetLatestFrame_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UCameraManagerSubsystem_GetLatestFrame()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCameraManagerSubsystem_GetLatestFrame_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UCameraManagerSubsystem::execGetLatestFrame)
{
	P_GET_TARRAY_REF(uint8,Z_Param_Out_OutFrameData);
	P_GET_PROPERTY_REF(FIntProperty,Z_Param_Out_OutWidth);
	P_GET_PROPERTY_REF(FIntProperty,Z_Param_Out_OutHeight);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->GetLatestFrame(Z_Param_Out_OutFrameData,Z_Param_Out_OutWidth,Z_Param_Out_OutHeight);
	P_NATIVE_END;
}
// ********** End Class UCameraManagerSubsystem Function GetLatestFrame ****************************

// ********** Begin Class UCameraManagerSubsystem Function IsCameraAvailable ***********************
struct Z_Construct_UFunction_UCameraManagerSubsystem_IsCameraAvailable_Statics
{
	struct CameraManagerSubsystem_eventIsCameraAvailable_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Vision" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Check if the camera is opened and actively capturing. */" },
#endif
		{ "ModuleRelativePath", "Vision/CameraManagerSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Check if the camera is opened and actively capturing." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function IsCameraAvailable constinit property declarations *********************
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsCameraAvailable constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsCameraAvailable Property Definitions ********************************
void Z_Construct_UFunction_UCameraManagerSubsystem_IsCameraAvailable_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((CameraManagerSubsystem_eventIsCameraAvailable_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UCameraManagerSubsystem_IsCameraAvailable_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(CameraManagerSubsystem_eventIsCameraAvailable_Parms), &Z_Construct_UFunction_UCameraManagerSubsystem_IsCameraAvailable_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCameraManagerSubsystem_IsCameraAvailable_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCameraManagerSubsystem_IsCameraAvailable_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UCameraManagerSubsystem_IsCameraAvailable_Statics::PropPointers) < 2048);
// ********** End Function IsCameraAvailable Property Definitions **********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCameraManagerSubsystem_IsCameraAvailable_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UCameraManagerSubsystem, nullptr, "IsCameraAvailable", 	Z_Construct_UFunction_UCameraManagerSubsystem_IsCameraAvailable_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UCameraManagerSubsystem_IsCameraAvailable_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UCameraManagerSubsystem_IsCameraAvailable_Statics::CameraManagerSubsystem_eventIsCameraAvailable_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCameraManagerSubsystem_IsCameraAvailable_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCameraManagerSubsystem_IsCameraAvailable_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UCameraManagerSubsystem_IsCameraAvailable_Statics::CameraManagerSubsystem_eventIsCameraAvailable_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UCameraManagerSubsystem_IsCameraAvailable()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCameraManagerSubsystem_IsCameraAvailable_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UCameraManagerSubsystem::execIsCameraAvailable)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsCameraAvailable();
	P_NATIVE_END;
}
// ********** End Class UCameraManagerSubsystem Function IsCameraAvailable *************************

// ********** Begin Class UCameraManagerSubsystem Function StartCapture ****************************
struct Z_Construct_UFunction_UCameraManagerSubsystem_StartCapture_Statics
{
	struct CameraManagerSubsystem_eventStartCapture_Parms
	{
		int32 CameraIndex;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Vision" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Start capturing from the given camera device index.\n\x09 * Spawns the background capture thread.\n\x09 * @param CameraIndex  OS camera device index (default 0).\n\x09 * @return true if the camera was opened successfully.\n\x09 */" },
#endif
		{ "CPP_Default_CameraIndex", "0" },
		{ "ModuleRelativePath", "Vision/CameraManagerSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Start capturing from the given camera device index.\nSpawns the background capture thread.\n@param CameraIndex  OS camera device index (default 0).\n@return true if the camera was opened successfully." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function StartCapture constinit property declarations **************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_CameraIndex;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function StartCapture constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function StartCapture Property Definitions *************************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UCameraManagerSubsystem_StartCapture_Statics::NewProp_CameraIndex = { "CameraIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CameraManagerSubsystem_eventStartCapture_Parms, CameraIndex), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UCameraManagerSubsystem_StartCapture_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((CameraManagerSubsystem_eventStartCapture_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UCameraManagerSubsystem_StartCapture_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(CameraManagerSubsystem_eventStartCapture_Parms), &Z_Construct_UFunction_UCameraManagerSubsystem_StartCapture_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCameraManagerSubsystem_StartCapture_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCameraManagerSubsystem_StartCapture_Statics::NewProp_CameraIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCameraManagerSubsystem_StartCapture_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UCameraManagerSubsystem_StartCapture_Statics::PropPointers) < 2048);
// ********** End Function StartCapture Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCameraManagerSubsystem_StartCapture_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UCameraManagerSubsystem, nullptr, "StartCapture", 	Z_Construct_UFunction_UCameraManagerSubsystem_StartCapture_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UCameraManagerSubsystem_StartCapture_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UCameraManagerSubsystem_StartCapture_Statics::CameraManagerSubsystem_eventStartCapture_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCameraManagerSubsystem_StartCapture_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCameraManagerSubsystem_StartCapture_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UCameraManagerSubsystem_StartCapture_Statics::CameraManagerSubsystem_eventStartCapture_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UCameraManagerSubsystem_StartCapture()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCameraManagerSubsystem_StartCapture_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UCameraManagerSubsystem::execStartCapture)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_CameraIndex);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->StartCapture(Z_Param_CameraIndex);
	P_NATIVE_END;
}
// ********** End Class UCameraManagerSubsystem Function StartCapture ******************************

// ********** Begin Class UCameraManagerSubsystem Function StopCapture *****************************
struct Z_Construct_UFunction_UCameraManagerSubsystem_StopCapture_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|Vision" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Stop capturing and release the camera device. */" },
#endif
		{ "ModuleRelativePath", "Vision/CameraManagerSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Stop capturing and release the camera device." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function StopCapture constinit property declarations ***************************
// ********** End Function StopCapture constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCameraManagerSubsystem_StopCapture_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UCameraManagerSubsystem, nullptr, "StopCapture", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCameraManagerSubsystem_StopCapture_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCameraManagerSubsystem_StopCapture_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UCameraManagerSubsystem_StopCapture()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCameraManagerSubsystem_StopCapture_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UCameraManagerSubsystem::execStopCapture)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->StopCapture();
	P_NATIVE_END;
}
// ********** End Class UCameraManagerSubsystem Function StopCapture *******************************

// ********** Begin Class UCameraManagerSubsystem **************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UCameraManagerSubsystem;
UClass* UCameraManagerSubsystem::GetPrivateStaticClass()
{
	using TClass = UCameraManagerSubsystem;
	if (!Z_Registration_Info_UClass_UCameraManagerSubsystem.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("CameraManagerSubsystem"),
			Z_Registration_Info_UClass_UCameraManagerSubsystem.InnerSingleton,
			StaticRegisterNativesUCameraManagerSubsystem,
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
	return Z_Registration_Info_UClass_UCameraManagerSubsystem.InnerSingleton;
}
UClass* Z_Construct_UClass_UCameraManagerSubsystem_NoRegister()
{
	return UCameraManagerSubsystem::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UCameraManagerSubsystem_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Shared camera manager subsystem providing double-buffered frame access.\n * A background FRunnable thread captures frames from OpenCV VideoCapture,\n * while reader threads (face tracking, hand tracking) read the latest frame\n * through a thread-safe interface.\n */" },
#endif
		{ "IncludePath", "Vision/CameraManagerSubsystem.h" },
		{ "ModuleRelativePath", "Vision/CameraManagerSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Shared camera manager subsystem providing double-buffered frame access.\nA background FRunnable thread captures frames from OpenCV VideoCapture,\nwhile reader threads (face tracking, hand tracking) read the latest frame\nthrough a thread-safe interface." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetFPS_MetaData[] = {
		{ "Category", "NPC|Vision" },
		{ "ClampMax", "60" },
		{ "ClampMin", "1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Target capture frame rate (default 15 FPS). */" },
#endif
		{ "ModuleRelativePath", "Vision/CameraManagerSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Target capture frame rate (default 15 FPS)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UCameraManagerSubsystem constinit property declarations ******************
	static const UECodeGen_Private::FIntPropertyParams NewProp_TargetFPS;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UCameraManagerSubsystem constinit property declarations ********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("GetLatestFrame"), .Pointer = &UCameraManagerSubsystem::execGetLatestFrame },
		{ .NameUTF8 = UTF8TEXT("IsCameraAvailable"), .Pointer = &UCameraManagerSubsystem::execIsCameraAvailable },
		{ .NameUTF8 = UTF8TEXT("StartCapture"), .Pointer = &UCameraManagerSubsystem::execStartCapture },
		{ .NameUTF8 = UTF8TEXT("StopCapture"), .Pointer = &UCameraManagerSubsystem::execStopCapture },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UCameraManagerSubsystem_GetLatestFrame, "GetLatestFrame" }, // 1086309371
		{ &Z_Construct_UFunction_UCameraManagerSubsystem_IsCameraAvailable, "IsCameraAvailable" }, // 216482909
		{ &Z_Construct_UFunction_UCameraManagerSubsystem_StartCapture, "StartCapture" }, // 3427534590
		{ &Z_Construct_UFunction_UCameraManagerSubsystem_StopCapture, "StopCapture" }, // 1088573044
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCameraManagerSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UCameraManagerSubsystem_Statics

// ********** Begin Class UCameraManagerSubsystem Property Definitions *****************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCameraManagerSubsystem_Statics::NewProp_TargetFPS = { "TargetFPS", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCameraManagerSubsystem, TargetFPS), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetFPS_MetaData), NewProp_TargetFPS_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCameraManagerSubsystem_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCameraManagerSubsystem_Statics::NewProp_TargetFPS,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCameraManagerSubsystem_Statics::PropPointers) < 2048);
// ********** End Class UCameraManagerSubsystem Property Definitions *******************************
UObject* (*const Z_Construct_UClass_UCameraManagerSubsystem_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UGameInstanceSubsystem,
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCameraManagerSubsystem_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UCameraManagerSubsystem_Statics::ClassParams = {
	&UCameraManagerSubsystem::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UCameraManagerSubsystem_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UCameraManagerSubsystem_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCameraManagerSubsystem_Statics::Class_MetaDataParams), Z_Construct_UClass_UCameraManagerSubsystem_Statics::Class_MetaDataParams)
};
void UCameraManagerSubsystem::StaticRegisterNativesUCameraManagerSubsystem()
{
	UClass* Class = UCameraManagerSubsystem::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UCameraManagerSubsystem_Statics::Funcs));
}
UClass* Z_Construct_UClass_UCameraManagerSubsystem()
{
	if (!Z_Registration_Info_UClass_UCameraManagerSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCameraManagerSubsystem.OuterSingleton, Z_Construct_UClass_UCameraManagerSubsystem_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UCameraManagerSubsystem.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UCameraManagerSubsystem);
UCameraManagerSubsystem::~UCameraManagerSubsystem() {}
// ********** End Class UCameraManagerSubsystem ****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_CameraManagerSubsystem_h__Script_LLM_NPC_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UCameraManagerSubsystem, UCameraManagerSubsystem::StaticClass, TEXT("UCameraManagerSubsystem"), &Z_Registration_Info_UClass_UCameraManagerSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCameraManagerSubsystem), 278575388U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_CameraManagerSubsystem_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_CameraManagerSubsystem_h__Script_LLM_NPC_3287580975{
	TEXT("/Script/LLM_NPC"),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_CameraManagerSubsystem_h__Script_LLM_NPC_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_CameraManagerSubsystem_h__Script_LLM_NPC_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
