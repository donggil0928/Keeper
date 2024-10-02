// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MonsterAIControllerBase.generated.h"

class APawn;
class UPawnSensingComponent;

/**
 * 
 */
UCLASS()
class KEEPER_API AMonsterAIControllerBase : public AAIController
{
	GENERATED_BODY()
public:
	AMonsterAIControllerBase();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	UPawnSensingComponent* PawnSensingComponent;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	UPawnSensingComponent* PawnSensingComponent1;

	UFUNCTION()
	void OnSeePawn1(APawn* InPawn);

	UFUNCTION()
	void OnSeePawn2(APawn* InPawn);
};
