#include "MetahumanAnimComponent.h"
#include "LLM_NPC/Emotion/EmotionComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ChildActorComponent.h"
#include "Animation/AnimInstance.h"

UMetahumanAnimComponent::UMetahumanAnimComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PostUpdateWork;
	SubsystemName = TEXT("MetahumanAnimation");
}

void UMetahumanAnimComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMetahumanAnimComponent::InitializeSubsystem()
{
	Super::InitializeSubsystem();

	// Load the blend shape mapping data asset (optional — we have defaults)
	if (!BlendShapeMappingAssetRef.IsNull())
	{
		LoadedMappingData = BlendShapeMappingAssetRef.LoadSynchronous();
	}

	// Cache the EmotionComponent
	if (AActor* Owner = GetOwner())
	{
		CachedEmotionComp = Owner->FindComponentByClass<UEmotionComponent>();

		// Find the Face skeletal mesh in Child Actors (Metahuman setup)
		CachedSkeletalMesh = FindFaceMesh(Owner);

		if (CachedSkeletalMesh)
		{
			UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: Found Face mesh '%s'"), *CachedSkeletalMesh->GetName());

			// Cache the Face AnimInstance and verify we can set properties on it
			CachedFaceAnimInstance = CachedSkeletalMesh->GetAnimInstance();
			if (CachedFaceAnimInstance)
			{
				UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: AnimInstance class: %s"), *CachedFaceAnimInstance->GetClass()->GetName());

				// Dump all float properties to find the exact names
				UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: Dumping float properties on AnimInstance:"));
				for (TFieldIterator<FFloatProperty> It(CachedFaceAnimInstance->GetClass()); It; ++It)
				{
					FString PropName = It->GetName();
					if (PropName.Contains(TEXT("Jaw")) || PropName.Contains(TEXT("jaw")) ||
						PropName.Contains(TEXT("Alpha")) || PropName.Contains(TEXT("Teeth")) ||
						PropName.Contains(TEXT("Open")))
					{
						float Value = It->GetPropertyValue_InContainer(CachedFaceAnimInstance);
						UE_LOG(LogTemp, Log, TEXT("  Property: '%s' = %.2f"), *PropName, Value);
					}
				}

				// Dump all functions to find Set Control
				UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: Dumping functions on AnimInstance:"));
				for (TFieldIterator<UFunction> It(CachedFaceAnimInstance->GetClass()); It; ++It)
				{
					FString FuncName = It->GetName();
					if (FuncName.Contains(TEXT("Control")) || FuncName.Contains(TEXT("Set")) ||
						FuncName.Contains(TEXT("Custom")) || FuncName.Contains(TEXT("Reset")))
					{
						UE_LOG(LogTemp, Log, TEXT("  Function: '%s'"), *FuncName);
					}
				}

				// Try to find Jaw Open Alpha with various names
				TArray<FString> JawNames = {
					TEXT("Jaw Open Alpha"), TEXT("JawOpenAlpha"), TEXT("Jaw_Open_Alpha"),
					TEXT("jawOpenAlpha"), TEXT("Jaw open Alpha")
				};
				for (const FString& Name : JawNames)
				{
					FProperty* JawProp = CachedFaceAnimInstance->GetClass()->FindPropertyByName(FName(*Name));
					if (JawProp)
					{
						UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: Found jaw property as '%s'"), *Name);
						break;
					}
				}

				// Find the "Set Control" function with various names
				TArray<FString> FuncNames = {
					TEXT("Set Control"), TEXT("SetControl"), TEXT("Set_Control"),
					TEXT("setControl"), TEXT("Set control")
				};
				for (const FString& Name : FuncNames)
				{
					CachedSetControlFunc = CachedFaceAnimInstance->FindFunction(FName(*Name));
					if (CachedSetControlFunc)
					{
						UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: Found Set Control function as '%s'"), *Name);
						break;
					}
				}
				if (!CachedSetControlFunc)
				{
					UE_LOG(LogTemp, Warning, TEXT("MetahumanAnim: Could not find Set Control function"));
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("MetahumanAnim: No AnimInstance on Face mesh"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("MetahumanAnim: No Face skeletal mesh found"));
		}
	}

	// Build default emotion-to-FACS-curve mappings
	BuildDefaultEmotionMappings();
}

USkeletalMeshComponent* UMetahumanAnimComponent::FindFaceMesh(AActor* Actor) const
{
	if (!Actor) return nullptr;

	auto SearchForFace = [](AActor* SearchActor) -> USkeletalMeshComponent*
	{
		TArray<USkeletalMeshComponent*> SkeletalMeshes;
		SearchActor->GetComponents<USkeletalMeshComponent>(SkeletalMeshes);
		for (USkeletalMeshComponent* SMC : SkeletalMeshes)
		{
			if (SMC && SMC->GetName().Contains(TEXT("Face")))
			{
				return SMC;
			}
		}
		return nullptr;
	};

	if (USkeletalMeshComponent* Found = SearchForFace(Actor))
	{
		return Found;
	}

	TArray<UChildActorComponent*> ChildActors;
	Actor->GetComponents<UChildActorComponent>(ChildActors);
	for (UChildActorComponent* CAC : ChildActors)
	{
		if (!CAC || !CAC->GetChildActor()) continue;

		if (USkeletalMeshComponent* Found = SearchForFace(CAC->GetChildActor()))
		{
			UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: Found Face mesh in Child Actor: %s"), *Found->GetName());
			return Found;
		}

		TArray<UChildActorComponent*> NestedChildren;
		CAC->GetChildActor()->GetComponents<UChildActorComponent>(NestedChildren);
		for (UChildActorComponent* Nested : NestedChildren)
		{
			if (Nested && Nested->GetChildActor())
			{
				if (USkeletalMeshComponent* Found = SearchForFace(Nested->GetChildActor()))
				{
					return Found;
				}
			}
		}
	}

	return nullptr;
}

void UMetahumanAnimComponent::BuildDefaultEmotionMappings()
{
	EmotionCurveMappings.Empty();

	// Map emotions to FACS/ARKit-compatible curve names that the Metahuman AnimBP reads
	// These are the INPUT curves, not the output morph targets

	// Joy — smile, cheek raise
	EmotionCurveMappings.Add(EEmotionType::Joy, {
		{FName("mouthSmile_L"), 0.8f},
		{FName("mouthSmile_R"), 0.8f},
		{FName("cheekSquint_L"), 0.4f},
		{FName("cheekSquint_R"), 0.4f},
	});

	// Sadness — frown, inner brow raise
	EmotionCurveMappings.Add(EEmotionType::Sadness, {
		{FName("mouthFrown_L"), 0.6f},
		{FName("mouthFrown_R"), 0.6f},
		{FName("browInnerUp"), 0.5f},
	});

	// Anger — brow down, nose wrinkle, jaw clench
	EmotionCurveMappings.Add(EEmotionType::Anger, {
		{FName("browDown_L"), 0.7f},
		{FName("browDown_R"), 0.7f},
		{FName("noseSneer_L"), 0.6f},
		{FName("noseSneer_R"), 0.6f},
		{FName("mouthFrown_L"), 0.3f},
		{FName("mouthFrown_R"), 0.3f},
	});

	// Fear — wide eyes, open mouth
	EmotionCurveMappings.Add(EEmotionType::Fear, {
		{FName("eyeWide_L"), 0.7f},
		{FName("eyeWide_R"), 0.7f},
		{FName("browInnerUp"), 0.6f},
		{FName("mouthStretch_L"), 0.3f},
		{FName("mouthStretch_R"), 0.3f},
	});

	// Surprise — wide eyes, jaw open
	EmotionCurveMappings.Add(EEmotionType::Surprise, {
		{FName("eyeWide_L"), 0.9f},
		{FName("eyeWide_R"), 0.9f},
		{FName("browInnerUp"), 0.7f},
	});

	// Disgust — nose wrinkle, upper lip raise
	EmotionCurveMappings.Add(EEmotionType::Disgust, {
		{FName("noseSneer_L"), 0.8f},
		{FName("noseSneer_R"), 0.8f},
		{FName("mouthUpperUp_L"), 0.5f},
		{FName("mouthUpperUp_R"), 0.5f},
	});

	// Trust — gentle smile
	EmotionCurveMappings.Add(EEmotionType::Trust, {
		{FName("mouthSmile_L"), 0.4f},
		{FName("mouthSmile_R"), 0.4f},
	});

	// Anticipation — slight smile, widened eyes
	EmotionCurveMappings.Add(EEmotionType::Anticipation, {
		{FName("mouthSmile_L"), 0.3f},
		{FName("mouthSmile_R"), 0.3f},
		{FName("eyeWide_L"), 0.3f},
		{FName("eyeWide_R"), 0.3f},
	});

	UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: Built %d emotion curve mappings"), EmotionCurveMappings.Num());
}

void UMetahumanAnimComponent::SetFaceControl(FName ControlName, float Value)
{
	if (!CachedFaceAnimInstance || !CachedSetControlFunc) return;

	// Call "Set Control" via ProcessEvent
	// UE 5.7 Blueprint floats are double internally, so we use double for Value
	// Struct must match the UFunction's parameter layout exactly
	struct
	{
		FName ControlName;
		double Value;      // Blueprint "float" is double in UE 5.7
		bool Result;
		uint8 Pad0[7];     // Padding after bool
		bool ControlAdded;
	} Params;
	FMemory::Memzero(&Params, sizeof(Params));
	Params.ControlName = ControlName;
	Params.Value = (double)Value;

	CachedFaceAnimInstance->ProcessEvent(CachedSetControlFunc, &Params);
}

void UMetahumanAnimComponent::SetJawOpenAlpha(float Value)
{
	if (!CachedFaceAnimInstance) return;

	// Set "JawOpenAlpha" via property reflection
	// In UE 5.7, Blueprint floats are stored as double internally
	static FProperty* CachedProp = nullptr;
	static bool bSearched = false;
	static bool bIsDouble = false;

	if (!bSearched)
	{
		bSearched = true;
		CachedProp = CachedFaceAnimInstance->GetClass()->FindPropertyByName(FName("JawOpenAlpha"));
		if (!CachedProp)
		{
			CachedProp = CachedFaceAnimInstance->GetClass()->FindPropertyByName(FName("Jaw Open Alpha"));
		}
		if (!CachedProp)
		{
			CachedProp = CachedFaceAnimInstance->GetClass()->FindPropertyByName(FName("Jaw_Open_Alpha"));
		}
		if (CachedProp)
		{
			bIsDouble = CachedProp->IsA<FDoubleProperty>();
			UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: JawOpenAlpha property type: %s (isDouble: %d)"),
				*CachedProp->GetCPPType(), bIsDouble ? 1 : 0);
		}
	}

	if (CachedProp)
	{
		float ClampedValue = FMath::Clamp(Value, 0.0f, 1.0f);
		if (bIsDouble)
		{
			double* ValuePtr = CachedProp->ContainerPtrToValuePtr<double>(CachedFaceAnimInstance);
			if (ValuePtr) *ValuePtr = (double)ClampedValue;
		}
		else
		{
			float* ValuePtr = CachedProp->ContainerPtrToValuePtr<float>(CachedFaceAnimInstance);
			if (ValuePtr) *ValuePtr = ClampedValue;
		}
	}
}

void UMetahumanAnimComponent::SetLipSyncJawOpen(float Value)
{
	LipSyncJawOpenValue = FMath::Clamp(Value, 0.0f, 1.0f);
}

void UMetahumanAnimComponent::ShutdownSubsystem()
{
	// Reset all controls
	for (const auto& ActivePair : ActiveCurveValues)
	{
		SetFaceControl(ActivePair.Key, 0.0f);
	}
	ActiveCurveValues.Empty();
	SetJawOpenAlpha(0.0f);

	Super::ShutdownSubsystem();
}

void UMetahumanAnimComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsInitialized || !CachedFaceAnimInstance)
	{
		return;
	}

	// Re-cache AnimInstance if it was recreated (can happen with PIE restarts)
	if (!CachedFaceAnimInstance->IsValidLowLevel())
	{
		CachedFaceAnimInstance = CachedSkeletalMesh ? CachedSkeletalMesh->GetAnimInstance() : nullptr;
		if (!CachedFaceAnimInstance) return;
	}

	// Read the current emotion state
	EEmotionType CurrentEmotion = EEmotionType::Neutral;
	float Intensity = 0.0f;
	if (CachedEmotionComp)
	{
		FEmotionState State = CachedEmotionComp->GetCurrentEmotionState();
		CurrentEmotion = State.PrimaryEmotion;
		Intensity = State.Intensity;
	}

	// Build target curve values from emotion mappings
	TMap<FName, float> TargetCurves;

	// Look up emotion curves
	if (const auto* Curves = EmotionCurveMappings.Find(CurrentEmotion))
	{
		for (const auto& Pair : *Curves)
		{
			TargetCurves.Add(Pair.Key, Pair.Value * Intensity);
		}
	}

	// Smoothly interpolate and apply all active curves
	// First, decay curves that are no longer targeted
	TArray<FName> ToRemove;
	for (auto& Pair : ActiveCurveValues)
	{
		if (!TargetCurves.Contains(Pair.Key))
		{
			Pair.Value = FMath::FInterpTo(Pair.Value, 0.0f, DeltaTime, InterpolationSpeed);
			SetFaceControl(Pair.Key, Pair.Value);
			if (FMath::IsNearlyZero(Pair.Value, 0.005f))
			{
				SetFaceControl(Pair.Key, 0.0f);
				ToRemove.Add(Pair.Key);
			}
		}
	}
	for (const FName& Name : ToRemove)
	{
		ActiveCurveValues.Remove(Name);
	}

	// Interpolate toward target values
	for (const auto& Pair : TargetCurves)
	{
		float& Current = ActiveCurveValues.FindOrAdd(Pair.Key, 0.0f);
		Current = FMath::FInterpTo(Current, Pair.Value, DeltaTime, InterpolationSpeed);
		SetFaceControl(Pair.Key, Current);
	}

	// Lip sync — drive Jaw Open Alpha directly
	float JawTarget = LipSyncJawOpenValue;

	// Emotion jaw open (for surprise, etc.) takes max with lip sync
	if (const auto* Curves = EmotionCurveMappings.Find(CurrentEmotion))
	{
		// Check if emotion wants jaw open
		if (CurrentEmotion == EEmotionType::Surprise)
		{
			JawTarget = FMath::Max(JawTarget, 0.5f * Intensity);
		}
	}

	CurrentJawOpenValue = FMath::FInterpTo(CurrentJawOpenValue, JawTarget, DeltaTime, LipSyncInterpolationSpeed);
	SetJawOpenAlpha(CurrentJawOpenValue);

	// Blinking
	BlinkTimer -= DeltaTime;
	if (BlinkTimer <= 0.0f)
	{
		BlinkTimer = FMath::RandRange(2.5f, 6.0f);
		BlinkPhase = 0.0f;
		bIsBlinking = true;
	}

	if (bIsBlinking)
	{
		BlinkPhase += DeltaTime;
		float BlinkValue = 0.0f;
		if (BlinkPhase < 0.08f)
			BlinkValue = BlinkPhase / 0.08f;
		else if (BlinkPhase < 0.15f)
			BlinkValue = 1.0f;
		else if (BlinkPhase < 0.3f)
			BlinkValue = 1.0f - (BlinkPhase - 0.15f) / 0.15f;
		else
		{
			bIsBlinking = false;
			BlinkValue = 0.0f;
		}

		SetFaceControl(FName("eyeBlink_L"), BlinkValue);
		SetFaceControl(FName("eyeBlink_R"), BlinkValue);
	}
}

void UMetahumanAnimComponent::UpdateBlendShapes(float DeltaTime)
{
	// Legacy — now handled in TickComponent via SetFaceControl / SetJawOpenAlpha
}
