// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Experience.generated.h"

UCLASS()
class CAMPIREBURVIVORS_API AExperience : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	float Amount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *Mesh;

public:	

	// Sets default values for this actor's properties
	AExperience();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent *hit_component, AActor *other_actor, UPrimitiveComponent *other_component, FVector normal_impulse, FHitResult const &hit);


};
