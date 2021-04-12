// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"



#include "Ability.h"
#include "BombEnemyConfig.h"
#include "BombProjectile.h"

#include "PoisonBomb.generated.h"

#define ECC_Weapon ECollisionChannel::ECC_GameTraceChannel1

USTRUCT(BlueprintType)
struct FProjectileAngle
{
	GENERATED_BODY()
	
	FProjectileAngle(): Angle(0), IsSet(false) {};
	FProjectileAngle(float f): Angle(f), IsSet(true) {};

	UPROPERTY(BlueprintReadWrite)
	float Angle;

	UPROPERTY(BlueprintReadWrite)
	bool IsSet;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WGAGAME_API UPoisonBomb : public UAbility
{
public:
	// Implements projectile spawning: projectile collision notifies this Component and causes explosion
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable)
	void PlaceProjectile(FTransform Transform);

	UFUNCTION()
	void Place();

	UBombEnemyConfig const* GetConfig() const
	{
		return static_cast<UBombEnemyConfig const*>(ConfigurationData);
	}

	UFUNCTION(BlueprintCallable)
	FProjectileAngle CalculateAngle(FVector TargetLocation);
	
public:
	UPROPERTY(EditDefaultsOnly, Category="ActorSpawning")
	TSubclassOf<ABombProjectile> ProjectileVisual;
	
private:
	UPROPERTY()
	ABombProjectile* ProjectileRef;

	const float g = -980.0f;
};
