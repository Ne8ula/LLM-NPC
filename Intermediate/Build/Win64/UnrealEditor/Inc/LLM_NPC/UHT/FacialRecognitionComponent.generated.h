// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Vision/FacialRecognitionComponent.h"

#ifdef LLM_NPC_FacialRecognitionComponent_generated_h
#error "FacialRecognitionComponent.generated.h already included, missing '#pragma once' in FacialRecognitionComponent.h"
#endif
#define LLM_NPC_FacialRecognitionComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FDetectedUserEmotion;

// ********** Begin Delegate FOnUserEmotionDetected ************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_FacialRecognitionComponent_h_11_DELEGATE \
LLM_NPC_API void FOnUserEmotionDetected_DelegateWrapper(const FMulticastScriptDelegate& OnUserEmotionDetected, FDetectedUserEmotion DetectedEmotion);


// ********** End Delegate FOnUserEmotionDetected **************************************************

// ********** Begin Class UFacialRecognitionComponent **********************************************
struct Z_Construct_UClass_UFacialRecognitionComponent_Statics;
LLM_NPC_API UClass* Z_Construct_UClass_UFacialRecognitionComponent_NoRegister();

#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_FacialRecognitionComponent_h_22_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUFacialRecognitionComponent(); \
	friend struct ::Z_Construct_UClass_UFacialRecognitionComponent_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend LLM_NPC_API UClass* ::Z_Construct_UClass_UFacialRecognitionComponent_NoRegister(); \
public: \
	DECLARE_CLASS2(UFacialRecognitionComponent, UNPCSubsystemComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LLM_NPC"), Z_Construct_UClass_UFacialRecognitionComponent_NoRegister) \
	DECLARE_SERIALIZER(UFacialRecognitionComponent)


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_FacialRecognitionComponent_h_22_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UFacialRecognitionComponent(UFacialRecognitionComponent&&) = delete; \
	UFacialRecognitionComponent(const UFacialRecognitionComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UFacialRecognitionComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UFacialRecognitionComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UFacialRecognitionComponent) \
	NO_API virtual ~UFacialRecognitionComponent();


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_FacialRecognitionComponent_h_19_PROLOG
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_FacialRecognitionComponent_h_22_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_FacialRecognitionComponent_h_22_INCLASS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_FacialRecognitionComponent_h_22_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UFacialRecognitionComponent;

// ********** End Class UFacialRecognitionComponent ************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Vision_FacialRecognitionComponent_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
