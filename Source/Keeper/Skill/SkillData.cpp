// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillData.h"
#include "Character/KeeperCharacter.h"

USkillData::USkillData()
{
	Name = FText::FromString(TEXT("Skill_Name"));
	Description = FText::FromString(TEXT("Skill_Description"));
	CurrentLevel = 1;
	Range = 1.0f;
	Cost = 1;
	SecondToCooldown = 1.0f;
	bIsCooldown = false;
}

void USkillData::Use(AKeeperCharacter* player)
{
	if (!bIsCooldown)
	{
		UE_LOG(LogTemp, Log, TEXT("%s is Activated!"), *Name.ToString());

		// 해당 부분에서 스킬 사용 시 애니메이션과 이펙트 등을 처리(예정)
		//

		//StartCooldown();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is Now Cooldown!"), *Name.ToString());
	}
}

void USkillData::StartCooldown()
{
	bIsCooldown = true;
	GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &USkillData::EndCooldown, SecondToCooldown, false); // this 호출 시 nullptr 에러 발생, CDO를 통해 함수를 호출하는 것이 문제로 보임.
}

void USkillData::EndCooldown()
{
	bIsCooldown = false;
	GetWorld()->GetTimerManager().ClearTimer(CooldownTimerHandle);
}
