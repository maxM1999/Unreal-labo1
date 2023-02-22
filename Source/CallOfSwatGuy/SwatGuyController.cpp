// Fill out your copyright notice in the Description page of Project Settings.


#include "SwatGuyController.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "SwatGuyAnimInstance.h"

ASwatGuyController::ASwatGuyController()
{
}

void ASwatGuyController::BeginPlay()
{
	MouseCameraSensitivity *= 10;
	GamepadCameraSensitivity *= 10;
}

void ASwatGuyController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (!InputComponent) return;

	InputComponent->BindAxis(TEXT("MoveForward"), this, &ASwatGuyController::MoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &ASwatGuyController::MoveRight);
	InputComponent->BindAxis(TEXT("LookVertical"), this, &ASwatGuyController::LookVertical);
	InputComponent->BindAxis(TEXT("LookHorizontal"), this, &ASwatGuyController::LookHorizontal);
	InputComponent->BindAxis(TEXT("GamepadLookVertical"), this, &ASwatGuyController::GamepadLookVertical);
	InputComponent->BindAxis(TEXT("GamepadLookHorizontal"), this, &ASwatGuyController::GamepadLookHorizontal);
	
	InputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &ASwatGuyController::Crouch);
	InputComponent->BindAction(TEXT("Dance"), EInputEvent::IE_Pressed, this, &ASwatGuyController::Dance);
}

void ASwatGuyController::MoveForward(float InValue)
{
	if (InValue == 0.f || bIsDancing) return;

	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn) return;

	const FVector ControlledPawnForward = ControlledPawn->GetActorForwardVector();
	ControlledPawn->AddMovementInput(ControlledPawnForward, InValue);
}

void ASwatGuyController::MoveRight(float InValue)
{
	if (InValue == 0.f || bIsDancing) return;

	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn) return;

	const FVector ControlledPawnRight = ControlledPawn->GetActorRightVector();
	ControlledPawn->AddMovementInput(ControlledPawnRight, InValue);
}

void ASwatGuyController::LookVertical(float InValue)
{
	if (InValue == 0.f || !GetWorld()) return;

	const float Dt = GetWorld()->GetDeltaSeconds();
	AddPitchInput(InValue * MouseCameraSensitivity.Y * Dt);
}

void ASwatGuyController::LookHorizontal(float InValue)
{
	if (InValue == 0.f || !GetWorld()) return;

	const float Dt = GetWorld()->GetDeltaSeconds();
	AddYawInput(InValue * MouseCameraSensitivity.X * Dt);
}

void ASwatGuyController::GamepadLookVertical(float InValue)
{
	if (InValue == 0.f || !GetWorld()) return;

	const float Dt = GetWorld()->GetDeltaSeconds();
	AddPitchInput(InValue * GamepadCameraSensitivity.Y * Dt);
}

void ASwatGuyController::GamepadLookHorizontal(float InValue)
{
	if (InValue == 0.f || !GetWorld()) return;

	const float Dt = GetWorld()->GetDeltaSeconds();
	AddYawInput(InValue * GamepadCameraSensitivity.X * Dt);
}

void ASwatGuyController::Crouch()
{
    if(bIsDancing) return;
	ACharacter* ControlledCharacter = Cast<ACharacter>(GetPawn());
	if (!ControlledCharacter) return;

	if (!ControlledCharacter->bIsCrouched)
	{
		ControlledCharacter->Crouch();
	}
	else
	{
		ControlledCharacter->UnCrouch();
	}
}

void ASwatGuyController::Dance()
{
	bIsDancing = !bIsDancing;
	if (ACharacter* Char = Cast<ACharacter>(GetPawn()))
	{
		USwatGuyAnimInstance* AnimInstance = Cast<USwatGuyAnimInstance>(Char->GetMesh()->GetAnimInstance());
		if (AnimInstance)
		{
			AnimInstance->ToggleIsDancing();
		}
	}
}
