// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrownProjectile.h"

#include "Enemy.h"


// Sets default values
AThrownProjectile::AThrownProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OnActorBeginOverlap.AddDynamic(this, &AThrownProjectile::OnOverlapBegin);
}

void AThrownProjectile::OnOverlapBegin(AActor* MyOverlappedActor, AActor* OtherActor)
{
	if (!OtherActor->GetClass()->IsChildOf(AEnemy::StaticClass()))
	{
        Notifier.Broadcast(OtherActor);
		OnOverlapEnd();
	}
}

// Called when the game starts or when spawned
void AThrownProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThrownProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

