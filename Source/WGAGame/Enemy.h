// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SpawnManager.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class WGAGAME_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override final;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(BlueprintReadOnly)
	float MaxHealth;
	
	UPROPERTY(BlueprintReadWrite)
	float Health;

	void SetSpawnManager(ASpawnManager* SpawnManager);

private:
	void OnEnemyDeath();
	
private:
	UPROPERTY()
	ASpawnManager* SpawnManager;
};

