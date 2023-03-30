// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "SAttributeComponent.h"

// Sets default values
ASAICharacter::ASAICharacter()
{
 	PawSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");
	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
}

void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawSensingComp->OnSeePawn.AddDynamic(this, &ASAICharacter::OnPawnSeen);
	
	AttributeComp->OnHealthChange.AddDynamic(this, &ASAICharacter::OnHealthChanged);

	Health = AttributeComp->GetHealth();
}

float ASAICharacter::GetHealth()
{
	if (AttributeComp)
	{
		return AttributeComp->GetHealth();
	}

	return 100.0f;
}

void ASAICharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwingComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f)
	{
		Health = NewHealth;

		AAIController* AIC = Cast<AAIController>(GetController());

		if (AIC)
		{
			UBlackboardComponent* BBC = AIC->GetBlackboardComponent();
			BBC->SetValueAsFloat("Health", NewHealth);
		}
	}
}

void ASAICharacter::OnPawnSeen(APawn* Pawn)
{
	AAIController* AIC = Cast<AAIController>(GetController());

	if (AIC)
	{
		UBlackboardComponent* BBC = AIC->GetBlackboardComponent();

		BBC->SetValueAsObject("TargetActor", Pawn);

		DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER_SPOTTED", nullptr, FColor::White, 4.0f, true);
	}
}

void ASAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

