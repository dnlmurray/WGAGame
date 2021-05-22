// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "SpawnManager.h"
#include "Enemy.h"
#include "WGAGameGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

float AMainCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                 AActor* DamageCauser)
{
	// UActorComponent* WeaponComponent = DamageCauser->GetComponentByClass(UWeapon::StaticClass());

	if (DamageCauser->GetClass()->IsChildOf(AEnemy::StaticClass()))
	{
		float coef;

		AWGAGameGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AWGAGameGameModeBase>();
		GameMode->GetEvilForcePercent(coef);

		coef /= 100;
		coef += 1;
		
		OnHitReaction(DamageAmount*coef);
	}

	return 0;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

