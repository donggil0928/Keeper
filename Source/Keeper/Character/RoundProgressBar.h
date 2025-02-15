// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoundProgressBar.generated.h"

/**
 * 
 */
UCLASS()
class KEEPER_API URoundProgressBar : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float PercentForRound;
public:
	void SetPercentForRound(float InPercent);
	UFUNCTION(BlueprintImplementableEvent)
	void SetPercentForRoundImplement();
};
