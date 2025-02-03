// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseSkillDamageField.generated.h"

UCLASS()
class KEEPER_API ABaseSkillDamageField : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseSkillDamageField();

public:	
	void CreateDamageField_Sphere(float Radius, float Damage);

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void SetDamage(float ActualDamage);

	void SetEffectDuration(float InDuration);
	void SpawnEffectActorToTarget(class AMonsterBase* InTarget);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//---
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//---

public:
	USceneComponent* CachedRootComponent;
	class USphereComponent* HitSphereComponent;

	UPROPERTY()
	TSubclassOf<class AAdditionalEffectActor> EffectActor;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Damage")
	float DamageAmount;

	UPROPERTY()
	float Duration;
};
