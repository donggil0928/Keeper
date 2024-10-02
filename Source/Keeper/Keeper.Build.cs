// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Keeper : ModuleRules
{
	public Keeper(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", 
		"InputCore", "EnhancedInput", "NavigationSystem", "AIModule", "UMG"});

		PrivateDependencyModuleNames.AddRange( new string[] { "Slate", "SlateCore" });

		PrivateIncludePaths.AddRange(new string[] { "Keeper" });

		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.AddRange(new string[]{"UnrealEd", "Persona"});
		}
		
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
