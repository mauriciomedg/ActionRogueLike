// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	Health = HealthMax;
}

float USAttributeComponent::GetMaxHealth() const
{
	return HealthMax;
}

float USAttributeComponent::GetHealth() const
{
	return Health;
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	float CurrentHealt = Health;

	Health += Delta;

	Health = FMath::Min(FMath::Max(Health, 0.0f), HealthMax);

	OnHealthChange.Broadcast(InstigatorActor, this, Health, Delta);

	return Health != CurrentHealt;
}

