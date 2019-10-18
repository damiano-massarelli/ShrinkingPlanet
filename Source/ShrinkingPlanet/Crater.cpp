// Fill out your copyright notice in the Description page of Project Settings.


#include "Crater.h"
#include "Car.h"
#include "DefaultPlayerController.h"

// Sets default values
ACrater::ACrater()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Component"));
	RootComponent = CollisionComponent;

	CraterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Crater Mesh"));
	CraterMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACrater::BeginPlay()
{
	Super::BeginPlay();
	
	FScriptDelegate Delegate;
	Delegate.BindUFunction(this, "OnOverlapBegin");
	CollisionComponent->OnComponentBeginOverlap.Add(Delegate);
}

// Called every frame
void ACrater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACrater::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACar* Car = Cast<ACar>(OtherActor);

	if (Car)
	{
		Car->Explode();

		UWorld* World = GetWorld();
		UE_LOG(LogTemp, Warning, TEXT("H"));
		if (World != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("K"));
			ADefaultPlayerController* PlayerController = Cast<ADefaultPlayerController>(World->GetFirstPlayerController());
			if (PlayerController != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("K2"));
				PlayerController->GameOver();
			}
		}
	}
}

