// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Skill/SkillDataStruct.h"
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
	// Info Of Q_Default.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* Q_Default;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Q_Default_Level;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Q_Default_Name;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Q_Default_Desc;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Q_Default_Cool;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Q_Default_Cost;
	// Buttons.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* Q_Default_Up;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* Q_Default_Down;

	// Info Of Q_Beast.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* Q_Beast;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Q_Beast_Level;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Q_Beast_Name;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Q_Beast_Desc;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Q_Beast_Cool;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Q_Beast_Cost;
	// Buttons.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* Q_Beast_Up;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* Q_Beast_Down;

	// Info Of Q_Mirror.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* Q_Mirror;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Q_Mirror_Level;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Q_Mirror_Name;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Q_Mirror_Desc;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Q_Mirror_Cool;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Q_Mirror_Cost;
	// Buttons.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* Q_Mirror_Up;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* Q_Mirror_Down;

	// Info Of Q_Puppet.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* Q_Puppet;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Q_Puppet_Level;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Q_Puppet_Name;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Q_Puppet_Desc;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Q_Puppet_Cool;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Q_Puppet_Cost;
	// Buttons.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* Q_Puppet_Up;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* Q_Puppet_Down;

	// Info Of Q_Dream.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* Q_Dream;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Q_Dream_Level;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Q_Dream_Name;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Q_Dream_Desc;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Q_Dream_Cool;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Q_Dream_Cost;
	// Buttons.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* Q_Dream_Up;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* Q_Dream_Down;

	// Info Of W_Default.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* W_Default;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* W_Default_Level;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* W_Default_Name;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* W_Default_Desc;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* W_Default_Cool;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* W_Default_Cost;
	// Buttons.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* W_Default_Up;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* W_Default_Down;

	// Info Of W_Beast.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* W_Beast;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* W_Beast_Level;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* W_Beast_Name;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* W_Beast_Desc;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* W_Beast_Cool;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* W_Beast_Cost;
	// Buttons.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* W_Beast_Up;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* W_Beast_Down;

	// Info Of W_Mirror.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* W_Mirror;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* W_Mirror_Level;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* W_Mirror_Name;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* W_Mirror_Desc;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* W_Mirror_Cool;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* W_Mirror_Cost;
	// Buttons.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* W_Mirror_Up;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* W_Mirror_Down;

	// Info Of W_Puppet.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* W_Puppet;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* W_Puppet_Level;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* W_Puppet_Name;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* W_Puppet_Desc;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* W_Puppet_Cool;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* W_Puppet_Cost;
	// Buttons.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* W_Puppet_Up;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* W_Puppet_Down;

	// Info Of W_Dream.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* W_Dream;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* W_Dream_Level;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* W_Dream_Name;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* W_Dream_Desc;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* W_Dream_Cool;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* W_Dream_Cost;
	// Buttons.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* W_Dream_Up;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* W_Dream_Down;

	// Info Of E_Default.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* E_Default;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* E_Default_Level;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* E_Default_Name;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* E_Default_Desc;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* E_Default_Cool;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* E_Default_Cost;
	// Buttons.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* E_Default_Up;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* E_Default_Down;

	// Info Of E_Beast.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* E_Beast;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* E_Beast_Level;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* E_Beast_Name;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* E_Beast_Desc;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* E_Beast_Cool;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* E_Beast_Cost;
	// Buttons.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* E_Beast_Up;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* E_Beast_Down;

	// Info Of E_Mirror.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* E_Mirror;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* E_Mirror_Level;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* E_Mirror_Name;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* E_Mirror_Desc;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* E_Mirror_Cool;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* E_Mirror_Cost;
	// Buttons.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* E_Mirror_Up;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* E_Mirror_Down;

	// Info Of E_Puppet.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* E_Puppet;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* E_Puppet_Level;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* E_Puppet_Name;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* E_Puppet_Desc;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* E_Puppet_Cool;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* E_Puppet_Cost;
	// Buttons.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* E_Puppet_Up;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* E_Puppet_Down;

	// Info Of E_Dream.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* E_Dream;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* E_Dream_Level;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* E_Dream_Name;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* E_Dream_Desc;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* E_Dream_Cool;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* E_Dream_Cost;
	// Buttons.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* E_Dream_Up;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* E_Dream_Down;

	// Info Of R_Default.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* R_Default;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* R_Default_Level;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* R_Default_Name;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* R_Default_Desc;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* R_Default_Cool;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* R_Default_Cost;
	// Buttons.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* R_Default_Up;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* R_Default_Down;

	// Info Of R_Beast.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* R_Beast;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* R_Beast_Level;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* R_Beast_Name;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* R_Beast_Desc;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* R_Beast_Cool;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* R_Beast_Cost;
	// Buttons.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* R_Beast_Up;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* R_Beast_Down;

	// Info Of R_Mirror.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* R_Mirror;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* R_Mirror_Level;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* R_Mirror_Name;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* R_Mirror_Desc;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* R_Mirror_Cool;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* R_Mirror_Cost;
	// Buttons.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* R_Mirror_Up;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* R_Mirror_Down;

	// Info Of R_Puppet.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* R_Puppet;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* R_Puppet_Level;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* R_Puppet_Name;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* R_Puppet_Desc;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* R_Puppet_Cool;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* R_Puppet_Cost;
	// Buttons.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* R_Puppet_Up;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* R_Puppet_Down;

	// Info Of R_Dream.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* R_Dream;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* R_Dream_Level;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* R_Dream_Name;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* R_Dream_Desc;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* R_Dream_Cool;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* R_Dream_Cost;
	// Buttons.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* R_Dream_Up;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* R_Dream_Down;


	// Info Of CurrentQ.
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

	// Info Of CurrentW.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* CurrentW;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* WName;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* WDesc;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* WCost;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* WCool;

	// Info Of CurrentE.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* CurrentE;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* EName;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* EDesc;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ECost;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ECool;

	// Info Of CurrentR.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* CurrentR;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* RName;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* RDesc;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* RCost;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* RCool;



protected:
	virtual void NativeOnInitialized();
	virtual void NativeConstruct();

public:
	// Implementable Events.
	// 
	// Method to Control the Panel.
	UFUNCTION(BlueprintImplementableEvent, Category = "SkillUI")
	void ToggleQPanel();
	UFUNCTION(BlueprintImplementableEvent, Category = "SkillUI")
	void ToggleWPanel();
	UFUNCTION(BlueprintImplementableEvent, Category = "SkillUI")
	void ToggleEPanel();
	UFUNCTION(BlueprintImplementableEvent, Category = "SkillUI")
	void ToggleRPanel();

	// Method to Control the Upgrade Image.
	UFUNCTION(BlueprintImplementableEvent, Category = "SkillUI")
	void ModifyQSkillUpgradeImage();
	UFUNCTION(BlueprintImplementableEvent, Category = "SkillUI")
	void ModifyWSkillUpgradeImage();
	UFUNCTION(BlueprintImplementableEvent, Category = "SkillUI")
	void ModifyESkillUpgradeImage();
	UFUNCTION(BlueprintImplementableEvent, Category = "SkillUI")
	void ModifyRSkillUpgradeImage();

private:
	// Debug.
	UFUNCTION()
	void TestButtonInteract();

	// Setup Method to Current Skill Slot.
	UFUNCTION()
	void SetupCurrentQWidgets(FSkillDataStruct InData, int32 InIndex);
	UFUNCTION()
	void SetupCurrentWWidgets(FSkillDataStruct InData, int32 InIndex);
	UFUNCTION()
	void SetupCurrentEWidgets(FSkillDataStruct InData, int32 InIndex);
	UFUNCTION()
	void SetupCurrentRWidgets(FSkillDataStruct InData, int32 InIndex);

	// Select Method to Each Skills.
	// Q Skills.
	UFUNCTION()
	void SelectSkill_Q_Default();
	UFUNCTION()
	void SelectSkill_Q_Beast();
	UFUNCTION()
	void SelectSkill_Q_Mirror();
	UFUNCTION()
	void SelectSkill_Q_Puppet();
	UFUNCTION()
	void SelectSkill_Q_Dream();
	// W Skills.
	UFUNCTION()
	void SelectSkill_W_Default();
	UFUNCTION()
	void SelectSkill_W_Beast();
	UFUNCTION()
	void SelectSkill_W_Mirror();
	UFUNCTION()
	void SelectSkill_W_Puppet();
	UFUNCTION()
	void SelectSkill_W_Dream();
	// E Skills.
	UFUNCTION()
	void SelectSkill_E_Default();
	UFUNCTION()
	void SelectSkill_E_Beast();
	UFUNCTION()
	void SelectSkill_E_Mirror();
	UFUNCTION()
	void SelectSkill_E_Puppet();
	UFUNCTION()
	void SelectSkill_E_Dream();
	// R Skills.
	UFUNCTION()
	void SelectSkill_R_Default();
	UFUNCTION()
	void SelectSkill_R_Beast();
	UFUNCTION()
	void SelectSkill_R_Mirror();
	UFUNCTION()
	void SelectSkill_R_Puppet();
	UFUNCTION()
	void SelectSkill_R_Dream();

	// Modify Method to Each Skills.
	// Q Skills.
	UFUNCTION()
	void ModifySkillData_Q_Default(int32 InSkillLevel = -1);
	UFUNCTION()
	void ModifySkillData_Q_Beast(int32 InSkillLevel = -1);
	UFUNCTION()
	void ModifySkillData_Q_Mirror(int32 InSkillLevel = -1);
	UFUNCTION()
	void ModifySkillData_Q_Puppet(int32 InSkillLevel = -1);
	UFUNCTION()
	void ModifySkillData_Q_Dream(int32 InSkillLevel = -1);
	// W Skills.
	UFUNCTION()
	void ModifySkillData_W_Default(int32 InSkillLevel = -1);
	UFUNCTION()
	void ModifySkillData_W_Beast(int32 InSkillLevel = -1);
	UFUNCTION()
	void ModifySkillData_W_Mirror(int32 InSkillLevel = -1);
	UFUNCTION()
	void ModifySkillData_W_Puppet(int32 InSkillLevel = -1);
	UFUNCTION()
	void ModifySkillData_W_Dream(int32 InSkillLevel = -1);
	// E Skills.
	UFUNCTION()
	void ModifySkillData_E_Default(int32 InSkillLevel = -1);
	UFUNCTION()
	void ModifySkillData_E_Beast(int32 InSkillLevel = -1);
	UFUNCTION()
	void ModifySkillData_E_Mirror(int32 InSkillLevel = -1);
	UFUNCTION()
	void ModifySkillData_E_Puppet(int32 InSkillLevel = -1);
	UFUNCTION()
	void ModifySkillData_E_Dream(int32 InSkillLevel = -1);
	// R Skills.
	UFUNCTION()
	void ModifySkillData_R_Default(int32 InSkillLevel = -1);
	UFUNCTION()
	void ModifySkillData_R_Beast(int32 InSkillLevel = -1);
	UFUNCTION()
	void ModifySkillData_R_Mirror(int32 InSkillLevel = -1);
	UFUNCTION()
	void ModifySkillData_R_Puppet(int32 InSkillLevel = -1);
	UFUNCTION()
	void ModifySkillData_R_Dream(int32 InSkillLevel = -1);

	// Button Method to Each ones.
	// Q Skills.
	UFUNCTION()
	void IncreaseSkillLevel_Q_Default();
	UFUNCTION()
	void DecreaseSkillLevel_Q_Default();
	UFUNCTION()
	void IncreaseSkillLevel_Q_Beast();
	UFUNCTION()
	void DecreaseSkillLevel_Q_Beast();
	UFUNCTION()
	void IncreaseSkillLevel_Q_Mirror();
	UFUNCTION()
	void DecreaseSkillLevel_Q_Mirror();
	UFUNCTION()
	void IncreaseSkillLevel_Q_Puppet();
	UFUNCTION()
	void DecreaseSkillLevel_Q_Puppet();
	UFUNCTION()
	void IncreaseSkillLevel_Q_Dream();
	UFUNCTION()
	void DecreaseSkillLevel_Q_Dream();
	// W Skills.
	UFUNCTION()
	void IncreaseSkillLevel_W_Default();
	UFUNCTION()
	void DecreaseSkillLevel_W_Default();
	UFUNCTION()
	void IncreaseSkillLevel_W_Beast();
	UFUNCTION()
	void DecreaseSkillLevel_W_Beast();
	UFUNCTION()
	void IncreaseSkillLevel_W_Mirror();
	UFUNCTION()
	void DecreaseSkillLevel_W_Mirror();
	UFUNCTION()
	void IncreaseSkillLevel_W_Puppet();
	UFUNCTION()
	void DecreaseSkillLevel_W_Puppet();
	UFUNCTION()
	void IncreaseSkillLevel_W_Dream();
	UFUNCTION()
	void DecreaseSkillLevel_W_Dream();
	// E Skills.
	UFUNCTION()
	void IncreaseSkillLevel_E_Default();
	UFUNCTION()
	void DecreaseSkillLevel_E_Default();
	UFUNCTION()
	void IncreaseSkillLevel_E_Beast();
	UFUNCTION()
	void DecreaseSkillLevel_E_Beast();
	UFUNCTION()
	void IncreaseSkillLevel_E_Mirror();
	UFUNCTION()
	void DecreaseSkillLevel_E_Mirror();
	UFUNCTION()
	void IncreaseSkillLevel_E_Puppet();
	UFUNCTION()
	void DecreaseSkillLevel_E_Puppet();
	UFUNCTION()
	void IncreaseSkillLevel_E_Dream();
	UFUNCTION()
	void DecreaseSkillLevel_E_Dream();
	// R Skills.
	UFUNCTION()
	void IncreaseSkillLevel_R_Default();
	UFUNCTION()
	void DecreaseSkillLevel_R_Default();
	UFUNCTION()
	void IncreaseSkillLevel_R_Beast();
	UFUNCTION()
	void DecreaseSkillLevel_R_Beast();
	UFUNCTION()
	void IncreaseSkillLevel_R_Mirror();
	UFUNCTION()
	void DecreaseSkillLevel_R_Mirror();
	UFUNCTION()
	void IncreaseSkillLevel_R_Puppet();
	UFUNCTION()
	void DecreaseSkillLevel_R_Puppet();
	UFUNCTION()
	void IncreaseSkillLevel_R_Dream();
	UFUNCTION()
	void DecreaseSkillLevel_R_Dream();

private:
	UPROPERTY()
	class USkillComponent* CharacterSkillComponent;

	//나중에 스텟UI(하단에 표시되는 UI) 레퍼런스를 가져와서 현재 스킬 초기화 시 함께 바뀔 수 있도록 수정.

};
