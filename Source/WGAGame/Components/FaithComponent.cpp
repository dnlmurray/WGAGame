// Fill out your copyright notice in the Description page of Project Settings.


#include "FaithComponent.h"

// Sets default values for this component's properties
UFaithComponent::UFaithComponent(): IsDead(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UFaithComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = static_cast<AWGACharacter*>(GetOwner());
}


// Called every frame: faith decrease on tick
void UFaithComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UFaithComponent::IncreaseFaith(float Faith)
{
	if (Faith >= 0) {
		FaithValue = FMath::Clamp(FaithValue + Faith, 0.0f, MaxFaith);
	}
}

void UFaithComponent::DecreaseFaith(float Faith)
{
	if (Faith >= 0) {
		FaithValue = FMath::Clamp(FaithValue - Faith, 0.0f, MaxFaith);
	}
}

void UFaithComponent::ResetFaith()
{
	FaithValue = 0;
	IsDead = false;
}

void UFaithComponent::Initialize(UMainCharacterConfig* Config, UAbilitiesState* State)
{
	ConfigurationData = Config;
	AbilitiesState = State;

	MaxFaith = ConfigurationData->FaithConfiguration.MaxFaith;
	FaithValue = 0;
}