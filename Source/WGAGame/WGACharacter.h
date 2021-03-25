// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WGACharacter.generated.h"

UCLASS()
class WGAGAME_API AWGACharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWGACharacter();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnHitReaction(const float DamageAmount);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnDeathReaction(const UActorComponent* causer);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnSpawnReaction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
