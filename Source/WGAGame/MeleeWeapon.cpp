// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeWeapon.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMeleeWeapon::AMeleeWeapon()
	: WeaponOwner(nullptr)
	, bExecutionEnabled(false)
	, LastActor(nullptr)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionQueryParams = FCollisionQueryParams::DefaultQueryParam;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMeshComponent"));
	WeaponMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay(); 

}

// Called every frame
void AMeleeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(!bExecutionEnabled || !ConfigurationData) return;
	
	UWorld* WorldReference = GetWorld();
	FTransform NewTransform = RootComponent->GetComponentTransform();
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
				if (HitResult.Actor != this && HitResult.Actor != LastActor) 
				{
					HitResult.Actor->TakeDamage(ConfigurationData->WeaponAttackConfiguration.Damage, SwordDamage, nullptr, this);
					LastActor = HitResult.Actor.Get();
				}
			}
		}
		
		if (ConfigurationData->WeaponAttackConfiguration.Debug) DrawDebugLine(WorldReference, TraceBegin, TraceEnd, FColor::Red, true, 10.0f, 0, 1);
		
		CurrentTransform = NewTransform;
	}
}

void AMeleeWeapon::EnableDamageApplying()
{
	bExecutionEnabled = true;
	CurrentTransform = RootComponent->GetComponentTransform();	
}

void AMeleeWeapon::DisableDamageApplying()
{
	bExecutionEnabled = false;
	LastActor = nullptr;
}

void AMeleeWeapon::SetNodes(const FVector& StartLocation, const FVector& EndLocation, int32 NumberOfNodes)
{
	Nodes.SetNum(NumberOfNodes, false);

	FVector UnitVector = EndLocation - StartLocation;
	if(!UnitVector.Normalize(0.001)) return;
	
	const float Step = FVector::Distance(StartLocation, EndLocation) / NumberOfNodes;
	
	for (uint16 Count = 0; Count < NumberOfNodes; Count++)
	{
		Nodes[Count] = UnitVector * (Step * Count);
		
		
	//  if (ConfigurationData->WeaponAttackConfiguration.Debug) 
	//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, Nodes[Count].ToString());
	}
}
