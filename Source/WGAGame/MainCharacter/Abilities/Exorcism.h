// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitiesConfig.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "AbilitiesState.h"
#include "Ability.h"

#include "Exorcism.generated.h"

#define ECC_Magic ECollisionChannel::ECC_GameTraceChannel2

UCLASS()
class AExorcismVisual : public AActor
{
	GENERATED_BODY()
	
	AExorcismVisual() { }
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WGAGAME_API UExorcism : public UAbility
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
    void Initialize(UAbilitiesConfig* Config, UAbilitiesState* State)
	{
		ConfigurationData = Config;
		AbilitiesState    = State;
		Owner             = Cast<ACharacter>(GetOwner());
	}

	// Visual representation
	UPROPERTY(EditDefaultsOnly,Category="ActorSpawning")
	TSubclassOf<AExorcismVisual> WeaponVisualObject;

private:
	UPROPERTY()
	AExorcismVisual*        VisualObjectRef;
	float                   TimeSinceLastActivation;
	bool                    bWasActivated;
};
