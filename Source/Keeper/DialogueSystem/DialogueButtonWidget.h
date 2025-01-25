// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "DialogueButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class KEEPER_API UDialogueButtonWidget : public UButton
{
	GENERATED_BODY()

public:
	void SetChoiceIndex(int32 Index) { ChoiceIndex = Index; }
	int32 GetChoiceIndex() const { return ChoiceIndex; }

private:
	int32 ChoiceIndex;
	
};
