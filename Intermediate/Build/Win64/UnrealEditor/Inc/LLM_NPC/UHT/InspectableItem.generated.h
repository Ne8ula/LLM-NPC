// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Gesture/InspectableItem.h"

#ifdef LLM_NPC_InspectableItem_generated_h
#error "InspectableItem.generated.h already included, missing '#pragma once' in InspectableItem.h"
#endif
#define LLM_NPC_InspectableItem_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AInspectableItem *********************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_InspectableItem_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execResetTransform); \
	DECLARE_FUNCTION(execApplyRotation); \
	DECLARE_FUNCTION(execApplyScale);


struct Z_Construct_UClass_AInspectableItem_Statics;
LLM_NPC_API UClass* Z_Construct_UClass_AInspectableItem_NoRegister();

#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_InspectableItem_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAInspectableItem(); \
	friend struct ::Z_Construct_UClass_AInspectableItem_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend LLM_NPC_API UClass* ::Z_Construct_UClass_AInspectableItem_NoRegister(); \
public: \
	DECLARE_CLASS2(AInspectableItem, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LLM_NPC"), Z_Construct_UClass_AInspectableItem_NoRegister) \
	DECLARE_SERIALIZER(AInspectableItem)


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_InspectableItem_h_15_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AInspectableItem(AInspectableItem&&) = delete; \
	AInspectableItem(const AInspectableItem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AInspectableItem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AInspectableItem); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AInspectableItem) \
	NO_API virtual ~AInspectableItem();


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_InspectableItem_h_12_PROLOG
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_InspectableItem_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_InspectableItem_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_InspectableItem_h_15_INCLASS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_InspectableItem_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AInspectableItem;

// ********** End Class AInspectableItem ***********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_InspectableItem_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
