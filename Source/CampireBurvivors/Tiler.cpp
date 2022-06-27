// Fill out your copyright notice in the Description page of Project Settings.


#include "Tiler.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelStreamingDynamic.h"

// Sets default values
ATiler::ATiler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; 
	
	OverlapVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapVolume"));
	OverlapVolume->SetBoxExtent(FVector(100.0), true);
	RootComponent = OverlapVolume;
	OverlapVolume->OnComponentBeginOverlap.AddDynamic(this, &ATiler::OnOverlapBegins);
	OverlapVolume->OnComponentEndOverlap.AddDynamic(this, &ATiler::OnOverlapEnd);
	this->bGenerateOverlapEventsDuringLevelStreaming = true;

	CurrentTile = FPoint2D {0, 0};
	Locations.insert(CurrentTile);
}

// Called when the game starts or when spawned
void ATiler::BeginPlay()
{ 
	Super::BeginPlay();
	
}

// Called every frame
void ATiler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float sign(float value) noexcept
{
	if (isinf(value) || isnan(value) || value == 0.0F) return 0.0F;
	else if (value < 0.0F) return -1.0F;
	else return 1.0F;
}

FVector round(FVector const value) noexcept
{
	FVector output;

	for (int i = 0; i < 3; ++i)
	{
		output[i] = round(value[i]);
	}

	return output;
}

void ATiler::OnOverlapBegins(UPrimitiveComponent *overlapped_component, AActor *other_actor, UPrimitiveComponent *other_comp, int32 other_body_index, bool from_sweep, const FHitResult &sweep_result)
{
	APawn * const player_controller = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (other_actor != player_controller)
	{
		return; 
	}

	FPoint2D P;
	FVector position = this->GetActorTransform().GetLocation();

	for (P.x = -TileCount; P.x <= TileCount; ++P.x)
	{
		for (P.y = -TileCount; P.y <= TileCount; ++P.y)
		{
			FPoint2D tile = P + CurrentTile;
			if (Locations.find(tile) == Locations.end())
			{
				Locations.insert(tile);
				FVector const end_location = Offset * FVector {float(tile.x), float(tile.y), 1.0F};
				bool success;
				ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(this, Level, end_location, FRotator::ZeroRotator, success);
				// Report this as it simply doesn't work
				/*auto * const level = ULevelStreamingDynamic::LoadLevelInstance(GetWorld(), LevelToLoad.ToString(), end_location, FRotator::ZeroRotator, success);*/
			}
		}
	}
}

void ATiler::OnOverlapEnd(UPrimitiveComponent *overlapped_component, AActor *other_actor, UPrimitiveComponent *other_component, int32 other_body_index)
{
	APawn *const player_controller = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (other_actor != player_controller)
	{
		return;
	}

	FVector const my_location = this->GetActorTransform().GetLocation();
	FVector const player_location = other_actor->GetActorTransform().GetLocation();

	FVector const distance_difference = (player_location - my_location) / (Offset/2.0);

	FVector offset {0.0};

	for (int i = 0; i < 2; ++i)
	{
		float element = distance_difference[i];
		if (abs(element) > 1.0F)
		{
			offset[i] = Offset[i] * sign(element);
			CurrentTile[i] += static_cast<int>(sign(element));
		}
	}

	this->AddActorWorldOffset(offset, false, nullptr, ETeleportType::TeleportPhysics);
}

