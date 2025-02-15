// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RoundProgressBar.h"

void URoundProgressBar::SetPercentForRound(float InPercent)
{
	PercentForRound = InPercent;
	SetPercentForRoundImplement();
}
