// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "../SkillDataStruct.h"
#include "AnimNotify_RadiusDamage.generated.h"

/**
 * 
 */
UCLASS()
class KEEPER_API UAnimNotify_RadiusDamage : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);

public:
	// 해당 데미지필드 노티파이가 어떤 키에 위치한 스킬인지를 의미한다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESkillKeyMapping MappingKey;

	UPROPERTY()
	TSubclassOf<class AAdditionalEffectActor> EffectActor;

	UPROPERTY()
	float Duration;

public:
	bool CheckInRadialRange(AActor* _Checker, AActor* _Target, float _RadialAngle);
	void SetEffectDuration(float InDuration);
	void SpawnEffectActorToTarget(class AMonsterBase* InTarget);
};
