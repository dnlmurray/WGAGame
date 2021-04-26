// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointManager.h"


#include "MainCharacter.h"
#include "WGAGameGameModeBase.h"


// Sets default values
ACheckpointManager::ACheckpointManager() : bIsActivated(false)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OnActorBeginOverlap.AddDynamic(this, &ACheckpointManager::OnBeginOverlap);
}

void ACheckpointManager::OnBeginOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
	if (!bIsActivated && OtherActor->GetClass()->IsChildOf(AMainCharacter::StaticClass()))
	{
		AMainCharacter* MC = static_cast<AMainCharacter*>(OtherActor);
		AWGAGameGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AWGAGameGameModeBase>();
		GameMode->SaveCheckpoint(MC->GetActorLocation());
		bIsActivated = true;
	}
}

// Called when the game starts or when spawned
void ACheckpointManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckpointManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

