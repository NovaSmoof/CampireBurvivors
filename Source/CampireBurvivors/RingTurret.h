// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RingTurret.generated.h"

UCLASS()
class CAMPIREBURVIVORS_API ARingTurret : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent * TurretBody;

public:	
	// Sets default values for this actor's properties
	ARingTurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Fire(float Speed, float Area, float BaseDamage, float Knockback, float Duration, int Penetration, int Bounces);

};
