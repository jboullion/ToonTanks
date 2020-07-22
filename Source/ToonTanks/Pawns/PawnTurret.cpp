// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnTurret.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

 // Sets default values
APawnTurret::APawnTurret()
{

}

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this,0));
}

void APawnTurret::HandleDestruction() 
{
	Super::HandleDestruction();
	Destroy();
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugCircle(
		GetWorld(), // const UWorld * InWorld,
		GetActorLocation(), // FVector Center,
		FireRange, // float Radius
		16, // int32 Segments,
		FColor(255, 0, 0), // const FColor & Color,
		true, // bool bPersistentLines,
		100.f, // float LifeTime,
		0, // uint8 DepthPriority,
		10, // float Thickness,
		FVector(1.f, 0.f, 0.f), // FVector YAxis,
		FVector(0.f, 1.f, 0.f), // FVector ZAxis,
		false // bool bDrawAxis
	);

	if( ! PlayerPawn || ! CheckInRange() ) {
		return;
	}

	RotateTurret(PlayerPawn->GetActorLocation());

}

bool APawnTurret::CheckInRange() 
{
	return GetDistanceToPlayer() <= FireRange;
}

void APawnTurret::CheckFireCondition() 
{

	if( !PlayerPawn || !PlayerPawn->GetIsPlayerAlive() ) 
	{
		return;
	}

	if( CheckInRange() )
	{
		Fire();
	}

}

float APawnTurret::GetDistanceToPlayer() 
{
	if(!PlayerPawn) return 0.f;

	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}