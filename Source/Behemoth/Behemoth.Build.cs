// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Behemoth : ModuleRules
{
	public Behemoth(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
