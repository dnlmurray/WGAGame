// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManager.h"

#include <cassert>
#include <string>


#include "Enemy.h"

// Sets default values
ASpawnManager::ASpawnManager()
: MaxEnemyNumber(0)
, MinEnemyNumber(0)
, EnemiesLeftToSpawn(0)
, bIsActivated(false)
, bWasActivatedInPast(false)
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
	assert(EnemiesClassesToSpawn.Num() == EnemiesClassesPercents.Num() == EnemiesMinNumber.Num());

	int sum = 0;
	for (int& num : EnemiesMinNumbers)
	{
		sum += num;
	}

	assert(sum <= EnemiesLeftToSpawn);
}

void ASpawnManager::OnBeginOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
	if (!bIsActivated && !bWasActivatedInPast)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enter spawner"));
		bIsActivated = true;

		EnemiesLeftToSpawn = MinEnemyNumber + (rand() % static_cast<int>(MaxEnemyNumber - MinEnemyNumber + 1));
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Blue, FString::Printf(TEXT("enemies to spawn: %d"), EnemiesLeftToSpawn));

		StateNotifier.Broadcast(bIsActivated);

		if (EnemiesLeftToSpawn > 0)
		{
			SpawnInitial();
		}
	}
}

void ASpawnManager::CheckSpawnerState()
{
	if (bIsActivated && EnemiesLeftToSpawn == 0)
	{
		bIsActivated = false;
		bWasActivatedInPast = true;
		StateNotifier.Broadcast(bIsActivated);
	}
}


void ASpawnManager::SpawnInitial()
{	
	for (auto& point : SpawnPoints)
	{
		SpawnOnPoint(point);
	}
}

void ASpawnManager::SpawnOnPoint(AActor* Point)
{
	if (EnemiesLeftToSpawn > 0)
	{
		bool SpawnedOnPoint = false;
		
		float val = static_cast<float>(rand())/ RAND_MAX;

		// first doing an iteration over essentials mobs
		
		int sum = 0;

		for (size_t i = 0; i < EnemiesMinNumbers.Num(); i++)
		{
			sum += EnemiesMinNumbers[i];
			if (val < (sum/EnemiesLeftToSpawn))
			{
				SpawnEnemy(EnemiesClassesToSpawn[i], Point);
				SpawnedOnPoint = true;
				EnemiesMinNumbers[i] --;
				break;
			}
		}

		// random mobs
		
		if (!SpawnedOnPoint)
		{
			float percent_sum = 0;
		
			for (size_t i = 0; i < EnemiesPercents.Num(); i++)
			{
				percent_sum += EnemiesPercents[i];
				if (val < percent_sum)
				{
					SpawnEnemy(EnemiesClassesToSpawn[i], Point);
					break;
				}
			}
		}
	}
}

void ASpawnManager::SpawnEnemy(UClass* EnemyClass, AActor* Point)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Blue, TEXT("spawned enemy"));

	auto SpawnLocation = Point->GetActorLocation();
	auto SpawnRotation = Point->GetActorRotation();
	
	const FTransform SpawnLocAndRotation(SpawnRotation, SpawnLocation, FVector::OneVector);
	AEnemy* SpawnedEnemy = GetWorld()->SpawnActorDeferred<AEnemy>(EnemyClass, SpawnLocAndRotation);

	assert(SpawnedEnemy != nullptr);
	
	SpawnedEnemy->SetSpawnManager(this);
	EnemiesLeftToSpawn --;
	SpawnedEnemy->FinishSpawning(SpawnLocAndRotation);
	SpawnedEnemy->SetActorHiddenInGame(true);
}
