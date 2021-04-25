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
	
public:
	UPROPERTY(BlueprintReadOnly)
	bool bWasCheckpointReached;

private:
	int CurrentEnemiesKilled;
	int EnemiesKilledCheckpoint;
	FVector CheckpointSpawnLocation;
	UPROPERTY()
	ASpawnManager* SpawnManager;
};
