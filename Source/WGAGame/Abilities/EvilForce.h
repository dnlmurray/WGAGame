// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EvilForce.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WGAGAME_API UEvilForce : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEvilForce();
	
	UFUNCTION(BlueprintCallable)
    void EnableEvilForceIncreasing() { bEvilForceIsIncreasing = true; }

	UFUNCTION(BlueprintCallable)
    void DisableEvilForceIncreasing() { bEvilForceIsIncreasing = false; }

	UFUNCTION(BlueprintCallable)
    void DecreaseEvilForce(float percent);

	UFUNCTION(BlueprintCallable)
	void IncreaseEvilForce(float percent);

	UFUNCTION(BlueprintCallable)
	void Reset();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite)
	float MinPercent;

	UPROPERTY(BlueprintReadWrite)
	float MaxPercent;
	
	UPROPERTY(BlueprintReadOnly)
	float Percent;

	UPROPERTY(BlueprintReadWrite)
	float EvilForceIncreasePerSecond;
	
private:
	
	bool bEvilForceIsIncreasing;
};
