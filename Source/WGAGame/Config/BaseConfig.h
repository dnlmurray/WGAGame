// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseConfig.generated.h"

USTRUCT(BlueprintType)
struct FHealthConfiguration
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHealth;
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

UCLASS(BlueprintType)
class WGAGAME_API UBaseConfig : public UDataAsset
{
public:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FHealthConfiguration HealthConfiguration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FWeaponAttackConfiguration WeaponAttackConfiguration;
}; 
