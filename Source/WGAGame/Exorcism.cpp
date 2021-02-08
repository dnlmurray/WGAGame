// Fill out your copyright notice in the Description page of Project Settings.


#include "Exorcism.h"

#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UExorcism::UExorcism()
	: bWasActivated(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called every frame
void UExorcism::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TimeSinceLastActivation += DeltaTime;

	if (TimeSinceLastActivation >= ConfigurationData->ExorcismConfiguration.Cooldown) bWasActivated = false;
}


void UExorcism::ApplyEffect()
{
	if (TimeSinceLastActivation <= ConfigurationData->ExorcismConfiguration.Cooldown && bWasActivated) return;

	const float ZoneLength = ConfigurationData->ExorcismConfiguration.Range;
	const float ZoneRadius = ConfigurationData->ExorcismConfiguration.SweepShapeRadius;
	
	FCollisionShape EffectiveZone = FCollisionShape::MakeSphere(ZoneRadius);

	TArray<FHitResult> HitsInfo;
	HitsInfo.SetNum(40);

	FVector SweepStart = Owner->GetActorTransform().TransformPosition(FVector(0.0f, 0.0f, Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() / 2));
	FVector SweepEnd   = Owner->GetActorTransform().TransformPosition(FVector(0.0f, ZoneLength, Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() / 2));
    
	if (ConfigurationData->ExorcismConfiguration.Debug)
		for (int i = 0; i < 3; i++)
			DrawDebugSphere(GetWorld(),
						 Owner->GetActorTransform().TransformPosition(FVector(0.0f, i * ZoneLength / 2, Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() / 2)),
						 ZoneRadius,
						 50,
						 FColor::Purple,
						 true);
		
	if (GetWorld()->SweepMultiByChannel(HitsInfo, SweepStart, SweepEnd, FQuat::Identity, ECC_Weapon, EffectiveZone))
	{
		FDamageEvent DamageEvent;
		
		for (auto& Hit : HitsInfo)
		{
			if(Hit.Actor != nullptr && Hit.Actor->CanBeDamaged())
			{
				Hit.Actor->TakeDamage(ConfigurationData->ExorcismConfiguration.Damage,
                                      DamageEvent,
                           Owner->GetController(),
                                      const_cast<ACharacter*>(Owner));

				if (ConfigurationData->ExorcismConfiguration.Debug && GEngine)
					GEngine->AddOnScreenDebugMessage(
                        -1,
                        5.f,
                        FColor::Green,
                        FString::Printf(TEXT("Hit Result: %s"),
                        *Hit.Actor->GetName()));
			}
		}
	}

	TimeSinceLastActivation = 0.0f;
	bWasActivated = true;
}

