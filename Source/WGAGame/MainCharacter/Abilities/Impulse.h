// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "AbilitiesConfig.h"
#include "AbilitiesState.h"
#include "Impulse.generated.h"

#define ECC_Magic ECollisionChannel::ECC_GameTraceChannel2

UCLASS()
class AImpulseVisual : public AActor
{
	GENERATED_BODY()
	
	AImpulseVisual() { }
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WGAGAME_API UImpulse : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UImpulse();

	UFUNCTION(BlueprintCallable)
    void Initialize(UAbilitiesConfig* Config)
	{ 
		ConfigurationData = Config;
		Owner = Cast<ACharacter>(GetOwner());
	}

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Applies the effect to every enemy in the area
	UFUNCTION(BlueprintCallable)
    void ApplyEffect();

	// Visual representation
	UPROPERTY(EditDefaultsOnly,Category="ActorSpawning")
	TSubclassOf<AImpulseVisual> ImpulseVisualObject;

private:
	UAbilitiesConfig const* ConfigurationData;
	UAbilitiesState const*  AbilitiesState;
	ACharacter const*       Owner;
	AImpulseVisual*         VisualObjectRef;
	float                   TimeSinceLastActivation;
	bool                    bWasActivated;
};
