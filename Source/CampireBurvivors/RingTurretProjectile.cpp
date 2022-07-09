// Fill out your copyright notice in the Description page of Project Settings.

#include "RingTurretProjectile.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "ProjectileDamageType.h"

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
	Projectile->SetCollisionProfileName(TEXT("Projectiles"), true);
	Projectile->SetNotifyRigidBodyCollision(true);

	static ConstructorHelpers::FObjectFinder<UObject> PhysicsMaterial(TEXT("PhysicalMaterial'/Game/PhysicsMaterials/PMBouncy.PMBouncy'"));
	if (PhysicsMaterial.Succeeded() && PhysicsMaterial.Object)
	{
		{
			Projectile->SetPhysMaterialOverride((UPhysicalMaterial*)PhysicsMaterial.Object);
		}
	}

	this->SetRootComponent(Projectile);

	Bounces = 3;
	Damage = 15.0F;
	EnemyPenetrations = 0;
}

// Called when the game starts or when spawned
void ARingTurretProjectile::BeginPlay()
{
	Super::BeginPlay();
	// Uncomment this line if you want the things to locked axially, but then when they collide their upwards direction doesn't go anywhere.
	// Projectile->SetConstraintMode(EDOFMode::XYPlane);
	Projectile->OnComponentHit.AddDynamic(this, &ARingTurretProjectile::OnHit);
	Projectile->OnComponentBeginOverlap.AddDynamic(this, &ARingTurretProjectile::OnOverlapBegins);
}

// Called every frame
void ARingTurretProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARingTurretProjectile::OnHit(UPrimitiveComponent *hit_component, 
	AActor *other_actor,
	UPrimitiveComponent *other_component, 
	FVector normal_impulse, 
	FHitResult const & hit)
{
	if (!other_actor)
	{
		return;
	}

	Bounces -= 1;
	if (Bounces == 0)
	{
		Destroy();
		return;
	}
}

void ARingTurretProjectile::OnOverlapBegins(UPrimitiveComponent *overlapped_component, 
                                            AActor *other_actor, 
                                            UPrimitiveComponent *other_comp, 
                                            int32 other_body_index, 
                                            bool from_sweep, 
                                            const FHitResult &sweep_result)
{
	if (!other_actor)
	{
		return;
	}

	if (other_actor->ActorHasTag("Enemy"))
	{
		APlayerController *const player_controller = GetWorld()->GetFirstPlayerController();
		APawn *const player = player_controller->GetPawn();

		FDamageEvent damage_event;
		other_actor->TakeDamage(Damage, damage_event, player_controller, player);
		if (this->EnemyPenetrations > 0)
		{
			this->EnemyPenetrations -= 1;
		}
		else
		{
			Destroy();
		}
		return;
	}
}
