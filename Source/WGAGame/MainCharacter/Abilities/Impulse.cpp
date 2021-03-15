// Fill out your copyright notice in the Description page of Project Settings.


#include "Impulse.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"

// Sets default values for this component's properties
UImpulse::UImpulse()
	: TimeSinceLastActivation(0)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called every frame
void UImpulse::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TimeSinceLastActivation += DeltaTime;

	if (TimeSinceLastActivation >= ConfigurationData->ImpulseConfiguration.Cooldown) bWasActivated = false;
}

void UImpulse::ApplyEffect()
{
	if (TimeSinceLastActivation <= ConfigurationData->ImpulseConfiguration.Cooldown && bWasActivated) return;

	const float ZoneRadius = ConfigurationData->ImpulseConfiguration.Radius;
	
	FCollisionShape EffectiveZone = FCollisionShape::MakeSphere(ZoneRadius);

	TArray<FHitResult> HitsInfo;
	HitsInfo.SetNum(40);

	FVector SweepStart = Owner->GetActorTransform().TransformPosition(FVector(0.0f, 0.0f, Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
	FVector& SweepEnd  = SweepStart;

	FVector Velocity;
    
	if (ConfigurationData->ExorcismConfiguration.Debug)
		DrawDebugSphere(GetWorld(),Owner->GetActorTransform().TransformPosition(FVector(0.0f, 0, Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() / 2)), ZoneRadius,50, FColor::Purple,true);
		
	if (GetWorld()->SweepMultiByChannel(HitsInfo, SweepStart, SweepEnd, FQuat::Identity, ECC_Magic, EffectiveZone))
	{
		FDamageEvent DamageEvent;
		
		for (auto& Hit : HitsInfo)
		{
			if(Hit.Actor != nullptr && Hit.Actor->CanBeDamaged())
			{
				Velocity = Hit.Actor->GetActorLocation() - Owner->GetActorLocation();

				Velocity *= ConfigurationData->ImpulseConfiguration.PushVelocity;

				// IMPORTANT!!
				// Only characters can block ECC_Magic channel. For pushing physical objects use RadialForce component
				Cast<ACharacter>(Hit.Actor)->LaunchCharacter(Velocity, false, false);

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

