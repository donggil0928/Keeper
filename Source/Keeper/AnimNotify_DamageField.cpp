// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_DamageField.h"

#if WITH_EDITOR
#include "AnimationEditorViewportClient.h"
#endif

#include "DamageField_Base.h"

#if WITH_EDITOR
#include "Subsystems/EditorActorSubsystem.h"
#endif

void UAnimNotify_DamageField::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                     const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const FTransform MeshTransform = MeshComp->GetComponentTransform();
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(MeshTransform.TransformPosition(LocationOffset));
		SpawnTransform.SetRotation(MeshTransform.GetRotation() * RotationOffsetQuat);
		SpawnTransform.SetScale3D(Scale);
		
		SpawnedDamageField = MeshComp->GetWorld()->SpawnActor<ADamageField_Base>(DamageFieldClass, SpawnTransform, SpawnInfo);
		if (SpawnedDamageField.IsValid()) 
		{
			SpawnedDamageField->CreateDamageField_Sphere(DamageFieldRadius);

			if (DamageFieldNiagaraEffect)
			{
				SpawnedDamageField->DamageEffectNiagara = DamageFieldNiagaraEffect;
			}

			if (DamageFieldLifeTime > 0.f)
			{
				SpawnedDamageField->SetLifeSpan(DamageFieldLifeTime);
			}
		}
	}
}

FString UAnimNotify_DamageField::GetNotifyName_Implementation() const
{
	if (DamageFieldClass)
	{
		return DamageFieldClass->GetName();
	}
	else
	{
		return Super::GetNotifyName_Implementation();
	}
}

void UAnimNotify_DamageField::PostLoad()
{
	Super::PostLoad();

	RotationOffsetQuat = FQuat(RotationOffset);
}

#if WITH_EDITOR
void UAnimNotify_DamageField::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.MemberProperty && PropertyChangedEvent.MemberProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UAnimNotify_DamageField, RotationOffset))
	{
		RotationOffsetQuat = FQuat(RotationOffset);
	}
}
#endif

ADamageField_Base* UAnimNotify_DamageField::GetSpawnedDamageField()
{
	return SpawnedDamageField.IsValid() ? SpawnedDamageField.Get() : nullptr;
}
