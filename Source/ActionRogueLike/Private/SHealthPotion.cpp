// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"
#include "SAttributeComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASHealthPotion::ASHealthPotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BottleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BottleMesh"));
	RootComponent = BottleMesh;
}

void ASHealthPotion::EnableHealthPotion()
{
	BottleMesh->SetVisibility(true);
	BottleMesh->SetCollisionProfileName("BlockAllDynamic");
}

void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (InstigatorPawn)
	{
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));

		if (AttributeComp)
		{
			if (AttributeComp->ApplyHealthChange(100.0f))
			{
				if (ensure(BottleMesh))
				{
					BottleMesh->SetVisibility(false);
					BottleMesh->SetCollisionProfileName("NoCollision");
				}

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
