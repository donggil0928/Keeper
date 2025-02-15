// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillDataStruct.h"
#include "Character/KeeperCharacter.h"

#include "Animation/AnimInstance.h"

SkillDataStruct::SkillDataStruct()
{
}

SkillDataStruct::~SkillDataStruct()
{
}

void FSkillDataStruct::Use(AKeeperCharacter* player)
{
	UE_LOG(LogTemp, Log, TEXT("Activated Skill :: %s"), *Name.ToString());

	// 스킬 사용 시 플레이어의 위치와 마우스의 위치를 초기화
	PlayerPosition = player->GetActorLocation();
	APlayerController* MyPlayerController;
	MyPlayerController = player->GetWorld()->GetFirstPlayerController();
	if (MyPlayerController)
	{
		FHitResult Hit;
		MyPlayerController->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		if (Hit.bBlockingHit)
		{
			MouseCursorPosition = Hit.ImpactPoint;
		}

		UE_LOG(LogTemp, Log, TEXT("PlayerPos	:: %f, %f, %f"), PlayerPosition.X, PlayerPosition.Y, PlayerPosition.Z);
		UE_LOG(LogTemp, Log, TEXT("MousePos		:: %f, %f, %f"), MouseCursorPosition.X, MouseCursorPosition.Y, MouseCursorPosition.Z);
	}
	else UE_LOG(LogTemp, Warning, TEXT("Not Found PlayerController!"));

	player->IncreasedMadness(Cost);

	// 해당 부분에서 스킬 사용 시 애니메이션과 이펙트 등을 처리(예정)
	// 타입별로 구분해서 구조체 내에 입력된 정보에 따라 스킬을 활성화
	// --> 스킬별 애님 몽타주를 만들어 이후 테이블을 통해 일괄 초기화할 예정.
	switch (SkillAttackType)
	{
	case ESkillAttackType::Melee:
	{
		UE_LOG(LogTemp, Log, TEXT("Melee Skill"));

		UAnimInstance* AnimInstance = player->GetMesh()->GetAnimInstance();
		if (AnimInstance)
		{
			if (SkillAnimMontage)
			{
				AnimInstance->Montage_Play(SkillAnimMontage);
			}
			else
				DrawDebugSphere(player->GetWorld(), PlayerPosition + player->GetActorForwardVector() * 100.0f, Range, 26, FColor::Red, false, 3.0f, 0, 2);
		}

		break;
	}
	case ESkillAttackType::Ranged:
	{
		UE_LOG(LogTemp, Log, TEXT("Ranged Skill"));

		UAnimInstance* AnimInstance = player->GetMesh()->GetAnimInstance();
		if (AnimInstance)
		{
			if (SkillAnimMontage)
			{
				AnimInstance->Montage_Play(SkillAnimMontage);
			}
			else
				DrawDebugSphere(player->GetWorld(), PlayerPosition + player->GetActorForwardVector() * 100.0f, Range, 26, FColor::Red, false, 3.0f, 0, 2);
		}

		break;
	}
	case ESkillAttackType::Buff:
	{
		UAnimInstance* AnimInstance = player->GetMesh()->GetAnimInstance();
		if (AnimInstance)
		{
			if (SkillAnimMontage)
			{
				AnimInstance->Montage_Play(SkillAnimMontage);
			}
			else
				UE_LOG(LogTemp, Warning, TEXT("Not Found Montage!"));
		}
		break;
	}

	default:
		break;
	}
}
