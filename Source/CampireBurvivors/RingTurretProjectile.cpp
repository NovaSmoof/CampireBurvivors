// Fill out your copyright notice in the Description page of Project Settings.

#include "RingTurretProjectile.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

// Sets default values
ARingTurretProjectile::ARingTurretProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	Projectile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Projectile->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (MeshObj.Succeeded())
	{
		Projectile->SetStaticMesh(MeshObj.Object);
	}
	Projectile->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Projectile->SetSimulatePhysics(true);
	Projectile->SetEnableGravity(false);
	Projectile->SetWorldScale3D(FVector(0.25F, 0.25F, 0.25F));
	Projectile->SetCollisionProfileName(TEXT("BlockAll"), true);
	Projectile->SetNotifyRigidBodyCollision(true);

	static ConstructorHelpers::FObjectFinder<UObject> PhysicsMaterial(TEXT("PhysicalMaterial'/Game/Bouncy.Bouncy'"));
	if (PhysicsMaterial.Succeeded() && PhysicsMaterial.Object)
	{
		{
			Projectile->SetPhysMaterialOverride((UPhysicalMaterial*)PhysicsMaterial.Object);
		}
	}

	this->SetRootComponent(Projectile);

	Bounces = 3;
	Lifespan = 5.0F;
}

// Called when the game starts or when spawned
void ARingTurretProjectile::BeginPlay()
{
	Super::BeginPlay();
	// Uncomment this line if you want the things to locked axially, but then when they collide their upwards direction doesn't go anywhere.
	// Projectile->SetConstraintMode(EDOFMode::XYPlane);
	Projectile->OnComponentHit.AddDynamic(this, &ARingTurretProjectile::OnHit);
}

// Called every frame
void ARingTurretProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Lifespan -= DeltaTime;
	if (Lifespan < 0.0F)
	{
		Destroy();
	}
}

void ARingTurretProjectile::OnHit(UPrimitiveComponent *hit_component, 
	AActor *other_actor,
	UPrimitiveComponent *other_component, 
	FVector normal_impulse, 
	FHitResult const & hit)
{
	Bounces -= 1;
	if (Bounces == 0)
	{
		Destroy();
	}

	if (!other_actor || other_actor->ActorHasTag("Enemy"))
	{
		Destroy();
	}
}

void ARingTurretProjectile::OnOverlapBegin(UPrimitiveComponent * const overlapped_component, AActor *const other_actor, UPrimitiveComponent *const other_comp, int32 other_body_index, bool from_sweep, FHitResult const &sweep_result)
{
}

void ARingTurretProjectile::OnOverlapEnd(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
}

