// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillComponent.h"
#include "Character/KeeperCharacter.h"
//#include "SkillProjectile.h"
#include "SkillUI/SkillSlot.h"

#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
USkillComponent::USkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	FString SkillDataTablePath = TEXT("/Script/Engine.DataTable'/Game/Blueprints/TempSkill/SkillDataTable.SkillDataTable'");
	static ConstructorHelpers::FObjectFinder<UDataTable> SkillDataTableRef(*SkillDataTablePath);
	if (SkillDataTableRef.Succeeded())
	{
		SkillDataTable = SkillDataTableRef.Object;
	}
	
	Skills.Add(ESkillKeyMapping::Q,
		GetSkillDataRow(GetSkillDataIndexToCurrentLevel(ESkillKeyMapping::Q, ESkillSetType::Defalut, 0)));
	Skills.Add(ESkillKeyMapping::W,
		GetSkillDataRow(GetSkillDataIndexToCurrentLevel(ESkillKeyMapping::W, ESkillSetType::Defalut, 0)));
	Skills.Add(ESkillKeyMapping::E,
		GetSkillDataRow(GetSkillDataIndexToCurrentLevel(ESkillKeyMapping::E, ESkillSetType::Defalut, 0)));
	Skills.Add(ESkillKeyMapping::R,
		GetSkillDataRow(GetSkillDataIndexToCurrentLevel(ESkillKeyMapping::R, ESkillSetType::Defalut, 0)));

	SkillLevelArray.Init(0, 20);
}

FSkillDataStruct USkillComponent::GetSkillDataRow(int32 index)
{
	return *(SkillDataTable->FindRow<FSkillDataStruct>(FName(*(FString::FromInt(index))), FString("")));
}

int32 USkillComponent::GetSkillDataIndexToCurrentLevel(ESkillKeyMapping key, ESkillSetType skillSet, int32 currentSkillLevel)
{
	int32 ClampSkillLevel = FMath::Clamp<int32>(currentSkillLevel, 0, 5);
	return int32((int32(skillSet) * 24) + (int32(key) * 6) + ClampSkillLevel);
}

int32 USkillComponent::GetSkillLevelIndex(ESkillKeyMapping InKey, ESkillSetType SkillSet)
{
	return int32(int32(SkillSet) * 4 + int32(InKey));
}

void USkillComponent::SetupSelectedSkillData(USkillSlot* InSlot)
{
	FSkillDataStruct SelectedSkillData = GetSkillDataRow(InSlot->GetActualSkillIndex()); // 레벨이 적용된 스킬데이터.

	Skills[InSlot->GetSkillOnKey()] = SelectedSkillData;
	OnSkillChanged.Execute();
}

void USkillComponent::ModifySkillLevel(USkillSlot* InSlot, ESkillKeyMapping InKey)
{
	int32 ModifiedSkillIndex = GetSkillLevelIndex(InKey, InSlot->GetSkillData().SkillSet);
	SkillLevelArray[ModifiedSkillIndex] = InSlot->GetCurrentSkillLevel();
}

// Called when the game starts
void USkillComponent::BeginPlay()
{
	Super::BeginPlay();

	Skills[ESkillKeyMapping::Q] = GetSkillDataRow(GetSkillDataIndexToCurrentLevel(ESkillKeyMapping::Q, ESkillSetType::Defalut, 0));
	Skills[ESkillKeyMapping::W] = GetSkillDataRow(GetSkillDataIndexToCurrentLevel(ESkillKeyMapping::W, ESkillSetType::Defalut, 0));
	Skills[ESkillKeyMapping::E] = GetSkillDataRow(GetSkillDataIndexToCurrentLevel(ESkillKeyMapping::E, ESkillSetType::Defalut, 0));
	Skills[ESkillKeyMapping::R] = GetSkillDataRow(GetSkillDataIndexToCurrentLevel(ESkillKeyMapping::R, ESkillSetType::Defalut, 0));
}