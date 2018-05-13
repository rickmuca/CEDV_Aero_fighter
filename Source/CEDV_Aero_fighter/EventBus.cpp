// Fill out your copyright notice in the Description page of Project Settings.

#include "EventBus.h"
#include "Observer.h"

void UEventBus::Register(TScriptInterface<IObserver> Observer)
{
	Observers.Emplace((IObserver*)Observer.GetInterface());
}

void UEventBus::Unregister(TScriptInterface<IObserver> Observer)
{
	Observers.Remove((IObserver*)Observer.GetInterface());
}

void UEventBus::Post(UObject* Entity, UGameEvent* Event)
{
	for (auto Observer : Observers) {
		Observer->OnNotify(Entity, Event);
	}
}