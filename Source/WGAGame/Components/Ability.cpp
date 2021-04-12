// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability.h"


#include "GameFramework/Character.h"

UAbility::UAbility()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbility::BeginPlay()
{
	Super::BeginPlay();
}

void UAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAbility::Initialize(UBaseConfig* Config, UAbilitiesState* State)
{
	ConfigurationData = Config;
	AbilitiesState    = State;
	Owner             = Cast<ACharacter>(GetOwner());
}

void UAbility::PlaceVisual(FTransform& Transform)
{
	VisualRef = GetWorld()->SpawnActor<AAbilityVisual>(Visual, Transform, FActorSpawnParameters{});
	VisualRef->SetOwner(Owner);
}