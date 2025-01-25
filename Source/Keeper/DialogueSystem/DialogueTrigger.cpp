// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSystem/DialogueTrigger.h"
#include "DialogueManager.h"
#include "GameFramework/Character.h"

ADialogueTrigger::ADialogueTrigger()
{
	OnActorBeginOverlap.AddDynamic(this, &ADialogueTrigger::OnOverlapBegin);
}

void ADialogueTrigger::BeginPlay()
{
	Super::BeginPlay();

	if (!DialogueData || SequenceName.IsNone())
	{
		UE_LOG(LogTemp, Error, TEXT("DialogueData or SequenceName not set in %s"), *GetName());
	}
	if (!DialogueManager)
	{
		UE_LOG(LogTemp, Error, TEXT("DialogueManager not set in %s"), *GetName());
	}
}

void ADialogueTrigger::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!OtherActor || !OtherActor->IsA(TargetBlueprintClass) || !DialogueManager || bHasBeenTriggered)
	{
		return;
	}

	if (DialogueData && !SequenceName.IsNone())
	{
		FDialogueSequence* Sequence = DialogueData->FindRow<FDialogueSequence>(SequenceName, TEXT(""));
		if (Sequence)
		{
			UE_LOG(LogTemp, Warning, TEXT("Loading Sequence: %s, Entries: %d"), 
				*SequenceName.ToString(), Sequence->DialogueEntries.Num());
            
			DialogueManager->DialogueSequence = *Sequence;
			
			UE_LOG(LogTemp, Warning, TEXT("Sequence Initialized - Name: %s, Entries: %d"), 
				*DialogueManager->DialogueSequence.SequenceName,
				DialogueManager->DialogueSequence.DialogueEntries.Num());
                
			DialogueManager->StartDialogue();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to find dialogue sequence: %s"), *SequenceName.ToString());
		}
	}

	bHasBeenTriggered = true;
}