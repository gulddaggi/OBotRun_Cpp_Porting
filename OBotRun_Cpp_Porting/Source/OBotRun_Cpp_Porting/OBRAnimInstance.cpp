// Fill out your copyright notice in the Description page of Project Settings.


#include "OBRAnimInstance.h"

UOBRAnimInstance::UOBRAnimInstance()
{
	IsInAir = false;
}

void UOBRAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Character = Cast<ACharacter>(TryGetPawnOwner());
	if (Character != nullptr)
	{
		IsInAir = Character->GetMovementComponent()->IsFalling();
	}
}


