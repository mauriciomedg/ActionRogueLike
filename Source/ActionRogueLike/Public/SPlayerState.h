// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Cost")
	float PotionCost = 3.0f;

	UPROPERTY(EditAnywhere, Category = "Grant")
	float BotKilled = 10.0f;

	UFUNCTION()
	void GrantCredits(float Credit);

	UFUNCTION()
	bool CostCredits(float Cost);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static ASPlayerState* GetSPlayerState(AActor* Player);
};
