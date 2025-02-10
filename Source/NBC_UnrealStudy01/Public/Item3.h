// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item3.generated.h"

UCLASS()
class NBC_UNREALSTUDY01_API AItem3 : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem3();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Item|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Components")
	UStaticMeshComponent* StaticMeshComp;

	float MoveSpeedX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|MoveProperties")
	float MoveSpeedY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|MoveProperties")
	float MoveSpeedZ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|MoveProperties")
	float MoveRangeX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|MoveProperties")
	float MoveRangeY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|MoveProperties")
	float MoveRangeZ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|RotateProperties")
	float RotationSpeedX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|RotateProperties")
	float RotationSpeedY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|RotateProperties")
	float RotationSpeedZ;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Second")
	float MovingSec;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Second")
	float StopMovingSec;


	FVector CurrentLocation;
	FVector MaxLocation;
	FVector MinLocation;

	float MovementUpdateRate = 0.016f;
	FTimerHandle MovementTimerHandle;
	FTimerHandle StartMovementTimerHandle;
	FTimerHandle StopMovementTimerHandle;
	FTimerHandle RotationTimerHandle;
	FTimerHandle StartRotationTimerHandle;
	FTimerHandle StopRotationTimerHandle;

	virtual void BeginPlay() override;

	void MoveActor();
	void StartMove();
	void StopMove();

	void RotateActor();
	void StartRotation();
	void StopRotation();

};
