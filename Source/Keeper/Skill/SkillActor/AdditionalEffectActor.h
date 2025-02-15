// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AdditionalEffectActor.generated.h"

UCLASS()
class KEEPER_API AAdditionalEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAdditionalEffectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// Target액터 변수가 필요. 해당 변수는 생성될 때 Attach된 부모 액터의 정보를 가짐.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class AActor* Target;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UNiagaraComponent* AppliedEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float EffectDuration;

public:
	UFUNCTION()
	void SetTargetActor(AActor* InTarget);
	UFUNCTION()
	void SetEffectDuration(float InDuration);
	UFUNCTION()
	void DestroyEffect();
	UFUNCTION(BlueprintImplementableEvent)
	void ActivateEffectImplement();
};
