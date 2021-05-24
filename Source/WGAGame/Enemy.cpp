

#include "Enemy.h"

#include <cassert>

#include "MainCharacter/MainCharacter.h"
#include "Weapon.h"
#include "WGAGameGameModeBase.h"

// Sets default values
AEnemy::AEnemy()
	: SpawnManager(nullptr)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemy::SetSpawnManager(ASpawnManager* SM)
{
	SpawnManager = SM;
	SpawnManager->ResetNotifier.AddDynamic(this, &AEnemy::ResetEnemy);
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{	
	UActorComponent* WeaponComponent = DamageCauser->GetComponentByClass(UWeapon::StaticClass());
	
	if (WeaponComponent->GetClass()->IsChildOf(UWeapon::StaticClass()) &&
		DamageCauser->GetClass()->IsChildOf(AMainCharacter::StaticClass()))
	{
		float coef;

		AWGAGameGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AWGAGameGameModeBase>();
		GameMode->GetEvilForcePercent(coef);

		coef /= 100;
		coef += 1;
		
		OnHitReaction(DamageAmount/coef);
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
	
	Destroy();
}

void AEnemy::ResetEnemy()
{
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

