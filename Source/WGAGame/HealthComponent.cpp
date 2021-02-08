// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
	: bRegenerationIsEnabled(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	HealthValue = HealthMaxValue;
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bRegenerationIsEnabled) return;

	HealthValue += DeltaTime * RegenerationSpeed;
}

void UHealthComponent::EnableRegeneration()
{
	bRegenerationIsEnabled = true;
}

void UHealthComponent::ApplyInflictedDamage(float Damage)
{
	HealthValue = (Damage <= HealthValue) ? HealthValue - Damage : 0.0f;
}