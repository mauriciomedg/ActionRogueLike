// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USInteractionComponent;
class UAnimMontage;
class USAttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	// VisibleAnywhere = read only, still useful to view in the editor and enforce a convention.
	UPROPERTY(VisibleAnywhere, Category = "Effect")
	FName HandSocketName;
	
	UPROPERTY(EditAnywhere, Category = "Atack")
	TSubclassOf<AActor> ProjectileMagicClass;

	UPROPERTY(EditAnywhere, Category = "Atack")
	TSubclassOf<AActor> ProjectileBlackHoleClass;

	UPROPERTY(EditAnywhere, Category = "Atack")
	TSubclassOf<AActor> ProjectileTeleport;

	UPROPERTY(EditAnywhere, Category = "Atack")
	UAnimMontage* AttackAnim;

	FTimerHandle TimerHandle_PrimaryAttack;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwingComp, float NewHealth, float Delta);

	virtual void PostInitializeComponents() override;
	
public:
	// Sets default values for this character's properties
	ASCharacter();

protected:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USAttributeComponent* AttributeComp;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	// Interaction
	void PrimaryInteract();

	// Attack
	void PrimaryAttackMagicProjectile();
	void PrimaryAttackBlackHole();
	void PrimaryAttackTeleport();

	void PrimaryAttack_TimeEnlapsed(TSubclassOf<AActor> ProjectileClass);

	void PrimaryAttackMagicP_TimeEnlapsed();
	void PrimaryAttackBlackHole_TimeEnlapsed();
	void PrimaryAttackTeleport_TimeEnlapsed();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
