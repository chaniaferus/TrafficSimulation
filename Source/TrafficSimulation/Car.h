// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Car.generated.h"

UCLASS()
class TRAFFICSIMULATION_API ACar : public AActor
{
	GENERATED_BODY()
	
public:	
	ACar();
	void Move(ACar* front_car, float delta_time);
	void SetDefaultVelocity(float velocity);
	void SetAccelerationRate(float acceleration_rate);
	void SetDirection(FVector direction);

	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* mesh_;

protected:
	void UpdateVelocity(float acceleration, float delta_time);

	float default_velocity_;
	float current_velocity_ = 0;
	FVector direction_;
	float acceleration_rate_;
	float deceleration_rate_ = 300;
	static constexpr float max_deceleration_rate_ = 1000;

};
