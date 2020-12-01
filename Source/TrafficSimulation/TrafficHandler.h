// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Car.h"
#include "TrafficHandler.generated.h"

UCLASS()
class TRAFFICSIMULATION_API ATrafficHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	ATrafficHandler();

	UPROPERTY(EditAnywhere)
	AActor* start_position_;

	UPROPERTY(EditAnywhere)
	AActor* end_position_;

	UPROPERTY(EditAnywhere)
	float minimum_velocity_ = 100;

	UPROPERTY(EditAnywhere)
	float maximum_velocity_ = 1000;

	UPROPERTY(EditAnywhere)
	float minimum_acceleration_rate_ = 600;

	UPROPERTY(EditAnywhere)
	float maximum_acceleration_rate_ = 800;

protected:
	virtual void BeginPlay() override;
	bool CanSpawnCar();
	void HandleTraffic(float delta_time);
	void SetCarInitialValues(ACar* car);
	void SpawnCar();

	std::vector<ACar*> cars_;
	float last_spawn_time_ = 0;
	float next_spawn_time_ = 0;
	const float minimum_spawn_distance_ = 1000;
	FVector traffic_direction_;

public:	
	virtual void Tick(float DeltaTime) override;

};
