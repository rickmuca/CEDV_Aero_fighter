// Fill out your copyright notice in the Description page of Project Settings.

#include "RockEnemy.h"
#include "EngineMinimal.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

const FString ARockEnemy::TYPE_NAME = "RockEnemy";

// Sets default values
ARockEnemy::ARockEnemy() : Super()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMeshComponent");
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Rock/Mesh/Rock.Rock'"));
	if (MeshAsset.Succeeded())
	{
		StaticMesh->SetStaticMesh(MeshAsset.Object);
		StaticMesh->SetWorldScale3D(FVector(50.0f, 50.0f, 50.0f));
		StaticMesh->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	}

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
	SetType(TYPE_NAME);
	SetLife(5);
	SetPoints(300);
}

void ARockEnemy::RunBehaviour()
{
	// Rotation
	// on every frame change rotationg for a smooth rotating actor
	FRotator NewRotation = FRotator(5.0f, 5.0f, 0.0f);
	FQuat QuatRotation = FQuat(NewRotation);
	StaticMesh->SetRelativeRotation(QuatRotation, false, nullptr, ETeleportType::TeleportPhysics);

	// Just move forward
	// Move towards to player
	FVector Distance = PlayerPawn->GetActorLocation() - GetActorLocation();

	//if (Distance.Size() >= 100.0f) {
		FVector Direction = GetActorForwardVector();
		SetActorRelativeLocation(FVector(
			GetActorLocation().X + -20.f,
			GetActorLocation().Y,
			GetActorLocation().Z));
	//}
}