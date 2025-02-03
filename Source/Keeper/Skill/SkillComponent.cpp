// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillComponent.h"
#include "Character/KeeperCharacter.h"
//#include "SkillProjectile.h"

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
	//FString SkillDataPath = TEXT("/Game/Blueprints/Skills/KeeperSkillData.KeeperSkillData");
	//static ConstructorHelpers::FObjectFinder<UDataTable> DT_Skill(*SkillDataPath);
	//KeeperSkillData = DT_Skill.Object;
}

//FSkillCustomData* USkillComponent::GetSkillCustomData(int32 index)
//{
//	return KeeperSkillData->FindRow<FSkillCustomData>(*FString::FromInt(index), TEXT(""));
//}


// Called when the game starts
void USkillComponent::BeginPlay()
{
	Super::BeginPlay();

	//SkillToQ = *GetSkillCustomData(1);
	//SkillToW = *GetSkillCustomData(6);
}