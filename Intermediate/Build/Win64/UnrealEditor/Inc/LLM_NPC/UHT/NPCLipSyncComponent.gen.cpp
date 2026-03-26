// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LLM_NPC/Animation/NPCLipSyncComponent.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeNPCLipSyncComponent() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UAudioComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USkeletalMeshComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USoundWave_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UNPCLipSyncComponent();
LLM_NPC_API UClass* Z_Construct_UClass_UNPCLipSyncComponent_NoRegister();
LLM_NPC_API UClass* Z_Construct_UClass_UNPCSubsystemComponent();
UPackage* Z_Construct_UPackage__Script_LLM_NPC();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UNPCLipSyncComponent Function StartLipSync *******************************
struct Z_Construct_UFunction_UNPCLipSyncComponent_StartLipSync_Statics
{
	struct NPCLipSyncComponent_eventStartLipSync_Parms
	{
		USoundWave* AudioSource;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|LipSync" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Begin driving lip sync from the given audio source.\n\x09 * Creates an audio component on the owner and plays the sound.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Animation/NPCLipSyncComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Begin driving lip sync from the given audio source.\nCreates an audio component on the owner and plays the sound." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function StartLipSync constinit property declarations **************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AudioSource;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function StartLipSync constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function StartLipSync Property Definitions *************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UNPCLipSyncComponent_StartLipSync_Statics::NewProp_AudioSource = { "AudioSource", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NPCLipSyncComponent_eventStartLipSync_Parms, AudioSource), Z_Construct_UClass_USoundWave_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNPCLipSyncComponent_StartLipSync_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNPCLipSyncComponent_StartLipSync_Statics::NewProp_AudioSource,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UNPCLipSyncComponent_StartLipSync_Statics::PropPointers) < 2048);
// ********** End Function StartLipSync Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNPCLipSyncComponent_StartLipSync_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UNPCLipSyncComponent, nullptr, "StartLipSync", 	Z_Construct_UFunction_UNPCLipSyncComponent_StartLipSync_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UNPCLipSyncComponent_StartLipSync_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UNPCLipSyncComponent_StartLipSync_Statics::NPCLipSyncComponent_eventStartLipSync_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNPCLipSyncComponent_StartLipSync_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNPCLipSyncComponent_StartLipSync_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UNPCLipSyncComponent_StartLipSync_Statics::NPCLipSyncComponent_eventStartLipSync_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNPCLipSyncComponent_StartLipSync()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNPCLipSyncComponent_StartLipSync_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNPCLipSyncComponent::execStartLipSync)
{
	P_GET_OBJECT(USoundWave,Z_Param_AudioSource);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->StartLipSync(Z_Param_AudioSource);
	P_NATIVE_END;
}
// ********** End Class UNPCLipSyncComponent Function StartLipSync *********************************

// ********** Begin Class UNPCLipSyncComponent Function StopLipSync ********************************
struct Z_Construct_UFunction_UNPCLipSyncComponent_StopLipSync_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC|LipSync" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Stop lip sync and smoothly close the mouth. */" },
#endif
		{ "ModuleRelativePath", "Animation/NPCLipSyncComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Stop lip sync and smoothly close the mouth." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function StopLipSync constinit property declarations ***************************
// ********** End Function StopLipSync constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNPCLipSyncComponent_StopLipSync_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UNPCLipSyncComponent, nullptr, "StopLipSync", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNPCLipSyncComponent_StopLipSync_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNPCLipSyncComponent_StopLipSync_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UNPCLipSyncComponent_StopLipSync()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNPCLipSyncComponent_StopLipSync_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNPCLipSyncComponent::execStopLipSync)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->StopLipSync();
	P_NATIVE_END;
}
// ********** End Class UNPCLipSyncComponent Function StopLipSync **********************************

// ********** Begin Class UNPCLipSyncComponent *****************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UNPCLipSyncComponent;
UClass* UNPCLipSyncComponent::GetPrivateStaticClass()
{
	using TClass = UNPCLipSyncComponent;
	if (!Z_Registration_Info_UClass_UNPCLipSyncComponent.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("NPCLipSyncComponent"),
			Z_Registration_Info_UClass_UNPCLipSyncComponent.InnerSingleton,
			StaticRegisterNativesUNPCLipSyncComponent,
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
	return Z_Registration_Info_UClass_UNPCLipSyncComponent.InnerSingleton;
}
UClass* Z_Construct_UClass_UNPCLipSyncComponent_NoRegister()
{
	return UNPCLipSyncComponent::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UNPCLipSyncComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "LLMNPC" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Drives viseme blend shapes from TTS audio output for lip synchronization.\n *\n * Currently implements a simple amplitude-based mouth open/close driver as a\n * placeholder. Designed to be replaced with OVRLipSync or a similar phoneme-based\n * solution in production.\n */" },
#endif
		{ "IncludePath", "Animation/NPCLipSyncComponent.h" },
		{ "ModuleRelativePath", "Animation/NPCLipSyncComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Drives viseme blend shapes from TTS audio output for lip synchronization.\n\nCurrently implements a simple amplitude-based mouth open/close driver as a\nplaceholder. Designed to be replaced with OVRLipSync or a similar phoneme-based\nsolution in production." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MouthOpenBlendShape_MetaData[] = {
		{ "Category", "NPC|LipSync" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Name of the morph target controlling mouth open on the skeletal mesh. */" },
#endif
		{ "ModuleRelativePath", "Animation/NPCLipSyncComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Name of the morph target controlling mouth open on the skeletal mesh." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Sensitivity_MetaData[] = {
		{ "Category", "NPC|LipSync" },
		{ "ClampMax", "10.0" },
		{ "ClampMin", "0.1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Sensitivity multiplier for amplitude-to-morph-target mapping. */" },
#endif
		{ "ModuleRelativePath", "Animation/NPCLipSyncComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Sensitivity multiplier for amplitude-to-morph-target mapping." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LipSyncInterpolationSpeed_MetaData[] = {
		{ "Category", "NPC|LipSync" },
		{ "ClampMin", "0.1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Interpolation speed for smoothing mouth movement. */" },
#endif
		{ "ModuleRelativePath", "Animation/NPCLipSyncComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Interpolation speed for smoothing mouth movement." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CachedSkeletalMesh_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Cached reference to the owner's skeletal mesh component. */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Animation/NPCLipSyncComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Cached reference to the owner's skeletal mesh component." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActiveAudioComponent_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Audio component used for playback. */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Animation/NPCLipSyncComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Audio component used for playback." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UNPCLipSyncComponent constinit property declarations *********************
	static const UECodeGen_Private::FNamePropertyParams NewProp_MouthOpenBlendShape;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Sensitivity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LipSyncInterpolationSpeed;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CachedSkeletalMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ActiveAudioComponent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UNPCLipSyncComponent constinit property declarations ***********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("StartLipSync"), .Pointer = &UNPCLipSyncComponent::execStartLipSync },
		{ .NameUTF8 = UTF8TEXT("StopLipSync"), .Pointer = &UNPCLipSyncComponent::execStopLipSync },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UNPCLipSyncComponent_StartLipSync, "StartLipSync" }, // 108953438
		{ &Z_Construct_UFunction_UNPCLipSyncComponent_StopLipSync, "StopLipSync" }, // 2468642427
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNPCLipSyncComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UNPCLipSyncComponent_Statics

// ********** Begin Class UNPCLipSyncComponent Property Definitions ********************************
const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_UNPCLipSyncComponent_Statics::NewProp_MouthOpenBlendShape = { "MouthOpenBlendShape", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNPCLipSyncComponent, MouthOpenBlendShape), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MouthOpenBlendShape_MetaData), NewProp_MouthOpenBlendShape_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UNPCLipSyncComponent_Statics::NewProp_Sensitivity = { "Sensitivity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNPCLipSyncComponent, Sensitivity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Sensitivity_MetaData), NewProp_Sensitivity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UNPCLipSyncComponent_Statics::NewProp_LipSyncInterpolationSpeed = { "LipSyncInterpolationSpeed", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNPCLipSyncComponent, LipSyncInterpolationSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LipSyncInterpolationSpeed_MetaData), NewProp_LipSyncInterpolationSpeed_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UNPCLipSyncComponent_Statics::NewProp_CachedSkeletalMesh = { "CachedSkeletalMesh", nullptr, (EPropertyFlags)0x0144000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNPCLipSyncComponent, CachedSkeletalMesh), Z_Construct_UClass_USkeletalMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CachedSkeletalMesh_MetaData), NewProp_CachedSkeletalMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UNPCLipSyncComponent_Statics::NewProp_ActiveAudioComponent = { "ActiveAudioComponent", nullptr, (EPropertyFlags)0x0144000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNPCLipSyncComponent, ActiveAudioComponent), Z_Construct_UClass_UAudioComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActiveAudioComponent_MetaData), NewProp_ActiveAudioComponent_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UNPCLipSyncComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCLipSyncComponent_Statics::NewProp_MouthOpenBlendShape,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCLipSyncComponent_Statics::NewProp_Sensitivity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCLipSyncComponent_Statics::NewProp_LipSyncInterpolationSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCLipSyncComponent_Statics::NewProp_CachedSkeletalMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNPCLipSyncComponent_Statics::NewProp_ActiveAudioComponent,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNPCLipSyncComponent_Statics::PropPointers) < 2048);
// ********** End Class UNPCLipSyncComponent Property Definitions **********************************
UObject* (*const Z_Construct_UClass_UNPCLipSyncComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UNPCSubsystemComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_LLM_NPC,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNPCLipSyncComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UNPCLipSyncComponent_Statics::ClassParams = {
	&UNPCLipSyncComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UNPCLipSyncComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UNPCLipSyncComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNPCLipSyncComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UNPCLipSyncComponent_Statics::Class_MetaDataParams)
};
void UNPCLipSyncComponent::StaticRegisterNativesUNPCLipSyncComponent()
{
	UClass* Class = UNPCLipSyncComponent::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UNPCLipSyncComponent_Statics::Funcs));
}
UClass* Z_Construct_UClass_UNPCLipSyncComponent()
{
	if (!Z_Registration_Info_UClass_UNPCLipSyncComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNPCLipSyncComponent.OuterSingleton, Z_Construct_UClass_UNPCLipSyncComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UNPCLipSyncComponent.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UNPCLipSyncComponent);
UNPCLipSyncComponent::~UNPCLipSyncComponent() {}
// ********** End Class UNPCLipSyncComponent *******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Animation_NPCLipSyncComponent_h__Script_LLM_NPC_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNPCLipSyncComponent, UNPCLipSyncComponent::StaticClass, TEXT("UNPCLipSyncComponent"), &Z_Registration_Info_UClass_UNPCLipSyncComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNPCLipSyncComponent), 2985690978U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Animation_NPCLipSyncComponent_h__Script_LLM_NPC_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Animation_NPCLipSyncComponent_h__Script_LLM_NPC_760629027{
	TEXT("/Script/LLM_NPC"),
	Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Animation_NPCLipSyncComponent_h__Script_LLM_NPC_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Animation_NPCLipSyncComponent_h__Script_LLM_NPC_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
