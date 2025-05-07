// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/InteractableActor/TestActor.h"

ATestActor::ATestActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATestActor::BeginPlay()
{
	Super::BeginPlay();
}

void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATestActor::OnEnterInteraction(UInteractorComponent* Interactor, const FHitResult& HitResult)
{
	UE_LOG(LogTemp, Log, TEXT("Enter the interaction"));
}

void ATestActor::OnStayInteraction()
{
	UE_LOG(LogTemp, Log, TEXT("Stay the interaction"));
}

void ATestActor::OnExitInteraction()
{
	UE_LOG(LogTemp, Log, TEXT("Exit the interaction"));
}
