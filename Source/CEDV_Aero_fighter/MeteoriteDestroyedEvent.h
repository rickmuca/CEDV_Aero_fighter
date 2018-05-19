// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameEvent.h"
#include "MeteoriteDestroyedEvent.generated.h"

/**
 * This event represents a meteorite destroyed
 */
UCLASS(BlueprintType)
class CEDV_AERO_FIGHTER_API UMeteoriteDestroyedEvent : public UGameEvent
{
	GENERATED_BODY()
	
public:
	int Score;

	UMeteoriteDestroyedEvent();
	~UMeteoriteDestroyedEvent();
};
