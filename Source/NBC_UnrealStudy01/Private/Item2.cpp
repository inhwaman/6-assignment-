// Fill out your copyright notice in the Description page of Project Settings.


#include "Item2.h"

AItem2::AItem2()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = false;
	
}

void AItem2::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(
		RotationTimerHandle,
		this,
		&AItem2::RotateActor,
		RotationUpdateRate,
		true
	);
}

void AItem2::RotateActor()
{
	bool bShouldRotateX = !FMath::IsNearlyZero(RotationSpeedX);
	bool bShouldRotateY = !FMath::IsNearlyZero(RotationSpeedY);
	bool bShouldRotateZ = !FMath::IsNearlyZero(RotationSpeedZ);

	if (bShouldRotateX || bShouldRotateY || bShouldRotateZ)
	{
		AddActorLocalRotation(FRotator(RotationSpeedX * RotationUpdateRate, RotationSpeedZ * RotationUpdateRate, RotationSpeedY * RotationUpdateRate));
	}
}