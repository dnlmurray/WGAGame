#include "GhostBomb.h"

#include "MainCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"

void UGhostBomb::PlaceProjectile(FTransform Transform)
{	
	ProjectileRef = GetWorld()->SpawnActorDeferred<AThrownProjectile>(ProjectileVisual, Transform);
	ProjectileRef->SetOwner(Owner);
	ProjectileRef->FinishSpawning(Transform);

	UProjectileMovementComponent* PMC = static_cast<UProjectileMovementComponent*>(ProjectileRef->GetComponentByClass(
    UProjectileMovementComponent::StaticClass()));

	if (PMC != nullptr)
	{
		PMC->InitialSpeed = PMC->MaxSpeed = GetConfig()->GhostConfiguration.ProjectileSpeed;
	}
	
	ProjectileRef->Notifier.AddDynamic(this, &UGhostBomb::TakeDamage);
}

void UGhostBomb::TakeDamage(AActor* OverlappedActor)
{
	auto MC = Cast<AMainCharacter>(OverlappedActor);

	if (MC != nullptr)
	{
		MC->TakeDamage(GetConfig()->GhostConfiguration.Damage,
									FDamageEvent{},
							        Owner->Controller,
							        Owner);
	}
}
