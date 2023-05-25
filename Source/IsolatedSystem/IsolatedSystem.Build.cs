// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class IsolatedSystem : ModuleRules
{
	public IsolatedSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" , "UMG", "NavigationSystem", "AIModule", "GameplayTasks"});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PrivateIncludePaths.AddRange(new string[] { "IsolatedSystem/Interface", "IsolatedSystem/AI", "IsolatedSystem/Animation", "IsolatedSystem/Physics", "IsolatedSystem/Stat"});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
