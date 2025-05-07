// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/InteractorComponent.h"
#include "Interaction/InteractableComponent.h"

// Sets default values for this component's properties
UInteractorComponent::UInteractorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsInteracting)
	{
		CurrentInteractable->OnStayInteractionDelegate.Broadcast();
	}
}

void UInteractorComponent::BeginInteraction()
{
	FHitResult HitResult;
	if (DetectInteractableActor(HitResult)) {
		//UE_LOG(LogTemp, Log, TEXT("Detection"));
		UInteractableComponent* Interact = HitResult.GetActor()->GetComponentByClass<UInteractableComponent>();
		if (!Interact) {
			return;
		}
		CurrentInteractable = Interact;
		CurrentInteractable->OnEnterInteractionDelegate.Broadcast(this, HitResult);
		bIsInteracting = true;
	}
}

void UInteractorComponent::EndInteraction()
{
	if (!CurrentInteractable) return;
	CurrentInteractable->OnExitInteractionDelegate.Broadcast();
	CurrentInteractable = nullptr;
	bIsInteracting = false;
}

bool UInteractorComponent::DetectInteractableActor(FHitResult& OutHitResult)
{
	FVector Start = GetComponentLocation() + FVector::UpVector * HeightOffset;	// 트레이스 시작지점
	FVector End = Start + GetForwardVector() * DetectRange;	// 트레이스 종료지점

	DrawDebugLine(GetWorld(), Start, End, FColor::Red, true, 5.0f);
	//UE_LOG(LogTemp, Log, TEXT("Detection"));

	return GetWorld()->LineTraceSingleByChannel(OutHitResult, Start, End, ECollisionChannel::ECC_GameTraceChannel1);
}

