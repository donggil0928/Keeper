// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class KEEPER_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	FName WeaponSocketName = TEXT("WeaponSocket");
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	float BaseDamage = 100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	float WeaponLength = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	float AttackSpeed = 1.0f;
	
};
