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

        LoadEigen(Target);
        LoadGLog(Target);
        LoadGFlag(Target);
        LoadCeres(Target);
    }

    public bool LoadEigen(TargetInfo Target) {
        string EigenPath = Path.Combine(ThirdPartyPath, "Eigen");
        PublicIncludePaths.Add(EigenPath);
        return true;
    }

    public bool LoadGLog(TargetInfo Target) {
        string gLogPath = Path.Combine(ThirdPartyPath, "glog");
        string LibraryPath = Path.Combine(gLogPath, "Release");
        Definitions.Add("GLOG_NO_ABBREVIATED_SEVERITIES");
        Definitions.Add("GOOGLE_GLOG_DLL_DECL=_MBCS");
        PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "glog.lib"));
        PublicIncludePaths.Add(gLogPath);
        PublicIncludePaths.Add(Path.Combine(gLogPath, "src"));
        return true;
    }

    public bool LoadGFlag(TargetInfo Target) {
        string gFlagPath = Path.Combine(ThirdPartyPath, "gflags");
        string LibraryPath = Path.Combine(gFlagPath, "lib", "Release");
        string IncludePath = Path.Combine(gFlagPath, "include");
        PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "gflags_static.lib"));
        PublicIncludePaths.Add(IncludePath);
        return true;
    }

    public bool LoadCeres(TargetInfo Target) {
        string CeresPath = Path.Combine(ThirdPartyPath, "Ceres");
        string LibraryPath = Path.Combine(CeresPath, "bin", "lib", "Release");
        string IncludePath = Path.Combine(CeresPath, "include");
        PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "ceres.lib"));
        PublicIncludePaths.Add(IncludePath);
        return true;
    }
}
