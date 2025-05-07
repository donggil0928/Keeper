// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/InteractableActor.h"
#include "Interaction/InteractableComponent.h"
#include "Interaction/InteractorComponent.h"

// Sets default values
AInteractableActor::AInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("InteractableComponent"));
	InteractableComponent->OnEnterInteractionDelegate.AddDynamic(this, &AInteractableActor::OnEnterInteraction);
	InteractableComponent->OnStayInteractionDelegate.AddDynamic(this, &AInteractableActor::OnStayInteraction);
	InteractableComponent->OnExitInteractionDelegate.AddDynamic(this, &AInteractableActor::OnExitInteraction);
}

// Called when the game starts or when spawned
void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableActor::OnEnterInteraction(UInteractorComponent* Interactor, const FHitResult& HitResult)
{
	unimplemented();
}

void AInteractableActor::OnStayInteraction()
{
	unimplemented();
}

void AInteractableActor::OnExitInteraction()
{
	unimplemented();
}

