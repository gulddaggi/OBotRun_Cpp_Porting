// Fill out your copyright notice in the Description page of Project Settings.


#include "OBRFloorStraight.h"
#include "OBRCharacter.h"


AOBRFloorStraight::AOBRFloorStraight()
{
	// Create Components
	WallLD = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WALL1"));
	WallLU = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WALL2"));
	WallRD = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WALL3"));
	WallRU = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WALL4"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_WALL(TEXT("/Game/StackOBot/Environment/Modular/SM_Modular_Wall_250.SM_Modular_Wall_250"));
	if (SM_WALL.Succeeded())
	{
		WallLD->SetStaticMesh(SM_WALL.Object);
		WallLU->SetStaticMesh(SM_WALL.Object);
		WallRD->SetStaticMesh(SM_WALL.Object);
		WallRU->SetStaticMesh(SM_WALL.Object);
	}

	// Attachment
	WallLD->SetupAttachment(GetRootComponent());
	WallLU->SetupAttachment(GetRootComponent());
	WallRD->SetupAttachment(GetRootComponent());
	WallRU->SetupAttachment(GetRootComponent());

	// Set Properties
	FloorMesh->SetRelativeLocation(FVector(350.0f, 0.0f, 0.0f));
	WallLD->SetRelativeLocationAndRotation(FVector(0.0f, -155.0f, 250.0f), FRotator(0.0f, -90.0f, 0.0f));
	WallLD->SetRelativeScale3D(FVector(1.0f, 1.0f, 2.0f));
	WallLU->SetRelativeLocationAndRotation(FVector(0.0f, -155.0f, 750.0f), FRotator(0.0f, -90.0f, 0.0f));
	WallLU->SetRelativeScale3D(FVector(1.0f, 1.0f, 2.0f));
	WallRD->SetRelativeLocationAndRotation(FVector(0.0f, 155.0f, 250.0f), FRotator(0.0f, 90.0f, 0.0f));
	WallRD->SetRelativeScale3D(FVector(1.0f, 1.0f, 2.0f));
	WallRU->SetRelativeLocationAndRotation(FVector(0.0f, 155.0f, 750.0f), FRotator(0.0f, 90.0f, 0.0f));
	WallRU->SetRelativeScale3D(FVector(1.0f, 1.0f, 2.0f));

	NextSpawnPoint->SetRelativeLocation(FVector(125.0f, 0.0f, 0.0f));
	EndTrigger->SetRelativeLocation(FVector(155.0f, 0.0f, 350.0f));

	// Init Values
	EnableSpawn = true;
	BlockSpawnVectors = { FVector(90.0f, 0.0f, 5.0f), FVector(90.0f, -80.0f, 5.0f), FVector(90.0f, 80.0f, 5.0f) };
	CoinSpawnVectors = { FVector(-100.0f, 0.0f, 100.0f), FVector(-100.0f, -80.0f, 100.0f), FVector(-100.0f, 80.0f, 100.0f) };
	BlockSpawnedLineNum = -5;
	CoinSpawnedLineNum = -5;
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