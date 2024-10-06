// Fill out your copyright notice in the Description page of Project Settings.


#include "OBRHUDWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UOBRHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ScoreText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ScoreTxt")));
	ShieldImage = Cast<UImage>(GetWidgetFromName(TEXT("ShieldImage")));

	EnableShieldImageVisibility = false;
	ShieldImage->SetVisibility(ESlateVisibility::Hidden);
}

void UOBRHUDWidget::UpdateScore(int Value)
{
	ScoreText->SetText(FText::FromString(FString::FromInt(Value)));
}

void UOBRHUDWidget::SetShieldImageVisibility(bool Value)
{
	EnableShieldImageVisibility = Value;

	if (EnableShieldImageVisibility)
	{
		ShieldImage->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ShieldImage->SetVisibility(ESlateVisibility::Hidden);
	}

}
