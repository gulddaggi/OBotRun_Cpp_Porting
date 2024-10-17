// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OBotRun_Cpp_Porting.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "OBRFloor.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPlayerReachedEndTrigger);

UCLASS()
class OBOTRUN_CPP_PORTING_API AOBRFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	AOBRFloor();

	FTransform GetNextSpawnTransform() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	UStaticMeshComponent* FloorMesh;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = Trigger)
	UBoxComponent* EndTrigger;

	UPROPERTY(VisibleAnywhere, Category = Point)
	UArrowComponent* NextSpawnPoint;

	UFUNCTION()
	void OnEndTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FTimerHandle DestoryTimerHandle;

	void DestroyFloor();

public:	
	FOnPlayerReachedEndTrigger OnPlayerReachedEndTrigger;
};
