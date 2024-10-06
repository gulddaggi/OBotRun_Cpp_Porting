// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class OBotRun_Cpp_Porting : ModuleRules
{
	public OBotRun_Cpp_Porting(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG" });
	}
}
