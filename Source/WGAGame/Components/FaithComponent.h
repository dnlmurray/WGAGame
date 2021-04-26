// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "AbilitiesState.h"
#include "MainCharacterConfig.h"
#include "WGACharacter.h"
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
	void IncreaseFaith(float Faith);

	UFUNCTION(BlueprintCallable)
	bool GetFaithDecreasingStatus() const { return bFaithDecreasingIsEnabled; }

	UFUNCTION(BlueprintCallable)
    void Initialize(UMainCharacterConfig* Config, UAbilitiesState* State);

	UFUNCTION(BlueprintCallable)
	void DecreasePerKill();

	UFUNCTION(BlueprintCallable)
	void DecreaseFaith(float Faith);

	UFUNCTION(BlueprintCallable)
	void ResetFaith();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// Decrease faith on demand

	void OnZeroFaith();

	void CheckFaithAmount();

public:
	UPROPERTY(BlueprintReadOnly)
	float MaxFaith;
	
	UPROPERTY(BlueprintReadOnly)
	float FaithValue;
	
private:
	UPROPERTY()
	UMainCharacterConfig* ConfigurationData;

	UPROPERTY()
	UAbilitiesState* AbilitiesState;

	uint8 bFaithDecreasingIsEnabled:1;

	UPROPERTY()
	AWGACharacter* Owner;

	bool IsDead;
};
