// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Particles/ParticleSystemComponent.h>
#include <Camera/CameraComponent.h>
#include "GameFramework/Pawn.h"
#include <Components/SphereComponent.h>
#include "Car.generated.h"

UCLASS()
class SHRINKINGPLANET_API ACar : public APawn
{
	GENERATED_BODY()	

private:
	bool bCanMove = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this pawn's properties
	ACar();

	float Distance = 0.0f;

	UPROPERTY(EditAnywhere, Category = Visual)
		UStaticMeshComponent* CarMesh;

	UPROPERTY(EditAnywhere, Category = Visual)
		UParticleSystemComponent* ExplosionParticle;

	UPROPERTY(EditAnywhere)
		UCameraComponent* Cam;

	UPROPERTY(EditAnywhere, Category = Collision)
		USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, Category = Gameplay)
		class AEarth* Earth;

	UPROPERTY(EditAnywhere, Category = Gameplay)
		float SteerSpeed = 0.5f;

	UPROPERTY(EditAnywhere, Category = Gameplay)
		float CarSpeed = 200.0f;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Explode();

	UFUNCTION()
		void Steer(float Val);

};
