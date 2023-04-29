// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction.h"
#include "SActionComponent.h"

bool USAction::CanStart_Implementation(AActor* Instigator)
{
	if (IsRunning())
	{
		return false;
	}

	USActionComponent* Comp = GetOwningComponent();

	if (Comp->ActiveGameplayTags.HasAny(BlockedTags))
	{
		FString FailedMsg = FString::Printf(TEXT("Failed to run: %s"), *ActionName.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FailedMsg);

		return false;
	}

	return true;
}

void USAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Running: %s"), *GetNameSafe(this));
	
	USActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.AppendTags(GrantTags);

	bIsRunning = true;
}

void USAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Stopped: %s"), *GetNameSafe(this));

	ensureAlways(bIsRunning);

	USActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.RemoveTags(GrantTags);

	bIsRunning = false;
}

UWorld* USAction::GetWorld() const
{
	//It was passed when doing thr NewObject<T>(outer, class)

	UActorComponent* Comp = Cast<UActorComponent>(GetOuter());

	if (Comp)
	{
		return Comp->GetWorld();
	}

	return nullptr;
}

USActionComponent* USAction::GetOwningComponent() const
{
	return Cast<USActionComponent>(GetOuter());
}

bool USAction::IsRunning() const
{
	return bIsRunning;
}