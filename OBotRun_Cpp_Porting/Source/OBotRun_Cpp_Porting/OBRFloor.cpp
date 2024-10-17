// Fill out your copyright notice in the Description page of Project Settings.

#include "OBRFloor.h"
#include "OBRCharacter.h"
#include "OBRTitleCharacter.h"

AOBRFloor::AOBRFloor()
{
	PrimaryActorTick.bCanEverTick = false;

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	EndTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	NextSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("NEXTSPAWNPOINT"));

	SetRootComponent(FloorMesh);
	EndTrigger->SetupAttachment(GetRootComponent());
	NextSpawnPoint->SetupAttachment(GetRootComponent());

	FloorMesh->SetRelativeScale3D(FVector(3.0f, 3.0f, 1.0f));
	EndTrigger->SetBoxExtent(FVector(32.0f, 200.0f, 350.0f));
	NextSpawnPoint->SetRelativeScale3D(FVector((1.0f / 3.0f), (1.0f / 3.0f), 1.0f));
}

void AOBRFloor::BeginPlay()
{
	Super::BeginPlay();

	EndTrigger->OnComponentBeginOverlap.AddDynamic(this, &AOBRFloor::OnEndTriggerBeginOverlap);
}

FTransform AOBRFloor::GetNextSpawnTransform() const
{
	return NextSpawnPoint->GetComponentTransform();
}

void AOBRFloor::OnEndTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AOBRCharacter* OBot = Cast<AOBRCharacter>(OtherActor);
	AOBRTitleCharacter* TitleOBot = Cast<AOBRTitleCharacter>(OtherActor);

	if (OBot != nullptr || TitleOBot != nullptr)
	{
		OnPlayerReachedEndTrigger.Broadcast();
		OnPlayerReachedEndTrigger.Clear();
		GetWorld()->GetTimerManager().SetTimer(DestoryTimerHandle, this, &AOBRFloor::DestroyFloor, 1.0f);
	}
}

void AOBRFloor::DestroyFloor()
{
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	for (auto Act : AttachedActors) Act->Destroy();
	Destroy();
}
