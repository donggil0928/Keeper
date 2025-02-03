// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillNotify/AnimNotify_RadiusDamage.h"
#include "Character/KeeperCharacter.h"
#include "Monster/MonsterBase.h"
#include "Skill/SkillActor/AdditionalEffectActor.h"

#include "Engine/OverlapResult.h"

//https://blog.naver.com/kzh8055/222066096980 : 부채꼴 범위의 공격 판정 참고

void UAnimNotify_RadiusDamage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp)
	{
		AKeeperCharacter* Player = Cast<AKeeperCharacter>(MeshComp->GetAnimInstance()->GetOwningActor());
		FSkillDataStruct CurrentSkillData;
		if (Player)
		{
			CurrentSkillData = Player->FindSkillDataWithMappingKey(MappingKey);

			if (CurrentSkillData.SkillAttackType == ESkillAttackType::Debuff && CurrentSkillData.EffectActor)
			{
				EffectActor = CurrentSkillData.EffectActor;
				SetEffectDuration(CurrentSkillData.EffectDuration);
			}

			FCollisionQueryParams Params(NAME_None, false, Player);
			const FVector Extent(CurrentSkillData.Range, CurrentSkillData.Range, 200.0f);
			TArray<FOverlapResult> OutOverlaps;
			if (GetWorld()->OverlapMultiByChannel(
				OutOverlaps,
				Player->GetActorLocation(),
				FQuat::Identity,
				ECollisionChannel::ECC_GameTraceChannel1, //trace 채널 설정 필요
				FCollisionShape::MakeCapsule(Extent),
				Params
			)) {
				for (const FOverlapResult& Result : OutOverlaps)
				{
					AMonsterBase* Monster = Cast<AMonsterBase>(Result.GetComponent()->GetOwner());
					if (Monster)
					{
						if (CheckInRadialRange(Player, Monster, 90.0f))
						{
							float AmountDamage = Player->AttackPower * CurrentSkillData.DamageCoefficient;
							Monster->TakeDamage(AmountDamage);

							if (EffectActor) SpawnEffectActorToTarget(Monster);
						}
					}
				}
			}
			DrawDebugCapsule(GetWorld(), Player->GetActorLocation(), 200.0f, CurrentSkillData.Range, FQuat::Identity, FColor::Red, false, 2.0f, 0, 3.0f);
		}
	}
}

bool UAnimNotify_RadiusDamage::CheckInRadialRange(AActor* _Checker, AActor* _Target, float _RadialAngle)
{
	FVector FirstVector = _Checker->GetActorForwardVector();
	FVector SecondVector = _Target->GetActorLocation() - _Checker->GetActorLocation();

	float DegreeBetween = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(FirstVector, SecondVector)));
	if (DegreeBetween <= _RadialAngle / 2.0f)
	{
		return true;
	}
	return false;
}

void UAnimNotify_RadiusDamage::SetEffectDuration(float InDuration)
{
	Duration = InDuration;
}

void UAnimNotify_RadiusDamage::SpawnEffectActorToTarget(AMonsterBase* InTarget)
{
	AAdditionalEffectActor* SpawnedEffectActor;

	FVector SpawnLocation = InTarget->GetActorLocation();
	FRotator SpawnRotation = FRotator::ZeroRotator;
	SpawnedEffectActor = GetWorld()->SpawnActor<AAdditionalEffectActor>(EffectActor, SpawnLocation, SpawnRotation);

	SpawnedEffectActor->SetTargetMonster(InTarget);
	SpawnedEffectActor->SetEffectDuration(Duration);
}
