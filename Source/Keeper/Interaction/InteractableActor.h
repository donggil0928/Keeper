// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "InteractableActor.generated.h"

class UInteractableComponent;
class UInteractorComponent;

UCLASS()
class KEEPER_API AInteractableActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableActor();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	virtual void OnEnterInteraction(UInteractorComponent* Interactor, const FHitResult& HitResult) override;
	UFUNCTION(BlueprintCallable)
	virtual void OnStayInteraction() override;
	UFUNCTION(BlueprintCallable)
	virtual void OnExitInteraction() override;

private:
	UPROPERTY()
	UInteractableComponent* InteractableComponent;
};
