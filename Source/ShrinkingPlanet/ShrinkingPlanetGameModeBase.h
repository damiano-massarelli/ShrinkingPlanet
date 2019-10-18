// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Earth.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShrinkingPlanetGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHRINKINGPLANET_API AShrinkingPlanetGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	FTimerHandle MissileGenerationHandler;

	void GenerateMissle();

public:
	UPROPERTY(EditAnywhere, Category = MissileGeneration)
		float TimeToGenerate = 5.0f;

	UPROPERTY(EditAnywhere, Category = MissileGeneration)
		float InitialDistance = 1000.0f;

	UPROPERTY(EditAnywhere, Category = MissileGeneration)
		TSubclassOf<class AMissile> MissileClass;


protected:
	virtual void BeginPlay() override;

};
