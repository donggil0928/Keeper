// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
//#include "Skill/SkillData.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "KeeperCharacterController.generated.h"

class AKeeperCharacter;

UCLASS()
class KEEPER_API AKeeperCharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	AKeeperCharacterController();

protected:
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	
	void Move(const FInputActionValue& Value);
	void OnRightClick(const FInputActionValue& Value);
	void SetNewDestination(const FVector& DestLocation);
	void Dodge();

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MinMoveDistance = 120.0f;

private:
	UPROPERTY()
	AKeeperCharacter* MyChar; // UObject라 스마트 포인터가 아닌 UPROPERTY

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
    
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* RightClickAction;
    
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LeftClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* DodgeAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* TabAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SkillPopupAction;

	UPROPERTY()
	class UInputAction* QSkillAction;
	UPROPERTY()
	class UInputAction* WSkillAction;
	UPROPERTY()
	class UInputAction* ESkillAction;
	UPROPERTY()
	class UInputAction* RSkillAction;

	void OnLeftClickPressed();
	void OnLeftClickReleased();
	void OnTabPressed();
	void OnTabReleased();
	void OnSkillPopupPressed();
	void OnButtonQPressed();
	void OnButtonWPressed();
	void OnButtonEPressed();
	void OnButtonRPressed();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> TabMenuWidgetClass;

	UPROPERTY()
	UUserWidget* CurrentTabMenuWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> SkillPopupWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UUserWidget* CurrentSkillPopupWidget;
};
