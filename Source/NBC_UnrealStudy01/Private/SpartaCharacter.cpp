

#include "SpartaCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include"Camera/CameraComponent.h"
#include"GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "SpartaPlayerController.h"

ASpartaCharacter::ASpartaCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	RootComponent = CapsuleComp;
	CapsuleComp->InitCapsuleSize(34.f, 88.f);
	CapsuleComp->SetSimulatePhysics(false);//¹°¸® ²ô±â

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(CapsuleComp);
	MeshComp->SetSimulatePhysics(false);//¹°¸® ²ô±â

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp -> SetupAttachment(CapsuleComp);
	SpringArmComp->TargetArmLength = 300.f;
	SpringArmComp->bUsePawnControlRotation = false;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	MovementInput = FVector2D::ZeroVector;
	LookInput = FVector2D::ZeroVector;
	Velocity = FVector::ZeroVector;

}

void ASpartaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const FRotator CameraRotation = CameraComp->GetComponentRotation();
	const FRotator YawOnlyRotation(0.f, CameraRotation.Yaw, 0.f);

	const FVector CameraForward = FRotationMatrix(YawOnlyRotation).GetUnitAxis(EAxis::X);
	const FVector CameraRight = FRotationMatrix(YawOnlyRotation).GetUnitAxis(EAxis::Y);

	const FVector InputDirection = (CameraForward * MovementInput.X) + (CameraRight * MovementInput.Y);
	const FVector DesiredVelocity = InputDirection.GetSafeNormal() * MaxWalkSpeed;

	Velocity = FMath::VInterpTo(Velocity, DesiredVelocity, DeltaTime, VelocityInterpSpeed);
	AddActorWorldOffset(Velocity * DeltaTime, true);
	if (!FMath::IsNearlyZero(LookInput.X))
	{
		const float YawRotation = LookInput.X * TurnRate * DeltaTime;
		AddActorLocalRotation(FRotator(0.f, YawRotation, 0.f));
	}

	if (!FMath::IsNearlyZero(LookInput.Y))
	{
		FRotator CurrentArmRotation = SpringArmComp->GetRelativeRotation();
		float NewPitch = CurrentArmRotation.Pitch - (LookInput.Y * LookUpRate * DeltaTime);
		NewPitch = FMath::Clamp(NewPitch, MinPitch, MaxPitch);
		CurrentArmRotation.Pitch = NewPitch;
		SpringArmComp->SetRelativeRotation(CurrentArmRotation);
	}
}

void ASpartaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ASpartaPlayerController* PlayerController = Cast<ASpartaPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction
				(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaCharacter::Move
				);
				EnhancedInput->BindAction
				(
					PlayerController->MoveAction,
					ETriggerEvent::Completed,
					this,
					&ASpartaCharacter::StopMove
				);
			}
			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction
				(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaCharacter::Look
				);
				EnhancedInput->BindAction
				(
					PlayerController->LookAction,
					ETriggerEvent::Completed,
					this,
					&ASpartaCharacter::StopLook
				);
			}
			if (PlayerController->SprintAction)
			{
				EnhancedInput->BindAction
				(
					PlayerController->SprintAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaCharacter::Sprint
				);
				EnhancedInput->BindAction
				(
					PlayerController->SprintAction,
					ETriggerEvent::Completed,
					this,
					&ASpartaCharacter::StopSprint
				);
			}

		}
	}
}

void ASpartaCharacter::Move(const FInputActionValue& Value)
{
	MovementInput = Value.Get<FVector2D>();
}

void ASpartaCharacter::StopMove(const FInputActionValue& Value)
{
	MovementInput = FVector2D::ZeroVector;
}

void ASpartaCharacter::Look(const FInputActionValue& Value)
{
	LookInput = Value.Get<FVector2D>();
}

void ASpartaCharacter::StopLook(const FInputActionValue& Value)
{
	LookInput = FVector2D::ZeroVector;
}

void ASpartaCharacter::Sprint(const FInputActionValue& Value)
{
	MaxWalkSpeed = SprintSpeed;
}

void ASpartaCharacter::StopSprint(const FInputActionValue& Value)
{
	MaxWalkSpeed = NormalSpeed;
}

