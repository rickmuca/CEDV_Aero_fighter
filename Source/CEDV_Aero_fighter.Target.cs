// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class CEDV_Aero_fighterTarget : TargetRules
{
	public CEDV_Aero_fighterTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "CEDV_Aero_fighter" } );
	}
}
