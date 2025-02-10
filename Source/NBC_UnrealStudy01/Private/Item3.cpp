

#include "Item3.h"

AItem3::AItem3()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = false;
	//이동속도, 이동 거리 초기화
	MoveSpeedX = 0;
	MoveSpeedY = 0;
	MoveSpeedZ = FMath::RandRange(10.0f,20.0f);

	MoveRangeX = 0;
	MoveRangeY = 0;
	MoveRangeZ = MoveSpeedZ = FMath::RandRange(20.0f, 40.0f);

	RotationSpeedX = 0;
	RotationSpeedY = 0;
	RotationSpeedZ = FMath::RandRange(20.0f, 40.0f);

	MovingSec = FMath::RandRange(2.0f, 5.0f);
	StopMovingSec = 0;

}

void AItem3::BeginPlay()
{
	Super::BeginPlay();
	CurrentLocation = GetActorLocation();
	MaxLocation = CurrentLocation + FVector(MoveRangeX, MoveRangeY, MoveRangeZ);
	MinLocation = CurrentLocation;//이동 거리, 현재위치 계산

	StartRotation();
	StartMove();
}

void AItem3::MoveActor()
{
	CurrentLocation += FVector(MoveSpeedX, MoveSpeedY, MoveSpeedZ) * MovementUpdateRate;
	SetActorLocation(CurrentLocation);

	if (CurrentLocation.X >= MaxLocation.X || CurrentLocation.X <= MinLocation.X)
	{
		MoveSpeedX = -MoveSpeedX;
	}
	if (CurrentLocation.Y >= MaxLocation.Y || CurrentLocation.Y <= MinLocation.Y)
	{
		MoveSpeedY = -MoveSpeedY;
	}
	if (CurrentLocation.Z >= MaxLocation.Z || CurrentLocation.Z <= MinLocation.Z)
	{
		MoveSpeedZ = -MoveSpeedZ;
	}
}

void AItem3::StartMove()
{
	GetWorld()->GetTimerManager().SetTimer(
		MovementTimerHandle,
		this,
		&AItem3::MoveActor,
		MovementUpdateRate,
		true
	);
	GetWorld()->GetTimerManager().SetTimer(
		StopMovementTimerHandle,
		this,
		&AItem3::StopMove,
		MovingSec,
		false
	);
}

void AItem3::StopMove()
{
	GetWorld()->GetTimerManager().ClearTimer(MovementTimerHandle);

	GetWorld()->GetTimerManager().SetTimer
	(
		StartMovementTimerHandle,
		this,
		&AItem3::StartMove,
		StopMovingSec,
		false
	);
}

void AItem3::RotateActor()
{
	bool bShouldRotateX = !FMath::IsNearlyZero(RotationSpeedX);
	bool bShouldRotateY = !FMath::IsNearlyZero(RotationSpeedY);
	bool bShouldRotateZ = !FMath::IsNearlyZero(RotationSpeedZ);

	if (bShouldRotateX || bShouldRotateY || bShouldRotateZ)
	{
		AddActorLocalRotation(FRotator(RotationSpeedX * MovementUpdateRate, RotationSpeedZ * MovementUpdateRate, RotationSpeedY * MovementUpdateRate));
	}
}

void AItem3::StartRotation()
{
	GetWorld()->GetTimerManager().SetTimer(
		RotationTimerHandle,
		this,
		&AItem3::RotateActor,
		MovementUpdateRate,
		true
	);
	GetWorld()->GetTimerManager().SetTimer(
		StopRotationTimerHandle,
		this,
		&AItem3::StopRotation,
		MovingSec,
		false
	);
}

void AItem3::StopRotation()
{
	GetWorld()->GetTimerManager().ClearTimer(RotationTimerHandle);

	GetWorld()->GetTimerManager().SetTimer(
		StartRotationTimerHandle,
		this,
		&AItem3::StartRotation,
		StopMovingSec,
		false
	);
}


