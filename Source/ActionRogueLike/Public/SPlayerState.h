// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCreditChanged, float, NewCredit, bool, bGrant);

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

	UPROPERTY(BlueprintAssignable)
	FOnCreditChanged OnCreditChange;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static ASPlayerState* GetSPlayerState(AActor* Player);
};
