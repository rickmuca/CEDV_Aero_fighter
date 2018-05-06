// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "EasyEnemy.generated.h"

UCLASS()
class CEDV_AERO_FIGHTER_API AEasyEnemy : public ABaseEnemy
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEasyEnemy();
	static const FString TYPE_NAME;

private:
	void RunBehaviour() override;
};
 