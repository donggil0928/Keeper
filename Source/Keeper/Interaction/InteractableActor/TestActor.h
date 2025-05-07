// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/InteractableActor.h"
#include "TestActor.generated.h"

/**
 * 
 */
UCLASS()
class KEEPER_API ATestActor : public AInteractableActor
{
	GENERATED_BODY()
	
public:
	ATestActor();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

public:
	void OnEnterInteraction(UInteractorComponent* Interactor, const FHitResult& HitResult) override;
	void OnStayInteraction() override;
	void OnExitInteraction() override;

};
