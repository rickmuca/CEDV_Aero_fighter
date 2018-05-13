// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AirProjectile.h"
#include "AeroFighterGameStateBase.h"
#include "EventBus.h"
#include "BaseEnemy.generated.h"

class UEventBus;

UCLASS(Abstract)
class CEDV_AERO_FIGHTER_API ABaseEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category = "BaseEnemy")
	int GetPoints();

private:
	UPROPERTY()
	TWeakObjectPtr<UParticleSystem> ExplosionParticleSystem;

	AAeroFighterGameStateBase* GameState;
	FString Type;
	int Life; // Número de colisiones antes de ser destruido
	int Points; // Puntuacion conseguida al destruir al enemigo

	void GenerateKillingEvent();

protected:
	UFUNCTION()
	virtual void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	virtual void RunBehaviour() PURE_VIRTUAL(ABaseEnemy::RunBehaviour, );

	UPROPERTY()
	TWeakObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY()
	TSubclassOf<class AAirProjectile> ProjectileClass;

	UPROPERTY()
	class USoundBase* FireSound;

	TWeakObjectPtr<APawn> PlayerPawn;
	float AccumulatedDeltaTime;
	
	float FireTimeInterval = 2.0f;

	void SetType(FString Type);
	void SetLife(int Life);
	void SetPoints(int Points);
};
