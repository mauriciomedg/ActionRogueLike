// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemChest.h"
#include "Components/StaticMeshComponent.h"

ASItemChest::ASItemChest()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(BaseMesh);

	Credit = 1.0f;
}

void ASItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	PickUp(InstigatorPawn, TreasureCredit);

	//LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}
