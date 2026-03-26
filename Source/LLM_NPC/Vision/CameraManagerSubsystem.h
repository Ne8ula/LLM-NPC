#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"
#include "HAL/CriticalSection.h"
#include "CameraManagerSubsystem.generated.h"

/**
 * Shared camera manager subsystem providing double-buffered frame access.
 * A background FRunnable thread captures frames from OpenCV VideoCapture,
 * while reader threads (face tracking, hand tracking) read the latest frame
 * through a thread-safe interface.
 */
UCLASS()
class LLM_NPC_API UCameraManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UCameraManagerSubsystem();

	// USubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/**
	 * Start capturing from the given camera device index.
	 * Spawns the background capture thread.
	 * @param CameraIndex  OS camera device index (default 0).
	 * @return true if the camera was opened successfully.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Vision")
	bool StartCapture(int32 CameraIndex = 0);

	/** Stop capturing and release the camera device. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Vision")
	void StopCapture();

	/**
	 * Get the most recently captured frame (thread-safe read from double buffer).
	 * @param OutFrameData  Raw BGR pixel data.
	 * @param OutWidth      Frame width in pixels.
	 * @param OutHeight     Frame height in pixels.
	 * @return true if a valid frame was available.
	 */
	UFUNCTION(BlueprintCallable, Category = "NPC|Vision")
	bool GetLatestFrame(TArray<uint8>& OutFrameData, int32& OutWidth, int32& OutHeight);

	/** Check if the camera is opened and actively capturing. */
	UFUNCTION(BlueprintCallable, Category = "NPC|Vision")
	bool IsCameraAvailable() const;

	/** Target capture frame rate (default 15 FPS). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Vision", meta = (ClampMin = "1", ClampMax = "60"))
	int32 TargetFPS = 15;

private:
	/** Background capture thread implementation. */
	class FCaptureRunnable : public FRunnable
	{
	public:
		FCaptureRunnable(UCameraManagerSubsystem* InOwner, int32 InCameraIndex);

		// FRunnable interface
		virtual bool Init() override;
		virtual uint32 Run() override;
		virtual void Stop() override;

	private:
		UCameraManagerSubsystem* Owner;
		int32 CameraIndex;
		FThreadSafeBool bShouldStop;
	};

	/** Swap the write buffer into the read buffer (called by capture thread). */
	void SwapBuffers(const TArray<uint8>& NewFrameData, int32 NewWidth, int32 NewHeight);

	/** Critical section protecting the read buffer. */
	mutable FCriticalSection BufferCriticalSection;

	/** Double-buffered frame data: the read buffer is accessed by consumers. */
	TArray<uint8> ReadBuffer;
	int32 ReadWidth = 0;
	int32 ReadHeight = 0;
	bool bHasValidFrame = false;

	/** Background capture thread. */
	TUniquePtr<FRunnableThread> CaptureThread;
	TUniquePtr<FCaptureRunnable> CaptureRunnable;

	/** Whether the camera is currently open. */
	FThreadSafeBool bIsCameraOpen;
};
