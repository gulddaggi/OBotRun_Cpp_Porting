// Fill out your copyright notice in the Description page of Project Settings.


#include "OBRShield.h"
#include "OBRCharacter.h"
#include "OBRMainGameMode.h"

// Sets default values
AOBRShield::AOBRShield()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_SHIELD(TEXT("/Game/PolygonIcons/Meshes/SM_Icon_Shield_01.SM_Icon_Shield_01"));
	if (SM_SHIELD.Succeeded())
	{
		Mesh->SetStaticMesh(SM_SHIELD.Object);
	}

	SetRootComponent(Mesh);

	Mesh->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}

// Called when the game starts or when spawned
void AOBRShield::BeginPlay()
{
	Super::BeginPlay();
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AOBRShield::OnShieldBeginoverlap);
}

// Called every frame
void AOBRShield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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


