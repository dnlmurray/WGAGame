// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
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

	Owner = static_cast<AWGACharacter*>(GetOwner());
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::OnZeroHealth() const
{
	Owner->OnDeathReaction(this);
}

void UHealthComponent::CheckHealthAmount() const
{
	if (HealthValue <= 0)
	{
		OnZeroHealth();
	}
}

void UHealthComponent::IncreaseHealth(float Health)
{
	if (Health >= 0) {
		// GEngine->AddOnScreenDebugMessage(
  //       -1,
  //       5.f,
  //       FColor::Blue,
  //       TEXT("Faith gain"),
  //       true,
  //       FVector2D(1.0f, 1.0f));
	 //
		HealthValue = FMath::Clamp(HealthValue + Health, 0.0f, MaxHealth);
	}
}

void UHealthComponent::DecreaseHealth(float Health)
{
	if (Health >= 0) {
		HealthValue -= Health;
		CheckHealthAmount();
	}
}

void UHealthComponent::Initialize(UAbilitiesConfig* Config, UAbilitiesState* State)
{
	ConfigurationData = Config;
	AbilitiesState = State;

	MaxHealth = ConfigurationData->HealthConfiguration.MaxHealth;
	HealthValue = MaxHealth;
}