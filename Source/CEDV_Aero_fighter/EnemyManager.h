// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AirProjectile.h"
#include "EventBus.h"
#include "EnemyManager.generated.h"

class ABaseEnemy;

UCLASS()
class CEDV_AERO_FIGHTER_API AEnemyManager : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AEnemyManager();

	UPROPERTY(Category = Projectile, EditAnywhere)
	TSubclassOf<class AAirProjectile> ProjectileClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	// Temporal reference to spawn new enemies
	float AccumulatedDeltaTime;
	float EnemySpawnTimeSeconds;

	// Invisible plane to spawn enemies
	TWeakObjectPtr<AActor> ReferencePlane;

	// Keeps a list of enemy types to spawn
	TArray<TSubclassOf<ABaseEnemy>> EnemyClasses;

	FVector GetRandomLocationFromReferencePlane() const;
	TSubclassOf<ABaseEnemy> GetRandomEnemyClass() const;

	UPROPERTY()
	TWeakObjectPtr<UEventBus> EventBus;

	void SpawnEnemy();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UEventBus* GetEventBus() const;
};
