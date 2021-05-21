// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseConfig.h"
#include "BombEnemyConfig.generated.h"

USTRUCT(BlueprintType)
struct FBombConfiguration
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ProjectileSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Radius;
};

UCLASS(BlueprintType)
class WGAGAME_API UBombEnemyConfig : public UBaseConfig
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FBombConfiguration BombConfiguration;
}; 
