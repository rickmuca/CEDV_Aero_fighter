// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseEnemy.generated.h"

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

private:
	UPROPERTY()
		TWeakObjectPtr<UParticleSystem> ExplosionParticleSystem;
	FString Type;

protected:
	UFUNCTION()
		virtual void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	virtual void RunBehaviour() PURE_VIRTUAL(ABaseEnemy::RunBehaviour, );

	UPROPERTY()
		TWeakObjectPtr<UStaticMeshComponent> StaticMesh;

	TSubclassOf<AActor> ProjectileClass;
	TWeakObjectPtr<APawn> PlayerPawn;
	float AccumulatedDeltaTime;
	
	float FireTimeInterval = 2.0f;

	void setType(FString type);
};
