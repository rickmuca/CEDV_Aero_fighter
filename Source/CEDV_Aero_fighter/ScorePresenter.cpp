// Fill out your copyright notice in the Description page of Project Settings.

#include "ScorePresenter.h"
#include "Blueprint/UserWidget.h"
#include "TextWidgetTypes.h"
#include "TextBlock.h"

// Sets default values
AScorePresenter::AScorePresenter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AScorePresenter::BeginPlay()
{
	Super::BeginPlay();

	if (ScoreTextWidget) {
		pScoreTextWidget = CreateWidget<UUserWidget>(GetGameInstance(), ScoreTextWidget);

		if (pScoreTextWidget.IsValid()) {
			pScoreTextWidget->AddToViewport();
			pScoreText = (UTextBlock*)pScoreTextWidget->GetWidgetFromName("TextScoreWidget");
			SetScore(0);
		}
	}
}

// Called every frame
void AScorePresenter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AScorePresenter::SetScore(int Score) {
	if (pScoreText.IsValid()) {
		pScoreText->SetText(FText::FromString(FString::FromInt(Score)));
	}
}

