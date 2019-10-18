// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DefaultPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHRINKINGPLANET_API ADefaultPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		class UBaseUserWidget* Widget;

	float Distance = 0.0f;

public:
	UPROPERTY(EditAnywhere, Category = Widget)
		TSubclassOf<class UBaseUserWidget> WidgetClass;

	void GameOver();


	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

};
