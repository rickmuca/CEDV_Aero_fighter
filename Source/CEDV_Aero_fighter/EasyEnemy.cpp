// Fill out your copyright notice in the Description page of Project Settings.

#include "EasyEnemy.h"
#include "EngineMinimal.h"

const FString AEasyEnemy::TYPE_NAME = "EasyEnemy";

// Sets default values
AEasyEnemy::AEasyEnemy() : Super()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMeshComponent");
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	if (MeshAsset.Succeeded())
	{
		StaticMesh->SetStaticMesh(MeshAsset.Object);
		StaticMesh->SetWorldScale3D(FVector(50.0f, 50.0f, 50.0f));
		StaticMesh->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	}

	StaticMesh->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
    SetType(TYPE_NAME);
	SetLife(1);
	SetPoints(100);
}

void AEasyEnemy::RunBehaviour()
{
	// Rotate to player
	FRotator EnemyRotation = FRotationMatrix::MakeFromX(PlayerPawn->GetActorLocation() - GetActorLocation()).Rotator();
	StaticMesh->SetRelativeRotation(EnemyRotation, false, nullptr, ETeleportType::TeleportPhysics);

	// Move towards to player
	FVector Distance = PlayerPawn->GetActorLocation() - GetActorLocation();
	if (Distance.Size() >= 200.0f) {

		FVector Direction = GetActorForwardVector();
		SetActorRelativeLocation(FVector(
			GetActorLocation().X + 15.f * Direction.X,
			GetActorLocation().Y + 15.f * Direction.Y,
			GetActorLocation().Z + 15.f * Direction.Z));
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
