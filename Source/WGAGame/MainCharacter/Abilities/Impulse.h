// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitiesConfig.h"
#include "Ability.h"

#include "Impulse.generated.h"

#define ECC_Weapon ECollisionChannel::ECC_GameTraceChannel1

UCLASS()
class AImpulseVisual : public AActor
{
	GENERATED_BODY()
	
	AImpulseVisual() { }
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WGAGAME_API UImpulse : public UAbility
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UImpulse();

	UFUNCTION(BlueprintCallable)
    void Initialize(UAbilitiesConfig* Config);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Applies the effect to every enemy in the area
	UFUNCTION(BlueprintCallable)
    void Place();

public:
	// Visual representation
	UPROPERTY(EditDefaultsOnly,Category="ActorSpawning")
	TSubclassOf<AImpulseVisual> ImpulseVisual;

private:
	UPROPERTY()
	AImpulseVisual*         ImpulseObjectRef;
};
