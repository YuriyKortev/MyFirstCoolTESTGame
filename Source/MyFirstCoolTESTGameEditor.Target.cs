// MyFirstCoolTESTGame. All rights RESRVED!

using UnrealBuildTool;
using System.Collections.Generic;

public class MyFirstCoolTESTGameEditorTarget : TargetRules
{
	public MyFirstCoolTESTGameEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "MyFirstCoolTESTGame" } );
	}
}
