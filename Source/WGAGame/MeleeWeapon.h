// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
	void EnableDebugMode();

	UFUNCTION(BlueprintCallable)
	void DisableDebugMode();

	// Creates nodes on the line between StartLocation and EndLocation
	UFUNCTION(BlueprintCallable)
	void SetNodes(const FVector& StartLocation, const FVector& EndLocation, int32 NumberOfNodes);

	// Visual representation
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* WeaponMesh;
	
protected:
	// Overrided Tick funtion, isn't really used as is is just a base class
	virtual void Tick(float DeltaTime) override;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Call it every frame in the Tick function
	//UFUNCTION(BlueprintCallable)
	//void ExecuteWeaponTrace();

	// The amount of damage this weapon applies to an object
	UPROPERTY(BlueprintReadWrite)
	float BaseDamage = 50;

public:
	UPROPERTY(BlueprintReadWrite)
	AActor* WeaponOwner;
	
private:
	// An array of nodes which are used to detect weapon collision.
	// (in local coordinates)
	TArray<FVector> Nodes;

	// The transformation matrix which determines the last recorded
	// weapon position
	FTransform CurrentTransform;

	// Property structure for the line trace function
	FCollisionQueryParams CollisionQueryParams;

	// If the flag is set then the weapon starts detecting collision and
	// applying damage to anything it hits
	uint8 bExecutionEnabled:1;

	// If the flag is set then the weapon enters debug mode:
	// TODO: debug mode description
	uint8 bDebugModeEnabled:1;

	// Last actor hit by this weapon
	AActor* LastActor;
};
