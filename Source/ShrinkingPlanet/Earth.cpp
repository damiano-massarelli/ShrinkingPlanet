// Fill out your copyright notice in the Description page of Project Settings.

#include "Earth.h"
#include <Components/InputComponent.h>
#include <GameFramework/Controller.h>
#include <Components/StaticMeshComponent.h>


// Sets default values
AEarth::AEarth()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	EarthMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EarthMesh"));

	EarthMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEarth::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEarth::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AEarth::GetRadius() const
{
	return GetActorScale3D().X;
}

