// Fill out your copyright notice in the Description page of Project Settings.

#include "Missile.h"
#include <Components/StaticMeshComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <Engine/Public/TimerManager.h>
#include <Engine/World.h>
#include "Crater.h"
#include "Car.h"


// Sets default values
AMissile::AMissile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Component"));
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Pawn"));
	RootComponent = CollisionComponent;

	MissileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Missile Mesh"));
	MissileMesh->SetupAttachment(RootComponent);

	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	Light->SetupAttachment(RootComponent);

	SmokeParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Particle"));
	SmokeParticle->SetupAttachment(RootComponent);

	ExplosionParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Explosion Particle"));
	ExplosionParticle->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
}

// Called when the game starts or when spawned
void AMissile::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->OnComponentHit.AddDynamic(this, &AMissile::OnHit);
	SmokeParticle->Activate(true);

	ProjectileMovementComponent->InitialSpeed = Velocity;
}

// Called every frame
void AMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMissile::Fire(const FVector& Direction)
{
	ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed;
}

void AMissile::OnHit(UPrimitiveComponent* HitComponent, AActor* otherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	// Generate crater
	UWorld* World = GetWorld();
	AEarth* Earth = Cast<AEarth>(otherActor);
	ACar* Car = Cast<ACar>(otherActor);

	if (World && Earth) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;

		FVector HitPoint = Hit.ImpactPoint;
		FVector FromEarth = HitPoint - Earth->GetActorLocation();
		FromEarth = FromEarth.GetClampedToSize(2 * Earth->GetRadius(), 2 * Earth->GetRadius());

		FRotator Rotation = UKismetMathLibrary::MakeRotFromZ(FromEarth);
		FVector Position = Earth->GetActorLocation() + FromEarth;

		ACrater* Crater = World->SpawnActor<ACrater>(CraterClass, Position, Rotation, SpawnParams);

		// Make this crater a child of Earth
		Crater->AttachToActor(Earth, FAttachmentTransformRules::KeepWorldTransform);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot GetWorld"));
	}

	if (Car) {
		UE_LOG(LogTemp, Warning, TEXT("Game Over"));
	}

	// Destroy this Missile
	MissileMesh->SetVisibility(false);

	ExplosionParticle->Activate();
	SmokeParticle->Deactivate();
	CollisionComponent->Deactivate();
	Light->DestroyComponent();

	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &AMissile::DestroyAfter, 10.0f, false);
}

void AMissile::DestroyAfter()
{
	Destroy();
}
