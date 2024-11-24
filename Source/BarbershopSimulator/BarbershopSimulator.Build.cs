// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BarbershopSimulator : ModuleRules
{
	public BarbershopSimulator(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", 
            "CoreUObject", 
            "Engine", 
            "InputCore", 
            "EnhancedInput", 
            "UMG", 
            "Niagara", 
            "PhysicsCore", 
            "GameplayTasks", 
            "NavigationSystem"
        });

		PublicIncludePaths.AddRange(new string[] { "BarbershopSimulator/Public/Character/STUBaseCharacter/",
                                                   "BarbershopSimulator/Public/Character/PlatformerCharacter/",
                                                   "BarbershopSimulator/Public/Pickup",
                                                   "BarbershopSimulator/Public/Weapon",
                                                   "BarbershopSimulator/Public/AI",
                                                   "BarbershopSimulator/Public/AI/Tasks/",
                                                   "BarbershopSimulator/Public/AI/Service",
                                                   "BarbershopSimulator/Public/AI/EQS",
                                                   "BarbershopSimulator/Public/AI/Decorators"
        });
	}
}
