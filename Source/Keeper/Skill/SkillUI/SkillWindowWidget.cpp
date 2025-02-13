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
	
	//skillComponent�� �ִ� SkillDataTable�� ������ �̿��Ͽ� ��ųâ���� �⺻������ ǥ�õǴ� ���� �������� ���⼭ �ѹ��� �ʱ�ȭ
	//���� ��ų �Ҵ� �� �⺻ ��ų�� ������ ������ ǥ��

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

	//���� SkillComponent�� ����� �� ��ų�� �������� GetSkillDataIndexToCurrentLevel�� �̿��� �ε����� ��´�.
	//�׸��� �� �ε����� GetSkillDataRow�� �� ��ųâ Ȱ��ȭ �� ������ ��ų ������ ��ųâ�� ǥ�õ� �� �ְ� �Ѵ�.
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

