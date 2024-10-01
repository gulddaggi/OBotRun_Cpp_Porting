// Fill out your copyright notice in the Description page of Project Settings.


#include "OBRFloor.h"

// Sets default values
AOBRFloor::AOBRFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Components
	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	EndTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	NextSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("NEXTSPAWNPOINT"));

	// Attachment
	SetRootComponent(FloorMesh);
	EndTrigger->SetupAttachment(GetRootComponent());
	NextSpawnPoint->SetupAttachment(GetRootComponent());

	// Set Properties
	FloorMesh->SetRelativeScale3D(FVector(3.0f, 3.0f, 1.0f));
	EndTrigger->SetBoxExtent(FVector(32.0f, 200.0f, 350.0f));
	NextSpawnPoint->SetRelativeScale3D(FVector((1.0f / 3.0f), (1.0f / 3.0f), 1.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_FLOOR(TEXT("/Game/StackOBot/Environment/Modular/SM_Modules_Floor.SM_Modules_Floor"));
	if (SM_FLOOR.Succeeded())
	{
		FloorMesh->SetStaticMesh(SM_FLOOR.Object);
	}
}

// Called when the game starts or when spawned
void AOBRFloor::BeginPlay()
{
	Super::BeginPlay();

	EndTrigger->OnComponentBeginOverlap.AddDynamic(this, &AOBRFloor::OnEndTriggerBeginOverlap);
}

// Called every frame
void AOBRFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FTransform AOBRFloor::GetNextSpawnTransform() const
{
	return NextSpawnPoint->GetComponentTransform();
}

void AOBRFloor::OnEndTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void AOBRFloor::DestroyFloor()
{
	Destroy();
}
