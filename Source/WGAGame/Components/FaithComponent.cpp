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

	Owner = static_cast<AWGACharacter*>(GetOwner());
}


// Called every frame: faith decrease on tick
void UFaithComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Blue,
	// 	FString::Printf(TEXT("faith decrease is enabled: %s"), GetFaithDecreasingStatus() ? TEXT("true") : TEXT("false")));
	//
	//
	if (bFaithDecreasingIsEnabled && !AbilitiesState->IsUnderWhiteBarrierEffect)
	{
		DecreaseFaith(ConfigurationData->FaithConfiguration.FaithDecreasePerSecond * DeltaTime);
	}
}

// faith decrease on kill
void UFaithComponent::DecreasePerKill()
{
	if (bFaithDecreasingIsEnabled && !AbilitiesState->IsUnderWhiteBarrierEffect)
	{
		GEngine->AddOnScreenDebugMessage(
		-1,
		5.f,
		FColor::Blue,
		TEXT("Faith decrease on kill"),
		true,
		FVector2D(1.0f, 1.0f));
		DecreaseFaith(ConfigurationData->FaithConfiguration.FaithDecreasePerKill);
	}
}

void UFaithComponent::OnZeroFaith() const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("YOU DIED: 0 FAITH"));

	Owner->OnDeathReaction(this);
}

void UFaithComponent::CheckFaithAmount() const
{
	if (FaithValue <= 0)
	{
		OnZeroFaith();
	}
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
		FaithValue -= Faith;
		CheckFaithAmount();
	}
}

void UFaithComponent::Initialize(UMainCharacterConfig* Config, UAbilitiesState* State)
{
	ConfigurationData = Config;
	AbilitiesState = State;

	MaxFaith = ConfigurationData->FaithConfiguration.MaxFaith;
	FaithValue = MaxFaith;
}