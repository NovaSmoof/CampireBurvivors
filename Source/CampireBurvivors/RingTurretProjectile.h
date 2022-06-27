// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RingTurretProjectile.generated.h"

UCLASS()
class CAMPIREBURVIVORS_API ARingTurretProjectile : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *Projectile;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	int32 Bounces;

	float Lifespan;
	
public:	
	// Sets default values for this actor's properties
	ARingTurretProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UFUNCTION()
	void OnHit(UPrimitiveComponent *hit_component, AActor *other_actor, UPrimitiveComponent *other_component, FVector normal_impulse, FHitResult const &hit);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent *overlapped_component, class AActor *other_actor, class UPrimitiveComponent *other_component, int32 other_body_index, bool from_sweep,  FHitResult const & sweep_result);

	// declare overlap end function
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent *overlapped_component, class AActor *other_actor, class UPrimitiveComponent *other_component, int32 other_body_index);
};
