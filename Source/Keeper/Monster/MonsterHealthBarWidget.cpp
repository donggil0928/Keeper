// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterHealthBarWidget.h"

#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/ProgressBar.h"


void UMonsterHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (HealthBarOverlay)
	{
		HealthBarOverlay->SetVisibility(ESlateVisibility::Visible);
	}
    
	if (HealthBar)
	{
		HealthBar->SetVisibility(ESlateVisibility::Visible);
		HealthBar->SetPercent(1.0f);
	}
	
	if (DelayedHealthBar)
	{
		DelayedHealthBar->SetVisibility(ESlateVisibility::Visible);
		DelayedHealthBar->SetPercent(1.0f);
	}

	if (BackgroundImage)
	{
		BackgroundImage->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMonsterHealthBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	CurrentHealthPercent = FMath::FInterpTo(
	CurrentHealthPercent, 
	TargetHealthPercent, 
	InDeltaTime, 
	InterpolationSpeed
);

	if (DelayedHealthBar)
	{
		DelayedHealthBar->SetPercent(FMath::Clamp(CurrentHealthPercent, 0.0f, 1.0f));
	}
}

void UMonsterHealthBarWidget::UpdateHealthPercent(float HealthPercent)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(FMath::Clamp(HealthPercent, 0.0f, 1.0f));
	}

	GetWorld()->GetTimerManager().ClearTimer(DelayedHealthBarTimerHandle);
	
	if (DelayedHealthBar)
	{
		GetWorld()->GetTimerManager().SetTimer(
			DelayedHealthBarTimerHandle, 
			[this, HealthPercent]() 
			{
				if (DelayedHealthBar)
				{
					TargetHealthPercent = FMath::Clamp(HealthPercent, 0.0f, 1.0f);
				}
			}, 
			1.0f, 
			false
		);
	}
}
