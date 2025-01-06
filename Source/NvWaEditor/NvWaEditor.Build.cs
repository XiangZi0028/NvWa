using UnrealBuildTool;

public class NvWaEditor : ModuleRules
{
    public NvWaEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateIncludePaths.AddRange(
            new string[] {
                System.IO.Path.Combine(GetModuleDirectory("AnimationEditor"), "Private"),
                System.IO.Path.Combine(GetModuleDirectory("SkeletonEditor"), "Private"),
                System.IO.Path.Combine(GetModuleDirectory("Persona"), "Private"),

            }
        );
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core" 
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "NvWa",
                "UnrealEd",
                "AssetDefinition",
                "AssetTools", "AnimationEditor", "NvWa", "EditorSubsystem", "SkeletonEditor", "Persona", "AnimGraph"
            }
        );
    }
}