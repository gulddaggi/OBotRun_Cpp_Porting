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
	// Sets default values for this actor's properties
	AOBRFloor();

	FTransform GetNextSpawnTransform() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent* FloorMesh;

	UPROPERTY(VisibleAnywhere, Category = Trigger)
	UBoxComponent* EndTrigger;

	UPROPERTY(VisibleAnywhere, Category = Point)
	UArrowComponent* NextSpawnPoint;

	UFUNCTION()
	virtual void OnEndTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FTimerHandle DestoryTimerHandle;

	void DestroyFloor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FOnPlayerReachedEndTrigger OnPlayerReachedEndTrigger;

};
