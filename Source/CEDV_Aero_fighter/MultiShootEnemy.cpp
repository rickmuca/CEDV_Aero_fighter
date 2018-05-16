// Fill out your copyright notice in the Description page of Project Settings.

#include "MultiShootEnemy.h"
#include "EngineMinimal.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
const FString AMultiShootEnemy::TYPE_NAME = "MultiShootEnemy";

// Sets default values
AMultiShootEnemy::AMultiShootEnemy() : Super()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMeshComponent");
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	if (MeshAsset.Succeeded())
	{
		StaticMesh->SetStaticMesh(MeshAsset.Object);
		StaticMesh->SetWorldScale3D(FVector(50.0f, 50.0f, 50.0f));
		StaticMesh->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	}

	TWeakObjectPtr<UMaterialInstanceDynamic> Material = StaticMesh->CreateAndSetMaterialInstanceDynamic(0);
	Material->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(0.0f, 0.0f, 1.0f));

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
	SetType(TYPE_NAME);
	SetLife(3);
	SetPoints(200);
}

void AMultiShootEnemy::RunBehaviour()
{
	// Rotate to player
	FRotator EnemyRotation = FRotationMatrix::MakeFromX(PlayerPawn->GetActorLocation() - GetActorLocation()).Rotator();
	StaticMesh->SetRelativeRotation(EnemyRotation, false, nullptr, ETeleportType::TeleportPhysics);

	// Just move forward
	// Move towards to player
	FVector Distance = PlayerPawn->GetActorLocation() - GetActorLocation();
	
	if (Distance.Size() >= 200.0f) {
		FVector Direction = GetActorForwardVector();
		SetActorRelativeLocation(FVector(
			GetActorLocation().X + -10.f,
			GetActorLocation().Y,
			GetActorLocation().Z));
	}

	// If fire interval has elapsed, spawn a new enemy projectile
	if (AccumulatedDeltaTime >= FireTimeInterval) {
		FVector SpawnLocation1 = GetActorLocation() + GetActorForwardVector() * 250.0f;
		FVector SpawnLocation2 = GetActorLocation() + GetActorForwardVector() * 500.0f;
		FVector SpawnLocation3 = GetActorLocation() + GetActorForwardVector() * 750.0f;

		FRotator SpawnRotation1 = GetActorRotation();
		FRotator SpawnRotation2 = GetActorRotation().Add(0.0f, 15.0f, 0.0f);
		FRotator SpawnRotation3 = GetActorRotation().Add(0.0f, -15.0f, 0.0f);

		GetWorld()->SpawnActor(ProjectileClass, &SpawnLocation1, &SpawnRotation1);
		GetWorld()->SpawnActor(ProjectileClass, &SpawnLocation2, &SpawnRotation2);
		GetWorld()->SpawnActor(ProjectileClass, &SpawnLocation3, &SpawnRotation3);

		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());

		AccumulatedDeltaTime = 0.0f;
	}
}
