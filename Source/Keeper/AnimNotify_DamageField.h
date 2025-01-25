// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_DamageField.generated.h"

/**
 * 
 */
UCLASS()
class KEEPER_API UAnimNotify_DamageField : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	virtual FString GetNotifyName_Implementation() const override;

	virtual void PostLoad() override;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float  DamageFieldRadius;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ADamageField_Base>  DamageFieldClass;

	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	ADamageField_Base* GetSpawnedDamageField();
	
	UPROPERTY()
	ADamageField_Base* SpawnedDamageField;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AnimNotify")
	FVector LocationOffset;

	// Rotation offset from socket
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AnimNotify")
	FRotator RotationOffset;

	// Scale to spawn the particle system at
	UPROPERTY(EditAnywhere, Category="AnimNotify")
	FVector Scale;

	UPROPERTY(EditAnywhere, Category="AnimNotify")
	float DamageFieldLifeTime;

private:
	FQuat RotationOffsetQuat;
};
