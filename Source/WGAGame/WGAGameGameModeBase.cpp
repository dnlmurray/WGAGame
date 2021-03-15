// Copyright Epic Games, Inc. All Rights Reserved.


#include "WGAGameGameModeBase.h"

#include "Kismet/GameplayStatics.h"

void AWGAGameGameModeBase::OnPlayerDeath() const
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}
