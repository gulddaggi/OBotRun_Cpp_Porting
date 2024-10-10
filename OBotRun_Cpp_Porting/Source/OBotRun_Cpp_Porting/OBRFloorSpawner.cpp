// Fill out your copyright notice in the Description page of Project Settings.


#include "OBRFloorSpawner.h"
#include "OBRFloorStraight.h"
#include "OBRFloorLeftCorner.h"
#include "OBRFloorRightCorner.h"
#include "OBRBlock.h"
#include "OBRCoin.h"
#include "OBRMainGameMode.h"

// Sets default values
AOBRFloorSpawner::AOBRFloorSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MaxStraightFloorCount = 6;
	StraightFloorCount = 0;
	CoinSpawnCount = 5;
	FTransform InitTransform(FRotator(0.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f));
	SpawnPoint = InitTransform;
	SpawnLineArray = { 0, 1, 2 };
	BlockCountArray = { 0, 1 };
}

// Called when the game starts or when spawned
void AOBRFloorSpawner::BeginPlay()
{
	Super::BeginPlay();

	auto MainGameMode = Cast<AOBRMainGameMode>(GetWorld()->GetAuthGameMode());

	if (MainGameMode != nullptr)
	{
		MainGameMode->OnDifficultyChanged.AddLambda([this]() -> void { SetBlockCountArray(); });
	}
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
		else
		{
			AOBRFloorStraight* SpawnedFloor = GetWorld()->SpawnActor<AOBRFloorStraight>(AOBRFloorStraight::StaticClass(), SpawnPoint);
			SpawnPoint = SpawnedFloor->GetNextSpawnTransform();
			SpawnedFloor->OnPlayerReachedEndTrigger.AddLambda([this]()-> void { SpawnStraightFloor(1, true); });

			if (EnableSpawnObs)
			{
				SpawnLineArray = { 0, 1, 2 };
				SpawnBlock(SpawnedFloor);
				SpawnCoin(SpawnedFloor);
			}

			++StraightFloorCount;
		}
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
		SpawnedCurveFloor->OnPlayerReachedEndTrigger.AddLambda([this]()-> void { SpawnStraightFloor(1, true); });
	}
	else
	{
		AOBRFloorRightCorner* SpawnedCurveFloor = GetWorld()->SpawnActor<AOBRFloorRightCorner>(AOBRFloorRightCorner::StaticClass(), SpawnPoint);
		SpawnPoint = SpawnedCurveFloor->GetNextSpawnTransform();
		SpawnedCurveFloor->OnPlayerReachedEndTrigger.AddLambda([this]()-> void { SpawnStraightFloor(1, true); });
	}

	StraightFloorCount = 0;
}

void AOBRFloorSpawner::SpawnBlock(AOBRFloorStraight* SpawnedFloor)
{
	int BlockCount = BlockCountArray[FMath::RandRange(0, BlockCountArray.Num()-1)];
	UE_LOG(LogTemp, Warning, TEXT("BlockCount : %d"), BlockCount);
	int RandomValue = FMath::RandRange(0, SpawnLineArray.Num()-1);
	int Index = SpawnLineArray[RandomValue];
	SpawnLineArray.RemoveAt(RandomValue);

	FVector BlockVector = SpawnedFloor->GetBlockSpawnVector(Index);

	auto SpawnedBlock = GetWorld()->SpawnActor<AOBRBlock>(AOBRBlock::StaticClass(), SpawnedFloor->GetTransform());
	
	SpawnedBlock->AttachToActor(SpawnedFloor, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SpawnedBlock->SetActorRelativeLocation(BlockVector);
	SpawnedBlock->SetActorRelativeScale3D(FVector(0.6f, 0.6f, 2.0f));
}

void AOBRFloorSpawner::SpawnCoin(AOBRFloorStraight* SpawnedFloor)
{
	int RandomValue = FMath::RandRange(0, SpawnLineArray.Num() - 1);
	int Index = SpawnLineArray[RandomValue];

	FVector StartVector = SpawnedFloor->GetCoinSpawnVector(Index);
	for (int i = 0; i < CoinSpawnCount; i++)
	{
		FVector CoinSpawnVector = FVector(StartVector.X + (i * 35.0f), StartVector.Y, StartVector.Z);

		auto SpawnedBlock = GetWorld()->SpawnActor<AOBRCoin>(AOBRCoin::StaticClass(), SpawnedFloor->GetTransform());

		SpawnedBlock->AttachToActor(SpawnedFloor, FAttachmentTransformRules::KeepWorldTransform);
		SpawnedBlock->SetActorRelativeLocation(CoinSpawnVector);
		SpawnedBlock->SetActorRelativeScale3D(FVector(0.3f, 0.3f, 1.0f));
	}

}

void AOBRFloorSpawner::SetBlockCountArray()
{
	auto MainGameMode = Cast<AOBRMainGameMode>(GetWorld()->GetAuthGameMode());

	if (MainGameMode != nullptr)
	{
		int Difficulty = MainGameMode->GetDifficulty();

		switch (Difficulty)
		{
			case 2:
				BlockCountArray = { 0, 1, 2 };
				UE_LOG(LogTemp, Warning, TEXT("Difficulty 2"));
				break;

			case 3:
				BlockCountArray = { 0, 1, 2, 3 };
				UE_LOG(LogTemp, Warning, TEXT("Difficulty 3"));
				break;

			default:
				break;
		}
	}

}
