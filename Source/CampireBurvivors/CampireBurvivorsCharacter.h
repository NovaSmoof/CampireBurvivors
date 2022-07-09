
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RingAbility.h"
#include "CampireBurvivorsCharacter.generated.h"

UCLASS(config=Game)
class ACampireBurvivorsCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true", ClampMin="0"))
	float DamageScale = 1.0F;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true", ClampMin="0"))
	float SpeedMultiplier = 1.0F;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true", ClampMin="0"))
	float DurationMultiplier = 1.0F;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true", ClampMin="-1", ClampMax="1"))
	float CooldownRate = 0.0F;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true", ClampMin="0"))
	float AreaScale = 1.0F;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true", ClampMin="0"))
	float KnockbackScale = 1.0F;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true", ClampMin="0"))
	int PenetrationExtra = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true", ClampMin="0"))
	int AmountExtra = 0;

public:
	ACampireBurvivorsCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }


	FORCEINLINE float GetSpeedMultiplier() const { return SpeedMultiplier; };
	FORCEINLINE float GetDamageScale() const { return DamageScale; }
	FORCEINLINE float GetDurationMultiplier() const { return DurationMultiplier; }
	FORCEINLINE float GetCooldownRate() const { return CooldownRate; }
	FORCEINLINE float GetAreaScale() const { return AreaScale; }
	FORCEINLINE float GetKnockbackScale() const { return KnockbackScale; }
	FORCEINLINE int GetExtraAmount() const { return AmountExtra; }
	FORCEINLINE int GetExtraPenetration() const { return PenetrationExtra; }
};

