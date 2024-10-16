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
	WallFD->OnComponentHit.AddDynamic(this, &AOBRFloorRightCorner::OnForwardWallHit);
	WallFU->OnComponentHit.AddDynamic(this, &AOBRFloorRightCorner::OnForwardWallHit);
	WallLD->OnComponentHit.AddDynamic(this, &AOBRFloorRightCorner::OnSideWallHit);
	WallLU->OnComponentHit.AddDynamic(this, &AOBRFloorRightCorner::OnSideWallHit);
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

void AOBRFloorRightCorner::OnForwardWallHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	auto OBot = Cast<AOBRCharacter>(OtherActor);

	if (OBot != nullptr)
	{
		OBot->GetActorForwardVector();
		double dotResult = FVector::DotProduct(OBot->GetActorForwardVector(), Hit.ImpactNormal);

		if (FMath::IsNearlyEqual(dotResult, 1.0, 0.01))
		{
			if (!OBot->Dead())
			{
				if (TurnZone != nullptr) TurnZone->DestroyComponent();
				HitComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

				OBot->AddActorLocalOffset(FVector(-300.0f, 0.0f, 0.0f));
				OBot->UseShield(1.0f);
			}
		}
	}
}

void AOBRFloorRightCorner::OnSideWallHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	auto OBot = Cast<AOBRCharacter>(OtherActor);

	if (OBot != nullptr)
	{
		OBot->GetActorForwardVector();
		double dotResult = FVector::DotProduct(OBot->GetActorForwardVector(), Hit.ImpactNormal);

		if (FMath::IsNearlyEqual(dotResult, 1.0, 0.01))
		{
			if (!OBot->Dead())
			{
				if (TurnZone != nullptr) TurnZone->DestroyComponent();
				HitComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

				OBot->AddActorLocalOffset(FVector(-300.0f, 0.0f, 0.0f));
				OBot->UseShield(2.0f);
			}
		}
	}
}
