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
	AOBRFloorSpawner();

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	void SpawnStraightFloor(int SpawnCount = 1, bool EnableSpawnObs = true);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Block)
	TSubclassOf<class AOBRBlock> BlockClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Coin)
	TSubclassOf<class AOBRCoin> CoinClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Floor)
	TSubclassOf<class AOBRFloorStraight> FloorStraightClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Floor)
	TSubclassOf<class AOBRFloorRightCorner> FloorRightCornerClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Floor)
	TSubclassOf<class AOBRFloorLeftCorner> FloorLeftCornerClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Shield)
	TSubclassOf<class AOBRShield> ShieldClass;

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
