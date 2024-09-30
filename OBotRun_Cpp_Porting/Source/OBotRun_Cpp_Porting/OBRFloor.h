// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OBotRun_Cpp_Porting.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "OBRFloor.generated.h"

UCLASS()
class OBOTRUN_CPP_PORTING_API AOBRFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOBRFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTransform GetNextSpawnTransform() const;
	
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent* FloorMesh;

	UPROPERTY(VisibleAnywhere, Category = Trigger)
	UBoxComponent* EndTrigger;

	UPROPERTY(VisibleAnywhere, Category = Point)
	UArrowComponent* NextSpawnPoint;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
