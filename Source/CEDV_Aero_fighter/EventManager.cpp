// Fill out your copyright notice in the Description page of Project Settings.

#include "EventManager.h"
#include "EventBus.h"
#include "KillEnemyEvent.h"
#include "AeroFighterGameStateBase.h"


// Sets default values
AEventManager::AEventManager() : KilledEnemies(0), Score(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEventManager::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld() != NULL) {
		GameState = GetWorld()->GetGameState<AAeroFighterGameStateBase>();
		GameState->GetEventBus()->Register(this);
	}
}

// Called every frame
void AEventManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEventManager ::OnNotify(UObject* Entity, UGameEvent* Event)
{
	if (Event == NULL) return;

	switch (Event->Code) {
	case UGameEvent::KILL_EVENT:
		this->KilledEnemies++;

		if (Event->IsA(UKillEnemyEvent::StaticClass())) {
			UKillEnemyEvent* KillEvent = Cast<UKillEnemyEvent>(Event);
			this->Score += KillEvent->Score;
			if (ScorePresenter != NULL) {
				ScorePresenter->SetScore(this->Score);
			}
		}
		break;
	}
}
