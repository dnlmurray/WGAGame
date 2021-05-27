// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BaseConfig.h"
#include "MainCharacterConfig.generated.h"


USTRUCT(BlueprintType)
struct FFaithConfiguration
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxFaith;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FaithInitialAmount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FaithIncreasePerAttack;
};

USTRUCT(BlueprintType)
struct FDashConfiguration
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Strength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cooldown;
};


USTRUCT(BlueprintType)
struct FWhiteBarrierConfiguration
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CastDuration;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FaithCost;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HealthGainPerSecond;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cooldown;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool Debug;
};

USTRUCT(BlueprintType)
struct FExorcismConfiguration
{
	GENERATED_BODY()
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Length;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FaithCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HealthGainPerKill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EvilForceDecreasePerKill;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cooldown;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool Debug;
};

USTRUCT(BlueprintType)
struct FSkyImpulseConfiguration
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FaithCost;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PushImpulse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EvilForceDecrease;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cooldown;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Debug;
};

USTRUCT(BlueprintType)
struct FAnimSpeed
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackSpeed_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackSpeed_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackSpeed_3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HitAnimSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WhiteBarrierSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SkyImpulseSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PureDeathSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExorcismSpeed;
};


UCLASS(BlueprintType)
class WGAGAME_API UMainCharacterConfig : public UBaseConfig
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FFaithConfiguration FaithConfiguration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDashConfiguration DashConfiguration;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWhiteBarrierConfiguration WhiteBarrierConfiguration; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FExorcismConfiguration ExorcismConfiguration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkyImpulseConfiguration SkyImpulseConfiguration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAnimSpeed AnimationsConfiguration;
}; 
