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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UOBRHUDWidget> HUDWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UOBRGameOverWidget> GameOverWidgetClass;

	void AddScore(int Value);
	void GameOver();

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
