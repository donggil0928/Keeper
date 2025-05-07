// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/InteractableActor/BloodStone.h"
#include "Character/KeeperCharacter.h"

ABloodStone::ABloodStone()
{
}

void ABloodStone::BeginPlay()
{
	Super::BeginPlay();
}

void ABloodStone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABloodStone::OnEnterInteraction(UInteractorComponent* Interactor, const FHitResult& HitResult)
{
	//UE_LOG(LogTemp, Log, TEXT("Detection"));
	AKeeperCharacter* Player = Cast<AKeeperCharacter>(Interactor->GetAttachParentActor());
	if (Player)
	{
		//UE_LOG(LogTemp, Log, TEXT("Enter the interaction"));
		if (!Player->UnlockedSkillInfo[UnlockSkillSet]) {
			//UE_LOG(LogTemp, Log, TEXT("Unlock Skill"));
			Player->UnlockedSkillInfo.Emplace(UnlockSkillSet, true);
		}
	}
}

void ABloodStone::OnStayInteraction()
{
	return;
}

void ABloodStone::OnExitInteraction()
{
	UE_LOG(LogTemp, Log, TEXT("Exit the interaction"));
	Destroy();
}
