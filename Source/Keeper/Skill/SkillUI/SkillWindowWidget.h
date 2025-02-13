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
	//���� �ʱ�ȭ �� ǥ�õ� ������ �ʱ�ȭ�� �ʿ��� ��ҵ�(Both Elements).
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* Q_Default;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Q_Default_Level;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* Q_Beast;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Q_Beast_Level;

	//��ųâ�� ǥ�õ� ������ �ʱ�ȭ�� �ʿ��� ��ҵ�(Construct Elements).
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


	//��ư��(Buttons).
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

	//���߿� ����UI ���۷����� �����ͼ� ���� ��ų �ʱ�ȭ �� �Բ� �ٲ� �� �ֵ��� ����.

public:
	UPROPERTY()
	TArray<int32> CurrentLevelArray;

};
