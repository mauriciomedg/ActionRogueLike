// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SItem.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASItem();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual bool PickUp(APawn* InstigatorPawn, bool IsCredit);

	UPROPERTY(VisibleAnywhere, Category = "Credit")
	float Credit = 0.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
