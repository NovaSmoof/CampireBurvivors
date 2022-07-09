// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include <set>
#include "Tiler.generated.h"

USTRUCT(BlueprintType)
struct FPoint2D
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int x = 0;

	UPROPERTY(EditAnywhere)
	int y = 0;

	int &operator[](signed int index)             { return reinterpret_cast<int *>(this)[index]; }
	int const &operator[](signed int index) const { return reinterpret_cast<int const *>(this)[index]; }
	FPoint2D operator+(FPoint2D const &other) const { return FPoint2D {this->x + other.x, this->y + other.y}; }
};

inline bool operator<(FPoint2D const &lhs, FPoint2D const &rhs) noexcept
{
	if (lhs.x < rhs.x)
	{
		return true;
	}
	if (lhs.x == rhs.x)
	{
		if (lhs.y < rhs.y)
		{
			return true;
		}
	}
	return false;
}

UCLASS()
class CAMPIREBURVIVORS_API ATiler : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (MetaClass = "World"))
	TSoftObjectPtr <UWorld> Level;
	
	UPROPERTY(EditAnywhere)
	FVector Offset;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "1"))
	int TileCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	UBoxComponent * OverlapVolume;

	std::set<FPoint2D> Locations;

	FPoint2D CurrentTile;

	int counter = 0;
	
	UFUNCTION()
	void OnOverlapBegins(UPrimitiveComponent *overlapped_component, AActor *other_actor, UPrimitiveComponent *other_comp, int32 other_body_index, bool from_sweep, const FHitResult &sweep_result);

	// declare overlap end function
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent *overlapped_component, class AActor *other_actor, class UPrimitiveComponent *other_component, int32 other_body_index);

public:	
	// Sets default values for this actor's properties
	ATiler();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};