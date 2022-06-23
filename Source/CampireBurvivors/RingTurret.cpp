// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/StaticMesh.h"
#include "RingTurret.h"

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

