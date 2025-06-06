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

	void SetLastClickedLocation(const FVector& Location);
	FVector GetLastClickedLocation() const;
	
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

	FVector LastClickedLocation;
	
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ESCMenuAction;
	
	UPROPERTY()
	class UInputAction* QSkillAction;
	UPROPERTY()
	class UInputAction* WSkillAction;
	UPROPERTY()
	class UInputAction* ESkillAction;
	UPROPERTY()
	class UInputAction* RSkillAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

	void OnLeftClickPressed();
	void OnLeftClickReleased();
	void OnTabPressed();
	void OnTabReleased();
	void OnESCPressed();
	void OnSkillPopupPressed();
	void OnButtonQPressed();
	void OnButtonWPressed();
	void OnButtonEPressed();
	void OnButtonRPressed();
	void OnBeginInteract();
	void OnEndInteract();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> TabMenuWidgetClass;

	UPROPERTY()
	UUserWidget* CurrentTabMenuWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> SkillPopupWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UUserWidget* CurrentSkillPopupWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> ESCMenuWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UUserWidget* CurrentESCMenuWidget;
};
