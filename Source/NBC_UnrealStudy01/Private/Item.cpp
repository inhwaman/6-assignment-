// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"


// Sets default values
AItem::AItem()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);//½ºÅÂÆ½¸Å½ÃÄÄÆ÷³ÍÆ® ¸¸µé°í ¾ÀÄÄÆ÷³ÍÆ®¿¡ ºÙÈû


	PrimaryActorTick.bCanEverTick = true;
	MoveSpeedX = 0;
	MoveSpeedY = 0;
	MoveSpeedZ = 20;

	MoveRangeX = 0;
	MoveRangeY = 0;
	MoveRangeZ = 40;
}
void AItem::BeginPlay()
{
	Super::BeginPlay();
	CurrentLocation = GetActorLocation();
	MaxLocation =CurrentLocation+ FVector(MoveRangeX, MoveRangeY, MoveRangeZ);
	MinLocation = CurrentLocation;
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrentLocation += FVector(MoveSpeedX,MoveSpeedY,MoveSpeedZ) * DeltaTime;
	SetActorLocation(CurrentLocation);

	if (CurrentLocation.X >= MaxLocation.X || CurrentLocation.X <= MinLocation.X)
	{
		MoveSpeedX = -MoveSpeedX;
	}
	if (CurrentLocation.Y >= MaxLocation.Y || CurrentLocation.Y<= MinLocation.Y)
	{
		MoveSpeedY = -MoveSpeedY;
	}
	if (CurrentLocation.Z >= MaxLocation.Z|| CurrentLocation.Z <= MinLocation.Z)
	{
		MoveSpeedZ = -MoveSpeedZ;
	}
}

