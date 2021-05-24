// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MainCharacterAbility.h"

#include "Impulse.generated.h"

#define ECC_Weapon ECollisionChannel::ECC_GameTraceChannel1

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WGAGAME_API UImpulse : public UMainCharacterAbility
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UImpulse();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Applies the effect to every enemy in the area
	UFUNCTION(BlueprintCallable)
	void Place();
};
