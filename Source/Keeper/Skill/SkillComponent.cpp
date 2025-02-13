// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillComponent.h"
#include "Character/KeeperCharacter.h"
//#include "SkillProjectile.h"

#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
USkillComponent::USkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Skills.Add(ESkillKeyMapping::Q);
	Skills.Add(ESkillKeyMapping::W);
	Skills.Add(ESkillKeyMapping::E);
	Skills.Add(ESkillKeyMapping::R);

	FString SkillDataTablePath = TEXT("/Script/Engine.DataTable'/Game/Blueprints/TempSkill/SkillDataTable.SkillDataTable'");
	static ConstructorHelpers::FObjectFinder<UDataTable> SkillDataTableRef(*SkillDataTablePath);
	if (SkillDataTableRef.Succeeded())
	{
		SkillDataTable = SkillDataTableRef.Object;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> SkillWindowWidgetRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Skill/WB_SkillWindow.WB_SkillWindow_C'"));
	if (SkillWindowWidgetRef.Succeeded())
	{
		SkillWindowWidget = SkillWindowWidgetRef.Class;
	}

	SkillLevelArray.Init(0, 20);
}

FSkillDataStruct USkillComponent::GetSkillDataRow(int32 index)
{
	return *(SkillDataTable->FindRow<FSkillDataStruct>(FName(*(FString::FromInt(index))), FString("")));
}

int32 USkillComponent::GetSkillDataIndexToCurrentLevel(ESkillKeyMapping key, ESkillSetType skillSet, int32 currentSkillLevel)
{
	int32 ClampSkillLevel = FMath::Clamp<int32>(currentSkillLevel, 0, 5);
	return int32((int32(skillSet) * 20) + (int32(key) * 5) + ClampSkillLevel);
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