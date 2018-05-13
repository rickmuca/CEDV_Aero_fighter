// Fill out your copyright notice in the Description page of Project Settings.

#include "KillEnemyEvent.h"

UKillEnemyEvent::UKillEnemyEvent() {
	Code = UGameEvent::KILL_EVENT;
	Score = 0;
	Type = "";
}

UKillEnemyEvent::~UKillEnemyEvent() { }


