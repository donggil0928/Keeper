// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractorComponent.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class KEEPER_API IInteractable
{
	GENERATED_BODY()

public:
	virtual void OnEnterInteraction(UInteractorComponent* Interactor, const FHitResult& HitResult) = 0;
	virtual void OnStayInteraction() = 0;
	virtual void OnExitInteraction() = 0;
};
