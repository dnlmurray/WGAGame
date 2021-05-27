// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "../Config/MainCharacterConfig.h"
#include "../WGACharacter.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class WGAGAME_API AMainCharacter : public AWGACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override final;
	
	UFUNCTION(BlueprintImplementableEvent)
    void OnActionStateChange(bool IsCombat);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnEnemyKill();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintImplementableEvent)
	void ResetPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMainCharacterConfig* ConfigInst;
	
	UPROPERTY(BlueprintReadWrite)
	bool bInCombat;
};