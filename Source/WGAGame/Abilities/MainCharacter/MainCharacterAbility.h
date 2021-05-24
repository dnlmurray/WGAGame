// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"



#include "../Ability.h"
#include "../../Config/MainCharacterConfig.h"
#include "../../WGAGameGameModeBase.h"

#include "MainCharacterAbility.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WGAGAME_API UMainCharacterAbility : public UAbility
{
public:
	GENERATED_BODY()

	UMainCharacterConfig const* GetConfig() const
	{
		return static_cast<UMainCharacterConfig const*>(ConfigurationData);
	}

	float GetEvilForce() const
	{
		float value;
		AWGAGameGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AWGAGameGameModeBase>();
		GameMode->GetEvilForcePercent(value);

		value /= 100;
		value += 1;

		return value;
	}
	
};
