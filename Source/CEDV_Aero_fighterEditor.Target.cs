// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class CEDV_Aero_fighterEditorTarget : TargetRules
{
	public CEDV_Aero_fighterEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "CEDV_Aero_fighter" } );
	}
}
