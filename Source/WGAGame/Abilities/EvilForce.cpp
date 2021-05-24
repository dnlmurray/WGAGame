// Fill out your copyright notice in the Description page of Project Settings.


#include "EvilForce.h"


// Sets default values for this component's properties
UEvilForce::UEvilForce()
	: MinPercent(0)
	, MaxPercent(100)
	, EvilForceIncreasePerSecond(0)
	, bEvilForceIsIncreasing(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UEvilForce::DecreaseEvilForce(float percent)
{
	Percent = FMath::Clamp(Percent - percent, MinPercent, MaxPercent);
}

void UEvilForce::IncreaseEvilForce(float percent)
{
	Percent = FMath::Clamp(Percent + percent, MinPercent, MaxPercent);
}

// Called when the game starts
void UEvilForce::BeginPlay()
{
	Super::BeginPlay();

	Percent = MinPercent;
	
}


// Called every frame
void UEvilForce::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bEvilForceIsIncreasing)
	{
		IncreaseEvilForce(EvilForceIncreasePerSecond * DeltaTime);
	}
}

