// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank_GameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"

#define OUT

void ATank_GameModeBase::BeginPlay() 
{
	Super::BeginPlay();

	HandleGameStart();
}


void ATank_GameModeBase::ActorDied(AActor* DeadActor) 
{
	// Check type of actor death. If Enemy, score points. If Player -> Lose Condition
	UE_LOG(LogTemp, Warning, TEXT("Actor Has Died!"));

	if(DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		HandleGameOver(false);

		// When the player dies, disabled their controller state
		if(PlayerControllerRef)
		{
			PlayerControllerRef->SetPlayerEnabledState(false);
		}

	}
	// If the dead actor is a turret, assign it to DestroyedTurret and act on it
	else if(APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();

		if(--TargetTurrets <= 0)
		{
			HandleGameOver(true);
		}
	}

}


void ATank_GameModeBase::HandleGameStart() 
{
	// Initialise the start countdown, turret activation, pawn check
	
	TargetTurrets = GetTargetTurretCount();

	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	// Call blueprint version GameStart()
	GameStart();

	// Enable the player controller after GameStart
	if(PlayerControllerRef)
	{
		PlayerControllerRef->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnabledState, true);
		
		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
	}
}


void ATank_GameModeBase::HandleGameOver(bool PlayerWon) 
{
	// If player has destroyed all turrets, win
	// if player is destroyed show loss
	// call blueprint version of 
	GameOver(PlayerWon);
}


int32 ATank_GameModeBase::GetTargetTurretCount() 
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), OUT TurretActors);

	return TurretActors.Num();
}