// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Observer.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EventManager.generated.h"

UCLASS()
class CEDV_AERO_FIGHTER_API AEventManager : public AActor, public IObserver
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEventManager();

	void OnNotify(UObject* Entity, UGameEvent* Event) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
