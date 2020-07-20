// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnTurret.h"
//#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"

 // Sets default values
APawnTurret::APawnTurret()
{

}

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Rotate();
}

void APawnTurret::CalculateRotateDirection()
{
	// float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	// FRotator Rotation = FRotator(0.f, RotateAmount, 0.f);
	// RotationDirection = FQuat(Rotation);
}

void APawnTurret::Rotate() 
{
	AddActorLocalRotation(RotationDirection, true);
}

void APawnTurret::CheckFireCondition() 
{
	
	UE_LOG(LogTemp, Warning, TEXT("Fire Condition Checked"));
}