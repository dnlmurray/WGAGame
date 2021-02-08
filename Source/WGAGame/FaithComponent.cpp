// Fill out your copyright notice in the Description page of Project Settings.


#include "FaithComponent.h"

// Sets default values for this component's properties
UFaithComponent::UFaithComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UFaithComponent::BeginPlay()
{
	Super::BeginPlay();

	FaithValue = FaithMaxValue;
}


// Called every frame
void UFaithComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bFaithDecreasingIsEnabled) return;

	FaithValue -= FaithDecreasingSpeed * DeltaTime;
}

