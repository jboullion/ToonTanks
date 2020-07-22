// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Tank_GameModeBase.generated.h"

class APawnTurret;
class APawnTank;
class APlayerControllerBase;

UCLASS()
class TOONTANKS_API ATank_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	APawnTank* PlayerTank;
	int32 TargetTurrets = 0;
	APlayerControllerBase* PlayerControllerRef;

	int32 GetTargetTurretCount();

	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);

public:

	void ActorDied(AActor* DeadActor);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
	int32 StartDelay = 3;

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent, Category="Game Actions")
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent, Category="Game Actions")
	void GameOver(bool PlayerWon);
};
