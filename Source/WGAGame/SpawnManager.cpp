// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManager.h"

#include <cassert>
#include <string>


#include "Enemy.h"

// Sets default values
ASpawnManager::ASpawnManager()
	: WavesNumber(1)
	, CurrentEnemyNumber(0)
	, CurrentWaveNumber(0)
	, bIsActivated(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	OnActorBeginOverlap.AddDynamic(this, &ASpawnManager::OnBeginOverlap);
}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();

	assert(EnemiesClassesToSpawn.Num() >= 1);
	assert(EnemiesClassesToSpawn.Num() == EnemiesClassesPercents.Num());

	float sum = 0;
	for (float p : EnemiesClassesPercents)
	{
		sum += p;
	}

	assert(sum == 1.f);
}

// Called every frame
void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsActivated && CurrentEnemyNumber == 0)
	{
		if (CurrentWaveNumber < WavesNumber)
		{
			CurrentWaveNumber ++;
			SpawnWave();
		}
		else
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("All waves clear!"));
			bIsActivated = false;
			StateNotifier.Broadcast(bIsActivated);
		}
	}

}

void ASpawnManager::OnBeginOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
	if (!bIsActivated && CurrentWaveNumber == 0)
	{	
		bIsActivated = true;

		CurrentWaveNumber = 1; // spawn first wave

		StateNotifier.Broadcast(bIsActivated);

		if (CurrentWaveNumber <= WavesNumber)
		{
			SpawnWave();
		}
	}
}

void ASpawnManager::SpawnWave()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
	//                                FString::Printf(TEXT("Begin wave number %d"), CurrentWaveNumber));
	
	for (auto& point : SpawnPoints)
	{
		// choosing an enemy to spawn randomly

		float val = static_cast<float>(rand())/ RAND_MAX;

		// we have at least one enemy to spawn
		float sum = 0;
		
		for (size_t i = 0; i < EnemiesClassesPercents.Num(); i++)
		{
			sum += EnemiesClassesPercents[i];
			if (val < sum)
			{
				SpawnEnemy(EnemiesClassesToSpawn[i], point->GetActorLocation(), point->GetActorRotation());
				break;
			}
		}
	}
}

void ASpawnManager::SpawnEnemy(UClass* EnemyClass, FVector SpawnLocation, FRotator SpawnRotation)
{
	const FTransform SpawnLocAndRotation(SpawnRotation, SpawnLocation, FVector::OneVector);
	AEnemy* SpawnedEnemy = GetWorld()->SpawnActorDeferred<AEnemy>(EnemyClass, SpawnLocAndRotation);

	assert(SpawnedEnemy != nullptr);
	
	SpawnedEnemy->SetSpawnManager(this);
	CurrentEnemyNumber++;
	SpawnedEnemy->FinishSpawning(SpawnLocAndRotation);
	SpawnedEnemy->SetActorHiddenInGame(true);
}
