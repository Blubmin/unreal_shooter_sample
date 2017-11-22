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
        LoadCeres(Target);
        //LoadTest(Target);
    }

    public bool LoadTest(TargetInfo Target) {
        string TestPath = Path.Combine(ThirdPartyPath, "testlib");
        string IncludePath = Path.Combine(TestPath, "include");
        string LibraryPath = Path.Combine(TestPath, "x64", "Release");
        PublicIncludePaths.Add(IncludePath);
        PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "testlib.lib"));
        return true;
    }

    public bool LoadEigen(TargetInfo Target) {
        string EigenPath = Path.Combine(ThirdPartyPath, "Eigen");
        PublicIncludePaths.Add(EigenPath);
        return true;
    }

    public bool LoadGLog(TargetInfo Target) {
        string gLogPath = Path.Combine(ThirdPartyPath, "glog");
        string LibraryPath = Path.Combine(gLogPath, "build", "Release");
        string IncludePath = Path.Combine(gLogPath, "build");
        Definitions.Add("GLOG_NO_ABBREVIATED_SEVERITIES");
        Definitions.Add("GOOGLE_GLOG_DLL_DECL=");
        string lib = Path.Combine(LibraryPath, "glog.lib");
        PublicLibraryPaths.Add(LibraryPath);
        PublicAdditionalLibraries.Add("glog.lib");
        PublicIncludePaths.Add(IncludePath);
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
        string LibraryPath = Path.Combine(CeresPath, "build", "lib", "Release");
        string IncludePath = Path.Combine(CeresPath, "include");
        //string MiniglogPath = Path.Combine(CeresPath, "internal", "ceres", "miniglog");
        PublicLibraryPaths.Add(LibraryPath);
        PublicAdditionalLibraries.Add("ceres.lib");
        PublicIncludePaths.Add(IncludePath);
        //PublicIncludePaths.Add(MiniglogPath);
        return true;
    }
}
