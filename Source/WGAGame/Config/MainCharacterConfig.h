// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BaseConfig.h"
#include "MainCharacterConfig.generated.h"


USTRUCT(BlueprintType)
struct FFaithConfiguration
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxFaith;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float FaithIncreasePerAttack;
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
	float FaithCost;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float HealthGainPerSecond;

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
	float FaithCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float HealthGainPerKill;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float EvilForceDecreasePerKill;
	
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
struct FAnimSpeed
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttackSpeed_1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttackSpeed_2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttackSpeed_3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float HitAnimSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float WhiteBarrierSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SkyImpulseSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PureDeathSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ExorcismSpeed;
};


UCLASS(BlueprintType)
class WGAGAME_API UMainCharacterConfig : public UBaseConfig
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FFaithConfiguration FaithConfiguration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FDashConfiguration DashConfiguration;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FWhiteBarrierConfiguration WhiteBarrierConfiguration; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FExorcismConfiguration ExorcismConfiguration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSkyImpulseConfiguration SkyImpulseConfiguration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FAnimSpeed AnimationsConfiguration;
}; 
