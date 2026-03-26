using UnrealBuildTool;

public class LLM_NPCEditorTarget : TargetRules
{
	public LLM_NPCEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.AddRange(new string[] { "LLM_NPC" });
	}
}
