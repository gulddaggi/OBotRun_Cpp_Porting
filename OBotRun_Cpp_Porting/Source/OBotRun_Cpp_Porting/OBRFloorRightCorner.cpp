// Fill out your copyright notice in the Description page of Project Settings.

#include "OBRFloorRightCorner.h"
#include "OBRCharacter.h"


AOBRFloorRightCorner::AOBRFloorRightCorner()
{
	// Create Components
	WallFD = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WALL1"));
	WallFU = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WALL2"));
	WallLD = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WALL3"));
	WallLU = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WALL4"));
	TurnZone = CreateDefaultSubobject<UBoxComponent>(TEXT("TURNZONE"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_WALL(TEXT("/Game/StackOBot/Environment/Modular/SM_Modular_Wall_250.SM_Modular_Wall_250"));
	if (SM_WALL.Succeeded())
	{
		WallFD->SetStaticMesh(SM_WALL.Object);
		WallFU->SetStaticMesh(SM_WALL.Object);
		WallLD->SetStaticMesh(SM_WALL.Object);
		WallLU->SetStaticMesh(SM_WALL.Object);
	}

	// Attachment
	WallFD->SetupAttachment(GetRootComponent());
	WallFU->SetupAttachment(GetRootComponent());
	WallLD->SetupAttachment(GetRootComponent());
	WallLU->SetupAttachment(GetRootComponent());
	TurnZone->SetupAttachment(GetRootComponent());

	// Set Properties
	FloorMesh->SetRelativeLocation(FVector(350.0f, 0.0f, 0.0f));
	WallFD->SetRelativeLocation(FVector(155.0f, 0.0f, 250.0f));
	WallFD->SetRelativeScale3D(FVector(1.0f, 1.0f, 2.0f));
	WallFU->SetRelativeLocation(FVector(155.0f, 0.0f, 750.0f));
	WallFU->SetRelativeScale3D(FVector(1.0f, 1.0f, 2.0f));
	WallLD->SetRelativeLocationAndRotation(FVector(0.0f, -155.0f, 250.0f), FRotator(0.0f, -90.0f, 0.0f));
	WallLD->SetRelativeScale3D(FVector(1.0f, 1.0f, 2.0f));
	WallLU->SetRelativeLocationAndRotation(FVector(0.0f, -155.0f, 750.0f), FRotator(0.0f, -90.0f, 0.0f));
	WallLU->SetRelativeScale3D(FVector(1.0f, 1.0f, 2.0f));

	NextSpawnPoint->SetRelativeLocationAndRotation(FVector(0.0f, 125.0f, 0.0f), FRotator(0.0f, 90.0f, 0.0f));
	NextSpawnPoint->SetRelativeScale3D(FVector((1.0f / 3.0f), (1.0f / 3.0f), 1.0f));
	EndTrigger->SetRelativeLocationAndRotation(FVector(0.0f, 155.0f, 350.0f), FRotator(0.0f, 90.0f, 0.0f));
	TurnZone->SetBoxExtent(FVector(120.0f, 120.0f, 500.0f));

}

void AOBRFloorRightCorner::BeginPlay()
{
	Super::BeginPlay();

	TurnZone->OnComponentBeginOverlap.AddDynamic(this, &AOBRFloorRightCorner::OnTurnZoneBeginOverlap);
}


void AOBRFloorRightCorner::OnEndTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto OBot = Cast<AOBRCharacter>(OtherActor);

	if (OBot != nullptr)
	{
		OnPlayerReachedEndTrigger.Broadcast();
		GetWorld()->GetTimerManager().SetTimer(DestoryTimerHandle, this, &AOBRFloorRightCorner::DestroyFloor, 2.0f);
	}
}

void AOBRFloorRightCorner::OnTurnZoneBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto OBot = Cast<AOBRCharacter>(OtherActor);

	if (OBot != nullptr)
	{
		OBot->SetEnableTurn();
		TurnZone->DestroyComponent();
	}
}