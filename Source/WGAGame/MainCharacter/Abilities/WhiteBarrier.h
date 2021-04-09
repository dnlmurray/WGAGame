// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "AbilitiesConfig.h"
#include "AbilitiesState.h"
#include "Ability.h"
#include "Components/ActorComponent.h"
#include "WhiteBarrier.generated.h"

UCLASS()
class AWhiteBarrierVisual : public AActor
{
	GENERATED_BODY()
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WGAGAME_API UWhiteBarrier : public UAbility
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWhiteBarrier();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Places white barrier on the ground under character's feet
	UFUNCTION(BlueprintCallable)
	void Place();

	UFUNCTION(BlueprintCallable)
	bool IsCharacterUnderEffect() const { return OwnerIsUnderEffect; }
	
	UFUNCTION(BlueprintCallable)
    void Initialize(UAbilitiesConfig* Config, UAbilitiesState* State);

public:	
	// Visual representation
	UPROPERTY(EditDefaultsOnly,Category="ActorSpawning")
	TSubclassOf<AWhiteBarrierVisual> WhiteBarrierObject;
	
private:
	// Removes white barrier
	void Remove();

	// Checks if the character (owner) is currently under effect
	void CheckIfOwnerIsUnderEffect();
	
	FVector Location;

	UPROPERTY()
	AWhiteBarrierVisual* WhiteBarrierObjectRef;
	
	float TimeSinceActivation;

	uint8 IsActive:1;
	
	uint8 OwnerIsUnderEffect:1;

	uint8 OwnerIsCasting:1;
};
