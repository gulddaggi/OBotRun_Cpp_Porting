// Fill out your copyright notice in the Description page of Project Settings.


#include "OBRMainGameMode.h"
#include "OBRCharacter.h"
#include "OBRFloorSpawner.h"

AOBRMainGameMode::AOBRMainGameMode()
{
	DefaultPawnClass = AOBRCharacter::StaticClass();
}

void AOBRMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	Spawner = GetWorld()->SpawnActor<AOBRFloorSpawner>(AOBRFloorSpawner::StaticClass());
	Spawner->SpawnStraightFloor(6, false);
}
