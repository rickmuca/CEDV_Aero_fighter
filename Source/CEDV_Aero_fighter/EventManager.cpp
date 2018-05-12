// Fill out your copyright notice in the Description page of Project Settings.

#include "EventManager.h"


// Sets default values
AEventManager::AEventManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEventManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEventManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEventManager ::OnNotify(UObject* Entity, UGameEvent* Event)
{

}
