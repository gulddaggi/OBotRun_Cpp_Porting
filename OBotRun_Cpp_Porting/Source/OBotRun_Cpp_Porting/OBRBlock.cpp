// Fill out your copyright notice in the Description page of Project Settings.


#include "OBRBlock.h"
#include "OBRCharacter.h"

// Sets default values
AOBRBlock::AOBRBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BLOCK(TEXT("/Game/StackOBot/Environment/Props/SM_Crate.SM_Crate"));
	if (SM_BLOCK.Succeeded())
	{
		Mesh->SetStaticMesh(SM_BLOCK.Object);
	}

	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned
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
			OBot->Dead();
		}
	}
}

