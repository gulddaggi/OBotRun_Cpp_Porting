// Fill out your copyright notice in the Description page of Project Settings.

#include "OBRFloorLeftCorner.h"
#include "OBRCharacter.h"


AOBRFloorLeftCorner::AOBRFloorLeftCorner()
{
	WallFD = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WALL1"));
	WallFU = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WALL2"));
	WallRD = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WALL3"));
	WallRU = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WALL4"));
	TurnZone = CreateDefaultSubobject<UBoxComponent>(TEXT("TURNZONE"));

	WallFD->SetupAttachment(GetRootComponent());
	WallFU->SetupAttachment(GetRootComponent());
	WallRD->SetupAttachment(GetRootComponent());
	WallRU->SetupAttachment(GetRootComponent());
	TurnZone->SetupAttachment(GetRootComponent());

	FloorMesh->SetRelativeLocation(FVector(350.0f, 0.0f, 0.0f));
	NextSpawnPoint->SetRelativeLocationAndRotation(FVector(0.0f, -125.0f, 0.0f), FRotator(0.0f, -90.0f, 0.0f));
	NextSpawnPoint->SetRelativeScale3D(FVector((1.0f / 3.0f), (1.0f / 3.0f), 1.0f));
	EndTrigger->SetRelativeLocationAndRotation(FVector(0.0f, -155.0f, 350.0f), FRotator(0.0f, -90.0f, 0.0f));
	TurnZone->SetBoxExtent(FVector(120.0f, 120.0f, 500.0f));
}

void AOBRFloorLeftCorner::BeginPlay()
{
	Super::BeginPlay();

	TurnZone->OnComponentBeginOverlap.AddDynamic(this, &AOBRFloorLeftCorner::OnTurnZoneBeginOverlap);
	WallFD->OnComponentHit.AddDynamic(this, &AOBRFloorLeftCorner::OnForwardWallHit);
	WallFU->OnComponentHit.AddDynamic(this, &AOBRFloorLeftCorner::OnForwardWallHit);
	WallRD->OnComponentHit.AddDynamic(this, &AOBRFloorLeftCorner::OnSideWallHit);
	WallRU->OnComponentHit.AddDynamic(this, &AOBRFloorLeftCorner::OnSideWallHit);
}

void AOBRFloorLeftCorner::OnTurnZoneBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto OBot = Cast<AOBRCharacter>(OtherActor);

	if (OBot != nullptr)
	{
		OBot->SetEnableTurn();
		TurnZone->DestroyComponent();
	}
}

void AOBRFloorLeftCorner::OnForwardWallHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
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
				OBot->UseShield(-1.0f);
			}
		}
	}
}

void AOBRFloorLeftCorner::OnSideWallHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
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
				OBot->UseShield(-2.0f);
			}
		}
	}
}

