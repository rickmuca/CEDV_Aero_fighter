// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameEvent.h"
#include "KillEnemyEvent.generated.h"

/**
* Event to generate when killing an enemy
*/
UCLASS()
class CEDV_AERO_FIGHTER_API UKillEnemyEvent : public UGameEvent
{
	GENERATED_BODY()

public:
	int score;
	FString type;

	UKillEnemyEvent();
	~UKillEnemyEvent();
};
