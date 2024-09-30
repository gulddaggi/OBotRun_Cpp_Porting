// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OBotRun_Cpp_Porting.h"
#include "OBRFloor.h"
#include "OBRFloorStraight.generated.h"

/**
 * 
 */
UCLASS()
class OBOTRUN_CPP_PORTING_API AOBRFloorStraight : public AOBRFloor
{
	GENERATED_BODY()

private:
	AOBRFloorStraight();

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent* WallLD;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent* WallLU;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent* WallRD;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent* WallRU;
	
};
