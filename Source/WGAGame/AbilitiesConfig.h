// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilitiesConfig.generated.h"

USTRUCT(BlueprintType)
struct FFaithConfiguration
{
	GENERATED_USTRUCT_BODY()

	FFaithConfiguration() { }
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaximumFaith;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float FaithDecreasingPerSecond;
};

USTRUCT(BlueprintType)
struct FWeaponAttackConfiguration
{
	GENERATED_USTRUCT_BODY()
	
	FWeaponAttackConfiguration() { }
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Damage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool Debug;
};

USTRUCT(BlueprintType)
struct FWhiteBarrierConfiguration
{
	GENERATED_USTRUCT_BODY()

	FWhiteBarrierConfiguration() { }
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Duration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float FaithGainPerStandartAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool Debug;
};

USTRUCT(BlueprintType)
struct FExorcismConfiguration
{
	GENERATED_USTRUCT_BODY()

	FExorcismConfiguration() { }
	
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Range;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SweepShapeRadius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Cooldown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float FaithGain;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool Debug;
};

UCLASS(BlueprintType)
class WGAGAME_API UAbilitiesConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FFaithConfiguration FaithConfiguration;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FWeaponAttackConfiguration WeaponAttackConfiguration;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FWhiteBarrierConfiguration WhiteBarrierConfiguration; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FExorcismConfiguration ExorcismConfiguration;
};
