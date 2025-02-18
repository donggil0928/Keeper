// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_TestSkillNotify.generated.h"

/**
 * 
 */
UCLASS()
class KEEPER_API UAnimNotify_TestSkillNotify : public UAnimNotify
{
	GENERATED_BODY()
	
public:
// Fill out your copyright notice in the Description page of Project Settings.
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

};
