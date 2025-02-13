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
	int32 Level;
	UPROPERTY()
	int32 DefaultIndex;		// index on Lv 0.
	UPROPERTY()
	ESkillKeyMapping OnKey;
	UPROPERTY()
	FSkillDataStruct SkillData;

public:
	UPROPERTY(meta = (BindWidget))
	class UButton* Slot_Button;
	UPROPERTY(meta = (BindWidget))
	class UImage* Slot_Icon;

public:
	UFUNCTION(BlueprintCallable, Category = "SkillSlot")
	void SetupSlotData(int32 InIndexAddedSkillLevel, ESkillKeyMapping InKey);

	UFUNCTION(BlueprintCallable, Category = "SkillSlot")
	FORCEINLINE int32 GetCurrentSkillLevel() { return Level; }
	FORCEINLINE void SetCurrentSkillLevel(int32 InLevel) { Level = InLevel; }
	FORCEINLINE int32 GetDefaultIndex() { return DefaultIndex; }
	FORCEINLINE void SetDefaultIndex(int32 InIndex) { DefaultIndex = InIndex; }
	FORCEINLINE ESkillKeyMapping GetSkillOnKey() { return OnKey; }
	FORCEINLINE void SetSkillOnKey(ESkillKeyMapping InKey) { OnKey = InKey; }
	FORCEINLINE int32 GetActualSkillIndex() { return DefaultIndex + Level; }

	UFUNCTION(BlueprintCallable, Category = "SkillSlot")
	FORCEINLINE void SetSkillData(FSkillDataStruct InData) { SkillData = InData; }
	UFUNCTION(BlueprintCallable, Category = "SkillSlot")
	FORCEINLINE FSkillDataStruct GetSkillData() { return SkillData; }

protected:
	virtual void NativeOnInitialized();
	//virtual void NativeConstruct();
};
