// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_DamageField.h"

#include "AnimationEditorViewportClient.h"
#include "DamageField_Base.h"
#include "Subsystems/EditorActorSubsystem.h"

void UAnimNotify_DamageField::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                     const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (SpawndDamageField)
	{
		SpawndDamageField->Destroy();
		SpawndDamageField = nullptr;
	}
	
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const FTransform MeshTransform = MeshComp->GetComponentTransform();
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(MeshTransform.TransformPosition(LocationOffset));
		SpawnTransform.SetRotation(MeshTransform.GetRotation() * RotationOffsetQuat);
		SpawnTransform.SetScale3D(Scale);
		
		SpawndDamageField = MeshComp->GetWorld()->SpawnActor<ADamageField_Base>(DamageFieldClass, SpawnTransform, SpawnInfo);
		SpawndDamageField->CreateDamageField_Sphere(DamageFieldRadius);

		if (DamageFieldLifeTime > 0.f)
		{
			SpawndDamageField->SetLifeSpan(DamageFieldLifeTime);
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

ADamageField_Base* UAnimNotify_DamageField::GetSpawndDamageField()
{
	return SpawndDamageField;
}
