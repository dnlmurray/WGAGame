// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilitiesState.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WGAGAME_API UAbilitiesState : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAbilitiesState()
		: IsUnderWhiteBarrierEffect(false)
		, IsInvincible(false)
		, IsUnderPureDeathEffect(false)
	{ }

	bool  IsUnderWhiteBarrierEffect;
	
	bool  IsInvincible;
	
	UPROPERTY(BlueprintReadWrite)
	bool  IsUnderPureDeathEffect;

	UPROPERTY(BlueprintReadWrite)
	bool  IsUnderExorcismEffect;
};
