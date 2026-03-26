#include "NPCSubsystemComponent.h"

UNPCSubsystemComponent::UNPCSubsystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UNPCSubsystemComponent::BeginPlay()
{
	Super::BeginPlay();
	InitializeSubsystem();
}

void UNPCSubsystemComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ShutdownSubsystem();
	Super::EndPlay(EndPlayReason);
}

void UNPCSubsystemComponent::InitializeSubsystem()
{
	bIsInitialized = true;
	bIsAvailable = true;
	UE_LOG(LogTemp, Log, TEXT("NPC Subsystem [%s] initialized"), *SubsystemName);
}

void UNPCSubsystemComponent::ShutdownSubsystem()
{
	bIsInitialized = false;
	bIsAvailable = false;
	UE_LOG(LogTemp, Log, TEXT("NPC Subsystem [%s] shut down"), *SubsystemName);
}

bool UNPCSubsystemComponent::IsSubsystemAvailable() const
{
	return bIsInitialized && bIsAvailable;
}
