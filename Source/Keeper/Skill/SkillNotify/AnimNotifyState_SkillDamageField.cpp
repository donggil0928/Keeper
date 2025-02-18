// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillNotify/AnimNotifyState_SkillDamageField.h"
#include "Keeper/Character/KeeperCharacter.h"
#include "Skill/SkillComponent.h"
#include "Skill/BaseSkillDamageField.h"

#if WITH_EDITOR
#include "AnimationEditorViewportClient.h"
#endif

void UAnimNotifyState_SkillDamageField::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	//Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp)
	{
		AKeeperCharacter* Player = Cast<AKeeperCharacter>(MeshComp->GetOwner());
		FSkillDataStruct CurrentSkillData;
		if (Player)
		{
			CurrentSkillData = Player->FindSkillDataWithMappingKey(MappingKey);
			ModifyDamageFieldMembers(Player->AttackPower, CurrentSkillData.DamageCoefficient, CurrentSkillData.Range);
		}

		if (SpawnedDamageField)
		{
			SpawnedDamageField->Destroy();
			SpawnedDamageField = nullptr;
		}
		{
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			const FTransform MeshTransform = MeshComp->GetComponentTransform();
			FTransform SpawnTransform;
			SpawnTransform.SetLocation(MeshTransform.TransformPosition(LocationOffset));
			SpawnTransform.SetRotation(MeshTransform.GetRotation() * RotationOffsetQuat);
			SpawnTransform.SetScale3D(Scale.One());
			
			SpawnedDamageField = MeshComp->GetWorld()->SpawnActor<ABaseSkillDamageField>(ABaseSkillDamageField::StaticClass(), SpawnTransform, SpawnInfo);
			SpawnedDamageField->CreateDamageField_Sphere(DamageRadius, ActualDamage);
			// 디버프 부여효과가 있는 경우.
			if (CurrentSkillData.SkillAttackType == ESkillAttackType::Debuff && CurrentSkillData.EffectActor)
			{
				SpawnedDamageField->EffectActor = CurrentSkillData.EffectActor;
				SpawnedDamageField->SetEffectDuration(CurrentSkillData.EffectDuration);
			}
		}
	}
}

void UAnimNotifyState_SkillDamageField::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	//Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UAnimNotifyState_SkillDamageField::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	//Super::NotifyEnd(MeshComp, Animation);

	if (SpawnedDamageField)
	{
		SpawnedDamageField->Destroy();
		SpawnedDamageField = nullptr;
	}
}

void UAnimNotifyState_SkillDamageField::PostLoad()
{
	Super::PostLoad();

	RotationOffsetQuat = FQuat(RotationOffset);
}

#if WITH_EDITOR
void UAnimNotifyState_SkillDamageField::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.MemberProperty && PropertyChangedEvent.MemberProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UAnimNotifyState_SkillDamageField, RotationOffset))
	{
		RotationOffsetQuat = FQuat(RotationOffset);
	}
}
#endif

void UAnimNotifyState_SkillDamageField::ModifyDamageFieldMembers(float NewDamage, float NewCoefficient, float NewRadius)
{
	BaseDamage = NewDamage;
	DamageCoefficient = NewCoefficient;
	DamageRadius = NewRadius;
	ActualDamage = BaseDamage * DamageCoefficient;
}
