 // Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManager.h"

#include <cassert>
#include <string>


#include "Enemy.h"
#include "WGAGameGameModeBase.h"

// Sets default values
ASpawnManager::ASpawnManager()
: MaxEnemyNumber(0)
, MinEnemyNumber(0)
, bIsActivated(false)
, EnemiesLeftToSpawn(0)
, bWasActivatedInPast(false)
, bUseSpawnThreshes(false)
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
	assert(EnemiesKilledThreshes.Num() == SpawnPointsThreshes.Num());

	int sum = 0;
	for (int& num : EnemiesMinNumbers)
	{
		sum += num;
	}

	assert(sum <= EnemiesLeftToSpawn);

	for (int i = 0; i < SpawnPointsThreshes.Num(); ++i)
	{
		assert(SpawnPointsThreshes[i] <= SpawnPoints.Num());
		if (i > 0)
		{
			assert(SpawnPointsThreshes[i] >= SpawnPointsThreshes[i-1]);
		}
	}
	
	TotalEnemies = EnemiesLeftToSpawn = MinEnemyNumber + (rand() % static_cast<int>(MaxEnemyNumber - MinEnemyNumber + 1));

	for (int i = 0; i < EnemiesKilledThreshes.Num(); ++i)
	{
		assert(EnemiesKilledThreshes[i] <= EnemiesLeftToSpawn);
		if (i > 0)
		{
			assert(EnemiesKilledThreshes[i] >= EnemiesKilledThreshes[i-1]);
		}
	}

	if (SpawnPointsThreshes.Num() > 0 && EnemiesKilledThreshes.Num() > 0)
	{
		bUseSpawnThreshes = true;
	}
}

void ASpawnManager::OnBeginOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
	if (!bIsActivated && !bWasActivatedInPast)
	{
		AWGAGameGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AWGAGameGameModeBase>();
		GameMode->SetSpawnManager(this);
		
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enter spawner"));
		bIsActivated = true;

		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Blue, FString::Printf(TEXT("enemies to spawn: %d"), EnemiesLeftToSpawn));

		if (bUseSpawnThreshes)
		{
			CurrSpawnPointThresh = ThresholdStruct(SpawnPointsThreshes[0], 0, SpawnPointsThreshes.Num()-1);
			CurrEnemiesKilledThresh = ThresholdStruct(EnemiesKilledThreshes[0], 0, EnemiesKilledThreshes.Num()-1);
		}
		
		StateNotifier.Broadcast(bIsActivated);

		if (EnemiesLeftToSpawn > 0)
		{
			SpawnInitial();
		}
		
		UpdateEvilForce();
	}
}

void ASpawnManager::CheckSpawnerState()
{
	if (bIsActivated && EnemiesLeftToSpawn == 0)
	{
		bIsActivated = false;
		bWasActivatedInPast = true;
		StateNotifier.Broadcast(bIsActivated);
		UpdateEvilForce();
	}
}


void ASpawnManager::SpawnInitial()
{
	int SpawnPointsNum = SpawnPoints.Num();

	if (bUseSpawnThreshes && CurrSpawnPointThresh && CurrEnemiesKilledThresh)
	{
		SpawnPointsNum = CurrSpawnPointThresh.GetValue();
	}
	
	for (int i = 0; i < SpawnPointsNum; ++i)
	{
		SpawnOnPoint(SpawnPoints[i]);
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

void ASpawnManager::Reset()
{
	EnemiesLeftToSpawn = 0;
	bIsActivated = false;
	bWasActivatedInPast = false;
	ResetNotifier.Broadcast();
	StateNotifier.Broadcast(bIsActivated);
}

void ASpawnManager::SpawnOnRandomPoint()
{
	const int i = rand() % static_cast<int>(EnemiesClassesToSpawn.Num() + 1);
	
	SpawnOnPoint(SpawnPoints[i]);
}
