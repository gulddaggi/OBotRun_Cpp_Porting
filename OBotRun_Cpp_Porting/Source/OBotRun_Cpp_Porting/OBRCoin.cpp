// Fill out your copyright notice in the Description page of Project Settings.


#include "OBRCoin.h"
#include "OBRCharacter.h"
#include "OBRMainGameMode.h"

// Sets default values
AOBRCoin::AOBRCoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_COIN(TEXT("/Game/StarterContent/Shapes/Shape_Torus.Shape_Torus"));
	if (SM_COIN.Succeeded())
	{
		Mesh->SetStaticMesh(SM_COIN.Object);
	}

	SetRootComponent(Mesh);

	Mesh->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	Mesh->SetWorldRotation(FRotator(90.0f, 0.0f, 0.0f));

	CoinValue = 20;
}

// Called when the game starts or when spawned
void AOBRCoin::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AOBRCoin::OnCoinBeginoverlap);
}

// Called every frame
void AOBRCoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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