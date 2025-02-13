// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillUI/SkillWindowWidget.h"
#include "Character/KeeperCharacter.h"
#include "Skill/SkillComponent.h"
#include "Skill/SkillDataStruct.h"
#include "Skill/SkillUI/SkillSlot.h"

#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void USkillWindowWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	CurrentQ->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::ToggleQPanel);

	CharacterSkillComponent = (Cast<AKeeperCharacter>(GetOwningPlayerPawn()))->SkillComponent;
	
	//skillComponent에 있는 SkillDataTable의 정보를 이용하여 스킬창에서 기본적으로 표시되는 고정 정보들을 여기서 한번에 초기화
	//최초 스킬 할당 시 기본 스킬을 장착한 것으로 표시

	FSkillDataStruct TempStruct;
	int32 SkillIndex = CharacterSkillComponent->GetSkillDataIndexToCurrentLevel(
		ESkillKeyMapping::Q,
		ESkillSetType::Defalut,
		0);
	TempStruct = CharacterSkillComponent->GetSkillDataRow(SkillIndex);

	Q_Default->SetSkillData(TempStruct);
	Q_Default->InitSlotData();

	SkillIndex = CharacterSkillComponent->GetSkillDataIndexToCurrentLevel(
		ESkillKeyMapping::Q,
		ESkillSetType::Beast,
		0);
	TempStruct = CharacterSkillComponent->GetSkillDataRow(SkillIndex);

	Q_Beast->SetSkillData(TempStruct);
	Q_Beast->InitSlotData();
}

void USkillWindowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FSkillDataStruct TempStruct;

	//현재 SkillComponent에 저장된 각 스킬의 정보에서 GetSkillDataIndexToCurrentLevel를 이용해 인덱스를 얻는다.
	//그리고 그 인덱스로 GetSkillDataRow를 얻어서 스킬창 활성화 시 장착된 스킬 정보가 스킬창에 표시될 수 있게 한다.
	int32 CurrentSkillIndex = CharacterSkillComponent->GetSkillDataIndexToCurrentLevel(
		ESkillKeyMapping::Q,
		CharacterSkillComponent->Skills[ESkillKeyMapping::Q].SkillSet,
		CharacterSkillComponent->Skills[ESkillKeyMapping::Q].CurrentLevel);
	TempStruct = CharacterSkillComponent->GetSkillDataRow(CurrentSkillIndex);

	CurrentQ->SetSkillData(TempStruct);
	CurrentQ->InitSlotData();
	QName->SetText(CurrentQ->GetSkillData().Name);
	QDesc->SetText(CurrentQ->GetSkillData().Description);
	QCost->SetText(FText::FromString(FString::FromInt(CurrentQ->GetSkillData().Cost)));
	QCool->SetText(FText::FromString(FString::FromInt(CurrentQ->GetSkillData().SecondToCooldown)));
}

void USkillWindowWidget::TestButtonInteract()
{
	UE_LOG(LogTemp, Log, TEXT("Click!"));
}

