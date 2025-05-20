// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/InteractableActor.h"
#include "InteractiveDialogue.generated.h"

class ADialogueTrigger;

UCLASS()
class KEEPER_API AInteractiveDialogue : public AInteractableActor
{
	GENERATED_BODY()
	
public:
	AInteractiveDialogue();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

public:
	void OnEnterInteraction(UInteractorComponent* Interactor, const FHitResult& HitResult) override;
	void OnStayInteraction() override;
	void OnExitInteraction() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TSubclassOf<ADialogueTrigger> DialogueTrigger;
	UPROPERTY()
	ADialogueTrigger* DialogueBox;


	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Dialogue")
	class ADialogueManager* InitDialogueManager;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Dialogue")
	UDataTable* InitDialogueData;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Dialogue")
	FName InitSequenceName;
};
