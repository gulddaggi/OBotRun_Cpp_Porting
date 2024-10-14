// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OBotRun_Cpp_porting.h"
#include "GameFramework/Actor.h"
#include "OBRFloorSpawner.generated.h"

UCLASS()
class OBOTRUN_CPP_PORTING_API AOBRFloorSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOBRFloorSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SpawnStraightFloor(int SpawnCount = 1, bool EnableSpawnObs = true);

private:
	void SpawnCurveFloor();
	void SpawnBlock(class AOBRFloorStraight* SpawnedFloor);
	void SpawnCoin(class AOBRFloorStraight* SpawnedFloor);
	void SpawnShield(class AOBRFloorStraight* SpawnedFloor);
	void SetBlockCountArray();

	int StraightFloorCount;
	int MaxStraightFloorCount;
	int CoinSpawnCount;
	int EnableThreeBlocksCount;
	int CurrentDifficulty;
	int ShieldSpawnRemainCount;
	FTransform SpawnPoint;
	TArray<int32> SpawnLineArray;
	TArray<float> BlockCountProbArray;
};
