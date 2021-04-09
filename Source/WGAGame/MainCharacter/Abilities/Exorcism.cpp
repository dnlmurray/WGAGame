// Fill out your copyright notice in the Description page of Project Settings.


#include "Exorcism.h"

#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UExorcism::UExorcism()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called every frame
void UExorcism::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UExorcism::Initialize(UAbilitiesConfig* Config)
{
	ConfigurationData = Config;
	Owner             = Cast<ACharacter>(GetOwner());
}

void UExorcism::Place(FVector ExorcismVector)
{
	FVector Location = Owner->GetActorLocation();

	FActorSpawnParameters SpawnParams;

	FTransform Transform(ExorcismVector.Rotation(),
	                     Location + ExorcismVector * ConfigurationData->ExorcismConfiguration.Length,
	                     FVector(10.0f, 10.0f, 0.025f));

	ExorcismObjectRef
		= GetWorld()->SpawnActor<AExorcismVisual>(ExorcismVisual, Transform, SpawnParams);

	FVector BoxExtent(ConfigurationData->ExorcismConfiguration.Length,
	                  ConfigurationData->ExorcismConfiguration.Width,
	                  Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	FCollisionShape ExorcismZone = FCollisionShape::MakeBox(BoxExtent);

	TArray<FHitResult> HitsInfo;
	HitsInfo.SetNum(40);

	FVector SweepStart = Owner->GetActorTransform().TransformPosition(
		FVector(0.0f, 0.0f, Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
	FVector& SweepEnd = SweepStart;

	if (GetWorld()->SweepMultiByChannel(HitsInfo, SweepStart, SweepEnd, FQuat::Identity, ECC_Weapon, ExorcismZone))
	{
		FDamageEvent DamageEvent;

		for (auto& HitResult : HitsInfo)
		{
			if (HitResult.Actor != nullptr && HitResult.Actor->CanBeDamaged())
			{
				ACharacter* HitCharacter = Cast<ACharacter>(HitResult.Actor);

				if (HitCharacter != nullptr && HitCharacter->GetClass()->IsChildOf(AEnemy::StaticClass()))
				{
					HitCharacter->TakeDamage(ConfigurationData->ExorcismConfiguration.Damage,
					                         DamageEvent,
					                         nullptr,
					                         Owner);

					if (ConfigurationData->ExorcismConfiguration.Debug && GEngine)
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

