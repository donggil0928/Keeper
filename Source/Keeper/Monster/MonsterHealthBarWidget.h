// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MonsterHealthBarWidget.generated.h"


UCLASS()
class KEEPER_API UMonsterHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void UpdateHealthPercent(float HealthPercent);

	// UFUNCTION(BlueprintCallable)
	// void UpdateDelayedHealthPercent(float HealthPercent);

protected:
	UPROPERTY(meta = (BindWidget))
	class UOverlay* HealthBarOverlay;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* DelayedHealthBar;

	UPROPERTY(meta = (BindWidget))
	class UImage* BackgroundImage;

	UPROPERTY(EditAnywhere, Category = "Health Bar")
	float InterpolationSpeed = 2.0f;
	
	FTimerHandle DelayedHealthBarTimerHandle;
	float LastHealthPercent;

private:
	float CurrentHealthPercent = 1.0f;
	float TargetHealthPercent = 1.0f;
};
