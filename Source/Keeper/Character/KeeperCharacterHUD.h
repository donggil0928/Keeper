// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Skill/SkillDataStruct.h"
#include "KeeperCharacterHUD.generated.h"

class UTextBlock;
class USkillSlot;
class UProgressBar;
class URoundProgressBar;
class UCooldownRound;

UCLASS()
class KEEPER_API UKeeperCharacterHUD : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	// KeeperCharacter의 정보(캐릭터 정보)를 표시
	UPROPERTY(meta = (BindWidget))
	URoundProgressBar* HUD_HPBar;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HUD_HP;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HUD_Cost;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HUD_Exp;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HUD_Level;

	// 캐릭터의 SkillComponent의 정보를 표시
	UPROPERTY(meta = (BindWidget))
	USkillSlot* HUD_Q;
	UPROPERTY(meta = (BindWidget))
	USkillSlot* HUD_W;
	UPROPERTY(meta = (BindWidget))
	USkillSlot* HUD_E;
	UPROPERTY(meta = (BindWidget))
	USkillSlot* HUD_R;

	//HUD_Q_Cooldown, HUD_W_Cooldown, HUD_E_Cooldown, HUD_R_Cooldown <-- 에디터에서 UI 작업 필요
	UPROPERTY(meta = (BindWidget))
	UCooldownRound* HUD_Q_Cooldown;
	UPROPERTY(meta = (BindWidget))
	UCooldownRound* HUD_W_Cooldown;
	UPROPERTY(meta = (BindWidget))
	UCooldownRound* HUD_E_Cooldown;
	UPROPERTY(meta = (BindWidget))
	UCooldownRound* HUD_R_Cooldown;

public:
	virtual void NativeOnInitialized() override;
	
	// 해당 UI는 플레이어의 정보를 가져와 표시하는 것이 주된 목적이다.
	// 플레이어의 정보가 변경될 때마다 해당 UI의 정보를 업데이트 해줄 필요가 잇다.
	UFUNCTION()
	void SetupHUDStatusWidgets();
	UFUNCTION()
	void SetupHUDSkillSlotWidget();
	UFUNCTION()
	void StartCooldownRoundAnim(ESkillKeyMapping InKey);
};
