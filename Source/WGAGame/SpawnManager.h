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
	ThresholdStruct() : value(0), index(-1), max_index(-1) {}
	
	ThresholdStruct(int val, int i, int max_i): value(val), index(i), max_index(max_i) {}
	
	ThresholdStruct(const ThresholdStruct& s): value(s.value), index(s.index), max_index(s.max_index) {}
	
	int GetValue() const { return value; }

	int GetIndex() const { return index; }

	int GetMaxIndex() const { return max_index; }

private:
	int value;
	int index;
	int max_index;
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

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateEvilForce();

	void Reset();

	void SpawnOnRandomPoint();

	void CheckSpawnerState();
private:
	void SpawnInitial();

	void SpawnEnemy(UClass* EnemyClass, AActor* Point);

	void SpawnOnPoint(AActor* Point);
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawner|Points")
	TArray<AActor*> SpawnPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawner|Classes")
	TArray<UClass*> EnemiesClassesToSpawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawner|Classes")
	TArray<float> EnemiesPercents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawner|Classes")
	TArray<int> EnemiesMinNumbers;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawner")
	TArray<int> SpawnPointsThreshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawner")
	TArray<int> EnemiesKilledThreshes;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawner")
	int MaxEnemyNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawner")
	int MinEnemyNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Evil Force")
	float MinPercent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Evil Force")
	float MaxPercent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Evil Force")
	float EvilForceIncreasePerSecond;
	
	FSpawnManagerStateNotifier StateNotifier;

	FCheckpointResetNotifier ResetNotifier;
	
	TOptional<ThresholdStruct> CurrSpawnPointThresh;

	TOptional<ThresholdStruct> CurrEnemiesKilledThresh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Spawner|Status")
	bool bIsActivated;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Spawner|Status")
	int EnemiesLeftToSpawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Spawner|Status")
	int TotalEnemies;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Spawner|Status")
	int PointsActivated;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Spawner|Status")
	int TotalPoints;

	bool bWasActivatedInPast;

	bool bUseSpawnThreshes;
};
