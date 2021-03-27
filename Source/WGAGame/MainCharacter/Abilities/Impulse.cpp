// Fill out your copyright notice in the Description page of Project Settings.


#include "Impulse.h"
#include "DrawDebugHelpers.h"
#include "Enemy.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UImpulse::UImpulse()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called every frame
void UImpulse::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UImpulse::Initialize(UAbilitiesConfig* Config)
{ 
	ConfigurationData = Config;
	Owner = Cast<ACharacter>(GetOwner());
}

void UImpulse::Place()
{
	FVector Location = Owner->GetActorLocation();

	FActorSpawnParameters SpawnParams;

	FTransform Transform(Owner->GetActorRotation(),
	                     Location,
	                     FVector(10.0f, 10.0f, 0.025f));

	ImpulseObjectRef
		= GetWorld()->SpawnActor<AImpulseVisual>(ImpulseVisual, Transform, SpawnParams);

	FCollisionShape ImpulseZone = FCollisionShape::MakeSphere(ConfigurationData->SkyImpulseConfiguration.Radius);

	TArray<FHitResult> HitsInfo;
	HitsInfo.SetNum(40);

	FVector SweepStart = Owner->GetActorTransform().TransformPosition(
		FVector(0.0f, 0.0f, Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
	FVector& SweepEnd = SweepStart;

	FVector VelocityVector;
	float Distance;

	if (GetWorld()->SweepMultiByChannel(HitsInfo, SweepStart, SweepEnd, FQuat::Identity, ECC_Weapon, ImpulseZone))
	{
		FDamageEvent DamageEvent;

		for (auto& HitResult : HitsInfo)
		{
			if (HitResult.Actor != nullptr && HitResult.Actor->CanBeDamaged())
			{
				ACharacter* HitCharacter = Cast<ACharacter>(HitResult.Actor);

				if (HitCharacter != nullptr && HitCharacter->GetClass()->IsChildOf(AEnemy::StaticClass()))
				{
					Distance = Owner->GetDistanceTo(HitCharacter);
					VelocityVector = HitCharacter->GetActorLocation() - Location;
					VelocityVector *= ConfigurationData->SkyImpulseConfiguration.PushImpulse;
					VelocityVector *= (ConfigurationData->SkyImpulseConfiguration.Radius/Distance);

					HitCharacter->GetController()->StopMovement();
					HitCharacter->GetCharacterMovement()->AddImpulse(VelocityVector, false);

					HitCharacter->TakeDamage(ConfigurationData->SkyImpulseConfiguration.Damage,
					                         DamageEvent,
					                         nullptr,
					                         Owner);

					if (ConfigurationData->SkyImpulseConfiguration.Debug && GEngine)
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

