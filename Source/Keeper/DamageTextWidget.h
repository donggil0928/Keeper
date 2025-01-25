// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "DamageTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class KEEPER_API UDamageTextWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DamageTextBlock;

	UPROPERTY(Transient, BlueprintReadWrite, meta = (BindWidgetAnim))
	UWidgetAnimation* FloatUpFadeOutAnimation;
	
	void SetDamageText(const FString& DamageText, bool bAutoRemove = false);
	//void RemoveFromParentSafely();

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FSlateFontInfo CustomFont;

private:
	bool bShouldAutoRemove = false;
};
