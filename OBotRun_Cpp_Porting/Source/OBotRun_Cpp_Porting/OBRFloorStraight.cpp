// Fill out your copyright notice in the Description page of Project Settings.

#include "OBRFloorStraight.h"
#include "OBRCharacter.h"

AOBRFloorStraight::AOBRFloorStraight()
{
	WallLD = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WALL1"));
	WallLU = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WALL2"));
	WallRD = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WALL3"));
	WallRU = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WALL4"));

	WallLD->SetupAttachment(GetRootComponent());
	WallLU->SetupAttachment(GetRootComponent());
	WallRD->SetupAttachment(GetRootComponent());
	WallRU->SetupAttachment(GetRootComponent());

	FloorMesh->SetRelativeLocation(FVector(350.0f, 0.0f, 0.0f));
	NextSpawnPoint->SetRelativeLocation(FVector(125.0f, 0.0f, 0.0f));
	EndTrigger->SetRelativeLocation(FVector(155.0f, 0.0f, 350.0f));

	EnableSpawn = true;
	BlockSpawnVectors = { FVector(90.0f, 0.0f, 5.0f), FVector(90.0f, -80.0f, 5.0f), FVector(90.0f, 80.0f, 5.0f) };
	CoinSpawnVectors = { FVector(-100.0f, 0.0f, 100.0f), FVector(-100.0f, -80.0f, 100.0f), FVector(-100.0f, 80.0f, 100.0f) };
	BlockSpawnedLineNum = -5;
	CoinSpawnedLineNum = -5;
	ShieldSpawnVector = FVector(0.0f, 0.0f, 130.0f);
}

FVector& AOBRFloorStraight::GetBlockSpawnVector(int Index)
{
	SetBlockSpawnedLineNum(Index);
	return BlockSpawnVectors[Index];
}

void AOBRFloorStraight::SetBlockSpawnedLineNum(int Index)
{
	BlockSpawnedLineNum = Index;
}

int AOBRFloorStraight::GetBlockSpawnedLineNum() const
{
	return BlockSpawnedLineNum;
}

FVector& AOBRFloorStraight::GetCoinSpawnVector(int Index)
{
	SetCoinSpawnedLineNum(Index);
	return CoinSpawnVectors[Index];
}

void AOBRFloorStraight::SetCoinSpawnedLineNum(int Index)
{
	CoinSpawnedLineNum = Index;
}

FVector& AOBRFloorStraight::GetShieldSpawnVector()
{
	return ShieldSpawnVector;
}
