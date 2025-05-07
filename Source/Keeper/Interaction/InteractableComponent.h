// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interaction/InteractorComponent.h"
#include "InteractableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEnterInteractionDelegate, UInteractorComponent*, Interactor, const FHitResult&, HitResult);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStayInteractionDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExitInteractionDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KEEPER_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractableComponent();
	
	UPROPERTY()
	FOnEnterInteractionDelegate OnEnterInteractionDelegate;
	UPROPERTY()
	FOnStayInteractionDelegate OnStayInteractionDelegate;
	UPROPERTY()
	FOnExitInteractionDelegate OnExitInteractionDelegate;
};
