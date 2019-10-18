// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Earth.generated.h"

UCLASS()
class SHRINKINGPLANET_API AEarth : public AActor
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* EarthMesh;

	UPROPERTY(EditAnywhere)
		float AngularSpeed = 20.0f;

	// Sets default values for this pawn's properties
	AEarth();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetRadius() const;

};
