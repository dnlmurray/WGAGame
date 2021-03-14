// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilitiesConfig.h"
#include "AbilitiesState.h"

#include "Weapon.generated.h"

UCLASS()
class AWeaponVisual : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AWeaponVisual() { }
	
	// Visual representation
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* WeaponMesh;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WGAGAME_API UWeapon : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	UWeapon();

	// Sets up execution flag, must be called BEFORE combat animations
	UFUNCTION(BlueprintCallable)
    void EnableDamageApplying();

	// Drops execution flag, must be called AFTER combat animation
	UFUNCTION(BlueprintCallable)
    void DisableDamageApplying();

	UFUNCTION(BlueprintCallable)
    void Initialize(UAbilitiesConfig* Config, UAbilitiesState* State);
	// Creates nodes on the line between StartLocation and EndLocation
	UFUNCTION(BlueprintCallable)
    void SetNodes(const FVector& StartLocation, const FVector& EndLocation, int32 NumberOfNodes);
	
	// Overrided Tick funtion, isn't really used as is is just a base class
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

	// Visual representation
	UPROPERTY(EditDefaultsOnly,Category="ActorSpawning")
	TSubclassOf<AWeaponVisual> WeaponVisualObject;
	
private:
	// An array of nodes which are used to detect weapon collision.
	// (in local coordinates)
	TArray<FVector> Nodes;

	// The transformation matrix which determines the last recorded
	// weapon position
	FTransform CurrentTransform;

	// Weapon's visual representation
	AWeaponVisual* WeaponVisual;

	// This component's owner
	ACharacter* Owner;

	// Last actor hit by this weapon
	AActor const* LastActor;
	
	// General configuration
	UAbilitiesConfig const* ConfigurationData;

	// External state component
	UAbilitiesState* AbilitiesState;
	
	// Property structure for the line trace function
	FCollisionQueryParams CollisionQueryParams;

	// If the flag is set then the weapon starts detecting collision and
	// applying damage to anything it hits
	uint8 bExecutionEnabled:1;		
};
