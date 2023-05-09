// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"
#include "SCharacter.h"

void ASPlayerState::GrantCredits(int32 Credit)
{
	SetScore(GetScore() + Credit);
	OnCreditChange.Broadcast(GetScore(), true);
}

bool ASPlayerState::CostCredits(int32 Cost)
{
	if (GetScore() + Cost > 0)
	{
		SetScore(GetScore() + Cost);
		OnCreditChange.Broadcast(GetScore(), false);

		return true;
	}

	return false;
}

ASPlayerState* ASPlayerState::GetSPlayerState(AActor* Player)
{
	ACharacter* Charact = Cast<ACharacter>(Player);

	if (Charact)
	{
		return Cast<ASPlayerState>(Charact->GetPlayerState());
	}
	
	return nullptr;
}