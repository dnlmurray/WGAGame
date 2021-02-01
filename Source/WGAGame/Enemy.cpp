// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include <cassert>


#include "MainCharacter.h"
#include "MeleeWeapon.h"

// Sets default values
AEnemy::AEnemy()
	: MaxHealth(100)
	, Health(MaxHealth)
	, EnemyWeapon(nullptr)
	, SpawnManager(nullptr)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemy::SetSpawnManager(ASpawnManager* SM)
{
	SpawnManager = SM;
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enemy damaged!"));

	if (DamageCauser->GetClass()->IsChildOf(AMeleeWeapon::StaticClass()))
	{
		AMeleeWeapon* Weapon = static_cast<AMeleeWeapon*>(DamageCauser);
		AActor* WeaponOwner = Weapon->WeaponOwner;
		assert(WeaponOwner != nullptr);
		
		if (WeaponOwner->GetClass()->IsChildOf(AMainCharacter::StaticClass()))
		{
			Health -= DamageAmount;

			if (Health <= 0)
			{
				OnEnemyDeath();
			}
		}
	}

	return 0;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
}


void AEnemy::OnEnemyDeath()
{
	assert(SpawnManager != nullptr);
	assert(EnemyWeapon != nullptr);

	EnemyWeapon->Destroy();
	SpawnManager->CurrentEnemyNumber --;
	Destroy();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

