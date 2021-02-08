// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

constexpr float MaxHealth = 100.0f;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WGAGAME_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void EnableRegeneration();

	// Applies damage and returns an amount of remaining health
	UFUNCTION(BlueprintCallable)
	void ApplyInflictedDamage(float Damage);

	UFUNCTION(BlueprintCallable)
	float GetHealthValue() const { return HealthValue; };
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float HealthValue;
	float RegenerationSpeed;

	const float HealthMaxValue = 100.0f;
	
	uint8 bRegenerationIsEnabled:1;
};
