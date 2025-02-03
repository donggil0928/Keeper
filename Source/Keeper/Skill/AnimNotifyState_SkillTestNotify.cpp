// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/AnimNotifyState_SkillTestNotify.h"
#include "Keeper/Character/KeeperCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAnimNotifyState_SkillTestNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	UE_LOG(LogTemp, Warning, TEXT("Test Notify Begin"));

	if (MeshComp)
	{
		AKeeperCharacter* Player = Cast<AKeeperCharacter>(MeshComp->GetAnimInstance()->GetOwningActor());
		if (Player)
		{
			Player->GetCharacterMovement()->MaxWalkSpeed = DashSpeed;
			Player->GetCharacterMovement()->MaxAcceleration = DashAcceleration;
		}
	}
}

void UAnimNotifyState_SkillTestNotify::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	if (MeshComp)
	{
		AKeeperCharacter* Player = Cast<AKeeperCharacter>(MeshComp->GetAnimInstance()->GetOwningActor());
		if (Player)
		{
			FVector Dir = Player->GetActorForwardVector();
			Player->AddMovementInput(Dir, 1.0f);
		}
	}
}

void UAnimNotifyState_SkillTestNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	UE_LOG(LogTemp, Warning, TEXT("Test Notify End"));

	if (MeshComp)
	{
		AKeeperCharacter* Player = Cast<AKeeperCharacter>(MeshComp->GetAnimInstance()->GetOwningActor());
		if (Player)
		{
			Player->GetCharacterMovement()->MaxWalkSpeed = Player->MovementSpeed;
			Player->GetCharacterMovement()->MaxAcceleration = 2048.0f;
		}
	}
}
