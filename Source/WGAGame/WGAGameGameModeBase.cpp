// Copyright Epic Games, Inc. All Rights Reserved.


#include "WGAGameGameModeBase.h"

#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"

void AWGAGameGameModeBase::OnPlayerDeath() const
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void AWGAGameGameModeBase::OnEnemyKill() const
{
	StaticCast<AMainCharacter*>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->OnEnemyKill();
}