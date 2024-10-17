// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OBotRun_Cpp_Porting.h"
#include "Blueprint/UserWidget.h"
#include "OBRHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class OBOTRUN_CPP_PORTING_API UOBRHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
public:
	void UpdateScore(int Value);
	void SetShieldImageVisibility(bool Value);

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ScoreText;

	UPROPERTY(meta = (BindWidget))
	class UImage* ShieldImage;

	bool EnableShieldImageVisibility;
};
