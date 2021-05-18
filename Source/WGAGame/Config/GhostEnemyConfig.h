// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseConfig.h"
#include "GhostEnemyConfig.generated.h"

USTRUCT(BlueprintType)
struct FGhostConfiguration
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ProjectileSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Cooldown;
};

UCLASS(BlueprintType)
class WGAGAME_API UGhostEnemyConfig : public UBaseConfig
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGhostConfiguration GhostConfiguration;
}; 
