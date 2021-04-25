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
}

void AWGAGameGameModeBase::LoadCheckpoint()
{
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
}

void AWGAGameGameModeBase::SetSpawnManager(ASpawnManager* SM)
{
	SpawnManager = SM;
}


