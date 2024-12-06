// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageField_Base.generated.h"

UCLASS()
class KEEPER_API ADamageField_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamageField_Base();

	void CreateDamageField_Sphere(float radius);
	
	UFUNCTION(BlueprintCallable)
	class USphereComponent*		GetHitSphereComponent() const;
	
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void SetDamageAmount(float NewDamageAmount);

	// 데미지 활성화/비활성화 함수
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void ActivateDamage();

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void DeactivateDamage();
	//---
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//---
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	//---
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime);
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent*		CachedRootComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent*		HitSphereComponent;
private:
	float					damageRadius;
	float                   damage;
	
	UPROPERTY(EditAnywhere, Category = "Damage")
	float DamageAmount;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float damageCalculation;
	
	UPROPERTY(EditAnywhere, Category = "Damage")
	bool bCanDealDamage;
};
