// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TheHallway : ModuleRules
{
	public TheHallway(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
