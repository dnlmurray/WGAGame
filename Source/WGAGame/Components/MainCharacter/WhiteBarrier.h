// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MainCharacterAbility.h"

#include "WhiteBarrier.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WGAGAME_API UWhiteBarrier : public UMainCharacterAbility
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

private:
	// Removes white barrier
	void Remove();

	// Checks if the character (owner) is currently under effect
	void CheckIfOwnerIsUnderEffect();

private:	
	FVector Location;
	
	float TimeSinceActivation;

	uint8 IsActive:1;
	
	uint8 OwnerIsUnderEffect:1;

	uint8 OwnerIsCasting:1;
};
