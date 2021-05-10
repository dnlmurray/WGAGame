// Copyright Epic Games, Inc. All Rights Reserved.


#include "WGAGameGameModeBase.h"

#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"

AWGAGameGameModeBase::AWGAGameGameModeBase():
	bWasCheckpointReached(false),
	CurrentEnemiesKilled(0),
	EnemiesKilledCheckpoint(0)
{
};

void AWGAGameGameModeBase::OnEnemyKill()
{
	CurrentEnemiesKilled++;
	StaticCast<AMainCharacter*>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->OnEnemyKill();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue,
		FString::Printf(TEXT("Killed enemies: %d"), CurrentEnemiesKilled));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue,
            FString::Printf(TEXT("Next threshold after: %d"), SpawnManager->CurrEnemiesKilledThresh.GetValue()));
	
	if (SpawnManager->CurrEnemiesKilledThresh && SpawnManager->CurrSpawnPointThresh &&
		SpawnManager->CurrEnemiesKilledThresh.GetIndex() < SpawnManager->CurrEnemiesKilledThresh.GetMaxIndex() &&
		SpawnManager->CurrSpawnPointThresh.GetIndex() < SpawnManager->CurrSpawnPointThresh.GetMaxIndex())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("THRESHOLD CHECKED"));

		if (GetLocationEnemiesKilled() >= SpawnManager->CurrEnemiesKilledThresh.GetValue())
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("THRESHOLD PASSED"));

			const int OldPointsNum = SpawnManager->CurrSpawnPointThresh.GetValue();
			const int OldIndex = SpawnManager->CurrSpawnPointThresh.GetIndex();
			const int MaxIndex = SpawnManager->CurrSpawnPointThresh.GetMaxIndex();

			SpawnManager->CurrSpawnPointThresh = ThresholdStruct(SpawnManager->SpawnPointsThreshes[OldIndex + 1],
			                                                     OldIndex + 1, MaxIndex);

			SpawnManager->CurrEnemiesKilledThresh = ThresholdStruct(SpawnManager->EnemiesKilledThreshes[OldIndex + 1],
                                                     OldIndex + 1, MaxIndex);
			
			const int DeltaPointsNum = SpawnManager->CurrSpawnPointThresh.GetValue() - OldPointsNum;
			for (int i = 0; i < DeltaPointsNum; ++i)
			{
				SpawnManager->SpawnOnRandomPoint();
			}
		}
		else
		{
			SpawnManager->SpawnOnRandomPoint();
		}
	} else
	{
		SpawnManager->SpawnOnRandomPoint();
	}

	if (SpawnManager->TotalEnemies == GetLocationEnemiesKilled())
	{
		SpawnManager->CheckSpawnerState();
	}
}

void AWGAGameGameModeBase::LoadCheckpoint()
{
	CurrentEnemiesKilled = EnemiesKilledCheckpoint;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CHECKPOINT LOADED"));
	
	if (SpawnManager != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("SM RESETED"));

		SpawnManager->Reset();
	}
	
	AMainCharacter* MC = StaticCast<AMainCharacter*>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	MC->ResetPlayer();
	MC->SetActorLocation(CheckpointSpawnLocation);


}

void AWGAGameGameModeBase::SaveCheckpoint(FVector PlayerLocation)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CHECKPOINT SAVED"));

	CheckpointSpawnLocation = PlayerLocation;
	bWasCheckpointReached = true;
	EnemiesKilledCheckpoint = CurrentEnemiesKilled;
}

void AWGAGameGameModeBase::SetSpawnManager(ASpawnManager* SM)
{
	SpawnManager = SM;
}


