// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/AnimNotify_TestSkillNotify.h"
#include "Keeper/Character/KeeperCharacter.h"

void UAnimNotify_TestSkillNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	UE_LOG(LogTemp, Warning, TEXT("Test Notify Check"));

	if (MeshComp)
	{
		AKeeperCharacter* Player = Cast<AKeeperCharacter>(MeshComp->GetAnimInstance()->GetOwningActor());
		if (Player)
		{

		}
	}
}
