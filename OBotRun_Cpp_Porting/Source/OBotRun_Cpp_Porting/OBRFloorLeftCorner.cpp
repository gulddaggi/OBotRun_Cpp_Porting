// Fill out your copyright notice in the Description page of Project Settings.

#include "OBRFloorLeftCorner.h"
#include "OBRCharacter.h"


AOBRFloorLeftCorner::AOBRFloorLeftCorner()
{
	// Create Components
	WallFD = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WALL1"));
	WallFU = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WALL2"));
	WallRD = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WALL3"));
	WallRU = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WALL4"));
	TurnZone = CreateDefaultSubobject<UBoxComponent>(TEXT("TURNZONE"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_WALL(TEXT("/Game/StackOBot/Environment/Modular/SM_Modular_Wall_250.SM_Modular_Wall_250"));
	if (SM_WALL.Succeeded())
	{
		WallFD->SetStaticMesh(SM_WALL.Object);
		WallFU->SetStaticMesh(SM_WALL.Object);
		WallRD->SetStaticMesh(SM_WALL.Object);
		WallRU->SetStaticMesh(SM_WALL.Object);
	}

	// Attachment
	WallFD->SetupAttachment(GetRootComponent());
	WallFU->SetupAttachment(GetRootComponent());
	WallRD->SetupAttachment(GetRootComponent());
	WallRU->SetupAttachment(GetRootComponent());
	TurnZone->SetupAttachment(GetRootComponent());

	// Set Properties
	FloorMesh->SetRelativeLocation(FVector(350.0f, 0.0f, 0.0f));
	WallFD->SetRelativeLocation(FVector(155.0f, 0.0f, 250.0f));
	WallFD->SetRelativeScale3D(FVector(1.0f, 1.0f, 2.0f));
	WallFU->SetRelativeLocation(FVector(155.0f, 0.0f, 750.0f));
	WallFU->SetRelativeScale3D(FVector(1.0f, 1.0f, 2.0f));
	WallRD->SetRelativeLocationAndRotation(FVector(0.0f, 155.0f, 250.0f), FRotator(0.0f, 90.0f, 0.0f));
	WallRD->SetRelativeScale3D(FVector(1.0f, 1.0f, 2.0f));
	WallRU->SetRelativeLocationAndRotation(FVector(0.0f, 155.0f, 750.0f), FRotator(0.0f, 90.0f, 0.0f));
	WallRU->SetRelativeScale3D(FVector(1.0f, 1.0f, 2.0f));

	NextSpawnPoint->SetRelativeLocationAndRotation(FVector(0.0f, -125.0f, 0.0f), FRotator(0.0f, -90.0f, 0.0f));
	NextSpawnPoint->SetRelativeScale3D(FVector((1.0f / 3.0f), (1.0f / 3.0f), 1.0f));
	EndTrigger->SetRelativeLocationAndRotation(FVector(0.0f, -155.0f, 350.0f), FRotator(0.0f, -90.0f, 0.0f));
	TurnZone->SetBoxExtent(FVector(120.0f, 120.0f, 500.0f));
}

void AOBRFloorLeftCorner::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto OBot = Cast<AOBRCharacter>(OtherActor);

	if (OBot != nullptr)
	{
		OnPlayerReachedEndTrigger.Broadcast();
	}
}