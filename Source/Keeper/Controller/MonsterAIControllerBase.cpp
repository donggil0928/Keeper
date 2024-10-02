// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MonsterAIControllerBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Kismet/GameplayStatics.h"

AMonsterAIControllerBase::AMonsterAIControllerBase()
{
    PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));

    PawnSensingComponent1 = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent1"));

    PawnSensingComponent->SetPeripheralVisionAngle(180.0f);
    PawnSensingComponent->SightRadius = 500.0f;

    PawnSensingComponent1->SetPeripheralVisionAngle(45.0f);
    PawnSensingComponent1->SightRadius = 1000.0f;
    
    PawnSensingComponent->OnSeePawn.AddDynamic(this, &AMonsterAIControllerBase::OnSeePawn1);

    PawnSensingComponent1->OnSeePawn.AddDynamic(this, &AMonsterAIControllerBase::OnSeePawn2);

}

void AMonsterAIControllerBase::BeginPlay()
{
    Super::BeginPlay();
    
    if (BehaviorTreeAsset)
    {
        RunBehaviorTree(BehaviorTreeAsset);
    }
}

void AMonsterAIControllerBase::OnSeePawn1(APawn* InPawn)
{
    if (Blackboard)
    {
        Blackboard->SetValueAsBool(TEXT("seeingTarget?"), true);
    }
}

void AMonsterAIControllerBase::OnSeePawn2(APawn* InPawn)
{
    if (Blackboard)
    {
        Blackboard->SetValueAsBool(TEXT("seeingTarget?"), true);
    }
}
