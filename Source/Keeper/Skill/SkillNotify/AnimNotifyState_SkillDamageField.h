// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "../SkillDataStruct.h"
#include "AnimNotifyState_SkillDamageField.generated.h"


/**
 * 
 */
UCLASS()
class KEEPER_API UAnimNotifyState_SkillDamageField : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	virtual void PostLoad() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:
	// 해당 데미지필드 노티파이가 어떤 키에 위치한 스킬인지를 의미한다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESkillKeyMapping MappingKey;
	UPROPERTY()
	class ABaseSkillDamageField* SpawnedDamageField;
	// Location offset from socket
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify")
	FVector LocationOffset;
	// Rotation offset from socket
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify")
	FRotator RotationOffset;
	// Scale to spawn the particle system at
	UPROPERTY(EditAnywhere, Category = "AnimNotify")
	FVector Scale;

private:
	float					DamageRadius;
	float                   ActualDamage;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float BaseDamage;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float DamageCoefficient;

	FQuat RotationOffsetQuat;

public:
	void ModifyDamageFieldMembers(float NewDamage, float NewCoefficient, float NewRadius);
};
