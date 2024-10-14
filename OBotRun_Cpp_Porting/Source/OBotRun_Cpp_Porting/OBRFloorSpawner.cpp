// Fill out your copyright notice in the Description page of Project Settings.


#include "OBRFloorSpawner.h"
#include "OBRFloorStraight.h"
#include "OBRFloorLeftCorner.h"
#include "OBRFloorRightCorner.h"
#include "OBRBlock.h"
#include "OBRCoin.h"
#include "OBRMainGameMode.h"
#include "OBRShield.h"

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
	BlockCountProbArray = { 0.3f, 0.7f };
	EnableThreeBlocksCount = 0;
	CurrentDifficulty = 1;
	ShieldSpawnRemainCount = 10;
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

			if (EnableSpawnObs && StraightFloorCount != 0)
			{
				SpawnLineArray = { 0, 1, 2 };
				SpawnBlock(SpawnedFloor);
				SpawnCoin(SpawnedFloor);
				if (ShieldSpawnRemainCount == 0) SpawnShield(SpawnedFloor);
				else --ShieldSpawnRemainCount;

			}

			++StraightFloorCount;
			UE_LOG(LogTemp, Warning, TEXT("Count : %d"), ShieldSpawnRemainCount);
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
	int BlockCount = 0;
	if (CurrentDifficulty == 3)
	{
		if (EnableThreeBlocksCount != 0)
		{
			BlockCountProbArray = { 0.1f, 0.3f, 0.6f };
			--EnableThreeBlocksCount;
		}
		else
		{
			BlockCountProbArray = { 0.1f, 0.3f, 0.4f, 0.2f };
		}
	}

	float prob = FMath::RandRange(0.0f, 1.0f);
	for (int i = 0; i < BlockCountProbArray.Num(); i++)
	{
		if (prob <= BlockCountProbArray[i])
		{
			BlockCount = i;
			break;
		}
		else
		{
			prob -= BlockCountProbArray[i];
		}
	}

	if (BlockCount == 3) EnableThreeBlocksCount = 10;

	for (int i = 0; i < BlockCount; i++)
	{
		int RandomValue = FMath::RandRange(0, SpawnLineArray.Num() - 1);
		int Index = SpawnLineArray[RandomValue];
		SpawnLineArray.RemoveAt(RandomValue);

		FVector BlockVector = SpawnedFloor->GetBlockSpawnVector(Index);
		auto SpawnedBlock = GetWorld()->SpawnActor<AOBRBlock>(AOBRBlock::StaticClass(), SpawnedFloor->GetTransform());

		SpawnedBlock->AttachToActor(SpawnedFloor, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		SpawnedBlock->SetActorRelativeLocation(BlockVector);
		SpawnedBlock->SetActorRelativeScale3D(FVector(0.6f, 0.6f, 2.0f));
	}
}

void AOBRFloorSpawner::SpawnCoin(AOBRFloorStraight* SpawnedFloor)
{
	if (SpawnLineArray.Num() == 0) return;

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
		CurrentDifficulty = MainGameMode->GetDifficulty();

		switch (CurrentDifficulty)
		{
			case 2:
				BlockCountProbArray = { 0.1f, 0.5f, 0.4f };
				break;

			case 3:
				BlockCountProbArray = { 0.1f, 0.3f, 0.4f, 0.2f };
				break;

			default:
				break;
		}
	}

}

void AOBRFloorSpawner::SpawnShield(class AOBRFloorStraight* SpawnedFloor)
{
	ShieldSpawnRemainCount = FMath::RandRange(7, 10);

	FVector ShieldVector = SpawnedFloor->GetShieldSpawnVector();
	auto SpawnedShield = GetWorld()->SpawnActor<AOBRShield>(AOBRShield::StaticClass(), SpawnedFloor->GetTransform());

	SpawnedShield->AttachToActor(SpawnedFloor, FAttachmentTransformRules::SnapToTargetIncludingScale);
	SpawnedShield->SetActorRelativeLocation(ShieldVector);
	SpawnedShield->SetActorRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	SpawnedShield->SetActorRelativeScale3D(FVector(1.5f, 1.5f, 4.5f));
}