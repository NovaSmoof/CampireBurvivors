// Fill out your copyright notice in the Description page of Project Settings.

#include "RingAbility.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
URingAbility::URingAbility()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Speed = 0.5F;
	BaseDamage = 15.0F;
	Duration = 5.0F;
	Cooldown = 1.83F;
	Area = 0.25F;
	Knockback = 0.0F;
	Amount = 3;
	Penetration = 6;

	TurretOffset = 100.0F;
	Bounces = 3;
	
	static ConstructorHelpers::FClassFinder<ARingTurret> BPRingTurretFinder(TEXT("Class'/Game/Abilities/Ring/BPRingTurret.BPRingTurret_C'"));
	if (!BPRingTurretFinder.Succeeded())
	{
		return;
	}
	BPRingTurret = BPRingTurretFinder.Class;
}

// Called when the game starts
void URingAbility::BeginPlay()
{
	Super::BeginPlay();
	
	this->SetUsingAbsoluteRotation(true);
	CreateTurrets(GetEffectiveAmount()); 
	ReassignTurretRotation();
}


// Called every frame
void URingAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FRotator const rotate = UKismetMathLibrary::RotatorFromAxisAndAngle(FVector(0.0, 0.0, 1.0), GetEffectiveSpeed() * DeltaTime * 360.0F);
	this->AddLocalRotation(rotate);
}

void URingAbility::ActivateAbility_Implementation()
{
	for (int i = 0; i < this->GetNumChildrenComponents(); ++i)
	{
		USceneComponent *const child = this->GetChildComponent(i);
		for (int j = 0; j < child->GetNumChildrenComponents(); ++j)
		{
			auto *const child_actor = child->GetChildComponent(j);
			if (child_actor)
			{
				if (ARingTurret *const turret = child_actor->GetOwner<ARingTurret>(); turret != nullptr)
				{
					turret->Fire(GetEffectiveSpeed(), GetEffectiveArea(), GetEffectiveDamage(), GetEffectiveKnockback(), GetEffectiveDuration(), GetEffectivePenetration(), Bounces);
				}
			}
		}
	}
}

void URingAbility::CreateTurrets(int TurretCount)
{
	for (int i = 0; i < TurretCount; ++i)
	{
		// Create a turret fixture
		USpringArmComponent *const TurretBoom = NewObject<USpringArmComponent>(this, *FString::Printf(TEXT("TurretBoom %i"), this->GetNumChildrenComponents()));
		if (TurretBoom != nullptr)
		{
			TurretBoom->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
			TurretBoom->bDoCollisionTest = true; // This arm should just stay as far away as it is
			TurretBoom->TargetArmLength = 200.0f; // This is a random default value that looked okay in testing.
			TurretBoom->RegisterComponent();
		}

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FRotator rotation(90, 0.0, 0.0);

		ARingTurret *ChildTurret = GetWorld()->SpawnActor<ARingTurret>(BPRingTurret, FVector::ZeroVector, rotation, SpawnParams);
		if (ChildTurret)
		{

			// Create a boom for the turret
			if (TurretBoom)
			{
				FAttachmentTransformRules transformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::SnapToTarget, false);
				ChildTurret->AttachToComponent(TurretBoom, transformRules, USpringArmComponent::SocketName);
			}
			else
			{
				ChildTurret->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
			}
		}
	}
}

void URingAbility::ReassignTurretRotation()
{
	float const child_count = static_cast<float>(this->GetNumChildrenComponents());
	float const arm_length = 100.0F + 50.0F * child_count;

	for (int i = 0; i < this->GetNumChildrenComponents(); ++i)
	{
		if (USpringArmComponent *const arm = dynamic_cast<USpringArmComponent *>(this->GetChildComponent(i)); arm != nullptr)
		{
			FRotator const rotate = UKismetMathLibrary::RotatorFromAxisAndAngle(FVector(0.0, 0.0, 1.0), (static_cast<float>(i) / child_count) * 360.0F);
			arm->TargetArmLength = arm_length;
			arm->SetRelativeRotation(rotate, false, nullptr, ETeleportType::TeleportPhysics);
		}
	}
}

