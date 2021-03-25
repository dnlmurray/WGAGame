// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "SpawnManager.h"
#include "Enemy.h"
#include "Weapon.h"
#include "WGAGameGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OnActorBeginOverlap.AddDynamic(this, &AMainCharacter::OnBeginOverlap);
}

void AMainCharacter::OnBeginOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
	
	if (OtherActor->GetClass()->IsChildOf(ASpawnManager::StaticClass()))
	{
		ASpawnManager* SpawnManager = static_cast<ASpawnManager*>(OtherActor);
		SpawnManager->StateNotifier.AddDynamic(this, &AMainCharacter::OnActionStateChange);
	}
}

float AMainCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                 AActor* DamageCauser)
{
	UActorComponent* WeaponComponent = DamageCauser->GetComponentByClass(UWeapon::StaticClass());

	if (WeaponComponent->GetClass()->IsChildOf(UWeapon::StaticClass()) &&
		DamageCauser->GetClass()->IsChildOf((AEnemy::StaticClass())))
	{
		OnHitReaction(DamageAmount);
	}

	return 0;
}

void AMainCharacter::OnPlayerDeath() const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("YOU DIED: 0 HEALTH"));

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

