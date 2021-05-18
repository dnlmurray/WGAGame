// "who needs it at all? "

#pragma once

#include "CoreMinimal.h"

#include "Ability.h"
#include "GhostEnemyConfig.h"
#include "ThrownProjectile.h"

#include "GhostBomb.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WGAGAME_API UGhostBomb : public UAbility
{
public:
	// Implements projectile spawning: projectile collision notifies this Component and causes explosion
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable)
    void PlaceProjectile(FTransform Transform);

	UFUNCTION()
    void TakeDamage(AActor* OverlappedActor);
	
	UGhostEnemyConfig const* GetConfig() const
	{
		return static_cast<UGhostEnemyConfig const*>(ConfigurationData);
	}
	
public:
	UPROPERTY(EditDefaultsOnly, Category="ActorSpawning")
	TSubclassOf<AThrownProjectile> ProjectileVisual;
	
	private:
	UPROPERTY()
	AThrownProjectile* ProjectileRef;
};
