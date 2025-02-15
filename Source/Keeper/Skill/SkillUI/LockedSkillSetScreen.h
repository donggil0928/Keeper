// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../SkillDataStruct.h"
#include "LockedSkillSetScreen.generated.h"

/**
 * 
 */
UCLASS()
class KEEPER_API ULockedSkillSetScreen : public UUserWidget 
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	ESkillSetType LockedSkillSetByThisScreen;

protected:
	virtual void NativeConstruct() override;
};
