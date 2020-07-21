// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank_GameModeBase.h"

void ATank_GameModeBase::BeginPlay() 
{
	
}

void ATank_GameModeBase::ActorDied(AActor* DeadActor) 
{
	// Check type of actor death. If Enemy, score points. If Player -> Lose Condition
	UE_LOG(LogTemp, Warning, TEXT("Actor Has Died!"));
}

void ATank_GameModeBase::HandleGameStart() 
{
	// Initialise the start countdown, turret activation, pawn check
	// Call blueprint version GameStart()
}

void ATank_GameModeBase::HandleGameOver(bool PlayerWon) 
{
	// If player has destroyed all turrets, win
	// if player is destroyed show loss
	// call blueprint version of GameOver(bool)
}