// Fill out your copyright notice in the Description page of Project Settings.


#include "Experience.h"

#include "Kismet/KismetSystemLibrary.h"
#include <array>

// Sets default values
AExperience::AExperience()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Mesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Game/crystal.crystal'"));
	if (MeshObj.Succeeded())
	{
		Mesh->SetStaticMesh(MeshObj.Object);
	}
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetSimulatePhysics(true);
	Mesh->SetEnableGravity(false);
	Mesh->SetCollisionProfileName(TEXT("BlockAllDynamic"), true);
	Mesh->SetNotifyRigidBodyCollision(true);
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Amount = 1;
}

// Called when the game starts or when spawned
void AExperience::BeginPlay()
{
	Super::BeginPlay();
	Mesh->OnComponentHit.AddDynamic(this, &AExperience::OnHit);
}

// Called every frame
void AExperience::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto const & transform = this->GetTransform();
	TArray<TEnumAsByte<EObjectTypeQuery>> object_types {UEngineTypes::ConvertToObjectType(ECC_WorldDynamic)};
	TArray<AActor *> out_actors;
	float const radius = (Amount * 5.0F + 5.0F) * 20.0F;
	if (UKismetSystemLibrary::SphereOverlapActors(GetWorld(), transform.GetLocation(), radius, object_types, this->StaticClass(), {}, out_actors))
	{
		for (AActor *const actor : out_actors)
		{
			AExperience *const other = dynamic_cast<AExperience *>(actor);
			UE_LOG(LogTemp, Warning, TEXT("The %s's velocity is: %s"), *other->GetName(), * other->Mesh->GetComponentVelocity().ToString());
			other->Mesh->AddForce(9.81F * 9.81F * 9.81F * -(other->GetTransform().GetLocation() - transform.GetLocation()).GetSafeNormal());
		}
	}
}

void AExperience::OnHit(UPrimitiveComponent *hit_component, AActor *other_actor, UPrimitiveComponent *other_component, FVector normal_impulse, FHitResult const &hit)
{
	if (other_actor == GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		// Something to handle receiving experience here
		Destroy();
	}

	if (AExperience * const other = dynamic_cast<AExperience*>(other_actor); other != nullptr && !other->IsActorBeingDestroyed())
	{
		FActorSpawnParameters spawn_params;
		spawn_params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AExperience * const merged_expereince = GetWorld()->SpawnActor<AExperience>((this->GetTransform().GetLocation() + other_actor->GetTransform().GetLocation())/2.0F, FRotator::ZeroRotator);
		if (merged_expereince)
		{
			merged_expereince->Amount = this->Amount + other->Amount;
			if (merged_expereince->Amount < 10.0F)
			{
				merged_expereince->Amount += 1;
			}
			else
			{
				merged_expereince->Amount *= 1.1;
			}
		}
		this->Destroy();
		other->Destroy();
	}
}



