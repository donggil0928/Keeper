// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/KeeperCharacterHUD.h"

#include "KeeperCharacter.h"
#include "RoundProgressBar.h"
#include "Skill/SkillDataStruct.h"
#include "Skill/SkillComponent.h"
#include "Skill/SkillUI/SkillSlot.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "components/ProgressBar.h"
#include "Skill/SkillUI/CooldownRound.h"

void UKeeperCharacterHUD::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	AKeeperCharacter* Player = Cast<AKeeperCharacter>(GetOwningPlayerPawn());
	USkillComponent* PlayerSkillComponent = Player->SkillComponent;

	Player->OnStatChanged.BindUObject(this, &UKeeperCharacterHUD::SetupHUDStatusWidgets);
	Player->StartCooldown.BindUObject(this, &UKeeperCharacterHUD::StartCooldownRoundAnim);
	PlayerSkillComponent->OnSkillChanged.BindUObject(this, &UKeeperCharacterHUD::SetupHUDSkillSlotWidget);
	
	SetupHUDStatusWidgets();
	SetupHUDSkillSlotWidget();
}

void UKeeperCharacterHUD::SetupHUDStatusWidgets()
{
	AKeeperCharacter* Player = Cast<AKeeperCharacter>(GetOwningPlayerPawn());

	HUD_HP->SetText(FText::FromString(FString::FromInt(int32((float(Player->CurrentHP) / Player->MaxHP) * 100))));
	HUD_HPBar->SetPercentForRound(float(Player->CurrentHP) / Player->MaxHP);
	HUD_Cost->SetPercent(float(Player->CurrentMadness) / Player->MaxMadness);
	HUD_Exp->SetPercent(0);
	HUD_Level->SetText(FText::FromString(FString::FromInt(int32(Player->Level))));
}

void UKeeperCharacterHUD::SetupHUDSkillSlotWidget()
{
	AKeeperCharacter* Player = Cast<AKeeperCharacter>(GetOwningPlayerPawn());
	USkillComponent* PlayerSkillComponent = Player->SkillComponent;

	HUD_Q->Slot_Icon->SetBrushFromTexture(PlayerSkillComponent->Skills[ESkillKeyMapping::Q].SkillIcon);
	HUD_W->SetSkillData(PlayerSkillComponent->Skills[ESkillKeyMapping::W]);
	HUD_W->Slot_Icon->SetBrushFromTexture(HUD_W->GetSkillData().SkillIcon);
	HUD_E->SetSkillData(PlayerSkillComponent->Skills[ESkillKeyMapping::E]);
	HUD_E->Slot_Icon->SetBrushFromTexture(HUD_E->GetSkillData().SkillIcon);
	HUD_R->SetSkillData(PlayerSkillComponent->Skills[ESkillKeyMapping::R]);
	HUD_R->Slot_Icon->SetBrushFromTexture(HUD_R->GetSkillData().SkillIcon);
}

void UKeeperCharacterHUD::StartCooldownRoundAnim(ESkillKeyMapping InKey)
{
	AKeeperCharacter* Player = Cast<AKeeperCharacter>(GetOwningPlayerPawn());
	USkillComponent* PlayerSkillComponent = Player->SkillComponent;
	
	switch (InKey)
	{
	case ESkillKeyMapping::Q :
		HUD_Q_Cooldown->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		HUD_Q_Cooldown->SetCooldownRoundPercent(PlayerSkillComponent->Skills[InKey].SecondToCooldown);
		break;
	case ESkillKeyMapping::W :
		HUD_W_Cooldown->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		HUD_W_Cooldown->SetCooldownRoundPercent(PlayerSkillComponent->Skills[InKey].SecondToCooldown);
		break;
	case ESkillKeyMapping::E :
		HUD_E_Cooldown->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		HUD_E_Cooldown->SetCooldownRoundPercent(PlayerSkillComponent->Skills[InKey].SecondToCooldown);
		break;
	case ESkillKeyMapping::R :
		HUD_R_Cooldown->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		HUD_R_Cooldown->SetCooldownRoundPercent(PlayerSkillComponent->Skills[InKey].SecondToCooldown);
		break;
	}
}
