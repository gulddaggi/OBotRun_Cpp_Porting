// Fill out your copyright notice in the Description page of Project Settings.


#include "OBRTitleGameModeBase.h"
#include "OBRTitleWidget.h"
#include "OBRFloorStraight.h"

AOBRTitleGameModeBase::AOBRTitleGameModeBase()
{
	FTransform InitTransform(FRotator(0.0f, 0.0f, 0.0f), FVector(-1000.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f));
	SpawnPoint = InitTransform;
}

void AOBRTitleGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	TitleWidget = CreateWidget<UOBRTitleWidget>(GetWorld(), TitleWidgetClass);
	TitleWidget->AddToViewport();
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

	for (int i = 0; i < 3; i++)
	{
		SpawnFloor();
	}
}

void AOBRTitleGameModeBase::SpawnFloor()
{
	AOBRFloorStraight* SpawnedFloor = GetWorld()->SpawnActor<AOBRFloorStraight>(AOBRFloorStraight::StaticClass(), SpawnPoint);
	SpawnPoint = SpawnedFloor->GetNextSpawnTransform();
	SpawnedFloor->OnPlayerReachedEndTrigger.AddLambda([this]()-> void { SpawnFloor(); });
}