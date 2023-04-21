// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"
#include "SAttributeComponent.h"
#include "SGameModeBase.h"
#include "SPlayerState.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASHealthPotion::ASHealthPotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BottleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BottleMesh"));
	RootComponent = BottleMesh;

	Credit = 3.0f;
	// we can do a
	//BottleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// and add a sphere to handle the overlap.
}

void ASHealthPotion::EnableHealthPotion()
{
	//BottleMesh->SetVisibility(true);
	//BottleMesh->SetCollisionProfileName("BlockAllDynamic");
	SetActorEnableCollision(true);
	RootComponent->SetVisibility(true, true);
}

void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (InstigatorPawn)
	{
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));

		if (AttributeComp)
		{
			if (!PickUp(InstigatorPawn, false))
			{
				return;
			}
			
			if (AttributeComp->ApplyHealthChange(this, 100.0f))
			{
				ASGameModeBase* GM = GetWorld()->GetAuthGameMode<ASGameModeBase>();

				if (GM)
				{
					GM->OnHealthPotionPickUp();
				}

				SetActorEnableCollision(false);
				RootComponent->SetVisibility(false, true);
		
				FTimerHandle TimerHandel_EnableHealthPotion;
				GetWorldTimerManager().SetTimer(TimerHandel_EnableHealthPotion, this, &ASHealthPotion::EnableHealthPotion, 5);
			}
		}
	}
}

// Called when the game starts or when spawned
void ASHealthPotion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASHealthPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

