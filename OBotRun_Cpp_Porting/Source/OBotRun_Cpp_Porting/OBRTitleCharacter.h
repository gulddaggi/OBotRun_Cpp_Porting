// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OBotRun_Cpp_Porting.h"
#include "GameFramework/Character.h"
#include "OBRTitleCharacter.generated.h"

UCLASS()
class OBOTRUN_CPP_PORTING_API AOBRTitleCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AOBRTitleCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
