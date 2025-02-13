// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillUI/SkillSlot.h"

#include "Components/Button.h"
#include "Components/Image.h"

void USkillSlot::SetupSlotData(int32 InIndexAddedSkillLevel, ESkillKeyMapping InKey)
{
	SetCurrentSkillLevel(SkillData.CurrentLevel);
	SetDefaultIndex(InIndexAddedSkillLevel - GetCurrentSkillLevel());
	SetSkillOnKey(InKey);
	Slot_Icon->SetBrushFromTexture(SkillData.SkillIcon);
}

void USkillSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}
