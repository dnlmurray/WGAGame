// Fill out your copyright notice in the Description page of Project Settings.


#include "Impulse.h"
#include "Enemy.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UImpulse::UImpulse()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UImpulse::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UImpulse::Place()
{
	FTransform Transform(Owner->GetActorRotation(),
                         Owner->GetActorLocation(),
                         FVector(10.0f, 10.0f, 0.025f));

	PlaceVisual(Transform);

	const FCollisionShape ImpulseZone = FCollisionShape::MakeSphere(GetConfig()->SkyImpulseConfiguration.Radius);

	TArray<FHitResult> HitsInfo;
	HitsInfo.SetNum(40);

	FVector SweepStart = Transform.TransformPosition(
		FVector(0.0f, 0.0f, Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
	FVector& SweepEnd = SweepStart;

	const float EvilForce = GetEvilForce();
	const float FinalDamage = GetConfig()->SkyImpulseConfiguration.Damage * EvilForce;
	
	FVector VelocityVector{};
	float Distance = 0;
	const FVector Location = Owner->GetActorLocation();

	if (GetWorld()->SweepMultiByChannel(HitsInfo, SweepStart, SweepEnd, FQuat::Identity, ECC_Weapon, ImpulseZone))
	{
		for (auto& HitResult : HitsInfo)
		{
			if (HitResult.Actor != nullptr && HitResult.Actor->CanBeDamaged())
			{
				ACharacter* HitCharacter = Cast<ACharacter>(HitResult.Actor);

				if (HitCharacter != nullptr && HitCharacter->GetClass()->IsChildOf(AEnemy::StaticClass()))
				{
					Distance = Owner->GetDistanceTo(HitCharacter);
					VelocityVector = HitCharacter->GetActorLocation() - Location;
					VelocityVector *= GetConfig()->SkyImpulseConfiguration.PushImpulse;
					VelocityVector *= (GetConfig()->SkyImpulseConfiguration.Radius/Distance);

					HitCharacter->GetController()->StopMovement();
					HitCharacter->GetCharacterMovement()->AddImpulse(VelocityVector, false);

					HitCharacter->TakeDamage(FinalDamage,
					                         FDamageEvent{},
					                         Owner->Controller,
					                         Owner);

					if (GetConfig()->SkyImpulseConfiguration.Debug)
						GEngine->AddOnScreenDebugMessage(
							-1,
							5.f,
							FColor::Green,
							FString::Printf(TEXT("Hit Result: %s"),
							                *HitCharacter->GetName()));
				}
			}
		}
	}
}

