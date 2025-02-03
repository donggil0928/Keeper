﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillNotify/AnimNotify_SpawnEffectActor.h"

#include "Skill/SkillActor/AdditionalEffectActor.h"
#include "Character/KeeperCharacter.h"

void UAnimNotify_SpawnEffectActor::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp)
	{
		AKeeperCharacter* Player = Cast<AKeeperCharacter>(MeshComp->GetAnimInstance()->GetOwningActor());
		FSkillDataStruct CurrentSkillData;
		if (Player)
		{
			CurrentSkillData = Player->FindSkillDataWithMappingKey(MappingKey);
			if (!EffectActor && CurrentSkillData.EffectActor)
			{
				FVector SpawnLocation = Player->GetActorLocation();
				FRotator SpawnRotation = FRotator::ZeroRotator;
				EffectActor = GetWorld()->SpawnActor<AAdditionalEffectActor>(CurrentSkillData.EffectActor, SpawnLocation, SpawnRotation);
				EffectActor->SetEffectDuration(CurrentSkillData.EffectDuration);

				EffectActor = nullptr;
			}
		}
	}
}
