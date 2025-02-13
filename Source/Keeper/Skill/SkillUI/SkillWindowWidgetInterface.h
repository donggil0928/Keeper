// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SkillSlot.h"
#include "SkillWindowWidgetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USkillWindowWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class KEEPER_API ISkillWindowWidgetInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetupSelectedSkillData(USkillSlot* InSlot) = 0;
	virtual void ModifySkillLevel(USkillSlot* InSlot, ESkillKeyMapping InKey) = 0;
};
