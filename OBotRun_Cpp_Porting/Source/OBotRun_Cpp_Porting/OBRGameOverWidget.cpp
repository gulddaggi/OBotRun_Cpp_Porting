// Fill out your copyright notice in the Description page of Project Settings.


#include "OBRGameOverWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"


void UOBRGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	RestartButton->OnClicked.AddDynamic(this, &UOBRGameOverWidget::OnRestartButtonClicked);
	QuitButton->OnClicked.AddDynamic(this, &UOBRGameOverWidget::OnQuitButtonClicked);	
}

void UOBRGameOverWidget::SetScore(int Value)
{
	ScoreText->SetText(FText::FromString(FString::FromInt(Value)));
}

void UOBRGameOverWidget::OnRestartButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainGame");
}

void UOBRGameOverWidget::OnQuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this, 0, EQuitPreference::Quit, false);
}