// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillWindowWidget.generated.h"

class UImage;
class UButton;
class UTextBlock;
class USkillSlot;
/**
 * 
 */
UCLASS()
class KEEPER_API USkillWindowWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	//최초 초기화 후 표시될 때마다 초기화가 필요한 요소들(Both Elements).
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* Q_Default;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Q_Default_Level;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* Q_Beast;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Q_Beast_Level;

	//스킬창이 표시될 때마다 초기화가 필요한 요소들(Construct Elements).
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* CurrentQ;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* QName;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* QDesc;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* QCost;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* QCool;


	//버튼들(Buttons).
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* Q_Default_Up;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* Q_Default_Down;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* Q_Beast_Up;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* Q_Beast_Down;

protected:
	virtual void NativeOnInitialized();
	virtual void NativeConstruct();

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "SkillUI")
	void ToggleQPanel();

private:
	//UFUNCTION()
	//void SelectSkill();
	UFUNCTION()
	void TestButtonInteract();

private:
	UPROPERTY()
	class USkillComponent* CharacterSkillComponent;

	//나중에 스텟UI 레퍼런스를 가져와서 현재 스킬 초기화 시 함께 바뀔 수 있도록 수정.

public:
	UPROPERTY()
	TArray<int32> CurrentLevelArray;

};
