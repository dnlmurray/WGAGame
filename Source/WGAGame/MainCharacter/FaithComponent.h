// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AbilitiesConfig.h"
#include "WhiteBarrier.h"
#include "Components/ActorComponent.h"
#include "FaithComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WGAGAME_API UFaithComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFaithComponent();

	// Enable/disable faith decreasing when the character is in battle/out of battle
	UFUNCTION(BlueprintCallable)
	void EnableFaithDecreasing() { bFaithDecreasingIsEnabled = true; }

	UFUNCTION(BlueprintCallable)
	void DisableFaithDecreasing() { bFaithDecreasingIsEnabled = false; }

	// Restore some amount of faith when special skills are applied
	UFUNCTION(BlueprintCallable)
	void RestoreFaith(float Faith) { FaithValue += Faith; }

	// ...
	UFUNCTION(BlueprintCallable)
	bool GetFaithDecreasingStatus() const { return bFaithDecreasingIsEnabled; }

	UFUNCTION(BlueprintCallable)
    void Initialize(UAbilitiesConfig* Config) { ConfigurationData = Config; }
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UAbilitiesConfig* ConfigurationData;
	
	float FaithValue;

	uint8 bFaithDecreasingIsEnabled:1;
	
};
