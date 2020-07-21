// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Tank_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:

	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);

public:

	void ActorDied(AActor* DeadActor);

protected:

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent, Category="Game Actions")
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent, Category="Game Actions")
	void GameOver(bool PlayerWon);
};
