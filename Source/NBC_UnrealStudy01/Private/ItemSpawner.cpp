// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpawner.h"
// Sets default values
AItemSpawner::AItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnItem();
}

void AItemSpawner::SpawnItem()
{
	for (int32 i = 0; i < 10; i++)
	{
		float RandomX = FMath::RandRange(200.0f, 1500.0f);
		float RandomY = FMath::RandRange(2380.0f, 3850.0f);

		FVector SpawnLocation(RandomX, RandomY, 80.0f);
		FRotator SpawnRotation(0.0f, 0.0f, 0.0f);

		AItem* SpawnItem = GetWorld()->SpawnActor<AItem>(ItemClass, SpawnLocation, SpawnRotation);

		if (SpawnItem)
		{
			SpawnItem->SetLifeSpan(10.0f);
		}
	}
}