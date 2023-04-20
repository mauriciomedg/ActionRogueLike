// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"
#include "SCharacter.h"

void ASPlayerState::GrantCredits(float Credit)
{
	SetScore(GetScore() + Credit);
	OnCreditChange.Broadcast(GetScore(), true);
}

bool ASPlayerState::CostCredits(float Cost)
{
	if (GetScore() > Cost)
	{
		SetScore(GetScore() - Cost);
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