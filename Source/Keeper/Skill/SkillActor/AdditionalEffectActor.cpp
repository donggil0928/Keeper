// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillActor/AdditionalEffectActor.h"
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

void AAdditionalEffectActor::SetTargetMonster(AMonsterBase* Monster)
{
	Target = Monster;
}

void AAdditionalEffectActor::SetEffectDuration(float InDuration)
{
	EffectDuration = InDuration;
	if(Target)	Target->OnMonsterDead.AddUObject(this, &AAdditionalEffectActor::DestroyEffect);
	SetLifeSpan(EffectDuration);
}

void AAdditionalEffectActor::DestroyEffect()
{
	Destroy();
}

