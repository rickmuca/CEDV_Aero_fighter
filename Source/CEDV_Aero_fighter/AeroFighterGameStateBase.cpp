// Fill out your copyright notice in the Description page of Project Settings.

#include "AeroFighterGameStateBase.h"
#include "EventBus.h"

UEventBus* AAeroFighterGameStateBase::GetEventBus()
{
	// If the event bus has not been instanced yet, instance it
	// 
	// Why don't we override the HandleBeginPlay()? Because we don't know
	// when that method will be executed, and we have to make sure the instance
	// exists before any other BeginPlay event
	if (!EventBus.IsValid()) {
		// Notice how UObjects must be instanced with the NewObject factory
		// method instead of "new".
		EventBus = NewObject<UEventBus>();
	}
	return EventBus.Get();
}

