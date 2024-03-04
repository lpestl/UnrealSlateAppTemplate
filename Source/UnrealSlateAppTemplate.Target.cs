// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

[SupportedPlatforms(UnrealPlatformClass.Desktop)]
[SupportedPlatforms("IOS")]
public class UnrealSlateAppTemplateTarget : TargetRules
{
	public UnrealSlateAppTemplateTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Program;
		LinkType = TargetLinkType.Monolithic;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		LaunchModuleName = "UnrealSlateAppTemplate";
		if (bBuildEditor)
		{
			ExtraModuleNames.Add("EditorStyle");
		}

		// UnrealSlateAppTemplate doesn't ever compile with the engine linked in
		bCompileAgainstEngine = false;

		// We need CoreUObject compiled in as the source code access module requires it
		bCompileAgainstCoreUObject = true;

		// UnrealSlateAppTemplate.exe has no exports, so no need to verify that a .lib and .exp file was emitted by
		// the linker.
		bHasExports = false;

		// Make sure to get all code in SlateEditorStyle compiled in
        bBuildDeveloperTools = true;
	}
}
