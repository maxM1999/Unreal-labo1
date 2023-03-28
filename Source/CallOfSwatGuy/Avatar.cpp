// Fill out your copyright notice in the Description page of Project Settings.


#include "Avatar.h"
#include "CharacterAttribute.h"

AAvatar::AAvatar()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AAvatar::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(Attributes))
	{
		CurrentHealth = Attributes->MaxHealth;
	}
}

void AAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AAvatar::GetHealth()
{
	return CurrentHealth;
}

float AAvatar::GetMaxHealth()
{
	if (IsValid(Attributes))
	{
		return Attributes->MaxHealth;
	}

	return 0.f;
}

float AAvatar::GetPercentHealth()
{
	if (IsValid(Attributes))
	{
		if(Attributes->MaxHealth > 0.f)
		return CurrentHealth / Attributes->MaxHealth;
	}

	return 0.f;
}

UTexture2D* AAvatar::GetPortrait()
{
	if (IsValid(Attributes))
	{
		return Attributes->Portrait;
	}
	return nullptr;
}

float AAvatar::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float MaxHealth = GetMaxHealth();
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.f, MaxHealth);
	OnHealthChanged();
	return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

