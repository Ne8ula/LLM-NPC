#include "ObjectInspectWidget.h"
#include "InspectableItem.h"

DEFINE_LOG_CATEGORY_STATIC(LogObjectInspect, Log, All);

UObjectInspectWidget::UObjectInspectWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UObjectInspectWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UObjectInspectWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// The inspectable item handles its own smooth interpolation in its Tick,
	// so no additional work is needed here beyond what the widget itself renders.
}

void UObjectInspectWidget::SetInspectItem(AInspectableItem* Item)
{
	if (CurrentItem == Item)
	{
		return;
	}

	// Reset previous item if any
	if (CurrentItem)
	{
		CurrentItem->ResetTransform();
	}

	CurrentItem = Item;

	if (CurrentItem)
	{
		UE_LOG(LogObjectInspect, Log, TEXT("Inspecting item: %s"), *CurrentItem->GetName());
	}
	else
	{
		UE_LOG(LogObjectInspect, Log, TEXT("Cleared inspect item."));
	}
}

void UObjectInspectWidget::ApplyGestureInput(const FGestureInput& Input)
{
	if (!CurrentItem)
	{
		return;
	}

	switch (Input.GestureType)
	{
	case EGestureType::Pinch:
		// Pinch -> scale down
		CurrentItem->ApplyScale(-FMath::Abs(Input.Delta) * GestureScaleSensitivity);
		break;

	case EGestureType::Spread:
		// Spread -> scale up
		CurrentItem->ApplyScale(FMath::Abs(Input.Delta) * GestureScaleSensitivity);
		break;

	case EGestureType::Rotate:
	{
		// Rotate around the up axis
		const float RotationDegrees = Input.Delta * GestureRotationSensitivity;
		CurrentItem->ApplyRotation(FRotator(0.0f, RotationDegrees, 0.0f));
		break;
	}

	case EGestureType::Spindle:
	{
		// Spindle (two-hand): combined scale and rotation
		CurrentItem->ApplyScale(Input.Delta * GestureScaleSensitivity);
		break;
	}

	case EGestureType::None:
	default:
		break;
	}
}

void UObjectInspectWidget::ApplyMouseInput(FVector2D MouseDelta, float ScrollDelta)
{
	if (!CurrentItem)
	{
		return;
	}

	// Mouse drag -> rotation (X = yaw, Y = pitch)
	if (!MouseDelta.IsNearlyZero())
	{
		const float Yaw = MouseDelta.X * MouseRotationSensitivity;
		const float Pitch = MouseDelta.Y * MouseRotationSensitivity;
		CurrentItem->ApplyRotation(FRotator(Pitch, Yaw, 0.0f));
	}

	// Scroll wheel -> scale
	if (!FMath::IsNearlyZero(ScrollDelta))
	{
		CurrentItem->ApplyScale(ScrollDelta * ScrollScaleSensitivity);
	}
}
