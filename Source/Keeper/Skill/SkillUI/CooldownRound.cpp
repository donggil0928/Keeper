// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillUI/CooldownRound.h"

void UCooldownRound::SetCooldownRoundPercent(float InCooldownRate)
{
	CooldownRoundPercent = 1.0f;

	GetWorld()->GetTimerManager().SetTimer(
		RoundedTimerHandle,
		this,
		&UCooldownRound::SetCooldownRoundPercentImplement,
		100.0f / InCooldownRate,
		true,
		InCooldownRate);
}
