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
}