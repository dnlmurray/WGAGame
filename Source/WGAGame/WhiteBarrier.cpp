// Fill out your copyright notice in the Description page of Project Settings.


#include "WhiteBarrier.h"

#include "Components/CapsuleComponent.h"

#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UWhiteBarrier::UWhiteBarrier()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called every frame
void UWhiteBarrier::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsActive) return;

	if (TimeSinceActivation >= ConfigurationData->WhiteBarrierConfiguration.Duration) Remove();

	CheckIfOwnerIsUnderEffect();

	TimeSinceActivation += DeltaTime;
}

void UWhiteBarrier::Place()
{
	if (IsActive || ConfigurationData->WhiteBarrierConfiguration.Duration == 0) return;

	IsActive = true;
	Location = Owner->GetActorLocation() -
			FVector(0.0f,
				    0.0f,
				    Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	TimeSinceActivation = 0.0f;
	
	FActorSpawnParameters SpawnParams;

	FTransform Transform(Owner->GetActorRotation(),
		        Location,
		          FVector(10.0f, 10.0f, 0.025f));
	
	WhiteBarrierObjectRef
		= GetWorld()->SpawnActor<AWhiteBarrierVisual>(WhiteBarrierObject, Transform, SpawnParams);
}

void UWhiteBarrier::Remove()
{
	WhiteBarrierObjectRef->Destroy();
	IsActive = false;
}

void UWhiteBarrier::CheckIfOwnerIsUnderEffect()
{
	float Distance = (Owner->GetActorLocation() - Location).Size();
	Distance = FMath::Abs(Distance);

	OwnerIsUnderEffect
		= (Distance <= ConfigurationData->WhiteBarrierConfiguration.Radius) ? true : false;

	if (OwnerIsUnderEffect && ConfigurationData->WhiteBarrierConfiguration.Debug && GEngine)
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.f,
			FColor::Green,
			TEXT("[WB]: Effect is applied."),
			true,
			FVector2D(1.0f, 1.0f));
}

