// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "MissleLauncher.generated.h"

/**
 * 
 */
UCLASS()
class CAMPIREBURVIVORS_API UMissleLauncher : public UBaseAbility
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	UMissleLauncher();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// The function that causes the ability to do something when it gets off cooldown
	void ActivateAbility_Implementation() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
};
