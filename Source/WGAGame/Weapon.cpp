// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "DrawDebugHelpers.h"
#include "Enemy.h"
#include "GameFramework/Character.h"

// Make sure this redefenition matches the corresponding one in the DefaultEngine.ini file
#define ECC_Weapon ECollisionChannel::ECC_GameTraceChannel1

// Sets default values
UWeapon::UWeapon()
	: bExecutionEnabled(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;

	CollisionQueryParams = FCollisionQueryParams::DefaultQueryParam;
}

void UWeapon::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());

	FActorSpawnParameters SpawnParams;
	
	WeaponVisual
	  = GetWorld()->SpawnActor<AWeaponVisual>(WeaponVisualObject,
		                                      Owner->GetMesh()->GetSocketTransform("WeaponSocket"),
		                                      SpawnParams);

	const FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
	
	WeaponVisual->AttachToComponent(Owner->GetMesh(), AttachmentTransformRules, FName("WeaponSocket"));
}

void UWeapon::Initialize(UAbilitiesConfig* Config, UAbilitiesState* State, UFaithComponent* Faith)
{
	ConfigurationData = Config;
    AbilitiesState    = State;
	FaithComponent    = Faith;
	
	SetNodes(ConfigurationData->WeaponAttackConfiguration.Start,
             ConfigurationData->WeaponAttackConfiguration.End,
             ConfigurationData->WeaponAttackConfiguration.NumberOfNodes);
}

// Called every frame
void UWeapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(!bExecutionEnabled) return;
	
	UWorld* WorldReference = GetWorld();
	FTransform NewTransform = Owner->GetMesh()->GetSocketTransform("WeaponSocket");
	FVector TraceBegin, TraceEnd;

	FHitResult HitResult;
	
	// Replace this event later
	FDamageEvent SwordDamage;
	
	for (FVector& Node : Nodes)	
	{
		TraceBegin = CurrentTransform.TransformPosition(Node);
		TraceEnd = NewTransform.TransformPosition(Node);
		if (WorldReference->LineTraceSingleByChannel(HitResult, TraceBegin, TraceEnd, ECC_Weapon, CollisionQueryParams))
		{
			if(HitResult.Actor != nullptr && HitResult.Actor->CanBeDamaged())
			{
				ACharacter* HitCharacter = Cast<ACharacter>(HitResult.Actor);
				
				if (HitCharacter != nullptr && HitCharacter != Owner && HitResult.Actor.Get() != LastActor) 
				{
					if (AbilitiesState != nullptr && FaithComponent != nullptr &&
						AbilitiesState->CharacterIsUnderWhiteBarrierEffect)
					{	
						FaithComponent->IncreaseFaith(ConfigurationData->WhiteBarrierConfiguration.FaithGainPerStandartAttack);
					}

					HitResult.Actor->TakeDamage(ConfigurationData->WeaponAttackConfiguration.Damage,
					                            SwordDamage,
					                            nullptr,
					                            Owner);
					LastActor = HitResult.Actor.Get();

				}
			}
		}
		
		if (ConfigurationData->WeaponAttackConfiguration.Debug)
		{
			DrawDebugLine(WorldReference, TraceBegin, TraceEnd, FColor::Red, true, 10.0f, 0, 1);
		}
		
		CurrentTransform = NewTransform;
	}
}

void UWeapon::EnableDamageApplying()
{
	bExecutionEnabled = true;
	CurrentTransform = Owner->GetMesh()->GetSocketTransform("WeaponSocket");	
}

void UWeapon::DisableDamageApplying()
{
	bExecutionEnabled = false;
	LastActor = nullptr;
}

void UWeapon::SetNodes(const FVector& StartLocation, const FVector& EndLocation, int32 NumberOfNodes)
{
	Nodes.SetNum(NumberOfNodes, false);

	FVector UnitVector = EndLocation - StartLocation;
	if(!UnitVector.Normalize(0.001)) return;
	
	const float Step = FVector::Distance(StartLocation, EndLocation) / NumberOfNodes;
	
	for (uint16 Count = 0; Count < NumberOfNodes; Count++)
	{
		Nodes[Count] = UnitVector * (Step * Count);
	}
}

void UWeapon::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);

	if (IsValid(WeaponVisual))
	{
		WeaponVisual->Destroy();
	}
}