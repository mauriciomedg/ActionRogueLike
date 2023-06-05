// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"
#include "SCharacter.h"

void ASPlayerState::GrantCredits(int32 Credit)
{
	SetScore(GetScore() + Credit);
	OnRep_Score();
}

void ASPlayerState::CostCredits(int32 Cost)
{
	SetScore(GetScore() + Cost);
	OnRep_Score();
}

void ASPlayerState::OnRep_Score()
{
	Super::OnRep_Score();

	if (GetScore() > Credits)
	{
		OnCreditChange.Broadcast(GetScore(), true);
	}
	else
	{
		OnCreditChange.Broadcast(GetScore(), false);
	}

	Credits = GetScore();
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