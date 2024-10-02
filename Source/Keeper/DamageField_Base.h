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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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
};
