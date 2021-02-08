// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "AbilitiesConfig.h"
#include "Components/ActorComponent.h"
#include "WhiteBarrier.generated.h"

UCLASS()
class AWhiteBarrierVisual : public AActor
{
	GENERATED_BODY()
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WGAGAME_API UWhiteBarrier : public UActorComponent
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

	// Visual representation
	UPROPERTY(EditDefaultsOnly,Category="ActorSpawning")
	TSubclassOf<AWhiteBarrierVisual> WhiteBarrierObject;

	UFUNCTION(BlueprintCallable)
    void Initialize(UAbilitiesConfig* Config)
	{
		ConfigurationData = Config;
		Owner = (ACharacter*)GetOwner();
	}
	
private:
	// Removes white barrier
	void Remove();

	// Checks if the character (owner) is currently under effect
	void CheckIfOwnerIsUnderEffect();
	
	FVector Location;
	
	UAbilitiesConfig const* ConfigurationData;

	ACharacter const* Owner;

	AWhiteBarrierVisual* WhiteBarrierObjectRef;
	
	float TimeSinceActivation;

	uint8 IsActive:1;
	
	uint8 OwnerIsUnderEffect:1;
};
