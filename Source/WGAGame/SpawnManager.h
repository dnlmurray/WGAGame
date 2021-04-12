// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "Containers/Map.h"
#include "SpawnManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpawnManagerStateNotifier, bool, IsAction);

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

	void SpawnOnPoint(AActor* Point);
	
private:
	void CheckSpawnerState();

	void SpawnInitial();

	void SpawnEnemy(UClass* EnemyClass, AActor* Point);

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
	int MaxEnemyNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinEnemyNumber;

	FSpawnManagerStateNotifier StateNotifier;
	
private:

	int EnemiesLeftToSpawn;
	
	bool bIsActivated;

	bool bWasActivatedInPast;
};
