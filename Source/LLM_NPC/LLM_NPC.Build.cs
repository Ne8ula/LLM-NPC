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
			"AIModule",
			"EnhancedInput"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"RenderCore",
			"RHI"
		});

		// Third-party library paths
		string ThirdPartyPath = Path.Combine(ModuleDirectory, "../../ThirdParty");

		string WhisperPath = Path.Combine(ThirdPartyPath, "whisper.cpp");
		string WhisperLibPath = Path.Combine(WhisperPath, "lib");

		string OpenCVPath = Path.Combine(ThirdPartyPath, "OpenCV");
		string OpenCVLibPath = Path.Combine(OpenCVPath, "lib");

		string ONNXPath = Path.Combine(ThirdPartyPath, "ONNXRuntime");
		string ONNXLibPath = Path.Combine(ONNXPath, "lib");

		// Detect which third-party libraries are actually present
		bool bHasWhisper = File.Exists(Path.Combine(WhisperPath, "include", "whisper.h"));
		bool bHasOpenCV = File.Exists(Path.Combine(OpenCVPath, "include", "opencv2", "core.hpp"))
			|| File.Exists(Path.Combine(OpenCVPath, "include", "opencv2", "opencv.hpp"));
		bool bHasONNX = File.Exists(Path.Combine(ONNXPath, "include", "onnxruntime_cxx_api.h"));

		System.Console.WriteLine("LLM_NPC ThirdParty: Whisper={0}, OpenCV={1}, ONNX={2}", bHasWhisper, bHasOpenCV, bHasONNX);

		// --- whisper.cpp (only if fully present) ---
		if (bHasWhisper)
		{
			PublicIncludePaths.Add(Path.Combine(WhisperPath, "include"));

			if (Target.Platform == UnrealTargetPlatform.Win64)
			{
				string WhisperLib = Path.Combine(WhisperLibPath, "whisper.lib");
				if (File.Exists(WhisperLib))
				{
					PublicAdditionalLibraries.Add(WhisperLib);
				}
				string WhisperDll = Path.Combine(WhisperLibPath, "whisper.dll");
				if (File.Exists(WhisperDll))
				{
					PublicDelayLoadDLLs.Add("whisper.dll");
					RuntimeDependencies.Add(WhisperDll);
				}
			}
		}

		// --- OpenCV 4.x ---
		if (bHasOpenCV)
		{
			PublicIncludePaths.Add(Path.Combine(OpenCVPath, "include"));

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
		}

		// --- ONNX Runtime ---
		if (bHasONNX)
		{
			PublicIncludePaths.Add(Path.Combine(ONNXPath, "include"));

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
		}

		// Preprocessor defines — code uses #if WITH_WHISPER etc. to guard third-party calls
		PublicDefinitions.Add(string.Format("WITH_WHISPER={0}", bHasWhisper ? "1" : "0"));
		PublicDefinitions.Add(string.Format("WITH_OPENCV={0}", bHasOpenCV ? "1" : "0"));
		PublicDefinitions.Add(string.Format("WITH_ONNXRUNTIME={0}", bHasONNX ? "1" : "0"));
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
