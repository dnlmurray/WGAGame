// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilitiesConfig.h"
#include "MeleeEnemyConfig.generated.h"

USTRUCT(BlueprintType)
struct FMeleeEnemyConfiguration
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHealth;
};

UCLASS(BlueprintType)
class WGAGAME_API UEnemyConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FMeleeEnemyConfiguration StatsConfiguration;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FWeaponAttackConfiguration WeaponAttackConfiguration;
}; 
