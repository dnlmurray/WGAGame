// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MainCharacterAbility.h"

#include "Exorcism.generated.h"

#define ECC_Weapon ECollisionChannel::ECC_GameTraceChannel1

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WGAGAME_API UExorcism : public UMainCharacterAbility
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UExorcism();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// TODO: make conus/trapeze possible
	UFUNCTION(BlueprintCallable)
	void Place(FVector ExorcismVector);
};
