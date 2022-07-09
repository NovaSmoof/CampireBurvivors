// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RingTurretProjectile.generated.h"

UCLASS()
class CAMPIREBURVIVORS_API ARingTurretProjectile : public AActor
{
	GENERATED_BODY()

	friend class ARingTurret;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *Projectile;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	int32 Bounces;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	int32 EnemyPenetrations;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	float Damage;
	
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
	void OnOverlapBegins(UPrimitiveComponent *overlapped_component, AActor *other_actor, UPrimitiveComponent *other_comp, int32 other_body_index, bool from_sweep, const FHitResult &sweep_result);

};
