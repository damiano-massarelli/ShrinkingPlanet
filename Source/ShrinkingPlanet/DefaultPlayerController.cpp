// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerController.h"
#include "BaseUserWidget.h"

void ADefaultPlayerController::GameOver()
{
	PrimaryActorTick.bCanEverTick = true;

	bShowMouseCursor = true;
	Widget->ShowGameOverHud(static_cast<int32>(Distance));
}

void ADefaultPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Distance += DeltaSeconds * 20.0f;
	Widget->UpdateDistance(static_cast<int32>(Distance));
}

void ADefaultPlayerController::BeginPlay()
{
	Super::BeginPlay();

	Widget = CreateWidget<UBaseUserWidget>(this, WidgetClass);

	if (Widget)
	{
		Widget->AddToViewport();		
	}
}
