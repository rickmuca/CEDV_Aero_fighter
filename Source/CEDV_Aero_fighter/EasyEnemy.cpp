// Fill out your copyright notice in the Description page of Project Settings.

#include "EasyEnemy.h"
#include "EngineMinimal.h"

const FString AEasyEnemy::TYPE_NAME = "EasyEnemy";

// Sets default values
AEasyEnemy::AEasyEnemy() : Super()
{
	StaticMesh->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
    SetType(TYPE_NAME);
	SetLife(1);
	SetPoints(100);
}

void AEasyEnemy::RunBehaviour()
{
	// Move towards to player
	FVector Distance = PlayerPawn->GetActorLocation() - GetActorLocation();
	if (Distance.Size() >= 200.0f) {

		FVector Direction = GetActorForwardVector();
		SetActorRelativeLocation(FVector(
			GetActorLocation().X + 3.f * Direction.X,
			GetActorLocation().Y + 3.f * Direction.Y,
			GetActorLocation().Z + 3.f * Direction.Z));
	}

	// If fire interval has elapsed, spawn a new enemy projectile
	if (AccumulatedDeltaTime >= FireTimeInterval) {
		FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 250.0f;
		FRotator SpawnRotation = GetActorRotation();

		GetWorld()->SpawnActor(ProjectileClass, &SpawnLocation, &SpawnRotation);
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());

		AccumulatedDeltaTime = 0.0f;
	}
}
