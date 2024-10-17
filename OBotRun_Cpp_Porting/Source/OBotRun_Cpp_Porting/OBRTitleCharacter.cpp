// Fill out your copyright notice in the Description page of Project Settings.

#include "OBRTitleCharacter.h"

AOBRTitleCharacter::AOBRTitleCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(40.0f, 66.0f);
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -60.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
}

void AOBRTitleCharacter::BeginPlay()
{
	Super::BeginPlay();

	DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void AOBRTitleCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(FVector(10.0f, 0.0f, 0.0f));
}

void AOBRTitleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

