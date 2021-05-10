// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


#include "SpawnManager.h"
#include "GameFramework/GameModeBase.h"
#include "WGAGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class WGAGAME_API AWGAGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AWGAGameGameModeBase();
	
public:
	// UFUNCTION(BlueprintImplementableEvent)
	// void OnPlayerDeath();

	UFUNCTION(BlueprintCallable)
	void OnEnemyKill();

	UFUNCTION(BlueprintCallable)
	void LoadCheckpoint();

	void SaveCheckpoint(FVector PlayerLocation);

	void SetSpawnManager(ASpawnManager* SM);

	int GetLocationEnemiesKilled() const
	{
		return CurrentEnemiesKilled - EnemiesKilledCheckpoint;
	}

	UFUNCTION(BlueprintImplementableEvent)
	void GetEvilForcePercent(float& percent);
	
public:
	UPROPERTY(BlueprintReadOnly)
	bool bWasCheckpointReached;
	
	UPROPERTY(BlueprintReadOnly)
	ASpawnManager* SpawnManager;
private:
	int CurrentEnemiesKilled;
	int EnemiesKilledCheckpoint;
	FVector CheckpointSpawnLocation;

};
