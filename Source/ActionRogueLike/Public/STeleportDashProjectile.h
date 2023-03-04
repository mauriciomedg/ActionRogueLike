// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectileBase.h"
#include "STeleportDashProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASTeleportDashProjectile : public ASProjectileBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTeleportDashProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void TeleportInstigator_TimeEnlapsed();

protected:
	FTimerHandle TimerHandle_Teleport;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
