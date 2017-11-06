// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class ShooterGame : ModuleRules
{

    private string ModulePath {
        get { return ModuleDirectory; }
    }

    private string ThirdPartyPath {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
    }

    public ShooterGame(TargetInfo Target) {
        PrivateIncludePaths.AddRange(
            new string[] {
                "ShooterGame/Classes/Player",
                "ShooterGame/Private",
                "ShooterGame/Private/UI",
                "ShooterGame/Private/UI/Menu",
                "ShooterGame/Private/UI/Style",
                "ShooterGame/Private/UI/Widgets",
            }
        );

        PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine",
                "OnlineSubsystem",
                "OnlineSubsystemUtils",
                "AssetRegistry",
                "AIModule",
                "GameplayTasks",
                "PhysX",
                "APEX",
                "RHI",
                "RenderCore",
                "ShaderCore",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "InputCore",
                "Slate",
                "SlateCore",
                "ShooterGameLoadingScreen",
                "Json"
            }
        );

        DynamicallyLoadedModuleNames.AddRange(
            new string[] {
                "OnlineSubsystemNull",
                "NetworkReplayStreaming",
                "NullNetworkReplayStreaming",
                "HttpNetworkReplayStreaming"
            }
        );

        PrivateIncludePathModuleNames.AddRange(
            new string[] {
                "NetworkReplayStreaming"
            }
        );

        //LoadPhysX(Target);
    }

    public bool LoadPhysX(TargetInfo Target) {
        bool isLibrarySupported = false;

        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32)) {
            isLibrarySupported = true;

            string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";
            string LibrariesPath = Path.Combine(ThirdPartyPath, "PhysX", "Libraries");

            /*
            test your path with:
            using System; // Console.WriteLine("");
            Console.WriteLine("... LibrariesPath -> " + LibrariesPath);
            */

            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "PhysX3DEBUG_" + PlatformString + ".lib"));
        }

        if (isLibrarySupported) {
            // Include path
            PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "PhysX", "Includes"));
        }

        Definitions.Add(string.Format("WITH_PHYSX_BINDING={0}", isLibrarySupported ? 1 : 0));

        return isLibrarySupported;
    }

}
