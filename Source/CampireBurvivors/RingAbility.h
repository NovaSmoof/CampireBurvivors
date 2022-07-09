// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RingTurret.h"
#include "Components/SceneComponent.h"
#include "BaseAbility.h"
#include "RingAbility.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAMPIREBURVIVORS_API URingAbility : public UBaseAbility
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	float TurretOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	int Bounces;

	TSubclassOf<ARingTurret> BPRingTurret;
public:	
	// Sets default values for this component's properties
	URingAbility();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// The function that causes the ability to do something when it gets off cooldown
	void ActivateAbility_Implementation() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void CreateTurrets(int TurretCount);
	void ReassignTurretRotation();

	float Timer = 0.0F;
		
};
