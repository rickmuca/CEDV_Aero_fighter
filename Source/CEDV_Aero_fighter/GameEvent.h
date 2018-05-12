// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameEvent.generated.h"

/**
*
*/
UCLASS(Abstract)
class CEDV_AERO_FIGHTER_API UGameEvent : public UObject
{
	GENERATED_BODY()

public:
	UGameEvent();
	~UGameEvent();
};
