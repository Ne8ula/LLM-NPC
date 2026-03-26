using UnrealBuildTool;
using System.IO;

public class LLM_NPC : ModuleRules
{
	public LLM_NPC(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		bEnableExceptions = true;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"HTTP",
			"Json",
			"JsonUtilities",
			"AudioCapture",
			"AudioMixer",
			"UMG",
			"SlateCore",
			"Slate",
			"AIModule"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"RenderCore",
			"RHI"
		});

		// Third-party library paths
		string ThirdPartyPath = Path.Combine(ModuleDirectory, "../../ThirdParty");

		// whisper.cpp - Local speech-to-text
		// Uses prebuilt DLL from whisper.cpp releases (whisper.dll + whisper.h)
		string WhisperPath = Path.Combine(ThirdPartyPath, "whisper.cpp");
		PublicIncludePaths.Add(Path.Combine(WhisperPath, "include"));
		string WhisperLibPath = Path.Combine(WhisperPath, "lib");

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// If whisper.lib exists (generated from DLL or from source build), link it
			string WhisperLib = Path.Combine(WhisperLibPath, "whisper.lib");
			if (File.Exists(WhisperLib))
			{
				PublicAdditionalLibraries.Add(WhisperLib);
			}
			PublicDelayLoadDLLs.Add("whisper.dll");
			RuntimeDependencies.Add(Path.Combine(WhisperLibPath, "whisper.dll"));
		}
		else
		{
			PublicAdditionalLibraries.Add(Path.Combine(WhisperLibPath, GetPlatformLibName("whisper")));
		}

		// OpenCV 4.x - Camera capture, face detection, preprocessing
		string OpenCVPath = Path.Combine(ThirdPartyPath, "OpenCV");
		PublicIncludePaths.Add(Path.Combine(OpenCVPath, "include"));
		string OpenCVLibPath = Path.Combine(OpenCVPath, "lib");

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PublicAdditionalLibraries.Add(Path.Combine(OpenCVLibPath, "opencv_world4120.lib"));
			PublicDelayLoadDLLs.Add("opencv_world4120.dll");
			RuntimeDependencies.Add(Path.Combine(OpenCVLibPath, "opencv_world4120.dll"));
		}
		else if (Target.Platform == UnrealTargetPlatform.Linux)
		{
			PublicAdditionalLibraries.Add(Path.Combine(OpenCVLibPath, "libopencv_world.so"));
			RuntimeDependencies.Add(Path.Combine(OpenCVLibPath, "libopencv_world.so"));
		}
		else if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			PublicAdditionalLibraries.Add(Path.Combine(OpenCVLibPath, "libopencv_world.dylib"));
			RuntimeDependencies.Add(Path.Combine(OpenCVLibPath, "libopencv_world.dylib"));
		}

		// ONNX Runtime - ML model inference
		string ONNXPath = Path.Combine(ThirdPartyPath, "ONNXRuntime");
		PublicIncludePaths.Add(Path.Combine(ONNXPath, "include"));
		string ONNXLibPath = Path.Combine(ONNXPath, "lib");

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PublicAdditionalLibraries.Add(Path.Combine(ONNXLibPath, "onnxruntime.lib"));
			PublicDelayLoadDLLs.Add("onnxruntime.dll");
			RuntimeDependencies.Add(Path.Combine(ONNXLibPath, "onnxruntime.dll"));
		}
		else if (Target.Platform == UnrealTargetPlatform.Linux)
		{
			PublicAdditionalLibraries.Add(Path.Combine(ONNXLibPath, "libonnxruntime.so"));
			RuntimeDependencies.Add(Path.Combine(ONNXLibPath, "libonnxruntime.so"));
		}
		else if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			PublicAdditionalLibraries.Add(Path.Combine(ONNXLibPath, "libonnxruntime.dylib"));
			RuntimeDependencies.Add(Path.Combine(ONNXLibPath, "libonnxruntime.dylib"));
		}

		// Only enable third-party integrations if the libraries are actually present
		bool bHasOpenCV = File.Exists(Path.Combine(OpenCVPath, "include", "opencv2", "opencv.hpp"))
			|| File.Exists(Path.Combine(OpenCVPath, "include", "opencv2", "core.hpp"));
		bool bHasONNX = File.Exists(Path.Combine(ONNXPath, "include", "onnxruntime_cxx_api.h"));
		bool bHasWhisper = File.Exists(Path.Combine(WhisperPath, "include", "whisper.h"))
			&& File.Exists(Path.Combine(WhisperPath, "include", "ggml.h"));

		PublicDefinitions.Add(string.Format("WITH_OPENCV={0}", bHasOpenCV ? "1" : "0"));
		PublicDefinitions.Add(string.Format("WITH_ONNXRUNTIME={0}", bHasONNX ? "1" : "0"));
		PublicDefinitions.Add(string.Format("WITH_WHISPER={0}", bHasWhisper ? "1" : "0"));

		System.Console.WriteLine("LLM_NPC ThirdParty: OpenCV={0}, ONNX={1}, Whisper={2}", bHasOpenCV, bHasONNX, bHasWhisper);
	}

	private string GetPlatformLibName(string BaseName)
	{
		if (Target.Platform == UnrealTargetPlatform.Win64)
			return BaseName + ".lib";
		else if (Target.Platform == UnrealTargetPlatform.Linux)
			return "lib" + BaseName + ".a";
		else if (Target.Platform == UnrealTargetPlatform.Mac)
			return "lib" + BaseName + ".a";
		return BaseName;
	}
}
