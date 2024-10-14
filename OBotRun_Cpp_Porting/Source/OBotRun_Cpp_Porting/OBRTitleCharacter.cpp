// Fill out your copyright notice in the Description page of Project Settings.


#include "OBRTitleCharacter.h"

// Sets default values
AOBRTitleCharacter::AOBRTitleCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(40.0f, 66.0f);
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -60.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
}

// Called when the game starts or when spawned
void AOBRTitleCharacter::BeginPlay()
{
	Super::BeginPlay();

	DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

// Called every frame
void AOBRTitleCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(FVector(10.0f, 0.0f, 0.0f));

}

// Called to bind functionality to input
void AOBRTitleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

