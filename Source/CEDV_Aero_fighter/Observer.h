// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameEvent.h"
#include "Observer.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UObserver : public UInterface
{
	GENERATED_BODY()
};

/**
* Observer interface to listen game events
*/
class CEDV_AERO_FIGHTER_API IObserver
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void OnNotify(UObject* Entity, UGameEvent* GameEvent) = 0;
};
