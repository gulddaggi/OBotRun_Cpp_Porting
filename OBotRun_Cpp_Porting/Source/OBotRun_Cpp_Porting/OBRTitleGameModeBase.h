// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OBotRun_Cpp_Porting.h"
#include "GameFramework/GameModeBase.h"
#include "OBRTitleGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class OBOTRUN_CPP_PORTING_API AOBRTitleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AOBRTitleGameModeBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UOBRTitleWidget> TitleWidgetClass;

protected:
	virtual void BeginPlay() override;

private:
	UOBRTitleWidget* TitleWidget;

	void SpawnFloor();

	FTransform SpawnPoint;
};
