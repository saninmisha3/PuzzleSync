// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PuzzlePlatforms : ModuleRules
{
	public PuzzlePlatforms(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"HeadMountedDisplay",
			"UMG",
		});
		
		PublicIncludePaths.AddRange(new string[]
		{
			"PuzzlePlatforms/Public/Meshes",
			"PuzzlePlatforms/Public/HUD",
			"PuzzlePlatforms/Public/Interfaces",
		});
	}
}
