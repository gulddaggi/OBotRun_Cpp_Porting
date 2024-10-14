// Fill out your copyright notice in the Description page of Project Settings.


#include "OBRTitleWidget.h"
#include "Components/Button.h"

void UOBRTitleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	StartButton->OnClicked.AddDynamic(this, &UOBRTitleWidget::OnStartButtonClicked);
	QuitButton->OnClicked.AddDynamic(this, &UOBRTitleWidget::OnQuitButtonClicked);
}

void UOBRTitleWidget::OnStartButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainGame");
}

void UOBRTitleWidget::OnQuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this, 0, EQuitPreference::Quit, false);
}
