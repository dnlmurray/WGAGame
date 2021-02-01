// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "SpawnManager.generated.h"

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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(AActor* MyOverlappedActor, AActor* OtherActor);

private:

	void SpawnWave();

	void SpawnEnemy(UClass* EnemyClass, FVector SpawnLocation, FRotator SpawnRotation);

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> SpawnPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UClass*> EnemiesClassesToSpawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> EnemiesClassesPercents;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int WavesNumber;
	
	int CurrentEnemyNumber;

private:
	// Number of enemies spawned in current wave
	
	int CurrentWaveNumber;

	bool IsActivated;
};
