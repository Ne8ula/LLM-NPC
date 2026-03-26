// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Core/NPCAIController.h"

#ifdef LLM_NPC_NPCAIController_generated_h
#error "NPCAIController.generated.h already included, missing '#pragma once' in NPCAIController.h"
#endif
#define LLM_NPC_NPCAIController_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FDetectedUserEmotion;

// ********** Begin Class ANPCAIController *********************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCAIController_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execHandleUserInput);


struct Z_Construct_UClass_ANPCAIController_Statics;
LLM_NPC_API UClass* Z_Construct_UClass_ANPCAIController_NoRegister();

#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCAIController_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesANPCAIController(); \
	friend struct ::Z_Construct_UClass_ANPCAIController_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend LLM_NPC_API UClass* ::Z_Construct_UClass_ANPCAIController_NoRegister(); \
public: \
	DECLARE_CLASS2(ANPCAIController, AAIController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LLM_NPC"), Z_Construct_UClass_ANPCAIController_NoRegister) \
	DECLARE_SERIALIZER(ANPCAIController)


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCAIController_h_19_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ANPCAIController(ANPCAIController&&) = delete; \
	ANPCAIController(const ANPCAIController&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ANPCAIController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ANPCAIController); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ANPCAIController) \
	NO_API virtual ~ANPCAIController();


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCAIController_h_16_PROLOG
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCAIController_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCAIController_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCAIController_h_19_INCLASS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCAIController_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ANPCAIController;

// ********** End Class ANPCAIController ***********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Core_NPCAIController_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
