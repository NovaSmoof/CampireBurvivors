// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Map.h"
#include "UObject/UnrealType.h"
#include "BaseAbility.generated.h"

UENUM(BlueprintType)
enum class AbilityType : uint8
{
	Damage UMETA(DisplayName = "Damage"),
	Speed UMETA(DisplayName = "Speed"),
	Duration UMETA(DisplayName = "Duration"),
	Cooldown UMETA(DisplayName = "Cooldown"),
	Area UMETA(DisplayName = "Area"),
	Knockback UMETA(DisplayName = "Knockback"),
	Amount UMETA(DisplayName = "Amount"),
	Penetration UMETA(DisplayName = "Penetration"),
};

UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup = (Ability), meta = (BlueprintSpawnableComponent))
class CAMPIREBURVIVORS_API UBaseAbility : public USceneComponent
{
	GENERATED_BODY()

private:

	class ACampireBurvivorsCharacter const * GetMyPlayer() const;

protected:

	// The time into the cooldown the ability is
	float Timer = 0.0F;

	// The speed at which the ability moves
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability, meta = (AllowPrivateAccess = "true"))
	float Speed = 0.0F;

	// The base damage of the ability
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability, meta = (AllowPrivateAccess = "true"))
	float BaseDamage = 0.0F;

	// The duration the ability lasts
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability, meta = (AllowPrivateAccess = "true"))
	float Duration = 0.0F;

	// The cooldown for the ability
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability, meta = (AllowPrivateAccess = "true"))
	float Cooldown = 0.0F;

	// The size of the abilities effects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability, meta = (AllowPrivateAccess = "true"))
	float Area = 0.0F;

	// The magnitude of the knockback vector
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability, meta = (AllowPrivateAccess = "true"))
	float Knockback = 0.0F;

	// The amount of projectiles this Ability manages
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability, meta = (AllowPrivateAccess = "true"))
	int Amount = 0;

	// The amount of enemies that can be penetrated by this ability
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability, meta = (AllowPrivateAccess = "true"))
	int Penetration = 0;

	static TMap<FString, FProperty *> AbilityValues;
	static TMap<AbilityType, FString> EnumToString;

public:	
	// Sets default values for this actor's properties
	UBaseAbility();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// The function that causes the ability to do something when it gets off cooldown
	UFUNCTION(BlueprintNativeEvent)
	void ActivateAbility();

	virtual void ActivateAbility_Implementation();

public:

	UFUNCTION(BlueprintCallable)
	float GetStat(AbilityType type);

	UFUNCTION(BlueprintCallable)
	void SetStat(AbilityType type, float value);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	float GetEffectiveSpeed() const;
	UFUNCTION(BlueprintCallable)
	float GetTrueSpeed() const;

	UFUNCTION(BlueprintCallable)
	float GetEffectiveDamage() const;
	UFUNCTION(BlueprintCallable)
	float GetTrueDamage() const;

	UFUNCTION(BlueprintCallable)
	float GetEffectiveDuration() const;
	UFUNCTION(BlueprintCallable)
	float GetTrueDuration() const;

	UFUNCTION(BlueprintCallable)
	float GetEffectiveCooldown() const;
	UFUNCTION(BlueprintCallable)
	float GetTrueCooldown() const;

	UFUNCTION(BlueprintCallable)
	float GetEffectiveArea() const;
	UFUNCTION(BlueprintCallable)
	float GetTrueArea() const;

	UFUNCTION(BlueprintCallable)
	float GetEffectiveKnockback() const;
	UFUNCTION(BlueprintCallable)
	float GetTrueKnockback() const;

	UFUNCTION(BlueprintCallable)
	int GetEffectiveAmount() const;
	UFUNCTION(BlueprintCallable)
	int GetTrueAmount() const;

	UFUNCTION(BlueprintCallable)
	int GetEffectivePenetration() const;
	UFUNCTION(BlueprintCallable)
	int GetTruePenetration() const;

};
