// Fill out your copyright notice in the Description page of Project Settings.


#include "OBRCoin.h"
#include "OBRCharacter.h"
#include "OBRMainGameMode.h"

AOBRCoin::AOBRCoin()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	SetRootComponent(Mesh);

	Mesh->SetWorldRotation(FRotator(90.0f, 0.0f, 0.0f));
	CoinValue = 20;
}

void AOBRCoin::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AOBRCoin::OnCoinBeginoverlap);
}


void AOBRCoin::OnCoinBeginoverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto OBot = Cast<AOBRCharacter>(OtherActor);

	if (OBot != nullptr)
	{
		Cast<AOBRMainGameMode>(GetWorld()->GetAuthGameMode())->AddScore(CoinValue);
		Destroy();
	}
}