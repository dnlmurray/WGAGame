// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitiesConfig.h"
#include "Components/ActorComponent.h"
#include "Exorcism.generated.h"

#define ECC_Weapon ECollisionChannel::ECC_GameTraceChannel1

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WGAGAME_API UExorcism : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UExorcism();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Applies the effect to every enemy in the area
	UFUNCTION(BlueprintCallable)
    void ApplyEffect();

	UFUNCTION(BlueprintCallable)
	void Initialize(UAbilitiesConfig* Config)
	{
		ConfigurationData = Config;
		Owner = (ACharacter*)GetOwner();
	}
	
private:
	ACharacter const* Owner;

	UAbilitiesConfig const* ConfigurationData;

	float TimeSinceLastActivation;

	bool bWasActivated;
};
