// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemState.generated.h"

/**
 * 
 */
UCLASS()
class WGAGAME_API AAbilitySystemState : public APlayerState
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	TMap<AActor*, float> SpawnedActors;
	
	
};
