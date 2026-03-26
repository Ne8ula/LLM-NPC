// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Gesture/GestureRecognitionComponent.h"

#ifdef LLM_NPC_GestureRecognitionComponent_generated_h
#error "GestureRecognitionComponent.generated.h already included, missing '#pragma once' in GestureRecognitionComponent.h"
#endif
#define LLM_NPC_GestureRecognitionComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UGestureClassifier;
struct FGestureInput;

// ********** Begin Delegate FOnGestureDetected ****************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_GestureRecognitionComponent_h_12_DELEGATE \
LLM_NPC_API void FOnGestureDetected_DelegateWrapper(const FMulticastScriptDelegate& OnGestureDetected, FGestureInput DetectedGesture);


// ********** End Delegate FOnGestureDetected ******************************************************

// ********** Begin Class UGestureRecognitionComponent *********************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_GestureRecognitionComponent_h_22_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetGestureClassifier);


struct Z_Construct_UClass_UGestureRecognitionComponent_Statics;
LLM_NPC_API UClass* Z_Construct_UClass_UGestureRecognitionComponent_NoRegister();

#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_GestureRecognitionComponent_h_22_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGestureRecognitionComponent(); \
	friend struct ::Z_Construct_UClass_UGestureRecognitionComponent_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend LLM_NPC_API UClass* ::Z_Construct_UClass_UGestureRecognitionComponent_NoRegister(); \
public: \
	DECLARE_CLASS2(UGestureRecognitionComponent, UNPCSubsystemComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LLM_NPC"), Z_Construct_UClass_UGestureRecognitionComponent_NoRegister) \
	DECLARE_SERIALIZER(UGestureRecognitionComponent)


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_GestureRecognitionComponent_h_22_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UGestureRecognitionComponent(UGestureRecognitionComponent&&) = delete; \
	UGestureRecognitionComponent(const UGestureRecognitionComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGestureRecognitionComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGestureRecognitionComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UGestureRecognitionComponent) \
	NO_API virtual ~UGestureRecognitionComponent();


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_GestureRecognitionComponent_h_19_PROLOG
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_GestureRecognitionComponent_h_22_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_GestureRecognitionComponent_h_22_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_GestureRecognitionComponent_h_22_INCLASS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_GestureRecognitionComponent_h_22_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UGestureRecognitionComponent;

// ********** End Class UGestureRecognitionComponent ***********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Gesture_GestureRecognitionComponent_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
