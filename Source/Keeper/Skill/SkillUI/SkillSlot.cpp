// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillUI/SkillSlot.h"

#include "Components/Button.h"
#include "Components/Image.h"

void USkillSlot::InitSlotData()
{
	Slot_Icon->SetBrushFromTexture(SkillData.SkillIcon);
}

void USkillSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//Slot_Button->OnClicked.AddDynamic(this, &USkillSlot::InitSlotData);
}
