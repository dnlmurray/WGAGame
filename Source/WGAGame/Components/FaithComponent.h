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

	// Restore some amount of faith when special skills are applied
	UFUNCTION(BlueprintCallable)
	void IncreaseFaith(float Faith);

	UFUNCTION(BlueprintCallable)
    void Initialize(UMainCharacterConfig* Config, UAbilitiesState* State);

	UFUNCTION(BlueprintCallable)
	void DecreaseFaith(float Faith);

	UFUNCTION(BlueprintCallable)
	void ResetFaith();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

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

	UPROPERTY()
	AWGACharacter* Owner;

	bool IsDead;
};
