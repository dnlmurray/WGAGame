// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include <cassert>



#include "MeleeWeapon.h"
#include "WGAGameGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMainCharacter::AMainCharacter()
	: MaxHealth(400)
	, Health(MaxHealth)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

float AMainCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                 AActor* DamageCauser)
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Player damaged!"));

	if (DamageCauser->GetClass()->IsChildOf(AMeleeWeapon::StaticClass()))
	{
		AMeleeWeapon* Weapon = static_cast<AMeleeWeapon*>(DamageCauser);
		AActor* WeaponOwner = Weapon->WeaponOwner;
		assert(WeaponOwner != nullptr);

		if (WeaponOwner->GetClass()->IsChildOf(AEnemy::StaticClass())) {
			Health -= DamageAmount;

			if (Health <= 0)
			{
				OnPlayerDeath();
			}
		}
	}

	return 0;
}

void AMainCharacter::OnPlayerDeath()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("YOU DIED"));

	AWGAGameGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AWGAGameGameModeBase>();
	GameMode->OnPlayerDeath();
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

