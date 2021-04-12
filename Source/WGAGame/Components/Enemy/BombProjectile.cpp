// Fill out your copyright notice in the Description page of Project Settings.


#include "BombProjectile.h"


// Sets default values
ABombProjectile::ABombProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OnActorBeginOverlap.AddDynamic(this, &ABombProjectile::OnOverlapBegin);
}

void ABombProjectile::OnOverlapBegin(AActor* MyOverlappedActor, AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
        Notifier.Broadcast();
		OnOverlapEnd();
	}
}

// Called when the game starts or when spawned
void ABombProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABombProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

