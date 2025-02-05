// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"


UCLASS()
class NBC_UNREALSTUDY01_API AItem : public AActor
{
	GENERATED_BODY()

public:
	AItem();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item|Components")
	UStaticMeshComponent* StaticMeshComp;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item|Properties")

	float MoveSpeedX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Properties")
	float MoveSpeedY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Properties")
	float MoveSpeedZ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Properties")
	float MoveRangeX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Properties")
	float MoveRangeY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Properties")
	float MoveRangeZ;
	FVector CurrentLocation;
	FVector MaxLocation;
	FVector MinLocation;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime)override;
	

};
