// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OBotRun_Cpp_Porting.h"
#include "Blueprint/UserWidget.h"
#include "OBRTitleWidget.generated.h"

/**
 * 
 */
UCLASS()
class OBOTRUN_CPP_PORTING_API UOBRTitleWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UButton* StartButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UButton* QuitButton;

	UFUNCTION()
	void OnStartButtonClicked();

	UFUNCTION()
	void OnQuitButtonClicked();

private:

};
