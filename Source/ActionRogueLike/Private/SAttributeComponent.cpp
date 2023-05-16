// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

#include "SGameModeBase.h"

// su. its to make the own category of console variables
// ECVF_Cheat means that it is not include in the final build
static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("su.DamageMultiplier"), 1.0f, TEXT("Global Damage Modifier for Attribute Component"), ECVF_Cheat);

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	Health = HealthMax;
}

bool USAttributeComponent::Kill(AActor* InstigatorActor)
{
	return ApplyHealthChange(InstigatorActor, -GetMaxHealth());
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
	if (!GetOwner()->CanBeDamaged() && Delta < 0.0f) // can be damage could be set in the console as God
	{
		return false;
	}

	if (Delta < 0.0f)
	{
		float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();

		Delta *= DamageMultiplier;
	}

	float OldHealth = Health;

	Health = FMath::Clamp(Health + Delta, 0.0f, HealthMax);

	float ActualDelta = Health - OldHealth;

	if (ActualDelta < 0.0f)
	{
		Rage = FMath::Clamp(Health - ActualDelta, 0.0f, RageMax);
	}

	OnHealthChange.Broadcast(InstigatorActor, this, Health, ActualDelta);

	// Dead
	if (ActualDelta < 0.0f && Health == 0.0f)
	{
		// Auth Authority, GameMode only exist in the sever.
		ASGameModeBase* GM = GetWorld()->GetAuthGameMode<ASGameModeBase>();

		if (GM)
		{
			GM->OnActorKilled(GetOwner(), InstigatorActor);
		}
	}

	return ActualDelta != 0.0f;
}

USAttributeComponent* USAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return FromActor->FindComponentByClass<USAttributeComponent>();
		//return Cast<USAttributeComponent>(FromActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	}

	return nullptr;
}

bool USAttributeComponent::IsActorAlive(AActor* FromActor)
{
	USAttributeComponent* AttributeComp = GetAttributes(FromActor);

	if (AttributeComp)
	{
		return AttributeComp->IsAlive();
	}

	return false;
}

