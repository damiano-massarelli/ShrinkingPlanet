// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHRINKINGPLANET_API UBaseUserWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidgetAnim))
		class UWidgetAnimation* UIA_GameOverAppear;

	UPROPERTY(meta = (BindWidget))
		class UCanvasPanel* GamePanel;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Distance;

	UPROPERTY(meta = (BindWidget))
		class UCanvasPanel* GameOverPanel;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* GameOverDistance;

public:
	void ShowGameOverHud(int32 Distance);

	void ShowGameHud();

	void UpdateDistance(int32 Value);
};
