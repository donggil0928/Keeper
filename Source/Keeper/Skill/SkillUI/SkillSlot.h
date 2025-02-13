// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Skill/SkillDataStruct.h"
#include "SkillSlot.generated.h"

/**
 * 
 */
UCLASS()
class KEEPER_API USkillSlot : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	FSkillDataStruct SkillData;

public:
	UPROPERTY(meta = (BindWidget))
	class UButton* Slot_Button;
	UPROPERTY(meta = (BindWidget))
	class UImage* Slot_Icon;

public:
	UFUNCTION(BlueprintCallable)
	void InitSlotData();
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetSkillData(FSkillDataStruct InData) { SkillData = InData; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE FSkillDataStruct GetSkillData() { return SkillData; }

protected:
	virtual void NativeOnInitialized();
	//virtual void NativeConstruct();
};
