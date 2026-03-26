// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Core/NPCSubsystemComponent.h"

#ifdef LLM_NPC_NPCSubsystemComponent_generated_h
#error "NPCSubsystemComponent.generated.h already included, missing '#pragma once' in NPCSubsystemComponent.h"
#endif
#define LLM_NPC_NPCSubsystemComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UNPCSubsystemComponent ***************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCSubsystemComponent_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetSubsystemName); \
	DECLARE_FUNCTION(execIsSubsystemAvailable); \
	DECLARE_FUNCTION(execShutdownSubsystem); \
	DECLARE_FUNCTION(execInitializeSubsystem);


struct Z_Construct_UClass_UNPCSubsystemComponent_Statics;
LLM_NPC_API UClass* Z_Construct_UClass_UNPCSubsystemComponent_NoRegister();

#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCSubsystemComponent_h_18_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUNPCSubsystemComponent(); \
	friend struct ::Z_Construct_UClass_UNPCSubsystemComponent_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend LLM_NPC_API UClass* ::Z_Construct_UClass_UNPCSubsystemComponent_NoRegister(); \
public: \
	DECLARE_CLASS2(UNPCSubsystemComponent, UActorComponent, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/LLM_NPC"), Z_Construct_UClass_UNPCSubsystemComponent_NoRegister) \
	DECLARE_SERIALIZER(UNPCSubsystemComponent)


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCSubsystemComponent_h_18_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UNPCSubsystemComponent(UNPCSubsystemComponent&&) = delete; \
	UNPCSubsystemComponent(const UNPCSubsystemComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNPCSubsystemComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNPCSubsystemComponent); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(UNPCSubsystemComponent) \
	NO_API virtual ~UNPCSubsystemComponent();


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCSubsystemComponent_h_15_PROLOG
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCSubsystemComponent_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCSubsystemComponent_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCSubsystemComponent_h_18_INCLASS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCSubsystemComponent_h_18_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UNPCSubsystemComponent;

// ********** End Class UNPCSubsystemComponent *****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCSubsystemComponent_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
