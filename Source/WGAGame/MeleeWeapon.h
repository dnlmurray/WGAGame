// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitiesConfig.h"
#include "MeleeWeapon.generated.h"

// Make sure this redefenition matches the corresponding one in the DefaultEngine.ini file
#define ECC_Weapon ECollisionChannel::ECC_GameTraceChannel1

UCLASS()
class WGAGAME_API AMeleeWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeleeWeapon();

	// Sets up execution flag, must be called BEFORE combat animations
	UFUNCTION(BlueprintCallable)
	void EnableDamageApplying();

	// Drops execution flag, must be called AFTER combat animation
	UFUNCTION(BlueprintCallable)
	void DisableDamageApplying();

	UFUNCTION(BlueprintCallable)
    void Initialize(UAbilitiesConfig* Config)
	{
		ConfigurationData = Config;
	}

	// Creates nodes on the line between StartLocation and EndLocation
	UFUNCTION(BlueprintCallable)
	void SetNodes(const FVector& StartLocation, const FVector& EndLocation, int32 NumberOfNodes);

	// Visual representation
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(BlueprintReadWrite)
	AActor* WeaponOwner;
	
protected:
	// Overrided Tick funtion, isn't really used as is is just a base class
	virtual void Tick(float DeltaTime) override;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	// An array of nodes which are used to detect weapon collision.
	// (in local coordinates)
	TArray<FVector> Nodes;

	// The transformation matrix which determines the last recorded
	// weapon position
	FTransform CurrentTransform;

	// Last actor hit by this weapon
	AActor* LastActor;
	
	// General configuration
	UAbilitiesConfig* ConfigurationData;

	// Property structure for the line trace function
	FCollisionQueryParams CollisionQueryParams;

	// If the flag is set then the weapon starts detecting collision and
	// applying damage to anything it hits
	uint8 bExecutionEnabled:1;
};
