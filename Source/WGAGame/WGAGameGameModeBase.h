// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameModeBase.h"
#include "WGAGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class WGAGAME_API AWGAGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void OnPlayerDeath() const;

	UFUNCTION(BlueprintCallable)
	void OnEnemyKill() const;
};
