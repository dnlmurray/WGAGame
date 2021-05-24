// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "ThrownProjectile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FProjectileNotifier, AActor*, OverlappedActor);

UCLASS()
class WGAGAME_API AThrownProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AThrownProjectile();
	
	UFUNCTION()
    void OnOverlapBegin(AActor* MyOverlappedActor, AActor* OtherActor);

	UFUNCTION(BlueprintImplementableEvent)
	void OnOverlapEnd();
	
    virtual void Tick(float DeltaTime) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	FProjectileNotifier Notifier;
};
