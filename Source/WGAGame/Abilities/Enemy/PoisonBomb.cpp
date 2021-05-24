#include "PoisonBomb.h"


#include "../../MainCharacter/MainCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"

UPoisonBomb::UPoisonBomb()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPoisonBomb::PlaceProjectile(FTransform Transform)
{	
	ProjectileRef = GetWorld()->SpawnActorDeferred<AThrownProjectile>(ProjectileVisual, Transform);
	ProjectileRef->SetOwner(Owner);
	ProjectileRef->FinishSpawning(Transform);

	UProjectileMovementComponent* PMC = static_cast<UProjectileMovementComponent*>(ProjectileRef->GetComponentByClass(
    UProjectileMovementComponent::StaticClass()));

	if (PMC != nullptr)
	{
		PMC->InitialSpeed = PMC->MaxSpeed = GetConfig()->BombConfiguration.ProjectileSpeed;
	}
	
	// when projectile collides with anything, visual and damage logic will be placed
	ProjectileRef->Notifier.AddDynamic(this, &UPoisonBomb::PlaceExplosion);
}

void UPoisonBomb::PlaceExplosion(AActor* OverlappedActor)
{
	FTransform Transform(ProjectileRef->GetActorRotation(),
                         ProjectileRef->GetActorLocation(),
                         FVector(10.0f, 10.0f, 0.025f));
	
	PlaceVisual(Transform);

	const FCollisionShape BombZone = FCollisionShape::MakeSphere(GetConfig()->BombConfiguration.Radius);

	TArray<FHitResult> HitsInfo;
	HitsInfo.SetNum(40);

	FVector SweepStart = ProjectileRef->GetActorTransform().TransformPosition(FVector(0.0f, 0.0f, 0.0f));
	FVector& SweepEnd = SweepStart;

	if (GetWorld()->SweepMultiByChannel(HitsInfo, SweepStart, SweepEnd, FQuat::Identity, ECC_Weapon, BombZone))
	{
		for (auto& HitResult : HitsInfo)
		{
			if (HitResult.Actor != nullptr && HitResult.Actor->CanBeDamaged())
			{
				ACharacter* HitCharacter = Cast<ACharacter>(HitResult.Actor);

				if (HitCharacter != nullptr && HitCharacter->GetClass()->IsChildOf(AMainCharacter::StaticClass()))
				{
					HitCharacter->TakeDamage(GetConfig()->BombConfiguration.Damage,
                                             FDamageEvent{},
                                             Owner->Controller,
                                             Owner);
				}
			}
		}
	}
}

FProjectileAngle UPoisonBomb::CalculateAngle(FVector TargetLocation)
{
	/*
	 * tan theta = (v^2 +- sqrt(v^4 - g(gx^2 + 2yv^2)))/gx
	 */

	FVector OwnerLocation = Owner->GetActorLocation();
	
	float V = GetConfig()->BombConfiguration.ProjectileSpeed;
	
	float dx = TargetLocation.X - OwnerLocation.X;
	float dy = TargetLocation.Y - OwnerLocation.Y;
	float dz = TargetLocation.Z - OwnerLocation.Z;
	float dxylength = FMath::Sqrt(FMath::Pow(dx, 2.0f) + FMath::Pow(dy, 2.0f));
	
	float Sqrt = FMath::Pow(V, 4.0f) - g * (g * FMath::Pow(dxylength, 2.0f) + 2*dz*FMath::Pow(V, 2.0f));

	if (Sqrt < 0)
	{
		return FProjectileAngle();
	}

	Sqrt = FMath::Sqrt(Sqrt);
	float Numerator = FMath::Min(FMath::Pow(V, 2.0f) + Sqrt, FMath::Pow(V, 2.0f) - Sqrt);
	float Denominator = g * dxylength;

	float tan = Numerator/Denominator;
	float angle = FMath::RadiansToDegrees(FMath::Atan(tan));

	return FProjectileAngle(angle);
}
