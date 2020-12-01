// Fill out your copyright notice in the Description page of Project Settings.


#include "Car.h"

// Sets default values
ACar::ACar()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> cube_mesh(TEXT("StaticMesh'/Game/CubeMesh'"));
	mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeVisualComponent"));
	mesh_->SetStaticMesh(cube_mesh.Object);
}

void ACar::SetDefaultVelocity(float velocity) {
	default_velocity_ = velocity;
	deceleration_rate_ = default_velocity_ / 5;
}

void ACar::SetAccelerationRate(float acceleration_rate) {
	acceleration_rate_ = acceleration_rate;
}

void ACar::SetDirection(FVector direction) {
	direction_ = direction;
}

void ACar::Move(ACar* front_car, float delta_time) {
	if (front_car) {
		float distance_to_front_car = GetDistanceTo(front_car) - GetDistanceTo(this);
		float safe_distance = current_velocity_;
		float time_to_stop_car = current_velocity_ / deceleration_rate_;			// dt = dV / a
		float braking_distance = 0.5 * deceleration_rate_ * time_to_stop_car * time_to_stop_car;			// s = 1/2 * a * t^2
		float braking_urgency = braking_distance / (distance_to_front_car - safe_distance);

		if (braking_urgency >= 1.0) {
			UpdateVelocity(braking_urgency * deceleration_rate_ * -1, delta_time);
		}
		else if (braking_urgency <= 0.9) {
			UpdateVelocity(acceleration_rate_, delta_time);
		}
	}
	else {
		UpdateVelocity(acceleration_rate_, delta_time);
	}

	auto current_position = GetActorLocation();
	SetActorLocation(current_position + direction_ * current_velocity_ * delta_time);
}

void ACar::UpdateVelocity(float acceleration, float delta_time) {
	current_velocity_ += acceleration * delta_time;
	current_velocity_ = FMath::Clamp(current_velocity_, 0.0f, default_velocity_);
	deceleration_rate_ = current_velocity_;
	deceleration_rate_ = FMath::Clamp(deceleration_rate_, 0.0f, max_deceleration_rate_);
}

