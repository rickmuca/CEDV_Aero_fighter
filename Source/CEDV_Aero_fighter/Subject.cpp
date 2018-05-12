// Fill out your copyright notice in the Description page of Project Settings.

#include "Subject.h"
#include "Observer.h"

void USubject::AddObserver(TScriptInterface<IObserver> Observer)
{
	Observers.Add((IObserver*)Observer.GetInterface());
}

void USubject::RemoveObserver(TScriptInterface<IObserver> Observer)
{
	Observers.Remove((IObserver*)Observer.GetInterface());
}

void USubject::Notify(UObject* Entity, UGameEvent* Event)
{
	for (auto Observer : Observers) {
		Observer->OnNotify(Entity, Event);
	}
}
