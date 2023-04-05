// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "SAttributeComponent.h"

// Sets default values
ASAICharacter::ASAICharacter()
{
 	PawSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
}

void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawSensingComp->OnSeePawn.AddDynamic(this, &ASAICharacter::OnPawnSeen);
	
	AttributeComp->OnHealthChange.AddDynamic(this, &ASAICharacter::OnHealthChanged);

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
		AAIController* AIC = Cast<AAIController>(GetController());

		if (!AIC)
		{
			return;
		}

		if (InstigatorActor) // we dont check if there is the player or the bot that takes damages
		{
			SetTargetActor(InstigatorActor);
		}

		if (NewHealth > 0)
		{
			UBlackboardComponent* BBC = AIC->GetBlackboardComponent();
			BBC->SetValueAsFloat("Health", NewHealth);
		}
		else
		{
			// bot dead //
			// stop BT
			AIC->GetBrainComponent()->StopLogic("Killed");

			// Ragdoll
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");

			// set lifespan. This gives time to play ragdoll before desapear 
			SetLifeSpan(10.0f); 
		}
	}
}

void ASAICharacter::SetTargetActor(AActor* NewTarget)
{
	AAIController* AIC = Cast<AAIController>(GetController());

	if (AIC)
	{
		AIC->GetBlackboardComponent()->SetValueAsObject("TargetActor", NewTarget);
	}
}

void ASAICharacter::OnPawnSeen(APawn* Pawn)
{
	SetTargetActor(Pawn);
	DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER_SPOTTED", nullptr, FColor::White, 4.0f, true);
}

void ASAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

