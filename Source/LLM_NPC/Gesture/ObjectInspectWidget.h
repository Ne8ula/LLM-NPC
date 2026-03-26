#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LLM_NPC/Core/NPCTypes.h"
#include "ObjectInspectWidget.generated.h"

class AInspectableItem;

/**
 * Widget providing a 3D viewport for inspecting objects.
 * Features a 3D Bubble Cursor (semi-transparent selection sphere indicator).
 * Accepts gesture input (pinch/spread/rotate) or traditional keyboard/mouse input
 * for manipulating the inspected object.
 */
UCLASS()
class FLLM_NPC_API UObjectInspectWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UObjectInspectWidget(const FObjectInitializer& ObjectInitializer);

	/**
	 * Set the item to inspect in the 3D viewport.
	 * @param Item  The inspectable actor to display.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Gesture|Inspect")
	void SetInspectItem(AInspectableItem* Item);

	/**
	 * Apply gesture-based input to the inspected item.
	 * Pinch -> scale down, Spread -> scale up, Rotate -> rotate.
	 * @param Input  The detected gesture input.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Gesture|Inspect")
	void ApplyGestureInput(const FGestureInput& Input);

	/**
	 * Apply mouse/keyboard input to the inspected item.
	 * Mouse drag rotates, scroll wheel scales.
	 * @param MouseDelta  Mouse movement delta (X = yaw, Y = pitch).
	 * @param ScrollDelta Scroll wheel delta (positive = scale up).
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Gesture|Inspect")
	void ApplyMouseInput(FVector2D MouseDelta, float ScrollDelta);

	/** Get the currently inspected item. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Gesture|Inspect")
	AInspectableItem* GetInspectItem() const { return CurrentItem; }

	/** Whether an item is currently being inspected. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Gesture|Inspect")
	bool HasInspectItem() const { return CurrentItem != nullptr; }

	// ------------------------------------------------------------------
	// Bubble Cursor settings
	// ------------------------------------------------------------------

	/** Radius of the 3D Bubble Cursor selection sphere. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Gesture|BubbleCursor")
	float BubbleCursorRadius = 50.0f;

	/** Color of the Bubble Cursor sphere indicator. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Gesture|BubbleCursor")
	FLinearColor BubbleCursorColor = FLinearColor(0.2f, 0.6f, 1.0f, 0.3f);

	/** Whether the Bubble Cursor is visible. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Gesture|BubbleCursor")
	bool bShowBubbleCursor = true;

	// ------------------------------------------------------------------
	// Input mapping sensitivity
	// ------------------------------------------------------------------

	/** Scale sensitivity for gesture-based scaling. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Gesture|Inspect")
	float GestureScaleSensitivity = 2.0f;

	/** Rotation sensitivity for gesture-based rotation (degrees per unit). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Gesture|Inspect")
	float GestureRotationSensitivity = 45.0f;

	/** Scale sensitivity for scroll wheel. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Gesture|Inspect")
	float ScrollScaleSensitivity = 0.1f;

	/** Rotation sensitivity for mouse drag (degrees per pixel). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Gesture|Inspect")
	float MouseRotationSensitivity = 0.5f;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	/** The item currently being inspected. */
	UPROPERTY()
	TObjectPtr<AInspectableItem> CurrentItem;
};
