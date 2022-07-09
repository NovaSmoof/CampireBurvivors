// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAbility.h"

#include "CampireBurvivorsCharacter.h"
TMap<FString, FProperty *> UBaseAbility::AbilityValues;
TMap<AbilityType, FString> UBaseAbility::EnumToString
{
	{AbilityType::Damage, TEXT("BaseDamage")},
	{AbilityType::Speed, TEXT("Speed")},
	{AbilityType::Duration, TEXT("Duration")},
	{AbilityType::Cooldown, TEXT("Cooldown")},
	{AbilityType::Area, TEXT("Area")},
	{AbilityType::Knockback, TEXT("Knockback")},
	{AbilityType::Amount, TEXT("Amount")},
	{AbilityType::Penetration, TEXT("Penetration")},
};

ACampireBurvivorsCharacter const *UBaseAbility::GetMyPlayer() const
{
	return this->GetOwner<ACampireBurvivorsCharacter>();
}

// Sets default values
UBaseAbility::UBaseAbility()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;

	for (TFieldIterator<FProperty> it(UBaseAbility::StaticClass()); it; ++it)
	{
		FProperty *prop = *it;
		// if(prop->GetMetaData(TEXT("Category")) == TEXT("Ability"))
		if (auto *owner_class = prop->GetOwnerClass(); owner_class && owner_class->IsChildOf<UBaseAbility>())
		{
			if (prop->GetName() != TEXT("Timer"))
			{
				AbilityValues.Add(prop->GetName(), prop);
			}
		}
		// check for the category here
	}
}

float UBaseAbility::GetStat(AbilityType type)
{
	FProperty *prop = *AbilityValues.Find(*EnumToString.Find(type));
	if (FString(TEXT("float")) == prop->GetCPPType())
	{
		float * const value = prop->ContainerPtrToValuePtr<float>(static_cast<UObject*>(this), 0);
		if (value != nullptr)
		{
			return *value;
		}
	}
	else
	{
		int *const value = prop->ContainerPtrToValuePtr<int>(static_cast<UObject *>(this), 0);
		if (value != nullptr)
		{
			return *value;
		}
	}
	return 0.0f;
}

void UBaseAbility::SetStat(AbilityType type, float value)
{
	FProperty *prop = *AbilityValues.Find(*EnumToString.Find(type));
	if (FString(TEXT("float")) == prop->GetCPPType())
	{
		float *const value_ptr = prop->ContainerPtrToValuePtr<float>(static_cast<UObject *>(this), 0);
		if (value_ptr != nullptr)
		{
			*value_ptr = value;
		}
	}
	else
	{
		int *const value_ptr = prop->ContainerPtrToValuePtr<int>(static_cast<UObject *>(this), 0);
		if (value_ptr != nullptr)
		{
			*value_ptr = static_cast<int>(value);
		}
	}
}

// Called when the game starts or when spawned
void UBaseAbility::BeginPlay()
{
	Super::BeginPlay();
}

void UBaseAbility::ActivateAbility_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("This should not happen."));
}

// Called every frame
void UBaseAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Timer += DeltaTime * (1.0F + GetMyPlayer()->GetCooldownRate());
	if (Timer >= Cooldown)
	{
		Timer -= Cooldown;
		ActivateAbility();
	}
}

float UBaseAbility::GetEffectiveSpeed() const
{
	return GetTrueSpeed() * GetMyPlayer()->GetSpeedMultiplier();
}

float UBaseAbility::GetTrueSpeed() const
{
	return Speed;
}

float UBaseAbility::GetEffectiveDamage() const
{
	return GetTrueDamage() * GetMyPlayer()->GetDamageScale();
}

float UBaseAbility::GetTrueDamage() const
{
	return BaseDamage;
}

float UBaseAbility::GetEffectiveDuration() const
{
	return GetTrueDuration() * GetMyPlayer()->GetDurationMultiplier();
}

float UBaseAbility::GetTrueDuration() const
{
	return Duration;
}

float UBaseAbility::GetEffectiveCooldown() const
{
	return GetTrueCooldown() * (1.0F - GetMyPlayer()->GetCooldownRate());
}

float UBaseAbility::GetTrueCooldown() const
{
	return Cooldown;
}

float UBaseAbility::GetEffectiveArea() const
{
	return GetTrueArea() * GetMyPlayer()->GetAreaScale();
}

float UBaseAbility::GetTrueArea() const
{
	return Area;
}

float UBaseAbility::GetEffectiveKnockback() const
{
	return GetTrueKnockback() * GetMyPlayer()->GetKnockbackScale();
}

float UBaseAbility::GetTrueKnockback() const
{
	return Knockback;
}

int UBaseAbility::GetEffectiveAmount() const
{
	return GetTrueAmount() + GetMyPlayer()->GetExtraAmount();
}

int UBaseAbility::GetTrueAmount() const
{
	return Amount;
}

int UBaseAbility::GetEffectivePenetration() const
{
	return GetTruePenetration() + GetMyPlayer()->GetExtraPenetration();
}

int UBaseAbility::GetTruePenetration() const
{
	return Penetration;
}

