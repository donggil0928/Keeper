// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/InteractableActor.h"
#include "Skill/SkillDataStruct.h"
#include "BloodStone.generated.h"

UCLASS()
class KEEPER_API ABloodStone : public AInteractableActor
{
	GENERATED_BODY()

public:
	ABloodStone();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

public:
	void OnEnterInteraction(UInteractorComponent* Interactor, const FHitResult& HitResult) override;
	void OnStayInteraction() override;
	void OnExitInteraction() override;

public:
	UPROPERTY(EditAnywhere, Category = "Skill")
	ESkillSetType UnlockSkillSet;
};
