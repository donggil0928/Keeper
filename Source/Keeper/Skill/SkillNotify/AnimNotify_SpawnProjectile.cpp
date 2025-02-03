// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillNotify/AnimNotify_SpawnProjectile.h"

#include "Character/KeeperCharacter.h"
#include "Skill/SkillActor/BaseProjectileActor.h"

void UAnimNotify_SpawnProjectile::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp)
	{
		AKeeperCharacter* Player = Cast<AKeeperCharacter>(MeshComp->GetAnimInstance()->GetOwningActor());
		FSkillDataStruct CurrentSkillData;
		if (Player)
		{
			CurrentSkillData = Player->FindSkillDataWithMappingKey(MappingKey);
			if (!ProjectileActor)
			{
				FVector SpawnLocation = Player->GetActorLocation();
				FRotator SpawnRotation = FRotator::MakeFromEuler(Player->GetActorForwardVector());
				//ABaseProjectileActor* SpawnProjectile = CurrentSkillData.Projectile;
				ProjectileActor = GetWorld()->SpawnActor<ABaseProjectileActor>(CurrentSkillData.Projectile, SpawnLocation, FRotator::ZeroRotator);

				ProjectileActor->SetProjectileInfo(Player->AttackPower, CurrentSkillData.DamageCoefficient, CurrentSkillData.Range);
				ProjectileActor->FireInDirection(Player->GetActorForwardVector());

				ProjectileActor = nullptr;
			}
		}
	}
}
