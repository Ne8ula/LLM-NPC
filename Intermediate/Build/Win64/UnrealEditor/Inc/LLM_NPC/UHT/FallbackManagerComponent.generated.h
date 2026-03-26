// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Fallback/FallbackManagerComponent.h"

#ifdef LLM_NPC_FallbackManagerComponent_generated_h
#error "FallbackManagerComponent.generated.h already included, missing '#pragma once' in FallbackManagerComponent.h"
#endif
#define LLM_NPC_FallbackManagerComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class EDegradationLevel : uint8;
enum class EDialogueInputMode : uint8;
enum class EManipulationInputMode : uint8;

// ********** Begin Delegate FOnInputModeChanged ***************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_FallbackManagerComponent_h_10_DELEGATE \
LLM_NPC_API void FOnInputModeChanged_DelegateWrapper(const FMulticastScriptDelegate& OnInputModeChanged, const FString& ModeName, bool bAvailable);


// ********** End Delegate FOnInputModeChanged *****************************************************

// ********** Begin Class UFallbackManagerComponent ************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_FallbackManagerComponent_h_37_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execCheckDeviceAvailability); \
	DECLARE_FUNCTION(execSetManipulationMode); \
	DECLARE_FUNCTION(execSetDialogueMode); \
	DECLARE_FUNCTION(execGetCurrentDegradationLevel);


struct Z_Construct_UClass_UFallbackManagerComponent_Statics;
LLM_NPC_API UClass* Z_Construct_UClass_UFallbackManagerComponent_NoRegister();

#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_FallbackManagerComponent_h_37_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUFallbackManagerComponent(); \
	friend struct ::Z_Construct_UClass_UFallbackManagerComponent_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend LLM_NPC_API UClass* ::Z_Construct_UClass_UFallbackManagerComponent_NoRegister(); \
public: \
	DECLARE_CLASS2(UFallbackManagerComponent, UNPCSubsystemComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LLM_NPC"), Z_Construct_UClass_UFallbackManagerComponent_NoRegister) \
	DECLARE_SERIALIZER(UFallbackManagerComponent)


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_FallbackManagerComponent_h_37_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UFallbackManagerComponent(UFallbackManagerComponent&&) = delete; \
	UFallbackManagerComponent(const UFallbackManagerComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UFallbackManagerComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UFallbackManagerComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UFallbackManagerComponent) \
	NO_API virtual ~UFallbackManagerComponent();


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_FallbackManagerComponent_h_34_PROLOG
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_FallbackManagerComponent_h_37_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_FallbackManagerComponent_h_37_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_FallbackManagerComponent_h_37_INCLASS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_FallbackManagerComponent_h_37_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UFallbackManagerComponent;

// ********** End Class UFallbackManagerComponent **************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Fallback_FallbackManagerComponent_h

// ********** Begin Enum EDegradationLevel *********************************************************
#define FOREACH_ENUM_EDEGRADATIONLEVEL(op) \
	op(EDegradationLevel::Full) \
	op(EDegradationLevel::NoCamera) \
	op(EDegradationLevel::NoMic) \
	op(EDegradationLevel::Minimal) 

enum class EDegradationLevel : uint8;
template<> struct TIsUEnumClass<EDegradationLevel> { enum { Value = true }; };
template<> LLM_NPC_NON_ATTRIBUTED_API UEnum* StaticEnum<EDegradationLevel>();
// ********** End Enum EDegradationLevel ***********************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
