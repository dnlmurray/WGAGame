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

	// ...
	
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
	bRegenerationIsEnabled = (!bRegenerationIsEnabled) ? true : false;
}

void UHealthComponent::ApplyInflictedDamage(float Damage)
{
	float Delta = HealthValue - Damage;
	HealthValue = (Delta > 0) ? Delta : 0.0f;
}