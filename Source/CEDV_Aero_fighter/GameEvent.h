// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameEvent.generated.h"

/**
* Game Event parent class
*/

UCLASS(Abstract)
class CEDV_AERO_FIGHTER_API UGameEvent : public UObject
{
	GENERATED_BODY()

public:
	UGameEvent();
	~UGameEvent();

	int Code;

	static const int KILL_EVENT = 0;
};
