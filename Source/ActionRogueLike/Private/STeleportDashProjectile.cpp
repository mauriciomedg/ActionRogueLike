// Fill out your copyright notice in the Description page of Project Settings.


#include "STeleportDashProjectile.h"

// Sets default values
ASTeleportDashProjectile::ASTeleportDashProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASTeleportDashProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_Teleport, this, &ASTeleportDashProjectile::TeleportInstigator_TimeEnlapsed, 2);
}

void ASTeleportDashProjectile::TeleportInstigator_TimeEnlapsed()
{
	FVector pos = GetActorLocation();
	FRotator rot = GetActorRotation();

	GetInstigator()->TeleportTo(pos, rot);
	GetWorldTimerManager().ClearTimer(TimerHandle_Teleport);

	Destroy();
}

// Called every frame
void ASTeleportDashProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

