using UnrealBuildTool;

public class LLM_NPCTarget : TargetRules
{
	public LLM_NPCTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V6;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;
		ExtraModuleNames.AddRange(new string[] { "LLM_NPC" });
	}
}
