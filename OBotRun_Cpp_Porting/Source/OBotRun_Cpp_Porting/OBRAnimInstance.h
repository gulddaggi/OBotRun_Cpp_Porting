// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OBotRun_Cpp_Porting.h"
#include "Animation/AnimInstance.h"
#include "OBRAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class OBOTRUN_CPP_PORTING_API UOBRAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	UOBRAnimInstance();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsInAir;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
