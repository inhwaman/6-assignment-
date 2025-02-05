// Fill out your copyright notice in the Description page of Project Settings.


#include "Item2.h"

AItem2::AItem2()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = true;
	
}

void AItem2::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItem2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bool bShouldRotateX = !FMath::IsNearlyZero(RotationSpeedX);
	bool bShouldRotateY = !FMath::IsNearlyZero(RotationSpeedY);
	bool bShouldRotateZ = !FMath::IsNearlyZero(RotationSpeedZ);
	
	if (bShouldRotateX||bShouldRotateY||bShouldRotateZ)
	{
		AddActorLocalRotation(FRotator(RotationSpeedX * DeltaTime, RotationSpeedZ * DeltaTime, RotationSpeedY*DeltaTime));
	}

}

