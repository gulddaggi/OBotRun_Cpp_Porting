// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OBotRun_Cpp_Porting.h"
#include "Blueprint/UserWidget.h"
#include "OBRGameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class OBOTRUN_CPP_PORTING_API UOBRGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void SetScore(int Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UTextBlock* ScoreText;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UButton* RestartButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UButton* QuitButton;

private:
	UFUNCTION()
	void OnRestartButtonClicked();

	UFUNCTION()
	void OnQuitButtonClicked();
};
