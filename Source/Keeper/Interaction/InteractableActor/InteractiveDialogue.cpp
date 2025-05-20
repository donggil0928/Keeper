// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/InteractableActor/InteractiveDialogue.h"

#include "Character/KeeperCharacter.h"
#include "DialogueSystem/DialogueTrigger.h"
#include "Components/ShapeComponent.h"

AInteractiveDialogue::AInteractiveDialogue()
{
}

void AInteractiveDialogue::BeginPlay()
{
	Super::BeginPlay();
	DialogueBox = GetWorld()->SpawnActor<ADialogueTrigger>(DialogueTrigger, GetTransform());
	if (DialogueBox)
	{
		//UE_LOG(LogTemp, Log, TEXT("Spawned Interactive Dialogue"));
		DialogueBox->DialogueManager = InitDialogueManager;
		DialogueBox->DialogueData = InitDialogueData;
		DialogueBox->SequenceName = InitSequenceName;
	}
}

void AInteractiveDialogue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractiveDialogue::OnEnterInteraction(UInteractorComponent* Interactor, const FHitResult& HitResult)
{
	//UE_LOG(LogTemp, Log, TEXT("Detection"));
	AKeeperCharacter* Player = Cast<AKeeperCharacter>(Interactor->GetAttachParentActor());
	if (Player)
	{
		if (DialogueBox)
		{
			//UE_LOG(LogTemp, Log, TEXT("Enter the interaction"));
			if (DialogueBox->IsValidDialogue())
			{
				DialogueBox->BeginDialogue();
			}
		}
	}
}

void AInteractiveDialogue::OnStayInteraction()
{
	return;
}

void AInteractiveDialogue::OnExitInteraction()
{
	return;
}
