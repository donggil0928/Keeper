// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageTextWidget.h"

#include "Animation/WidgetAnimation.h"

void UDamageTextWidget::NativeConstruct()
{
	Super::NativeConstruct();
    
	if (DamageTextBlock && CustomFont.FontObject)
	{
		DamageTextBlock->SetFont(CustomFont);
	}
}

void UDamageTextWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (!FloatUpFadeOutAnimation)
	{
		UE_LOG(LogTemp, Error, TEXT("FloatUpFadeOutAnimation is NULL"));
		return;
	}

	if (bShouldAutoRemove)
	{
		float CurrentTime = GetAnimationCurrentTime(FloatUpFadeOutAnimation);
		float EndTime = FloatUpFadeOutAnimation->GetEndTime();
		
		if (CurrentTime >= (EndTime - 0.02f))
		{
			UE_LOG(LogTemp, Warning, TEXT("RemoveFromParent Called"));
			RemoveFromParent();
		}
	}
}

void UDamageTextWidget::SetDamageText(const FString& DamageText, bool bAutoRemove)
{
	if (DamageTextBlock)
	{
		DamageTextBlock->SetText(FText::FromString(DamageText));
	}
	bShouldAutoRemove = bAutoRemove;

	//SetRenderTranslation(FVector2D::ZeroVector);
	
	if (FloatUpFadeOutAnimation)
	{
		PlayAnimation(FloatUpFadeOutAnimation);

		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::RemoveFromParent, 
			FloatUpFadeOutAnimation->GetEndTime(), false);
	}
}