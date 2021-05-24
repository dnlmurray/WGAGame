// Fill out your copyright notice in the Description page of Project Settings.


#include "WhiteBarrier.h"

#include "Components/CapsuleComponent.h"

#include "GameFramework/Character.h"

UWhiteBarrier::UWhiteBarrier()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWhiteBarrier::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsActive) return;

	if (TimeSinceActivation >= GetConfig()->WhiteBarrierConfiguration.Duration) Remove();

	OwnerIsCasting = TimeSinceActivation <= GetConfig()->WhiteBarrierConfiguration.CastDuration; 

	CheckIfOwnerIsUnderEffect();

	TimeSinceActivation += DeltaTime;
}

void UWhiteBarrier::Place()
{
	if (IsActive || GetConfig()->WhiteBarrierConfiguration.Duration == 0) return;

	IsActive = true;
	Location = Owner->GetActorLocation() -
			FVector(0.0f,
				    0.0f,
				    Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	TimeSinceActivation = 0.0f;
	
	FTransform Transform(Owner->GetActorRotation(),
                Location,
                  FVector(10.0f, 10.0f, 0.025f));
	PlaceVisual(Transform);
}

void UWhiteBarrier::Remove()
{
	if (GetConfig()->WhiteBarrierConfiguration.Debug)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("WB removed"));
	}
	
	IsActive = false;
	OwnerIsCasting = false;
	OwnerIsUnderEffect = false;

	if (AbilitiesState != nullptr) {
		AbilitiesState->IsUnderWhiteBarrierEffect = OwnerIsUnderEffect;
		AbilitiesState->IsInvincible = OwnerIsCasting;
	}
}

void UWhiteBarrier::CheckIfOwnerIsUnderEffect()
{
	if (!IsActive) return;
	
	float Distance = (Owner->GetActorLocation() - Location).Size();
	Distance = FMath::Abs(Distance);

	OwnerIsUnderEffect
        = (Distance <= GetConfig()->WhiteBarrierConfiguration.Radius) ? true : false;

	if (OwnerIsUnderEffect && GetConfig()->WhiteBarrierConfiguration.Debug)
	{
		if (OwnerIsCasting)
		{
			GEngine->AddOnScreenDebugMessage(
                        -1,
                        1.f,
                        FColor::Green,
                        TEXT("[WB]: Casting: owner is invincible."),
                        true,
                        FVector2D(1.0f, 1.0f));
		} else
		{
			GEngine->AddOnScreenDebugMessage(
                         -1,
                         1.f,
                         FColor::Green,
                         TEXT("[WB]: Effect is applied."),
                         true,
                         FVector2D(1.0f, 1.0f));
		}
	}

	if (AbilitiesState != nullptr) {
		AbilitiesState->IsUnderWhiteBarrierEffect = OwnerIsUnderEffect;
		AbilitiesState->IsInvincible = OwnerIsCasting;
	}
}

