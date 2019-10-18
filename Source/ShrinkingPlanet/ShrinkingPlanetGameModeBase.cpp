// Fill out your copyright notice in the Description page of Project Settings.

#include "ShrinkingPlanetGameModeBase.h"
#include "Earth.h"
#include <Engine/Public/TimerManager.h>
#include <Engine/World.h>
#include "Missile.h"


void AShrinkingPlanetGameModeBase::GenerateMissle()
{
	UWorld* World = GetWorld();

	if (World) {
		FVector RandomPosition = FMath::VRand();
		RandomPosition.Normalize();
		RandomPosition *= InitialDistance;

		FVector DirectionToEarth = FVector{ 0.0f } -RandomPosition;
		DirectionToEarth.Normalize();

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;

		AMissile* Missile = World->SpawnActor<AMissile>(MissileClass, RandomPosition, DirectionToEarth.Rotation(), SpawnParams);

		if (Missile) 
		{
			Missile->Fire(DirectionToEarth);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot GetWorld"));
	}
}

void AShrinkingPlanetGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(MissileGenerationHandler, this, &AShrinkingPlanetGameModeBase::GenerateMissle, TimeToGenerate, true);
}
