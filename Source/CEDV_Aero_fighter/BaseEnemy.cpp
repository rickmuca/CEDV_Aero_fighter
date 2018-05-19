// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseEnemy.h"
#include "EngineMinimal.h"
#include "EngineUtils.h"
#include "EnemyManager.h"
#include "KillEnemyEvent.h"
#include "EventBus.h"
#include "AeroFighterGameStateBase.h"
#include "PhysicsEngine/PhysicsAsset.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto ParticleSystemAsset = ConstructorHelpers::FObjectFinder<UParticleSystem>(TEXT("ParticleSystem'/Game/Particles/P_Explosion.P_Explosion'"));
	if (ParticleSystemAsset.Succeeded())
	{
		ExplosionParticleSystem = ParticleSystemAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;

	OnActorHit.AddDynamic(this, &ABaseEnemy::OnHit);
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	FString EnemyManCtl = FString(TEXT("EnemyManager_2"));
	TWeakObjectPtr<AActor> EnemyManRef;

	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		if (EnemyManCtl.Equals(ActorItr->GetName())) {
			EnemyManRef = *ActorItr;
			if (EnemyManRef.IsValid() && EnemyManRef.Get()->IsA(AEnemyManager::StaticClass())) {
				this->ProjectileClass = Cast<AEnemyManager>(EnemyManRef.Get())->ProjectileClass;
				this->MeteoriteClass = Cast<AEnemyManager>(EnemyManRef.Get())->MeteoriteClass;
				this->EventBus = Cast<AEnemyManager>(EnemyManRef.Get())->GetEventBus();
			}
			break;
		}
	}
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AccumulatedDeltaTime += DeltaTime;

	RunBehaviour();
}

void ABaseEnemy::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor) {
		return;
	}

	this->Life--;
	if (this->Life == 0) {
		if (OtherActor->IsA(AAirProjectile::StaticClass())) {
			GenerateKillingEvent();
		}
		this->DestroyEnemy(Hit.Location);
	}
	else {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleSystem.Get(), Hit.Location);
	}
}

void ABaseEnemy::SetType(FString Type)
{
	this->Type = Type;
}

void ABaseEnemy::SetLife(int Life)
{
	this->Life = Life;
}

int ABaseEnemy::GetPoints()
{
	return this->Points;
}

void ABaseEnemy::SetPoints(int Points)
{
	this->Points = Points;
}

void ABaseEnemy::DestroyEnemy(FVector Location) {
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleSystem.Get(), Location);
	Destroy();
}

void ABaseEnemy::GenerateKillingEvent() {
	if (EventBus != NULL) {
		UKillEnemyEvent* KillEvent = NewObject<UKillEnemyEvent>();
		KillEvent->Type = this->Type;
		KillEvent->Score = this->Points;

		EventBus->Post(this, KillEvent);
	}
}