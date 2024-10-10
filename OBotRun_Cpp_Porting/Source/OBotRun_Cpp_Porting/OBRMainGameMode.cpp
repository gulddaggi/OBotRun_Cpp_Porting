// Fill out your copyright notice in the Description page of Project Settings.


#include "OBRMainGameMode.h"
#include "OBRCharacter.h"
#include "OBRFloorSpawner.h"
#include "OBRHUDWidget.h"

AOBRMainGameMode::AOBRMainGameMode()
{
	static ConstructorHelpers::FClassFinder<UOBRHUDWidget> UI_HUD_C(TEXT("/Game/UI/UI_HUD.UI_HUD_C"));

	if (UI_HUD_C.Succeeded())
	{
		HUDWidgetClass = UI_HUD_C.Class;
	}

	DefaultPawnClass = AOBRCharacter::StaticClass();

	Score = 0;
	Difficulty = 1;
}

void AOBRMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	Spawner = GetWorld()->SpawnActor<AOBRFloorSpawner>(AOBRFloorSpawner::StaticClass());
	Spawner->SpawnStraightFloor(6, false);

	
	HUDWidget = CreateWidget<UOBRHUDWidget>(GetWorld(), HUDWidgetClass);
	HUDWidget->AddToViewport();
	HUDWidget->UpdateScore(Score);
}

void AOBRMainGameMode::AddScore(int Value)
{
	Score += Value;
	HUDWidget->UpdateScore(Score);

	if (Difficulty != 3)
	{
		CheckDifficulty();
	}
}

void AOBRMainGameMode::CheckDifficulty()
{
	if (Score >= 10000)
	{
		Difficulty = 3;
		OnDifficultyChanged.Broadcast();
	}
	else if (Score >= 5000)
	{
		if (Difficulty == 1)
		{
			Difficulty = 2;
			OnDifficultyChanged.Broadcast();
		}
	}
}

int AOBRMainGameMode::GetDifficulty()
{
	return Difficulty;
}