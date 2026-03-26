// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Core/NPCCharacter.h"

#ifdef LLM_NPC_NPCCharacter_generated_h
#error "NPCCharacter.generated.h already included, missing '#pragma once' in NPCCharacter.h"
#endif
#define LLM_NPC_NPCCharacter_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ANPCCharacter ************************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCCharacter_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execInitializeNPC);


struct Z_Construct_UClass_ANPCCharacter_Statics;
LLM_NPC_API UClass* Z_Construct_UClass_ANPCCharacter_NoRegister();

#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCCharacter_h_28_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesANPCCharacter(); \
	friend struct ::Z_Construct_UClass_ANPCCharacter_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend LLM_NPC_API UClass* ::Z_Construct_UClass_ANPCCharacter_NoRegister(); \
public: \
	DECLARE_CLASS2(ANPCCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LLM_NPC"), Z_Construct_UClass_ANPCCharacter_NoRegister) \
	DECLARE_SERIALIZER(ANPCCharacter)


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCCharacter_h_28_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ANPCCharacter(ANPCCharacter&&) = delete; \
	ANPCCharacter(const ANPCCharacter&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ANPCCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ANPCCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ANPCCharacter) \
	NO_API virtual ~ANPCCharacter();


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCCharacter_h_25_PROLOG
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCCharacter_h_28_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCCharacter_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCCharacter_h_28_INCLASS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCCharacter_h_28_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ANPCCharacter;

// ********** End Class ANPCCharacter **************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCCharacter_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
