// Fill out your copyright notice in the Description page of Project Settings.

#include "MeteoriteDestroyedEvent.h"

UMeteoriteDestroyedEvent::UMeteoriteDestroyedEvent() {
	Code = UGameEvent::METEORITE_DESTROYED;
	Score = 50;
}

UMeteoriteDestroyedEvent::~UMeteoriteDestroyedEvent() { }

