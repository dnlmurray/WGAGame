// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilitiesConfig.generated.h"

USTRUCT(BlueprintType)
struct FHealthConfiguration
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float HealthIncreaseAfterLocationPassed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float HealthIncreaseAfterLoad;
};


USTRUCT(BlueprintType)
struct FFaithConfiguration
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxFaith;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float FaithDecreasePerSecond;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float FaithDecreasePerKill;
};

USTRUCT(BlueprintType)
struct FWeaponAttackConfiguration
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Damage;
	
	// Nodes to track: (for most cases x and y are equal to 0)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector Start;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector End;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	uint8 NumberOfNodes;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool Debug;
};

USTRUCT(BlueprintType)
struct FDashConfiguration
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Strength;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Cooldown;
};


USTRUCT(BlueprintType)
struct FWhiteBarrierConfiguration
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CastDuration;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Duration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float FaithGainPerStandartAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float HealthGainPerKill;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Cooldown;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool Debug;
};

USTRUCT(BlueprintType)
struct FExorcismConfiguration
{
	GENERATED_BODY()
	
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Length;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Width;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float FaithGainPerKill;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float HealthGainPerKill;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Cooldown;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool Debug;
};

USTRUCT(BlueprintType)
struct FSkyImpulseConfiguration
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PushImpulse;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Cooldown;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool Debug;
};

USTRUCT(BlueprintType)
struct FPureDeathConfiguration
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ChargeTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float FaithGainPerKill;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Cooldown;
};


UCLASS(BlueprintType)
class WGAGAME_API UAbilitiesConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FHealthConfiguration HealthConfiguration;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FFaithConfiguration FaithConfiguration;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FWeaponAttackConfiguration WeaponAttackConfiguration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FDashConfiguration DashConfiguration;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FWhiteBarrierConfiguration WhiteBarrierConfiguration; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FExorcismConfiguration ExorcismConfiguration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSkyImpulseConfiguration SkyImpulseConfiguration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPureDeathConfiguration PureDeathConfiguration;
}; 
