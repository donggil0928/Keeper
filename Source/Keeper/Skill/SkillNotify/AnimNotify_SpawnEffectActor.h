// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "../SkillDataStruct.h"
#include "AnimNotify_SpawnEffectActor.generated.h"

/**
 * 플레이어 캐릭터가 스스로에게 버프를 부여할 때 사용하는 노티파이.
 */
UCLASS()
class KEEPER_API UAnimNotify_SpawnEffectActor : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:
	// 해당 데미지필드 노티파이가 어떤 키에 위치한 스킬인지를 의미한다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESkillKeyMapping MappingKey;
	// 스폰된 투사체 액터
	UPROPERTY()
	class AAdditionalEffectActor* EffectActor;
};
