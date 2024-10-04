// Fill out your copyright notice in the Description page of Project Settings.


#include "OBRFloorSpawner.h"
#include "OBRFloorStraight.h"
#include "OBRFloorLeftCorner.h"
#include "OBRFloorRightCorner.h"
#include "OBRBlock.h"

// Sets default values
AOBRFloorSpawner::AOBRFloorSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MaxStraightFloorCount = 6;
	StraightFloorCount = 0;
	FTransform InitTransform(FRotator(0.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f));
	SpawnPoint = InitTransform;
}

// Called when the game starts or when spawned
void AOBRFloorSpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AOBRFloorSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOBRFloorSpawner::SpawnStraightFloor(int SpawnCount, bool EnableSpawnObs)
{
	for (int i = 0; i < SpawnCount; i++)
	{
		if (StraightFloorCount == MaxStraightFloorCount) SpawnCurveFloor();

		AOBRFloorStraight* SpawnedFloor = GetWorld()->SpawnActor<AOBRFloorStraight>(AOBRFloorStraight::StaticClass(), SpawnPoint);
		SpawnPoint = SpawnedFloor->GetNextSpawnTransform();
		SpawnedFloor->OnPlayerReachedEndTrigger.AddLambda([this]()->void {SpawnStraightFloor(); });

		if (EnableSpawnObs)
		{
			SpawnBlock(SpawnedFloor);
		}

		++StraightFloorCount;
	}
}

void AOBRFloorSpawner::SpawnCurveFloor()
{
	int32 min = 0;
	int32 max = 1;
	int32 Value = FMath::RandRange(min, max);

	if (Value == 1)
	{
		AOBRFloorLeftCorner* SpawnedCurveFloor = GetWorld()->SpawnActor<AOBRFloorLeftCorner>(AOBRFloorLeftCorner::StaticClass(), SpawnPoint);
		SpawnPoint = SpawnedCurveFloor->GetNextSpawnTransform();
		SpawnedCurveFloor->OnPlayerReachedEndTrigger.AddLambda([this]()->void {SpawnStraightFloor(); });
	}
	else
	{
		AOBRFloorRightCorner* SpawnedCurveFloor = GetWorld()->SpawnActor<AOBRFloorRightCorner>(AOBRFloorRightCorner::StaticClass(), SpawnPoint);
		SpawnPoint = SpawnedCurveFloor->GetNextSpawnTransform();
		SpawnedCurveFloor->OnPlayerReachedEndTrigger.AddLambda([this]()->void {SpawnStraightFloor(); });
	}

	StraightFloorCount = 0;
}

void AOBRFloorSpawner::SpawnBlock(AOBRFloorStraight* SpawnedFloor)
{
	int Index = FMath::RandRange(0, 2);

	FVector BlockVector = SpawnedFloor->GetBlockSpawnVector(Index);

	auto SpawnedBlock = GetWorld()->SpawnActor<AOBRBlock>(AOBRBlock::StaticClass(), SpawnedFloor->GetTransform());
	
	SpawnedBlock->AttachToActor(SpawnedFloor, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SpawnedBlock->SetActorRelativeLocation(BlockVector);
	SpawnedBlock->SetActorRelativeScale3D(FVector(0.6f, 0.6f, 2.0f));
}
