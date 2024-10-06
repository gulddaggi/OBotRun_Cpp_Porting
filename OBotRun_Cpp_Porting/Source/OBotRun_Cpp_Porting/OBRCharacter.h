// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OBotRun_Cpp_Porting.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "OBRCharacter.generated.h"

UCLASS()
class OBOTRUN_CPP_PORTING_API AOBRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOBRCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

private:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputMappingContext* Context;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* MoverightOBotAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* JumpOBotAction;

	FTimerHandle MoveForwardTimerHandle;
	FTimerHandle JumpTimerHandle;
	FTimerHandle AddScoreHandle;

	bool EnableJump;
	bool EnableTurn;
	float JumpDelay;
	int RunningScore;
	bool IsDead;

	void SetEnableJump();
	void MoveRightOBot(const FInputActionValue& Value);
	void JumpOBot();
	void MoveForward();
	void Turn(float AxisValue);
	void AddScore();

public:
	void SetEnableTurn();
};
