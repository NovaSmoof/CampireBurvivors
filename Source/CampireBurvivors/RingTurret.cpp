// Fill out your copyright notice in the Description page of Project Settings.

#include "RingTurret.h"
#include "RingTurretProjectile.h"
#include "Engine/StaticMesh.h"

// Sets default values
ARingTurret::ARingTurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TurretBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	TurretBody->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/Abilities/Ring/fear-turret.fear-turret"));
	if (MeshObj.Succeeded())
	{
		TurretBody->SetStaticMesh(MeshObj.Object);
	}
	TurretBody->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	this->SetRootComponent(TurretBody);
}

// Called when the game starts or when spawned
void ARingTurret::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARingTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARingTurret::Fire()
{
	auto const &transform = this->GetTransform();
	ARingTurretProjectile *projectile = GetWorld()->SpawnActor<ARingTurretProjectile>(transform.GetLocation(), transform.GetRotation().Rotator());
	if (projectile) 
	{
		projectile->AddActorWorldOffset(FVector(10.0, 0.0, 0.0));
		UStaticMeshComponent * const mesh = dynamic_cast<UStaticMeshComponent *>(projectile->GetComponentByClass(UStaticMeshComponent::StaticClass()));
		FVector x_axis = transform.GetUnitAxis(EAxis::Type::Z);
		mesh->AddImpulse(10000.0F * x_axis);
	}
}

