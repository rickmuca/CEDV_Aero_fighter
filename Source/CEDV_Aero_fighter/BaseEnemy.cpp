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
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMeshComponent");
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	if (MeshAsset.Succeeded())
	{
		StaticMesh->SetStaticMesh(MeshAsset.Object);
		StaticMesh->SetWorldScale3D(FVector(50.0f, 50.0f, 50.0f));
		StaticMesh->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	}

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

	// The common behaviour for all enemies will be to rotate them to face the player
	FRotator EnemyRotation = FRotationMatrix::MakeFromX(PlayerPawn->GetActorLocation() - GetActorLocation()).Rotator();
	StaticMesh->SetRelativeRotation(EnemyRotation, false, nullptr, ETeleportType::TeleportPhysics);

	RunBehaviour();
}

void ABaseEnemy::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor) {
		if (OtherActor->IsA(AAirProjectile::StaticClass())) {
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleSystem.Get(), Hit.Location);
			GenerateKillingEvent();
			Destroy();
		}
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

void ABaseEnemy::GenerateKillingEvent() {
	if (EventBus != NULL) {
		UKillEnemyEvent* KillEvent = NewObject<UKillEnemyEvent>();
		KillEvent->Type = this->Type;
		KillEvent->Score = this->Points;

		EventBus->Post(this, KillEvent);
	}
}