// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillUI/LockedSkillSetScreen.h"
#include "Character/KeeperCharacter.h"


void ULockedSkillSetScreen::NativeConstruct()
{
	AKeeperCharacter* Player = Cast<AKeeperCharacter>(GetOwningPlayerPawn());
	if (Player)
	{
		/*
		bool bIsUnlocked = Player->UnlockedSkillInfo[LockedSkillSetByThisScreen];
		if(bIsUnlocked)
		{
			this->SetVisibility(ESlateVisibility::Hidden);
		}
		else this->SetVisibility(ESlateVisibility::Visible);
		*/
	} 
}
