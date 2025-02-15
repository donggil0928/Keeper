// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "DamageField_Base.generated.h"

UENUM(BlueprintType)
enum class EDamageTarget : uint8
{
	Monster     UMETA(DisplayName = "Monster Only"),
	Character   UMETA(DisplayName = "Character Only"),
	Both        UMETA(DisplayName = "Both")
};

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	class UNiagaraSystem* DamageEffectNiagara;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Screen Effect")
	// bool bEnableScreenShake = false;
	//
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Screen Effect", meta = (EditCondition = "bEnableScreenShake"))
	// TSubclassOf<UCameraShakeBase> DamageFieldCameraShake;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	EDamageTarget TargetType;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime);
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* CachedRootComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* HitSphereComponent;

private:
	float damageRadius;
	float damage;
	
	UPROPERTY(EditAnywhere, Category = "Damage")
	float DamageAmount;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float damageCalculation;
	
	UPROPERTY(EditAnywhere, Category = "Damage")
	bool bCanDealDamage;

	TArray<ADamageField_Base*> SpawnedDamageFields;
};
