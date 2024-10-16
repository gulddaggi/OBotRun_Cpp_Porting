// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OBotRun_Cpp_Porting.h"
#include "OBRFloor.h"
#include "OBRFloorRightCorner.generated.h"

/**
 * 
 */
UCLASS()
class OBOTRUN_CPP_PORTING_API AOBRFloorRightCorner : public AOBRFloor
{
	GENERATED_BODY()

private:
	AOBRFloorRightCorner();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent* WallFD;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent* WallFU;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent* WallLD;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent* WallLU;

	UPROPERTY(VisibleAnywhere, Category = Trigger)
	UBoxComponent* TurnZone;

	UFUNCTION()
	void OnTurnZoneBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnForwardWallHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnSideWallHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
