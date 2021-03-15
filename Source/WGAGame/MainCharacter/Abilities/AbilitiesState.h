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
		: NumberOfEnemiesKilledByExorcism(0)
		, CharacterIsUnderWhiteBarrierEffect(false)
		, CharacterIsInvincible(false)
	{ }

	int   NumberOfEnemiesKilledByExorcism;
	bool  CharacterIsUnderWhiteBarrierEffect;
	bool  CharacterIsInvincible;
};
