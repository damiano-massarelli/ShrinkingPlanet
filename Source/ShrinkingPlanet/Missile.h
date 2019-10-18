// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Particles/ParticleSystemComponent.h>
#include "Earth.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Components/PointLightComponent.h>
#include "Missile.generated.h"

UCLASS()
class SHRINKINGPLANET_API AMissile : public AActor
{
	GENERATED_BODY()

private:
	void DestroyAfter();

public:	
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = Movement)
		UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, Category = Movement)
		float Velocity = 200.0f;

	UPROPERTY(EditAnywhere, Category = Visual)
		UStaticMeshComponent* MissileMesh;

	UPROPERTY(EditAnywhere, Category = Visual)
		TSubclassOf<class ACrater> CraterClass;

	UPROPERTY(EditAnywhere, Category = Visual)
		UParticleSystemComponent* SmokeParticle;

	UPROPERTY(EditAnywhere, Category = Visual)
		UParticleSystemComponent* ExplosionParticle;

	UPROPERTY(EditAnywhere, Category = Visual)
		UPointLightComponent* Light;

	// Sets default values for this actor's properties
	AMissile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Fire(const FVector& Direction);

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* otherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};
