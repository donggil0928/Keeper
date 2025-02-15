// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillActor/AdditionalEffectActor.h"
#include "Character/KeeperCharacter.h"
#include "Monster/MonsterBase.h"

#include "NiagaraComponent.h"

// Sets default values
AAdditionalEffectActor::AAdditionalEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AppliedEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effect"));
	AppliedEffect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AAdditionalEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAdditionalEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAdditionalEffectActor::SetTargetActor(AActor* InTarget)
{
	Target = InTarget;
	this->AttachToActor(Target, FAttachmentTransformRules::KeepRelativeTransform);
	ActivateEffectImplement();
}

void AAdditionalEffectActor::SetEffectDuration(float InDuration)
{
	EffectDuration = InDuration;
	if (AMonsterBase* Monster = Cast<AMonsterBase>(Target)) {
		Monster->OnMonsterDead.AddUObject(this, &AAdditionalEffectActor::DestroyEffect);
	}
	if (AKeeperCharacter* Player = Cast<AKeeperCharacter>(Target)) {
		//
	}
	SetLifeSpan(EffectDuration);
}

void AAdditionalEffectActor::DestroyEffect()
{
	Destroy();
}

