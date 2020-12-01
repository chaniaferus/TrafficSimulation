// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/KismetMathLibrary.h"
#include "TrafficHandler.h"

// Sets default values
ATrafficHandler::ATrafficHandler()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATrafficHandler::BeginPlay()
{
	Super::BeginPlay();
	traffic_direction_ = UKismetMathLibrary::GetDirectionUnitVector(start_position_->GetActorLocation(), end_position_->GetActorLocation());
}

bool ATrafficHandler::CanSpawnCar() {
	return cars_.empty() || ((FApp::GetCurrentTime() >= next_spawn_time_) && (cars_.back()->GetDistanceTo(start_position_) >= minimum_spawn_distance_));
}

void ATrafficHandler::HandleTraffic(float delta_time) {
	for (unsigned i = 0; i < cars_.size(); i++) {
		if (i != 0) {
			cars_[i]->Move(cars_[i - 1], delta_time);
		}
		else {
			cars_[i]->Move(nullptr, delta_time);
		}
		if (cars_[i]->GetActorLocation().Y >= end_position_->GetActorLocation().Y) {  
			cars_[i]->Destroy();
			cars_.erase(cars_.begin() + i);
		}
	}
}

void ATrafficHandler::SetCarInitialValues(ACar* car) {
	float default_velocity = FMath::FRandRange(minimum_velocity_, maximum_velocity_);
	float acceleration_rate = FMath::FRandRange(minimum_acceleration_rate_, maximum_acceleration_rate_);
	car->SetDefaultVelocity(default_velocity);
	car->SetAccelerationRate(acceleration_rate);
	car->SetDirection(traffic_direction_);
}

void ATrafficHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CanSpawnCar()) {
		SpawnCar();
	}
	HandleTraffic(DeltaTime);
}

void ATrafficHandler::SpawnCar() {
	FRotator rot = { 0, 0, 0 };
	auto spawned_car = GetWorld()->SpawnActor<ACar>(start_position_->GetActorLocation(), rot);
	SetCarInitialValues(spawned_car);
	cars_.push_back(spawned_car);
	last_spawn_time_ = FApp::GetCurrentTime();
	next_spawn_time_ = last_spawn_time_ + (FMath::FRandRange(0.0, 10.0));
}

