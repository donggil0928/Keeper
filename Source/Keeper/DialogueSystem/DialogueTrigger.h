// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "DialogueTrigger.generated.h"

class ADialogueManager;

UCLASS(Blueprintable)
class KEEPER_API ADialogueTrigger : public ATriggerBox
{
	GENERATED_BODY()

public:
	ADialogueTrigger();

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Dialogue")
	ADialogueManager* DialogueManager;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Dialogue")
	UDataTable* DialogueData;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Dialogue")
	FName SequenceName;
	
	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	UPROPERTY(EditAnywhere, Category = "Trigger")
	UClass* TargetBlueprintClass;

private:
	bool bHasBeenTriggered = false;
	
protected:
	virtual void BeginPlay() override;
};
