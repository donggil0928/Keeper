// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterBase.generated.h"

UCLASS()
class KEEPER_API AMonsterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AMonsterBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	class UBehaviorTree* BehaviorTree;
	
	void TakeDamage(float DamageAmount);

	void SomeEventTrigger();
	void ResetMovementSpeed();
	
	float GetCurrentHP() const { return CurrentHP; }
	
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Die();

	UFUNCTION(BlueprintCallable, Category="Movement")
	void SetMovementSpeed(float NewSpeed);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int32 MaxHP;		// 몬스터의 최대 HP

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int32 CurrentHP;	// 몬스터의 현재 HP

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int32 MonsterAtk;	// 몬스터의 공격력

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int32 MonsterDef;	// 몬스터의 방어력

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int32 MonsterExp;	// 몬스터가 주는 마석

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int32 MonsterCoin;	// 몬스터가 주는 돈
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement", meta = (AllowPrivateAccess = "true"))
	float DefaultMovementSpeed; // 몬스터의 이동속도
};
