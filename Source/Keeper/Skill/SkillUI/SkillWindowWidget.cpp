// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillUI/SkillWindowWidget.h"
#include "Character/KeeperCharacter.h"
#include "Skill/SkillComponent.h"
#include "Skill/SkillUI/SkillSlot.h"

#include "SkillWindowWidgetInterface.h"

#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void USkillWindowWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	CharacterSkillComponent = (Cast<AKeeperCharacter>(GetOwningPlayerPawn()))->SkillComponent;

	// Binding to Current SkillSlot Buttons.
	CurrentQ->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::ToggleQPanel);
	CurrentW->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::ToggleWPanel);
	CurrentE->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::ToggleEPanel);
	CurrentR->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::ToggleRPanel);

	// Binding to Each SkillSlot Buttons and Level Modify Buttons.
	Q_Default->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::ToggleQPanel);
	Q_Default->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::SelectSkill_Q_Default);
	Q_Default_Up->OnClicked.AddDynamic(this, &USkillWindowWidget::IncreaseSkillLevel_Q_Default);
	Q_Default_Down->OnClicked.AddDynamic(this, &USkillWindowWidget::DecreaseSkillLevel_Q_Default);

	Q_Beast->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::ToggleQPanel);
	Q_Beast->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::SelectSkill_Q_Beast);
	Q_Beast_Up->OnClicked.AddDynamic(this, &USkillWindowWidget::IncreaseSkillLevel_Q_Beast);
	Q_Beast_Down->OnClicked.AddDynamic(this, &USkillWindowWidget::DecreaseSkillLevel_Q_Beast);

	Q_Mirror->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::ToggleQPanel);
	Q_Mirror->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::SelectSkill_Q_Mirror);
	Q_Mirror_Up->OnClicked.AddDynamic(this, &USkillWindowWidget::IncreaseSkillLevel_Q_Mirror);
	Q_Mirror_Down->OnClicked.AddDynamic(this, &USkillWindowWidget::DecreaseSkillLevel_Q_Mirror);

	Q_Puppet->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::ToggleQPanel);
	Q_Puppet->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::SelectSkill_Q_Puppet);
	Q_Puppet_Up->OnClicked.AddDynamic(this, &USkillWindowWidget::IncreaseSkillLevel_Q_Puppet);
	Q_Puppet_Down->OnClicked.AddDynamic(this, &USkillWindowWidget::DecreaseSkillLevel_Q_Puppet);

	Q_Dream->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::ToggleQPanel);
	Q_Dream->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::SelectSkill_Q_Dream);
	Q_Dream_Up->OnClicked.AddDynamic(this, &USkillWindowWidget::IncreaseSkillLevel_Q_Dream);
	Q_Dream_Down->OnClicked.AddDynamic(this, &USkillWindowWidget::DecreaseSkillLevel_Q_Dream);

	W_Default->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::ToggleWPanel);
	W_Default->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::SelectSkill_W_Default);
	W_Default_Up->OnClicked.AddDynamic(this, &USkillWindowWidget::IncreaseSkillLevel_W_Default);
	W_Default_Down->OnClicked.AddDynamic(this, &USkillWindowWidget::DecreaseSkillLevel_W_Default);

	W_Beast->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::ToggleWPanel);
	W_Beast->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::SelectSkill_W_Beast);
	W_Beast_Up->OnClicked.AddDynamic(this, &USkillWindowWidget::IncreaseSkillLevel_W_Beast);
	W_Beast_Down->OnClicked.AddDynamic(this, &USkillWindowWidget::DecreaseSkillLevel_W_Beast);

	W_Mirror->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::ToggleWPanel);
	W_Mirror->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::SelectSkill_W_Mirror);
	W_Mirror_Up->OnClicked.AddDynamic(this, &USkillWindowWidget::IncreaseSkillLevel_W_Mirror);
	W_Mirror_Down->OnClicked.AddDynamic(this, &USkillWindowWidget::DecreaseSkillLevel_W_Mirror);

	W_Puppet->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::ToggleWPanel);
	W_Puppet->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::SelectSkill_W_Puppet);
	W_Puppet_Up->OnClicked.AddDynamic(this, &USkillWindowWidget::IncreaseSkillLevel_W_Puppet);
	W_Puppet_Down->OnClicked.AddDynamic(this, &USkillWindowWidget::DecreaseSkillLevel_W_Puppet);

	W_Dream->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::ToggleWPanel);
	W_Dream->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::SelectSkill_W_Dream);
	W_Dream_Up->OnClicked.AddDynamic(this, &USkillWindowWidget::IncreaseSkillLevel_W_Dream);
	W_Dream_Down->OnClicked.AddDynamic(this, &USkillWindowWidget::DecreaseSkillLevel_W_Dream);

	E_Default->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::ToggleEPanel);
	E_Default->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::SelectSkill_E_Default);
	E_Default_Up->OnClicked.AddDynamic(this, &USkillWindowWidget::IncreaseSkillLevel_E_Default);
	E_Default_Down->OnClicked.AddDynamic(this, &USkillWindowWidget::DecreaseSkillLevel_E_Default);

	E_Beast->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::ToggleEPanel);
	E_Beast->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::SelectSkill_E_Beast);
	E_Beast_Up->OnClicked.AddDynamic(this, &USkillWindowWidget::IncreaseSkillLevel_E_Beast);
	E_Beast_Down->OnClicked.AddDynamic(this, &USkillWindowWidget::DecreaseSkillLevel_E_Beast);

	E_Mirror->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::ToggleEPanel);
	E_Mirror->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::SelectSkill_E_Mirror);
	E_Mirror_Up->OnClicked.AddDynamic(this, &USkillWindowWidget::IncreaseSkillLevel_E_Mirror);
	E_Mirror_Down->OnClicked.AddDynamic(this, &USkillWindowWidget::DecreaseSkillLevel_E_Mirror);

	E_Puppet->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::ToggleEPanel);
	E_Puppet->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::SelectSkill_E_Puppet);
	E_Puppet_Up->OnClicked.AddDynamic(this, &USkillWindowWidget::IncreaseSkillLevel_E_Puppet);
	E_Puppet_Down->OnClicked.AddDynamic(this, &USkillWindowWidget::DecreaseSkillLevel_E_Puppet);

	E_Dream->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::ToggleEPanel);
	E_Dream->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::SelectSkill_E_Dream);
	E_Dream_Up->OnClicked.AddDynamic(this, &USkillWindowWidget::IncreaseSkillLevel_E_Dream);
	E_Dream_Down->OnClicked.AddDynamic(this, &USkillWindowWidget::DecreaseSkillLevel_E_Dream);

	R_Default->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::ToggleRPanel);
	R_Default->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::SelectSkill_R_Default);
	R_Default_Up->OnClicked.AddDynamic(this, &USkillWindowWidget::IncreaseSkillLevel_R_Default);
	R_Default_Down->OnClicked.AddDynamic(this, &USkillWindowWidget::DecreaseSkillLevel_R_Default);

	R_Beast->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::ToggleRPanel);
	R_Beast->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::SelectSkill_R_Beast);
	R_Beast_Up->OnClicked.AddDynamic(this, &USkillWindowWidget::IncreaseSkillLevel_R_Beast);
	R_Beast_Down->OnClicked.AddDynamic(this, &USkillWindowWidget::DecreaseSkillLevel_R_Beast);

	R_Mirror->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::ToggleRPanel);
	R_Mirror->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::SelectSkill_R_Mirror);
	R_Mirror_Up->OnClicked.AddDynamic(this, &USkillWindowWidget::IncreaseSkillLevel_R_Mirror);
	R_Mirror_Down->OnClicked.AddDynamic(this, &USkillWindowWidget::DecreaseSkillLevel_R_Mirror);

	R_Puppet->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::ToggleRPanel);
	R_Puppet->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::SelectSkill_R_Puppet);
	R_Puppet_Up->OnClicked.AddDynamic(this, &USkillWindowWidget::IncreaseSkillLevel_R_Puppet);
	R_Puppet_Down->OnClicked.AddDynamic(this, &USkillWindowWidget::DecreaseSkillLevel_R_Puppet);

	R_Dream->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::ToggleRPanel);
	R_Dream->Slot_Button->OnClicked.AddDynamic(this, &USkillWindowWidget::SelectSkill_R_Dream);
	R_Dream_Up->OnClicked.AddDynamic(this, &USkillWindowWidget::IncreaseSkillLevel_R_Dream);
	R_Dream_Down->OnClicked.AddDynamic(this, &USkillWindowWidget::DecreaseSkillLevel_R_Dream);

	
	//skillComponent에 있는 SkillDataTable의 정보를 이용하여 스킬창에서 기본적으로 표시되는 고정 정보들을 여기서 한번에 초기화.
	//최초 스킬 할당 시 기본 스킬을 장착한 것으로 표시.
	FSkillDataStruct TempStruct;
	int32 SkillIndex;

	// Q Skills.
	SkillIndex = CharacterSkillComponent->GetSkillDataIndexToCurrentLevel(
		ESkillKeyMapping::Q,
		ESkillSetType::Defalut,
		0);
	TempStruct = CharacterSkillComponent->GetSkillDataRow(SkillIndex);
	Q_Default->SetSkillData(TempStruct);
	Q_Default->SetCurrentSkillLevel(0);
	Q_Default->SetupSlotData(SkillIndex, ESkillKeyMapping::Q);
	Q_Default_Level->SetText(FText::FromString(FString::FromInt(Q_Default->GetCurrentSkillLevel())));

	SkillIndex = CharacterSkillComponent->GetSkillDataIndexToCurrentLevel(
		ESkillKeyMapping::Q,
		ESkillSetType::Beast,
		0);
	TempStruct = CharacterSkillComponent->GetSkillDataRow(SkillIndex);
	Q_Beast->SetSkillData(TempStruct);
	Q_Beast->SetCurrentSkillLevel(0);
	Q_Beast->SetupSlotData(SkillIndex, ESkillKeyMapping::Q);
	Q_Beast_Level->SetText(FText::FromString(FString::FromInt(Q_Beast->GetCurrentSkillLevel())));

	SkillIndex = CharacterSkillComponent->GetSkillDataIndexToCurrentLevel(
		ESkillKeyMapping::Q,
		ESkillSetType::Mirror,
		0);
	TempStruct = CharacterSkillComponent->GetSkillDataRow(SkillIndex);
	Q_Mirror->SetSkillData(TempStruct);
	Q_Mirror->SetCurrentSkillLevel(0);
	Q_Mirror->SetupSlotData(SkillIndex, ESkillKeyMapping::Q);
	Q_Mirror_Level->SetText(FText::FromString(FString::FromInt(Q_Mirror->GetCurrentSkillLevel())));

	SkillIndex = CharacterSkillComponent->GetSkillDataIndexToCurrentLevel(
		ESkillKeyMapping::Q,
		ESkillSetType::Puppet,
		0);
	TempStruct = CharacterSkillComponent->GetSkillDataRow(SkillIndex);
	Q_Puppet->SetSkillData(TempStruct);
	Q_Puppet->SetCurrentSkillLevel(0);
	Q_Puppet->SetupSlotData(SkillIndex, ESkillKeyMapping::Q);
	Q_Puppet_Level->SetText(FText::FromString(FString::FromInt(Q_Puppet->GetCurrentSkillLevel())));

	SkillIndex = CharacterSkillComponent->GetSkillDataIndexToCurrentLevel(
		ESkillKeyMapping::Q,
		ESkillSetType::Dream,
		0);
	TempStruct = CharacterSkillComponent->GetSkillDataRow(SkillIndex);
	Q_Dream->SetSkillData(TempStruct);
	Q_Dream->SetCurrentSkillLevel(0);
	Q_Dream->SetupSlotData(SkillIndex, ESkillKeyMapping::Q);
	Q_Dream_Level->SetText(FText::FromString(FString::FromInt(Q_Dream->GetCurrentSkillLevel())));

	// W Skills.
	SkillIndex = CharacterSkillComponent->GetSkillDataIndexToCurrentLevel(
		ESkillKeyMapping::W,
		ESkillSetType::Defalut,
		0);
	TempStruct = CharacterSkillComponent->GetSkillDataRow(SkillIndex);
	W_Default->SetSkillData(TempStruct);
	W_Default->SetCurrentSkillLevel(0);
	W_Default->SetupSlotData(SkillIndex, ESkillKeyMapping::W);
	W_Default_Level->SetText(FText::FromString(FString::FromInt(W_Default->GetCurrentSkillLevel())));

	SkillIndex = CharacterSkillComponent->GetSkillDataIndexToCurrentLevel(
		ESkillKeyMapping::W,
		ESkillSetType::Beast,
		0);
	TempStruct = CharacterSkillComponent->GetSkillDataRow(SkillIndex);
	W_Beast->SetSkillData(TempStruct);
	W_Beast->SetCurrentSkillLevel(0);
	W_Beast->SetupSlotData(SkillIndex, ESkillKeyMapping::W);
	W_Beast_Level->SetText(FText::FromString(FString::FromInt(W_Beast->GetCurrentSkillLevel())));

	SkillIndex = CharacterSkillComponent->GetSkillDataIndexToCurrentLevel(
		ESkillKeyMapping::W,
		ESkillSetType::Mirror,
		0);
	TempStruct = CharacterSkillComponent->GetSkillDataRow(SkillIndex);
	W_Mirror->SetSkillData(TempStruct);
	W_Mirror->SetCurrentSkillLevel(0);
	W_Mirror->SetupSlotData(SkillIndex, ESkillKeyMapping::W);
	W_Mirror_Level->SetText(FText::FromString(FString::FromInt(W_Mirror->GetCurrentSkillLevel())));

	SkillIndex = CharacterSkillComponent->GetSkillDataIndexToCurrentLevel(
		ESkillKeyMapping::W,
		ESkillSetType::Puppet,
		0);
	TempStruct = CharacterSkillComponent->GetSkillDataRow(SkillIndex);
	W_Puppet->SetSkillData(TempStruct);
	W_Puppet->SetCurrentSkillLevel(0);
	W_Puppet->SetupSlotData(SkillIndex, ESkillKeyMapping::W);
	W_Puppet_Level->SetText(FText::FromString(FString::FromInt(W_Puppet->GetCurrentSkillLevel())));

	SkillIndex = CharacterSkillComponent->GetSkillDataIndexToCurrentLevel(
		ESkillKeyMapping::W,
		ESkillSetType::Dream,
		0);
	TempStruct = CharacterSkillComponent->GetSkillDataRow(SkillIndex);
	W_Dream->SetSkillData(TempStruct);
	W_Dream->SetCurrentSkillLevel(0);
	W_Dream->SetupSlotData(SkillIndex, ESkillKeyMapping::W);
	W_Dream_Level->SetText(FText::FromString(FString::FromInt(W_Dream->GetCurrentSkillLevel())));

	// E Skills.
	SkillIndex = CharacterSkillComponent->GetSkillDataIndexToCurrentLevel(
		ESkillKeyMapping::E,
		ESkillSetType::Defalut,
		0);
	TempStruct = CharacterSkillComponent->GetSkillDataRow(SkillIndex);
	E_Default->SetSkillData(TempStruct);
	E_Default->SetCurrentSkillLevel(0);
	E_Default->SetupSlotData(SkillIndex, ESkillKeyMapping::E);
	E_Default_Level->SetText(FText::FromString(FString::FromInt(E_Default->GetCurrentSkillLevel())));

	SkillIndex = CharacterSkillComponent->GetSkillDataIndexToCurrentLevel(
		ESkillKeyMapping::E,
		ESkillSetType::Beast,
		0);
	TempStruct = CharacterSkillComponent->GetSkillDataRow(SkillIndex);
	E_Beast->SetSkillData(TempStruct);
	E_Beast->SetCurrentSkillLevel(0);
	E_Beast->SetupSlotData(SkillIndex, ESkillKeyMapping::E);
	E_Beast_Level->SetText(FText::FromString(FString::FromInt(E_Beast->GetCurrentSkillLevel())));

	SkillIndex = CharacterSkillComponent->GetSkillDataIndexToCurrentLevel(
		ESkillKeyMapping::E,
		ESkillSetType::Mirror,
		0);
	TempStruct = CharacterSkillComponent->GetSkillDataRow(SkillIndex);
	E_Mirror->SetSkillData(TempStruct);
	E_Mirror->SetCurrentSkillLevel(0);
	E_Mirror->SetupSlotData(SkillIndex, ESkillKeyMapping::E);
	E_Mirror_Level->SetText(FText::FromString(FString::FromInt(E_Mirror->GetCurrentSkillLevel())));

	SkillIndex = CharacterSkillComponent->GetSkillDataIndexToCurrentLevel(
		ESkillKeyMapping::E,
		ESkillSetType::Puppet,
		0);
	TempStruct = CharacterSkillComponent->GetSkillDataRow(SkillIndex);
	E_Puppet->SetSkillData(TempStruct);
	E_Puppet->SetCurrentSkillLevel(0);
	E_Puppet->SetupSlotData(SkillIndex, ESkillKeyMapping::E);
	E_Puppet_Level->SetText(FText::FromString(FString::FromInt(E_Puppet->GetCurrentSkillLevel())));

	SkillIndex = CharacterSkillComponent->GetSkillDataIndexToCurrentLevel(
		ESkillKeyMapping::E,
		ESkillSetType::Dream,
		0);
	TempStruct = CharacterSkillComponent->GetSkillDataRow(SkillIndex);
	E_Dream->SetSkillData(TempStruct);
	E_Dream->SetCurrentSkillLevel(0);
	E_Dream->SetupSlotData(SkillIndex, ESkillKeyMapping::E);
	E_Dream_Level->SetText(FText::FromString(FString::FromInt(E_Dream->GetCurrentSkillLevel())));

	// R Skills.
	SkillIndex = CharacterSkillComponent->GetSkillDataIndexToCurrentLevel(
		ESkillKeyMapping::R,
		ESkillSetType::Defalut,
		0);
	TempStruct = CharacterSkillComponent->GetSkillDataRow(SkillIndex);
	R_Default->SetSkillData(TempStruct);
	R_Default->SetCurrentSkillLevel(0);
	R_Default->SetupSlotData(SkillIndex, ESkillKeyMapping::R);
	R_Default_Level->SetText(FText::FromString(FString::FromInt(R_Default->GetCurrentSkillLevel())));

	SkillIndex = CharacterSkillComponent->GetSkillDataIndexToCurrentLevel(
		ESkillKeyMapping::R,
		ESkillSetType::Beast,
		0);
	TempStruct = CharacterSkillComponent->GetSkillDataRow(SkillIndex);
	R_Beast->SetSkillData(TempStruct);
	R_Beast->SetCurrentSkillLevel(0);
	R_Beast->SetupSlotData(SkillIndex, ESkillKeyMapping::R);
	R_Beast_Level->SetText(FText::FromString(FString::FromInt(R_Beast->GetCurrentSkillLevel())));

	SkillIndex = CharacterSkillComponent->GetSkillDataIndexToCurrentLevel(
		ESkillKeyMapping::R,
		ESkillSetType::Mirror,
		0);
	TempStruct = CharacterSkillComponent->GetSkillDataRow(SkillIndex);
	R_Mirror->SetSkillData(TempStruct);
	R_Mirror->SetCurrentSkillLevel(0);
	R_Mirror->SetupSlotData(SkillIndex, ESkillKeyMapping::R);
	R_Mirror_Level->SetText(FText::FromString(FString::FromInt(R_Mirror->GetCurrentSkillLevel())));

	SkillIndex = CharacterSkillComponent->GetSkillDataIndexToCurrentLevel(
		ESkillKeyMapping::R,
		ESkillSetType::Puppet,
		0);
	TempStruct = CharacterSkillComponent->GetSkillDataRow(SkillIndex);
	R_Puppet->SetSkillData(TempStruct);
	R_Puppet->SetCurrentSkillLevel(0);
	R_Puppet->SetupSlotData(SkillIndex, ESkillKeyMapping::R);
	R_Puppet_Level->SetText(FText::FromString(FString::FromInt(R_Puppet->GetCurrentSkillLevel())));

	SkillIndex = CharacterSkillComponent->GetSkillDataIndexToCurrentLevel(
		ESkillKeyMapping::R,
		ESkillSetType::Dream,
		0);
	TempStruct = CharacterSkillComponent->GetSkillDataRow(SkillIndex);
	R_Dream->SetSkillData(TempStruct);
	R_Dream->SetCurrentSkillLevel(0);
	R_Dream->SetupSlotData(SkillIndex, ESkillKeyMapping::R);
	R_Dream_Level->SetText(FText::FromString(FString::FromInt(R_Dream->GetCurrentSkillLevel())));
}

void USkillWindowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FSkillDataStruct TempStruct;
	int32 CurrentSkillIndex;

	//현재 SkillComponent에 저장된 각 스킬의 정보에서 GetSkillDataIndexToCurrentLevel를 이용해 인덱스를 얻는다.
	//그리고 그 인덱스로 GetSkillDataRow를 얻어서 스킬창 활성화 시 장착된 스킬 정보가 스킬창에 표시될 수 있게 한다.
	CurrentSkillIndex = CharacterSkillComponent->GetSkillDataIndexToCurrentLevel(
		ESkillKeyMapping::Q,
		CharacterSkillComponent->Skills[ESkillKeyMapping::Q].SkillSet,
		CharacterSkillComponent->Skills[ESkillKeyMapping::Q].CurrentLevel);
	TempStruct = CharacterSkillComponent->GetSkillDataRow(CurrentSkillIndex);
	SetupCurrentQWidgets(TempStruct, CurrentSkillIndex);

	CurrentSkillIndex = CharacterSkillComponent->GetSkillDataIndexToCurrentLevel(
		ESkillKeyMapping::W,
		CharacterSkillComponent->Skills[ESkillKeyMapping::W].SkillSet,
		CharacterSkillComponent->Skills[ESkillKeyMapping::W].CurrentLevel);
	TempStruct = CharacterSkillComponent->GetSkillDataRow(CurrentSkillIndex);
	SetupCurrentWWidgets(TempStruct, CurrentSkillIndex);

	CurrentSkillIndex = CharacterSkillComponent->GetSkillDataIndexToCurrentLevel(
		ESkillKeyMapping::E,
		CharacterSkillComponent->Skills[ESkillKeyMapping::E].SkillSet,
		CharacterSkillComponent->Skills[ESkillKeyMapping::E].CurrentLevel);
	TempStruct = CharacterSkillComponent->GetSkillDataRow(CurrentSkillIndex);
	SetupCurrentEWidgets(TempStruct, CurrentSkillIndex);

	CurrentSkillIndex = CharacterSkillComponent->GetSkillDataIndexToCurrentLevel(
		ESkillKeyMapping::R,
		CharacterSkillComponent->Skills[ESkillKeyMapping::R].SkillSet,
		CharacterSkillComponent->Skills[ESkillKeyMapping::R].CurrentLevel);
	TempStruct = CharacterSkillComponent->GetSkillDataRow(CurrentSkillIndex);
	SetupCurrentRWidgets(TempStruct, CurrentSkillIndex);


	int32 TempSkillLevelIndex, TempSkillLevel;

	// SkillComponent에 저장된 스킬레벨 변동사항을 읽어와 각 스킬의 정보에 입력해준다.
	// Q Skills.
	TempSkillLevelIndex = CharacterSkillComponent->GetSkillLevelIndex(ESkillKeyMapping::Q, Q_Default->GetSkillData().SkillSet);
	TempSkillLevel = CharacterSkillComponent->SkillLevelArray[TempSkillLevelIndex];
	ModifySkillData_Q_Default(TempSkillLevel);

	TempSkillLevelIndex = CharacterSkillComponent->GetSkillLevelIndex(ESkillKeyMapping::Q, Q_Beast->GetSkillData().SkillSet);
	TempSkillLevel = CharacterSkillComponent->SkillLevelArray[TempSkillLevelIndex];
	ModifySkillData_Q_Beast(TempSkillLevel);

	TempSkillLevelIndex = CharacterSkillComponent->GetSkillLevelIndex(ESkillKeyMapping::Q, Q_Mirror->GetSkillData().SkillSet);
	TempSkillLevel = CharacterSkillComponent->SkillLevelArray[TempSkillLevelIndex];
	ModifySkillData_Q_Mirror(TempSkillLevel);

	TempSkillLevelIndex = CharacterSkillComponent->GetSkillLevelIndex(ESkillKeyMapping::Q, Q_Puppet->GetSkillData().SkillSet);
	TempSkillLevel = CharacterSkillComponent->SkillLevelArray[TempSkillLevelIndex];
	ModifySkillData_Q_Puppet(TempSkillLevel);

	TempSkillLevelIndex = CharacterSkillComponent->GetSkillLevelIndex(ESkillKeyMapping::Q, Q_Dream->GetSkillData().SkillSet);
	TempSkillLevel = CharacterSkillComponent->SkillLevelArray[TempSkillLevelIndex];
	ModifySkillData_Q_Dream(TempSkillLevel);

	// W Skills.
	TempSkillLevelIndex = CharacterSkillComponent->GetSkillLevelIndex(ESkillKeyMapping::W, W_Default->GetSkillData().SkillSet);
	TempSkillLevel = CharacterSkillComponent->SkillLevelArray[TempSkillLevelIndex];
	ModifySkillData_W_Default(TempSkillLevel);

	TempSkillLevelIndex = CharacterSkillComponent->GetSkillLevelIndex(ESkillKeyMapping::W, W_Beast->GetSkillData().SkillSet);
	TempSkillLevel = CharacterSkillComponent->SkillLevelArray[TempSkillLevelIndex];
	ModifySkillData_W_Beast(TempSkillLevel);

	TempSkillLevelIndex = CharacterSkillComponent->GetSkillLevelIndex(ESkillKeyMapping::W, W_Mirror->GetSkillData().SkillSet);
	TempSkillLevel = CharacterSkillComponent->SkillLevelArray[TempSkillLevelIndex];
	ModifySkillData_W_Mirror(TempSkillLevel);

	TempSkillLevelIndex = CharacterSkillComponent->GetSkillLevelIndex(ESkillKeyMapping::W, W_Puppet->GetSkillData().SkillSet);
	TempSkillLevel = CharacterSkillComponent->SkillLevelArray[TempSkillLevelIndex];
	ModifySkillData_W_Puppet(TempSkillLevel);

	TempSkillLevelIndex = CharacterSkillComponent->GetSkillLevelIndex(ESkillKeyMapping::W, W_Dream->GetSkillData().SkillSet);
	TempSkillLevel = CharacterSkillComponent->SkillLevelArray[TempSkillLevelIndex];
	ModifySkillData_W_Dream(TempSkillLevel);

	// E Skills.
	TempSkillLevelIndex = CharacterSkillComponent->GetSkillLevelIndex(ESkillKeyMapping::E, E_Default->GetSkillData().SkillSet);
	TempSkillLevel = CharacterSkillComponent->SkillLevelArray[TempSkillLevelIndex];
	ModifySkillData_E_Default(TempSkillLevel);

	TempSkillLevelIndex = CharacterSkillComponent->GetSkillLevelIndex(ESkillKeyMapping::E, E_Beast->GetSkillData().SkillSet);
	TempSkillLevel = CharacterSkillComponent->SkillLevelArray[TempSkillLevelIndex];
	ModifySkillData_E_Beast(TempSkillLevel);

	TempSkillLevelIndex = CharacterSkillComponent->GetSkillLevelIndex(ESkillKeyMapping::E, E_Mirror->GetSkillData().SkillSet);
	TempSkillLevel = CharacterSkillComponent->SkillLevelArray[TempSkillLevelIndex];
	ModifySkillData_E_Mirror(TempSkillLevel);

	TempSkillLevelIndex = CharacterSkillComponent->GetSkillLevelIndex(ESkillKeyMapping::E, E_Puppet->GetSkillData().SkillSet);
	TempSkillLevel = CharacterSkillComponent->SkillLevelArray[TempSkillLevelIndex];
	ModifySkillData_E_Puppet(TempSkillLevel);

	TempSkillLevelIndex = CharacterSkillComponent->GetSkillLevelIndex(ESkillKeyMapping::E, E_Dream->GetSkillData().SkillSet);
	TempSkillLevel = CharacterSkillComponent->SkillLevelArray[TempSkillLevelIndex];
	ModifySkillData_E_Dream(TempSkillLevel);

	// R Skills.
	TempSkillLevelIndex = CharacterSkillComponent->GetSkillLevelIndex(ESkillKeyMapping::R, R_Default->GetSkillData().SkillSet);
	TempSkillLevel = CharacterSkillComponent->SkillLevelArray[TempSkillLevelIndex];
	ModifySkillData_R_Default(TempSkillLevel);

	TempSkillLevelIndex = CharacterSkillComponent->GetSkillLevelIndex(ESkillKeyMapping::R, R_Beast->GetSkillData().SkillSet);
	TempSkillLevel = CharacterSkillComponent->SkillLevelArray[TempSkillLevelIndex];
	ModifySkillData_R_Beast(TempSkillLevel);

	TempSkillLevelIndex = CharacterSkillComponent->GetSkillLevelIndex(ESkillKeyMapping::R, R_Mirror->GetSkillData().SkillSet);
	TempSkillLevel = CharacterSkillComponent->SkillLevelArray[TempSkillLevelIndex];
	ModifySkillData_R_Mirror(TempSkillLevel);

	TempSkillLevelIndex = CharacterSkillComponent->GetSkillLevelIndex(ESkillKeyMapping::R, R_Puppet->GetSkillData().SkillSet);
	TempSkillLevel = CharacterSkillComponent->SkillLevelArray[TempSkillLevelIndex];
	ModifySkillData_R_Puppet(TempSkillLevel);

	TempSkillLevelIndex = CharacterSkillComponent->GetSkillLevelIndex(ESkillKeyMapping::R, R_Dream->GetSkillData().SkillSet);
	TempSkillLevel = CharacterSkillComponent->SkillLevelArray[TempSkillLevelIndex];
	ModifySkillData_R_Dream(TempSkillLevel);
}

void USkillWindowWidget::TestButtonInteract()
{
	UE_LOG(LogTemp, Log, TEXT("Click!"));
}

// Setup Method to Current Skill Slot.
void USkillWindowWidget::SetupCurrentQWidgets(FSkillDataStruct InData, int32 InIndex)
{
	CurrentQ->SetSkillData(InData);
	CurrentQ->SetupSlotData(InIndex, ESkillKeyMapping::Q);
	QName->SetText(CurrentQ->GetSkillData().Name);
	QDesc->SetText(CurrentQ->GetSkillData().Description);
	QCost->SetText(FText::FromString(FString::FromInt(CurrentQ->GetSkillData().Cost)));
	QCool->SetText(FText::FromString(FString::FromInt(CurrentQ->GetSkillData().SecondToCooldown)));
	ModifyQSkillUpgradeImage();
}
void USkillWindowWidget::SetupCurrentWWidgets(FSkillDataStruct InData, int32 InIndex)
{
	CurrentW->SetSkillData(InData);
	CurrentW->SetupSlotData(InIndex, ESkillKeyMapping::W);
	WName->SetText(CurrentW->GetSkillData().Name);
	WDesc->SetText(CurrentW->GetSkillData().Description);
	WCost->SetText(FText::FromString(FString::FromInt(CurrentW->GetSkillData().Cost)));
	WCool->SetText(FText::FromString(FString::FromInt(CurrentW->GetSkillData().SecondToCooldown)));
	ModifyWSkillUpgradeImage();
}
void USkillWindowWidget::SetupCurrentEWidgets(FSkillDataStruct InData, int32 InIndex)
{
	CurrentE->SetSkillData(InData);
	CurrentE->SetupSlotData(InIndex, ESkillKeyMapping::E);
	EName->SetText(CurrentE->GetSkillData().Name);
	EDesc->SetText(CurrentE->GetSkillData().Description);
	ECost->SetText(FText::FromString(FString::FromInt(CurrentE->GetSkillData().Cost)));
	ECool->SetText(FText::FromString(FString::FromInt(CurrentE->GetSkillData().SecondToCooldown)));
	ModifyESkillUpgradeImage();
}
void USkillWindowWidget::SetupCurrentRWidgets(FSkillDataStruct InData, int32 InIndex)
{
	CurrentR->SetSkillData(InData);
	CurrentR->SetupSlotData(InIndex, ESkillKeyMapping::R);
	RName->SetText(CurrentR->GetSkillData().Name);
	RDesc->SetText(CurrentR->GetSkillData().Description);
	RCost->SetText(FText::FromString(FString::FromInt(CurrentR->GetSkillData().Cost)));
	RCool->SetText(FText::FromString(FString::FromInt(CurrentR->GetSkillData().SecondToCooldown)));
	ModifyRSkillUpgradeImage();
}


// Select Method to Each Skills.
// Q Skills.
void USkillWindowWidget::SelectSkill_Q_Default()
{
	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->SetupSelectedSkillData(Q_Default);
	}
	SetupCurrentQWidgets(Q_Default->GetSkillData(), Q_Default->GetActualSkillIndex());
}
void USkillWindowWidget::SelectSkill_Q_Beast()
{
	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->SetupSelectedSkillData(Q_Beast);
	}
	SetupCurrentQWidgets(Q_Beast->GetSkillData(), Q_Beast->GetActualSkillIndex());
}
void USkillWindowWidget::SelectSkill_Q_Mirror()
{
	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->SetupSelectedSkillData(Q_Mirror);
	}
	SetupCurrentQWidgets(Q_Mirror->GetSkillData(), Q_Mirror->GetActualSkillIndex());
}
void USkillWindowWidget::SelectSkill_Q_Puppet()
{
	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->SetupSelectedSkillData(Q_Puppet);
	}
	SetupCurrentQWidgets(Q_Puppet->GetSkillData(), Q_Puppet->GetActualSkillIndex());
}
void USkillWindowWidget::SelectSkill_Q_Dream()
{
	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->SetupSelectedSkillData(Q_Dream);
	}
	SetupCurrentQWidgets(Q_Dream->GetSkillData(), Q_Dream->GetActualSkillIndex());
}

// W Skills.
void USkillWindowWidget::SelectSkill_W_Default()
{
	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->SetupSelectedSkillData(W_Default);
	}
	SetupCurrentWWidgets(W_Default->GetSkillData(), W_Default->GetActualSkillIndex());
}
void USkillWindowWidget::SelectSkill_W_Beast()
{
	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->SetupSelectedSkillData(W_Beast);
	}
	SetupCurrentWWidgets(W_Beast->GetSkillData(), W_Beast->GetActualSkillIndex());
}
void USkillWindowWidget::SelectSkill_W_Mirror()
{
	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->SetupSelectedSkillData(W_Mirror);
	}
	SetupCurrentWWidgets(W_Mirror->GetSkillData(), W_Mirror->GetActualSkillIndex());
}
void USkillWindowWidget::SelectSkill_W_Puppet()
{
	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->SetupSelectedSkillData(W_Puppet);
	}
	SetupCurrentWWidgets(W_Puppet->GetSkillData(), W_Puppet->GetActualSkillIndex());
}
void USkillWindowWidget::SelectSkill_W_Dream()
{
	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->SetupSelectedSkillData(W_Dream);
	}
	SetupCurrentWWidgets(W_Dream->GetSkillData(), W_Dream->GetActualSkillIndex());
}

// E Skills.
void USkillWindowWidget::SelectSkill_E_Default()
{
	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->SetupSelectedSkillData(E_Default);
	}
	SetupCurrentEWidgets(E_Default->GetSkillData(), E_Default->GetActualSkillIndex());
}
void USkillWindowWidget::SelectSkill_E_Beast()
{
	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->SetupSelectedSkillData(E_Beast);
	}
	SetupCurrentEWidgets(E_Beast->GetSkillData(), E_Beast->GetActualSkillIndex());
}
void USkillWindowWidget::SelectSkill_E_Mirror()
{
	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->SetupSelectedSkillData(E_Mirror);
	}
	SetupCurrentEWidgets(E_Mirror->GetSkillData(), E_Mirror->GetActualSkillIndex());
}
void USkillWindowWidget::SelectSkill_E_Puppet()
{
	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->SetupSelectedSkillData(E_Puppet);
	}
	SetupCurrentEWidgets(E_Puppet->GetSkillData(), E_Puppet->GetActualSkillIndex());
}
void USkillWindowWidget::SelectSkill_E_Dream()
{
	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->SetupSelectedSkillData(E_Dream);
	}
	SetupCurrentEWidgets(E_Dream->GetSkillData(), E_Dream->GetActualSkillIndex());
}

// R Skills.
void USkillWindowWidget::SelectSkill_R_Default()
{
	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->SetupSelectedSkillData(R_Default);
	}
	SetupCurrentRWidgets(R_Default->GetSkillData(), R_Default->GetActualSkillIndex());
}
void USkillWindowWidget::SelectSkill_R_Beast()
{
	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->SetupSelectedSkillData(R_Beast);
	}
	SetupCurrentRWidgets(R_Beast->GetSkillData(), R_Beast->GetActualSkillIndex());
}
void USkillWindowWidget::SelectSkill_R_Mirror()
{
	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->SetupSelectedSkillData(R_Mirror);
	}
	SetupCurrentRWidgets(R_Mirror->GetSkillData(), R_Mirror->GetActualSkillIndex());
}
void USkillWindowWidget::SelectSkill_R_Puppet()
{
	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->SetupSelectedSkillData(R_Puppet);
	}
	SetupCurrentRWidgets(R_Puppet->GetSkillData(), R_Puppet->GetActualSkillIndex());
}
void USkillWindowWidget::SelectSkill_R_Dream()
{
	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->SetupSelectedSkillData(R_Dream);
	}
	SetupCurrentRWidgets(R_Dream->GetSkillData(), R_Dream->GetActualSkillIndex());
}


// Modify Method to Each Skills.
// Q Skills.
void USkillWindowWidget::ModifySkillData_Q_Default(int32 InSkillLevel)
{
	if (InSkillLevel >= 0)
	{
		Q_Default->SetCurrentSkillLevel(InSkillLevel);
	}
	int32 SkillDataIndex = Q_Default->GetActualSkillIndex();
	Q_Default->SetSkillData(CharacterSkillComponent->GetSkillDataRow(SkillDataIndex));
	// 기타 텍스트 위젯 추가되면 여기서 셋업
	Q_Default_Level->SetText(FText::FromString(FString::FromInt(Q_Default->GetCurrentSkillLevel())));
	Q_Default_Name->SetText(Q_Default->GetSkillData().Name);
	Q_Default_Desc->SetText(Q_Default->GetSkillData().Description);
	Q_Default_Cost->SetText(FText::FromString(FString::FromInt(Q_Default->GetSkillData().Cost)));
	Q_Default_Cool->SetText(FText::FromString(FString::FromInt(Q_Default->GetSkillData().SecondToCooldown)));
}
void USkillWindowWidget::ModifySkillData_Q_Beast(int32 InSkillLevel)
{
	if (InSkillLevel >= 0)
	{
		Q_Beast->SetCurrentSkillLevel(InSkillLevel);
	}
	int32 SkillDataIndex = Q_Beast->GetActualSkillIndex();
	Q_Beast->SetSkillData(CharacterSkillComponent->GetSkillDataRow(SkillDataIndex));
	// 기타 텍스트 위젯 추가되면 여기서 셋업
	Q_Beast_Level->SetText(FText::FromString(FString::FromInt(Q_Beast->GetCurrentSkillLevel())));
	Q_Beast_Name->SetText(Q_Beast->GetSkillData().Name);
	Q_Beast_Desc->SetText(Q_Beast->GetSkillData().Description);
	Q_Beast_Cost->SetText(FText::FromString(FString::FromInt(Q_Beast->GetSkillData().Cost)));
	Q_Beast_Cool->SetText(FText::FromString(FString::FromInt(Q_Beast->GetSkillData().SecondToCooldown)));
}
void USkillWindowWidget::ModifySkillData_Q_Mirror(int32 InSkillLevel)
{
	if (InSkillLevel >= 0)
	{
		Q_Mirror->SetCurrentSkillLevel(InSkillLevel);
	}
	int32 SkillDataIndex = Q_Mirror->GetActualSkillIndex();
	Q_Mirror->SetSkillData(CharacterSkillComponent->GetSkillDataRow(SkillDataIndex));
	// 기타 텍스트 위젯 추가되면 여기서 셋업
	Q_Mirror_Level->SetText(FText::FromString(FString::FromInt(Q_Mirror->GetCurrentSkillLevel())));
	Q_Mirror_Name->SetText(Q_Mirror->GetSkillData().Name);
	Q_Mirror_Desc->SetText(Q_Mirror->GetSkillData().Description);
	Q_Mirror_Cost->SetText(FText::FromString(FString::FromInt(Q_Mirror->GetSkillData().Cost)));
	Q_Mirror_Cool->SetText(FText::FromString(FString::FromInt(Q_Mirror->GetSkillData().SecondToCooldown)));
}
void USkillWindowWidget::ModifySkillData_Q_Puppet(int32 InSkillLevel)
{
	if (InSkillLevel >= 0)
	{
		Q_Puppet->SetCurrentSkillLevel(InSkillLevel);
	}
	int32 SkillDataIndex = Q_Puppet->GetActualSkillIndex();
	Q_Puppet->SetSkillData(CharacterSkillComponent->GetSkillDataRow(SkillDataIndex));
	// 기타 텍스트 위젯 추가되면 여기서 셋업
	Q_Puppet_Level->SetText(FText::FromString(FString::FromInt(Q_Puppet->GetCurrentSkillLevel())));
	Q_Puppet_Name->SetText(Q_Puppet->GetSkillData().Name);
	Q_Puppet_Desc->SetText(Q_Puppet->GetSkillData().Description);
	Q_Puppet_Cost->SetText(FText::FromString(FString::FromInt(Q_Puppet->GetSkillData().Cost)));
	Q_Puppet_Cool->SetText(FText::FromString(FString::FromInt(Q_Puppet->GetSkillData().SecondToCooldown)));
}
void USkillWindowWidget::ModifySkillData_Q_Dream(int32 InSkillLevel)
{
	if (InSkillLevel >= 0)
	{
		Q_Dream->SetCurrentSkillLevel(InSkillLevel);
	}
	int32 SkillDataIndex = Q_Dream->GetActualSkillIndex();
	Q_Dream->SetSkillData(CharacterSkillComponent->GetSkillDataRow(SkillDataIndex));
	// 기타 텍스트 위젯 추가되면 여기서 셋업
	Q_Dream_Level->SetText(FText::FromString(FString::FromInt(Q_Dream->GetCurrentSkillLevel())));
	Q_Dream_Name->SetText(Q_Dream->GetSkillData().Name);
	Q_Dream_Desc->SetText(Q_Dream->GetSkillData().Description);
	Q_Dream_Cost->SetText(FText::FromString(FString::FromInt(Q_Dream->GetSkillData().Cost)));
	Q_Dream_Cool->SetText(FText::FromString(FString::FromInt(Q_Dream->GetSkillData().SecondToCooldown)));
}

// W Skills.
void USkillWindowWidget::ModifySkillData_W_Default(int32 InSkillLevel)
{
	if (InSkillLevel >= 0)
	{
		W_Default->SetCurrentSkillLevel(InSkillLevel);
	}
	int32 SkillDataIndex = W_Default->GetActualSkillIndex();
	W_Default->SetSkillData(CharacterSkillComponent->GetSkillDataRow(SkillDataIndex));
	// 기타 텍스트 위젯 추가되면 여기서 셋업
	W_Default_Level->SetText(FText::FromString(FString::FromInt(W_Default->GetCurrentSkillLevel())));
	W_Default_Name->SetText(W_Default->GetSkillData().Name);
	W_Default_Desc->SetText(W_Default->GetSkillData().Description);
	W_Default_Cost->SetText(FText::FromString(FString::FromInt(W_Default->GetSkillData().Cost)));
	W_Default_Cool->SetText(FText::FromString(FString::FromInt(W_Default->GetSkillData().SecondToCooldown)));
}
void USkillWindowWidget::ModifySkillData_W_Beast(int32 InSkillLevel)
{
	if (InSkillLevel >= 0)
	{
		W_Beast->SetCurrentSkillLevel(InSkillLevel);
	}
	int32 SkillDataIndex = W_Beast->GetActualSkillIndex();
	W_Beast->SetSkillData(CharacterSkillComponent->GetSkillDataRow(SkillDataIndex));
	// 기타 텍스트 위젯 추가되면 여기서 셋업
	W_Beast_Level->SetText(FText::FromString(FString::FromInt(W_Beast->GetCurrentSkillLevel())));
	W_Beast_Name->SetText(W_Beast->GetSkillData().Name);
	W_Beast_Desc->SetText(W_Beast->GetSkillData().Description);
	W_Beast_Cost->SetText(FText::FromString(FString::FromInt(W_Beast->GetSkillData().Cost)));
	W_Beast_Cool->SetText(FText::FromString(FString::FromInt(W_Beast->GetSkillData().SecondToCooldown)));
}
void USkillWindowWidget::ModifySkillData_W_Mirror(int32 InSkillLevel)
{
	if (InSkillLevel >= 0)
	{
		W_Mirror->SetCurrentSkillLevel(InSkillLevel);
	}
	int32 SkillDataIndex = W_Mirror->GetActualSkillIndex();
	W_Mirror->SetSkillData(CharacterSkillComponent->GetSkillDataRow(SkillDataIndex));
	// 기타 텍스트 위젯 추가되면 여기서 셋업
	W_Mirror_Level->SetText(FText::FromString(FString::FromInt(W_Mirror->GetCurrentSkillLevel())));
	W_Mirror_Name->SetText(W_Mirror->GetSkillData().Name);
	W_Mirror_Desc->SetText(W_Mirror->GetSkillData().Description);
	W_Mirror_Cost->SetText(FText::FromString(FString::FromInt(W_Mirror->GetSkillData().Cost)));
	W_Mirror_Cool->SetText(FText::FromString(FString::FromInt(W_Mirror->GetSkillData().SecondToCooldown)));
}
void USkillWindowWidget::ModifySkillData_W_Puppet(int32 InSkillLevel)
{
	if (InSkillLevel >= 0)
	{
		W_Puppet->SetCurrentSkillLevel(InSkillLevel);
	}
	int32 SkillDataIndex = W_Puppet->GetActualSkillIndex();
	W_Puppet->SetSkillData(CharacterSkillComponent->GetSkillDataRow(SkillDataIndex));
	// 기타 텍스트 위젯 추가되면 여기서 셋업
	W_Puppet_Level->SetText(FText::FromString(FString::FromInt(W_Puppet->GetCurrentSkillLevel())));
	W_Puppet_Name->SetText(W_Puppet->GetSkillData().Name);
	W_Puppet_Desc->SetText(W_Puppet->GetSkillData().Description);
	W_Puppet_Cost->SetText(FText::FromString(FString::FromInt(W_Puppet->GetSkillData().Cost)));
	W_Puppet_Cool->SetText(FText::FromString(FString::FromInt(W_Puppet->GetSkillData().SecondToCooldown)));
}
void USkillWindowWidget::ModifySkillData_W_Dream(int32 InSkillLevel)
{
	if (InSkillLevel >= 0)
	{
		W_Dream->SetCurrentSkillLevel(InSkillLevel);
	}
	int32 SkillDataIndex = W_Dream->GetActualSkillIndex();
	W_Dream->SetSkillData(CharacterSkillComponent->GetSkillDataRow(SkillDataIndex));
	// 기타 텍스트 위젯 추가되면 여기서 셋업
	W_Dream_Level->SetText(FText::FromString(FString::FromInt(W_Dream->GetCurrentSkillLevel())));
	W_Dream_Name->SetText(W_Dream->GetSkillData().Name);
	W_Dream_Desc->SetText(W_Dream->GetSkillData().Description);
	W_Dream_Cost->SetText(FText::FromString(FString::FromInt(W_Dream->GetSkillData().Cost)));
	W_Dream_Cool->SetText(FText::FromString(FString::FromInt(W_Dream->GetSkillData().SecondToCooldown)));
}

// E Skills.
void USkillWindowWidget::ModifySkillData_E_Default(int32 InSkillLevel)
{
	if (InSkillLevel >= 0)
	{
		E_Default->SetCurrentSkillLevel(InSkillLevel);
	}
	int32 SkillDataIndex = E_Default->GetActualSkillIndex();
	E_Default->SetSkillData(CharacterSkillComponent->GetSkillDataRow(SkillDataIndex));
	// 기타 텍스트 위젯 추가되면 여기서 셋업
	E_Default_Level->SetText(FText::FromString(FString::FromInt(E_Default->GetCurrentSkillLevel())));
	E_Default_Name->SetText(E_Default->GetSkillData().Name);
	E_Default_Desc->SetText(E_Default->GetSkillData().Description);
	E_Default_Cost->SetText(FText::FromString(FString::FromInt(E_Default->GetSkillData().Cost)));
	E_Default_Cool->SetText(FText::FromString(FString::FromInt(E_Default->GetSkillData().SecondToCooldown)));
}
void USkillWindowWidget::ModifySkillData_E_Beast(int32 InSkillLevel)
{
	if (InSkillLevel >= 0)
	{
		E_Beast->SetCurrentSkillLevel(InSkillLevel);
	}
	int32 SkillDataIndex = E_Beast->GetActualSkillIndex();
	E_Beast->SetSkillData(CharacterSkillComponent->GetSkillDataRow(SkillDataIndex));
	// 기타 텍스트 위젯 추가되면 여기서 셋업
	E_Beast_Level->SetText(FText::FromString(FString::FromInt(E_Beast->GetCurrentSkillLevel())));
	E_Beast_Name->SetText(E_Beast->GetSkillData().Name);
	E_Beast_Desc->SetText(E_Beast->GetSkillData().Description);
	E_Beast_Cost->SetText(FText::FromString(FString::FromInt(E_Beast->GetSkillData().Cost)));
	E_Beast_Cool->SetText(FText::FromString(FString::FromInt(E_Beast->GetSkillData().SecondToCooldown)));
}
void USkillWindowWidget::ModifySkillData_E_Mirror(int32 InSkillLevel)
{
	if (InSkillLevel >= 0)
	{
		E_Mirror->SetCurrentSkillLevel(InSkillLevel);
	}
	int32 SkillDataIndex = E_Mirror->GetActualSkillIndex();
	E_Mirror->SetSkillData(CharacterSkillComponent->GetSkillDataRow(SkillDataIndex));
	// 기타 텍스트 위젯 추가되면 여기서 셋업
	E_Mirror_Level->SetText(FText::FromString(FString::FromInt(E_Mirror->GetCurrentSkillLevel())));
	E_Mirror_Name->SetText(E_Mirror->GetSkillData().Name);
	E_Mirror_Desc->SetText(E_Mirror->GetSkillData().Description);
	E_Mirror_Cost->SetText(FText::FromString(FString::FromInt(E_Mirror->GetSkillData().Cost)));
	E_Mirror_Cool->SetText(FText::FromString(FString::FromInt(E_Mirror->GetSkillData().SecondToCooldown)));
}
void USkillWindowWidget::ModifySkillData_E_Puppet(int32 InSkillLevel)
{
	if (InSkillLevel >= 0)
	{
		E_Puppet->SetCurrentSkillLevel(InSkillLevel);
	}
	int32 SkillDataIndex = E_Puppet->GetActualSkillIndex();
	E_Puppet->SetSkillData(CharacterSkillComponent->GetSkillDataRow(SkillDataIndex));
	// 기타 텍스트 위젯 추가되면 여기서 셋업
	E_Puppet_Level->SetText(FText::FromString(FString::FromInt(E_Puppet->GetCurrentSkillLevel())));
	E_Puppet_Name->SetText(E_Puppet->GetSkillData().Name);
	E_Puppet_Desc->SetText(E_Puppet->GetSkillData().Description);
	E_Puppet_Cost->SetText(FText::FromString(FString::FromInt(E_Puppet->GetSkillData().Cost)));
	E_Puppet_Cool->SetText(FText::FromString(FString::FromInt(E_Puppet->GetSkillData().SecondToCooldown)));
}
void USkillWindowWidget::ModifySkillData_E_Dream(int32 InSkillLevel)
{
	if (InSkillLevel >= 0)
	{
		E_Dream->SetCurrentSkillLevel(InSkillLevel);
	}
	int32 SkillDataIndex = E_Dream->GetActualSkillIndex();
	E_Dream->SetSkillData(CharacterSkillComponent->GetSkillDataRow(SkillDataIndex));
	// 기타 텍스트 위젯 추가되면 여기서 셋업
	E_Dream_Level->SetText(FText::FromString(FString::FromInt(E_Dream->GetCurrentSkillLevel())));
	E_Dream_Name->SetText(E_Dream->GetSkillData().Name);
	E_Dream_Desc->SetText(E_Dream->GetSkillData().Description);
	E_Dream_Cost->SetText(FText::FromString(FString::FromInt(E_Dream->GetSkillData().Cost)));
	E_Dream_Cool->SetText(FText::FromString(FString::FromInt(E_Dream->GetSkillData().SecondToCooldown)));
}

// R Skills.
void USkillWindowWidget::ModifySkillData_R_Default(int32 InSkillLevel)
{
	if (InSkillLevel >= 0)
	{
		R_Default->SetCurrentSkillLevel(InSkillLevel);
	}
	int32 SkillDataIndex = R_Default->GetActualSkillIndex();
	R_Default->SetSkillData(CharacterSkillComponent->GetSkillDataRow(SkillDataIndex));
	// 기타 텍스트 위젯 추가되면 여기서 셋업
	R_Default_Level->SetText(FText::FromString(FString::FromInt(R_Default->GetCurrentSkillLevel())));
	R_Default_Name->SetText(R_Default->GetSkillData().Name);
	R_Default_Desc->SetText(R_Default->GetSkillData().Description);
	R_Default_Cost->SetText(FText::FromString(FString::FromInt(R_Default->GetSkillData().Cost)));
	R_Default_Cool->SetText(FText::FromString(FString::FromInt(R_Default->GetSkillData().SecondToCooldown)));
}
void USkillWindowWidget::ModifySkillData_R_Beast(int32 InSkillLevel)
{
	if (InSkillLevel >= 0)
	{
		R_Beast->SetCurrentSkillLevel(InSkillLevel);
	}
	int32 SkillDataIndex = R_Beast->GetActualSkillIndex();
	R_Beast->SetSkillData(CharacterSkillComponent->GetSkillDataRow(SkillDataIndex));
	// 기타 텍스트 위젯 추가되면 여기서 셋업
	R_Beast_Level->SetText(FText::FromString(FString::FromInt(R_Beast->GetCurrentSkillLevel())));
	R_Beast_Name->SetText(R_Beast->GetSkillData().Name);
	R_Beast_Desc->SetText(R_Beast->GetSkillData().Description);
	R_Beast_Cost->SetText(FText::FromString(FString::FromInt(R_Beast->GetSkillData().Cost)));
	R_Beast_Cool->SetText(FText::FromString(FString::FromInt(R_Beast->GetSkillData().SecondToCooldown)));
}
void USkillWindowWidget::ModifySkillData_R_Mirror(int32 InSkillLevel)
{
	if (InSkillLevel >= 0)
	{
		R_Mirror->SetCurrentSkillLevel(InSkillLevel);
	}
	int32 SkillDataIndex = R_Mirror->GetActualSkillIndex();
	R_Mirror->SetSkillData(CharacterSkillComponent->GetSkillDataRow(SkillDataIndex));
	// 기타 텍스트 위젯 추가되면 여기서 셋업
	R_Mirror_Level->SetText(FText::FromString(FString::FromInt(R_Mirror->GetCurrentSkillLevel())));
	R_Mirror_Name->SetText(R_Mirror->GetSkillData().Name);
	R_Mirror_Desc->SetText(R_Mirror->GetSkillData().Description);
	R_Mirror_Cost->SetText(FText::FromString(FString::FromInt(R_Mirror->GetSkillData().Cost)));
	R_Mirror_Cool->SetText(FText::FromString(FString::FromInt(R_Mirror->GetSkillData().SecondToCooldown)));
}
void USkillWindowWidget::ModifySkillData_R_Puppet(int32 InSkillLevel)
{
	if (InSkillLevel >= 0)
	{
		R_Puppet->SetCurrentSkillLevel(InSkillLevel);
	}
	int32 SkillDataIndex = R_Puppet->GetActualSkillIndex();
	R_Puppet->SetSkillData(CharacterSkillComponent->GetSkillDataRow(SkillDataIndex));
	// 기타 텍스트 위젯 추가되면 여기서 셋업
	R_Puppet_Level->SetText(FText::FromString(FString::FromInt(R_Puppet->GetCurrentSkillLevel())));
	R_Puppet_Name->SetText(R_Puppet->GetSkillData().Name);
	R_Puppet_Desc->SetText(R_Puppet->GetSkillData().Description);
	R_Puppet_Cost->SetText(FText::FromString(FString::FromInt(R_Puppet->GetSkillData().Cost)));
	R_Puppet_Cool->SetText(FText::FromString(FString::FromInt(R_Puppet->GetSkillData().SecondToCooldown)));
}
void USkillWindowWidget::ModifySkillData_R_Dream(int32 InSkillLevel)
{
	if (InSkillLevel >= 0)
	{
		R_Dream->SetCurrentSkillLevel(InSkillLevel);
	}
	int32 SkillDataIndex = R_Dream->GetActualSkillIndex();
	R_Dream->SetSkillData(CharacterSkillComponent->GetSkillDataRow(SkillDataIndex));
	// 기타 텍스트 위젯 추가되면 여기서 셋업
	R_Dream_Level->SetText(FText::FromString(FString::FromInt(R_Dream->GetCurrentSkillLevel())));
	R_Dream_Name->SetText(R_Dream->GetSkillData().Name);
	R_Dream_Desc->SetText(R_Dream->GetSkillData().Description);
	R_Dream_Cost->SetText(FText::FromString(FString::FromInt(R_Dream->GetSkillData().Cost)));
	R_Dream_Cool->SetText(FText::FromString(FString::FromInt(R_Dream->GetSkillData().SecondToCooldown)));
}


// Button Method to Each ones.
// Q Skills.
void USkillWindowWidget::IncreaseSkillLevel_Q_Default()
{
	int32 PrevLevel = Q_Default->GetCurrentSkillLevel();
	Q_Default->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel + 1, 0, 5));
	ModifySkillData_Q_Default(); 

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(Q_Default, ESkillKeyMapping::Q);
	}
}
void USkillWindowWidget::DecreaseSkillLevel_Q_Default()
{
	int32 PrevLevel = Q_Default->GetCurrentSkillLevel();
	Q_Default->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel - 1, 0, 5));
	ModifySkillData_Q_Default();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(Q_Default, ESkillKeyMapping::Q);
	}
}

void USkillWindowWidget::IncreaseSkillLevel_Q_Beast()
{
	int32 PrevLevel = Q_Beast->GetCurrentSkillLevel();
	Q_Beast->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel + 1, 0, 5));
	ModifySkillData_Q_Beast();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(Q_Beast, ESkillKeyMapping::Q);
	}
}
void USkillWindowWidget::DecreaseSkillLevel_Q_Beast()
{
	int32 PrevLevel = Q_Beast->GetCurrentSkillLevel();
	Q_Beast->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel - 1, 0, 5));
	ModifySkillData_Q_Beast();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(Q_Beast, ESkillKeyMapping::Q);
	}
}

void USkillWindowWidget::IncreaseSkillLevel_Q_Mirror()
{
	int32 PrevLevel = Q_Mirror->GetCurrentSkillLevel();
	Q_Mirror->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel + 1, 0, 5));
	ModifySkillData_Q_Mirror();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(Q_Mirror, ESkillKeyMapping::Q);
	}
}
void USkillWindowWidget::DecreaseSkillLevel_Q_Mirror()
{
	int32 PrevLevel = Q_Mirror->GetCurrentSkillLevel();
	Q_Mirror->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel - 1, 0, 5));
	ModifySkillData_Q_Mirror();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(Q_Mirror, ESkillKeyMapping::Q);
	}
}

void USkillWindowWidget::IncreaseSkillLevel_Q_Puppet()
{
	int32 PrevLevel = Q_Puppet->GetCurrentSkillLevel();
	Q_Puppet->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel + 1, 0, 5));
	ModifySkillData_Q_Puppet();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(Q_Puppet, ESkillKeyMapping::Q);
	}
}
void USkillWindowWidget::DecreaseSkillLevel_Q_Puppet()
{
	int32 PrevLevel = Q_Puppet->GetCurrentSkillLevel();
	Q_Puppet->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel - 1, 0, 5));
	ModifySkillData_Q_Puppet();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(Q_Puppet, ESkillKeyMapping::Q);
	}
}

void USkillWindowWidget::IncreaseSkillLevel_Q_Dream()
{
	int32 PrevLevel = Q_Dream->GetCurrentSkillLevel();
	Q_Dream->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel + 1, 0, 5));
	ModifySkillData_Q_Dream();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(Q_Dream, ESkillKeyMapping::Q);
	}
}
void USkillWindowWidget::DecreaseSkillLevel_Q_Dream()
{
	int32 PrevLevel = Q_Dream->GetCurrentSkillLevel();
	Q_Dream->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel - 1, 0, 5));
	ModifySkillData_Q_Dream();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(Q_Dream, ESkillKeyMapping::Q);
	}
}

// W Skills.
void USkillWindowWidget::IncreaseSkillLevel_W_Default()
{
	int32 PrevLevel = W_Default->GetCurrentSkillLevel();
	W_Default->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel + 1, 0, 5));
	ModifySkillData_W_Default();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(W_Default, ESkillKeyMapping::W);
	}
}
void USkillWindowWidget::DecreaseSkillLevel_W_Default()
{
	int32 PrevLevel = W_Default->GetCurrentSkillLevel();
	W_Default->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel - 1, 0, 5));
	ModifySkillData_W_Default();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(W_Default, ESkillKeyMapping::W);
	}
}

void USkillWindowWidget::IncreaseSkillLevel_W_Beast()
{
	int32 PrevLevel = W_Beast->GetCurrentSkillLevel();
	W_Beast->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel + 1, 0, 5));
	ModifySkillData_W_Beast();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(W_Beast, ESkillKeyMapping::W);
	}
}
void USkillWindowWidget::DecreaseSkillLevel_W_Beast()
{
	int32 PrevLevel = W_Beast->GetCurrentSkillLevel();
	W_Beast->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel - 1, 0, 5));
	ModifySkillData_W_Beast();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(W_Beast, ESkillKeyMapping::W);
	}
}

void USkillWindowWidget::IncreaseSkillLevel_W_Mirror()
{
	int32 PrevLevel = W_Mirror->GetCurrentSkillLevel();
	W_Mirror->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel + 1, 0, 5));
	ModifySkillData_W_Mirror();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(W_Mirror, ESkillKeyMapping::W);
	}
}
void USkillWindowWidget::DecreaseSkillLevel_W_Mirror()
{
	int32 PrevLevel = W_Mirror->GetCurrentSkillLevel();
	W_Mirror->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel - 1, 0, 5));
	ModifySkillData_W_Mirror();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(W_Mirror, ESkillKeyMapping::W);
	}
}

void USkillWindowWidget::IncreaseSkillLevel_W_Puppet()
{
	int32 PrevLevel = W_Puppet->GetCurrentSkillLevel();
	W_Puppet->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel + 1, 0, 5));
	ModifySkillData_W_Puppet();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(W_Puppet, ESkillKeyMapping::W);
	}
}
void USkillWindowWidget::DecreaseSkillLevel_W_Puppet()
{
	int32 PrevLevel = W_Puppet->GetCurrentSkillLevel();
	W_Puppet->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel - 1, 0, 5));
	ModifySkillData_W_Puppet();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(W_Puppet, ESkillKeyMapping::W);
	}
}

void USkillWindowWidget::IncreaseSkillLevel_W_Dream()
{
	int32 PrevLevel = W_Dream->GetCurrentSkillLevel();
	W_Dream->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel + 1, 0, 5));
	ModifySkillData_W_Dream();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(W_Dream, ESkillKeyMapping::W);
	}
}
void USkillWindowWidget::DecreaseSkillLevel_W_Dream()
{
	int32 PrevLevel = W_Dream->GetCurrentSkillLevel();
	W_Dream->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel - 1, 0, 5));
	ModifySkillData_W_Dream();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(W_Dream, ESkillKeyMapping::W);
	}
}

// E Skills.
void USkillWindowWidget::IncreaseSkillLevel_E_Default()
{
	int32 PrevLevel = E_Default->GetCurrentSkillLevel();
	E_Default->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel + 1, 0, 5));
	ModifySkillData_E_Default();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(E_Default, ESkillKeyMapping::E);
	}
}
void USkillWindowWidget::DecreaseSkillLevel_E_Default()
{
	int32 PrevLevel = E_Default->GetCurrentSkillLevel();
	E_Default->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel - 1, 0, 5));
	ModifySkillData_E_Default();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(E_Default, ESkillKeyMapping::E);
	}
}

void USkillWindowWidget::IncreaseSkillLevel_E_Beast()
{
	int32 PrevLevel = E_Beast->GetCurrentSkillLevel();
	E_Beast->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel + 1, 0, 5));
	ModifySkillData_E_Beast();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(E_Beast, ESkillKeyMapping::E);
	}
}
void USkillWindowWidget::DecreaseSkillLevel_E_Beast()
{
	int32 PrevLevel = E_Beast->GetCurrentSkillLevel();
	E_Beast->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel - 1, 0, 5));
	ModifySkillData_E_Beast();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(E_Beast, ESkillKeyMapping::E);
	}
}

void USkillWindowWidget::IncreaseSkillLevel_E_Mirror()
{
	int32 PrevLevel = E_Mirror->GetCurrentSkillLevel();
	E_Mirror->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel + 1, 0, 5));
	ModifySkillData_E_Mirror();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(E_Mirror, ESkillKeyMapping::E);
	}
}
void USkillWindowWidget::DecreaseSkillLevel_E_Mirror()
{
	int32 PrevLevel = E_Mirror->GetCurrentSkillLevel();
	E_Mirror->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel - 1, 0, 5));
	ModifySkillData_E_Mirror();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(E_Mirror, ESkillKeyMapping::E);
	}
}

void USkillWindowWidget::IncreaseSkillLevel_E_Puppet()
{
	int32 PrevLevel = E_Puppet->GetCurrentSkillLevel();
	E_Puppet->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel + 1, 0, 5));
	ModifySkillData_E_Puppet();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(E_Puppet, ESkillKeyMapping::E);
	}
}
void USkillWindowWidget::DecreaseSkillLevel_E_Puppet()
{
	int32 PrevLevel = E_Puppet->GetCurrentSkillLevel();
	E_Puppet->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel - 1, 0, 5));
	ModifySkillData_E_Puppet();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(E_Puppet, ESkillKeyMapping::E);
	}
}

void USkillWindowWidget::IncreaseSkillLevel_E_Dream()
{
	int32 PrevLevel = E_Dream->GetCurrentSkillLevel();
	E_Dream->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel + 1, 0, 5));
	ModifySkillData_E_Dream();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(E_Dream, ESkillKeyMapping::E);
	}
}
void USkillWindowWidget::DecreaseSkillLevel_E_Dream()
{
	int32 PrevLevel = E_Dream->GetCurrentSkillLevel();
	E_Dream->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel - 1, 0, 5));
	ModifySkillData_E_Dream();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(E_Dream, ESkillKeyMapping::E);
	}
}

// R Skills.
void USkillWindowWidget::IncreaseSkillLevel_R_Default()
{
	int32 PrevLevel = R_Default->GetCurrentSkillLevel();
	R_Default->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel + 1, 0, 5));
	ModifySkillData_R_Default();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(R_Default, ESkillKeyMapping::R);
	}
}
void USkillWindowWidget::DecreaseSkillLevel_R_Default()
{
	int32 PrevLevel = R_Default->GetCurrentSkillLevel();
	R_Default->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel - 1, 0, 5));
	ModifySkillData_R_Default();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(R_Default, ESkillKeyMapping::R);
	}
}

void USkillWindowWidget::IncreaseSkillLevel_R_Beast()
{
	int32 PrevLevel = R_Beast->GetCurrentSkillLevel();
	R_Beast->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel + 1, 0, 5));
	ModifySkillData_R_Beast();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(R_Beast, ESkillKeyMapping::R);
	}
}
void USkillWindowWidget::DecreaseSkillLevel_R_Beast()
{
	int32 PrevLevel = R_Beast->GetCurrentSkillLevel();
	R_Beast->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel - 1, 0, 5));
	ModifySkillData_R_Beast();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(R_Beast, ESkillKeyMapping::R);
	}
}

void USkillWindowWidget::IncreaseSkillLevel_R_Mirror()
{
	int32 PrevLevel = R_Mirror->GetCurrentSkillLevel();
	R_Mirror->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel + 1, 0, 5));
	ModifySkillData_R_Mirror();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(R_Mirror, ESkillKeyMapping::R);
	}
}
void USkillWindowWidget::DecreaseSkillLevel_R_Mirror()
{
	int32 PrevLevel = R_Mirror->GetCurrentSkillLevel();
	R_Mirror->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel - 1, 0, 5));
	ModifySkillData_R_Mirror();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(R_Mirror, ESkillKeyMapping::R);
	}
}

void USkillWindowWidget::IncreaseSkillLevel_R_Puppet()
{
	int32 PrevLevel = R_Puppet->GetCurrentSkillLevel();
	R_Puppet->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel + 1, 0, 5));
	ModifySkillData_R_Puppet();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(R_Puppet, ESkillKeyMapping::R);
	}
}
void USkillWindowWidget::DecreaseSkillLevel_R_Puppet()
{
	int32 PrevLevel = R_Puppet->GetCurrentSkillLevel();
	R_Puppet->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel - 1, 0, 5));
	ModifySkillData_R_Puppet();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(R_Puppet, ESkillKeyMapping::R);
	}
}

void USkillWindowWidget::IncreaseSkillLevel_R_Dream()
{
	int32 PrevLevel = R_Dream->GetCurrentSkillLevel();
	R_Dream->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel + 1, 0, 5));
	ModifySkillData_R_Dream();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(R_Dream, ESkillKeyMapping::R);
	}
}
void USkillWindowWidget::DecreaseSkillLevel_R_Dream()
{
	int32 PrevLevel = R_Dream->GetCurrentSkillLevel();
	R_Dream->SetCurrentSkillLevel(FMath::Clamp<int32>(PrevLevel - 1, 0, 5));
	ModifySkillData_R_Dream();

	ISkillWindowWidgetInterface* SkillWidget = Cast<ISkillWindowWidgetInterface>(CharacterSkillComponent);
	if (SkillWidget)
	{
		SkillWidget->ModifySkillLevel(R_Dream, ESkillKeyMapping::R);
	}
}

