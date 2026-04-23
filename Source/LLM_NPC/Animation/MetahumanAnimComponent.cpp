#include "MetahumanAnimComponent.h"
#include "LLM_NPC/Emotion/EmotionComponent.h"
#include "LLM_NPC/Dialogue/WhisperSTTComponent.h"
#include "LLM_NPC/Dialogue/ElevenLabsTTSComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ChildActorComponent.h"
#include "Animation/AnimInstance.h"

UMetahumanAnimComponent::UMetahumanAnimComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PostUpdateWork;
	SubsystemName = TEXT("MetahumanAnimation");

	// Default subtle "thinking" pose — brow-only (see header). These names
	// are ARKit/FACS curves that flow through the same "Set Control" path
	// the emotion curves use successfully today. browInnerUp is also used
	// by Sadness/Fear/Surprise — proven working. browOuterUp_L/R are not
	// touched by any existing emotion, so they're pure additive.
	ThinkingCurves.Add(FName("browInnerUp"),   0.25f);
	ThinkingCurves.Add(FName("browOuterUp_L"), 0.10f);
	ThinkingCurves.Add(FName("browOuterUp_R"), 0.10f);
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

				// DIAGNOSTIC: dump Set Control's parameter signature so we can
				// verify the FName/double/bool/pad/bool struct layout used by
				// SetFaceControl actually matches this AnimBP's real function.
				if (CachedSetControlFunc)
				{
					UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: === Set Control signature ==="));
					int32 ParamIdx = 0;
					for (TFieldIterator<FProperty> PropIt(CachedSetControlFunc); PropIt; ++PropIt)
					{
						FProperty* Param = *PropIt;
						FString Flags;
						if (Param->HasAnyPropertyFlags(CPF_ReturnParm))  Flags += TEXT("return ");
						if (Param->HasAnyPropertyFlags(CPF_OutParm))     Flags += TEXT("out ");
						if (Param->HasAnyPropertyFlags(CPF_ReferenceParm)) Flags += TEXT("ref ");
						UE_LOG(LogTemp, Log,
							TEXT("  [%d] name='%s' cppType='%s' size=%d offset=%d flags=%s"),
							ParamIdx++,
							*Param->GetName(),
							*Param->GetCPPType(),
							Param->GetSize(),
							Param->GetOffset_ForUFunction(),
							*Flags);
					}
					UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: ParamsSize=%d, ReturnValueOffset=%d"),
						CachedSetControlFunc->ParmsSize,
						CachedSetControlFunc->ReturnValueOffset);
				}

				// DIAGNOSTIC: find and invoke GetCustomControls so we can dump
				// the authoritative list of curve names that Set Control will
				// actually accept on this MetaHuman Face AnimBP.
				if (UFunction* GetCtrlFunc = CachedFaceAnimInstance->FindFunction(FName("GetCustomControls")))
				{
					UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: === GetCustomControls signature ==="));
					int32 ParamIdx = 0;
					FProperty* OutParamProp = nullptr;
					for (TFieldIterator<FProperty> PropIt(GetCtrlFunc); PropIt; ++PropIt)
					{
						FProperty* Param = *PropIt;
						FString Flags;
						if (Param->HasAnyPropertyFlags(CPF_ReturnParm))  Flags += TEXT("return ");
						if (Param->HasAnyPropertyFlags(CPF_OutParm))     Flags += TEXT("out ");
						if (Param->HasAnyPropertyFlags(CPF_ReferenceParm)) Flags += TEXT("ref ");
						UE_LOG(LogTemp, Log,
							TEXT("  [%d] name='%s' cppType='%s' size=%d offset=%d flags=%s"),
							ParamIdx++,
							*Param->GetName(),
							*Param->GetCPPType(),
							Param->GetSize(),
							Param->GetOffset_ForUFunction(),
							*Flags);

						// Capture the out/return parameter (TArray, TMap, or TSet) so we can read it back after the call.
						if (Param->HasAnyPropertyFlags(CPF_ReturnParm | CPF_OutParm)
							&& (Param->IsA<FArrayProperty>() || Param->IsA<FMapProperty>() || Param->IsA<FSetProperty>()))
						{
							OutParamProp = Param;
						}
					}

					// Allocate a params buffer matching the function's parms size, zero it,
					// invoke ProcessEvent, then read the out container if we found one.
					if (GetCtrlFunc->ParmsSize > 0)
					{
						void* ParamsBuffer = FMemory_Alloca(GetCtrlFunc->ParmsSize);
						FMemory::Memzero(ParamsBuffer, GetCtrlFunc->ParmsSize);

						// Initialize each param in-place so containers have valid headers.
						for (TFieldIterator<FProperty> PropIt(GetCtrlFunc); PropIt; ++PropIt)
						{
							PropIt->InitializeValue_InContainer(ParamsBuffer);
						}

						CachedFaceAnimInstance->ProcessEvent(GetCtrlFunc, ParamsBuffer);

						if (OutParamProp)
						{
							// TMap return — log key=value pairs (the keys are the valid control names).
							if (FMapProperty* MapProp = CastField<FMapProperty>(OutParamProp))
							{
								FScriptMapHelper Helper(MapProp, MapProp->ContainerPtrToValuePtr<void>(ParamsBuffer));
								const int32 Count = Helper.Num();
								UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: GetCustomControls returned TMap with %d entries:"), Count);
								int32 Logged = 0;
								for (int32 i = 0; Logged < Count && i < Helper.GetMaxIndex(); ++i)
								{
									if (!Helper.IsValidIndex(i)) continue;
									FString KeyStr, ValueStr;
									MapProp->KeyProp  ->ExportTextItem_Direct(KeyStr,   Helper.GetKeyPtr(i),   nullptr, nullptr, PPF_None);
									MapProp->ValueProp->ExportTextItem_Direct(ValueStr, Helper.GetValuePtr(i), nullptr, nullptr, PPF_None);
									UE_LOG(LogTemp, Log, TEXT("  [%d] key='%s' value=%s"), Logged, *KeyStr, *ValueStr);
									++Logged;
								}
							}
							// TArray return — log entries.
							else if (FArrayProperty* ArrProp = CastField<FArrayProperty>(OutParamProp))
							{
								FScriptArrayHelper Helper(ArrProp, ArrProp->ContainerPtrToValuePtr<void>(ParamsBuffer));
								const int32 Count = Helper.Num();
								UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: GetCustomControls returned TArray with %d entries:"), Count);
								for (int32 i = 0; i < Count; ++i)
								{
									FString EntryStr;
									ArrProp->Inner->ExportTextItem_Direct(EntryStr, Helper.GetRawPtr(i), nullptr, nullptr, PPF_None);
									UE_LOG(LogTemp, Log, TEXT("  [%d] %s"), i, *EntryStr);
								}
							}
						}

						// Destroy the params we initialized so we don't leak container allocations.
						for (TFieldIterator<FProperty> PropIt(GetCtrlFunc); PropIt; ++PropIt)
						{
							PropIt->DestroyValue_InContainer(ParamsBuffer);
						}
					}
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("MetahumanAnim: GetCustomControls not found — cannot enumerate valid curve names"));
				}

				// DIAGNOSTIC: GetCustomControls only returns the *currently set* curves
				// (a runtime cache), not the list of valid names. Set Control internally
				// validates the requested name against UAnimInstance::GetAllCurveNames(),
				// so that's the authoritative list. Call it directly via reflection.
				if (UFunction* GetAllCurvesFunc = CachedFaceAnimInstance->FindFunction(FName("GetAllCurveNames")))
				{
					UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: === GetAllCurveNames signature ==="));
					int32 ParamIdx = 0;
					FProperty* OutArrayProp = nullptr;
					for (TFieldIterator<FProperty> PropIt(GetAllCurvesFunc); PropIt; ++PropIt)
					{
						FProperty* Param = *PropIt;
						FString Flags;
						if (Param->HasAnyPropertyFlags(CPF_ReturnParm))    Flags += TEXT("return ");
						if (Param->HasAnyPropertyFlags(CPF_OutParm))       Flags += TEXT("out ");
						if (Param->HasAnyPropertyFlags(CPF_ReferenceParm)) Flags += TEXT("ref ");
						UE_LOG(LogTemp, Log,
							TEXT("  [%d] name='%s' cppType='%s' size=%d offset=%d flags=%s"),
							ParamIdx++,
							*Param->GetName(),
							*Param->GetCPPType(),
							Param->GetSize(),
							Param->GetOffset_ForUFunction(),
							*Flags);

						if (Param->HasAnyPropertyFlags(CPF_ReturnParm | CPF_OutParm)
							&& Param->IsA<FArrayProperty>())
						{
							OutArrayProp = Param;
						}
					}

					if (GetAllCurvesFunc->ParmsSize > 0)
					{
						void* ParamsBuffer = FMemory_Alloca(GetAllCurvesFunc->ParmsSize);
						FMemory::Memzero(ParamsBuffer, GetAllCurvesFunc->ParmsSize);
						for (TFieldIterator<FProperty> PropIt(GetAllCurvesFunc); PropIt; ++PropIt)
						{
							PropIt->InitializeValue_InContainer(ParamsBuffer);
						}

						CachedFaceAnimInstance->ProcessEvent(GetAllCurvesFunc, ParamsBuffer);

						if (FArrayProperty* ArrProp = CastField<FArrayProperty>(OutArrayProp))
						{
							FScriptArrayHelper Helper(ArrProp, ArrProp->ContainerPtrToValuePtr<void>(ParamsBuffer));
							const int32 Count = Helper.Num();
							UE_LOG(LogTemp, Log, TEXT("MetahumanAnim: GetAllCurveNames returned %d entries:"), Count);
							for (int32 i = 0; i < Count; ++i)
							{
								FString EntryStr;
								ArrProp->Inner->ExportTextItem_Direct(EntryStr, Helper.GetRawPtr(i), nullptr, nullptr, PPF_None);
								UE_LOG(LogTemp, Log, TEXT("  [%d] %s"), i, *EntryStr);
							}
						}

						for (TFieldIterator<FProperty> PropIt(GetAllCurvesFunc); PropIt; ++PropIt)
						{
							PropIt->DestroyValue_InContainer(ParamsBuffer);
						}
					}
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("MetahumanAnim: GetAllCurveNames not found on Face AnimInstance"));
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

	// Subscribe to the voice pipeline for the thinking-pose feature.
	// IMPORTANT: use FindComponentByClass, matching UNPCLipSyncComponent's
	// discovery path — ANPCCharacter has two UElevenLabsTTSComponent
	// subobjects (pre-existing quirk), and we must subscribe to the same
	// instance lip sync hooks, otherwise our events won't correlate with it.
	if (AActor* Owner = GetOwner())
	{
		CachedSTT = Owner->FindComponentByClass<UWhisperSTTComponent>();
		if (CachedSTT.IsValid())
		{
			CachedSTT->OnTranscriptReady.AddDynamic(
				this, &UMetahumanAnimComponent::HandleTranscriptReady);
		}

		CachedTTS = Owner->FindComponentByClass<UElevenLabsTTSComponent>();
		if (CachedTTS.IsValid())
		{
			CachedTTS->OnTTSAlignmentReceived.AddDynamic(
				this, &UMetahumanAnimComponent::HandleTTSAlignmentReceived);
			CachedTTS->OnSpeechStarted.AddDynamic(
				this, &UMetahumanAnimComponent::HandleSpeechStarted);
			CachedTTS->OnSpeechFinished.AddDynamic(
				this, &UMetahumanAnimComponent::HandleSpeechFinished);
			CachedTTS->OnSpeechError.AddDynamic(
				this, &UMetahumanAnimComponent::HandleSpeechError);
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
	if (!CachedFaceAnimInstance || !CachedSetControlFunc)
	{
		// DIAGNOSTIC: log ONCE per component instance if SetFaceControl is
		// called while the reflection bridge is broken, so we know that the
		// specific component the LipSync is pushing to has stale init state.
		static TSet<const UMetahumanAnimComponent*> LoggedNullComponents;
		if (!LoggedNullComponents.Contains(this))
		{
			LoggedNullComponents.Add(this);
			UE_LOG(LogTemp, Warning,
				TEXT("MetahumanAnim.SetFaceControl: NO-OP on component %p — FaceAnimInstance=%s, SetControlFunc=%s (first attempted curve='%s')"),
				this,
				CachedFaceAnimInstance ? TEXT("VALID") : TEXT("NULL"),
				CachedSetControlFunc   ? TEXT("VALID") : TEXT("NULL"),
				*ControlName.ToString());
		}
		return;
	}

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

void UMetahumanAnimComponent::SetVisemeCurves(const TMap<FName, float>& Curves)
{
	// DIAGNOSTIC: log the first time SetVisemeCurves is called with a non-empty
	// map, including the cached reflection pointer state at that moment.
	static bool bLoggedFirstCall = false;
	if (!bLoggedFirstCall && Curves.Num() > 0)
	{
		bLoggedFirstCall = true;
		UE_LOG(LogTemp, Log,
			TEXT("MetahumanAnim.SetVisemeCurves: FIRST call — NumCurves=%d, FaceAnimInstance=%s, SetControlFunc=%s, FaceAnimClass=%s"),
			Curves.Num(),
			CachedFaceAnimInstance ? TEXT("VALID") : TEXT("NULL"),
			CachedSetControlFunc   ? TEXT("VALID") : TEXT("NULL"),
			CachedFaceAnimInstance ? *CachedFaceAnimInstance->GetClass()->GetName() : TEXT("n/a"));
	}

	// Zero any curve that was active last time but is absent from this call —
	// otherwise stale viseme weights linger on the face.
	for (const FName& Name : ActiveVisemeCurveNames)
	{
		if (!Curves.Contains(Name))
		{
			SetFaceControl(Name, 0.0f);
			ActiveCurveValues.Remove(Name);
		}
	}

	ActiveVisemeCurveNames.Reset();

	// Push the new curves. These override any emotion-driven values for the
	// same curve names while speaking — the emotion decay loop in
	// TickComponent skips names in ActiveVisemeCurveNames.
	float VisemeJawOpen = 0.0f;
	for (const TPair<FName, float>& Pair : Curves)
	{
		const float ClampedValue = FMath::Clamp(Pair.Value, 0.0f, 1.0f);
		SetFaceControl(Pair.Key, ClampedValue);
		ActiveCurveValues.Add(Pair.Key, ClampedValue);
		ActiveVisemeCurveNames.Add(Pair.Key);

		// Track the jawOpen value so we can drive the proven-working
		// JawOpenAlpha property directly — the stock MetaHuman Face AnimBP
		// gates jaw-related lip-sync blending through that property, so
		// leaving it at 0 hides every viseme mouth movement we push.
		// (We push CTRL_expressions_jawOpen via Set Control above too, as a
		// belt-and-suspenders — both paths cooperate.)
		if (Pair.Key == FName("CTRL_expressions_jawOpen"))
		{
			VisemeJawOpen = ClampedValue;
		}
	}

	// Mirror the viseme jawOpen value into JawOpenAlpha (direct property write,
	// bypasses the legacy Tick interpolation loop) and keep LipSyncJawOpenValue
	// in sync so the Tick loop won't fight us back toward 0 on the next frame.
	LipSyncJawOpenValue  = VisemeJawOpen;
	CurrentJawOpenValue  = VisemeJawOpen;
	SetJawOpenAlpha(VisemeJawOpen);
}

void UMetahumanAnimComponent::ShutdownSubsystem()
{
	// Detach voice pipeline delegates.
	if (CachedSTT.IsValid())
	{
		CachedSTT->OnTranscriptReady.RemoveDynamic(
			this, &UMetahumanAnimComponent::HandleTranscriptReady);
	}
	if (CachedTTS.IsValid())
	{
		CachedTTS->OnTTSAlignmentReceived.RemoveDynamic(
			this, &UMetahumanAnimComponent::HandleTTSAlignmentReceived);
		CachedTTS->OnSpeechStarted.RemoveDynamic(
			this, &UMetahumanAnimComponent::HandleSpeechStarted);
		CachedTTS->OnSpeechFinished.RemoveDynamic(
			this, &UMetahumanAnimComponent::HandleSpeechFinished);
		CachedTTS->OnSpeechError.RemoveDynamic(
			this, &UMetahumanAnimComponent::HandleSpeechError);
	}

	bIsThinking   = false;
	ThinkingTimer = 0.0f;

	// Reset all controls, including any viseme-owned curves.
	for (const auto& ActivePair : ActiveCurveValues)
	{
		SetFaceControl(ActivePair.Key, 0.0f);
	}
	ActiveCurveValues.Empty();
	ActiveVisemeCurveNames.Empty();
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

	// Look up emotion curves. When bUseCurveBasedEmotions is false, the
	// MetaHuman template animations (driven by UTemplateAnimationDriverComponent)
	// carry the emotional expression — running the curve path here would
	// double-drive and fight the template. We still build the (empty) TargetCurves
	// so the decay loop below can zero any residual curves from a previous frame
	// when the flag flipped or emotion decayed.
	if (bUseCurveBasedEmotions)
	{
		if (const auto* Curves = EmotionCurveMappings.Find(CurrentEmotion))
		{
			for (const auto& Pair : *Curves)
			{
				TargetCurves.Add(Pair.Key, Pair.Value * Intensity);
			}
		}
	}

	// Watchdog: auto-clear thinking if nothing downstream fired the clear
	// event. Covers DialogueComponent silent-error paths and TTS create-sound
	// failures, where no OnSpeech* event ever fires to reset the flag.
	if (bIsThinking)
	{
		ThinkingTimer += DeltaTime;
		if (ThinkingTimer >= ThinkingTimeoutSeconds)
		{
			UE_LOG(LogTemp, Warning,
				TEXT("MetahumanAnim: Thinking watchdog tripped after %.1fs — clearing."),
				ThinkingTimer);
			SetThinkingActive(false);
		}
	}

	// Merge the thinking pose on top of the emotion target. Max preserves
	// stronger existing values on shared curves (e.g. Sadness already drives
	// browInnerUp to 0.5 — don't shrink it to 0.25). Thinking-only curves
	// get added fresh. The existing FInterpTo loops below handle blend-in
	// and blend-out automatically.
	if (bIsThinking)
	{
		for (const TPair<FName, float>& Pair : ThinkingCurves)
		{
			float& Target = TargetCurves.FindOrAdd(Pair.Key, 0.0f);
			Target = FMath::Max(Target, Pair.Value);
		}
	}

	// Smoothly interpolate and apply all active curves.
	// First, decay curves that are no longer targeted — but skip curves that
	// the viseme lip sync is currently driving, otherwise this loop would
	// interpolate them back toward zero between each lip sync push.
	TArray<FName> ToRemove;
	for (auto& Pair : ActiveCurveValues)
	{
		if (ActiveVisemeCurveNames.Contains(Pair.Key))
		{
			continue;
		}
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

	// Interpolate toward target values — again, viseme-owned curves are
	// authoritative and must not be clobbered by the emotion mapping.
	for (const auto& Pair : TargetCurves)
	{
		if (ActiveVisemeCurveNames.Contains(Pair.Key))
		{
			continue;
		}
		float& Current = ActiveCurveValues.FindOrAdd(Pair.Key, 0.0f);
		Current = FMath::FInterpTo(Current, Pair.Value, DeltaTime, InterpolationSpeed);
		SetFaceControl(Pair.Key, Current);
	}

	// Lip sync — drive JawOpenAlpha.
	// When the viseme lip sync is actively pushing curves, SetVisemeCurves has
	// already written the authoritative JawOpenAlpha value for this frame, so
	// we skip the legacy interpolation path entirely to avoid fighting it.
	if (!ActiveVisemeCurveNames.Contains(FName("CTRL_expressions_jawOpen")))
	{
		float JawTarget = LipSyncJawOpenValue;

		// Emotion jaw open (for surprise, etc.) takes max with lip sync.
		// Gated on bUseCurveBasedEmotions: when templates drive emotion,
		// the Surprise template already opens the jaw visually and an
		// additional curve write here stacks on top and looks exaggerated.
		if (bUseCurveBasedEmotions)
		{
			if (CurrentEmotion == EEmotionType::Surprise)
			{
				JawTarget = FMath::Max(JawTarget, 0.5f * Intensity);
			}
		}

		CurrentJawOpenValue = FMath::FInterpTo(CurrentJawOpenValue, JawTarget, DeltaTime, LipSyncInterpolationSpeed);
		SetJawOpenAlpha(CurrentJawOpenValue);
	}

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

void UMetahumanAnimComponent::SetThinkingActive(bool bActive)
{
	if (bIsThinking == bActive)
	{
		return;
	}
	bIsThinking   = bActive;
	ThinkingTimer = 0.0f;
	UE_LOG(LogTemp, Verbose, TEXT("MetahumanAnim: Thinking=%d"), bActive ? 1 : 0);
}

void UMetahumanAnimComponent::HandleTranscriptReady(const FString& /*Transcript*/)
{
	SetThinkingActive(true);
}

void UMetahumanAnimComponent::HandleTTSAlignmentReceived(
	const FString& /*Characters*/,
	const TArray<float>& /*StartTimesSec*/,
	const TArray<float>& /*DurationsSec*/)
{
	SetThinkingActive(false);
}

void UMetahumanAnimComponent::HandleSpeechStarted()
{
	SetThinkingActive(false);
}

void UMetahumanAnimComponent::HandleSpeechFinished()
{
	SetThinkingActive(false);
}

void UMetahumanAnimComponent::HandleSpeechError(int32 ResponseCode, const FString& ErrorBody)
{
	UE_LOG(LogTemp, Warning,
		TEXT("MetahumanAnim: HandleSpeechError — code=%d, body=%s — clearing thinking."),
		ResponseCode, *ErrorBody);
	SetThinkingActive(false);
}
