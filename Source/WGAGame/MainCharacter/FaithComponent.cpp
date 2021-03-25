// Fill out your copyright notice in the Description page of Project Settings.


#include "FaithComponent.h"

#include <string>



#include "MainCharacter.h"
#include "WGAGameGameModeBase.h"

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
}


// Called every frame: faith decrease on tick
void UFaithComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Blue,
	// 	FString::Printf(TEXT("faith decrease is enabled: %s"), GetFaithDecreasingStatus() ? TEXT("true") : TEXT("false")));
	//
	//
	if (bFaithDecreasingIsEnabled && !AbilitiesState->CharacterIsUnderWhiteBarrierEffect)
	{
		DecreaseFaith(ConfigurationData->FaithConfiguration.FaithDecreasePerSecond * DeltaTime);
	}
}

// faith decrease on kill
void UFaithComponent::DecreasePerKill()
{
	if (bFaithDecreasingIsEnabled && !AbilitiesState->CharacterIsUnderWhiteBarrierEffect)
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

	AWGAGameGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AWGAGameGameModeBase>();
	GameMode->OnPlayerDeath();
}

void UFaithComponent::CheckFaithAmount() const
{
	if (FaithValue <= 0)
	{
		OnZeroFaith();
	}
}

void UFaithComponent::RestoreFaith(float Faith)
{
	GEngine->AddOnScreenDebugMessage(
	-1,
	5.f,
	FColor::Blue,
	TEXT("Faith gain"),
	true,
	FVector2D(1.0f, 1.0f));
	
	FaithValue = FMath::Clamp(FaithValue + Faith, 0.0f, ConfigurationData->FaithConfiguration.MaximumFaith);
}

void UFaithComponent::DecreaseFaith(float Faith)
{
	FaithValue -= Faith;
	CheckFaithAmount();
}

void UFaithComponent::Initialize(UAbilitiesConfig* Config, UAbilitiesState* State)
{
	ConfigurationData = Config;
	AbilitiesState = State;

	MaxFaith = ConfigurationData->FaithConfiguration.MaximumFaith;
	FaithValue = MaxFaith;
}