// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Gesture/GestureClassifier.h"

#ifdef LLM_NPC_GestureClassifier_generated_h
#error "GestureClassifier.generated.h already included, missing '#pragma once' in GestureClassifier.h"
#endif
#define LLM_NPC_GestureClassifier_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FGestureInput;

// ********** Begin Class UGestureClassifier *******************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_GestureClassifier_h_22_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execReset); \
	DECLARE_FUNCTION(execClassifyTwoHandGesture); \
	DECLARE_FUNCTION(execClassifyGesture);


struct Z_Construct_UClass_UGestureClassifier_Statics;
LLM_NPC_API UClass* Z_Construct_UClass_UGestureClassifier_NoRegister();

#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_GestureClassifier_h_22_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGestureClassifier(); \
	friend struct ::Z_Construct_UClass_UGestureClassifier_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend LLM_NPC_API UClass* ::Z_Construct_UClass_UGestureClassifier_NoRegister(); \
public: \
	DECLARE_CLASS2(UGestureClassifier, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LLM_NPC"), Z_Construct_UClass_UGestureClassifier_NoRegister) \
	DECLARE_SERIALIZER(UGestureClassifier)


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_GestureClassifier_h_22_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UGestureClassifier(UGestureClassifier&&) = delete; \
	UGestureClassifier(const UGestureClassifier&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGestureClassifier); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGestureClassifier); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UGestureClassifier) \
	NO_API virtual ~UGestureClassifier();


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_GestureClassifier_h_19_PROLOG
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_GestureClassifier_h_22_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_GestureClassifier_h_22_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_GestureClassifier_h_22_INCLASS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_GestureClassifier_h_22_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UGestureClassifier;

// ********** End Class UGestureClassifier *********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_GestureClassifier_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
