// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item2.generated.h"

UCLASS()
class NBC_UNREALSTUDY01_API AItem2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem2();

protected:
	// Called when the game starts or when spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Properties")
	float RotationSpeedX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Properties")
	float RotationSpeedY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Properties")
	float RotationSpeedZ;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
