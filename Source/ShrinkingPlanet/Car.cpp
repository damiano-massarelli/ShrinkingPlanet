// Fill out your copyright notice in the Description page of Project Settings.

#include "Car.h"
#include <Components/StaticMeshComponent.h>
#include <Components/InputComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include "Earth.h"


// Sets default values
ACar::ACar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CarMesh"));
	CarMesh->SetupAttachment(RootComponent);
	RootComponent = CarMesh;

	ExplosionParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Explosion Particle"));
	ExplosionParticle->SetupAttachment(RootComponent);

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(RootComponent);

	Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	Cam->SetupAttachment(RootComponent);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();
	
	Distance = FVector::Distance(GetActorLocation(), Earth->GetActorLocation());
}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bCanMove) return;

	FVector NewLocation = GetActorLocation() + GetActorUpVector() * CarSpeed * DeltaTime;

	FVector FromEarth = NewLocation - Earth->GetActorLocation();
	FromEarth = FromEarth.GetClampedToMaxSize(Distance);

	SetActorLocation(Earth->GetActorLocation() + FromEarth);

	FRotator Rotation = UKismetMathLibrary::MakeRotFromXY(-FromEarth, GetActorRightVector());


	SetActorRotation(Rotation);
}

// Called to bind functionality to input
void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Steer", this, &ACar::Steer);
}

void ACar::Explode()
{
	bCanMove = false;

	ExplosionParticle->Activate();
	CarMesh->SetVisibility(false, true);

	ExplosionParticle->SetVisibility(true);
	CollisionComponent->Deactivate();
}

void ACar::Steer(float Value)
{
	if (!bCanMove) return;

	FRotator Rotator = GetActorRotation();

	Rotator.Roll -= SteerSpeed * Value;

	SetActorRotation(Rotator);
}


