// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
//#include "Skill/SkillData.h"
#include "KeeperCharacterController.generated.h"

class AKeeperCharacter;

UCLASS()
class KEEPER_API AKeeperCharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	AKeeperCharacterController();
	virtual void BeginPlay() override;
	
protected:
	UPROPERTY()
	AKeeperCharacter* MyChar; // UObject라 스마트 포인터가 아닌 UPROPERTY
	bool bClickRightMouse;
	
	void InputRightMouseButtonPressed();
	void InputRightMouseButtonReleased();
	void SetNewDestination(const FVector Destination);
	void MoveToMouseCursor();
	virtual void SetupInputComponent() override;
	void OnLeftClickPressed();
	void OnLeftClickReleased();
	void UseSkill(int SkillIndex);
	virtual void PlayerTick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> TabMenuWidgetClass;

	UPROPERTY()
	UUserWidget* CurrentTabMenuWidget;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void OnTabPressed();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void OnTabReleased();
};
