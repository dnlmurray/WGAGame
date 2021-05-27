// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AbilitiesState.h"
#include "../Config/BaseConfig.h"
#include "Components/ActorComponent.h"
#include "Ability.generated.h"

UCLASS()
class AAbilityVisual : public AActor
{
	GENERATED_BODY()
};

UCLASS(Abstract)
class WGAGAME_API UAbility : public UActorComponent
{
	GENERATED_BODY()

public:
	UAbility();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
    void Initialize(UBaseConfig* Config, UAbilitiesState* State);
	
protected:
	virtual void BeginPlay() override;

	void PlaceVisual(FTransform& Transform);

public:
	UPROPERTY(EditDefaultsOnly, Category="ActorSpawning")
	TSubclassOf<AAbilityVisual> Visual;

	UPROPERTY(BlueprintReadWrite)
	UBaseConfig const* ConfigurationData;
	
protected:
	
	UPROPERTY()
	UAbilitiesState* AbilitiesState;
	
	UPROPERTY()
	ACharacter* Owner;

	UPROPERTY()
	AAbilityVisual* VisualRef;
};
