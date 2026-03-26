#include "CameraManagerSubsystem.h"
#include "HAL/PlatformProcess.h"

#if WITH_OPENCV
#include "PreOpenCVHeaders.h"
#include "opencv2/videoio.hpp"
#include "PostOpenCVHeaders.h"
#endif

DEFINE_LOG_CATEGORY_STATIC(LogCameraManager, Log, All);

// ---------------------------------------------------------------------------
// UCameraManagerSubsystem
// ---------------------------------------------------------------------------

UCameraManagerSubsystem::UCameraManagerSubsystem()
	: bIsCameraOpen(false)
{
}

void UCameraManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogCameraManager, Log, TEXT("CameraManagerSubsystem initialized."));
}

void UCameraManagerSubsystem::Deinitialize()
{
	StopCapture();
	Super::Deinitialize();
	UE_LOG(LogCameraManager, Log, TEXT("CameraManagerSubsystem deinitialized."));
}

bool UCameraManagerSubsystem::StartCapture(int32 CameraIndex)
{
	if (bIsCameraOpen)
	{
		UE_LOG(LogCameraManager, Warning, TEXT("Capture already running. Stop first before restarting."));
		return true;
	}

	CaptureRunnable = MakeUnique<FCaptureRunnable>(this, CameraIndex);
	CaptureThread = TUniquePtr<FRunnableThread>(
		FRunnableThread::Create(CaptureRunnable.Get(), TEXT("CameraCapture"), 0, TPri_BelowNormal));

	if (!CaptureThread.IsValid())
	{
		UE_LOG(LogCameraManager, Error, TEXT("Failed to create camera capture thread."));
		CaptureRunnable.Reset();
		return false;
	}

	// Allow a brief moment for Init() to run and set bIsCameraOpen.
	FPlatformProcess::Sleep(0.2f);
	return bIsCameraOpen;
}

void UCameraManagerSubsystem::StopCapture()
{
	if (CaptureRunnable.IsValid())
	{
		CaptureRunnable.Reset(); // destructor triggers Stop via thread kill
	}
	if (CaptureThread.IsValid())
	{
		CaptureThread->Kill(true);
		CaptureThread.Reset();
	}

	FScopeLock Lock(&BufferCriticalSection);
	bHasValidFrame = false;
	ReadBuffer.Empty();
	ReadWidth = 0;
	ReadHeight = 0;
	bIsCameraOpen = false;

	UE_LOG(LogCameraManager, Log, TEXT("Camera capture stopped."));
}

bool UCameraManagerSubsystem::GetLatestFrame(TArray<uint8>& OutFrameData, int32& OutWidth, int32& OutHeight)
{
	FScopeLock Lock(&BufferCriticalSection);
	if (!bHasValidFrame)
	{
		return false;
	}

	OutFrameData = ReadBuffer;
	OutWidth = ReadWidth;
	OutHeight = ReadHeight;
	return true;
}

bool UCameraManagerSubsystem::IsCameraAvailable() const
{
	return bIsCameraOpen;
}

void UCameraManagerSubsystem::SwapBuffers(const TArray<uint8>& NewFrameData, int32 NewWidth, int32 NewHeight)
{
	FScopeLock Lock(&BufferCriticalSection);
	ReadBuffer = NewFrameData;
	ReadWidth = NewWidth;
	ReadHeight = NewHeight;
	bHasValidFrame = true;
}

// ---------------------------------------------------------------------------
// FCaptureRunnable
// ---------------------------------------------------------------------------

UCameraManagerSubsystem::FCaptureRunnable::FCaptureRunnable(UCameraManagerSubsystem* InOwner, int32 InCameraIndex)
	: Owner(InOwner)
	, CameraIndex(InCameraIndex)
	, bShouldStop(false)
{
}

bool UCameraManagerSubsystem::FCaptureRunnable::Init()
{
	return true;
}

uint32 UCameraManagerSubsystem::FCaptureRunnable::Run()
{
#if WITH_OPENCV
	cv::VideoCapture Capture;
	if (!Capture.open(CameraIndex))
	{
		UE_LOG(LogCameraManager, Error, TEXT("Failed to open camera at index %d"), CameraIndex);
		return 1;
	}

	Owner->bIsCameraOpen = true;
	UE_LOG(LogCameraManager, Log, TEXT("Camera opened at index %d"), CameraIndex);

	const double FrameInterval = 1.0 / static_cast<double>(FMath::Max(1, Owner->TargetFPS));
	cv::Mat Frame;

	while (!bShouldStop)
	{
		const double StartTime = FPlatformTime::Seconds();

		if (Capture.read(Frame) && !Frame.empty())
		{
			const int32 Width = Frame.cols;
			const int32 Height = Frame.rows;
			const int32 DataSize = Width * Height * Frame.channels();

			TArray<uint8> FrameData;
			FrameData.SetNumUninitialized(DataSize);
			FMemory::Memcpy(FrameData.GetData(), Frame.data, DataSize);

			Owner->SwapBuffers(FrameData, Width, Height);
		}

		const double Elapsed = FPlatformTime::Seconds() - StartTime;
		const double SleepTime = FrameInterval - Elapsed;
		if (SleepTime > 0.0)
		{
			FPlatformProcess::Sleep(static_cast<float>(SleepTime));
		}
	}

	Capture.release();
	Owner->bIsCameraOpen = false;
	UE_LOG(LogCameraManager, Log, TEXT("Camera capture thread exiting."));
#else
	UE_LOG(LogCameraManager, Warning, TEXT("OpenCV not available. Camera capture disabled."));
#endif

	return 0;
}

void UCameraManagerSubsystem::FCaptureRunnable::Stop()
{
	bShouldStop = true;
}
