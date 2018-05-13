// Fill out your copyright notice in the Description page of Project Settings.

#include "EventManager.h"
#include "EngineMinimal.h"
#include "EngineUtils.h"
#include "EventBus.h"
#include "KillEnemyEvent.h"
#include "AeroFighterGameStateBase.h"


// Sets default values
AEventManager::AEventManager() : KilledEnemies(0), Score(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto ParticleSystemAsset = ConstructorHelpers::FObjectFinder<UParticleSystem>(TEXT("ParticleSystem'/Game/Particles/P_Explosion.P_Explosion'"));
	if (ParticleSystemAsset.Succeeded())
	{
		ExplosionParticleSystem = ParticleSystemAsset.Object;
	}
}

// Called when the game starts or when spawned
void AEventManager::BeginPlay()
{
	Super::BeginPlay();

	Instance = this;
	if (GetWorld() != NULL) {
		AAeroFighterGameStateBase* GameState = GetWorld()->GetGameState<AAeroFighterGameStateBase>();

		EventBus = GameState->GetEventBus();
		if (EventBus != NULL) {
			EventBus->Register(Instance.Get());
		}
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
	case UGameEvent::PLAYER_KILLED_EVENT:

		TWeakObjectPtr<APawn> PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleSystem.Get(), PlayerPawn.Get()->GetActorLocation());
		UGameplayStatics::OpenLevel(GetWorld(), "TwinStickExampleMap");
		break;
	}
}
