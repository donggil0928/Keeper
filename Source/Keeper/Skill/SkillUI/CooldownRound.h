// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CooldownRound.generated.h"

/**
 * 
 */
UCLASS()
class KEEPER_API UCooldownRound : public UUserWidget
{
	GENERATED_BODY()

protected:
	FTimerHandle RoundedTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CooldownRoundPercent;
	
public:
	UFUNCTION()
	void SetCooldownRoundPercent(float InCooldownRate);
	UFUNCTION(BlueprintImplementableEvent)
	void SetCooldownRoundPercentImplement(); // <-- 해당 함수 percent 값이 0.01씩 줄어들게 블루프린트로 작성.
};
