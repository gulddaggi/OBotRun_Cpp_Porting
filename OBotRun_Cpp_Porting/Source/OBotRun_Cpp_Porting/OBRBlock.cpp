// Fill out your copyright notice in the Description page of Project Settings.

#include "OBRBlock.h"
#include "OBRCharacter.h"

AOBRBlock::AOBRBlock()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	SetRootComponent(Mesh);
}

void AOBRBlock::BeginPlay()
{
	Super::BeginPlay();

	Mesh->OnComponentHit.AddDynamic(this, &AOBRBlock::OnBlockHit);
}

void AOBRBlock::OnBlockHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
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
				Destroy();
			}
		}
	}
}

