// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Gesture/ObjectInspectWidget.h"

#ifdef LLM_NPC_ObjectInspectWidget_generated_h
#error "ObjectInspectWidget.generated.h already included, missing '#pragma once' in ObjectInspectWidget.h"
#endif
#define LLM_NPC_ObjectInspectWidget_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AInspectableItem;
struct FGestureInput;

// ********** Begin Class UObjectInspectWidget *****************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_ObjectInspectWidget_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execHasInspectItem); \
	DECLARE_FUNCTION(execGetInspectItem); \
	DECLARE_FUNCTION(execApplyMouseInput); \
	DECLARE_FUNCTION(execApplyGestureInput); \
	DECLARE_FUNCTION(execSetInspectItem);


struct Z_Construct_UClass_UObjectInspectWidget_Statics;
LLM_NPC_API UClass* Z_Construct_UClass_UObjectInspectWidget_NoRegister();

#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_ObjectInspectWidget_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUObjectInspectWidget(); \
	friend struct ::Z_Construct_UClass_UObjectInspectWidget_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend LLM_NPC_API UClass* ::Z_Construct_UClass_UObjectInspectWidget_NoRegister(); \
public: \
	DECLARE_CLASS2(UObjectInspectWidget, UUserWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LLM_NPC"), Z_Construct_UClass_UObjectInspectWidget_NoRegister) \
	DECLARE_SERIALIZER(UObjectInspectWidget)


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_ObjectInspectWidget_h_19_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UObjectInspectWidget(UObjectInspectWidget&&) = delete; \
	UObjectInspectWidget(const UObjectInspectWidget&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UObjectInspectWidget); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UObjectInspectWidget); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UObjectInspectWidget) \
	NO_API virtual ~UObjectInspectWidget();


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_ObjectInspectWidget_h_16_PROLOG
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_ObjectInspectWidget_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_ObjectInspectWidget_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_ObjectInspectWidget_h_19_INCLASS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_ObjectInspectWidget_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UObjectInspectWidget;

// ********** End Class UObjectInspectWidget *******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_ObjectInspectWidget_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
