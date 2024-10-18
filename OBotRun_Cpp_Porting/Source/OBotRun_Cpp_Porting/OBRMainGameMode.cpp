// Fill out your copyright notice in the Description page of Project Settings.


#include "OBRMainGameMode.h"
#include "OBRCharacter.h"
#include "OBRFloorSpawner.h"
#include "OBRHUDWidget.h"
#include "OBRGameOverWidget.h"

AOBRMainGameMode::AOBRMainGameMode()
{
	Score = 0;
	Difficulty = 1;
}

void AOBRMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	Spawner = GetWorld()->SpawnActor<AOBRFloorSpawner>(FloorSpawnerClass);
	Spawner->SpawnStraightFloor(7, false);

	HUDWidget = CreateWidget<UOBRHUDWidget>(GetWorld(), HUDWidgetClass);
	HUDWidget->AddToViewport();
	HUDWidget->UpdateScore(Score);
}

void AOBRMainGameMode::AddScore(int Value)
{
	Score += Value;
	HUDWidget->UpdateScore(Score);

	if (Difficulty != 3) CheckDifficulty();
}

void AOBRMainGameMode::CheckDifficulty()
{
	if (Score >= 15000)
	{
		Difficulty = 3;
		auto OBot = Cast<AOBRCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		OBot->SetRunningScore(50);
		OBot->SetAddingSpeed(0.5f);
		OnDifficultyChanged.Broadcast();
	}
	else if (Score >= 7500)
	{
		if (Difficulty == 1)
		{
			auto OBot = Cast<AOBRCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
			OBot->SetRunningScore(30);
			OBot->SetAddingSpeed(0.1f);
			Difficulty = 2;
			OnDifficultyChanged.Broadcast();
		}
	}
}

int AOBRMainGameMode::GetDifficulty()
{
	return Difficulty;
}

void AOBRMainGameMode::GameOver()
{
	GameOverWidget = CreateWidget<UOBRGameOverWidget>(GetWorld(), GameOverWidgetClass);
	GameOverWidget->AddToViewport();
	GameOverWidget->SetScore(Score);
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
}

void AOBRMainGameMode::ActivateShield()
{
	HUDWidget->SetShieldImageVisibility(true);
}

void AOBRMainGameMode::DeactivateShield()
{
	HUDWidget->SetShieldImageVisibility(false);
}