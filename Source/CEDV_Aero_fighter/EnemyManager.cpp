// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyManager.h"
#include "EngineUtils.h"
#include "EasyEnemy.h"

// Sets default values
AEnemyManager::AEnemyManager()
	: AccumulatedDeltaTime(0.0f), EnemySpawnTimeSeconds(3.5f), ReferencePlane(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Store references to enemy classes for later
	EnemyClasses.AddUnique(AEasyEnemy::StaticClass());
}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	FString EnemySpawnPlaneString = FString(TEXT("EnemySpawnPlane"));
	// Get a reference to the invisible plane used to spawn enemies
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (EnemySpawnPlaneString.Equals(ActorItr->GetName()))
		{
			// Conversion to smart pointer
			ReferencePlane = *ActorItr;
			break;
		}
	}

	AAeroFighterGameStateBase* GameState = GetWorld()->GetGameState<AAeroFighterGameStateBase>();
	EventBus = GameState->GetEventBus();
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AccumulatedDeltaTime += DeltaTime;
	printf("%f", AccumulatedDeltaTime);
	if (AccumulatedDeltaTime >= EnemySpawnTimeSeconds)
	{
		// Spawn new enemy and reset the counter
		SpawnEnemy();
		AccumulatedDeltaTime = 0.0f;
	}
}

FVector AEnemyManager::GetRandomLocationFromReferencePlane() const
{
	FVector RandomLocation;
	FVector Orgin;
	FVector BoundsExtent;
	ReferencePlane->GetActorBounds(false, Orgin, BoundsExtent);

	// Build a bounding box and get a random location.
	RandomLocation = FMath::RandPointInBox(FBox::BuildAABB(Orgin, BoundsExtent));

	return RandomLocation;
}

TSubclassOf<ABaseEnemy> AEnemyManager::GetRandomEnemyClass() const
{
	return EnemyClasses[FMath::RandRange(0, EnemyClasses.Num() - 1)];
}

void AEnemyManager::SpawnEnemy()
{
	TSubclassOf<ABaseEnemy> EnemyType = GetRandomEnemyClass();
	FVector EnemySpawnLocation = GetRandomLocationFromReferencePlane();
	GetWorld()->SpawnActor(EnemyType, &EnemySpawnLocation);
}

UEventBus* AEnemyManager::GetEventBus() const {
	return EventBus.Get();
}
