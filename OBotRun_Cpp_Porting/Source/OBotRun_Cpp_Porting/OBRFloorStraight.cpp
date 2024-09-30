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

	EnableSpawn = true;
}

void AOBRFloorStraight::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AOBRCharacter* OBot = Cast<AOBRCharacter>(OtherActor);

	if (OBot != nullptr)
	{
		OnPlayerReachedEndTrigger.Broadcast();
	}
}
