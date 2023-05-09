// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCreditChanged, int32, NewCredit, bool, bGrant);

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	
	UFUNCTION()
	void GrantCredits(int32 Credit);

	UFUNCTION()
	bool CostCredits(int32 Cost);

	UPROPERTY(BlueprintAssignable)
	FOnCreditChanged OnCreditChange;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static ASPlayerState* GetSPlayerState(AActor* Player);
};
