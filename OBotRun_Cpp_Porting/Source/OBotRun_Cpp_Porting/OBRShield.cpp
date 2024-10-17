// Fill out your copyright notice in the Description page of Project Settings.

#include "OBRShield.h"
#include "OBRCharacter.h"
#include "OBRMainGameMode.h"

AOBRShield::AOBRShield()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	SetRootComponent(Mesh);
}

void AOBRShield::BeginPlay()
{
	Super::BeginPlay();

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AOBRShield::OnShieldBeginoverlap);
}

void AOBRShield::OnShieldBeginoverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto OBot = Cast<AOBRCharacter>(OtherActor);

	if (OBot != nullptr)
	{
		Cast<AOBRMainGameMode>(GetWorld()->GetAuthGameMode())->ActivateShield();
		OBot->SetEnableShield(true);
		Destroy();
	}
}


