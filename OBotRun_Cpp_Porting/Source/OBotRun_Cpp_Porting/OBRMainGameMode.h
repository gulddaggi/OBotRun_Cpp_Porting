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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UOBRHUDWidget> HUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UOBRGameOverWidget> GameOverWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Spawner)
	TSubclassOf<class AOBRFloorSpawner> FloorSpawnerClass;

	void AddScore(int Value);
	void GameOver();
	void ActivateShield();
	void DeactivateShield();
	int GetDifficulty();

	FOnDifficultyChanged OnDifficultyChanged;

protected:
	virtual void BeginPlay() override;

private:
	UOBRHUDWidget* HUDWidget;
	UOBRGameOverWidget* GameOverWidget;

	UPROPERTY(VisibleAnywhere)
	int Difficulty;

	int Score;

	void CheckDifficulty();
};
