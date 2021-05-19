// MyFirstCoolTESTGame. All rights RESRVED!

using UnrealBuildTool;
using System.Collections.Generic;

public class MyFirstCoolTESTGameTarget : TargetRules
{
	public MyFirstCoolTESTGameTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "MyFirstCoolTESTGame" } );
	}
}
