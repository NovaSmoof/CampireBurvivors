// Fill out your copyright notice in the Description page of Project Settings.


#include "MissleLauncher.h"

UMissleLauncher::UMissleLauncher()
{
	PrimaryComponentTick.bCanEverTick = true;

	Speed = 0.5F;
	BaseDamage = 15.0F;
	Duration = 5.0F;
	Cooldown = 1.83F;
	Area = 0.25F;
	Knockback = 0.0F;
	Amount = 3;
	Penetration = 6;
}

void UMissleLauncher::BeginPlay()
{
	Super::BeginPlay();
}

void UMissleLauncher::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMissleLauncher::ActivateAbility_Implementation()
{
}