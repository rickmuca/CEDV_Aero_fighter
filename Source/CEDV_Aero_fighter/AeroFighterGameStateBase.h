// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AeroFighterGameStateBase.generated.h"

class UEventBus;

UCLASS()
class CEDV_AERO_FIGHTER_API AAeroFighterGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "EventBus")
	UEventBus* GetEventBus();

private:
	UPROPERTY()
	TWeakObjectPtr<UEventBus> EventBus;
};
