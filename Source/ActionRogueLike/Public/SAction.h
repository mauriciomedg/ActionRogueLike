// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "SAction.generated.h"

class USActionComponent;
/**
 * 
 */
UCLASS(Blueprintable) // Without it we cannot have child classes from USAction, that will show up in the class wizard
class ACTIONROGUELIKE_API USAction : public UObject
{
	GENERATED_BODY()

protected:

	UPROPERTY(Replicated)
	USActionComponent* ActionComp;

	UFUNCTION(BlueprintCallable, Category = "Action")
	USActionComponent* GetOwningComponent() const;

	/* Tags added to owinig actor when activated, removed when action stops*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	FGameplayTagContainer GrantTags;

	/* Action can only start if OwningActor has none of these Tags applied*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	FGameplayTagContainer BlockedTags;

	UPROPERTY(ReplicatedUsing = "OnRep_IsRunning")
	bool bIsRunning = false;

	UFUNCTION()
	void OnRep_IsRunning();

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty>& OutLifetimeProps) const override;

public:

	void Initialize(USActionComponent* NewActionComp);
	 
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	bool bAutoStart;

	UFUNCTION(BlueprintCallable, Category = "Action")
	bool IsRunning() const;

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	bool CanStart(AActor* Instigator);

	//BlueprintNativeEvent can be implement in c++ and blueprint can override the behavior and extended
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StartAction(AActor* Instigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Action")
	void StopAction(AActor* Instigator);
	
	/* Action nickname to start/stop without a reference to the object */
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName ActionName;

	UWorld* GetWorld() const override;

	bool IsSupportedForNetworking() const override
	{
		return true;
	}
};
