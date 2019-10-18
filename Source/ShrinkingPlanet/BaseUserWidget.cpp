// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseUserWidget.h"
#include <Components/CanvasPanel.h>
#include <Components/TextBlock.h>
#include <Text.h>

void UBaseUserWidget::ShowGameOverHud(int32 Distance)
{
	GamePanel->SetVisibility(ESlateVisibility::Hidden);

	GameOverDistance->SetText(FText::FromString(FString::Printf(TEXT("%d m"), Distance)));

	GameOverPanel->SetVisibility(ESlateVisibility::Visible);
	PlayAnimation(UIA_GameOverAppear);
}

void UBaseUserWidget::ShowGameHud()
{
	GameOverPanel->SetVisibility(ESlateVisibility::Hidden);
	GamePanel->SetVisibility(ESlateVisibility::Visible);
}

void UBaseUserWidget::UpdateDistance(int32 Value)
{
	Distance->SetText(FText::FromString(FString::Printf(TEXT("%d m"), Value)));
}
