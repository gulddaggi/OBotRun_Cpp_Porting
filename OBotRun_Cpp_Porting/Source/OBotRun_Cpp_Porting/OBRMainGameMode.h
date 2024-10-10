// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OBotRun_Cpp_Porting.h"
#include "GameFramework/GameModeBase.h"
#include "OBRMainGameMode.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDifficultyChanged);

/**
 * 
 */
UCLASS()
class OBOTRUN_CPP_PORTING_API AOBRMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AOBRMainGameMode();
	
	UPROPERTY()
	class AOBRFloorSpawner* Spawner;

	void AddScore(int Value);

	int GetDifficulty();

	FOnDifficultyChanged OnDifficultyChanged;

protected:
	virtual void BeginPlay() override;

private:
	TSubclassOf<class UOBRHUDWidget> HUDWidgetClass;

	UPROPERTY()
	class UOBRHUDWidget* HUDWidget;

	int Score;

	UPROPERTY(VisibleAnywhere)
	int Difficulty;

	void CheckDifficulty();
};
