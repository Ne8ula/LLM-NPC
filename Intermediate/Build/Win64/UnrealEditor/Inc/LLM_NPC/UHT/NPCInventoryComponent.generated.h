// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Inventory/NPCInventoryComponent.h"

#ifdef LLM_NPC_NPCInventoryComponent_generated_h
#error "NPCInventoryComponent.generated.h already included, missing '#pragma once' in NPCInventoryComponent.h"
#endif
#define LLM_NPC_NPCInventoryComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FEmotionState;
struct FInventoryItem;

// ********** Begin Delegate FOnItemUnlocked *******************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Inventory_NPCInventoryComponent_h_11_DELEGATE \
LLM_NPC_API void FOnItemUnlocked_DelegateWrapper(const FMulticastScriptDelegate& OnItemUnlocked, FName ItemID);


// ********** End Delegate FOnItemUnlocked *********************************************************

// ********** Begin Delegate FOnItemGiven **********************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Inventory_NPCInventoryComponent_h_12_DELEGATE \
LLM_NPC_API void FOnItemGiven_DelegateWrapper(const FMulticastScriptDelegate& OnItemGiven, FName ItemID);


// ********** End Delegate FOnItemGiven ************************************************************

// ********** Begin Class UNPCInventoryComponent ***************************************************
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Inventory_NPCInventoryComponent_h_25_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execHandleEmotionStateChanged); \
	DECLARE_FUNCTION(execUpdateKeywords); \
	DECLARE_FUNCTION(execGetUnlockedItems); \
	DECLARE_FUNCTION(execTryGiveItem); \
	DECLARE_FUNCTION(execCheckUnlockConditions);


struct Z_Construct_UClass_UNPCInventoryComponent_Statics;
LLM_NPC_API UClass* Z_Construct_UClass_UNPCInventoryComponent_NoRegister();

#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Inventory_NPCInventoryComponent_h_25_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUNPCInventoryComponent(); \
	friend struct ::Z_Construct_UClass_UNPCInventoryComponent_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend LLM_NPC_API UClass* ::Z_Construct_UClass_UNPCInventoryComponent_NoRegister(); \
public: \
	DECLARE_CLASS2(UNPCInventoryComponent, UNPCSubsystemComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LLM_NPC"), Z_Construct_UClass_UNPCInventoryComponent_NoRegister) \
	DECLARE_SERIALIZER(UNPCInventoryComponent)


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Inventory_NPCInventoryComponent_h_25_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UNPCInventoryComponent(UNPCInventoryComponent&&) = delete; \
	UNPCInventoryComponent(const UNPCInventoryComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNPCInventoryComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNPCInventoryComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UNPCInventoryComponent) \
	NO_API virtual ~UNPCInventoryComponent();


#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Inventory_NPCInventoryComponent_h_22_PROLOG
#define FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Inventory_NPCInventoryComponent_h_25_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Inventory_NPCInventoryComponent_h_25_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Inventory_NPCInventoryComponent_h_25_INCLASS_NO_PURE_DECLS \
	FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Inventory_NPCInventoryComponent_h_25_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UNPCInventoryComponent;

// ********** End Class UNPCInventoryComponent *****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_alexx_OneDrive_Documents_GitHub_LLM_NPC_Source_LLM_NPC_Inventory_NPCInventoryComponent_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
