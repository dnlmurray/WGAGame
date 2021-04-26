// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "Containers/Map.h"
#include "SpawnManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpawnManagerStateNotifier, bool, IsAction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCheckpointResetNotifier);

struct ThresholdStruct
{
	ThresholdStruct() : value(0), index(-1), max_index(-1), bIsInitialised(false) {}
	
	ThresholdStruct(int val, int i, int max_i): value(val), index(i), max_index(max_i), bIsInitialised(true) {}
	
	ThresholdStruct(const ThresholdStruct& s): value(s.value), index(s.index), max_index(s.max_index), bIsInitialised(true) {}
	
	operator bool() const
	{
		return bIsInitialised;
	}

	int GetValue() const { return value; }

	int GetIndex() const { return index; }

	int GetMaxIndex() const { return max_index; }

private:
	int value;
	int index;
	int max_index;
	bool bIsInitialised;
};


UCLASS()
class WGAGAME_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	UFUNCTION()
	void OnBeginOverlap(AActor* MyOverlappedActor, AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	bool IsActivated() { return bIsActivated; }

	void Reset();

	void SpawnOnRandomPoint();
private:
	void CheckSpawnerState();

	void SpawnInitial();

	void SpawnEnemy(UClass* EnemyClass, AActor* Point);

	void SpawnOnPoint(AActor* Point);
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> SpawnPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UClass*> EnemiesClassesToSpawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> EnemiesPercents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> EnemiesMinNumbers;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> SpawnPointsThreshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> EnemiesKilledThreshes;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxEnemyNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinEnemyNumber;

	FSpawnManagerStateNotifier StateNotifier;

	FCheckpointResetNotifier ResetNotifier;
	
	ThresholdStruct CurrSpawnPointThresh;

	ThresholdStruct CurrEnemiesKilledThresh;
private:

	int EnemiesLeftToSpawn;
	
	bool bIsActivated;

	bool bWasActivatedInPast;

	bool bUseSpawnThreshes;
};
